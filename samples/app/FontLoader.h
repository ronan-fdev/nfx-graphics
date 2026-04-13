#pragma once

/**
 * \file FontLoader.h
 * \brief Declares helpers that build runtime Font resources from TTF data.
 */

#include <nfx/graphics/gl/resources/FontCache.h>
#include <nfx/graphics/gl/resources/Texture2DCache.h>

#include <cstddef>
#include <filesystem>
#include <optional>

namespace nfx::samples
{
    /**
     * \brief Utility class loading TTF fonts into runtime Font resources.
     */
    class FontLoader final
    {
    public:
        /**
         * \brief Loads one runtime font from an embedded TTF resource and stores in font cache.
         * \param textureCache Texture cache used to upload glyph atlas.
         * \param fontCache Font cache used to store runtime font resource.
         * \param resourceName Embedded font resource name (e.g. "fonts/JetBrainsMono").
         * \param pixelHeight Target baked glyph height in pixels.
         * \param firstCodepoint First codepoint included in the bake range.
         * \param lastCodepoint Last codepoint included in the bake range.
         * \return Valid FontHandle on success, invalid handle on failure.
         */
        [[nodiscard]] static graphics::gl::FontHandle fromEmbedded(
            graphics::gl::Texture2DCache& textureCache,
            graphics::gl::FontCache& fontCache,
            const char* resourceName,
            float pixelHeight = 32.0f,
            std::uint32_t firstCodepoint = 32u,
            std::uint32_t lastCodepoint = 126u);

    private:
        FontLoader() = delete;

        /**
         * \brief Loads one runtime font from TTF source bytes.
         * \param textureCache Texture cache used to upload glyph atlas.
         * \param ttfBytes Pointer to TTF source bytes.
         * \param ttfSize Source byte size.
         * \param pixelHeight Target baked glyph height in pixels.
         * \param firstCodepoint First codepoint included in the bake range.
         * \param lastCodepoint Last codepoint included in the bake range.
         * \return Runtime font resource on success, empty on failure.
         */
        [[nodiscard]] static std::optional<graphics::gl::Font> fromSource(
            graphics::gl::Texture2DCache& textureCache,
            const unsigned char* ttfBytes,
            std::size_t ttfSize,
            float pixelHeight,
            std::uint32_t firstCodepoint,
            std::uint32_t lastCodepoint);
    };
} // namespace nfx::samples
