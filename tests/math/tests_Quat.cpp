#include <doctest/doctest.h>

#include <nfx/graphics/math/Quat.h>

#include <numbers>

using namespace nfx::graphics::math;

TEST_SUITE("Quat")
{
    TEST_CASE("quatAngleAxis with zero angle returns identity")
    {
        const Quat q = quatAngleAxis(0.0f, 0.0f, 1.0f, 0.0f);
        CHECK(q.w == doctest::Approx(1.0f));
        CHECK(q.x == doctest::Approx(0.0f));
        CHECK(q.y == doctest::Approx(0.0f));
        CHECK(q.z == doctest::Approx(0.0f));
    }

    TEST_CASE("quatNormalize returns unit quaternion")
    {
        const Quat q = quatNormalize({ 2.0f, 0.0f, 0.0f, 0.0f });
        CHECK(q.w == doctest::Approx(1.0f));
        CHECK(q.x == doctest::Approx(0.0f));
        CHECK(q.y == doctest::Approx(0.0f));
        CHECK(q.z == doctest::Approx(0.0f));
    }

    TEST_CASE("quatNormalize of zero quaternion returns identity")
    {
        const Quat q = quatNormalize({ 0.0f, 0.0f, 0.0f, 0.0f });
        CHECK(q.w == doctest::Approx(1.0f));
        CHECK(q.x == doctest::Approx(0.0f));
        CHECK(q.y == doctest::Approx(0.0f));
        CHECK(q.z == doctest::Approx(0.0f));
    }

    TEST_CASE("quatRotate around Y by 90 degrees maps +X to -Z")
    {
        const Quat q = quatAngleAxis(std::numbers::pi_v<float> * 0.5f, 0.0f, 1.0f, 0.0f);
        const float v[3] = { 1.0f, 0.0f, 0.0f };
        float out[3] = {};

        quatRotate(q, v, out);

        CHECK(out[0] == doctest::Approx(0.0f).epsilon(1e-5f));
        CHECK(out[1] == doctest::Approx(0.0f).epsilon(1e-5f));
        CHECK(out[2] == doctest::Approx(-1.0f).epsilon(1e-5f));
    }

    TEST_CASE("quatMul composition matches sequential rotations")
    {
        const Quat qx = quatAngleAxis(std::numbers::pi_v<float> * 0.5f, 1.0f, 0.0f, 0.0f);
        const Quat qy = quatAngleAxis(std::numbers::pi_v<float> * 0.5f, 0.0f, 1.0f, 0.0f);
        const Quat combined = quatNormalize(quatMul(qy, qx));

        const float v[3] = { 0.0f, 0.0f, 1.0f };
        float step1[3] = {};
        float sequential[3] = {};
        float composed[3] = {};

        quatRotate(qx, v, step1);
        quatRotate(qy, step1, sequential);
        quatRotate(combined, v, composed);

        CHECK(composed[0] == doctest::Approx(sequential[0]).epsilon(1e-5f));
        CHECK(composed[1] == doctest::Approx(sequential[1]).epsilon(1e-5f));
        CHECK(composed[2] == doctest::Approx(sequential[2]).epsilon(1e-5f));
    }

    TEST_CASE("quatToMat4 identity quaternion produces identity matrix")
    {
        const Quat q = { 1.0f, 0.0f, 0.0f, 0.0f };
        Mat4 m;
        quatToMat4(q, m);

        CHECK(m[0] == doctest::Approx(1.0f));
        CHECK(m[5] == doctest::Approx(1.0f));
        CHECK(m[10] == doctest::Approx(1.0f));
        CHECK(m[15] == doctest::Approx(1.0f));
        CHECK(m[1] == doctest::Approx(0.0f));
        CHECK(m[2] == doctest::Approx(0.0f));
        CHECK(m[4] == doctest::Approx(0.0f));
        CHECK(m[6] == doctest::Approx(0.0f));
        CHECK(m[8] == doctest::Approx(0.0f));
        CHECK(m[9] == doctest::Approx(0.0f));
    }

    TEST_CASE("quatToMat4 Y-90 rotation maps +X column to -Z")
    {
        const Quat q = quatAngleAxis(std::numbers::pi_v<float> * 0.5f, 0.0f, 1.0f, 0.0f);
        Mat4 m;
        quatToMat4(q, m);

        // First column of rotation matrix = where +X goes
        CHECK(m[0] == doctest::Approx(0.0f).epsilon(1e-5f));  // x'
        CHECK(m[1] == doctest::Approx(0.0f).epsilon(1e-5f));  // y'
        CHECK(m[2] == doctest::Approx(-1.0f).epsilon(1e-5f)); // z'
    }
}
