#include "nfx/graphics/gl/pipeline/passes/SkyboxPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    bool SkyboxPass::initialize()
    {
        const auto* vertRes = shaders::find("passes/skybox.vert");
        const auto* fragRes = shaders::find("passes/skybox.frag");
        if (!vertRes || !fragRes)
        {
            internal::runtime::logError(
                "SkyboxPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Missing embedded shader resources");
            return false;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vertRes->str() }, { ShaderProgram::Stage::Fragment, fragRes->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "SkyboxPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to compile skybox shader");
            return false;
        }

        return true;
    }

    void SkyboxPass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    void SkyboxPass::execute(RenderResources& resources)
    {
        if (!m_shader.isValid() || !m_cubeCache || !m_cubemap.isValid())
        {
            return;
        }

        if (m_targetColor.isValid())
        {
            const Texture2D* color = resources.textures2D.get(m_targetColor);
            if (!color)
            {
                char msg[128];
                std::snprintf(
                    msg,
                    sizeof(msg),
                    "target color handle %llu not found, skipping",
                    static_cast<unsigned long long>(m_targetColor.id));
                internal::runtime::logError(
                    "SkyboxPass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
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
            m_targetBound = true;
        }

        const TextureCube* cube = m_cubeCache->get(m_cubemap);
        if (!cube || !cube->isValid())
        {
            return;
        }

        RenderState::skybox().apply();

        cube->bind(0);
        ++m_runtimeStats.textureBinds;
        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniform("uSkybox", 0);

        m_vao.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 36);
        m_vao.unbind();
    }

    void SkyboxPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
