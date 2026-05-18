#include "nfx/graphics/gl/pipeline/passes/PresentPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/raster/ViewportRect.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    bool PresentPass::initialize()
    {
        const auto* vertRes = shaders::find("fullscreen.vert");
        const auto* fragRes = shaders::find("passes/present.frag");
        if (!vertRes || !fragRes)
        {
            internal::runtime::logError(
                "PresentPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Missing embedded present shaders");
            return false;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vertRes->str() }, { ShaderProgram::Stage::Fragment, fragRes->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "PresentPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to compile present shader");
            return false;
        }

        return true;
    }

    void PresentPass::begin()
    {
        resetRuntimeStats();
    }

    void PresentPass::execute(RenderResources& resources)
    {
        if (!m_inputHandle.isValid() || !m_shader.isValid())
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
                "PresentPass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        RenderState rs;
        rs.depthTest = false;
        rs.depthWrite = false;
        rs.blend = false;
        rs.apply();

        if (const ViewportRect* viewport = currentViewport())
        {
            Context::current().functions().glViewport(viewport->x, viewport->y, viewport->width, viewport->height);
        }

        inputTex->bind(0);
        ++m_runtimeStats.textureBinds;

        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniform("uColorInput", 0);
        m_shader.setUniform("uExposure", std::max(m_exposure, 0.001f));
        m_shader.setUniform("uGamma", std::max(m_gamma, 0.001f));
        m_shader.setUniform("uTonemapEnabled", m_tonemapEnabled ? 1 : 0);
        m_shader.setUniform("uGammaEnabled", m_gammaEnabled ? 1 : 0);

        m_dummyVAO.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 3);
        m_dummyVAO.unbind();
    }

    void PresentPass::end() {}
} // namespace nfx::graphics::gl
