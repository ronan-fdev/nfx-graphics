#include "nfx/graphics/gl/material/ibl/BrdfLutGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    BrdfLutGenerator::BrdfLutGenerator()
    {
        if (!Context::isInitialized())
        {
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "OpenGL context is not initialized on this thread");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/brdf_lut.frag");
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "missing embedded shaders: fullscreen.vert / material/ibl/brdf_lut.frag");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "shader compilation failed");
        }
    }

    bool BrdfLutGenerator::isValid() const noexcept
    {
        return m_shader.isValid();
    }

    Texture2D BrdfLutGenerator::generate(const Desc& desc) const
    {
        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Recoverable,
                "generator is not initialized");
            return {};
        }

        if (desc.width <= 0 || desc.height <= 0)
        {
            char msg[128];
            std::snprintf(msg, sizeof(msg), "invalid texture size %dx%d", desc.width, desc.height);
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                msg);
            return {};
        }

        Texture2D lut = Texture2D::allocate(
            desc.width,
            desc.height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Linear,
              .magFilter = Texture2D::Filter::Linear,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA16F });

        if (!lut.isValid())
        {
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to allocate LUT texture");
            return {};
        }

        Framebuffer fbo;
        fbo.bind();
        fbo.attachColorTexture(lut, 0);
        if (!fbo.isComplete())
        {
            char msg[160];
            std::snprintf(msg, sizeof(msg), "framebuffer incomplete: %s", fbo.statusString());
            internal::runtime::logError(
                "BrdfLutGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                msg);
            fbo.unbind();
            return {};
        }

        const auto& gl = Context::current().functions();
        GLint prevViewport[4] = { 0, 0, 0, 0 };
        gl.glGetIntegerv(VIEWPORT, prevViewport);
        gl.glViewport(0, 0, desc.width, desc.height);
        m_shader.bind();

        VertexArray vao;
        vao.bind();
        gl.glDrawArrays(TRIANGLES, 0, 3);
        vao.unbind();

        ShaderProgram::unbind();
        fbo.unbind();
        gl.glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
        return lut;
    }
} // namespace nfx::graphics::gl
