#include "nfx/graphics/gl/pipeline/passes/TextPass.h"

#include "nfx/graphics/gl/core/buffers/VertexLayout.h"
#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/pipeline/ViewportRect.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        // One quad vertex: screen-space position + atlas UV
        struct GlyphVertex
        {
            float x, y;
            float u, v;
        };

        // Build 6 vertices (2 triangles) for one glyph and append to buffer
        void appendGlyphQuad(std::vector<GlyphVertex>& buf, const Glyph& g, float penX, float penY, float scale)
        {
            const float x0 = penX + g.bearingXPx * scale;
            const float y0 = penY - g.bearingYPx * scale;
            const float x1 = x0 + g.widthPx * scale;
            const float y1 = y0 + g.heightPx * scale;

            // Triangle 1: top-left, bottom-left, bottom-right
            buf.push_back({ x0, y0, g.u0, g.v0 });
            buf.push_back({ x0, y1, g.u0, g.v1 });
            buf.push_back({ x1, y1, g.u1, g.v1 });

            // Triangle 2: top-left, bottom-right, top-right
            buf.push_back({ x0, y0, g.u0, g.v0 });
            buf.push_back({ x1, y1, g.u1, g.v1 });
            buf.push_back({ x1, y0, g.u1, g.v0 });
        }
    } // namespace

    TextItemHandle TextPass::addTextUtf8(
        FontHandle font, std::string_view utf8, float x, float y, const TextStyle& style)
    {
        if (!font.isValid())
        {
            std::fprintf(stderr, "[TextPass] addTextUtf8: invalid font handle\n");
            return {};
        }

        TextItem item;
        item.handle = TextItemHandle{ m_nextTextId++ };
        item.font = font;
        item.utf8 = std::string{ utf8 };
        item.preShaped = false;
        item.x = x;
        item.y = y;
        item.style = style;

        m_itemIndex[item.handle.id] = m_items.size();
        m_items.push_back(std::move(item));
        return m_items.back().handle;
    }

    TextItemHandle TextPass::addGlyphRun(
        FontHandle font, const std::vector<GlyphPlacement>& glyphs, float x, float y, const TextStyle& style)
    {
        if (!font.isValid())
        {
            std::fprintf(stderr, "[TextPass] addGlyphRun: invalid font handle\n");
            return {};
        }

        TextItem item;
        item.handle = TextItemHandle{ m_nextTextId++ };
        item.font = font;
        item.glyphs = glyphs;
        item.preShaped = true;
        item.x = x;
        item.y = y;
        item.style = style;

        m_itemIndex[item.handle.id] = m_items.size();
        m_items.push_back(std::move(item));
        return m_items.back().handle;
    }

    void TextPass::updateText(TextItemHandle handle, std::string_view utf8)
    {
        const auto it = m_itemIndex.find(handle.id);
        if (it == m_itemIndex.end())
        {
            std::fprintf(
                stderr,
                "[TextPass] updateText(utf8): handle %llu not found\n",
                static_cast<unsigned long long>(handle.id));
            return;
        }

        TextItem& item = m_items[it->second];
        item.utf8 = std::string{ utf8 };
        item.glyphs.clear();
        item.preShaped = false;
    }

    void TextPass::updateText(TextItemHandle handle, const std::vector<GlyphPlacement>& glyphs)
    {
        const auto it = m_itemIndex.find(handle.id);
        if (it == m_itemIndex.end())
        {
            std::fprintf(
                stderr,
                "[TextPass] updateText(glyphs): handle %llu not found\n",
                static_cast<unsigned long long>(handle.id));
            return;
        }

        TextItem& item = m_items[it->second];
        item.glyphs = glyphs;
        item.preShaped = true;
    }

    void TextPass::removeText(TextItemHandle handle)
    {
        const auto it = m_itemIndex.find(handle.id);
        if (it == m_itemIndex.end())
        {
            std::fprintf(
                stderr, "[TextPass] removeText: handle %llu not found\n", static_cast<unsigned long long>(handle.id));
            return;
        }

        const std::size_t index = it->second;
        m_itemIndex.erase(it);

        // Swap with back and update index
        if (index < m_items.size() - 1)
        {
            m_items[index] = std::move(m_items.back());
            m_itemIndex[m_items[index].handle.id] = index;
        }
        m_items.pop_back();
    }

    void TextPass::clearTexts()
    {
        m_items.clear();
        m_itemIndex.clear();
    }

    void TextPass::begin()
    {
        m_targetBound = false;
        resetRuntimeStats();
    }

    bool TextPass::initialize()
    {
        const auto* vert = shaders::find("passes/text.vert");
        const auto* frag = shaders::find("passes/text.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[TextPass] Missing embedded shader resources\n");
            return false;
        }

        m_shader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        if (!m_shader.isValid())
        {
            std::fprintf(stderr, "[TextPass] Failed to compile text shader\n");
            return false;
        }

        m_vbo.bind();
        m_vao.bind();
        m_vao.setVertexLayout({
            VertexLayout::Float2, // location 0: screen-space pos
            VertexLayout::Float2  // location 1: atlas UV
        });
        m_vao.unbind();
        m_vbo.unbind();

        return true;
    }

    void TextPass::execute(RenderResources& resources)
    {
        if (m_items.empty() || !m_shader.isValid())
        {
            return;
        }

        if (!m_fontCache)
        {
            std::fprintf(stderr, "[TextPass] execute: font cache not set, call setFontCache() first\n");
            return;
        }

        const Texture2D* targetColor = nullptr;

        if (m_targetColor.isValid())
        {
            targetColor = resources.textures2D.get(m_targetColor);
            if (!targetColor)
            {
                std::fprintf(
                    stderr,
                    "[TextPass] target color handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(m_targetColor.id));
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

        RenderState blendState = RenderState::opaque();
        blendState.blend = true;
        blendState.blendSrc = RenderState::BlendFactor::SrcAlpha;
        blendState.blendDst = RenderState::BlendFactor::OneMinusSrcAlpha;
        blendState.depthWrite = false;
        blendState.depthTest = false;
        blendState.apply();

        m_shader.bind();
        ++m_runtimeStats.shaderBinds;
        m_shader.setUniform("uViewport", UniformVec2{ vpW, vpH });
        m_shader.setUniform("uAtlas", 0);

        m_vao.bind();
        ++m_runtimeStats.vaoBinds;

        std::vector<GlyphVertex> quadVerts;
        quadVerts.reserve(1024);

        for (const TextItem& item : m_items)
        {
            const Font* font = m_fontCache->get(item.font);
            if (!font)
            {
                std::fprintf(
                    stderr,
                    "[TextPass] execute: font handle %llu not found, skipping text item\n",
                    static_cast<unsigned long long>(item.font.id));
                continue;
            }

            const Texture2D* atlas = resources.textures2D.get(font->atlas);
            if (!atlas)
            {
                std::fprintf(
                    stderr,
                    "[TextPass] execute: atlas handle %llu not found for text item\n",
                    static_cast<unsigned long long>(font->atlas.id));
                continue;
            }

            quadVerts.clear();

            const float scale = (item.style.sizePx > 0.0f && font->metrics.ascentPx > 0.0f)
                                    ? item.style.sizePx / font->metrics.ascentPx
                                    : 1.0f;

            if (scale <= 0.0f)
            {
                std::fprintf(stderr, "[TextPass] execute: invalid text size %f or font metrics\n", item.style.sizePx);
                continue;
            }

            if (item.preShaped)
            {
                for (const GlyphPlacement& p : item.glyphs)
                {
                    const Glyph* g = font->glyph(p.codepoint);
                    if (!g)
                    {
                        std::fprintf(stderr, "[TextPass] execute: glyph U+%04X not found in font\n", p.codepoint);
                        continue;
                    }
                    appendGlyphQuad(quadVerts, *g, item.x + p.x * scale, item.y + p.y * scale, scale);
                }
            }
            else
            {
                float penX = item.x;
                float penY = item.y;
                std::uint32_t prev = 0;
                const float lineAdvancePx =
                    std::max(font->metrics.ascentPx - font->metrics.descentPx + font->metrics.lineGapPx, 1.0f) * scale;
                const auto* s = reinterpret_cast<const unsigned char*>(item.utf8.data());
                const auto* end = s + item.utf8.size();
                // Walk the UTF-8 byte stream directly so TextPass does not depend on a shaping library
                while (s < end)
                {
                    std::uint32_t cp = 0;
                    if ((*s & 0x80u) == 0u)
                    {
                        // ASCII fast path: one byte, one code point
                        cp = *s++;
                    }
                    else if ((*s & 0xE0u) == 0xC0u && s + 1 < end)
                    {
                        // 2-byte UTF-8 sequence
                        cp = ((*s & 0x1Fu) << 6u) | (s[1] & 0x3Fu);
                        s += 2;
                    }
                    else if ((*s & 0xF0u) == 0xE0u && s + 2 < end)
                    {
                        // 3-byte UTF-8 sequence
                        cp = ((*s & 0x0Fu) << 12u) | ((s[1] & 0x3Fu) << 6u) | (s[2] & 0x3Fu);
                        s += 3;
                    }
                    else if ((*s & 0xF8u) == 0xF0u && s + 3 < end)
                    {
                        // 4-byte UTF-8 sequence
                        cp = ((*s & 0x07u) << 18u) | ((s[1] & 0x3Fu) << 12u) | ((s[2] & 0x3Fu) << 6u) | (s[3] & 0x3Fu);
                        s += 4;
                    }
                    else
                    {
                        ++s;
                        continue;
                    }

                    if (cp == '\r')
                    {
                        // Ignore carriage return so Windows line endings behave like Unix ones
                        prev = 0;
                        continue;
                    }

                    if (cp == '\n')
                    {
                        // Move the baseline to the next line using the font line metrics
                        penX = item.x;
                        penY += lineAdvancePx;
                        prev = 0;
                        continue;
                    }

                    if (prev != 0)
                    {
                        penX += font->kerningPx(prev, cp) * scale;
                    }

                    const Glyph* g = font->glyph(cp);
                    if (g)
                    {
                        appendGlyphQuad(quadVerts, *g, penX, penY, scale);
                        penX += (g->advanceXPx + item.style.letterSpacingPx) * scale;
                    }

                    prev = cp;
                }
            }

            if (quadVerts.empty())
            {
                continue;
            }

            atlas->bind(0);
            ++m_runtimeStats.textureBinds;
            m_shader.setUniform(
                "uColor",
                UniformVec4{ item.style.color[0], item.style.color[1], item.style.color[2], item.style.alpha });

            m_vbo.bind();
            ++m_runtimeStats.vboBinds;
            m_vbo.setData(
                quadVerts.data(),
                static_cast<std::ptrdiff_t>(quadVerts.size() * sizeof(GlyphVertex)),
                Buffer::Usage::StreamDraw);

            ++m_runtimeStats.drawCalls;
            gl.glDrawArrays(TRIANGLES, 0, static_cast<GLsizei>(quadVerts.size()));

            m_vbo.unbind();
            Texture2D::unbind(0);
        }

        m_vao.unbind();
        m_shader.unbind();
    }

    void TextPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
