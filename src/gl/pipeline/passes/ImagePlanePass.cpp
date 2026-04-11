#include "nfx/graphics/gl/pipeline/passes/ImagePlanePass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"

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
            std::fprintf(stderr, "[ImagePlanePass] missing embedded shaders: passes/image_plane.vert / .frag\n");
            return false;
        }

        m_shader = ShaderProgram::fromSources({
            { ShaderProgram::Stage::Vertex, vert->str() },
            { ShaderProgram::Stage::Fragment, frag->str() },
        });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[ImagePlanePass] failed to compile image plane shader\n");
            return false;
        }

        return true;
    }

    void ImagePlanePass::begin()
    {
        m_targetBound = false;
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
            std::fprintf(
                stderr,
                "[ImagePlanePass] image texture handle %llu not found\n",
                static_cast<unsigned long long>(m_imageHandle.id));
            return;
        }

        const Texture2D* colorTex = resources.textures2D.get(m_targetColor);
        if (!colorTex)
        {
            std::fprintf(
                stderr,
                "[ImagePlanePass] target color handle %llu not found\n",
                static_cast<unsigned long long>(m_targetColor.id));
            return;
        }

        m_targetFbo.bind();
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
            std::fprintf(stderr, "[ImagePlanePass] target framebuffer incomplete: %s\n", m_targetFbo.statusString());
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
        m_shader.bind();
        m_shader.setUniformMat4("uModel", m_transform);
        m_shader.setUniform("uImage", 0);
        m_shader.setUniform("uOpacity", safeOpacity);

        m_vao.bind();
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
