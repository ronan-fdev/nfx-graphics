#pragma once

/**
 * \file TransparentPass.h
 * \brief Declares the transparent render pass performing back-to-front sorted alpha blending.
 */

#include "nfx/graphics/gl/pipeline/queue/RenderCommand.h"
#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "RenderPass.h"

#include <cstdint>
#include <string>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Transparent geometry render pass.
     *
     * Sorts submitted RenderCommand values back-to-front relative to the camera position,
     * then draws them with depth writes disabled so transparent surfaces blend correctly.
     *
     * State precedence:
     * - This pass enforces transparent policy during execution (blending enabled, depth writes disabled,
     *   culling configured for the two-pass front/back sequence).
     * - Material state may still configure shader/textures/uniforms, but pass-level transparency policy wins
     *   for blend/depth-write/culling behavior.
     */
    class TransparentPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Per-frame execution counters produced by TransparentPass::execute().
         */
        struct ExecutionStats
        {
            std::uint32_t commandsSubmitted = 0; ///< Number of queued transparent commands
            std::uint32_t commandsDrawn = 0;     ///< Number of transparent draw calls effectively executed
            std::uint32_t commandsInvalid = 0;   ///< Number of commands rejected due to invalid mesh/material/shader
            std::uint32_t shaderBinds = 0;       ///< Number of shader/material bind changes applied
            std::uint32_t vaoBinds = 0;          ///< Number of mesh VAO binds applied
            std::uint32_t vboBinds = 0;          ///< Number of vertex-buffer binding changes applied
            std::uint32_t textureBinds = 0;      ///< Number of texture bind calls applied
            std::uint32_t fboBinds = 0;          ///< Number of framebuffer bind calls applied
            std::uint32_t instancedDraws = 0;    ///< Number of draw calls using instanceCount > 1
        };

        /**
         * \brief Submits one transparent draw command.
         * \param cmd Draw command to enqueue.
         */
        void submit(RenderCommand cmd) { m_queue.submit(cmd); }

        /**
         * \brief Removes all queued transparent commands.
         */
        void clearQueue() { m_queue.clear(); }

        /**
         * \brief Sets the world-space camera position used for sorting.
         * \param pos Camera world position.
         */
        void setCameraPosition(const float (&pos)[3])
        {
            m_cameraPos[0] = pos[0];
            m_cameraPos[1] = pos[1];
            m_cameraPos[2] = pos[2];
        }

        /**
         * \brief Sets the target textures receiving the transparent composite.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Optional target depth texture, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Returns whether no transparent commands are queued.
         */
        [[nodiscard]] bool empty() const noexcept { return m_queue.empty(); }

        /**
         * \brief Returns the number of queued transparent commands.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_queue.size(); }

        /**
         * \brief Returns execution counters from the most recent execute() call.
         */
        [[nodiscard]] const ExecutionStats& executionStats() const noexcept { return m_executionStats; }

        /**
         * \brief Returns the target framebuffer receiving this pass output.
         */
        [[nodiscard]] virtual const Framebuffer* outputFramebuffer() const noexcept override
        {
            return m_targetColor.isValid() ? &m_targetFbo : nullptr;
        }

    private:
        explicit TransparentPass(std::string name = "TransparentPass")
            : RenderPass{ std::move(name) }
        {}

        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;
        RenderQueue m_queue;
        float m_cameraPos[3] = { 0.f, 0.f, 0.f };
        ExecutionStats m_executionStats;
    };
} // namespace nfx::graphics::gl
