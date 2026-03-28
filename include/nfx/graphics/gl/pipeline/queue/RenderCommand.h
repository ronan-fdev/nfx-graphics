#pragma once

/**
 * \file RenderCommand.h
 * \brief Declares the draw command structure submitted to the render queue.
 */

#include "nfx/graphics/gl/resources/Handle.h"
#include "nfx/graphics/gl/pipeline/RenderMode.h"
#include "nfx/graphics/math/Mat4.h"

#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief One queued draw command describing what to render and how to render it.
     */
    struct RenderCommand
    {
        MeshHandle mesh;                         ///< Mesh handle identifying the geometry to draw
        MaterialHandle material;                 ///< Material handle identifying the material to bind
        RenderMode mode = RenderMode::Triangles; ///< Primitive topology used for the draw call
        std::uint64_t sortKey = 0; ///< Sort key. If 0, submit() assigns the material handle id as fallback.
        int instanceCount = 1;     ///< Number of instances to draw. Must be >= 1.
        math::Mat4 transform = math::Mat4::identity(); ///< Model transform matrix
    };
} // namespace nfx::graphics::gl
