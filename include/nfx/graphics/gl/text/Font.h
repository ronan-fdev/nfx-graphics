#pragma once

/**
 * \file Font.h
 * \brief Declares the runtime font resource used by TextPass.
 */

#include "nfx/graphics/gl/resources/Handle.h"
#include "nfx/graphics/gl/text/TextTypes.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace nfx::graphics::gl
{
    /**
     * \brief Runtime font resource containing one atlas and glyph metadata.
     */
    struct Font
    {
        Texture2DHandle atlas;
        FontMetrics metrics;
        std::unordered_map<std::uint32_t, Glyph> glyphs;
        std::unordered_map<std::uint64_t, float> kerning;

        /**
         * \brief Returns glyph metadata for one codepoint.
         * \param codepoint Unicode codepoint.
         * \return Pointer to glyph metadata, or nullptr when missing.
         */
        [[nodiscard]] const Glyph* glyph(std::uint32_t codepoint) const noexcept
        {
            const auto it = glyphs.find(codepoint);
            return it != glyphs.end() ? &it->second : nullptr;
        }

        /**
         * \brief Returns kerning adjustment for a glyph pair.
         * \param left Left codepoint.
         * \param right Right codepoint.
         * \return Kerning in pixels. Returns 0 when not present.
         */
        [[nodiscard]] float kerningPx(std::uint32_t left, std::uint32_t right) const noexcept
        {
            const std::uint64_t key = (static_cast<std::uint64_t>(left) << 32u) | static_cast<std::uint64_t>(right);
            const auto it = kerning.find(key);
            return it != kerning.end() ? it->second : 0.0f;
        }
    };
} // namespace nfx::graphics::gl
