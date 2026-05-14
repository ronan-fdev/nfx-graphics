#pragma once

/**
 * \file ForwardRenderPath.h
 * \brief Declares ForwardRenderPath: a forward rendering pipeline with a fluent configuration API.
 */

#include "nfx/graphics/gl/pipeline/frame/FrameData.h"
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
#include "nfx/graphics/gl/pipeline/passes/RenderPass.h"
#include "nfx/graphics/gl/pipeline/passes/SkyboxPass.h"
#include "nfx/graphics/gl/pipeline/passes/SpotShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/TextPass.h"
#include "nfx/graphics/gl/pipeline/passes/TransparentPass.h"
#include "nfx/graphics/gl/pipeline/passes/WboitPass.h"
#include "nfx/graphics/gl/pipeline/queue/RenderCommand.h"
#include "nfx/graphics/gl/resources/TextureCubeCache.h"
#include "Renderer.h"
#include "ViewportRect.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <type_traits>

namespace nfx::graphics::gl
{
    /**
     * \brief Carries the color and depth texture handles that connect render passes.
     *
     * Wire downstream overlay or post-process passes to the geometry output via
     * ForwardRenderPath::geoOutput().
     */
    struct PassTargetBundle
    {
        Texture2DHandle color; ///< Color output handle
        Texture2DHandle depth; ///< Depth output handle
    };

    /**
     * \brief Assembles and drives the standard forward rendering pass sequence.
     *
     * Standard pass order (only GeometryPass and PresentPass are mandatory):
     * \code
     *   [Shadow passes] -> GeometryPass -> [SkyboxPass | EnvironmentPass]
     *       -> [WboitPass | TransparentPass] -> [Overlay passes: GridPass, AxesPass, custom...]
     *       -> [PostProcessPass] -> PresentPass
     * \endcode
     *
     * All optional stages are added via the typed configuration API before initialize().
     * The path wires color/depth targets automatically between passes.
     *
     * Usage:
     * \code
     *   ForwardRenderPath path;
     *
     *   path.addShadowPass<DirectionalShadowPass>("Sun")
     *       ->setResolution(tex2dCache, 2048, 2048);
     *
     *   path.setSkybox(cubemapCache, skyboxHandle);
     *   path.enableTransparency<WboitPass>();
     *
     *   path.addOverlay<GridPass>("Grid")
     *       ->setGridSize(1.0f);
     *
     *   path.initialize(resources);
     *
     *   // per frame:
     *   path.geometryPass().submit(cmd);
     *   path.render(frame, width, height);
     * \endcode
     */
    class ForwardRenderPath final
    {
    public:
        ForwardRenderPath() = default;

        ForwardRenderPath(const ForwardRenderPath&) = delete;
        ForwardRenderPath& operator=(const ForwardRenderPath&) = delete;
        ForwardRenderPath(ForwardRenderPath&&) = delete;
        ForwardRenderPath& operator=(ForwardRenderPath&&) = delete;

        /**
         * \brief Sets the background clear color for GeometryPass.
         * \param r Red channel.
         * \param g Green channel.
         * \param b Blue channel.
         * \param a Alpha channel.
         */
        void setClearColor(float r, float g, float b, float a = 1.0f) noexcept;

        /**
         * \brief Adds a shadow pass of the given type and returns a non-owning pointer for further configuration.
         *
         * Shadow passes are executed first, before GeometryPass.
         * Multiple shadow passes of different types may be added.
         *
         * \tparam TShadow Concrete shadow pass type (DirectionalShadowPass, PointShadowPass, SpotShadowPass).
         * \param name Human-readable pass name.
         * \return Non-owning pointer to the created pass, or nullptr when the name is invalid.
         */
        template <typename TShadow>
        TShadow* addShadowPass(std::string name)
        {
            static_assert(std::is_base_of_v<RenderPass, TShadow>, "TShadow must inherit RenderPass");
            if (isReservedName(name) || m_renderer.pass(name) != nullptr)
            {
                std::fprintf(
                    stderr, "[ForwardRenderPath] addShadowPass: duplicate or reserved pass name '%s'\n", name.c_str());
                assert(false && "ForwardRenderPath::addShadowPass: duplicate or reserved pass name");

                return nullptr;
            }

            return m_renderer.createPass<TShadow>(std::move(name));
        }

        /**
         * \brief Enables a SkyboxPass drawing the given cubemap as background.
         *
         * Mutually exclusive with enableEnvironment(). SkyboxPass takes priority when both are set.
         * \param cache   Cube texture cache owning the cubemap.
         * \param cubemap Cubemap texture handle.
         */
        void setSkybox(TextureCubeCache& cache, TextureCubeHandle cubemap) noexcept;

        /**
         * \brief Enables an EnvironmentPass compositing the cubemap from FrameData::envMap.
         *
         * Mutually exclusive with setSkybox(). Ignored when setSkybox() has also been called.
         * \param intensity Multiplicative intensity applied to sampled environment color.
         */
        void enableEnvironment(float intensity = 1.0f) noexcept;

        /**
         * \brief Enables a transparent pass of the given type.
         *
         * \tparam TTransparent Concrete transparent pass type (WboitPass or TransparentPass).
         */
        template <typename TTransparent>
        void enableTransparency()
        {
            static_assert(std::is_base_of_v<RenderPass, TTransparent>, "TTransparent must inherit RenderPass");
            m_wantsTransparentPass = true;
            m_transparentPassFactory = [this]() -> RenderPass* {
                return m_renderer.createPass<TTransparent>("Transparent");
            };
        }

        /**
         * \brief Adds an overlay pass (GridPass, AxesPass, custom...) and returns a non-owning pointer.
         *
         * Overlay passes are executed after transparent passes.
         * They are automatically wired to the GeometryPass color/depth output.
         *
         * \tparam TOverlay Concrete overlay pass type.
         * \param name Human-readable pass name. Must be unique across all registered passes.
         * \return Non-owning pointer to the created pass, or nullptr when the name is invalid.
         */
        template <typename TOverlay>
        TOverlay* addOverlay(std::string name)
        {
            static_assert(std::is_base_of_v<RenderPass, TOverlay>, "TOverlay must inherit RenderPass");
            if (isReservedName(name) || m_renderer.pass(name) != nullptr)
            {
                std::fprintf(
                    stderr, "[ForwardRenderPath] addOverlay: duplicate or reserved pass name '%s'\n", name.c_str());
                assert(false && "ForwardRenderPath::addOverlay: duplicate or reserved pass name");

                return nullptr;
            }

            TOverlay* ptr = m_renderer.createPass<TOverlay>(std::move(name));
            m_overlayPasses.push_back(ptr);

            return ptr;
        }

        /**
         * \brief Enables selection-outline compositing via OutlinePass.
         *
         * Must be called before initialize().
         * \param color Outline RGB color in [0..1].
         * \param thickness Outline thickness in texel units.
         */
        void enableOutline(const float (&color)[3], float thickness = 1.0f) noexcept;

        /**
         * \brief Sets the PresentPass exposure.
         * \param exposure Exposure multiplier applied during presentation.
         */
        void setExposure(float exposure) noexcept { m_exposure = exposure; }

        /**
         * \brief Enables or disables filmic tonemapping in PresentPass.
         * \param enabled When true, tonemapping is enabled during presentation.
         */
        void setTonemapEnabled(bool enabled) noexcept { m_tonemapEnabled = enabled; }

        /**
         * \brief Enables or disables gamma correction in PresentPass.
         * \param enabled When true, gamma correction is enabled during presentation.
         */
        void setGammaEnabled(bool enabled) noexcept { m_gammaEnabled = enabled; }

        /**
         * \brief Creates all mandatory passes and initializes the renderer.
         *
         * Must be called once after all configuration and before the first render().
         * \param resources Non-owning cache bundle used to resolve handles.
         */
        void initialize(RenderResources& resources);

        /**
         * \brief Returns the opaque geometry pass for command submission.
         *
         * Always valid after initialize().
         * \return Reference to the GeometryPass owned by this render path.
         */
        [[nodiscard]] GeometryPass& geometryPass() noexcept
        {
            assert(m_geometryPass);
            return *m_geometryPass;
        }

        /**
         * \brief Returns the transparent pass, or nullptr if not enabled.
         * \return Non-owning pointer to the transparent pass, or nullptr when disabled.
         */
        [[nodiscard]] RenderPass* transparentPass() noexcept { return m_transparentPass; }

        /**
         * \brief Returns the outline pass, or nullptr if outline is disabled.
         * \return Non-owning pointer to OutlinePass when enabled, nullptr otherwise.
         */
        [[nodiscard]] OutlinePass* outlinePass() noexcept { return m_outlinePass; }

        /**
         * \brief Returns a typed pointer to a named pass, or nullptr when not found.
         * \param name Pass name to search.
         * \return Non-owning typed pointer to the pass, or nullptr when not found.
         */
        template <typename TPass>
        [[nodiscard]] TPass* get(std::string_view name) noexcept
        {
            return dynamic_cast<TPass*>(m_renderer.pass(name));
        }

        /**
         * \brief Returns the GeometryPass color and depth output handles.
         *
         * Useful for wiring custom passes added after initialize().
         * Valid only after the first render() call.
         * \return Geometry output color/depth handle bundle.
         */
        [[nodiscard]] PassTargetBundle geoOutput() const noexcept;

        /**
         * \brief Executes all passes for one frame and handles viewport resize.
         *
         * \param frame  Frame-scoped camera, light, and environment data.
         * \param width  Viewport width in pixels.
         * \param height Viewport height in pixels.
         */
        void render(const FrameData& frame, int width, int height);

        /**
         * \brief Executes all passes for one frame using an explicit surface extent and active viewport rectangle.
         *
         * \param frame Frame-scoped camera, light, and environment data.
         * \param surfaceWidth Render-surface width in pixels used for target allocation.
         * \param surfaceHeight Render-surface height in pixels used for target allocation.
         * \param viewport Active viewport rectangle in pixel coordinates.
         */
        void render(const FrameData& frame, int surfaceWidth, int surfaceHeight, const ViewportRect& viewport);

        /**
         * \brief Returns the underlying renderer for advanced use.
         * \return Reference to the underlying Renderer.
         */
        [[nodiscard]] Renderer& renderer() noexcept { return m_renderer; }

        /**
         * \brief Returns frame stats from the most recent render() call.
         */
        [[nodiscard]] const Renderer::FrameStats& frameStats() const noexcept { return m_renderer.frameStats(); }

        /**
         * \brief Returns cumulative backend renderer stats.
         */
        [[nodiscard]] const Renderer::RendererStats& stats() const noexcept { return m_renderer.stats(); }

    private:
        // clang-format off
        static constexpr std::string_view kReservedNames[] = {
            "Geometry",
            "Skybox",
            "Environment",
            "Transparent",
            "Outline",
            "Present"
         };
        // clang-format on

        static bool isReservedName(std::string_view name) noexcept
        {
            for (const auto& r : kReservedNames)
            {
                if (r == name)
                {
                    return true;
                }
            }
            return false;
        }

        void rewireTargets();

        Renderer m_renderer;
        RenderResources* m_resources = nullptr;

        // Mandatory passes
        GeometryPass* m_geometryPass = nullptr;
        PresentPass* m_presentPass = nullptr;

        // Optional passes
        SkyboxPass* m_skyboxPass = nullptr;
        EnvironmentPass* m_environmentPass = nullptr;
        RenderPass* m_transparentPass = nullptr;
        OutlinePass* m_outlinePass = nullptr;
        std::vector<RenderPass*> m_overlayPasses;

        // Pre-initialize configuration
        float m_clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

        TextureCubeCache* m_skyboxCache = nullptr;
        TextureCubeHandle m_skyboxHandle;

        float m_envIntensity = 1.0f;
        bool m_hasSkybox = false;
        bool m_hasEnvPass = false;

        bool m_wantsTransparentPass = false;
        std::function<RenderPass*()> m_transparentPassFactory;

        bool m_wantsOutlinePass = false;
        float m_outlineColor[3] = { 1.0f, 0.9f, 0.1f };
        float m_outlineThickness = 1.0f;

        float m_exposure = 1.0f;
        bool m_tonemapEnabled = true;
        bool m_gammaEnabled = true;

        int m_lastWidth = 0;
        int m_lastHeight = 0;
        bool m_initialized = false;
    };
} // namespace nfx::graphics::gl
