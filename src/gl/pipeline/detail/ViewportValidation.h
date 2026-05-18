#pragma once

#include "nfx/graphics/gl/pipeline/raster/ViewportRect.h"

namespace nfx::graphics::gl::detail
{
    [[nodiscard]] inline bool isViewportInsideSurface(
        const ViewportRect& viewport, int surfaceWidth, int surfaceHeight) noexcept
    {
        return surfaceWidth >= 1 && surfaceHeight >= 1 && viewport.isValid() && viewport.x >= 0 && viewport.y >= 0 &&
               viewport.right() <= surfaceWidth && viewport.top() <= surfaceHeight;
    }
} // namespace nfx::graphics::gl::detail
