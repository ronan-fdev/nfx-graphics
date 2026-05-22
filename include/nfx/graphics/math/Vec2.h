#pragma once

/**
 * \file Vec2.h
 * \brief Declares lightweight helpers for 2D vector arithmetic on float pairs.
 */

#include <array>
#include <cmath>

namespace nfx::graphics::math
{
    /**
     * \brief Lightweight 2D float vector.
     */
    struct Vec2
    {
        float x = 0.f;
        float y = 0.f;

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
         * \param i Component index (0=x, 1=y).
         */
        [[nodiscard]] float& operator[](int i) noexcept { return data()[i]; }

        /**
         * \brief Returns a const component by index.
         * \param i Component index (0=x, 1=y).
         */
        [[nodiscard]] const float& operator[](int i) const noexcept { return data()[i]; }
    };

    /**
     * \brief Returns the Euclidean length of a 2D vector.
     * \param v Pointer to two float components.
     * \return Vector length.
     */
    inline float vec2len(const float* v)
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1]);
    }

    /**
     * \brief Returns the Euclidean length of a Vec2.
     * \param v Input vector.
     * \return Vector length.
     */
    inline float vec2len(const Vec2& v)
    {
        return vec2len(v.data());
    }

    /**
     * \brief Returns the dot product of two 2D vectors.
     * \param a Pointer to the first vector.
     * \param b Pointer to the second vector.
     * \return Dot product a.b.
     */
    inline float vec2dot(const float a[2], const float b[2])
    {
        return a[0] * b[0] + a[1] * b[1];
    }

    /**
     * \brief Returns the dot product of two Vec2 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Dot product a.b.
     */
    inline float vec2dot(const Vec2& a, const Vec2& b)
    {
        return vec2dot(a.data(), b.data());
    }

    /**
     * \brief Returns the 2D cross product (pseudo-z scalar) of two 2D vectors.
     * \param a Pointer to the first vector.
     * \param b Pointer to the second vector.
     * \return Scalar a[0]*b[1] - a[1]*b[0].
     */
    inline float vec2cross(const float a[2], const float b[2])
    {
        return a[0] * b[1] - a[1] * b[0];
    }

    /**
     * \brief Returns the 2D cross product (pseudo-z scalar) of two Vec2 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Scalar a.x*b.y - a.y*b.x.
     */
    inline float vec2cross(const Vec2& a, const Vec2& b)
    {
        return vec2cross(a.data(), b.data());
    }

    /**
     * \brief Returns a normalized copy of a 2D vector.
     * \param v Pointer to the vector to normalize.
     * \return Normalized vector or the zero vector when the input length is zero.
     */
    inline std::array<float, 2> vec2normalize(const float v[2])
    {
        const float len = std::sqrt(v[0] * v[0] + v[1] * v[1]);
        if (len == 0.f)
        {
            return { 0.f, 0.f };
        }
        return { v[0] / len, v[1] / len };
    }

    /**
     * \brief Returns a normalized copy of a Vec2.
     * \param v Input vector.
     * \return Normalized vector or the zero vector when the input length is zero.
     */
    inline Vec2 vec2normalize(const Vec2& v)
    {
        const auto n = vec2normalize(v.data());
        return { n[0], n[1] };
    }

    /**
     * \brief Returns the component-wise sum of two 2D vectors.
     * \param a Pointer to the left-hand vector.
     * \param b Pointer to the right-hand vector.
     * \return Component-wise addition a + b.
     */
    inline std::array<float, 2> vec2add(const float a[2], const float b[2])
    {
        return { a[0] + b[0], a[1] + b[1] };
    }

    /**
     * \brief Returns the component-wise sum of two Vec2 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Component-wise addition a + b.
     */
    inline Vec2 vec2add(const Vec2& a, const Vec2& b)
    {
        return { a.x + b.x, a.y + b.y };
    }

    /**
     * \brief Returns the scalar-multiplication of a 2D vector.
     * \param v Pointer to the input vector.
     * \param s Scalar multiplier.
     * \return Component-wise multiplication v * s.
     */
    inline std::array<float, 2> vec2mul(const float v[2], float s)
    {
        return { v[0] * s, v[1] * s };
    }

    /**
     * \brief Returns the scalar-multiplication of a 2D vector.
     * \param s Scalar multiplier.
     * \param v Pointer to the input vector.
     * \return Component-wise multiplication s * v.
     */
    inline std::array<float, 2> vec2mul(float s, const float v[2])
    {
        return vec2mul(v, s);
    }

    /**
     * \brief Returns the scalar-multiplication of a Vec2.
     * \param v Input vector.
     * \param s Scalar multiplier.
     * \return Component-wise multiplication v * s.
     */
    inline Vec2 vec2mul(const Vec2& v, float s)
    {
        return { v.x * s, v.y * s };
    }

    /**
     * \brief Returns the scalar-multiplication of a Vec2.
     * \param s Scalar multiplier.
     * \param v Input vector.
     * \return Component-wise multiplication s * v.
     */
    inline Vec2 vec2mul(float s, const Vec2& v)
    {
        return vec2mul(v, s);
    }

    /**
     * \brief Returns the component-wise difference of two 2D vectors.
     * \param a Pointer to the left-hand vector.
     * \param b Pointer to the right-hand vector.
     * \return Component-wise subtraction a - b.
     */
    inline std::array<float, 2> vec2sub(const float a[2], const float b[2])
    {
        return { a[0] - b[0], a[1] - b[1] };
    }

    /**
     * \brief Returns the component-wise difference of two Vec2 values.
     * \param a Left-hand vector.
     * \param b Right-hand vector.
     * \return Component-wise subtraction a - b.
     */
    inline Vec2 vec2sub(const Vec2& a, const Vec2& b)
    {
        return { a.x - b.x, a.y - b.y };
    }
} // namespace nfx::graphics::math
