#pragma once

/**
 * \file PunctualLight.h
 * \brief Declares shared punctual light GPU payload types used by point/spot light descriptors.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Shared punctual light contract for packed GPU payloads.
     */
    struct PunctualLight
    {
        /**
         * \brief Encodes the punctual light kind packed into \c GpuData::direction.w.
         */
        enum class Type : int
        {
            Point = 0,
            Spot
        };

        static constexpr int MaxLights = 64; ///< Maximum number of lights packed into one GpuBlock.

        /**
         * \brief std430-friendly packed punctual light payload.
         */
        struct GpuData
        {
            float position[4];       // xyz = world pos, w = radius
            float direction[4];      // xyz = direction, w = type (0=point, 1=spot)
            float colorIntensity[4]; // rgb = color    , w = intensity
            float params[4];         // x = cos(inner) for spot / 1 for point,
                                     // y = cos(outer) for spot / 1 for point,
                                     // z = shadow far plane, w = shadow near plane
        };

        /**
         * \brief std430-friendly array block of packed punctual lights.
         */
        struct GpuBlock
        {
            int count = 0;    ///< Number of active lights in the block.
            int _pad[3] = {}; ///< Explicit padding to keep \c lights 16-byte aligned (std140/std430 compatible).
            GpuData lights[MaxLights] = {}; ///< Packed light payloads.
        };
    };
} // namespace nfx::graphics::gl
