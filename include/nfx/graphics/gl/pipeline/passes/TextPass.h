#pragma once

/**
 * \file TextPass.h
 * \brief Declares the overlay pass used to render text items.
 */

#include "nfx/graphics/gl/core/buffers/Buffer.h"
#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/resources/FontCache.h"
#include "nfx/graphics/gl/text/Font.h"
#include "nfx/graphics/gl/text/TextTypes.h"
#include "RenderPass.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Overlay pass owning screen-space text items.
     */
    class TextPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures used by this pass.
         * \param color Target color texture.
         * \param depth Optional target depth texture.
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Binds the font cache used to resolve FontHandle during rendering.
         * \param cache Font cache owning the Font resources used by text items.
         */
        void setFontCache(FontCache& cache) noexcept { m_fontCache = &cache; }

        /**
         * \brief Adds one UTF-8 text item.
         * \param font Font handle used to resolve glyph metadata.
         * \param utf8 UTF-8 text.
         * \param x Baseline x in pixels.
         * \param y Baseline y in pixels.
         * \param style Text style.
         * \return Handle of the created text item, or invalid handle on failure.
         */
        TextItemHandle addTextUtf8(
            FontHandle font, std::string_view utf8, float x, float y, const TextStyle& style = {});

        /**
         * \brief Adds one pre-shaped glyph run item.
         * \param font Font handle used to resolve glyph metadata.
         * \param glyphs Positioned glyph placements.
         * \param x Baseline x offset in pixels.
         * \param y Baseline y offset in pixels.
         * \param style Text style.
         * \return Handle of the created text item, or invalid handle on failure.
         */
        TextItemHandle addGlyphRun(
            FontHandle font, const std::vector<GlyphPlacement>& glyphs, float x, float y, const TextStyle& style = {});

        /**
         * \brief Updates one text item from UTF-8 content.
         * \param handle Text item handle.
         * \param utf8 New UTF-8 text.
         */
        void updateText(TextItemHandle handle, std::string_view utf8);

        /**
         * \brief Updates one text item from pre-shaped glyph placements.
         * \param handle Text item handle.
         * \param glyphs New glyph placements.
         */
        void updateText(TextItemHandle handle, const std::vector<GlyphPlacement>& glyphs);

        /**
         * \brief Removes one text item.
         * \param handle Text item handle.
         */
        void removeText(TextItemHandle handle);

        /**
         * \brief Removes all text items.
         */
        void clearTexts();

        /**
         * \brief Returns number of items currently tracked by the pass.
         * \return Number of text items.
         */
        [[nodiscard]] std::size_t textCount() const noexcept { return m_items.size(); }

    private:
        explicit TextPass(std::string name = "TextPass")
            : RenderPass{ std::move(name) }
        {}

        bool initialize() override;
        void begin() override;
        void execute(RenderResources& resources) override;
        void end() override;

    private:
        struct TextItem
        {
            TextItemHandle handle;
            FontHandle font;
            std::string utf8;
            std::vector<GlyphPlacement> glyphs;
            bool preShaped = false;
            float x = 0.0f;
            float y = 0.0f;
            TextStyle style;
        };

        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;

        FontCache* m_fontCache = nullptr;

        ShaderProgram m_shader;
        Buffer m_vbo{ Buffer::Target::VertexAttributesArray };
        VertexArray m_vao;

        std::vector<TextItem> m_items;
        std::unordered_map<std::uint64_t, std::size_t> m_itemIndex;
        std::uint64_t m_nextTextId = 1;
    };
} // namespace nfx::graphics::gl
