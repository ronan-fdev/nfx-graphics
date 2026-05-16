#include "nfx/graphics/gl/material/ibl/PrefilteredEnvGenerator.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    PrefilteredEnvGenerator::PrefilteredEnvGenerator()
    {
        if (!Context::isInitialized())
        {
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "OpenGL context is not initialized on this thread");
            return;
        }

        const EmbeddedResource* vert = shaders::find("fullscreen.vert");
        const EmbeddedResource* frag = shaders::find("material/ibl/prefiltered_env.frag");
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "missing embedded shaders: fullscreen.vert / material/ibl/prefiltered_env.frag");
            return;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "shader compilation failed");
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
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Recoverable,
                "generator is not initialized");
            return {};
        }

        if (desc.size <= 0 || desc.numMips <= 0)
        {
            char msg[128];
            std::snprintf(msg, sizeof(msg), "invalid desc: size=%d numMips=%d", desc.size, desc.numMips);
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                msg);
            return {};
        }

        if (!envMap.isValid())
        {
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "invalid source environment cubemap");
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
            internal::runtime::logError(
                "PrefilteredEnvGenerator",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to allocate prefiltered cubemap");
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
                    char msg[176];
                    std::snprintf(
                        msg, sizeof(msg), "FBO incomplete at mip=%d face=%d: %s", mip, face, fbo.statusString());
                    internal::runtime::logError(
                        "PrefilteredEnvGenerator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        msg);
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
