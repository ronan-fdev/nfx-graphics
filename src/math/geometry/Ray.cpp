#include "nfx/graphics/math/geometry/Ray.h"

#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Vec3.h"

namespace nfx::graphics::math
{
    std::optional<Ray::Hit> intersect(const Ray& ray, const Bounds::AABB& aabb)
    {
        // Slab method
        float invDir[3] = { 1.f / ray.direction[0], 1.f / ray.direction[1], 1.f / ray.direction[2] };

        float t0[3] = { (aabb.min[0] - ray.origin[0]) * invDir[0],
                        (aabb.min[1] - ray.origin[1]) * invDir[1],
                        (aabb.min[2] - ray.origin[2]) * invDir[2] };
        float t1[3] = { (aabb.max[0] - ray.origin[0]) * invDir[0],
                        (aabb.max[1] - ray.origin[1]) * invDir[1],
                        (aabb.max[2] - ray.origin[2]) * invDir[2] };

        float tNear = std::fmax(std::fmax(std::fmin(t0[0], t1[0]), std::fmin(t0[1], t1[1])), std::fmin(t0[2], t1[2]));
        float tFar = std::fmin(std::fmin(std::fmax(t0[0], t1[0]), std::fmax(t0[1], t1[1])), std::fmax(t0[2], t1[2]));

        if (tNear > tFar || tFar < 0.f)
        {
            return std::nullopt;
        }

        float t = tNear >= 0.f ? tNear : tFar;

        Ray::Hit hit;
        hit.distance = t;
        auto p = ray.at(t);
        hit.point[0] = p[0];
        hit.point[1] = p[1];
        hit.point[2] = p[2];

        // Normal: dominant axis of (point - center) / extents
        auto c = aabb.center();
        auto e = aabb.extents();
        constexpr float bias = 1.0001f;
        float nx = static_cast<float>(static_cast<int>((hit.point[0] - c[0]) / e[0] * bias));
        float ny = static_cast<float>(static_cast<int>((hit.point[1] - c[1]) / e[1] * bias));
        float nz = static_cast<float>(static_cast<int>((hit.point[2] - c[2]) / e[2] * bias));
        float n[3] = { nx, ny, nz };
        auto norm = vec3normalize(n);
        hit.normal[0] = norm[0];
        hit.normal[1] = norm[1];
        hit.normal[2] = norm[2];

        return hit;
    }

    std::optional<Ray::Hit> intersect(const Ray& ray, const Bounds::Sphere& sphere)
    {
        auto oc = vec3sub(ray.origin, sphere.center);
        float b = vec3dot(oc.data(), ray.direction);
        float c = vec3dot(oc.data(), oc.data()) - sphere.radius * sphere.radius;
        float disc = b * b - c;

        if (disc < 0.f)
        {
            return std::nullopt;
        }

        float t = -b - std::sqrt(disc);
        if (t < 0.f)
        {
            t = -b + std::sqrt(disc);
            if (t < 0.f)
            {
                return std::nullopt;
            }
        }

        Ray::Hit hit;
        hit.distance = t;
        auto p = ray.at(t);
        hit.point[0] = p[0];
        hit.point[1] = p[1];
        hit.point[2] = p[2];

        float diff[3] = { hit.point[0] - sphere.center[0],
                          hit.point[1] - sphere.center[1],
                          hit.point[2] - sphere.center[2] };
        auto norm = vec3normalize(diff);
        hit.normal[0] = norm[0];
        hit.normal[1] = norm[1];
        hit.normal[2] = norm[2];

        return hit;
    }

    std::optional<Ray::Hit> intersect(const Ray& ray, const float* v0, const float* v1, const float* v2)
    {
        // Möller-Trumbore
        constexpr float EPSILON = 1e-7f;

        float edge1[3] = { v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2] };
        float edge2[3] = { v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2] };
        auto h = vec3cross(ray.direction, edge2);
        float a = vec3dot(edge1, h.data());

        if (a > -EPSILON && a < EPSILON)
        {
            return std::nullopt;
        }

        float f = 1.f / a;
        float s[3] = { ray.origin[0] - v0[0], ray.origin[1] - v0[1], ray.origin[2] - v0[2] };
        float u = f * vec3dot(s, h.data());

        if (u < 0.f || u > 1.f)
        {
            return std::nullopt;
        }

        auto q = vec3cross(s, edge1);
        float v = f * vec3dot(ray.direction, q.data());

        if (v < 0.f || u + v > 1.f)
        {
            return std::nullopt;
        }

        float t = f * vec3dot(edge2, q.data());
        if (t < EPSILON)
        {
            return std::nullopt;
        }

        Ray::Hit hit;
        hit.distance = t;
        auto p = ray.at(t);
        hit.point[0] = p[0];
        hit.point[1] = p[1];
        hit.point[2] = p[2];

        auto cross12 = vec3cross(edge1, edge2);
        auto norm = vec3normalize(cross12.data());
        hit.normal[0] = norm[0];
        hit.normal[1] = norm[1];
        hit.normal[2] = norm[2];

        return hit;
    }

    std::optional<Ray::Hit> intersect(const Ray& ray, const Vec3& v0, const Vec3& v1, const Vec3& v2)
    {
        return intersect(ray, v0.data(), v1.data(), v2.data());
    }

    Ray screenToWorldRay(
        const float* screenPos, const float* viewportSize, const float* viewMatrix, const float* projectionMatrix)
    {
        return screenToWorldRay(screenPos, viewportSize, viewMatrix, projectionMatrix, false);
    }

    Ray screenToWorldRay(
        const float* screenPos, const float* viewportSize, const Mat4& viewMatrix, const Mat4& projectionMatrix)
    {
        return screenToWorldRay(screenPos, viewportSize, viewMatrix.data(), projectionMatrix.data(), false);
    }

    Ray screenToWorldRay(
        const float* screenPos,
        const float* viewportSize,
        const float* viewMatrix,
        const float* projectionMatrix,
        bool isOrthographic)
    {
        const float vpW = (viewportSize[0] > 0.f) ? viewportSize[0] : 1.f;
        const float vpH = (viewportSize[1] > 0.f) ? viewportSize[1] : 1.f;
        const float ndcX = (2.f * screenPos[0]) / vpW - 1.f;
        const float ndcY = 1.f - (2.f * screenPos[1]) / vpH; // flip Y

        float invProj[16], invView[16];
        if (!mat4Inverse(invProj, projectionMatrix) || !mat4Inverse(invView, viewMatrix))
        {
            Ray fallback;
            fallback.direction[2] = -1.f;
            return fallback;
        }

        Ray ray;

        if (isOrthographic)
        {
            // Origin: unproject NDC point into world space
            float clipNear[4] = { ndcX, ndcY, -1.f, 1.f };
            auto eyeNear = mat4MulVec4(invProj, clipNear);
            float w = eyeNear[3] != 0.f ? eyeNear[3] : 1.f;
            float eyeNearW[4] = { eyeNear[0] / w, eyeNear[1] / w, eyeNear[2] / w, 1.f };
            auto worldOrigin = mat4MulVec4(invView, eyeNearW);
            ray.origin[0] = worldOrigin[0];
            ray.origin[1] = worldOrigin[1];
            ray.origin[2] = worldOrigin[2];

            // Direction: -Z column of invView = camera forward
            float fwd[3] = { -invView[8], -invView[9], -invView[10] };
            auto norm = vec3normalize(fwd);
            ray.direction[0] = norm[0];
            ray.direction[1] = norm[1];
            ray.direction[2] = norm[2];
        }
        else
        {
            // Clip -> eye (direction, w=0)
            float clipDir[4] = { ndcX, ndcY, -1.f, 1.f };
            auto eyeDir = mat4MulVec4(invProj, clipDir);
            float eyeDirW[4] = { eyeDir[0], eyeDir[1], -1.f, 0.f };

            // Eye -> world
            auto worldDir = mat4MulVec4(invView, eyeDirW);
            float dir3[3] = { worldDir[0], worldDir[1], worldDir[2] };
            auto norm = vec3normalize(dir3);
            ray.direction[0] = norm[0];
            ray.direction[1] = norm[1];
            ray.direction[2] = norm[2];

            // Origin: camera position = last column of invView
            ray.origin[0] = invView[12];
            ray.origin[1] = invView[13];
            ray.origin[2] = invView[14];
        }

        return ray;
    }

    Ray screenToWorldRay(
        const float* screenPos,
        const float* viewportSize,
        const Mat4& viewMatrix,
        const Mat4& projectionMatrix,
        bool isOrthographic)
    {
        return screenToWorldRay(screenPos, viewportSize, viewMatrix.data(), projectionMatrix.data(), isOrthographic);
    }
} // namespace nfx::graphics::math
