#include "nfx/graphics/gl/material/ibl/IrradianceMapGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    IrradianceMapGenerator::IrradianceMapGenerator()
    {
        if (!Context::isInitialized())
        {
            std::fprintf(stderr, "[IrradianceMapGenerator] OpenGL context is not initialized on this thread\n");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/irradiance_convolution.frag");
        if (!vert || !frag)
        {
            std::fprintf(
                stderr,
                "[IrradianceMapGenerator] missing embedded shaders: fullscreen.vert / "
                "material/ibl/irradiance_convolution.frag\n");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[IrradianceMapGenerator] shader compilation failed\n");
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
            std::fprintf(stderr, "[IrradianceMapGenerator] generator is not initialized\n");
            return {};
        }

        if (desc.size <= 0)
        {
            std::fprintf(stderr, "[IrradianceMapGenerator] invalid size %d\n", desc.size);
            return {};
        }

        if (!envMap.isValid())
        {
            std::fprintf(stderr, "[IrradianceMapGenerator] invalid source environment cubemap\n");
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
            std::fprintf(stderr, "[IrradianceMapGenerator] failed to allocate irradiance cubemap\n");
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
                std::fprintf(
                    stderr, "[IrradianceMapGenerator] FBO incomplete for face %d: %s\n", face, fbo.statusString());
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
