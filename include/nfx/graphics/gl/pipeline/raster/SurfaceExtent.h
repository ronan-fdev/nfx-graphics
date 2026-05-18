#pragma once

/**
 * \file SurfaceExtent.h
 * \brief Declares the surface extent used as render destination size.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Pixel dimensions of the active render destination.
     */
    struct SurfaceExtent
    {
        int width = 0;  ///< Surface width in pixels
        int height = 0; ///< Surface height in pixels

        /**
         * \brief Returns whether both dimensions are strictly positive.
         */
        [[nodiscard]] bool isValid() const noexcept { return width > 0 && height > 0; }
    };
} // namespace nfx::graphics::gl
