#include "nfx/graphics/gl/pipeline/passes/GridPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    bool GridPass::initialize()
    {
        const auto* vert = shaders::find("passes/grid.vert");
        const auto* frag = shaders::find("passes/grid.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[GridPass] Missing embedded shader resources for grid pass\n");
            return false;
        }

        m_gridShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_gridShader.isValid())
        {
            std::fprintf(stderr, "[GridPass] Failed to compile grid shader\n");
            return false;
        }

        return true;
    }

    void GridPass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    void GridPass::execute(RenderResources& resources)
    {
        if (!m_gridShader.isValid())
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
                    "[GridPass] target color handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(m_targetColor.id));
                return;
            }

            m_targetFbo.bind();
            ++m_runtimeStats.fboBinds;
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
                std::fprintf(stderr, "[GridPass] target framebuffer incomplete: %s\n", m_targetFbo.statusString());
                m_targetFbo.unbind();
                return;
            }

            Context::current().functions().glViewport(0, 0, color->width(), color->height());
            m_targetBound = true;
        }

        RenderState state = RenderState::transparent();
        state.depthWrite = false;
        state.cullFace = false;
        state.apply();

        m_gridShader.bind();
        ++m_runtimeStats.shaderBinds;
        m_gridShader.setUniform("uGridSize", m_params.gridSize);
        m_gridShader.setUniform("uFadeDistance", m_params.fadeDistance);
        m_gridShader.setUniformVec3("uGridColor", m_params.color);

        m_vao.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 6);
        m_vao.unbind();
    }

    void GridPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
