#include "nfx/graphics/gl/pipeline/ForwardRenderPath.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/passes/AxesPass.h"
#include "nfx/graphics/gl/pipeline/passes/EnvironmentPass.h"
#include "nfx/graphics/gl/pipeline/passes/GeometryPass.h"
#include "nfx/graphics/gl/pipeline/passes/GridPass.h"
#include "nfx/graphics/gl/pipeline/passes/ImagePlanePass.h"
#include "nfx/graphics/gl/pipeline/passes/OutlinePass.h"
#include "nfx/graphics/gl/pipeline/passes/Polygon2DPass.h"
#include "nfx/graphics/gl/pipeline/passes/PresentPass.h"
#include "nfx/graphics/gl/pipeline/passes/SkyboxPass.h"
#include "nfx/graphics/gl/pipeline/passes/StrokePass.h"
#include "nfx/graphics/gl/pipeline/passes/TextPass.h"
#include "nfx/graphics/gl/pipeline/passes/TransparentPass.h"
#include "nfx/graphics/gl/pipeline/passes/WboitPass.h"
#include "detail/ViewportValidation.h"
#include "internal/runtime/Error.h"

#include <cstdio>

namespace nfx::graphics::gl
{
    void ForwardRenderPath::reportDuplicateOrReservedPassName(std::string_view api, std::string_view name) noexcept
    {
        char msg[224];
        std::snprintf(
            msg,
            sizeof(msg),
            "%.*s: duplicate or reserved pass name '%.*s'",
            static_cast<int>(api.size()),
            api.data(),
            static_cast<int>(name.size()),
            name.data());
        internal::runtime::logError(
            "ForwardRenderPath", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::Programming, msg);
    }

    void ForwardRenderPath::setClearColor(float r, float g, float b, float a) noexcept
    {
        m_clearColor[0] = r;
        m_clearColor[1] = g;
        m_clearColor[2] = b;
        m_clearColor[3] = a;
    }

    void ForwardRenderPath::setSkybox(TextureCubeCache& cache, TextureCubeHandle cubemap) noexcept
    {
        if (m_initialized)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "setSkybox: cannot change after initialize()");
            assert(false && "ForwardRenderPath::setSkybox: called after initialize");
            return;
        }
        if (m_hasEnvPass)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "setSkybox() overrides enableEnvironment()");
            m_hasEnvPass = false;
        }
        m_skyboxCache = &cache;
        m_skyboxHandle = cubemap;
        m_hasSkybox = true;
    }

    void ForwardRenderPath::enableEnvironment(float intensity) noexcept
    {
        if (m_initialized)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "enableEnvironment: cannot change after initialize()");
            assert(false && "ForwardRenderPath::enableEnvironment: called after initialize");
            return;
        }
        if (m_hasSkybox)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "enableEnvironment() ignored: setSkybox() already set");
            return;
        }
        m_envIntensity = intensity;
        m_hasEnvPass = true;
    }

    void ForwardRenderPath::enableOutline(const float (&color)[3], float thickness) noexcept
    {
        if (m_initialized)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "enableOutline: cannot change after initialize()");
            assert(false && "ForwardRenderPath::enableOutline: called after initialize");
            return;
        }

        m_wantsOutlinePass = true;
        m_outlineColor[0] = color[0];
        m_outlineColor[1] = color[1];
        m_outlineColor[2] = color[2];
        m_outlineThickness = thickness;
    }

    StrokePass* ForwardRenderPath::addStrokePass(std::string name)
    {
        if (isReservedName(name) || m_renderer.pass(name) != nullptr)
        {
            reportDuplicateOrReservedPassName("addStrokePass", name);
            assert(false && "ForwardRenderPath::addStrokePass: duplicate or reserved pass name");
            return nullptr;
        }

        m_strokePass = m_renderer.createPass<StrokePass>(std::move(name));
        return m_strokePass;
    }

    void ForwardRenderPath::initialize(RenderResources& resources)
    {
        if (m_initialized)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "initialize() called more than once");
            assert(false && "ForwardRenderPath::initialize called more than once");
            return;
        }

        m_resources = &resources;

        if (m_hasSkybox && (!m_skyboxCache || !m_skyboxHandle.isValid()))
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "invalid skybox configuration before initialize()");
            assert(false && "ForwardRenderPath::initialize invalid skybox configuration");
            return;
        }

        // Geometry pass
        m_geometryPass = m_renderer.createPass<GeometryPass>("Geometry");
        m_geometryPass->setClearColor(true, m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        m_geometryPass->setClearDepth(true, 1.0f);

        // Background (skybox or environment, mutually exclusive)
        if (m_hasSkybox)
        {
            m_skyboxPass = m_renderer.createPass<SkyboxPass>("Skybox");
            m_skyboxPass->setCubemap(*m_skyboxCache, m_skyboxHandle);
        }
        else if (m_hasEnvPass)
        {
            m_environmentPass = m_renderer.createPass<EnvironmentPass>("Environment");
            m_environmentPass->setIntensity(m_envIntensity);
        }

        // Transparent pass (optional)
        if (m_wantsTransparentPass && m_transparentPassFactory)
        {
            m_transparentPass = m_transparentPassFactory();
        }

        if (m_wantsOutlinePass)
        {
            m_outlinePass = m_renderer.createPass<OutlinePass>("Outline");
            m_outlinePass->setOutlineColor(m_outlineColor);
            m_outlinePass->setThickness(m_outlineThickness);
        }

        // Present pass
        m_presentPass = m_renderer.createPass<PresentPass>("Present");
        m_presentPass->setExposure(m_exposure);
        m_presentPass->setTonemapEnabled(m_tonemapEnabled);
        m_presentPass->setGammaEnabled(m_gammaEnabled);

        m_renderer.initialize(resources);
        m_initialized = true;
    }

    PassTargetBundle ForwardRenderPath::geoOutput() const noexcept
    {
        if (!m_geometryPass)
        {
            return {};
        }
        return { m_geometryPass->colorOutput(), m_geometryPass->depthOutput() };
    }

    void ForwardRenderPath::render(const FrameData& frame, int width, int height)
    {
        if (!m_initialized || !m_resources || !m_geometryPass)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "render() called before successful initialize()");
            assert(false && "ForwardRenderPath::render called before initialize");
            return;
        }

        const int safeW = (width > 0) ? width : 1;
        const int safeH = (height > 0) ? height : 1;

        if (safeW != m_lastWidth || safeH != m_lastHeight)
        {
            m_lastWidth = safeW;
            m_lastHeight = safeH;

            m_geometryPass->setOutputSize(m_resources->textures2D, safeW, safeH);
            rewireTargets();
        }

        const auto& gl = Context::current().functions();
        gl.glViewport(0, 0, static_cast<GLsizei>(safeW), static_cast<GLsizei>(safeH));

        m_renderer.setFrameData(frame);
        m_renderer.resetViewport();
        m_renderer.render();
    }

    void ForwardRenderPath::render(
        const FrameData& frame, int surfaceWidth, int surfaceHeight, const ViewportRect& viewport)
    {
        if (!m_initialized || !m_resources || !m_geometryPass)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "render() called before successful initialize()");
            assert(false && "ForwardRenderPath::render called before initialize");
            return;
        }

        const int safeW = (surfaceWidth > 0) ? surfaceWidth : 1;
        const int safeH = (surfaceHeight > 0) ? surfaceHeight : 1;

        if (!detail::isViewportInsideSurface(viewport, safeW, safeH))
        {
            char msg[192];
            std::snprintf(
                msg,
                sizeof(msg),
                "render: viewport (%d,%d,%d,%d) outside surface (%d,%d), skipping",
                viewport.x,
                viewport.y,
                viewport.width,
                viewport.height,
                safeW,
                safeH);
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                msg);
            return;
        }

        if (safeW != m_lastWidth || safeH != m_lastHeight)
        {
            m_lastWidth = safeW;
            m_lastHeight = safeH;

            m_geometryPass->setOutputSize(m_resources->textures2D, safeW, safeH);
            rewireTargets();
        }

        m_renderer.setFrameData(frame);
        m_renderer.setViewport(viewport);
        m_renderer.render();
    }

    void ForwardRenderPath::rewireTargets()
    {
        if (!m_geometryPass || !m_resources)
        {
            internal::runtime::logError(
                "ForwardRenderPath",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "rewireTargets skipped: geometry/resources not ready");
            return;
        }

        const Texture2DHandle color = m_geometryPass->colorOutput();
        const Texture2DHandle depth = m_geometryPass->depthOutput();

        if (m_skyboxPass)
        {
            m_skyboxPass->setTargetTextures(color, depth);
        }

        if (m_environmentPass)
        {
            m_environmentPass->setTargetTextures(color, depth);
        }

        if (m_strokePass)
        {
            m_strokePass->setTargetTextures(color, depth);
        }

        if (m_transparentPass)
        {
            // WboitPass and TransparentPass have different wiring APIs
            bool wiredTransparent = false;
            if (auto* wboit = dynamic_cast<WboitPass*>(m_transparentPass))
            {
                wboit->setTargetColor(color);
                wboit->setGeometryDepth(depth);
                wboit->setOutputSize(m_resources->textures2D, m_lastWidth, m_lastHeight);
                wiredTransparent = true;
            }
            else if (auto* transp = dynamic_cast<TransparentPass*>(m_transparentPass))
            {
                transp->setTargetTextures(color, depth);
                wiredTransparent = true;
            }

            if (!wiredTransparent)
            {
                char msg[192];
                std::snprintf(
                    msg,
                    sizeof(msg),
                    "transparent pass '%s' has no known auto-wiring path",
                    m_transparentPass->name().c_str());
                internal::runtime::logError(
                    "ForwardRenderPath",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
            }
        }

        for (RenderPass* overlay : m_overlayPasses)
        {
            if (!overlay)
            {
                continue;
            }

            bool wiredOverlay = false;
            if (auto* grid = dynamic_cast<GridPass*>(overlay))
            {
                grid->setTargetTextures(color, depth);
                wiredOverlay = true;
            }
            else if (auto* axes = dynamic_cast<AxesPass*>(overlay))
            {
                axes->setTargetTextures(color, depth);
                wiredOverlay = true;
            }
            else if (auto* imagePlane = dynamic_cast<ImagePlanePass*>(overlay))
            {
                imagePlane->setTargetTextures(color, depth);
                wiredOverlay = true;
            }
            else if (auto* text = dynamic_cast<TextPass*>(overlay))
            {
                text->setTargetTextures(color, depth);
                wiredOverlay = true;
            }
            else if (auto* poly2d = dynamic_cast<Polygon2DPass*>(overlay))
            {
                poly2d->setTargetTextures(color, depth);
                wiredOverlay = true;
            }
            if (!wiredOverlay)
            {
                char msg[192];
                std::snprintf(
                    msg, sizeof(msg), "overlay pass '%s' has no known auto-wiring path", overlay->name().c_str());
                internal::runtime::logError(
                    "ForwardRenderPath",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
            }
        }

        if (m_presentPass)
        {
            if (m_outlinePass)
            {
                m_outlinePass->setInput(color, depth, m_geometryPass->outputFramebuffer());
                m_outlinePass->setOutputSize(m_resources->textures2D, m_lastWidth, m_lastHeight);
                m_presentPass->setInput(m_outlinePass->colorOutput());
            }
            else
            {
                m_presentPass->setInput(color);
            }
        }
    }
} // namespace nfx::graphics::gl
