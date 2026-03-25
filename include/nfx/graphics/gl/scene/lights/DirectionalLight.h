#pragma once

#include "nfx/graphics/math/Vec3.h"

/**
 * \file DirectionalLight.h
 * \brief Declares the directional light descriptor and its GPU upload layout.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Directional light descriptor storing color and intensity with GPU upload support.
     */
    struct DirectionalLight
    {
        float color[3] = { 1.0f, 1.0f, 1.0f }; ///< Directional light color
        float intensity = 1.0f;                ///< Scalar intensity multiplier

        /**
         * \brief std140-compatible directional light payload uploaded to the directional light uniform buffer.
         */
        struct GpuData
        {
            float direction[4];      // xyz = normalized world direction, w = unused
            float colorIntensity[4]; // rgb = color                     , w = intensity
        };

        /**
         * \brief Packs the light parameters into their GPU payload representation.
         * \param direction Normalized world-space light direction.
         */
        [[nodiscard]] GpuData toGpuData(const float direction[3]) const noexcept
        {
            return { { direction[0], direction[1], direction[2], 0.0f }, { color[0], color[1], color[2], intensity } };
        }

        /**
         * \brief Packs the light parameters into their GPU payload representation.
         * \param direction Normalized world-space light direction.
         */
        [[nodiscard]] GpuData toGpuData(const math::Vec3& direction) const noexcept
        {
            return { { direction.x, direction.y, direction.z, 0.0f }, { color[0], color[1], color[2], intensity } };
        }
    };
} // namespace nfx::graphics::gl
