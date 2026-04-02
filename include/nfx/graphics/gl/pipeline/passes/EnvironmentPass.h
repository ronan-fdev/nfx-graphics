#pragma once

/**
 * \file EnvironmentPass.h
 * \brief Declares the render pass compositing an environment cubemap into a target framebuffer.
 */

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "RenderPass.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Render pass drawing an environment cubemap as scene background contribution.
     *
     * The environment map texture/sampler are expected to be bound by Renderer frame scope
     * using FrameData (`envMap`, `envSampler`) on texture unit TextureBindings::EnvMap.
     */
    class EnvironmentPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures receiving the environment contribution.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Optional target depth texture, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Sets the environment contribution intensity.
         * \param intensity Multiplicative intensity applied to sampled cubemap color.
         */
        void setIntensity(float intensity) noexcept { m_intensity = intensity; }

    private:
        explicit EnvironmentPass(std::string name = "EnvironmentPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;
        float m_intensity = 1.0f;

        ShaderProgram m_shader;
        VertexArray m_vao;
    };
} // namespace nfx::graphics::gl
