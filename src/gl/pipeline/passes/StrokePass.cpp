#include "nfx/graphics/gl/pipeline/passes/StrokePass.h"

#include "nfx/graphics/gl/core/buffers/VertexLayout.h"
#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/frame/FrameData.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        [[nodiscard]] float toFloat(std::uint8_t v) noexcept
        {
            return static_cast<float>(v) / 255.0f;
        }

        constexpr const char* kStrokeVertResource = "passes/stroke.vert";
        constexpr const char* kStrokeFragResource = "flat_color.frag";
    } // namespace

    StrokeItemHandle StrokePass::addStroke(const StrokeItemDesc2D& desc)
    {
        if (desc.xy.empty() || desc.xy.data() == nullptr || desc.pointCount < 2 || desc.xy.size() < desc.pointCount * 2)
        {
            internal::runtime::logError(
                "StrokePass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "addStroke: invalid polyline input");
            return {};
        }

        StrokePolyline2D polyline;
        polyline.xy = desc.xy.data();
        polyline.pointCount = desc.pointCount;
        polyline.closed = desc.closed;

        const StrokeMesh2D mesh = m_tessellator.tessellate(polyline, desc.style);
        if (mesh.vertices.empty() || mesh.indices.empty())
        {
            internal::runtime::logError(
                "StrokePass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "addStroke: tessellation produced empty mesh");
            return {};
        }

        StrokeItem item;
        item.handle = StrokeItemHandle{ m_nextId++ };
        item.transform = desc.transform;
        item.mesh = mesh;

        item.gpuVerts.reserve(mesh.indices.size() * 7);
        for (std::uint16_t idx : mesh.indices)
        {
            if (idx >= mesh.vertices.size())
            {
                continue;
            }
            const StrokeVertex2D& v = mesh.vertices[idx];
            item.gpuVerts.push_back(v.x);
            item.gpuVerts.push_back(v.y);
            item.gpuVerts.push_back(0.0f);
            item.gpuVerts.push_back(toFloat(v.r));
            item.gpuVerts.push_back(toFloat(v.g));
            item.gpuVerts.push_back(toFloat(v.b));
            item.gpuVerts.push_back(toFloat(v.a));
        }

        m_items.push_back(std::move(item));
        return m_items.back().handle;
    }

    void StrokePass::remove(StrokeItemHandle handle)
    {
        const auto it = std::find_if(
            m_items.begin(), m_items.end(), [handle](const StrokeItem& item) { return item.handle == handle; });

        if (it == m_items.end())
        {
            char msg[128];
            std::snprintf(
                msg, sizeof(msg), "remove: handle %llu not found", static_cast<unsigned long long>(handle.id));
            internal::runtime::logError(
                "StrokePass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        m_items.erase(it);
    }

    void StrokePass::clear()
    {
        m_items.clear();
    }

    bool StrokePass::initialize()
    {
        const auto* vert = shaders::find(kStrokeVertResource);
        const auto* frag = shaders::find(kStrokeFragResource);
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "StrokePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Missing embedded shader resources");
            return false;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            internal::runtime::logError(
                "StrokePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to compile shader");
            return false;
        }

        m_vbo.bind();
        m_vao.bind();
        m_vao.setVertexLayout({ VertexLayout::Float3, VertexLayout::Float4 });
        m_vao.unbind();
        m_vbo.unbind();

        return true;
    }

    void StrokePass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    void StrokePass::execute(RenderResources& resources)
    {
        if (m_items.empty() || !m_shader.isValid())
        {
            return;
        }

        const FrameData* frame = currentFrameData();
        if (!frame)
        {
            internal::runtime::logError(
                "StrokePass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "execute: missing frame data");
            return;
        }

        const Texture2D* targetColor = nullptr;
        if (m_targetColor.isValid())
        {
            targetColor = resources.textures2D.get(m_targetColor);
            if (!targetColor)
            {
                char msg[128];
                std::snprintf(
                    msg,
                    sizeof(msg),
                    "target color handle %llu not found, skipping",
                    static_cast<unsigned long long>(m_targetColor.id));
                internal::runtime::logError(
                    "StrokePass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
                return;
            }

            m_targetFbo.bind();
            ++m_runtimeStats.fboBinds;
            m_targetFbo.attachColorTexture(*targetColor);
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

        const auto* vp = currentViewport();
        const GLint vpX = vp ? static_cast<GLint>(vp->x) : 0;
        const GLint vpY = vp ? static_cast<GLint>(vp->y) : 0;

        const float vpW =
            vp ? static_cast<float>(vp->width) : (targetColor ? static_cast<float>(targetColor->width()) : 1.0f);
        const float vpH =
            vp ? static_cast<float>(vp->height) : (targetColor ? static_cast<float>(targetColor->height()) : 1.0f);

        const auto& gl = Context::current().functions();
        gl.glViewport(vpX, vpY, static_cast<GLsizei>(vpW), static_cast<GLsizei>(vpH));

        RenderState state = RenderState::opaque();
        state.blend = false;
        state.depthWrite = true;
        state.depthTest = true;
        state.cullFace = false;
        state.apply();

        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniformMat4("uViewProj", frame->camera.viewProj);

        for (const StrokeItem& item : m_items)
        {
            if (item.gpuVerts.empty())
            {
                continue;
            }

            m_shader.setUniformMat4("uModel", item.transform.data());

            m_vao.bind();
            ++m_runtimeStats.vaoBinds;
            m_vbo.bind();
            ++m_runtimeStats.vboBinds;
            m_vbo.setData(item.gpuVerts.data(), item.gpuVerts.size() * sizeof(float), Buffer::Usage::StaticDraw);

            ++m_runtimeStats.drawCalls;
            gl.glDrawArrays(TRIANGLES, 0, static_cast<GLsizei>(item.gpuVerts.size() / 7));

            m_vbo.unbind();
            m_vao.unbind();
        }
        m_shader.unbind();
    }

    void StrokePass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
