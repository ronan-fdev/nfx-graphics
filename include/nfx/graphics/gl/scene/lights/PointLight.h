#pragma once

/**
 * \file PointLight.h
 * \brief Declares the CPU-side descriptor for a punctual point light.
 */

#include "PunctualLight.h"

#include "nfx/graphics/math/Vec3.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Point light descriptor storing position, color and attenuation parameters.
     */
    struct PointLight
    {
        float position[3] = {};             ///< World-space light position.
        float color[3] = { 1.f, 1.f, 1.f }; ///< Linear RGB light color.
        float intensity = 1.f;              ///< Scalar intensity multiplier.
        float radius = 0.f;                 ///< Attenuation cutoff radius. 0 = infinite range.
        float shadowFarPlane = 0.f;         ///< Shadow far plane for \c PointShadowPass. 0 = not a shadow caster.
        float shadowNearPlane = 0.05f;      ///< Shadow near plane for \c PointShadowPass.

        /**
         * \brief Creates a point light from raw scalar components.
         * \param px,py,pz       World-space light position.
         * \param r,g,b          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         * \param shadowNearPlane Shadow near plane used for the shadow cube map projection.
         */
        [[nodiscard]] static PointLight create(
            float px,
            float py,
            float pz,
            float r,
            float g,
            float b,
            float intensity,
            float radius = 0.f,
            float shadowFarPlane = 0.f,
            float shadowNearPlane = 0.05f) noexcept
        {
            PointLight l;
            l.position[0] = px;
            l.position[1] = py;
            l.position[2] = pz;
            l.color[0] = r;
            l.color[1] = g;
            l.color[2] = b;
            l.intensity = intensity;
            l.radius = radius;
            l.shadowFarPlane = shadowFarPlane;
            l.shadowNearPlane = shadowNearPlane;
            return l;
        }

        /**
         * \brief Creates a point light from typed vector components.
         * \param position       World-space light position.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         * \param shadowNearPlane Shadow near plane used for the shadow cube map projection.
         */
        [[nodiscard]] static PointLight create(
            const math::Vec3& position,
            const math::Vec3& color,
            float intensity,
            float radius = 0.f,
            float shadowFarPlane = 0.f,
            float shadowNearPlane = 0.05f) noexcept
        {
            return create(
                position.x,
                position.y,
                position.z,
                color.x,
                color.y,
                color.z,
                intensity,
                radius,
                shadowFarPlane,
                shadowNearPlane);
        }

        /**
         * \brief Packs the light parameters into their GPU payload representation.
         */
        [[nodiscard]] PunctualLight::GpuData toGpuData() const noexcept
        {
            return toGpuData(position, color, intensity, radius, shadowFarPlane, shadowNearPlane);
        }

        /**
         * \brief Packs point light parameters into their GPU payload representation.
         * \param position       World-space light position.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         * \param shadowNearPlane Shadow near plane.
         */
        [[nodiscard]] static PunctualLight::GpuData toGpuData(
            const float position[3],
            const float color[3],
            float intensity,
            float radius = 0.f,
            float shadowFarPlane = 0.f,
            float shadowNearPlane = 0.05f) noexcept
        {
            constexpr float kPointType = static_cast<float>(static_cast<int>(PunctualLight::Type::Point));
            return PunctualLight::GpuData{ { position[0], position[1], position[2], radius },
                                           { 0.f, 0.f, 0.f, kPointType },
                                           { color[0], color[1], color[2], intensity },
                                           { 1.f, 1.f, shadowFarPlane, shadowNearPlane } };
        }

        /**
         * \brief Packs point light parameters into their GPU payload representation.
         * \param position       World-space light position.
         * \param color          Linear RGB light color.
         * \param intensity      Scalar intensity multiplier.
         * \param radius         Attenuation cutoff radius. 0 = infinite range.
         * \param shadowFarPlane Shadow far plane. 0 = not a shadow caster.
         * \param shadowNearPlane Shadow near plane.
         */
        [[nodiscard]] static PunctualLight::GpuData toGpuData(
            const math::Vec3& position,
            const math::Vec3& color,
            float intensity,
            float radius = 0.f,
            float shadowFarPlane = 0.f,
            float shadowNearPlane = 0.05f) noexcept
        {
            return toGpuData(position.data(), color.data(), intensity, radius, shadowFarPlane, shadowNearPlane);
        }
    };
} // namespace nfx::graphics::gl
