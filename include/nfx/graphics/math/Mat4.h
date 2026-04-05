#pragma once

/**
 * \file Mat4.h
 * \brief Declares helpers for building and manipulating column-major 4x4 transform matrices.
 */

#include "Vec3.h"

#include <array>
#include <cmath>

namespace nfx::graphics::math
{
    struct Mat4;
    inline void mat4Identity(Mat4& m);

    /**
     * \brief Column-major 4x4 float matrix.
     */
    struct Mat4
    {
        /// Column-major storage (index = col * 4 + row)
        std::array<float, 16> v{};

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
         * \param i Linear index in [0, 15].
         */
        [[nodiscard]] float& operator[](int i) noexcept { return v[static_cast<std::size_t>(i)]; }

        /**
         * \brief Returns a const matrix element by linear index.
         * \param i Linear index in [0, 15].
         */
        [[nodiscard]] const float& operator[](int i) const noexcept { return v[static_cast<std::size_t>(i)]; }

        /**
         * \brief Creates and returns the 4x4 identity matrix.
         */
        static Mat4 identity() noexcept
        {
            Mat4 m;
            mat4Identity(m);
            return m;
        }
    };

    /**
     * \brief Writes the 4x4 identity matrix.
     * \param m Output matrix stored in column-major order.
     */
    inline void mat4Identity(float m[16])
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] = 0.f;
        }
        m[0] = m[5] = m[10] = m[15] = 1.f;
    }

    /**
     * \brief Writes the 4x4 identity matrix.
     * \param m Output matrix stored in column-major order.
     */
    inline void mat4Identity(Mat4& m)
    {
        mat4Identity(m.data());
    }

    /**
     * \brief Writes a translation matrix.
     * \param m Output matrix stored in column-major order.
     * \param tx Translation on X.
     * \param ty Translation on Y.
     * \param tz Translation on Z.
     */
    inline void mat4Translate(float m[16], float tx, float ty, float tz)
    {
        mat4Identity(m);
        m[12] = tx;
        m[13] = ty;
        m[14] = tz;
    }

    /**
     * \brief Writes a translation matrix.
     * \param m Output matrix stored in column-major order.
     * \param tx Translation on X.
     * \param ty Translation on Y.
     * \param tz Translation on Z.
     */
    inline void mat4Translate(Mat4& m, float tx, float ty, float tz)
    {
        mat4Translate(m.data(), tx, ty, tz);
    }

    /**
     * \brief Writes a scaling matrix.
     * \param m Output matrix stored in column-major order.
     * \param sx Scale on X.
     * \param sy Scale on Y.
     * \param sz Scale on Z.
     */
    inline void mat4Scale(float m[16], float sx, float sy, float sz)
    {
        mat4Identity(m);
        m[0] = sx;
        m[5] = sy;
        m[10] = sz;
    }

    /**
     * \brief Writes a scaling matrix.
     * \param m Output matrix stored in column-major order.
     * \param sx Scale on X.
     * \param sy Scale on Y.
     * \param sz Scale on Z.
     */
    inline void mat4Scale(Mat4& m, float sx, float sy, float sz)
    {
        mat4Scale(m.data(), sx, sy, sz);
    }

    /**
     * \brief Writes a rotation matrix around the X axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateX(float m[16], float angle)
    {
        mat4Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[5] = c;
        m[6] = s;
        m[9] = -s;
        m[10] = c;
    }

    /**
     * \brief Writes a rotation matrix around the X axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateX(Mat4& m, float angle)
    {
        mat4RotateX(m.data(), angle);
    }

    /**
     * \brief Writes a rotation matrix around the Y axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateY(float m[16], float angle)
    {
        mat4Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[0] = c;
        m[2] = -s;
        m[8] = s;
        m[10] = c;
    }

    /**
     * \brief Writes a rotation matrix around the Y axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateY(Mat4& m, float angle)
    {
        mat4RotateY(m.data(), angle);
    }

    /**
     * \brief Writes a rotation matrix around the Z axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateZ(float m[16], float angle)
    {
        mat4Identity(m);
        float c = std::cos(angle);
        float s = std::sin(angle);
        m[0] = c;
        m[1] = s;
        m[4] = -s;
        m[5] = c;
    }

    /**
     * \brief Writes a rotation matrix around the Z axis.
     * \param m Output matrix stored in column-major order.
     * \param angle Rotation angle in radians.
     */
    inline void mat4RotateZ(Mat4& m, float angle)
    {
        mat4RotateZ(m.data(), angle);
    }

    /**
     * \brief Writes an orthographic projection matrix.
     * \param m Output matrix stored in column-major order.
     * \param left Left clipping plane.
     * \param right Right clipping plane.
     * \param bottom Bottom clipping plane.
     * \param top Top clipping plane.
     * \param zNear Near clipping plane.
     * \param zFar Far clipping plane.
     */
    inline void mat4Ortho(float m[16], float left, float right, float bottom, float top, float zNear, float zFar)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] = 0.f;
        }
        m[0] = 2.f / (right - left);
        m[5] = 2.f / (top - bottom);
        m[10] = -2.f / (zFar - zNear);
        m[12] = -(right + left) / (right - left);
        m[13] = -(top + bottom) / (top - bottom);
        m[14] = -(zFar + zNear) / (zFar - zNear);
        m[15] = 1.f;
    }

    /**
     * \brief Writes an orthographic projection matrix to a Mat4.
     * \param m Output matrix stored in column-major order.
     * \param left Left clipping plane.
     * \param right Right clipping plane.
     * \param bottom Bottom clipping plane.
     * \param top Top clipping plane.
     * \param zNear Near clipping plane.
     * \param zFar Far clipping plane.
     */
    inline void mat4Ortho(Mat4& m, float left, float right, float bottom, float top, float zNear, float zFar)
    {
        mat4Ortho(m.data(), left, right, bottom, top, zNear, zFar);
    }

    /**
     * \brief Writes a perspective projection matrix.
     * \param m Output matrix stored in column-major order.
     * \param fovY Vertical field of view in radians.
     * \param aspect Viewport aspect ratio.
     * \param zNear Near clipping plane.
     * \param zFar Far clipping plane.
     */
    inline void mat4Perspective(float m[16], float fovY, float aspect, float zNear, float zFar)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] = 0.f;
        }
        float f = 1.f / std::tan(fovY * 0.5f);
        m[0] = f / aspect;
        m[5] = f;
        m[10] = -(zFar + zNear) / (zFar - zNear);
        m[11] = -1.f;
        m[14] = -(2.f * zFar * zNear) / (zFar - zNear);
    }

    /**
     * \brief Writes a perspective projection matrix.
     * \param m Output matrix stored in column-major order.
     * \param fovY Vertical field of view in radians.
     * \param aspect Viewport aspect ratio.
     * \param zNear Near clipping plane.
     * \param zFar Far clipping plane.
     */
    inline void mat4Perspective(Mat4& m, float fovY, float aspect, float zNear, float zFar)
    {
        mat4Perspective(m.data(), fovY, aspect, zNear, zFar);
    }

    /**
     * \brief Writes a view matrix from eye, center and up vectors.
     * \param m Output matrix stored in column-major order.
     * \param ex Eye position X.
     * \param ey Eye position Y.
     * \param ez Eye position Z.
     * \param cx Target position X.
     * \param cy Target position Y.
     * \param cz Target position Z.
     * \param upx Up vector X component.
     * \param upy Up vector Y component.
     * \param upz Up vector Z component.
     * \note Handles degenerate eye/center and forward/up combinations with stable fallback axes.
     */
    inline void mat4LookAt(
        float m[16], float ex, float ey, float ez, float cx, float cy, float cz, float upx, float upy, float upz)
    {
        constexpr float eps = 1e-6f;

        const float eye[3] = { ex, ey, ez };
        const float center[3] = { cx, cy, cz };

        auto f = vec3sub(center, eye);
        if (vec3len(f.data()) <= eps)
        {
            // Degenerate eye/center: fallback to a sensible forward axis
            f = { 0.f, 0.f, -1.f };
        }
        f = vec3normalize(f.data());

        std::array<float, 3> up = { upx, upy, upz };
        if (vec3len(up.data()) <= eps)
        {
            up = { 0.f, 1.f, 0.f };
        }
        up = vec3normalize(up.data());

        if (std::fabs(vec3dot(f.data(), up.data())) > 0.999f)
        {
            // Degenerate forward/up pair: pick a stable fallback up axis
            if (std::fabs(f[1]) < 0.999f)
            {
                up = { 0.f, 1.f, 0.f };
            }
            else
            {
                up = { 1.f, 0.f, 0.f };
            }
        }

        auto r = vec3cross(f.data(), up.data());
        if (vec3len(r.data()) <= eps)
        {
            mat4Identity(m);
            m[12] = -ex;
            m[13] = -ey;
            m[14] = -ez;
            return;
        }
        r = vec3normalize(r.data());

        const auto u = vec3cross(r.data(), f.data());

        for (int i = 0; i < 16; ++i)
        {
            m[i] = 0.f;
        }
        m[0] = r[0];
        m[4] = r[1];
        m[8] = r[2];
        m[1] = u[0];
        m[5] = u[1];
        m[9] = u[2];
        m[2] = -f[0];
        m[6] = -f[1];
        m[10] = -f[2];
        m[12] = -vec3dot(r.data(), eye);
        m[13] = -vec3dot(u.data(), eye);
        m[14] = vec3dot(f.data(), eye);
        m[15] = 1.f;
    }

    /**
     * \brief Writes a view matrix from eye, center and up vectors.
     * \param m Output matrix stored in column-major order.
     * \param ex Eye position X.
     * \param ey Eye position Y.
     * \param ez Eye position Z.
     * \param cx Target position X.
     * \param cy Target position Y.
     * \param cz Target position Z.
     * \param upx Up vector X component.
     * \param upy Up vector Y component.
     * \param upz Up vector Z component.
     */
    inline void mat4LookAt(
        Mat4& m, float ex, float ey, float ez, float cx, float cy, float cz, float upx, float upy, float upz)
    {
        mat4LookAt(m.data(), ex, ey, ez, cx, cy, cz, upx, upy, upz);
    }

    /**
     * \brief Writes a view matrix from eye and center positions using the world up vector (0,1,0).
     * \param m Output matrix stored in column-major order.
     * \param ex Eye position X.
     * \param ey Eye position Y.
     * \param ez Eye position Z.
     * \param cx Target position X.
     * \param cy Target position Y.
     * \param cz Target position Z.
     */
    inline void mat4LookAt(float m[16], float ex, float ey, float ez, float cx, float cy, float cz)
    {
        mat4LookAt(m, ex, ey, ez, cx, cy, cz, 0.f, 1.f, 0.f);
    }

    /**
     * \brief Writes a view matrix using the world up vector (0,1,0).
     * \param m Output matrix stored in column-major order.
     * \param ex Eye position X.
     * \param ey Eye position Y.
     * \param ez Eye position Z.
     * \param cx Target position X.
     * \param cy Target position Y.
     * \param cz Target position Z.
     */
    inline void mat4LookAt(Mat4& m, float ex, float ey, float ez, float cx, float cy, float cz)
    {
        mat4LookAt(m.data(), ex, ey, ez, cx, cy, cz, 0.f, 1.f, 0.f);
    }

    /**
     * \brief Multiplies two column-major 4x4 matrices.
     * \param out Output matrix receiving a * b.
     * \param a Left-hand matrix.
     * \param b Right-hand matrix.
     */
    inline void mat4Mul(float out[16], const float a[16], const float b[16])
    {
        float tmp[16];
        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                float v = 0.f;
                for (int k = 0; k < 4; ++k)
                {
                    v += a[k * 4 + row] * b[col * 4 + k];
                }
                tmp[col * 4 + row] = v;
            }
        }

        for (int i = 0; i < 16; ++i)
        {
            out[i] = tmp[i];
        }
    }

    /**
     * \brief Multiplies two column-major 4x4 matrices.
     * \param out Output matrix receiving a * b.
     * \param a Left-hand matrix.
     * \param b Right-hand matrix.
     */
    inline void mat4Mul(Mat4& out, const Mat4& a, const Mat4& b)
    {
        mat4Mul(out.data(), a.data(), b.data());
    }

    /**
     * \brief Inverts a column-major 4x4 matrix.
     * \param out Output inverse matrix.
     * \param m Input matrix.
     * \return False when the matrix is singular, true otherwise.
     */
    inline bool mat4Inverse(float out[16], const float m[16])
    {
        // clang-format off
        float inv[16];
        inv[ 0] =  m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
        inv[ 4] = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
        inv[ 8] =  m[4]*m[9] *m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
        inv[12] = -m[4]*m[9] *m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];

        inv[ 1] = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
        inv[ 5] =  m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
        inv[ 9] = -m[0]*m[9] *m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
        inv[13] =  m[0]*m[9] *m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];

        inv[ 2] =  m[1]*m[6] *m[15] - m[1]*m[7] *m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7]  - m[13]*m[3]*m[6];
        inv[ 6] = -m[0]*m[6] *m[15] + m[0]*m[7] *m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7]  + m[12]*m[3]*m[6];
        inv[10] =  m[0]*m[5] *m[15] - m[0]*m[7] *m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7]  - m[12]*m[3]*m[5];
        inv[14] = -m[0]*m[5] *m[14] + m[0]*m[6] *m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6]  + m[12]*m[2]*m[5];

        inv[ 3] = -m[1]*m[6] *m[11] + m[1]*m[7] *m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7]   + m[9]*m[3]*m[6];
        inv[ 7] =  m[0]*m[6] *m[11] - m[0]*m[7] *m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7]   - m[8]*m[3]*m[6];
        inv[11] = -m[0]*m[5] *m[11] + m[0]*m[7] *m[9]  + m[4]*m[1]*m[11] - m[4]*m[3]*m[9]  - m[8]*m[1]*m[7]   + m[8]*m[3]*m[5];
        inv[15] =  m[0]*m[5] *m[10] - m[0]*m[6] *m[9]  - m[4]*m[1]*m[10] + m[4]*m[2]*m[9]  + m[8]*m[1]*m[6]   - m[8]*m[2]*m[5];
        // clang-format on

        const float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
        if (det == 0.f)
        {
            return false;
        }

        const float invDet = 1.f / det;
        for (int i = 0; i < 16; ++i)
        {
            out[i] = inv[i] * invDet;
        }

        return true;
    }

    /**
     * \brief Inverts a Mat4 matrix.
     * \param out Output inverse matrix.
     * \param m Input matrix.
     * \return False when the matrix is singular, true otherwise.
     */
    inline bool mat4Inverse(Mat4& out, const Mat4& m)
    {
        return mat4Inverse(out.data(), m.data());
    }

    /**
     * \brief Multiplies a column-major 4x4 matrix by a vec4.
     * \param m Input matrix.
     * \param v Input homogeneous vector.
     * \return The transformed homogeneous vector.
     */
    inline std::array<float, 4> mat4MulVec4(const float m[16], const float v[4])
    {
        // clang-format off
        return {
            m[0] * v[0] + m[4] * v[1] + m[8]  * v[2] + m[12] * v[3],
            m[1] * v[0] + m[5] * v[1] + m[9]  * v[2] + m[13] * v[3],
            m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3],
            m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3],
        };
        // clang-format on
    }

    /**
     * \brief Multiplies a Mat4 by a vec4.
     * \param m Input matrix.
     * \param v Input homogeneous vector.
     * \return The transformed homogeneous vector.
     */
    inline std::array<float, 4> mat4MulVec4(const Mat4& m, const float v[4])
    {
        return mat4MulVec4(m.data(), v);
    }

} // namespace nfx::graphics::math
