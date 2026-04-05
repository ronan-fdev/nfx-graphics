#pragma once

#include "nfx/graphics/math/geometry/Bounds.h"
#include "nfx/graphics/math/geometry/Frustum.h"
#include "nfx/graphics/math/Mat4.h"

#include <cmath>
#include <optional>

namespace nfx::graphics::gl::detail
{
    struct CullingDecision
    {
        bool tested = false;
        bool culled = false;
    };

    inline math::Bounds::Sphere transformSphere(const math::Bounds::Sphere& sphere, const math::Mat4& transform)
    {
        math::Bounds::Sphere result = sphere;

        const float localCenter4[4] = { sphere.center[0], sphere.center[1], sphere.center[2], 1.0f };
        const auto worldCenter = math::mat4MulVec4(transform, localCenter4);
        result.center[0] = worldCenter[0];
        result.center[1] = worldCenter[1];
        result.center[2] = worldCenter[2];

        const float linearNorm = std::sqrt(
            transform[0] * transform[0] + transform[1] * transform[1] + transform[2] * transform[2] +
            transform[4] * transform[4] + transform[5] * transform[5] + transform[6] * transform[6] +
            transform[8] * transform[8] + transform[9] * transform[9] + transform[10] * transform[10]);
        result.radius *= linearNorm;

        return result;
    }

    inline math::Bounds::AABB transformAABB(const math::Bounds::AABB& aabb, const math::Mat4& transform)
    {
        math::Bounds::AABB worldAABB;
        const float* m = transform.data();

        for (int i = 0; i < 3; ++i)
        {
            worldAABB.min[i] = m[12 + i];
            worldAABB.max[i] = m[12 + i];
            for (int j = 0; j < 3; ++j)
            {
                const float e = m[j * 4 + i] * aabb.min[j];
                const float f = m[j * 4 + i] * aabb.max[j];
                if (e < f)
                {
                    worldAABB.min[i] += e;
                    worldAABB.max[i] += f;
                }
                else
                {
                    worldAABB.min[i] += f;
                    worldAABB.max[i] += e;
                }
            }
        }

        return worldAABB;
    }

    inline CullingDecision decideFrustumCulling(
        const math::Frustum& frustum,
        const math::Mat4& transform,
        const std::optional<math::Bounds::AABB>& commandAABB,
        const std::optional<math::Bounds::Sphere>& commandSphere,
        const std::optional<math::Bounds::AABB>& meshAABB,
        const std::optional<math::Bounds::Sphere>& meshSphere)
    {
        // Prefer AABB (tighter), then sphere fallback
        const auto& aabb = commandAABB ? commandAABB : meshAABB;
        if (aabb)
        {
            const auto worldAABB = transformAABB(*aabb, transform);
            return { true, !frustum.intersects(worldAABB) };
        }

        const auto& sphere = commandSphere ? commandSphere : meshSphere;
        if (sphere)
        {
            const auto worldSphere = transformSphere(*sphere, transform);
            return { true, !frustum.intersects(worldSphere) };
        }

        return { false, false };
    }
} // namespace nfx::graphics::gl::detail
