#pragma once

/**
 * \file ScissorRect.h
 * \brief Declares a pixel-space scissor rectangle used for GL scissor testing.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Pixel-space scissor rectangle.
     */
    struct ScissorRect
    {
        int x = 0;      ///< Left coordinate in pixels
        int y = 0;      ///< Bottom coordinate in pixels
        int width = 1;  ///< Width in pixels
        int height = 1; ///< Height in pixels

        /**
         * \brief Returns whether dimensions are valid for scissor testing.
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
