#include "nfx/graphics/gl/pipeline/ForwardRenderPath.h"
#include "detail/ViewportValidation.h"

#include <cstdio>

namespace nfx::graphics::gl
{
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
            std::fprintf(stderr, "[ForwardRenderPath] setSkybox: cannot change after initialize()\n");
            assert(false && "ForwardRenderPath::setSkybox: called after initialize");
            return;
        }
        if (m_hasEnvPass)
        {
            std::fprintf(stderr, "[ForwardRenderPath] setSkybox() overrides enableEnvironment()\n");
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
            std::fprintf(stderr, "[ForwardRenderPath] enableEnvironment: cannot change after initialize()\n");
            assert(false && "ForwardRenderPath::enableEnvironment: called after initialize");
            return;
        }
        if (m_hasSkybox)
        {
            std::fprintf(stderr, "[ForwardRenderPath] enableEnvironment() ignored: setSkybox() already set\n");
            return;
        }
        m_envIntensity = intensity;
        m_hasEnvPass = true;
    }

    void ForwardRenderPath::enableOutline(const float (&color)[3], float thickness) noexcept
    {
        if (m_initialized)
        {
            std::fprintf(stderr, "[ForwardRenderPath] enableOutline: cannot change after initialize()\n");
            assert(false && "ForwardRenderPath::enableOutline: called after initialize");
            return;
        }

        m_wantsOutlinePass = true;
        m_outlineColor[0] = color[0];
        m_outlineColor[1] = color[1];
        m_outlineColor[2] = color[2];
        m_outlineThickness = thickness;
    }

    void ForwardRenderPath::initialize(RenderResources& resources)
    {
        if (m_initialized)
        {
            std::fprintf(stderr, "[ForwardRenderPath] initialize() called more than once\n");
            assert(false && "ForwardRenderPath::initialize called more than once");
            return;
        }

        m_resources = &resources;

        if (m_hasSkybox && (!m_skyboxCache || !m_skyboxHandle.isValid()))
        {
            std::fprintf(stderr, "[ForwardRenderPath] invalid skybox configuration before initialize()\n");
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
            std::fprintf(stderr, "[ForwardRenderPath] render() called before successful initialize()\n");
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

        m_renderer.setFrameData(frame);
        m_renderer.resetViewport();
        m_renderer.render();
    }

    void ForwardRenderPath::render(
        const FrameData& frame, int surfaceWidth, int surfaceHeight, const ViewportRect& viewport)
    {
        if (!m_initialized || !m_resources || !m_geometryPass)
        {
            std::fprintf(stderr, "[ForwardRenderPath] render() called before successful initialize()\n");
            assert(false && "ForwardRenderPath::render called before initialize");
            return;
        }

        const int safeW = (surfaceWidth > 0) ? surfaceWidth : 1;
        const int safeH = (surfaceHeight > 0) ? surfaceHeight : 1;

        if (!detail::isViewportInsideSurface(viewport, safeW, safeH))
        {
            std::fprintf(
                stderr,
                "[ForwardRenderPath] render: viewport (%d,%d,%d,%d) outside surface (%d,%d), skipping\n",
                viewport.x,
                viewport.y,
                viewport.width,
                viewport.height,
                safeW,
                safeH);
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
            std::fprintf(stderr, "[ForwardRenderPath] rewireTargets skipped: geometry/resources not ready\n");
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
                std::fprintf(
                    stderr,
                    "[ForwardRenderPath] transparent pass '%s' has no known auto-wiring path\n",
                    m_transparentPass->name().c_str());
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

            if (!wiredOverlay)
            {
                std::fprintf(
                    stderr,
                    "[ForwardRenderPath] overlay pass '%s' has no known auto-wiring path\n",
                    overlay->name().c_str());
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
