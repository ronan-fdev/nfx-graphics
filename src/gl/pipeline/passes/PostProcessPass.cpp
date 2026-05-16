#include "nfx/graphics/gl/pipeline/passes/PostProcessPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    void PostProcessPass::setInput(Texture2DHandle colorHandle) noexcept
    {
        m_inputHandle = colorHandle;
    }

    void PostProcessPass::setOutputSize(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            assert(width >= 1 && height >= 1 && "PostProcessPass::setOutputSize: width and height must be >= 1");
            return;
        }

        m_texCache = &texCache;
        if (m_width == width && m_height == height && m_outputHandle.isValid())
        {
            return;
        }
        m_width = width;
        m_height = height;
        reallocateTarget();
    }

    void PostProcessPass::setEffectSource(std::string fragSrc)
    {
        m_fragSrc = std::move(fragSrc);
        m_shaderDirty = true;
    }

    void PostProcessPass::setUniformFloat(std::string_view name, float value)
    {
        m_floatUniforms[std::string{ name }] = value;
    }

    void PostProcessPass::setUniformVec3(std::string_view name, const float v[3])
    {
        m_vec3Uniforms[std::string{ name }] = { v[0], v[1], v[2] };
    }

    void PostProcessPass::reallocateTarget()
    {
        if (!m_texCache || m_width == 0 || m_height == 0)
        {
            return;
        }

        if (m_outputHandle.isValid())
        {
            m_texCache->remove(m_outputHandle);
        }

        m_outputHandle = m_texCache->add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Linear,
              .magFilter = Texture2D::Filter::Linear,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA8 }));

        const Texture2D* outputTex = m_texCache->get(m_outputHandle);
        if (!outputTex)
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to resolve output texture from cache");
            return;
        }

        m_outputFbo.bind();
        m_outputFbo.attachColorTexture(*outputTex);
        if (!m_outputFbo.isComplete())
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "Output framebuffer is incomplete after color attachment");
        }
        m_outputFbo.unbind();
    }

    bool PostProcessPass::initialize()
    {
        if (m_fragSrc.empty())
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Programming,
                "No effect source set - call setEffectSource()");
            return false;
        }

        const auto* vertRes = shaders::find("fullscreen.vert");
        if (!vertRes)
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Builtin 'fullscreen.vert' not found");
            return false;
        }

        m_shader = ShaderProgram::fromSources({
            { ShaderProgram::Stage::Vertex, vertRes->str() },
            { ShaderProgram::Stage::Fragment, m_fragSrc },
        });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to compile effect shader");
            return false;
        }

        m_shaderDirty = false;
        m_fragSrc.clear();
        m_fragSrc.shrink_to_fit();
        return true;
    }

    void PostProcessPass::begin()
    {
        resetRuntimeStats();
        if (m_shaderDirty)
        {
            if (!initialize())
            {
                return;
            }
        }

        if (!m_outputHandle.isValid())
        {
            internal::runtime::logError(
                "PostProcessPass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "No output target set - call setOutputSize()");
            return;
        }

        Context::current().functions().glGetIntegerv(VIEWPORT, m_savedViewport);
        m_outputFbo.bind();
        ++m_runtimeStats.fboBinds;
        Context::current().functions().glViewport(0, 0, m_width, m_height);
    }

    void PostProcessPass::execute(RenderResources& resources)
    {
        if (!m_inputHandle.isValid() || !m_shader.isValid() || !m_outputHandle.isValid())
        {
            return;
        }

        const Texture2D* inputTex = resources.textures2D.get(m_inputHandle);
        if (!inputTex)
        {
            char msg[160];
            std::snprintf(
                msg,
                sizeof(msg),
                "input color handle %llu not found in Texture2DCache",
                static_cast<unsigned long long>(m_inputHandle.id));
            internal::runtime::logError(
                "PostProcessPass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        RenderState rs;
        rs.depthTest = false;
        rs.blend = false;
        rs.apply();

        inputTex->bind(0);
        ++m_runtimeStats.textureBinds;
        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniform("uColorInput", 0);

        for (const auto& [name, val] : m_floatUniforms)
        {
            m_shader.setUniform(name.c_str(), val);
        }
        for (const auto& [name, val] : m_vec3Uniforms)
        {
            m_shader.setUniformVec3(name.c_str(), val.data());
        }

        m_dummyVAO.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 3);
        m_dummyVAO.unbind();
    }

    void PostProcessPass::end()
    {
        if (!m_outputHandle.isValid())
        {
            return;
        }

        m_outputFbo.unbind();
        Context::current().functions().glViewport(
            m_savedViewport[0], m_savedViewport[1], m_savedViewport[2], m_savedViewport[3]);
    }
} // namespace nfx::graphics::gl
