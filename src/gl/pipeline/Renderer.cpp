#include "nfx/graphics/gl/pipeline/Renderer.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/frame/RenderResources.h"
#include "nfx/graphics/gl/pipeline/passes/AxesPass.h"
#include "nfx/graphics/gl/pipeline/passes/DirectionalShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/EnvironmentPass.h"
#include "nfx/graphics/gl/pipeline/passes/GeometryPass.h"
#include "nfx/graphics/gl/pipeline/passes/GridPass.h"
#include "nfx/graphics/gl/pipeline/passes/ImagePlanePass.h"
#include "nfx/graphics/gl/pipeline/passes/OutlinePass.h"
#include "nfx/graphics/gl/pipeline/passes/PointShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/Polygon2DPass.h"
#include "nfx/graphics/gl/pipeline/passes/PresentPass.h"
#include "nfx/graphics/gl/pipeline/passes/SkyboxPass.h"
#include "nfx/graphics/gl/pipeline/passes/SpotShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/TextPass.h"
#include "nfx/graphics/gl/pipeline/passes/TransparentPass.h"
#include "nfx/graphics/gl/pipeline/passes/WboitPass.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "gl/material/ShaderFeatures.h"
#include "detail/RasterRegionResolution.h"
#include "internal/runtime/Error.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <functional>
#include <utility>

namespace nfx::graphics::gl
{
    namespace
    {
        enum class PassStage : int
        {
            Shadows = 0,
            Opaque,
            Environment,
            Transparent,
            Overlays,
            FinalComposite,
            Present
        };

        class PassOrderingPolicy final
        {
        public:
            static void sort(std::vector<std::unique_ptr<RenderPass>>& passes)
            {
                std::stable_sort(passes.begin(), passes.end(), Less{});
            }

        private:
            static PassStage stageOf(const RenderPass& pass)
            {
                if (dynamic_cast<const DirectionalShadowPass*>(&pass) || dynamic_cast<const SpotShadowPass*>(&pass) ||
                    dynamic_cast<const PointShadowPass*>(&pass))
                {
                    return PassStage::Shadows;
                }
                if (dynamic_cast<const GeometryPass*>(&pass))
                {
                    return PassStage::Opaque;
                }
                if (dynamic_cast<const SkyboxPass*>(&pass) || dynamic_cast<const EnvironmentPass*>(&pass))
                {
                    return PassStage::Environment;
                }
                if (dynamic_cast<const WboitPass*>(&pass) || dynamic_cast<const TransparentPass*>(&pass))
                {
                    return PassStage::Transparent;
                }
                if (dynamic_cast<const GridPass*>(&pass) || dynamic_cast<const AxesPass*>(&pass) ||
                    dynamic_cast<const ImagePlanePass*>(&pass) || dynamic_cast<const TextPass*>(&pass) ||
                    dynamic_cast<const Polygon2DPass*>(&pass))
                {
                    return PassStage::Overlays;
                }
                if (dynamic_cast<const OutlinePass*>(&pass))
                {
                    return PassStage::FinalComposite;
                }
                if (dynamic_cast<const PresentPass*>(&pass))
                {
                    return PassStage::Present;
                }
                return PassStage::FinalComposite;
            }

            struct Less
            {
                bool operator()(const std::unique_ptr<RenderPass>& lhs, const std::unique_ptr<RenderPass>& rhs) const
                {
                    return static_cast<int>(PassOrderingPolicy::stageOf(*lhs)) <
                           static_cast<int>(PassOrderingPolicy::stageOf(*rhs));
                }
            };
        };

        [[nodiscard]] RasterValidationMode toRasterValidationMode(Renderer::ValidationMode mode) noexcept
        {
            switch (mode)
            {
                case Renderer::ValidationMode::Strict:
                    return RasterValidationMode::Strict;
                case Renderer::ValidationMode::Warn:
                    return RasterValidationMode::Warn;
                case Renderer::ValidationMode::Off:
                    return RasterValidationMode::Off;
            }
            return RasterValidationMode::Warn;
        }

        [[nodiscard]] const char* rasterStatusString(RasterResolutionStatus status) noexcept
        {
            switch (status)
            {
                case RasterResolutionStatus::Ok:
                    return "Ok";
                case RasterResolutionStatus::InvalidSurfaceExtent:
                    return "InvalidSurfaceExtent";
                case RasterResolutionStatus::InvalidViewViewport:
                    return "InvalidViewViewport";
                case RasterResolutionStatus::MissingExplicitViewport:
                    return "MissingExplicitViewport";
                case RasterResolutionStatus::InvalidExplicitViewport:
                    return "InvalidExplicitViewport";
                case RasterResolutionStatus::MissingExplicitScissor:
                    return "MissingExplicitScissor";
                case RasterResolutionStatus::InvalidExplicitScissor:
                    return "InvalidExplicitScissor";
            }
            return "UnknownRasterStatus";
        }

        void applyResolvedRasterState(const ResolvedRasterState& state, const Functions& gl)
        {
            gl.glViewport(state.viewport.x, state.viewport.y, state.viewport.width, state.viewport.height);
            if (state.scissorEnabled)
            {
                gl.glEnable(SCISSOR_TEST);
                gl.glScissor(state.scissor.x, state.scissor.y, state.scissor.width, state.scissor.height);
            }
            else
            {
                gl.glDisable(SCISSOR_TEST);
            }
        }
    } // namespace

    Renderer::~Renderer()
    {
        if (!m_gpuQueriesInitialized)
        {
            return;
        }
        if (!Context::isInitialized())
        {
            return;
        }

        const auto& gl = Context::current().functions();
        gl.glDeleteQueries(static_cast<GLsizei>(m_gpuFrameQueries.size()), m_gpuFrameQueries.data());

        m_gpuQueriesInitialized = false;
        m_gpuFrameQueries = { 0u, 0u };
    }

    void Renderer::addPass(std::unique_ptr<RenderPass> pass)
    {
        if (!pass)
        {
            return;
        }
        m_passes.push_back(std::move(pass));
    }

    RenderPass* Renderer::pass(std::string_view name) noexcept
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        return (it != m_passes.end()) ? it->get() : nullptr;
    }

    const RenderPass* Renderer::pass(std::string_view name) const noexcept
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        return (it != m_passes.end()) ? it->get() : nullptr;
    }

    bool Renderer::removePass(std::string_view name)
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        if (it == m_passes.end())
        {
            return false;
        }
        m_passes.erase(it);
        return true;
    }

    void Renderer::initialize(RenderResources& resources)
    {
        m_resources = &resources;

        PassOrderingPolicy::sort(m_passes);

        for (auto& passPtr : m_passes)
        {
            if (!passPtr)
            {
                continue;
            }
            if (!passPtr->m_initialized)
            {
                passPtr->m_initialized = passPtr->initialize();
            }
        }
    }

    void Renderer::render()
    {
        assert(m_resources && "Renderer::render: call initialize() before render()");
        if (!m_resources)
        {
            return;
        }

        const auto frameStart = std::chrono::steady_clock::now();

        m_frameStats = {};
        m_frameStats.frameIndex = ++m_nextFrameIndex;

        validatePermutations();
        bindFrameScope();

        const auto& ctx = Context::current();
        const auto& gl = ctx.functions();
        const bool debugGroups = ctx.isVersionSupported(4, 3);

        m_gpuTimingSupported = ctx.isVersionSupported(3, 3);
        if (m_gpuTimingSupported)
        {
            if (!m_gpuQueriesInitialized)
            {
                gl.glGenQueries(static_cast<GLsizei>(m_gpuFrameQueries.size()), m_gpuFrameQueries.data());
                m_gpuQueriesInitialized = true;
                m_gpuQueryWriteIndex = 0;
            }

            gl.glBeginQuery(TIME_ELAPSED, m_gpuFrameQueries[m_gpuQueryWriteIndex]);
        }
        else
        {
            m_frameStats.gpuFrameMs = 0.0f;
        }

        bool abortFrame = false;

        for (auto& passPtr : m_passes)
        {
            if (!passPtr)
            {
                continue;
            }
            if (!passPtr->isEnabled())
            {
                continue;
            }

            // Lazy-initialize passes added after initialize()
            if (!passPtr->m_initialized)
            {
                passPtr->m_initialized = passPtr->initialize();
            }

            if (!passPtr->m_initialized)
            {
                continue; // initialization failed, skip
            }

            GLint activeViewport[4] = { 0, 0, 1, 1 };
            gl.glGetIntegerv(VIEWPORT, activeViewport);

            RasterResolutionInput rasterInput;
            rasterInput.targetExtent = { std::max(activeViewport[2], 1), std::max(activeViewport[3], 1) };
            rasterInput.viewViewport =
                m_viewport ? *m_viewport
                           : ViewportRect{ 0, 0, rasterInput.targetExtent.width, rasterInput.targetExtent.height };

            if (m_viewport && m_viewport->x >= 0 && m_viewport->y >= 0)
            {
                rasterInput.targetExtent.width = std::max(rasterInput.targetExtent.width, m_viewport->right());
                rasterInput.targetExtent.height = std::max(rasterInput.targetExtent.height, m_viewport->top());
            }

            const RasterResolutionResult raster =
                detail::resolveRasterState(rasterInput, toRasterValidationMode(m_validationMode));

            if (!raster.ok())
            {
                char msg[192];
                std::snprintf(
                    msg,
                    sizeof(msg),
                    "render: pass '%s' raster resolution failed (%s)",
                    passPtr->name().c_str(),
                    rasterStatusString(raster.status));
                internal::runtime::logError(
                    "Renderer", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);

                if (raster.disposition == RasterResolutionDisposition::AbortFrame)
                {
                    abortFrame = true;
                    break;
                }

                continue;
            }

            applyResolvedRasterState(raster.state, gl);

            if (debugGroups)
            {
                gl.glPushDebugGroup(DEBUG_SOURCE_APPLICATION, 0, -1, passPtr->name().c_str());
            }

            passPtr->m_frameData = m_frameData ? &*m_frameData : nullptr;
            passPtr->m_viewport = m_viewport ? &*m_viewport : nullptr;
            passPtr->begin();
            passPtr->execute(*m_resources);
            passPtr->end();

            ++m_frameStats.passesExecuted;

            if (const auto* geometry = dynamic_cast<const GeometryPass*>(passPtr.get()))
            {
                const auto queueSize = geometry->queue().size();
                const auto& culling = geometry->cullingStats();
                const auto& execution = geometry->executionStats();

                m_frameStats.commandsSubmitted += static_cast<std::uint32_t>(queueSize);
                m_frameStats.commandsRejected += culling.commandsInvalid;
                m_frameStats.opaqueDraws += culling.commandsDrawn;
                m_frameStats.drawCalls += culling.commandsDrawn;
                m_frameStats.commandsDrawn += culling.commandsDrawn;
                m_frameStats.frustumTested += culling.commandsTested;
                m_frameStats.frustumCulled += culling.commandsCulled;
                m_frameStats.invalidBounds += culling.invalidBounds;
                m_frameStats.accepted += culling.commandsDrawn;
                m_frameStats.shaderBinds += execution.shaderBinds;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.textureBinds += execution.textureBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;

                m_stats.totalCulledCommands += culling.commandsCulled;
            }
            else if (const auto* transparent = dynamic_cast<const TransparentPass*>(passPtr.get()))
            {
                const auto& execution = transparent->executionStats();

                m_frameStats.commandsSubmitted += execution.commandsSubmitted;
                m_frameStats.commandsRejected += execution.commandsInvalid;
                m_frameStats.transparentDraws += execution.commandsDrawn;
                m_frameStats.transparentRejected += execution.commandsInvalid;
                m_frameStats.drawCalls += execution.commandsDrawn;
                m_frameStats.commandsDrawn += execution.commandsDrawn;
                m_frameStats.shaderBinds += execution.shaderBinds;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.textureBinds += execution.textureBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;
            }
            else if (const auto* wboit = dynamic_cast<const WboitPass*>(passPtr.get()))
            {
                const auto& execution = wboit->executionStats();

                m_frameStats.commandsSubmitted += execution.commandsSubmitted;
                m_frameStats.commandsRejected += execution.commandsInvalid;
                m_frameStats.transparentDraws += execution.commandsDrawn;
                m_frameStats.transparentRejected += execution.commandsInvalid;
                m_frameStats.drawCalls += execution.commandsDrawn;
                m_frameStats.commandsDrawn += execution.commandsDrawn;
                m_frameStats.shaderBinds += execution.shaderBinds;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.textureBinds += execution.textureBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;
            }
            else if (const auto* dirShadow = dynamic_cast<const DirectionalShadowPass*>(passPtr.get()))
            {
                const auto& execution = dirShadow->executionStats();

                m_frameStats.commandsSubmitted += execution.commandsSubmitted;
                m_frameStats.commandsRejected += execution.commandsInvalid;
                m_frameStats.shadowDraws += execution.commandsDrawn;
                m_frameStats.shadowRejected += execution.commandsInvalid;
                if (execution.commandsSubmitted > 0)
                {
                    ++m_frameStats.lightsCastingShadows;
                }
                m_frameStats.drawCalls += execution.commandsDrawn;
                m_frameStats.commandsDrawn += execution.commandsDrawn;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;
            }
            else if (const auto* spotShadow = dynamic_cast<const SpotShadowPass*>(passPtr.get()))
            {
                const auto& execution = spotShadow->executionStats();

                m_frameStats.commandsSubmitted += execution.commandsSubmitted;
                m_frameStats.commandsRejected += execution.commandsInvalid;
                m_frameStats.shadowDraws += execution.commandsDrawn;
                m_frameStats.shadowRejected += execution.commandsInvalid;
                m_frameStats.lightsCastingShadows += static_cast<std::uint32_t>(std::max(spotShadow->lightCount(), 0));
                m_frameStats.drawCalls += execution.commandsDrawn;
                m_frameStats.commandsDrawn += execution.commandsDrawn;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;
            }
            else if (const auto* pointShadow = dynamic_cast<const PointShadowPass*>(passPtr.get()))
            {
                const auto& execution = pointShadow->executionStats();

                m_frameStats.commandsSubmitted += execution.commandsSubmitted;
                m_frameStats.commandsRejected += execution.commandsInvalid;
                m_frameStats.shadowDraws += execution.commandsDrawn;
                m_frameStats.shadowRejected += execution.commandsInvalid;
                m_frameStats.lightsCastingShadows += static_cast<std::uint32_t>(std::max(pointShadow->lightCount(), 0));
                m_frameStats.drawCalls += execution.commandsDrawn;
                m_frameStats.commandsDrawn += execution.commandsDrawn;
                m_frameStats.vaoBinds += execution.vaoBinds;
                m_frameStats.vboBinds += execution.vboBinds;
                m_frameStats.fboBinds += execution.fboBinds;
                m_frameStats.instancedDraws += execution.instancedDraws;
            }
            else
            {
                const auto& stats = passPtr->runtimeStats();
                m_frameStats.drawCalls += stats.drawCalls;
                m_frameStats.shaderBinds += stats.shaderBinds;
                m_frameStats.vaoBinds += stats.vaoBinds;
                m_frameStats.vboBinds += stats.vboBinds;
                m_frameStats.fboBinds += stats.fboBinds;
                m_frameStats.textureBinds += stats.textureBinds;
            }

            if (debugGroups)
            {
                gl.glPopDebugGroup();
            }
        }

        if (abortFrame)
        {
            internal::runtime::logError(
                "Renderer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "render: frame aborted due to raster validation failure");
        }

        if (m_gpuTimingSupported)
        {
            gl.glEndQuery(TIME_ELAPSED);

            GLuint64 elapsedNs = 0;
            gl.glGetQueryObjectui64v(m_gpuFrameQueries[m_gpuQueryWriteIndex], QUERY_RESULT, &elapsedNs);
            m_lastGpuFrameMs = static_cast<float>(static_cast<double>(elapsedNs) / 1.0e6);
            m_frameStats.gpuFrameMs = m_lastGpuFrameMs;

            m_gpuQueryWriteIndex = 1 - m_gpuQueryWriteIndex;
        }

        ++m_stats.totalFrames;
        m_stats.totalPasses += m_frameStats.passesExecuted;
        m_stats.totalDrawCalls += m_frameStats.drawCalls;
        m_stats.totalInstancedDraws += m_frameStats.instancedDraws;
        m_stats.totalTextureBinds += m_frameStats.textureBinds;
        m_stats.totalFboBinds += m_frameStats.fboBinds;
        m_stats.totalVboBinds += m_frameStats.vboBinds;
        m_stats.totalStateChanges +=
            static_cast<std::uint64_t>(m_frameStats.shaderBinds) + static_cast<std::uint64_t>(m_frameStats.vaoBinds) +
            static_cast<std::uint64_t>(m_frameStats.vboBinds) + static_cast<std::uint64_t>(m_frameStats.textureBinds) +
            static_cast<std::uint64_t>(m_frameStats.fboBinds);

        const auto frameEnd = std::chrono::steady_clock::now();
        m_frameStats.cpuFrameMs = std::chrono::duration<float, std::milli>(frameEnd - frameStart).count();
        m_frameStats.fps = (m_frameStats.cpuFrameMs > 0.0f) ? (1000.0f / m_frameStats.cpuFrameMs) : 0.0f;
    }

    void Renderer::bindFrameScope()
    {
        if (!m_frameData.has_value())
        {
            internal::runtime::logError(
                "Renderer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "render() called without setFrameData()");
            return;
        }
        if (!m_resources)
        {
            return;
        }
        if (!m_cameraUbo)
        {
            m_cameraUbo.emplace();
        }
        if (!m_ambientUbo)
        {
            m_ambientUbo.emplace();
        }
        if (!m_directionalUbo)
        {
            m_directionalUbo.emplace();
        }
        if (!m_shadowMatricesUbo)
        {
            m_shadowMatricesUbo.emplace();
        }
        if (!m_iblFrameUbo)
        {
            m_iblFrameUbo.emplace();
        }
        if (!m_punctualLightsSsbo)
        {
            m_punctualLightsSsbo.emplace();
        }

        const FrameData& frame = *m_frameData;

        // UBOs
        m_cameraUbo->upload(frame.camera);
        m_cameraUbo->bind(UboBindings::CameraBlock);

        m_ambientUbo->upload(frame.ambientLight);
        m_ambientUbo->bind(UboBindings::AmbientLightBlock);

        m_directionalUbo->upload(frame.directionalLight);
        m_directionalUbo->bind(UboBindings::DirectionalLightBlock);

        IblFrameBlockData iblFrame;
        iblFrame.flags[0] = frame.hasEnvMap ? 1 : 0;
        iblFrame.flags[1] = frame.hasIrradianceMap ? 1 : 0;
        iblFrame.flags[2] = frame.hasPrefilteredEnvMap ? 1 : 0;
        iblFrame.flags[3] = frame.hasBrdfLut ? 1 : 0;
        m_iblFrameUbo->upload(iblFrame);
        m_iblFrameUbo->bind(UboBindings::IblFrameBlock);

        // Shadow matrices block built from FrameData so all fields are correct
        // When hasDirShadow=false, use a sentinel that makes proj.z = 2.0 > 1.0 for any
        // world position, guaranteeing shadowFactor() early-outs as fully lit
        ShadowMatricesBlockData smb;
        if (frame.hasDirShadow)
        {
            std::copy(
                std::begin(frame.dirShadowMap.lightSpaceMatrix),
                std::end(frame.dirShadowMap.lightSpaceMatrix),
                std::begin(smb.dirLightSpace));
        }
        else
        {
            std::fill(std::begin(smb.dirLightSpace), std::end(smb.dirLightSpace), 0.f);
            smb.dirLightSpace[14] = 2.f; // col3.z -> clip z = 2 > 1 -> no shadow
            smb.dirLightSpace[15] = 1.f; // col3.w -> clip w = 1 (valid perspective divide)
        }
        const int nSpot = std::min(frame.spotShadowCount, static_cast<int>(PipelineLimits::MaxSpotShadows));
        const int nPoint = std::min(frame.pointShadowCount, static_cast<int>(PipelineLimits::MaxPointShadows));
        smb.shadowInfo[0] = nSpot;
        smb.shadowInfo[1] = nPoint;
        smb.shadowInfo[2] = frame.hasDirShadow ? 1 : 0;
        smb.shadowInfo[3] = frame.hasEnvMap ? 1 : 0;

        for (int i = 0; i < nSpot; ++i)
        {
            std::copy(
                std::begin(frame.spotShadowMaps[i].lightSpaceMatrix),
                std::end(frame.spotShadowMaps[i].lightSpaceMatrix),
                std::begin(smb.spotLightSpace[i]));
        }
        m_shadowMatricesUbo->upload(smb);
        m_shadowMatricesUbo->bind(UboBindings::ShadowMatricesBlock);

        // SSBO LightBlock (packed from FrameData::lights at render time)
        {
            PunctualLight::GpuBlock lightBlock;
            const int n = static_cast<int>(frame.lights.size());
            lightBlock.count = n < PunctualLight::MaxLights ? n : PunctualLight::MaxLights;
            for (int i = 0; i < lightBlock.count; ++i)
            {
                lightBlock.lights[i] = frame.lights[i];
            }
            m_punctualLightsSsbo->upload(lightBlock);
        }
        m_punctualLightsSsbo->bind(SsboBindings::PunctualLightsBlock);

        // units 4-7: point shadow cube maps
        {
            const int maxPoint = static_cast<int>(PipelineLimits::MaxPointShadows);
            for (int i = 0; i < maxPoint; ++i)
            {
                if (i < frame.pointShadowCount)
                {
                    if (const TextureCube* tex = m_resources->texturesCube.get(frame.pointShadowMaps[i].texture))
                    {
                        tex->bind(TextureBindings::PointShadowMapBase + i);
                    }
                }
            }
        }

        // units 8-11: spot shadow maps
        {
            const int maxSpot = static_cast<int>(PipelineLimits::MaxSpotShadows);
            for (int i = 0; i < maxSpot; ++i)
            {
                if (i < frame.spotShadowCount)
                {
                    if (const Texture2D* tex = m_resources->textures2D.get(frame.spotShadowMaps[i].texture))
                    {
                        tex->bind(TextureBindings::SpotShadowMapBase + i);
                    }
                }
            }
        }

        // unit 12: directional shadow map
        if (frame.hasDirShadow)
        {
            if (const Texture2D* tex = m_resources->textures2D.get(frame.dirShadowMap.texture))
            {
                tex->bind(TextureBindings::DirectionalShadowMap);
            }
        }

        // unit 13: environment cube map
        {
            const GLuint envUnit = TextureBindings::EnvMap;
            if (frame.hasEnvMap)
            {
                if (const TextureCube* tex = m_resources->texturesCube.get(frame.envMap))
                {
                    tex->bind(envUnit);
                }
                else
                {
                    TextureCube::unbind(envUnit);
                }
            }
            else
            {
                TextureCube::unbind(envUnit);
            }

            if (frame.hasEnvSampler)
            {
                if (const Sampler* sampler = m_resources->samplers.get(frame.envSampler))
                {
                    sampler->bind(envUnit);
                }
                else
                {
                    Sampler::unbind(envUnit);
                }
            }
            else
            {
                Sampler::unbind(envUnit);
            }
        }

        if (frame.hasIrradianceMap)
        {
            if (const TextureCube* tex = m_resources->texturesCube.get(frame.irradianceMap))
            {
                tex->bind(TextureBindings::IrradianceMap);
            }
            else
            {
                TextureCube::unbind(TextureBindings::IrradianceMap);
            }
        }
        else
        {
            TextureCube::unbind(TextureBindings::IrradianceMap);
        }

        if (frame.hasPrefilteredEnvMap)
        {
            if (const TextureCube* tex = m_resources->texturesCube.get(frame.prefilteredEnvMap))
            {
                tex->bind(TextureBindings::PrefilteredEnvMap);
            }
            else
            {
                TextureCube::unbind(TextureBindings::PrefilteredEnvMap);
            }
        }
        else
        {
            TextureCube::unbind(TextureBindings::PrefilteredEnvMap);
        }

        if (frame.hasEnvSampler)
        {
            if (const Sampler* sampler = m_resources->samplers.get(frame.envSampler))
            {
                sampler->bind(TextureBindings::IrradianceMap);
                sampler->bind(TextureBindings::PrefilteredEnvMap);
            }
            else
            {
                Sampler::unbind(TextureBindings::IrradianceMap);
                Sampler::unbind(TextureBindings::PrefilteredEnvMap);
            }
        }
        else
        {
            Sampler::unbind(TextureBindings::IrradianceMap);
            Sampler::unbind(TextureBindings::PrefilteredEnvMap);
        }

        if (frame.hasBrdfLut)
        {
            if (const Texture2D* tex = m_resources->textures2D.get(frame.brdfLut))
            {
                tex->bind(TextureBindings::BrdfLut);
            }
            else
            {
                Texture2D::unbind(TextureBindings::BrdfLut);
            }
        }
        else
        {
            Texture2D::unbind(TextureBindings::BrdfLut);
        }
    }

    void Renderer::validatePermutations()
    {
        if (m_validationMode == ValidationMode::Off || !m_frameData)
        {
            return;
        }

        const FrameData& frame = *m_frameData;

        auto warnOnce = [&](std::string_view warnMsg) {
            const auto h = static_cast<std::uint32_t>(std::hash<std::string_view>{}(warnMsg));
            if (!m_validatedPermutations.insert(h).second)
            {
                return;
            }
            internal::runtime::logError(
                "Renderer", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Invariant, warnMsg);
        };

        auto fail = [&](std::string_view warnMsg, std::string_view errMsg) {
            if (m_validationMode == ValidationMode::Warn)
            {
                warnOnce(warnMsg);
            }
            else if (m_validationMode == ValidationMode::Strict)
            {
                internal::runtime::logError(
                    "Renderer", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::Invariant, errMsg);
                std::abort();
            }
        };

        if (frame.spotShadowCount < 0 || frame.spotShadowCount > static_cast<int>(PipelineLimits::MaxSpotShadows))
        {
            fail(
                "spotShadowCount is out of range for PipelineLimits::MaxSpotShadows",
                "spotShadowCount is out of range for PipelineLimits::MaxSpotShadows");
        }

        if (frame.pointShadowCount < 0 || frame.pointShadowCount > static_cast<int>(PipelineLimits::MaxPointShadows))
        {
            fail(
                "pointShadowCount is out of range for PipelineLimits::MaxPointShadows",
                "pointShadowCount is out of range for PipelineLimits::MaxPointShadows");
        }

        const int spotCount = std::clamp(frame.spotShadowCount, 0, static_cast<int>(PipelineLimits::MaxSpotShadows));
        const int pointCount = std::clamp(frame.pointShadowCount, 0, static_cast<int>(PipelineLimits::MaxPointShadows));

        if (frame.hasEnvMap && !m_resources->texturesCube.get(frame.envMap))
        {
            fail(
                "hasEnvMap=true but envMap does not resolve to a cached cubemap",
                "hasEnvMap=true but envMap does not resolve to a cached cubemap");
        }

        if (frame.hasEnvSampler && !m_resources->samplers.get(frame.envSampler))
        {
            fail(
                "hasEnvSampler=true but envSampler does not resolve to a cached sampler",
                "hasEnvSampler=true but envSampler does not resolve to a cached sampler");
        }

        if (frame.hasEnvSampler && !frame.hasEnvMap)
        {
            fail("hasEnvSampler=true while hasEnvMap=false", "hasEnvSampler=true while hasEnvMap=false");
        }

        if (frame.hasIrradianceMap && !m_resources->texturesCube.get(frame.irradianceMap))
        {
            fail(
                "hasIrradianceMap=true but irradianceMap does not resolve to a cached cubemap",
                "hasIrradianceMap=true but irradianceMap does not resolve to a cached cubemap");
        }

        if (frame.hasPrefilteredEnvMap && !m_resources->texturesCube.get(frame.prefilteredEnvMap))
        {
            fail(
                "hasPrefilteredEnvMap=true but prefilteredEnvMap does not resolve to a cached cubemap",
                "hasPrefilteredEnvMap=true but prefilteredEnvMap does not resolve to a cached cubemap");
        }

        if (frame.hasBrdfLut && !m_resources->textures2D.get(frame.brdfLut))
        {
            fail(
                "hasBrdfLut=true but brdfLut does not resolve to a cached 2D texture",
                "hasBrdfLut=true but brdfLut does not resolve to a cached 2D texture");
        }

        const bool hasAnySplitSumResource = frame.hasIrradianceMap || frame.hasPrefilteredEnvMap || frame.hasBrdfLut;
        const bool hasCompleteSplitSum = frame.hasIrradianceMap && frame.hasPrefilteredEnvMap && frame.hasBrdfLut;
        if (hasAnySplitSumResource && !hasCompleteSplitSum)
        {
            fail(
                "split-sum resources are incomplete (need hasIrradianceMap, hasPrefilteredEnvMap and hasBrdfLut)",
                "split-sum resources are incomplete (need hasIrradianceMap, hasPrefilteredEnvMap and hasBrdfLut)");
        }

        // Validate shadow data consistency:
        // If directional shadow is enabled, verify the shadow map is populated
        if (frame.hasDirShadow)
        {
            if (frame.dirShadowMap.texture.id == 0)
            {
                fail(
                    "hasDirShadow=true but dirShadowMap texture is invalid",
                    "hasDirShadow=true but dirShadowMap texture is invalid");
            }
        }

        // Validate spot shadow data consistency
        for (int i = 0; i < spotCount; ++i)
        {
            if (frame.spotShadowMaps[i].texture.id == 0)
            {
                if (m_validationMode == ValidationMode::Warn)
                {
                    char msg[160];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "spotShadowCount=%d but spotShadowMaps[%d] texture is invalid",
                        frame.spotShadowCount,
                        i);
                    warnOnce(msg);
                }
                else if (m_validationMode == ValidationMode::Strict)
                {
                    char msg[160];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "spotShadowCount=%d but spotShadowMaps[%d] texture is invalid",
                        frame.spotShadowCount,
                        i);
                    internal::runtime::logError(
                        "Renderer", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::Invariant, msg);
                    std::abort();
                }
            }
        }

        // Validate point shadow data consistency
        for (int i = 0; i < pointCount; ++i)
        {
            if (frame.pointShadowMaps[i].texture.id == 0)
            {
                if (m_validationMode == ValidationMode::Warn)
                {
                    char msg[160];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "pointShadowCount=%d but pointShadowMaps[%d] texture is invalid",
                        frame.pointShadowCount,
                        i);
                    warnOnce(msg);
                }
                else if (m_validationMode == ValidationMode::Strict)
                {
                    char msg[160];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "pointShadowCount=%d but pointShadowMaps[%d] texture is invalid",
                        frame.pointShadowCount,
                        i);
                    internal::runtime::logError(
                        "Renderer", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::Invariant, msg);
                    std::abort();
                }
            }
        }
    }
} // namespace nfx::graphics::gl
