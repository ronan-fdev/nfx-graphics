#include "nfx/graphics/gl/material/ibl/BrdfLutGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    BrdfLutGenerator::BrdfLutGenerator()
    {
        if (!Context::isInitialized())
        {
            std::fprintf(stderr, "[BrdfLutGenerator] OpenGL context is not initialized on this thread\n");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/brdf_lut.frag");
        if (!vert || !frag)
        {
            std::fprintf(
                stderr, "[BrdfLutGenerator] missing embedded shaders: fullscreen.vert / material/ibl/brdf_lut.frag\n");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[BrdfLutGenerator] shader compilation failed\n");
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
            std::fprintf(stderr, "[BrdfLutGenerator] generator is not initialized\n");
            return {};
        }

        if (desc.width <= 0 || desc.height <= 0)
        {
            std::fprintf(stderr, "[BrdfLutGenerator] invalid texture size %dx%d\n", desc.width, desc.height);
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
            std::fprintf(stderr, "[BrdfLutGenerator] failed to allocate LUT texture\n");
            return {};
        }

        Framebuffer fbo;
        fbo.bind();
        fbo.attachColorTexture(lut, 0);
        if (!fbo.isComplete())
        {
            std::fprintf(stderr, "[BrdfLutGenerator] framebuffer incomplete: %s\n", fbo.statusString());
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
