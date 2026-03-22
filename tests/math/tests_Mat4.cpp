#include <doctest/doctest.h>

#include <nfx/graphics/math/Mat4.h>

#include <limits>
#include <numbers>

using namespace nfx::graphics::math;

namespace
{
    constexpr float EPSILON = 100 * std::numeric_limits<float>::epsilon();

    void checkIdentity(const float* m)
    {
        for (int i = 0; i < 16; ++i)
        {
            const float expected = (i % 5 == 0) ? 1.0f : 0.0f;
            CHECK(m[i] == doctest::Approx(expected).epsilon(EPSILON));
        }
    }

    void checkApproxEqual(const float* a, const float* b, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            CHECK(a[i] == doctest::Approx(b[i]).epsilon(EPSILON));
        }
    }
} // namespace

TEST_SUITE("Mat4")
{
    TEST_CASE("mat4Identity constructs identity matrix")
    {
        float m[16];
        mat4Identity(m);
        checkIdentity(m);
    }

    TEST_CASE("mat4Translate constructs translation matrix")
    {
        float m[16];
        mat4Translate(m, 5.0f, 10.0f, -3.0f);

        CHECK(m[0] == 1.0f);
        CHECK(m[5] == 1.0f);
        CHECK(m[10] == 1.0f);
        CHECK(m[15] == 1.0f);
        CHECK(m[12] == doctest::Approx(5.0f));
        CHECK(m[13] == doctest::Approx(10.0f));
        CHECK(m[14] == doctest::Approx(-3.0f));
    }

    TEST_CASE("mat4Scale constructs scaling matrix")
    {
        float m[16];
        mat4Scale(m, 2.0f, 3.0f, 0.5f);

        CHECK(m[0] == doctest::Approx(2.0f));
        CHECK(m[5] == doctest::Approx(3.0f));
        CHECK(m[10] == doctest::Approx(0.5f));
        CHECK(m[15] == 1.0f);
    }

    TEST_CASE("mat4RotateY rotates around Y axis")
    {
        float m[16];
        mat4RotateY(m, 0.0f); // 0 radians
        checkIdentity(m);

        mat4RotateY(m, static_cast<float>(std::numbers::pi) / 2.0f); // 90 degrees
        // cos(90°) ≈ 0, sin(90°) ≈ 1
        CHECK(m[0] == doctest::Approx(0.0f).epsilon(EPSILON));
        CHECK(m[2] == doctest::Approx(-1.0f).epsilon(EPSILON));
        CHECK(m[8] == doctest::Approx(1.0f).epsilon(EPSILON));
        CHECK(m[10] == doctest::Approx(0.0f).epsilon(EPSILON));
    }

    TEST_CASE("mat4RotateX rotates around X axis")
    {
        float m[16];
        mat4RotateX(m, 0.0f);
        checkIdentity(m);

        mat4RotateX(m, static_cast<float>(std::numbers::pi) / 2.0f);
        CHECK(m[5] == doctest::Approx(0.0f).epsilon(EPSILON));
        CHECK(m[6] == doctest::Approx(1.0f).epsilon(EPSILON));
        CHECK(m[9] == doctest::Approx(-1.0f).epsilon(EPSILON));
        CHECK(m[10] == doctest::Approx(0.0f).epsilon(EPSILON));
    }

    TEST_CASE("mat4RotateZ rotates around Z axis")
    {
        float m[16];
        mat4RotateZ(m, 0.0f);
        checkIdentity(m);

        mat4RotateZ(m, static_cast<float>(std::numbers::pi) / 2.0f);
        CHECK(m[0] == doctest::Approx(0.0f).epsilon(EPSILON));
        CHECK(m[1] == doctest::Approx(1.0f).epsilon(EPSILON));
        CHECK(m[4] == doctest::Approx(-1.0f).epsilon(EPSILON));
        CHECK(m[5] == doctest::Approx(0.0f).epsilon(EPSILON));
    }

    TEST_CASE("mat4Ortho constructs orthographic projection matrix")
    {
        float m[16];
        mat4Ortho(m, -10.0f, 10.0f, -5.0f, 5.0f, 0.1f, 100.0f);

        CHECK(m[0] == doctest::Approx(0.1f));           // 2/(10+10) = 0.1
        CHECK(m[5] == doctest::Approx(0.2f));           // 2/(5+5) = 0.2
        CHECK(m[10] == doctest::Approx(-2.0f / 99.9f)); // -2/(100-0.1)
        CHECK(m[15] == 1.0f);
        CHECK(m[12] == doctest::Approx(0.0f)); // -(10-10)/(10+10) = 0
        CHECK(m[13] == doctest::Approx(0.0f)); // -(5-5)/(5+5) = 0
    }

    TEST_CASE("mat4Ortho raw and Mat4 overload are equivalent")
    {
        float mRaw[16];
        Mat4 mMat4;
        mat4Ortho(mRaw, -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 10.0f);
        mat4Ortho(mMat4, -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 10.0f);

        checkApproxEqual(mRaw, mMat4.data(), 16);
    }

    TEST_CASE("mat4Perspective constructs projection matrix")
    {
        float m[16];
        mat4Perspective(m, static_cast<float>(std::numbers::pi) / 4.0f, 16.0f / 9.0f, 0.1f, 100.0f);

        CHECK(m[15] == 0.0f);
        CHECK(m[11] == -1.0f);
        CHECK(m[0] > 0.0f);
        CHECK(m[5] > 0.0f);
        CHECK(m[10] < 0.0f);
    }

    TEST_CASE("mat4LookAt constructs view matrix from position to center")
    {
        float m[16];
        mat4LookAt(m, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);

        // Homogeneous coordinate preserved
        CHECK(m[15] == 1.0f);
        // Matrix is orthonormal (rotation part)
        CHECK(m[0] * m[0] + m[1] * m[1] + m[2] * m[2] == doctest::Approx(1.0f).epsilon(EPSILON));
    }

    TEST_CASE("mat4Mul multiplies two matrices")
    {
        float identity[16], translate[16], result[16];
        mat4Identity(identity);
        mat4Translate(translate, 3.0f, 4.0f, 5.0f);
        mat4Mul(result, identity, translate);

        CHECK(result[12] == doctest::Approx(3.0f));
        CHECK(result[13] == doctest::Approx(4.0f));
        CHECK(result[14] == doctest::Approx(5.0f));
    }

    TEST_CASE("mat4Mul combined with scale and translate")
    {
        float scale[16], trans[16], result[16];
        mat4Scale(scale, 2.0f, 3.0f, 4.0f);
        mat4Translate(trans, 1.0f, 2.0f, 3.0f);
        mat4Mul(result, scale, trans);

        // Translation gets scaled
        CHECK(result[12] == doctest::Approx(2.0f));
        CHECK(result[13] == doctest::Approx(6.0f));
        CHECK(result[14] == doctest::Approx(12.0f));
    }
}
