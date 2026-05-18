#include "nfx/graphics/gl/pipeline/passes/Polygon2DPass.h"

#include "nfx/graphics/gl/core/buffers/VertexLayout.h"
#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/raster/ViewportRect.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        constexpr float kEps = 1e-6f;

        struct Vertex2D
        {
            float x;
            float y;
            float r;
            float g;
            float b;
            float a;
        };

        [[nodiscard]] bool isValidPackedXy(std::span<const float> xyPairs)
        {
            return (xyPairs.size() >= 6u) && ((xyPairs.size() % 2u) == 0u);
        }

        [[nodiscard]] bool isConvexPolygon(std::span<const float> xyPairs)
        {
            const std::size_t n = xyPairs.size() / 2u;
            if (n < 3u)
            {
                return false;
            }

            float referenceCross = 0.0f;

            for (std::size_t i = 0; i < n; ++i)
            {
                const std::size_t i0 = i;
                const std::size_t i1 = (i + 1u) % n;
                const std::size_t i2 = (i + 2u) % n;

                const float x0 = xyPairs[i0 * 2u + 0u];
                const float y0 = xyPairs[i0 * 2u + 1u];
                const float x1 = xyPairs[i1 * 2u + 0u];
                const float y1 = xyPairs[i1 * 2u + 1u];
                const float x2 = xyPairs[i2 * 2u + 0u];
                const float y2 = xyPairs[i2 * 2u + 1u];

                const float e1x = x1 - x0;
                const float e1y = y1 - y0;
                const float e2x = x2 - x1;
                const float e2y = y2 - y1;
                const float cross = (e1x * e2y) - (e1y * e2x);

                if (std::abs(cross) <= kEps)
                {
                    continue;
                }

                if (std::abs(referenceCross) <= kEps)
                {
                    referenceCross = cross;
                    continue;
                }

                if ((referenceCross > 0.0f && cross < 0.0f) || (referenceCross < 0.0f && cross > 0.0f))
                {
                    return false;
                }
            }

            // Reject fully collinear point sets
            return std::abs(referenceCross) > kEps;
        }
    } // namespace

    Polygon2DHandle Polygon2DPass::addConvexPolygon(std::span<const float> xyPairs, const Polygon2DStyle& style)
    {
        if (!isValidPackedXy(xyPairs))
        {
            internal::runtime::logError(
                "Polygon2DPass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "addConvexPolygon: invalid packed XY list");
            return {};
        }

        if (!isConvexPolygon(xyPairs))
        {
            internal::runtime::logError(
                "Polygon2DPass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "addConvexPolygon: polygon is not strictly convex");
            return {};
        }

        PolygonItem item;
        item.handle = Polygon2DHandle{ m_nextId++ };
        item.xyPairs.assign(xyPairs.begin(), xyPairs.end());
        item.style = style;
        m_items.push_back(std::move(item));
        return m_items.back().handle;
    }

    Polygon2DHandle Polygon2DPass::addRect(float x, float y, float w, float h, const Polygon2DStyle& style)
    {
        if (w <= 0.0f || h <= 0.0f)
        {
            internal::runtime::logError(
                "Polygon2DPass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "addRect: non-positive size");
            return {};
        }

        const std::array<float, 8> rect = {
            x,     // top-left
            y,     // top-left
            x + w, // top-right
            y,     // top-right
            x + w, // bottom-right
            y + h, // bottom-right
            x,     // bottom-left
            y + h  // bottom-left
        };

        return addConvexPolygon(std::span<const float>{ rect.data(), rect.size() }, style);
    }

    void Polygon2DPass::remove(Polygon2DHandle handle)
    {
        const auto it =
            std::find_if(m_items.begin(), m_items.end(), [handle](const PolygonItem& p) { return p.handle == handle; });

        if (it == m_items.end())
        {
            char msg[128];
            std::snprintf(
                msg, sizeof(msg), "remove: handle %llu not found", static_cast<unsigned long long>(handle.id));
            internal::runtime::logError(
                "Polygon2DPass", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
            return;
        }

        m_items.erase(it);
    }

    void Polygon2DPass::clear()
    {
        m_items.clear();
    }

    bool Polygon2DPass::initialize()
    {
        const auto* vert = shaders::find("passes/polygon2d.vert");
        const auto* frag = shaders::find("flat_color.frag");
        if (!vert || !frag)
        {
            internal::runtime::logError(
                "Polygon2DPass",
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
                "Polygon2DPass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "Failed to compile shader");
            return false;
        }

        m_vbo.bind();
        m_vao.bind();
        m_vao.setVertexLayout({
            VertexLayout::Float2, // location 0: screen-space pos
            VertexLayout::Float4  // location 1: RGBA color
        });
        m_vao.unbind();
        m_vbo.unbind();

        return true;
    }

    void Polygon2DPass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    void Polygon2DPass::execute(RenderResources& resources)
    {
        if (m_items.empty() || !m_shader.isValid())
        {
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
                    "Polygon2DPass",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
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
        const float vpW =
            vp ? static_cast<float>(vp->width) : (targetColor ? static_cast<float>(targetColor->width()) : 1.0f);
        const float vpH =
            vp ? static_cast<float>(vp->height) : (targetColor ? static_cast<float>(targetColor->height()) : 1.0f);

        const auto& gl = Context::current().functions();
        gl.glViewport(0, 0, static_cast<GLsizei>(vpW), static_cast<GLsizei>(vpH));

        RenderState state = RenderState::opaque();
        state.blend = true;
        state.blendSrc = RenderState::BlendFactor::SrcAlpha;
        state.blendDst = RenderState::BlendFactor::OneMinusSrcAlpha;
        state.depthWrite = false;
        state.depthTest = false;
        state.cullFace = false;
        state.apply();

        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniform("uViewport", UniformVec2{ vpW, vpH });

        std::vector<Vertex2D> verts;
        verts.reserve(1024);

        for (const PolygonItem& item : m_items)
        {
            const std::size_t pointCount = item.xyPairs.size() / 2u;
            if (pointCount < 3u)
            {
                continue;
            }

            const float x0 = item.xyPairs[0];
            const float y0 = item.xyPairs[1];

            for (std::size_t i = 1u; (i + 1u) < pointCount; ++i)
            {
                const std::size_t i1 = i * 2u;
                const std::size_t i2 = (i + 1u) * 2u;

                verts.push_back(
                    { x0, y0, item.style.color[0], item.style.color[1], item.style.color[2], item.style.alpha });

                verts.push_back({ item.xyPairs[i1],
                                  item.xyPairs[i1 + 1u],
                                  item.style.color[0],
                                  item.style.color[1],
                                  item.style.color[2],
                                  item.style.alpha });

                verts.push_back({ item.xyPairs[i2],
                                  item.xyPairs[i2 + 1u],
                                  item.style.color[0],
                                  item.style.color[1],
                                  item.style.color[2],
                                  item.style.alpha });
            }
        }

        if (verts.empty())
        {
            m_shader.unbind();
            return;
        }

        m_vao.bind();
        ++m_runtimeStats.vaoBinds;
        m_vbo.bind();
        ++m_runtimeStats.vboBinds;
        m_vbo.setData(
            verts.data(), static_cast<std::size_t>(verts.size() * sizeof(Vertex2D)), Buffer::Usage::StreamDraw);

        ++m_runtimeStats.drawCalls;
        gl.glDrawArrays(TRIANGLES, 0, static_cast<GLsizei>(verts.size()));

        m_vbo.unbind();
        m_vao.unbind();
        m_shader.unbind();
    }

    void Polygon2DPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
