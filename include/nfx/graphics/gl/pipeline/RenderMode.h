#pragma once

/**
 * \file RenderMode.h
 * \brief Declares the primitive topology modes used for draw calls.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    // clang-format off
    /**
     * \brief Primitive topology modes mapped to the corresponding OpenGL draw enums.
     */
    enum class RenderMode : unsigned int
    {
        Points                 = POINTS,
        Lines                  = LINES,
        LineLoop               = LINE_LOOP,
        LineStrip              = LINE_STRIP,
        Triangles              = TRIANGLES,
        TriangleStrip          = TRIANGLE_STRIP,
        TriangleFan            = TRIANGLE_FAN,
        LinesAdjacency         = LINES_ADJACENCY,
        LineStripAdjacency     = LINE_STRIP_ADJACENCY,
        TrianglesAdjacency     = TRIANGLES_ADJACENCY,
        TriangleStripAdjacency = TRIANGLE_STRIP_ADJACENCY,
        Patches                = PATCHES
    };
    // clang-format on
} // namespace nfx::graphics::gl
