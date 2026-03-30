#include "nfx/graphics/gl/pipeline/Renderer.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "gl/material/ShaderFeatures.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <utility>

namespace nfx::graphics::gl
{
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

        bindFrameScope();
        validatePermutations();

        const auto& ctx = Context::current();
        const auto& gl = ctx.functions();
        const bool debugGroups = ctx.isVersionSupported(4, 3);

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

            if (debugGroups)
            {
                gl.glPushDebugGroup(DEBUG_SOURCE_APPLICATION, 0, -1, passPtr->name().c_str());
            }

            passPtr->begin();
            passPtr->execute(*m_resources);
            passPtr->end();

            if (debugGroups)
            {
                gl.glPopDebugGroup();
            }
        }
    }

    void Renderer::bindFrameScope()
    {
        if (!m_frameData.has_value())
        {
            std::fprintf(stderr, "[Renderer] WARNING: render() called without setFrameData()\n");
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
    }

    void Renderer::validatePermutations()
    {
        if (m_validationMode == ValidationMode::Off || !m_frameData)
        {
            return;
        }

        const FrameData& frame = *m_frameData;

        // Validate shadow data consistency:
        // If directional shadow is enabled, verify the shadow map is populated
        if (frame.hasDirShadow)
        {
            if (frame.dirShadowMap.texture.id == 0)
            {
                if (m_validationMode == ValidationMode::Warn)
                {
                    std::fprintf(stderr, "[Renderer] WARNING: hasDirShadow=true but dirShadowMap texture is invalid\n");
                }
                else if (m_validationMode == ValidationMode::Strict)
                {
                    std::fprintf(stderr, "[Renderer] ERROR: hasDirShadow=true but dirShadowMap texture is invalid\n");
                    std::abort();
                }
            }
        }

        // Validate spot shadow data consistency
        for (int i = 0; i < frame.spotShadowCount; ++i)
        {
            if (frame.spotShadowMaps[i].texture.id == 0)
            {
                if (m_validationMode == ValidationMode::Warn)
                {
                    std::fprintf(
                        stderr,
                        "[Renderer] WARNING: spotShadowCount=%d but spotShadowMaps[%d] texture is invalid\n",
                        frame.spotShadowCount,
                        i);
                }
                else if (m_validationMode == ValidationMode::Strict)
                {
                    std::fprintf(
                        stderr,
                        "[Renderer] ERROR: spotShadowCount=%d but spotShadowMaps[%d] texture is invalid\n",
                        frame.spotShadowCount,
                        i);
                    std::abort();
                }
            }
        }

        // Validate point shadow data consistency
        for (int i = 0; i < frame.pointShadowCount; ++i)
        {
            if (frame.pointShadowMaps[i].texture.id == 0)
            {
                if (m_validationMode == ValidationMode::Warn)
                {
                    std::fprintf(
                        stderr,
                        "[Renderer] WARNING: pointShadowCount=%d but pointShadowMaps[%d] texture is invalid\n",
                        frame.pointShadowCount,
                        i);
                }
                else if (m_validationMode == ValidationMode::Strict)
                {
                    std::fprintf(
                        stderr,
                        "[Renderer] ERROR: pointShadowCount=%d but pointShadowMaps[%d] texture is invalid\n",
                        frame.pointShadowCount,
                        i);
                    std::abort();
                }
            }
        }
    }
} // namespace nfx::graphics::gl
