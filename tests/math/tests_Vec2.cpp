#include <doctest/doctest.h>

#include <nfx/graphics/math/Vec2.h>

using namespace nfx::graphics::math;

TEST_SUITE("Vec2")
{
    TEST_CASE("vec2len raw overload returns Euclidean length")
    {
        const float v[2] = { 3.0f, 4.0f };
        CHECK(vec2len(v) == doctest::Approx(5.0f));
    }

    TEST_CASE("vec2len returns Euclidean length")
    {
        const Vec2 v{ 3.0f, 4.0f };
        CHECK(vec2len(v) == doctest::Approx(5.0f));
    }

    TEST_CASE("vec2len of zero vector is zero")
    {
        CHECK(vec2len(Vec2{}) == doctest::Approx(0.0f));
    }

    TEST_CASE("vec2dot returns scalar product")
    {
        const Vec2 a{ 1.0f, 2.0f };
        const Vec2 b{ 4.0f, -5.0f };
        CHECK(vec2dot(a, b) == doctest::Approx(-6.0f));
    }

    TEST_CASE("vec2dot raw overload returns scalar product")
    {
        const float a[2] = { 1.0f, 2.0f };
        const float b[2] = { 4.0f, -5.0f };
        CHECK(vec2dot(a, b) == doctest::Approx(-6.0f));
    }

    TEST_CASE("vec2dot of vector with itself equals squared length")
    {
        const Vec2 v{ -3.0f, 4.0f };
        const float l = vec2len(v);
        CHECK(vec2dot(v, v) == doctest::Approx(l * l));
    }

    TEST_CASE("vec2cross returns positive scalar for CCW pair")
    {
        const Vec2 x{ 1.0f, 0.0f };
        const Vec2 y{ 0.0f, 1.0f };
        CHECK(vec2cross(x, y) == doctest::Approx(1.0f));
    }

    TEST_CASE("vec2cross is anti-commutative")
    {
        const Vec2 a{ 2.0f, 3.0f };
        const Vec2 b{ 5.0f, -1.0f };
        CHECK(vec2cross(a, b) == doctest::Approx(-vec2cross(b, a)));
    }

    TEST_CASE("vec2cross raw overload returns scalar")
    {
        const float x[2] = { 1.0f, 0.0f };
        const float y[2] = { 0.0f, 1.0f };
        CHECK(vec2cross(x, y) == doctest::Approx(1.0f));
    }

    TEST_CASE("vec2cross of colinear vectors is zero")
    {
        const Vec2 a{ 2.0f, 2.0f };
        const Vec2 b{ 5.0f, 5.0f };
        CHECK(vec2cross(a, b) == doctest::Approx(0.0f));
    }

    TEST_CASE("vec2normalize returns unit vector")
    {
        const Vec2 v{ 3.0f, 4.0f };
        const Vec2 n = vec2normalize(v);
        CHECK(n.x == doctest::Approx(0.6f));
        CHECK(n.y == doctest::Approx(0.8f));
        CHECK(vec2len(n) == doctest::Approx(1.0f));
    }

    TEST_CASE("vec2normalize leaves unit vector unchanged")
    {
        const Vec2 v{ 0.0f, 1.0f };
        const Vec2 n = vec2normalize(v);
        CHECK(n.x == doctest::Approx(0.0f));
        CHECK(n.y == doctest::Approx(1.0f));
    }

    TEST_CASE("vec2normalize of zero vector returns zero vector")
    {
        const Vec2 n = vec2normalize(Vec2{});
        CHECK(n.x == doctest::Approx(0.0f));
        CHECK(n.y == doctest::Approx(0.0f));
    }

    TEST_CASE("vec2normalize raw overload returns normalized array")
    {
        const float v[2] = { 3.0f, 4.0f };
        const auto n = vec2normalize(v);
        CHECK(n[0] == doctest::Approx(0.6f));
        CHECK(n[1] == doctest::Approx(0.8f));
    }

    TEST_CASE("vec2normalize preserves direction")
    {
        const Vec2 v{ 3.0f, 4.0f };
        const Vec2 n = vec2normalize(v);
        CHECK(vec2dot(v, n) > 0.0f);
    }

    TEST_CASE("vec2add returns component-wise sum")
    {
        const Vec2 a{ 1.0f, -2.0f };
        const Vec2 b{ 3.0f, 5.0f };
        const Vec2 s = vec2add(a, b);
        CHECK(s.x == doctest::Approx(4.0f));
        CHECK(s.y == doctest::Approx(3.0f));
    }

    TEST_CASE("vec2add raw overload returns component-wise sum")
    {
        const float a[2] = { 1.0f, -2.0f };
        const float b[2] = { 3.0f, 5.0f };
        const auto s = vec2add(a, b);
        CHECK(s[0] == doctest::Approx(4.0f));
        CHECK(s[1] == doctest::Approx(3.0f));
    }

    TEST_CASE("vec2sub returns component-wise difference")
    {
        const Vec2 a{ 5.0f, 1.0f };
        const Vec2 b{ 2.0f, -3.0f };
        const Vec2 d = vec2sub(a, b);
        CHECK(d.x == doctest::Approx(3.0f));
        CHECK(d.y == doctest::Approx(4.0f));
    }

    TEST_CASE("vec2sub raw overload returns component-wise difference")
    {
        const float a[2] = { 5.0f, 1.0f };
        const float b[2] = { 2.0f, -3.0f };
        const auto d = vec2sub(a, b);
        CHECK(d[0] == doctest::Approx(3.0f));
        CHECK(d[1] == doctest::Approx(4.0f));
    }

    TEST_CASE("vec2mul returns component-wise scalar multiplication")
    {
        const Vec2 v{ 2.0f, -3.0f };
        const Vec2 m = vec2mul(v, 0.5f);
        CHECK(m.x == doctest::Approx(1.0f));
        CHECK(m.y == doctest::Approx(-1.5f));
    }

    TEST_CASE("vec2mul scalar-first overload matches vector-first overload")
    {
        const Vec2 v{ 2.0f, -3.0f };
        const Vec2 a = vec2mul(v, 0.5f);
        const Vec2 b = vec2mul(0.5f, v);
        CHECK(a.x == doctest::Approx(b.x));
        CHECK(a.y == doctest::Approx(b.y));
    }

    TEST_CASE("vec2mul raw overloads return component-wise scalar multiplication")
    {
        const float v[2] = { 2.0f, -3.0f };
        const auto a = vec2mul(v, 0.5f);
        const auto b = vec2mul(0.5f, v);
        CHECK(a[0] == doctest::Approx(1.0f));
        CHECK(a[1] == doctest::Approx(-1.5f));
        CHECK(a[0] == doctest::Approx(b[0]));
        CHECK(a[1] == doctest::Approx(b[1]));
    }

    TEST_CASE("Vec2 data and indexing are coherent")
    {
        Vec2 v{ 7.0f, 8.0f };
        CHECK(v.data()[0] == doctest::Approx(v.x));
        CHECK(v.data()[1] == doctest::Approx(v.y));
        CHECK(v[0] == doctest::Approx(v.x));
        CHECK(v[1] == doctest::Approx(v.y));

        v[0] = -1.0f;
        v[1] = -2.0f;
        CHECK(v.x == doctest::Approx(-1.0f));
        CHECK(v.y == doctest::Approx(-2.0f));
    }
}
