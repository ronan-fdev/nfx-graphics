#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::math;

TEST_SUITE("Ray")
{
    TEST_CASE("at(0) returns origin")
    {
        Ray ray{ { 1.0f, 2.0f, 3.0f }, { 0.0f, 0.0f, -1.0f } };
        auto p = ray.at(0.0f);
        CHECK(p[0] == doctest::Approx(1.0f));
        CHECK(p[1] == doctest::Approx(2.0f));
        CHECK(p[2] == doctest::Approx(3.0f));
    }

    TEST_CASE("at(t) advances along direction")
    {
        Ray ray{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } };
        auto p = ray.at(5.0f);
        CHECK(p[2] == doctest::Approx(-5.0f));
    }
}

TEST_SUITE("Intersect AABB")
{
    TEST_CASE("Ray along -Z hits unit AABB at origin")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::AABB box{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        auto hit = intersect(ray, box);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(4.5f));
    }

    TEST_CASE("Ray misses AABB - no hit")
    {
        Ray ray{ { 0.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::AABB box{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        auto hit = intersect(ray, box);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray origin inside AABB - hits from inside")
    {
        Ray ray{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::AABB box{ { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f } };
        auto hit = intersect(ray, box);
        REQUIRE(hit.has_value());
        CHECK(hit->distance >= 0.0f);
    }

    TEST_CASE("Ray going away from AABB - no hit")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 1.0f } };
        Bounds::AABB box{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        auto hit = intersect(ray, box);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray hitting left face reports -X normal")
    {
        Ray ray{ { -5.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
        Bounds::AABB box{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        auto hit = intersect(ray, box);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(4.5f));
        CHECK(hit->normal[0] == doctest::Approx(-1.0f));
        CHECK(hit->normal[1] == doctest::Approx(0.0f));
        CHECK(hit->normal[2] == doctest::Approx(0.0f));
    }

    TEST_CASE("Non-normalized direction still yields correct AABB hit point")
    {
        Ray ray{ { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -2.0f } };
        Bounds::AABB box{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        auto hit = intersect(ray, box);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(4.75f));
        CHECK(hit->point[0] == doctest::Approx(0.0f));
        CHECK(hit->point[1] == doctest::Approx(0.0f));
        CHECK(hit->point[2] == doctest::Approx(0.5f));
    }
}

TEST_SUITE("Intersect Sphere")
{
    TEST_CASE("ray along -Z hits unit sphere at origin")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::Sphere sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        auto hit = intersect(ray, sphere);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(4.0f));
    }

    TEST_CASE("Ray misses sphere - no hit")
    {
        Ray ray{ { 0.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::Sphere sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        auto hit = intersect(ray, sphere);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray tangent to sphere - hits")
    {
        Ray ray{ { 1.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Bounds::Sphere sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        auto hit = intersect(ray, sphere);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(5.0f));
    }

    TEST_CASE("Ray going away from sphere - no hit")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 1.0f } };
        Bounds::Sphere sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        auto hit = intersect(ray, sphere);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray origin inside sphere exits with positive distance")
    {
        Ray ray{ { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
        Bounds::Sphere sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        auto hit = intersect(ray, sphere);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(1.0f));
        CHECK(hit->point[0] == doctest::Approx(1.0f));
        CHECK(hit->point[1] == doctest::Approx(0.0f));
        CHECK(hit->point[2] == doctest::Approx(0.0f));
        CHECK(hit->normal[0] == doctest::Approx(1.0f));
    }
}

TEST_SUITE("Intersect Triangle")
{
    TEST_CASE("ray hits triangle front face")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        const float v0[3] = { -1.0f, -1.0f, 0.0f };
        const float v1[3] = { 1.0f, -1.0f, 0.0f };
        const float v2[3] = { 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(5.0f));
    }

    TEST_CASE("Ray misses triangle")
    {
        Ray ray{ { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        const float v0[3] = { -1.0f, -1.0f, 0.0f };
        const float v1[3] = { 1.0f, -1.0f, 0.0f };
        const float v2[3] = { 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray parallel to triangle - no hit")
    {
        Ray ray{ { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
        const float v0[3] = { -1.0f, -1.0f, 0.0f };
        const float v1[3] = { 1.0f, -1.0f, 0.0f };
        const float v2[3] = { 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        CHECK(!hit.has_value());
    }

    TEST_CASE("Ray hits triangle from back face")
    {
        Ray ray{ { 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 1.0f } };
        const float v0[3] = { -1.0f, -1.0f, 0.0f };
        const float v1[3] = { 1.0f, -1.0f, 0.0f };
        const float v2[3] = { 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(5.0f));
        CHECK(hit->point[2] == doctest::Approx(0.0f));
        CHECK(hit->normal[2] == doctest::Approx(1.0f));
    }

    TEST_CASE("Non-normalized direction still yields correct triangle hit point")
    {
        Ray ray{ { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -2.0f } };
        const float v0[3] = { -1.0f, -1.0f, 0.0f };
        const float v1[3] = { 1.0f, -1.0f, 0.0f };
        const float v2[3] = { 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(5.0f));
        CHECK(hit->point[0] == doctest::Approx(0.0f));
        CHECK(hit->point[1] == doctest::Approx(0.0f));
        CHECK(hit->point[2] == doctest::Approx(0.0f));
    }

    TEST_CASE("Vec3 triangle overload matches float-pointer overload")
    {
        Ray ray{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f } };
        Vec3 v0{ -1.0f, -1.0f, 0.0f };
        Vec3 v1{ 1.0f, -1.0f, 0.0f };
        Vec3 v2{ 0.0f, 1.0f, 0.0f };
        auto hit = intersect(ray, v0, v1, v2);
        REQUIRE(hit.has_value());
        CHECK(hit->distance == doctest::Approx(5.0f));
        CHECK(hit->point[2] == doctest::Approx(0.0f));
    }
}

TEST_SUITE("ScreenToWorldRay")
{
    TEST_CASE("Mat4 overload matches pointer overload")
    {
        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };

        Mat4 view = Mat4::identity();
        Mat4 proj = Mat4::identity();
        mat4Perspective(proj, 1.0f, viewportSize[0] / viewportSize[1], 0.1f, 100.0f);

        const Ray a = screenToWorldRay(screenPos, viewportSize, view.data(), proj.data());
        const Ray b = screenToWorldRay(screenPos, viewportSize, view, proj);

        CHECK(b.origin[0] == doctest::Approx(a.origin[0]));
        CHECK(b.origin[1] == doctest::Approx(a.origin[1]));
        CHECK(b.origin[2] == doctest::Approx(a.origin[2]));
        CHECK(b.direction[0] == doctest::Approx(a.direction[0]));
        CHECK(b.direction[1] == doctest::Approx(a.direction[1]));
        CHECK(b.direction[2] == doctest::Approx(a.direction[2]));
    }

    TEST_CASE("Mat4 orthographic overload matches pointer overload")
    {
        const float screenPos[2] = { 320.0f, 180.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };

        Mat4 view = Mat4::identity();
        Mat4 proj = Mat4::identity();
        mat4Ortho(proj, -10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

        const Ray a = screenToWorldRay(screenPos, viewportSize, view.data(), proj.data(), true);
        const Ray b = screenToWorldRay(screenPos, viewportSize, view, proj, true);

        CHECK(b.origin[0] == doctest::Approx(a.origin[0]));
        CHECK(b.origin[1] == doctest::Approx(a.origin[1]));
        CHECK(b.origin[2] == doctest::Approx(a.origin[2]));
        CHECK(b.direction[0] == doctest::Approx(a.direction[0]));
        CHECK(b.direction[1] == doctest::Approx(a.direction[1]));
        CHECK(b.direction[2] == doctest::Approx(a.direction[2]));
    }
}
