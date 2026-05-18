#pragma once

/**
 * \file ViewportRect.h
 * \brief Declares a pixel-space viewport rectangle used by rendering passes.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Pixel-space viewport rectangle.
     *
     * Coordinates are window- or target-relative and follow the OpenGL viewport convention.
     * A viewport is considered valid when `width >= 1` and `height >= 1`.
     */
    struct ViewportRect
    {
        int x = 0;      ///< Left coordinate in pixels
        int y = 0;      ///< Bottom coordinate in pixels
        int width = 1;  ///< Width in pixels
        int height = 1; ///< Height in pixels

        /**
         * \brief Returns whether the viewport dimensions are valid for rendering.
         */
        [[nodiscard]] bool isValid() const noexcept { return width >= 1 && height >= 1; }

        /**
         * \brief Returns the exclusive right edge in pixels.
         */
        [[nodiscard]] int right() const noexcept { return x + width; }

        /**
         * \brief Returns the exclusive top edge in pixels.
         */
        [[nodiscard]] int top() const noexcept { return y + height; }
    };
} // namespace nfx::graphics::gl
