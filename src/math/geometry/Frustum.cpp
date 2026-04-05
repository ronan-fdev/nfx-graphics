#include "nfx/graphics/math/geometry/Frustum.h"

#include <cmath>

namespace nfx::graphics::math
{
    namespace
    {
        void normalizePlane(float plane[4])
        {
            const float len = std::sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
            if (len == 0.0f)
            {
                return;
            }

            plane[0] /= len;
            plane[1] /= len;
            plane[2] /= len;
            plane[3] /= len;
        }

        float signedDistance(const float plane[4], const float point[3])
        {
            return plane[0] * point[0] + plane[1] * point[1] + plane[2] * point[2] + plane[3];
        }
    } // namespace

    Frustum Frustum::fromViewProj(const float m[16])
    {
        Frustum frustum;

        // Column-major extraction
        frustum.planes[0][0] = m[3] + m[0];
        frustum.planes[0][1] = m[7] + m[4];
        frustum.planes[0][2] = m[11] + m[8];
        frustum.planes[0][3] = m[15] + m[12];

        frustum.planes[1][0] = m[3] - m[0];
        frustum.planes[1][1] = m[7] - m[4];
        frustum.planes[1][2] = m[11] - m[8];
        frustum.planes[1][3] = m[15] - m[12];

        frustum.planes[2][0] = m[3] + m[1];
        frustum.planes[2][1] = m[7] + m[5];
        frustum.planes[2][2] = m[11] + m[9];
        frustum.planes[2][3] = m[15] + m[13];

        frustum.planes[3][0] = m[3] - m[1];
        frustum.planes[3][1] = m[7] - m[5];
        frustum.planes[3][2] = m[11] - m[9];
        frustum.planes[3][3] = m[15] - m[13];

        frustum.planes[4][0] = m[3] + m[2];
        frustum.planes[4][1] = m[7] + m[6];
        frustum.planes[4][2] = m[11] + m[10];
        frustum.planes[4][3] = m[15] + m[14];

        frustum.planes[5][0] = m[3] - m[2];
        frustum.planes[5][1] = m[7] - m[6];
        frustum.planes[5][2] = m[11] - m[10];
        frustum.planes[5][3] = m[15] - m[14];

        for (auto& plane : frustum.planes)
        {
            normalizePlane(plane);
        }

        return frustum;
    }

    Frustum Frustum::fromViewProj(const Mat4& m)
    {
        return fromViewProj(m.data());
    }

    bool Frustum::containsPoint(const float p[3]) const
    {
        for (const auto& plane : planes)
        {
            if (signedDistance(plane, p) < 0.0f)
            {
                return false;
            }
        }
        return true;
    }

    bool Frustum::containsPoint(const Vec3& p) const
    {
        return containsPoint(p.data());
    }

    bool Frustum::intersects(const Bounds::AABB& aabb) const
    {
        for (const auto& plane : planes)
        {
            const float px = plane[0] >= 0.0f ? aabb.max[0] : aabb.min[0];
            const float py = plane[1] >= 0.0f ? aabb.max[1] : aabb.min[1];
            const float pz = plane[2] >= 0.0f ? aabb.max[2] : aabb.min[2];
            const float positive[3] = { px, py, pz };

            if (signedDistance(plane, positive) < 0.0f)
            {
                return false;
            }
        }
        return true;
    }

    bool Frustum::intersects(const Bounds::Sphere& sphere) const
    {
        for (const auto& plane : planes)
        {
            if (signedDistance(plane, sphere.center) < -sphere.radius)
            {
                return false;
            }
        }
        return true;
    }
} // namespace nfx::graphics::math
