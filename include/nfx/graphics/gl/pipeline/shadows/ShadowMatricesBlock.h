#pragma once

/**
 * \file ShadowMatricesBlock.h
 * \brief CPU layout of the ShadowMatrices UBO (std140, binding = UboBindings::ShadowMatrices).
 *
 * Uploaded once per frame before geometry and consumed by \c blinn_phong.vert and \c blinn_phong.frag.
 * - \c dirLightSpace  : directional shadow projection×view (used when HAS_SHADOW is set on the material).
 * - \c spotLightSpace : up to 4 spot shadow projection×view matrices.
 * - \c shadowInfo     : packed flags/counts (ivec4 std140):
 *     x = spotCount    - number of active spot shadow maps
 *     y = pointCount   - number of active point shadow maps
 *     z = hasDirShadow - 1 if directional shadow map is active
 *     w = reserved     - unused
 *
 * std140 layout (336 bytes):
 *   offset   0 : mat4  dirLightSpace     (64 B)
 *   offset  64 : mat4  spotLightSpace[4] (256 B)
 *   offset 320 : ivec4 shadowInfo        (16 B - replaces spotCount + _pad[3])
 */

namespace nfx::graphics::gl
{
    struct ShadowMatricesBlockData
    {
        // Column-major identity as default so a zero-upload is never invalid
        // clang-format off
        float dirLightSpace[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };

        // Default to identity matrices so inactive spot entries remain harmless if sampled
        float spotLightSpace[4][16] = {
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            },
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            },
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            },
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            }
        };
        // clang-format on

        // x=spotCount, y=pointCount, z=hasDirShadow, w=unused
        int shadowInfo[4] = {};
    };
    static_assert(sizeof(ShadowMatricesBlockData) == 336, "ShadowMatricesBlock must be 336 bytes (std140)");
} // namespace nfx::graphics::gl
