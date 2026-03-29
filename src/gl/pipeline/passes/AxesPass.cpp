#include "nfx/graphics/gl/pipeline/passes/AxesPass.h"

#include "nfx/graphics/gl/core/Context.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    void AxesPass::rebuildGeometry()
    {
        constexpr float kGridBiasY = 0.001f;

        // clang-format off
        const float vertices[] = {
            // X axis                                                        Red                sign
           -m_params.axisLength,  kGridBiasY         ,  0.0f               , 1.0f, 0.0f, 0.0f, -1.0f,
            0.0f               ,  kGridBiasY         ,  0.0f               , 1.0f, 0.0f, 0.0f, -1.0f,
            0.0f               ,  kGridBiasY         ,  0.0f               , 1.0f, 0.0f, 0.0f,  1.0f,
            m_params.axisLength,  kGridBiasY         ,  0.0f               , 1.0f, 0.0f, 0.0f,  1.0f,

            // Y axis                                                        Green
            0.0f               , -m_params.axisLength,  0.0f               , 0.0f, 1.0f, 0.0f, -1.0f,
            0.0f               ,  0.0f               ,  0.0f               , 0.0f, 1.0f, 0.0f, -1.0f,
            0.0f               ,  0.0f               ,  0.0f               , 0.0f, 1.0f, 0.0f,  1.0f,
            0.0f               ,  m_params.axisLength,  0.0f               , 0.0f, 1.0f, 0.0f,  1.0f,

            // Z axis                                                        Blue
            0.0f               , kGridBiasY          , -m_params.axisLength, 0.0f, 0.0f, 1.0f, -1.0f,
            0.0f               , kGridBiasY          ,  0.0f               , 0.0f, 0.0f, 1.0f, -1.0f,
            0.0f               , kGridBiasY          ,  0.0f               , 0.0f, 0.0f, 1.0f,  1.0f,
            0.0f               , kGridBiasY          ,  m_params.axisLength, 0.0f, 0.0f, 1.0f,  1.0f
        };
        // clang-format on

        m_vbo.bind();
        m_vbo.setData(vertices, sizeof(vertices));

        m_vao.bind();
        m_vao.setVertexLayout({
            VertexLayout::Float3, // location 0: position
            VertexLayout::Float3, // location 1: color
            VertexLayout::Float   // location 2: sign
        });
        m_vao.unbind();
        m_vbo.unbind();

        m_dirty = false;
    }

    bool AxesPass::initialize()
    {
        const auto* vert = shaders::find("passes/axes.vert");
        const auto* frag = shaders::find("passes/axes.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[AxesPass] Missing embedded shader resources for axes pass\n");
            return false;
        }

        m_axesShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_axesShader.isValid())
        {
            std::fprintf(stderr, "[AxesPass] Failed to compile axes shader\n");
            return false;
        }

        rebuildGeometry();

        return true;
    }

    void AxesPass::begin()
    {
        m_targetBound = false;
    }

    void AxesPass::execute(RenderResources& resources)
    {
        if (!m_axesShader.isValid())
        {
            return;
        }

        if (m_targetColor.isValid())
        {
            const Texture2D* color = resources.textures2D.get(m_targetColor);
            if (!color)
            {
                std::fprintf(
                    stderr,
                    "[AxesPass] target color handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(m_targetColor.id));
                return;
            }

            m_targetFbo.bind();
            m_targetFbo.attachColorTexture(*color);
            if (m_targetDepth.isValid())
            {
                const Texture2D* depth = resources.textures2D.get(m_targetDepth);
                if (depth)
                {
                    m_targetFbo.attachDepthTexture(*depth);
                }
            }

            if (!m_targetFbo.isComplete())
            {
                std::fprintf(stderr, "[AxesPass] target framebuffer incomplete: %s\n", m_targetFbo.statusString());
                m_targetFbo.unbind();
                return;
            }

            Context::current().functions().glViewport(0, 0, color->width(), color->height());
            m_targetBound = true;
        }

        if (m_dirty)
        {
            rebuildGeometry();
        }

        RenderState state = RenderState::transparent();
        state.depthWrite = false;
        state.depthFunc = RenderState::DepthFunc::LessOrEqual;
        state.apply();

        m_axesShader.bind();
        m_axesShader.setUniform("uFadeDistance", m_params.fadeDistance);
        m_axesShader.setUniform("uOccludedAlpha", 1.0f);

        m_vao.bind();
        Context::current().functions().glDrawArrays(LINES, 0, 12);
        m_vao.unbind();
    }

    void AxesPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
