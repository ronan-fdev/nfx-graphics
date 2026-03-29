#pragma once

/**
 * \file AxesPass.h
 * \brief Declares the overlay render pass drawing world-space XYZ axes.
 */

#include "RenderPass.h"

#include <string>
#include <utility>

namespace nfx::graphics::gl
{
    /**
     * \brief Overlay render pass drawing world-space axes into a target framebuffer.
     */
    class AxesPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures that receive the axes overlay.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Optional target depth texture, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Sets the rendered axis length.
         * \param length Axis length in world units.
         */
        void setAxisLength(float length)
        {
            m_params.axisLength = length;
            m_dirty = true;
        }

        /**
         * \brief Sets the fade distance used by the axes shader.
         * \param dist Fade distance in world units.
         */
        void setFadeDistance(float dist) { m_params.fadeDistance = dist; }

    private:
        explicit AxesPass(std::string name = "AxesPass")
            : RenderPass{ std::move(name) }
        {}

        void rebuildGeometry();

        virtual bool initialize() override;

        virtual void begin() override;
        virtual void execute(RenderResources&) override;
        virtual void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;
        ShaderProgram m_axesShader;
        VertexArray m_vao;
        Buffer m_vbo{ Buffer::Target::VertexAttributesArray };

        struct Params
        {
            float axisLength = 10000.0f;
            float fadeDistance = 100.0f;
        } m_params;

        bool m_dirty = true;
    };
} // namespace nfx::graphics::gl
