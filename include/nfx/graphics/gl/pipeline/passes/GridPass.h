#pragma once

/**
 * \file GridPass.h
 * \brief Declares the overlay render pass drawing an infinite ground grid.
 */

#include "RenderPass.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Overlay render pass drawing an anti-aliased ground grid into a target framebuffer.
     */
    class GridPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures that receive the grid overlay.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Optional target depth texture, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Sets the logical grid cell size.
         * \param size Grid cell size in world units.
         */
        void setGridSize(float size) { m_params.gridSize = size; }

        /**
         * \brief Sets the distance at which the grid fades out.
         * \param dist Fade distance in world units.
         */
        void setFadeDistance(float dist) { m_params.fadeDistance = dist; }

        /**
         * \brief Sets the grid line color.
         * \param color RGB color array.
         */
        void setColor(const float (&color)[3])
        {
            m_params.color[0] = color[0];
            m_params.color[1] = color[1];
            m_params.color[2] = color[2];
        }

    private:
        explicit GridPass(std::string name = "GridPass")
            : RenderPass{ std::move(name) }
        {
            setRasterRegionState({ ViewportPolicy::InheritView, {}, ScissorPolicy::Disabled, {} });
        }

        virtual bool initialize() override;

        virtual void begin() override;
        virtual void execute(RenderResources&) override;
        virtual void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;
        ShaderProgram m_gridShader;
        VertexArray m_vao;

        struct Params
        {
            float gridSize = 1.0f;
            float fadeDistance = 100.0f;
            float color[3] = { 0.5f, 0.5f, 0.5f };
        } m_params;
    };
} // namespace nfx::graphics::gl
