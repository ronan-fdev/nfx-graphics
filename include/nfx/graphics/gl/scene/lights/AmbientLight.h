#pragma once

#include "nfx/graphics/math/Vec3.h"

/**
 * \file AmbientLight.h
 * \brief Declares the ambient light descriptor and its GPU upload layout.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Ambient light descriptor storing color and intensity.
     */
    struct AmbientLight
    {
        float color[3] = { 0.05f, 0.05f, 0.05f }; ///< Ambient light color
        float intensity = 1.0f;                   ///< Scalar intensity multiplier

        /**
         * \brief std140-compatible ambient light payload uploaded to the ambient light uniform buffer.
         */
        struct GpuData
        {
            float colorIntensity[4]; // rgb = color, w = intensity
        };

        /**
         * \brief Packs the ambient light into its GPU payload representation.
         */
        [[nodiscard]] GpuData toGpuData() const noexcept { return toGpuData(color, intensity); }

        /**
         * \brief Packs ambient parameters into their GPU payload representation.
         */
        [[nodiscard]] static GpuData toGpuData(const float color[3], float intensity) noexcept
        {
            return { { color[0], color[1], color[2], intensity } };
        }

        /**
         * \brief Packs ambient parameters into their GPU payload representation.
         */
        [[nodiscard]] static GpuData toGpuData(const math::Vec3& color, float intensity) noexcept
        {
            return { { color.x, color.y, color.z, intensity } };
        }
    };
} // namespace nfx::graphics::gl
