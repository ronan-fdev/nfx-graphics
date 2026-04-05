#pragma once

/**
 * \file GeometryPass.h
 * \brief Declares GeometryPass, the default opaque geometry rendering pass.
 */

#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/resources/Handle.h"
#include "RenderPass.h"

#include <cstdint>
#include <string>

namespace nfx::graphics::gl
{
    class Material;

    /**
     * \brief Renders opaque geometry commands into an owned color+depth framebuffer.
     *
     * Owns its output textures and framebuffer. Use setOutputSize() once to allocate
     * GPU resources, then wire outputs to downstream passes via colorOutput() / depthOutput().
     */
    class GeometryPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Per-frame culling counters produced by GeometryPass::execute().
         */
        struct CullingStats
        {
            std::uint32_t commandsTested = 0; ///< Number of commands tested against frustum bounds
            std::uint32_t commandsCulled = 0; ///< Number of commands rejected by frustum culling
            std::uint32_t commandsDrawn = 0;  ///< Number of commands effectively drawn
        };

        /**
         * \brief Submits one draw command to the pass queue.
         * \param cmd Draw command to enqueue for the next execute().
         */
        void submit(RenderCommand cmd) { m_queue.submit(cmd); }

        /**
         * \brief Removes all queued commands. Call once per frame before submitting new commands.
         */
        void clearQueue() { m_queue.clear(); }

        /**
         * \brief Allocates or resizes the pass output textures and framebuffer.
         *
         * Must be called at least once before the first render().
         * Safe to call again on window resize - invalidates current handles and reallocates.
         * \param texCache Texture cache receiving the color and depth textures.
         * \param width Output width in pixels.
         * \param height Output height in pixels.
         */
        void setOutputSize(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Sets the pass-level fixed-function render state applied before drawing.
         * \param state Render state to apply at pass begin.
         */
        void setRenderState(const RenderState& state) noexcept { m_state = state; }

        /**
         * \brief Sets the command ordering policy.
         * \param order Ordering policy applied during execute().
         */
        void setOrder(RenderQueue::Order order) noexcept { m_order = order; }

        /**
         * \brief Sets the patch vertex count used when drawing in RenderMode::Patches.
         * \param n Patch vertex count. Clamped to [1, Context::maxPatchVertices()] at draw time.
         */
        void setPatchVertices(int n) noexcept { m_patchVertices = n; }

        /**
         * \brief Configures color buffer clearing.
         * \param clear Whether to clear the color buffer at pass begin.
         * \param r Red component of the clear color.
         * \param g Green component.
         * \param b Blue component.
         * \param a Alpha component.
         */
        void setClearColor(bool clear, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
        {
            m_clearColor.clear = clear;
            m_clearColor.value[0] = r;
            m_clearColor.value[1] = g;
            m_clearColor.value[2] = b;
            m_clearColor.value[3] = a;
        }

        /**
         * \brief Configures depth buffer clearing.
         * \param clear Whether to clear the depth buffer at pass begin.
         * \param depth Depth clear value. Defaults to 1.0.
         */
        void setClearDepth(bool clear, float depth = 1.0f)
        {
            m_clearDepth.clear = clear;
            m_clearDepth.value = depth;
        }

        /**
         * \brief Sets an optional fallback material used when a command's material handle cannot be resolved.
         * \param fallback Fallback material instance, or nullptr to skip the command on resolution failure.
         */
        void setFallbackMaterial(Material* fallback) noexcept { m_fallback = fallback; }

        /**
         * \brief Returns read-only access to the current command queue.
         */
        [[nodiscard]] virtual const RenderQueue& queue() const noexcept { return m_queue; }

        /**
         * \brief Returns the color texture handle, or invalid when not yet allocated.
         */
        [[nodiscard]] virtual Texture2DHandle colorOutput() const noexcept override { return m_colorHandle; }

        /**
         * \brief Returns the depth texture handle, or invalid when not yet allocated.
         */
        [[nodiscard]] virtual Texture2DHandle depthOutput() const noexcept override { return m_depthHandle; }

        /**
         * \brief Returns the owned framebuffer, or nullptr when not yet allocated.
         */
        [[nodiscard]] virtual const Framebuffer* outputFramebuffer() const noexcept override
        {
            return m_colorHandle.isValid() ? &m_framebuffer : nullptr;
        }

        /**
         * \brief Returns the output width in pixels.
         */
        [[nodiscard]] virtual int outputWidth() const noexcept override { return m_width; }

        /**
         * \brief Returns the output height in pixels.
         */
        [[nodiscard]] virtual int outputHeight() const noexcept override { return m_height; }

        /**
         * \brief Returns culling counters from the most recent execute() call.
         */
        [[nodiscard]] const CullingStats& cullingStats() const noexcept { return m_cullingStats; }

    private:
        explicit GeometryPass(std::string name = "GeometryPass")
            : RenderPass{ std::move(name) }
        {}

        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

        RenderQueue m_queue;
        RenderState m_state;
        Framebuffer m_framebuffer;
        Texture2DHandle m_colorHandle;
        Texture2DHandle m_depthHandle;
        Material* m_fallback = nullptr;
        RenderQueue::Order m_order = RenderQueue::Order::BySortKey;
        int m_patchVertices = 3;
        int m_width = 0;
        int m_height = 0;
        CullingStats m_cullingStats;

        struct ClearColor
        {
            bool clear = true;
            float value[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
        } m_clearColor;

        struct ClearDepth
        {
            bool clear = true;
            float value = 1.0f;
        } m_clearDepth;
    };
} // namespace nfx::graphics::gl
