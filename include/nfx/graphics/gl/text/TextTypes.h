#pragma once

/**
 * \file TextTypes.h
 * \brief Declares text and glyph runtime types used by TextPass and Font resources.
 */

#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief Global vertical font metrics in pixels.
     */
    struct FontMetrics
    {
        float ascentPx = 0.0f;
        float descentPx = 0.0f;
        float lineGapPx = 0.0f;
    };

    /**
     * \brief One glyph metrics and atlas UV payload.
     */
    struct Glyph
    {
        std::uint32_t codepoint = 0;
        float u0 = 0.0f;
        float v0 = 0.0f;
        float u1 = 0.0f;
        float v1 = 0.0f;
        float widthPx = 0.0f;
        float heightPx = 0.0f;
        float bearingXPx = 0.0f;
        float bearingYPx = 0.0f;
        float advanceXPx = 0.0f;
    };

    /**
     * \brief One positioned glyph instance in screen-space layout.
     */
    struct GlyphPlacement
    {
        std::uint32_t codepoint = 0;
        float x = 0.0f;
        float y = 0.0f;
    };

    /**
     * \brief Per-item text draw style.
     */
    struct TextStyle
    {
        float color[3] = { 1.0f, 1.0f, 1.0f };
        float alpha = 1.0f;
        float sizePx = 16.0f;
        float letterSpacingPx = 0.0f;
        bool depthTest = false;
    };
} // namespace nfx::graphics::gl
