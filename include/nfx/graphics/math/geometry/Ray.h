#pragma once

/**
 * \file Ray.h
 * \brief Declares ray types and intersection helpers used for picking and geometric queries.
 */

#include "Bounds.h"
#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Vec3.h"

#include <array>
#include <optional>

namespace nfx::graphics::math
{
    /**
     * \brief Ray represented by an origin and direction.
     */
    struct Ray
    {
        float origin[3] = { 0.0f };
        float direction[3] = { 0.0f };

        /**
         * \brief Evaluates a point along the ray.
         * \param t Distance along the ray direction.
         * \return Point on the ray at distance `t`.
         */
        [[nodiscard]] std::array<float, 3> at(float t) const
        {
            return { origin[0] + t * direction[0], origin[1] + t * direction[1], origin[2] + t * direction[2] };
        }

        /**
         * \brief Result of an intersection query.
         */
        struct Hit
        {
            float distance = 0.0f;
            float point[3] = { 0.0f };
            float normal[3] = { 0.0f };
        };
    };

    /**
     * \brief Intersects a ray with an axis-aligned bounding box.
     * \param ray Input ray.
     * \param aabb Axis-aligned bounding box to test.
     * \return Intersection result when the ray hits the box, `std::nullopt` otherwise.
     */
    [[nodiscard]] std::optional<Ray::Hit> intersect(const Ray& ray, const Bounds::AABB& aabb);

    /**
     * \brief Intersects a ray with a sphere.
     * \param ray Input ray.
     * \param sphere Sphere to test.
     * \return Intersection result when the ray hits the sphere, `std::nullopt` otherwise.
     */
    [[nodiscard]] std::optional<Ray::Hit> intersect(const Ray& ray, const Bounds::Sphere& sphere);

    /**
     * \brief Intersects a ray with a triangle.
     * \param ray Input ray.
     * \param v0 First triangle vertex.
     * \param v1 Second triangle vertex.
     * \param v2 Third triangle vertex.
     * \return Intersection result when the ray hits the triangle, `std::nullopt` otherwise.
     */
    [[nodiscard]] std::optional<Ray::Hit> intersect(const Ray& ray, const float* v0, const float* v1, const float* v2);

    /**
     * \brief Intersects a ray with a triangle described by Vec3 vertices.
     * \param ray Input ray.
     * \param v0 First triangle vertex.
     * \param v1 Second triangle vertex.
     * \param v2 Third triangle vertex.
     * \return Intersection result when the ray hits the triangle, `std::nullopt` otherwise.
     */
    [[nodiscard]] std::optional<Ray::Hit> intersect(const Ray& ray, const Vec3& v0, const Vec3& v1, const Vec3& v2);

    /**
     * \brief Builds a world-space ray from screen coordinates using a perspective projection.
     * \param screenPos Screen-space position in pixels.
     * \param viewportSize Viewport size in pixels.
     * \param viewMatrix View matrix.
     * \param projectionMatrix Projection matrix.
     * \return World-space picking ray.
     */
    [[nodiscard]] Ray screenToWorldRay(
        const float* screenPos, const float* viewportSize, const float* viewMatrix, const float* projectionMatrix);

    /**
     * \brief Builds a world-space ray from screen coordinates using Mat4 inputs.
     * \param screenPos Screen-space position in pixels.
     * \param viewportSize Viewport size in pixels.
     * \param viewMatrix View matrix.
     * \param projectionMatrix Projection matrix.
     * \return World-space picking ray.
     */
    [[nodiscard]] Ray screenToWorldRay(
        const float* screenPos, const float* viewportSize, const Mat4& viewMatrix, const Mat4& projectionMatrix);

    /**
     * \brief Builds a world-space ray from screen coordinates using either perspective or orthographic projection.
     * \param screenPos Screen-space position in pixels.
     * \param viewportSize Viewport size in pixels.
     * \param viewMatrix View matrix.
     * \param projectionMatrix Projection matrix.
     * \param isOrthographic Whether the projection is orthographic.
     * \return World-space picking ray.
     */
    [[nodiscard]] Ray screenToWorldRay(
        const float* screenPos,
        const float* viewportSize,
        const float* viewMatrix,
        const float* projectionMatrix,
        bool isOrthographic);

    /**
     * \brief Builds a world-space ray from screen coordinates using Mat4 inputs.
     * \param screenPos Screen-space position in pixels.
     * \param viewportSize Viewport size in pixels.
     * \param viewMatrix View matrix.
     * \param projectionMatrix Projection matrix.
     * \param isOrthographic Whether the projection is orthographic.
     * \return World-space picking ray.
     */
    [[nodiscard]] Ray screenToWorldRay(
        const float* screenPos,
        const float* viewportSize,
        const Mat4& viewMatrix,
        const Mat4& projectionMatrix,
        bool isOrthographic);
} // namespace nfx::graphics::math
