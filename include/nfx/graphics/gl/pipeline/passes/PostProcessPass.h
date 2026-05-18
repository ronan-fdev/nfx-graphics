#pragma once

/**
 * \file PostProcessPass.h
 * \brief Declares a generic fullscreen post-processing render pass driven by a user fragment shader.
 */

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "RenderPass.h"

#include <array>
#include <string>
#include <string_view>
#include <unordered_map>

namespace nfx::graphics::gl
{
    /**
     * \brief Generic fullscreen post-processing pass.
     *
     * The user provides only a GLSL fragment source. The built-in fullscreen
     * vertex shader is composed internally.
     *
     * Output mode:
     * - The pass always renders into an owned output texture/FBO.
     * - Call setOutputSize() before the first render and again on resize.
     *
     * Fragment shader contract:
     * - in  vec2 vTexCoord;
     * - uniform sampler2D uColorInput; bound to unit 0
     * - out vec4 fragColor;
     *
     * Additional uniforms can be pushed with setUniformFloat() and setUniformVec3().
     */
    class PostProcessPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the input color texture produced by an upstream pass.
         * \param colorHandle Upstream color texture handle.
         */
        void setInput(Texture2DHandle colorHandle) noexcept;

        /**
         * \brief Allocates the output texture in the cache and configures the internal framebuffer.
         * \param texCache Texture cache receiving the output texture.
         * \param width Output width in pixels.
         * \param height Output height in pixels.
         *
         * Must be called before the first render. Safe to call every frame; no-op if size is unchanged.
         */
        void setOutputSize(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Sets the fragment shader source of the fullscreen effect.
         * \param fragSrc GLSL fragment shader source code.
         *
         * The pass compiles it internally with the built-in fullscreen vertex shader.
         * Can be called before initialization or at runtime. Changes are compiled lazily on the next frame.
         */
        void setEffectSource(std::string fragSrc);

        /**
         * \brief Sets a float uniform on the effect shader.
         * \param name Uniform name.
         * \param value Uniform value.
         */
        void setUniformFloat(std::string_view name, float value);

        /**
         * \brief Sets a vec3 uniform on the effect shader.
         * \param name Uniform name.
         * \param v Pointer to three float components.
         */
        void setUniformVec3(std::string_view name, const float v[3]);

        /**
         * \brief Returns the color output texture of the pass.
         */
        [[nodiscard]] virtual Texture2DHandle colorOutput() const noexcept override { return m_outputHandle; }

        /**
         * \brief Returns the output framebuffer used by the pass when initialized.
         *
         * Returns nullptr when setOutputSize() has not been called yet.
         */
        [[nodiscard]] virtual const Framebuffer* outputFramebuffer() const noexcept override
        {
            return m_outputHandle.isValid() ? &m_outputFbo : nullptr;
        }

        /**
         * \brief Returns the output width in pixels.
         */
        [[nodiscard]] virtual int outputWidth() const noexcept override { return m_width; }

        /**
         * \brief Returns the output height in pixels.
         */
        [[nodiscard]] virtual int outputHeight() const noexcept override { return m_height; }

    private:
        explicit PostProcessPass(std::string name = "PostProcessPass")
            : RenderPass{ std::move(name) }
        {
            setRasterRegionState({ ViewportPolicy::FullTarget, {}, ScissorPolicy::Disabled, {} });
        }

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        void reallocateTarget();

        Texture2DHandle m_inputHandle;
        Texture2DHandle m_outputHandle;
        Framebuffer m_outputFbo;

        ShaderProgram m_shader; ///< compiled internally from user frag + builtin vert
        std::string m_fragSrc;  ///< stored until initialize()
        bool m_shaderDirty = false;

        Texture2DCache* m_texCache = nullptr;
        int m_width = 0;
        int m_height = 0;
        GLint m_savedViewport[4] = {};

        VertexArray m_dummyVAO;

        std::unordered_map<std::string, float> m_floatUniforms;
        std::unordered_map<std::string, std::array<float, 3>> m_vec3Uniforms;
    };
} // namespace nfx::graphics::gl
