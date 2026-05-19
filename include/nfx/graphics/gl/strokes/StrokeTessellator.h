#pragma once

/**
 * \file StrokeTessellator.h
 * \brief Declares CPU-side stroke tessellation helpers.
 */

#include "StrokeTypes.h"

namespace nfx::graphics::gl
{
    /**
     * \brief CPU-side stroke tessellator.
     */
    class StrokeTessellator final
    {
    public:
        /**
         * \brief Returns whether the given stroke style is valid.
         * \param style Stroke style to validate.
         * \return True when the style is structurally valid, false otherwise.
         */
        [[nodiscard]] bool isValidStrokeStyle(const StrokeStyle& style) const noexcept;

        /**
         * \brief Tessellates one polyline stroke into a CPU-side triangle mesh.
         * \param polyline Polyline input.
         * \param style Stroke style.
         * \return Tessellated mesh. May be empty on invalid input.
         */
        [[nodiscard]] StrokeMesh2D tessellate(const StrokePolyline2D& polyline, const StrokeStyle& style) const;
    };
} // namespace nfx::graphics::gl
