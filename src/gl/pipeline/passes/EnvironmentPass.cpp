#include "nfx/graphics/gl/pipeline/passes/EnvironmentPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    bool EnvironmentPass::initialize()
    {
        const EmbeddedResource* vert = shaders::find("passes/environment.vert");
        const EmbeddedResource* frag = shaders::find("passes/environment.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[EnvironmentPass] Missing embedded environment shaders\n");
            return false;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[EnvironmentPass] Failed to compile environment shader\n");
            return false;
        }

        return true;
    }

    void EnvironmentPass::begin()
    {
        m_targetBound = false;
    }

    void EnvironmentPass::execute(RenderResources& resources)
    {
        if (!m_shader.isValid())
        {
            return;
        }

        if (!m_targetColor.isValid())
        {
            std::fprintf(stderr, "[EnvironmentPass] target color is not set, skipping\n");
            return;
        }

        if (m_targetColor.isValid())
        {
            const Texture2D* color = resources.textures2D.get(m_targetColor);
            if (!color)
            {
                std::fprintf(
                    stderr,
                    "[EnvironmentPass] target color handle %llu not found, skipping\n",
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
            m_targetBound = true;
        }

        RenderState::skybox().apply();

        m_shader.bind();
        m_shader.setUniform("uEnvMap", static_cast<int>(TextureBindings::EnvMap));
        m_shader.setUniform("uEnvIntensity", std::max(0.0f, m_intensity));

        m_vao.bind();
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 36);
        m_vao.unbind();
    }

    void EnvironmentPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
