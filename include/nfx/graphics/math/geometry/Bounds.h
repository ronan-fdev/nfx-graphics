#pragma once

/**
 * \file Bounds.h
 * \brief Declares simple bounding volume types used by the math and intersection helpers.
 */

#include <array>

namespace nfx::graphics::math
{
    namespace Bounds
    {
        /**
         * \brief Axis-aligned bounding box represented by minimum and maximum corners.
         */
        struct AABB
        {
            float min[3] = { 0.0f };
            float max[3] = { 0.0f };

            /**
             * \brief Returns the center of the bounding box.
             * \return Bounding box center as `(x, y, z)`.
             */
            [[nodiscard]] std::array<float, 3> center() const
            {
                return { (min[0] + max[0]) * 0.5f, (min[1] + max[1]) * 0.5f, (min[2] + max[2]) * 0.5f };
            }

            /**
             * \brief Returns the half-size extents of the bounding box.
             * \return Bounding box half-extents as `(x, y, z)`.
             */
            [[nodiscard]] std::array<float, 3> extents() const
            {
                return { (max[0] - min[0]) * 0.5f, (max[1] - min[1]) * 0.5f, (max[2] - min[2]) * 0.5f };
            }
        };

        /**
         * \brief Bounding sphere represented by a center and radius.
         */
        struct Sphere
        {
            float center[3] = { 0.0f };
            float radius = 1.0f;
        };
    } // namespace Bounds
} // namespace nfx::graphics::math
