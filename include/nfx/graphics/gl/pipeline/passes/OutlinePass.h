#pragma once

/**
 * \file OutlinePass.h
 * \brief Declares OutlinePass, a viewport-aware selection outline compositing pass.
 */

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/resources/Texture2DCache.h"
#include "RenderPass.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Produces a color output with outlines composited over a geometry color target.
     *
     * This pass renders selected geometry into an internal mask, extracts edges using a
     * Sobel-like filter, then composites the outline over a copy of the geometry color.
     */
    class OutlinePass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets geometry inputs consumed by the pass.
         * \param colorHandle Geometry color texture.
         * \param depthHandle Geometry depth texture.
         * \param geoFbo Geometry framebuffer (used for color/depth blits).
         */
        void setInput(Texture2DHandle colorHandle, Texture2DHandle depthHandle, const Framebuffer* geoFbo) noexcept;

        /**
         * \brief Allocates internal mask/composite targets.
         * \param texCache Texture cache used to allocate internal targets.
         * \param width Output width in pixels.
         * \param height Output height in pixels.
         */
        void setOutputSize(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Sets RGB outline color.
         * \param color Outline color as RGB values in [0..1].
         */
        void setOutlineColor(const float (&color)[3]) noexcept
        {
            m_outlineColor[0] = color[0];
            m_outlineColor[1] = color[1];
            m_outlineColor[2] = color[2];
        }

        /**
         * \brief Sets outline thickness in texel units.
         * \param thickness Outline thickness scale in texel units.
         */
        void setThickness(float thickness) noexcept { m_thickness = thickness; }

        /**
         * \brief Enqueues one selected draw command.
         * \param cmd Draw command to render into the outline mask.
         */
        void submit(RenderCommand cmd) { m_queue.submit(std::move(cmd)); }

        /**
         * \brief Clears selected draw commands.
         */
        void clearQueue() { m_queue.clear(); }

        /**
         * \brief Returns the composited output color texture handle.
         * \return Output color texture handle, or invalid handle when not allocated.
         */
        [[nodiscard]] Texture2DHandle colorOutput() const noexcept override { return m_outputHandle; }

        /**
         * \brief Returns the output framebuffer used by this pass.
         * \return Pointer to internal output framebuffer when allocated, otherwise nullptr.
         */
        [[nodiscard]] const Framebuffer* outputFramebuffer() const noexcept override
        {
            return m_outputHandle.isValid() ? &m_outputFbo : nullptr;
        }

        /**
         * \brief Returns output width in pixels.
         * \return Output width in pixels.
         */
        [[nodiscard]] int outputWidth() const noexcept override { return m_width; }

        /**
         * \brief Returns output height in pixels.
         * \return Output height in pixels.
         */
        [[nodiscard]] int outputHeight() const noexcept override { return m_height; }

    private:
        explicit OutlinePass(std::string name = "OutlinePass")
            : RenderPass{ std::move(name) }
        {}

        bool initialize() override;
        void begin() override;
        void execute(RenderResources& resources) override;
        void end() override;

        void reallocateTargets();
        void drawFullscreenTriangle();

        Texture2DHandle m_geoColorHandle;
        Texture2DHandle m_geoDepthHandle;
        const Framebuffer* m_geoFbo = nullptr;

        Texture2DHandle m_maskColorHandle;
        Texture2DHandle m_maskDepthHandle;
        Texture2DHandle m_outputHandle;

        Framebuffer m_maskFbo;
        Framebuffer m_outputFbo;

        ShaderProgram m_maskShader;
        ShaderProgram m_sobelShader;
        VertexArray m_dummyVAO;
        RenderQueue m_queue;

        Texture2DCache* m_texCache = nullptr;
        int m_width = 0;
        int m_height = 0;
        bool m_dirty = false;

        float m_outlineColor[3] = { 1.0f, 0.9f, 0.1f };
        float m_thickness = 1.0f;
    };
} // namespace nfx::graphics::gl
