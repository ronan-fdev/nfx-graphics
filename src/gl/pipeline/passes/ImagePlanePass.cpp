#include "nfx/graphics/gl/pipeline/passes/ImagePlanePass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    bool ImagePlanePass::initialize()
    {
        const auto* vert = shaders::find("passes/image_plane.vert");
        const auto* frag = shaders::find("passes/image_plane.frag");
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "ImagePlanePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "missing embedded shaders: passes/image_plane.vert / .frag");
            return false;
        }

        m_shader = ShaderProgram::fromSources({
            { ShaderProgram::Stage::Vertex, vert->str() },
            { ShaderProgram::Stage::Fragment, frag->str() },
        });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "ImagePlanePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to compile image plane shader");
            return false;
        }

        return true;
    }

    void ImagePlanePass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    void ImagePlanePass::execute(RenderResources& resources)
    {
        if (!m_shader.isValid() || !m_imageHandle.isValid() || !m_targetColor.isValid())
        {
            return;
        }

        const Texture2D* imageTex = resources.textures2D.get(m_imageHandle);
        if (!imageTex)
        {
            char msg[128];
            std::snprintf(
                msg,
                sizeof(msg),
                "image texture handle %llu not found",
                static_cast<unsigned long long>(m_imageHandle.id));
            internal::runtime::logError(
                "ImagePlanePass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        const Texture2D* colorTex = resources.textures2D.get(m_targetColor);
        if (!colorTex)
        {
            char msg[128];
            std::snprintf(
                msg,
                sizeof(msg),
                "target color handle %llu not found",
                static_cast<unsigned long long>(m_targetColor.id));
            internal::runtime::logError(
                "ImagePlanePass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        m_targetFbo.bind();
        ++m_runtimeStats.fboBinds;
        m_targetFbo.attachColorTexture(*colorTex, 0);
        if (m_targetDepth.isValid())
        {
            if (const Texture2D* depthTex = resources.textures2D.get(m_targetDepth))
            {
                m_targetFbo.attachDepthTexture(*depthTex);
            }
        }

        if (!m_targetFbo.isComplete())
        {
            char msg[128];
            std::snprintf(msg, sizeof(msg), "target framebuffer incomplete: %s", m_targetFbo.statusString());
            internal::runtime::logError(
                "ImagePlanePass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            m_targetFbo.unbind();
            return;
        }

        Context::current().functions().glViewport(0, 0, colorTex->width(), colorTex->height());
        m_targetBound = true;

        RenderState state;
        state.depthTest = m_depthTest;
        state.depthWrite = false;
        state.blend = true;
        state.blendSrc = RenderState::BlendFactor::SrcAlpha;
        state.blendDst = RenderState::BlendFactor::OneMinusSrcAlpha;
        state.cullFace = false;
        state.apply();

        const float safeOpacity = std::clamp(m_opacity, 0.0f, 1.0f);

        imageTex->bind(0);
        ++m_runtimeStats.textureBinds;
        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniformMat4("uModel", m_transform);
        m_shader.setUniform("uImage", 0);
        m_shader.setUniform("uOpacity", safeOpacity);

        m_vao.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 6);
        m_vao.unbind();
    }

    void ImagePlanePass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
