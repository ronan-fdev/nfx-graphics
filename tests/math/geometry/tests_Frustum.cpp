#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <cmath>

using namespace nfx::graphics::math;

TEST_SUITE("Frustum")
{
    TEST_CASE("fromViewProj extracts normalized planes")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 16.0f / 9.0f, 0.1f, 100.0f);

        Frustum f = Frustum::fromViewProj(proj);
        for (const auto& plane : f.planes)
        {
            const float len = std::sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
            CHECK(len == doctest::Approx(1.0f));
        }
    }

    TEST_CASE("containsPoint returns true for point inside")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        const float p[3] = { 0.0f, 0.0f, -1.0f };
        CHECK(f.containsPoint(p));
    }

    TEST_CASE("containsPoint returns false for point outside")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        const float p[3] = { 100.0f, 0.0f, -1.0f };
        CHECK(!f.containsPoint(p));
    }

    TEST_CASE("fromViewProj with non-identity view keeps camera-forward point inside")
    {
        Mat4 view = Mat4::identity();
        mat4LookAt(view, 2.0f, 1.0f, 5.0f, 2.0f, 1.0f, 0.0f);

        Mat4 proj = Mat4::identity();
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);

        Mat4 viewProj = Mat4::identity();
        mat4Mul(viewProj, proj, view);

        Frustum f = Frustum::fromViewProj(viewProj);

        const float inside[3] = { 2.0f, 1.0f, 0.0f };
        const float outside[3] = { 20.0f, 1.0f, 0.0f };

        CHECK(f.containsPoint(inside));
        CHECK(!f.containsPoint(outside));
    }

    TEST_CASE("sphere inside frustum intersects")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        Bounds::Sphere sphere{ { 0.0f, 0.0f, -3.0f }, 0.5f };
        CHECK(f.intersects(sphere));
    }

    TEST_CASE("sphere far outside frustum does not intersect")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        Bounds::Sphere sphere{ { 100.0f, 0.0f, -3.0f }, 0.5f };
        CHECK(!f.intersects(sphere));
    }

    TEST_CASE("aabb inside frustum intersects")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        Bounds::AABB aabb{ { -0.5f, -0.5f, -3.5f }, { 0.5f, 0.5f, -2.5f } };
        CHECK(f.intersects(aabb));
    }

    TEST_CASE("aabb outside frustum does not intersect")
    {
        Mat4 proj;
        mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        Frustum f = Frustum::fromViewProj(proj);
        Bounds::AABB aabb{ { 100.0f, -0.5f, -3.5f }, { 101.0f, 0.5f, -2.5f } };
        CHECK(!f.intersects(aabb));
    }
}
