#include "nfx/graphics/gl/material/ibl/IrradianceMapGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    IrradianceMapGenerator::IrradianceMapGenerator()
    {
        if (!Context::isInitialized())
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "OpenGL context is not initialized on this thread");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/irradiance_convolution.frag");
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "missing embedded shaders: fullscreen.vert / material/ibl/irradiance_convolution.frag");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "shader compilation failed");
        }
    }

    bool IrradianceMapGenerator::isValid() const noexcept
    {
        return m_shader.isValid();
    }

    TextureCube IrradianceMapGenerator::generate(const TextureCube& envMap, const Desc& desc) const
    {
        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Recoverable,
                "generator is not initialized");
            return {};
        }

        if (desc.size <= 0)
        {
            char msg[96];
            std::snprintf(msg, sizeof(msg), "invalid size %d", desc.size);
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                msg);
            return {};
        }

        if (!envMap.isValid())
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "invalid source environment cubemap");
            return {};
        }

        TextureCube irradiance = TextureCube::allocate(
            desc.size,
            { .generateMipmaps = false,
              .mipLevels = 1,
              .minFilter = TextureCube::Filter::Linear,
              .magFilter = TextureCube::Filter::Linear,
              .wrapS = TextureCube::Wrap::ClampToEdge,
              .wrapT = TextureCube::Wrap::ClampToEdge,
              .wrapR = TextureCube::Wrap::ClampToEdge,
              .internalFormat = TextureCube::InternalFormat::RGBA16F });

        if (!irradiance.isValid())
        {
            internal::runtime::logError(
                "IrradianceMapGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to allocate irradiance cubemap");
            return {};
        }

        const auto& gl = Context::current().functions();
        const bool depthTestWasEnabled = (gl.glIsEnabled(DEPTH_TEST) != 0);
        GLint prevViewport[4] = { 0, 0, 0, 0 };
        gl.glGetIntegerv(VIEWPORT, prevViewport);
        gl.glDisable(DEPTH_TEST);

        Framebuffer fbo;
        VertexArray vao;
        m_shader.bind();
        envMap.bind(0);

        for (int face = 0; face < 6; ++face)
        {
            fbo.bind();
            fbo.attachColorCubeFace(irradiance, static_cast<TextureCube::Face>(face), 0);

            if (!fbo.isComplete())
            {
                char msg[160];
                std::snprintf(msg, sizeof(msg), "FBO incomplete for face %d: %s", face, fbo.statusString());
                internal::runtime::logError(
                    "IrradianceMapGenerator",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
                fbo.unbind();
                return {};
            }

            gl.glViewport(0, 0, desc.size, desc.size);
            m_shader.setUniform("uFace", face);
            vao.bind();
            gl.glDrawArrays(TRIANGLES, 0, 3);
            vao.unbind();
            fbo.unbind();
        }

        ShaderProgram::unbind();
        TextureCube::unbind(0);
        gl.glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
        if (depthTestWasEnabled)
        {
            gl.glEnable(DEPTH_TEST);
        }

        return irradiance;
    }
} // namespace nfx::graphics::gl
