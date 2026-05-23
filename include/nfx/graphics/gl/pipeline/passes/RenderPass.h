#pragma once

/**
 * \file RenderPass.h
 * \brief Declares the abstract base class implemented by all rendering passes.
 */

#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/pipeline/frame/RenderResources.h"
#include "nfx/graphics/gl/pipeline/raster/RasterRegion.h"
#include "nfx/graphics/gl/resources/Handle.h"

#include <cstdint>
#include <string>

namespace nfx::graphics::gl
{
    struct FrameData;
    struct ViewportRect;

    struct PassRuntimeStats
    {
        std::uint32_t drawCalls = 0;
        std::uint32_t shaderBinds = 0;
        std::uint32_t vaoBinds = 0;
        std::uint32_t vboBinds = 0;
        std::uint32_t fboBinds = 0;
        std::uint32_t textureBinds = 0;
    };

    /**
     * \brief Abstract base class representing one stage of the renderer pipeline.
     */
    class RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Releases the render pass instance.
         */
        virtual ~RenderPass() = default;

        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(const RenderPass&) = delete;
        RenderPass(RenderPass&&) = delete;
        RenderPass& operator=(RenderPass&&) = delete;

        /**
         * \brief Returns the color texture output produced by the pass, when applicable.
         */
        [[nodiscard]] virtual Texture2DHandle colorOutput() const noexcept { return {}; }

        /**
         * \brief Returns the depth texture output produced by the pass, when applicable.
         */
        [[nodiscard]] virtual Texture2DHandle depthOutput() const noexcept { return {}; }

        /**
         * \brief Returns the output framebuffer used by the pass, when applicable.
         */
        [[nodiscard]] virtual const Framebuffer* outputFramebuffer() const noexcept { return nullptr; }

        /**
         * \brief Returns the output width in pixels, when applicable.
         */
        [[nodiscard]] virtual int outputWidth() const noexcept { return 0; }

        /**
         * \brief Returns the output height in pixels, when applicable.
         */
        [[nodiscard]] virtual int outputHeight() const noexcept { return 0; }

        /**
         * \brief Returns the human-readable pass name.
         */
        [[nodiscard]] const std::string& name() const noexcept { return m_name; }

        /**
         * \brief Returns whether the pass is enabled.
         */
        [[nodiscard]] bool isEnabled() const noexcept { return m_enabled; }

        /**
         * \brief Enables or disables execution of the pass.
         * \param enabled New enabled state.
         */
        void setEnabled(bool enabled) noexcept { m_enabled = enabled; }

        /**
         * \brief Returns generic runtime counters from the most recent pass execution.
         */
        [[nodiscard]] const PassRuntimeStats& runtimeStats() const noexcept { return m_runtimeStats; }

        /**
         * \brief Optional auto-wiring hook used by ForwardRenderPath.
         *
         * Passes may override this to consume the geometry color/depth outputs
         * without requiring hardcoded type checks in ForwardRenderPath.
         *
         * \param color Geometry color output handle.
         * \param depth Geometry depth output handle.
         * \return True when the pass consumed the targets, false otherwise.
         */
        [[nodiscard]] virtual bool setAutoWiredTargets(Texture2DHandle color, Texture2DHandle depth)
        {
            (void)color;
            (void)depth;
            return false;
        }

    protected:
        /**
         * \brief Creates a render pass with a fixed display name.
         * \param name Human-readable pass name.
         */
        explicit RenderPass(std::string name)
            : m_name{ std::move(name) }
        {}

        /**
         * \brief Performs one-time initialization of GPU resources used by the pass.
         * \return False when initialization failed, true otherwise.
         */
        virtual bool initialize() { return true; }

        /**
         * \brief Begins the pass and prepares its render targets or state.
         */
        virtual void begin() = 0;

        /**
         * \brief Executes the main rendering work of the pass.
         * \param resources Cache bundle used to resolve mesh, material, shader and texture handles.
         */
        virtual void execute(RenderResources&) = 0;

        /**
         * \brief Ends the pass and restores any state it owns.
         */
        virtual void end() = 0;

        /**
         * \brief Returns the frame data currently bound to the pass, when available.
         */
        [[nodiscard]] const FrameData* currentFrameData() const noexcept { return m_frameData; }

        /**
         * \brief Returns the active viewport override currently bound to the pass, when available.
         */
        [[nodiscard]] const ViewportRect* currentViewport() const noexcept { return m_viewport; }

        /**
         * \brief Returns the logical raster-region policy owned by the pass.
         */
        [[nodiscard]] const RasterRegionState& rasterRegionState() const noexcept { return m_rasterRegionState; }

        /**
         * \brief Sets the logical raster-region policy owned by the pass.
         */
        void setRasterRegionState(const RasterRegionState& state) noexcept { m_rasterRegionState = state; }

        void resetRuntimeStats() noexcept { m_runtimeStats = {}; }

        PassRuntimeStats m_runtimeStats;

    private:
        std::string m_name;
        bool m_enabled = true;
        bool m_initialized = false;
        const FrameData* m_frameData = nullptr;
        const ViewportRect* m_viewport = nullptr;
        RasterRegionState m_rasterRegionState;
    };
} // namespace nfx::graphics::gl
