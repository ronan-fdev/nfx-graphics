#pragma once

/**
 * \file Mat3.h
 * \brief Declares helpers for building and manipulating column-major 3x3 transform matrices.
 */

#include "Mat4.h"

#include <array>
#include <cmath>

namespace nfx::graphics::math
{
    struct Mat3;
    inline void mat3Identity(Mat3& m);

    /**
     * \brief Column-major 3x3 float matrix.
     */
    struct Mat3
    {
        /// Column-major storage (index = col * 3 + row)
        std::array<float, 9> v{};

        /**
         * \brief Returns a pointer to the first matrix element.
         */
        [[nodiscard]] float* data() noexcept { return v.data(); }

        /**
         * \brief Returns a const pointer to the first matrix element.
         */
        [[nodiscard]] const float* data() const noexcept { return v.data(); }

        /**
         * \brief Returns a mutable matrix element by linear index.
         * \param i Linear index in [0, 8].
         */
        [[nodiscard]] float& operator[](int i) noexcept { return v[static_cast<std::size_t>(i)]; }

        /**
         * \brief Returns a const matrix element by linear index.
         * \param i Linear index in [0, 8].
         */
        [[nodiscard]] const float& operator[](int i) const noexcept { return v[static_cast<std::size_t>(i)]; }

        /**
         * \brief Creates and returns the 3x3 identity matrix.
         */
        static Mat3 identity() noexcept
        {
            Mat3 m;
            mat3Identity(m);
            return m;
        }
    };

    /**
     * \brief Writes the 3x3 identity matrix.
     * \param m Output matrix stored in column-major order.
     */
    inline void mat3Identity(float m[9])
    {
        for (int i = 0; i < 9; ++i)
        {
            m[i] = 0.f;
        }
        m[0] = m[4] = m[8] = 1.f;
    }

    /**
     * \brief Writes the 3x3 identity matrix.
     * \param m Output matrix stored in column-major order.
     */
    inline void mat3Identity(Mat3& m)
    {
        mat3Identity(m.data());
    }

    /**
     * \brief Writes a scaling matrix.
     * \param m Output matrix stored in column-major order.
     * \param sx Scale on X.
     * \param sy Scale on Y.
     * \param sz Scale on Z.
     */
    inline void mat3Scale(float m[9], float sx, float sy, float sz)
    {
        mat3Identity(m);
        m[0] = sx;
        m[4] = sy;
        m[8] = sz;
    }

    /**
     * \brief Writes a scaling matrix.
     * \param m Output matrix stored in column-major order.
     * \param sx Scale on X.
     * \param sy Scale on Y.
     * \param sz Scale on Z.
     */
    inline void mat3Scale(Mat3& m, float sx, float sy, float sz)
    {
        mat3Scale(m.data(), sx, sy, sz);
    }

    /**
     * \brief Writes a rotation matrix around the X axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateX(float m[9], float angle)
    {
        mat3Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[4] = c;
        m[5] = s;
        m[7] = -s;
        m[8] = c;
    }

    /**
     * \brief Writes a rotation matrix around the X axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateX(Mat3& m, float angle)
    {
        mat3RotateX(m.data(), angle);
    }

    /**
     * \brief Writes a rotation matrix around the Y axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateY(float m[9], float angle)
    {
        mat3Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[0] = c;
        m[2] = -s;
        m[6] = s;
        m[8] = c;
    }

    /**
     * \brief Writes a rotation matrix around the Y axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateY(Mat3& m, float angle)
    {
        mat3RotateY(m.data(), angle);
    }

    /**
     * \brief Writes a rotation matrix around the Z axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateZ(float m[9], float angle)
    {
        mat3Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[0] = c;
        m[1] = s;
        m[3] = -s;
        m[4] = c;
    }

    /**
     * \brief Writes a rotation matrix around the Z axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat3RotateZ(Mat3& m, float angle)
    {
        mat3RotateZ(m.data(), angle);
    }

    /**
     * \brief Computes the inverse-transpose normal matrix from the upper-left 3x3 of a Mat4.
     * \param out Output 3x3 matrix stored in column-major order.
     * \param in Source 4x4 matrix stored in column-major order.
     * \note If the source 3x3 determinant is zero, writes a zero matrix.
     */
    inline void mat3InverseTranspose(float out[9], const float in[16])
    {
        // Extract upper-left 3x3 (column-major)
        const float m[9] = {
            in[0], in[1], in[2], // col 0
            in[4], in[5], in[6], // col 1
            in[8], in[9], in[10] // col 2
        };

        // Cofactors C(i,j): normal matrix N(i,j) = C(i,j) / det
        // clang-format off
        const float c00 =  (m[4] * m[8] - m[7] * m[5]);
        const float c10 = -(m[3] * m[8] - m[6] * m[5]);
        const float c20 =  (m[3] * m[7] - m[6] * m[4]);
        const float c01 = -(m[1] * m[8] - m[7] * m[2]);
        const float c11 =  (m[0] * m[8] - m[6] * m[2]);
        const float c21 = -(m[0] * m[7] - m[6] * m[1]);
        const float c02 =  (m[1] * m[5] - m[4] * m[2]);
        const float c12 = -(m[0] * m[5] - m[3] * m[2]);
        const float c22 =  (m[0] * m[4] - m[3] * m[1]);
        // clang-format on

        const float det = m[0] * c00 + m[3] * c01 + m[6] * c02;
        const float inv = (det != 0.f) ? 1.f / det : 0.f;

        // col-major: out[col*3 + row] = N(row, col)
        out[0] = c00 * inv;
        out[1] = c10 * inv;
        out[2] = c20 * inv;
        out[3] = c01 * inv;
        out[4] = c11 * inv;
        out[5] = c21 * inv;
        out[6] = c02 * inv;
        out[7] = c12 * inv;
        out[8] = c22 * inv;
    }

    /**
     * \brief Computes the inverse-transpose normal matrix from the upper-left 3x3 of a Mat4.
     * \param out Output 3x3 matrix.
     * \param in Source 4x4 matrix.
     */
    inline void mat3InverseTranspose(Mat3& out, const Mat4& in)
    {
        mat3InverseTranspose(out.data(), in.data());
    }
} // namespace nfx::graphics::math
