#pragma once

/**
 * \file Vec3.h
 * \brief Declares lightweight helpers for 3D vector arithmetic on float triplets.
 */

#include <array>
#include <cmath>

namespace nfx::graphics::math
{
    /**
     * \brief Lightweight 3D float vector.
     */
    struct Vec3
    {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;

        /**
         * \brief Returns a pointer to the first component.
         */
        [[nodiscard]] float* data() noexcept { return &x; }

        /**
         * \brief Returns a const pointer to the first component.
         */
        [[nodiscard]] const float* data() const noexcept { return &x; }

        /**
         * \brief Returns a mutable component by index.
         * \param i Component index (0=x, 1=y, 2=z).
         */
        [[nodiscard]] float& operator[](int i) noexcept { return data()[i]; }

        /**
         * \brief Returns a const component by index.
         * \param i Component index (0=x, 1=y, 2=z).
         */
        [[nodiscard]] const float& operator[](int i) const noexcept { return data()[i]; }
    };

    /**
     * \brief Returns the Euclidean length of a 3D vector.
     * \param v Pointer to three float components.
     * \return Vector length.
     */
    inline float vec3len(const float* v)
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    /**
     * \brief Returns the Euclidean length of a Vec3.
     * \param v Input vector.
     * \return Vector length.
     */
    inline float vec3len(const Vec3& v)
    {
        return vec3len(v.data());
    }

    /**
     * \brief Returns the dot product of two 3D vectors.
     * \param a Pointer to the first vector.
     * \param b Pointer to the second vector.
     * \return Dot product a.b.
     */
    inline float vec3dot(const float a[3], const float b[3])
    {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    /**
     * \brief Returns the dot product of two Vec3 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Dot product a.b.
     */
    inline float vec3dot(const Vec3& a, const Vec3& b)
    {
        return vec3dot(a.data(), b.data());
    }

    /**
     * \brief Returns the cross product of two 3D vectors.
     * \param a Pointer to the first vector.
     * \param b Pointer to the second vector.
     * \return Cross product a x b.
     */
    inline std::array<float, 3> vec3cross(const float a[3], const float b[3])
    {
        return {
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0],
        };
    }

    /**
     * \brief Returns the cross product of two Vec3 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Cross product a x b.
     */
    inline Vec3 vec3cross(const Vec3& a, const Vec3& b)
    {
        const auto c = vec3cross(a.data(), b.data());
        return { c[0], c[1], c[2] };
    }

    /**
     * \brief Returns a normalized copy of a 3D vector.
     * \param v Pointer to the vector to normalize.
     * \return Normalized vector or the zero vector when the input length is zero.
     */
    inline std::array<float, 3> vec3normalize(const float v[3])
    {
        const float len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        if (len == 0.f)
        {
            return { 0.f, 0.f, 0.f };
        }
        return { v[0] / len, v[1] / len, v[2] / len };
    }

    /**
     * \brief Returns a normalized copy of a Vec3.
     * \param v Input vector.
     * \return Normalized vector or the zero vector when the input length is zero.
     */
    inline Vec3 vec3normalize(const Vec3& v)
    {
        const auto n = vec3normalize(v.data());
        return { n[0], n[1], n[2] };
    }

    /**
     * \brief Returns the component-wise difference of two 3D vectors.
     * \param a Pointer to the left-hand vector.
     * \param b Pointer to the right-hand vector.
     * \return Component-wise subtraction a - b.
     */
    inline std::array<float, 3> vec3sub(const float a[3], const float b[3])
    {
        return { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
    }

    /**
     * \brief Returns the component-wise difference of two Vec3 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Component-wise subtraction a - b.
     */
    inline Vec3 vec3sub(const Vec3& a, const Vec3& b)
    {
        return { a.x - b.x, a.y - b.y, a.z - b.z };
    }
} // namespace nfx::graphics::math
