#pragma once

/**
 * \file Quat.h
 * \brief Declares a minimal quaternion type and helpers for rotation composition and application.
 */

#include "Mat4.h"

#include <cmath>

namespace nfx::graphics::math
{
    /**
     * \brief Quaternion stored as scalar part plus xyz vector part.
     */
    struct Quat
    {
        float w = 1.f;
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };

    /**
     * \brief Builds a quaternion from an angle-axis rotation.
     * \param angle Rotation angle in radians.
     * \param ax X component of the rotation axis.
     * \param ay Y component of the rotation axis.
     * \param az Z component of the rotation axis.
     * \return Angle-axis quaternion, or identity when axis length is zero.
     */
    inline Quat quatAngleAxis(float angle, float ax, float ay, float az)
    {
        const float axisLen = std::sqrt(ax * ax + ay * ay + az * az);
        if (axisLen == 0.f)
        {
            return { 1.f, 0.f, 0.f, 0.f };
        }

        ax /= axisLen;
        ay /= axisLen;
        az /= axisLen;

        const float half = angle * 0.5f;
        const float s = std::sin(half);
        return { std::cos(half), ax * s, ay * s, az * s };
    }

    /**
     * \brief Returns the Hamilton product of two quaternions.
     * \param a Left-hand quaternion.
     * \param b Right-hand quaternion.
     * \return Quaternion product a * b.
     */
    inline Quat quatMul(Quat a, Quat b)
    {
        return {
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        };
    }

    /**
     * \brief Returns a normalized quaternion.
     * \param q Quaternion to normalize.
     * \return Normalized quaternion, or identity when the input length is zero.
     */
    inline Quat quatNormalize(Quat q)
    {
        const float len = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
        if (len == 0.f)
        {
            return { 1.f, 0.f, 0.f, 0.f };
        }
        return { q.w / len, q.x / len, q.y / len, q.z / len };
    }

    /**
     * \brief Applies a quaternion rotation to a 3D vector.
     * \param q Rotation quaternion.
     * \param v Input vector.
     * \param out Output vector receiving the rotated result.
     * \note q is expected to be normalized.
     * \note Uses the optimized formula: v' = v + 2w(q×v) + 2(q×(q×v)).
     */
    inline void quatRotate(Quat q, const float v[3], float out[3])
    {
        // t = 2 * cross(q.xyz, v)
        const float tx = 2.f * (q.y * v[2] - q.z * v[1]);
        const float ty = 2.f * (q.z * v[0] - q.x * v[2]);
        const float tz = 2.f * (q.x * v[1] - q.y * v[0]);

        // v' = v + w*t + cross(q.xyz, t)
        out[0] = v[0] + q.w * tx + q.y * tz - q.z * ty;
        out[1] = v[1] + q.w * ty + q.z * tx - q.x * tz;
        out[2] = v[2] + q.w * tz + q.x * ty - q.y * tx;
    }

    /**
     * \brief Converts a normalized quaternion to a column-major 4x4 rotation matrix.
     * \param q Rotation quaternion. Expected to be normalized.
     * \param m Output matrix.
     */
    inline void quatToMat4(Quat q, Mat4& m)
    {
        const float xx = q.x * q.x;
        const float yy = q.y * q.y;
        const float zz = q.z * q.z;
        const float xy = q.x * q.y;
        const float xz = q.x * q.z;
        const float yz = q.y * q.z;
        const float wx = q.w * q.x;
        const float wy = q.w * q.y;
        const float wz = q.w * q.z;

        // Column 0
        m[0] = 1.f - 2.f * (yy + zz);
        m[1] = 2.f * (xy + wz);
        m[2] = 2.f * (xz - wy);
        m[3] = 0.f;
        // Column 1
        m[4] = 2.f * (xy - wz);
        m[5] = 1.f - 2.f * (xx + zz);
        m[6] = 2.f * (yz + wx);
        m[7] = 0.f;
        // Column 2
        m[8] = 2.f * (xz + wy);
        m[9] = 2.f * (yz - wx);
        m[10] = 1.f - 2.f * (xx + yy);
        m[11] = 0.f;
        // Column 3
        m[12] = 0.f;
        m[13] = 0.f;
        m[14] = 0.f;
        m[15] = 1.f;
    }
} // namespace nfx::graphics::math
