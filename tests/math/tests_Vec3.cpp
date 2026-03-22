#include <doctest/doctest.h>

#include <nfx/graphics/math/Vec3.h>

using namespace nfx::graphics::math;

TEST_SUITE("Vec3")
{
    TEST_CASE("vec3len returns Euclidean length")
    {
        const float v[3] = { 3.0f, 4.0f, 12.0f };
        CHECK(vec3len(v) == doctest::Approx(13.0f));
    }

    TEST_CASE("vec3dot returns scalar product")
    {
        const float a[3] = { 1.0f, 2.0f, 3.0f };
        const float b[3] = { 4.0f, -5.0f, 6.0f };
        CHECK(vec3dot(a, b) == doctest::Approx(12.0f));
    }

    TEST_CASE("vec3cross follows right-handed orientation")
    {
        const float x[3] = { 1.0f, 0.0f, 0.0f };
        const float y[3] = { 0.0f, 1.0f, 0.0f };
        const auto z = vec3cross(x, y);

        CHECK(z[0] == doctest::Approx(0.0f));
        CHECK(z[1] == doctest::Approx(0.0f));
        CHECK(z[2] == doctest::Approx(1.0f));
    }

    TEST_CASE("vec3cross is anti-commutative")
    {
        const float x[3] = { 1.0f, 0.0f, 0.0f };
        const float y[3] = { 0.0f, 1.0f, 0.0f };
        const auto xy = vec3cross(x, y);
        const auto yx = vec3cross(y, x);

        CHECK(xy[0] == doctest::Approx(-yx[0]));
        CHECK(xy[1] == doctest::Approx(-yx[1]));
        CHECK(xy[2] == doctest::Approx(-yx[2]));
    }

    TEST_CASE("vec3normalize returns unit vector")
    {
        const float v[3] = { 0.0f, 3.0f, 4.0f };
        const auto n = vec3normalize(v);

        CHECK(n[0] == doctest::Approx(0.0f));
        CHECK(n[1] == doctest::Approx(0.6f));
        CHECK(n[2] == doctest::Approx(0.8f));
        CHECK(vec3len(n.data()) == doctest::Approx(1.0f));
    }

    TEST_CASE("vec3dot of vector with itself equals squared length")
    {
        const float v[3] = { -2.0f, 3.0f, 6.0f };
        const float l = vec3len(v);
        CHECK(vec3dot(v, v) == doctest::Approx(l * l));
    }

    TEST_CASE("vec3normalize leaves unit vector unchanged")
    {
        const float v[3] = { 0.0f, 0.0f, 1.0f };
        const auto n = vec3normalize(v);

        CHECK(n[0] == doctest::Approx(0.0f));
        CHECK(n[1] == doctest::Approx(0.0f));
        CHECK(n[2] == doctest::Approx(1.0f));
    }

    TEST_CASE("vec3normalize of zero vector returns zero vector")
    {
        const float zero[3] = { 0.0f, 0.0f, 0.0f };
        const auto n = vec3normalize(zero);

        CHECK(n[0] == doctest::Approx(0.0f));
        CHECK(n[1] == doctest::Approx(0.0f));
        CHECK(n[2] == doctest::Approx(0.0f));
    }

    TEST_CASE("vec3sub returns component-wise difference")
    {
        const float a[3] = { 5.0f, 1.0f, -2.0f };
        const float b[3] = { 2.0f, -3.0f, 4.0f };
        const auto d = vec3sub(a, b);

        CHECK(d[0] == doctest::Approx(3.0f));
        CHECK(d[1] == doctest::Approx(4.0f));
        CHECK(d[2] == doctest::Approx(-6.0f));
    }

    TEST_CASE("vec3len of zero vector is zero")
    {
        const float zero[3] = { 0.0f, 0.0f, 0.0f };
        CHECK(vec3len(zero) == doctest::Approx(0.0f));
    }
}
