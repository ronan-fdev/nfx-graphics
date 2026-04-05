#pragma once

/**
 * \file Frustum.h
 * \brief Declares a view frustum built from a view-projection matrix.
 */

#include "Bounds.h"
#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Vec3.h"

namespace nfx::graphics::math
{
    /**
     * \brief View frustum represented by 6 normalized planes `(a, b, c, d)`.
     */
    struct Frustum
    {
        float planes[6][4] = {};

        /**
         * \brief Builds a frustum from a column-major view-projection matrix.
         * \param m View-projection matrix.
         * \return Extracted and normalized frustum.
         */
        [[nodiscard]] static Frustum fromViewProj(const float m[16]);

        /**
         * \brief Builds a frustum from a view-projection matrix.
         * \param m View-projection matrix.
         * \return Extracted and normalized frustum.
         */
        [[nodiscard]] static Frustum fromViewProj(const Mat4& m);

        /**
         * \brief Returns whether a point lies inside or on the frustum.
         * \param p Point to test.
         * \return True when the point is inside all planes.
         */
        [[nodiscard]] bool containsPoint(const float p[3]) const;

        /**
         * \brief Returns whether a point lies inside or on the frustum.
         * \param p Point to test.
         * \return True when the point is inside all planes.
         */
        [[nodiscard]] bool containsPoint(const Vec3& p) const;

        /**
         * \brief Returns whether an AABB intersects or lies inside the frustum.
         * \param aabb Axis-aligned bounding box to test.
         * \return True when the AABB is not fully outside any frustum plane.
         */
        [[nodiscard]] bool intersects(const Bounds::AABB& aabb) const;

        /**
         * \brief Returns whether a sphere intersects or lies inside the frustum.
         * \param sphere Sphere to test.
         * \return True when the sphere is not fully outside any frustum plane.
         */
        [[nodiscard]] bool intersects(const Bounds::Sphere& sphere) const;
    };
} // namespace nfx::graphics::math
