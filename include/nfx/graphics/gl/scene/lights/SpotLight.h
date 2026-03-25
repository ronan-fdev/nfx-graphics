#pragma once

/**
 * \file SpotLight.h
 * \brief Declares the CPU-side descriptor for a punctual spot light.
 */

#include "PunctualLight.h"

#include "nfx/graphics/math/Vec3.h"

#include <cmath>

namespace nfx::graphics::gl
{
    /**
     * \brief Spot light descriptor storing position, direction, cone and attenuation parameters.
     */
    struct SpotLight
    {
        float position[3] = {};                  ///< World-space light position.
        float direction[3] = { 0.f, -1.f, 0.f }; ///< World-space cone direction; need not be normalized.
        float color[3] = { 1.f, 1.f, 1.f };      ///< Linear RGB light color.
        float intensity = 1.f;                   ///< Scalar intensity multiplier.
        float innerAngle = 0.f;                  ///< Inner cone half-angle (radians). Full brightness inside.
        float outerAngle = 0.f;                  ///< Outer cone half-angle (radians). Zero beyond this.
        float radius = 0.f;                      ///< Attenuation cutoff radius (world units). 0 = infinite range.
        float shadowFarPlane = 0.f;              ///< Shadow far plane for \c SpotShadowPass. 0 = not a shadow caster.

        /**
         * \brief Creates a spot light from raw scalar components.
         * \param px,py,pz       World-space light position.
         * \param dx,dy,dz       World-space cone direction; need not be normalized.
         * \param r,g,b          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param innerAngle     Inner cone half-angle in radians. Full brightness inside.
         * \param outerAngle     Outer cone half-angle in radians. Zero brightness beyond this.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         */
        [[nodiscard]] static SpotLight create(
            float px,
            float py,
            float pz,
            float dx,
            float dy,
            float dz,
            float r,
            float g,
            float b,
            float intensity,
            float innerAngle,
            float outerAngle,
            float radius = 0.f,
            float shadowFarPlane = 0.f) noexcept
        {
            SpotLight l;
            l.position[0] = px;
            l.position[1] = py;
            l.position[2] = pz;
            l.direction[0] = dx;
            l.direction[1] = dy;
            l.direction[2] = dz;
            l.color[0] = r;
            l.color[1] = g;
            l.color[2] = b;
            l.intensity = intensity;
            l.innerAngle = innerAngle;
            l.outerAngle = outerAngle;
            l.radius = radius;
            l.shadowFarPlane = shadowFarPlane;
            return l;
        }

        /**
         * \brief Creates a spot light from typed vector components.
         * \param position       World-space light position.
         * \param direction      World-space cone direction; need not be normalized.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param innerAngle     Inner cone half-angle in radians. Full brightness inside.
         * \param outerAngle     Outer cone half-angle in radians. Zero brightness beyond this.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         */
        [[nodiscard]] static SpotLight create(
            const math::Vec3& position,
            const math::Vec3& direction,
            const math::Vec3& color,
            float intensity,
            float innerAngle,
            float outerAngle,
            float radius = 0.f,
            float shadowFarPlane = 0.f) noexcept
        {
            return create(
                position.x,
                position.y,
                position.z,
                direction.x,
                direction.y,
                direction.z,
                color.x,
                color.y,
                color.z,
                intensity,
                innerAngle,
                outerAngle,
                radius,
                shadowFarPlane);
        }

        /**
         * \brief Packs the light parameters into their GPU payload representation.
         */
        [[nodiscard]] PunctualLight::GpuData toGpuData() const noexcept
        {
            return toGpuData(position, direction, color, intensity, innerAngle, outerAngle, radius, shadowFarPlane);
        }

        /**
         * \brief Packs spot light parameters into their GPU payload representation.
         *
         * The direction vector is normalized internally; it need not be unit-length on input.
         * \param position       World-space light position.
         * \param direction      World-space cone direction.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param innerAngle     Inner cone half-angle in radians.
         * \param outerAngle     Outer cone half-angle in radians.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         */
        [[nodiscard]] static PunctualLight::GpuData toGpuData(
            const float position[3],
            const float direction[3],
            const float color[3],
            float intensity,
            float innerAngle,
            float outerAngle,
            float radius = 0.f,
            float shadowFarPlane = 0.f) noexcept
        {
            float dx = direction[0], dy = direction[1], dz = direction[2];
            const float dlen = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (dlen > 1e-6f)
            {
                dx /= dlen;
                dy /= dlen;
                dz /= dlen;
            }

            constexpr float kSpotType = static_cast<float>(static_cast<int>(PunctualLight::Type::Spot));
            return PunctualLight::GpuData{ { position[0], position[1], position[2], radius },
                                           { dx, dy, dz, kSpotType },
                                           { color[0], color[1], color[2], intensity },
                                           { std::cos(innerAngle), std::cos(outerAngle), shadowFarPlane, 0.f } };
        }

        /**
         * \brief Packs spot light parameters into their GPU payload representation.
         * \param position       World-space light position.
         * \param direction      World-space cone direction; need not be normalized.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param innerAngle     Inner cone half-angle in radians.
         * \param outerAngle     Outer cone half-angle in radians.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         */
        [[nodiscard]] static PunctualLight::GpuData toGpuData(
            const math::Vec3& position,
            const math::Vec3& direction,
            const math::Vec3& color,
            float intensity,
            float innerAngle,
            float outerAngle,
            float radius = 0.f,
            float shadowFarPlane = 0.f) noexcept
        {
            return toGpuData(
                position.data(),
                direction.data(),
                color.data(),
                intensity,
                innerAngle,
                outerAngle,
                radius,
                shadowFarPlane);
        }
    };
} // namespace nfx::graphics::gl
