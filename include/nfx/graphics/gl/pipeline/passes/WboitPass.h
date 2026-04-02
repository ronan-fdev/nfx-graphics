#pragma once

/**
 * \file WboitPass.h
 * \brief Declares the weighted blended order-independent transparency render pass.
 */

#include "nfx/graphics/gl/pipeline/queue/RenderCommand.h"
#include "RenderPass.h"

#include <cassert>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Weighted blended order-independent transparency render pass.
     *
     * Renders transparent geometry without sorting, reducing intersection artefacts inherent to
     * back-to-front sorted transparency.
     */
    class WboitPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Submits one transparent draw command to the WBOIT accumulation pass.
         * \param cmd Draw command to enqueue.
         */
        void submit(RenderCommand cmd)
        {
            if (cmd.instanceCount < 1)
            {
                assert(cmd.instanceCount >= 1 && "WboitPass::submit: instanceCount must be >= 1");
                cmd.instanceCount = 1;
            }
            if (cmd.sortKey == 0)
            {
                cmd.sortKey = cmd.material.id;
            }
            m_commands.push_back(cmd);
        }

        /**
         * \brief Sets the target color texture used for the final composite.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         */
        void setTargetColor(Texture2DHandle color) noexcept { m_targetColor = color; }

        /**
         * \brief Sets the geometry depth texture used during WBOIT accumulation.
         * \param depth Depth texture from the opaque pass.
         */
        void setGeometryDepth(Texture2DHandle depth) noexcept;

        /**
         * \brief Allocates or resizes the internal accumulation and reveal textures.
         * \param texCache Texture cache receiving the internal textures.
         * \param width Output width in pixels.
         * \param height Output height in pixels.
         *
         * Must be called once and again on resize.
         */
        void setOutputSize(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Returns whether no transparent commands are queued.
         */
        [[nodiscard]] bool empty() const noexcept { return m_commands.empty(); }

        /**
         * \brief Returns the number of queued transparent commands.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_commands.size(); }

    private:
        explicit WboitPass(std::string name = "WboitPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

        // Reallocates the internal accumulation and reveal targets
        void reallocate();

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        bool m_targetBound = false;
        Texture2DHandle m_geomDepthHandle;

        // Internal MRT FBO: attachment 0 = accum, attachment 1 = reveal
        Framebuffer m_accumFbo;
        Texture2DHandle m_accumHandle;
        Texture2DHandle m_revealHandle;

        // Composite fullscreen
        ShaderProgram m_accumShader;
        ShaderProgram m_compositeShader;
        VertexArray m_dummyVAO;

        Texture2DCache* m_texCache = nullptr;
        int m_width = 0;
        int m_height = 0;

        std::vector<RenderCommand> m_commands;
    };
} // namespace nfx::graphics::gl
