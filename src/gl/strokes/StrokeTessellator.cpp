#include "nfx/graphics/gl/strokes/StrokeTessellator.h"

namespace nfx::graphics::gl
{
    bool StrokeTessellator::isValidStrokeStyle(const StrokeStyle& style) const noexcept
    {
        if (style.width < 1.0f)
        {
            return false;
        }
        if (style.miterLimit < 1.0f)
        {
            return false;
        }
        return true;
    }

    StrokeMesh2D StrokeTessellator::tessellate(const StrokePolyline2D& polyline, const StrokeStyle& style) const
    {
        StrokeMesh2D mesh;
        if (!isValidStrokeStyle(style))
        {
            return mesh;
        }
        if (polyline.xy == nullptr)
        {
            return mesh;
        }
        if (polyline.pointCount < 2)
        {
            return mesh;
        }
        return mesh;
    }
} // namespace nfx::graphics::gl
