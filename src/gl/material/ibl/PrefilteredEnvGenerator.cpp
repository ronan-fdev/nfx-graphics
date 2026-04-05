#include "nfx/graphics/gl/material/ibl/PrefilteredEnvGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    PrefilteredEnvGenerator::PrefilteredEnvGenerator()
    {
        if (!Context::isInitialized())
        {
            std::fprintf(stderr, "[PrefilteredEnvGenerator] OpenGL context is not initialized on this thread\n");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/prefiltered_env.frag");
        if (!vert || !frag)
        {
            std::fprintf(
                stderr,
                "[PrefilteredEnvGenerator] missing embedded shaders: fullscreen.vert / "
                "material/ibl/prefiltered_env.frag\n");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[PrefilteredEnvGenerator] shader compilation failed\n");
        }
    }

    bool PrefilteredEnvGenerator::isValid() const noexcept
    {
        return m_shader.isValid();
    }

    TextureCube PrefilteredEnvGenerator::generate(const TextureCube& envMap, const Desc& desc) const
    {
        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[PrefilteredEnvGenerator] generator is not initialized\n");
            return {};
        }

        if (desc.size <= 0 || desc.numMips <= 0)
        {
            std::fprintf(
                stderr, "[PrefilteredEnvGenerator] invalid desc: size=%d numMips=%d\n", desc.size, desc.numMips);
            return {};
        }

        if (!envMap.isValid())
        {
            std::fprintf(stderr, "[PrefilteredEnvGenerator] invalid source environment cubemap\n");
            return {};
        }

        TextureCube prefiltered = TextureCube::allocate(
            desc.size,
            { .generateMipmaps = false,
              .mipLevels = desc.numMips,
              .minFilter = TextureCube::Filter::LinearMipmapLinear,
              .magFilter = TextureCube::Filter::Linear,
              .wrapS = TextureCube::Wrap::ClampToEdge,
              .wrapT = TextureCube::Wrap::ClampToEdge,
              .wrapR = TextureCube::Wrap::ClampToEdge,
              .internalFormat = TextureCube::InternalFormat::RGBA16F });

        if (!prefiltered.isValid())
        {
            std::fprintf(stderr, "[PrefilteredEnvGenerator] failed to allocate prefiltered cubemap\n");
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
        m_shader.setUniform("uSampleCount", desc.sampleCount);

        for (int mip = 0; mip < desc.numMips; ++mip)
        {
            const float roughness =
                (desc.numMips > 1) ? static_cast<float>(mip) / static_cast<float>(desc.numMips - 1) : 0.0f;

            const int mipSize = std::max(1, desc.size >> mip);
            m_shader.setUniform("uRoughness", roughness);

            for (int face = 0; face < 6; ++face)
            {
                fbo.bind();
                fbo.attachColorCubeFace(prefiltered, static_cast<TextureCube::Face>(face), mip);

                if (!fbo.isComplete())
                {
                    std::fprintf(
                        stderr,
                        "[PrefilteredEnvGenerator] FBO incomplete at mip=%d face=%d: %s\n",
                        mip,
                        face,
                        fbo.statusString());
                    fbo.unbind();
                    return {};
                }

                gl.glViewport(0, 0, mipSize, mipSize);
                m_shader.setUniform("uFace", face);
                vao.bind();
                gl.glDrawArrays(TRIANGLES, 0, 3);
                vao.unbind();
                fbo.unbind();
            }
        }

        ShaderProgram::unbind();
        TextureCube::unbind(0);
        gl.glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
        if (depthTestWasEnabled)
        {
            gl.glEnable(DEPTH_TEST);
        }

        return prefiltered;
    }
} // namespace nfx::graphics::gl
