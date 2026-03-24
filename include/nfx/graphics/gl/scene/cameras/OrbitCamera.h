#pragma once

/**
 * \file OrbitCamera.h
 * \brief Declares a quaternion-based orbit camera used to generate GPU-ready camera data.
 */

#include "nfx/graphics/math/Quat.h"
#include "Camera.h"

#include <algorithm>
#include <cassert>
#include <numbers>

namespace nfx::graphics::gl
{
    /**
     * \brief Quaternion-based orbit camera with Y-up orientation and no gimbal lock.
     *
     * Controls:
     * - orbit(dx, dy): rotate around the target
     * - zoom(delta): proportional zoom
     * - pan(dx, dy): translate the target in the view plane
     */
    struct OrbitCamera
    {
        float azimuth = 0.f;                               ///< Rotation around the global Y axis, in radians
        float elevation = std::numbers::pi_v<float> / 6.f; ///< Rotation above the horizon, in radians
        float distance = 8.f;                              ///< Distance from the eye position to the target
        float target[3] = { 0.f, 0.f, 0.f };               ///< Camera orbit target in world space
        float orbitSpeed = 0.004f;                         ///< Mouse-to-angle scale applied by orbit()
        float panSpeed = 0.001f;                           ///< Mouse-to-translation scale applied by pan()
        float zoomSpeed = 0.1f;                            ///< Scroll-to-distance scale applied by zoom()
        static constexpr float DistanceMin = 0.1f;         ///< Minimum allowed orbit distance
        static constexpr float DistanceMax = 10000.f;      ///< Maximum allowed orbit distance

        /**
         * \brief Orbits the camera around its target.
         * \param dx Horizontal input delta.
         * \param dy Vertical input delta.
         */
        void orbit(float dx, float dy)
        {
            azimuth -= dx * orbitSpeed;
            elevation += dy * orbitSpeed;
        }

        /**
         * \brief Applies a proportional zoom, faster when far and more precise when near.
         * \param delta Zoom input delta.
         */
        void zoom(float delta)
        {
            distance = std::clamp(distance - delta * distance * zoomSpeed, DistanceMin, DistanceMax);
        }

        /**
         * \brief Pans the orbit target in the current view plane.
         * \param dx Horizontal input delta.
         * \param dy Vertical input delta.
         */
        void pan(float dx, float dy)
        {
            const State s = state();
            const auto& orient = s.orient;
            math::Vec3 right{};
            math::Vec3 upVec{};
            const float rightLocal[3] = { 1.f, 0.f, 0.f };
            const float upLocal[3] = { 0.f, 1.f, 0.f };
            math::quatRotate(orient, rightLocal, right.data());
            math::quatRotate(orient, upLocal, upVec.data());

            const float speed = distance * panSpeed;
            target[0] -= (right.x * dx - upVec.x * dy) * speed;
            target[1] -= (right.y * dx - upVec.y * dy) * speed;
            target[2] -= (right.z * dx - upVec.z * dy) * speed;
        }

        /**
         * \brief Builds the GPU-ready camera payload from the current orbit camera state.
         * \param fovY Vertical field of view in radians.
         * \param aspect Viewport aspect ratio.
         * \param zNear Near clipping plane.
         * \param zFar Far clipping plane.
         */
        [[nodiscard]] Camera::GpuData toGpuData(float fovY, float aspect, float zNear = 0.1f, float zFar = 500.f) const
        {
            assert(aspect > 0.f && "OrbitCamera::toGpuData(): aspect must be > 0");
            assert(zNear > 0.f && "OrbitCamera::toGpuData(): zNear must be > 0");
            assert(zFar > zNear && "OrbitCamera::toGpuData(): zFar must be > zNear");

            const float safeAspect = (aspect > 0.f) ? aspect : 1.f;
            const float safeNear = (zNear > 0.f) ? zNear : 0.1f;
            const float safeFar = (zFar > safeNear) ? zFar : (safeNear + 1.f);

            const State s = state();
            const math::Vec3 eye{ s.eye[0], s.eye[1], s.eye[2] };
            const math::Vec3 up{ s.up[0], s.up[1], s.up[2] };

            const math::Vec3 targetPos{ target[0], target[1], target[2] };
            const math::Vec3 fwd = math::vec3normalize(math::vec3sub(targetPos, eye));

            math::Mat4 view, proj, viewProj;
            math::mat4LookAt(view, eye.x, eye.y, eye.z, targetPos.x, targetPos.y, targetPos.z, up.x, up.y, up.z);
            math::mat4Perspective(proj, fovY, safeAspect, safeNear, safeFar);
            math::mat4Mul(viewProj, proj, view);

            return Camera::toGpuData(view, proj, viewProj, eye, fwd);
        }

    private:
        /**
         * \brief Internal camera state derived from the current orbit parameters.
         */
        struct State
        {
            math::Quat orient;
            float eye[3];
            float up[3];
        };

        /**
         * \brief Computes the current orientation, eye position and up vector.
         */
        [[nodiscard]] State state() const
        {
            const math::Quat az = math::quatAngleAxis(azimuth, 0.f, 1.f, 0.f);
            const math::Quat el = math::quatAngleAxis(-elevation, 1.f, 0.f, 0.f);
            const math::Quat orient = math::quatNormalize(math::quatMul(az, el));

            const float offsetLocal[3] = { 0.f, 0.f, distance };
            float offset[3];
            math::quatRotate(orient, offsetLocal, offset);

            const float upLocal[3] = { 0.f, 1.f, 0.f };
            float up[3];
            math::quatRotate(orient, upLocal, up);

            return { orient,
                     { target[0] + offset[0], target[1] + offset[1], target[2] + offset[2] },
                     { up[0], up[1], up[2] } };
        }
    };
} // namespace nfx::graphics::gl
