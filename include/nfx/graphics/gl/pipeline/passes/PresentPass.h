#pragma once

/**
 * \file PresentPass.h
 * \brief Declares a fixed fullscreen present pass (tonemap + gamma) to the current framebuffer.
 */

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "RenderPass.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Fullscreen present pass rendering one input color texture to the active framebuffer.
     *
     * This pass is intended as the final stage of the pipeline and applies optional
     * exposure tonemapping and gamma correction.
     */
    class PresentPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the input color texture produced by an upstream pass.
         * \param colorHandle Upstream color texture handle.
         */
        void setInput(Texture2DHandle colorHandle) noexcept { m_inputHandle = colorHandle; }

        /**
         * \brief Sets the exposure used by tonemapping.
         * \param exposure Positive exposure multiplier.
         */
        void setExposure(float exposure) noexcept { m_exposure = exposure; }

        /**
         * \brief Sets the gamma exponent used for gamma correction.
         * \param gamma Positive gamma exponent (typically 2.2).
         */
        void setGamma(float gamma) noexcept { m_gamma = gamma; }

        /**
         * \brief Enables or disables filmic tonemapping.
         */
        void setTonemapEnabled(bool enabled) noexcept { m_tonemapEnabled = enabled; }

        /**
         * \brief Enables or disables gamma correction.
         */
        void setGammaEnabled(bool enabled) noexcept { m_gammaEnabled = enabled; }

    private:
        explicit PresentPass(std::string name = "PresentPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        Texture2DHandle m_inputHandle;
        ShaderProgram m_shader;
        VertexArray m_dummyVAO;

        float m_exposure = 1.0f;
        float m_gamma = 2.2f;
        bool m_tonemapEnabled = true;
        bool m_gammaEnabled = true;
    };
} // namespace nfx::graphics::gl
