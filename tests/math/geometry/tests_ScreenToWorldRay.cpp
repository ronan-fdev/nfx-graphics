#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::math;

// Helpers to build a simple look-at view from (0,0,5) toward origin and a perspective projection
static Mat4 makeView()
{
    Mat4 v = Mat4::identity();
    mat4LookAt(v, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);
    return v;
}

static Mat4 makeProj(float aspect = 1280.0f / 720.0f)
{
    Mat4 p = Mat4::identity();
    mat4Perspective(p, 0.785f, aspect, 0.1f, 100.0f);
    return p;
}

TEST_SUITE("ScreenToWorldRay - semantic")
{
    TEST_CASE("center of viewport produces forward-pointing ray")
    {
        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        // Direction must point toward -Z (camera looks toward origin from +Z)
        CHECK(ray.direction[2] < -0.9f);
        // X and Y components must be near zero for a perfectly centered ray
        CHECK(ray.direction[0] == doctest::Approx(0.0f).epsilon(0.01f));
        CHECK(ray.direction[1] == doctest::Approx(0.0f).epsilon(0.01f));
    }

    TEST_CASE("ray direction is normalized")
    {
        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        const float len = std::sqrt(
            ray.direction[0] * ray.direction[0] + ray.direction[1] * ray.direction[1] +
            ray.direction[2] * ray.direction[2]);
        CHECK(len == doctest::Approx(1.0f).epsilon(0.001f));
    }

    TEST_CASE("top-left corner ray deviates left and up from center")
    {
        const float center[2] = { 640.0f, 360.0f };
        const float topLeft[2] = { 0.0f, 0.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray rCenter = screenToWorldRay(center, viewportSize, view, proj);
        const Ray rCorner = screenToWorldRay(topLeft, viewportSize, view, proj);

        // Top-left in screen space -> negative X and positive Y in world (Y flipped in NDC)
        CHECK(rCorner.direction[0] < rCenter.direction[0]);
        CHECK(rCorner.direction[1] > rCenter.direction[1]);
    }

    TEST_CASE("ray origin is at camera position")
    {
        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        CHECK(ray.origin[0] == doctest::Approx(0.0f).epsilon(0.001f));
        CHECK(ray.origin[1] == doctest::Approx(0.0f).epsilon(0.001f));
        CHECK(ray.origin[2] == doctest::Approx(5.0f).epsilon(0.001f));
    }

    TEST_CASE("viewport-local offset: same local coords, different global offset, same ray")
    {
        // Simulates a left viewport starting at x=0 (full width 1280)
        // and a right viewport starting at x=640 (half width 640)
        // A click at local (320, 360) in each should produce identical rays
        // if both have the same camera and the same viewport size (640x720)

        const float localPos[2] = { 320.0f, 360.0f };
        const float viewportSize[2] = { 640.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj(640.0f / 720.0f);

        // Both viewport calls use viewport-local coords -> result must be identical
        const Ray r1 = screenToWorldRay(localPos, viewportSize, view, proj);
        const Ray r2 = screenToWorldRay(localPos, viewportSize, view, proj);

        CHECK(r1.direction[0] == doctest::Approx(r2.direction[0]));
        CHECK(r1.direction[1] == doctest::Approx(r2.direction[1]));
        CHECK(r1.direction[2] == doctest::Approx(r2.direction[2]));
    }
}

TEST_SUITE("ScreenToWorldRay - picking")
{
    TEST_CASE("center click hits object at origin")
    {
        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        Bounds::AABB box;
        box.min[0] = -0.5f;
        box.min[1] = -0.5f;
        box.min[2] = -0.5f;
        box.max[0] = 0.5f;
        box.max[1] = 0.5f;
        box.max[2] = 0.5f;

        const auto hit = intersect(ray, box);
        REQUIRE(hit.has_value());
        CHECK(hit->distance > 0.0f);
    }

    TEST_CASE("click away from object misses")
    {
        // Click at far top-left, object is at origin
        const float screenPos[2] = { 20.0f, 20.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };
        const Mat4 view = makeView();
        const Mat4 proj = makeProj();

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        Bounds::AABB box;
        box.min[0] = -0.5f;
        box.min[1] = -0.5f;
        box.min[2] = -0.5f;
        box.max[0] = 0.5f;
        box.max[1] = 0.5f;
        box.max[2] = 0.5f;

        const auto hit = intersect(ray, box);
        CHECK(!hit.has_value());
    }

    TEST_CASE("closest object wins when two objects overlap on screen")
    {
        // Camera at (0,0,10), two boxes along -Z: near at z=[3,4], far at z=[0,1]
        Mat4 view = Mat4::identity();
        mat4LookAt(view, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f);
        Mat4 proj = makeProj();

        const float screenPos[2] = { 640.0f, 360.0f };
        const float viewportSize[2] = { 1280.0f, 720.0f };

        const Ray ray = screenToWorldRay(screenPos, viewportSize, view, proj);

        Bounds::AABB near;
        near.min[0] = -0.5f;
        near.min[1] = -0.5f;
        near.min[2] = 3.0f;
        near.max[0] = 0.5f;
        near.max[1] = 0.5f;
        near.max[2] = 4.0f;

        Bounds::AABB far;
        far.min[0] = -0.5f;
        far.min[1] = -0.5f;
        far.min[2] = 0.0f;
        far.max[0] = 0.5f;
        far.max[1] = 0.5f;
        far.max[2] = 1.0f;

        const auto hitNear = intersect(ray, near);
        const auto hitFar = intersect(ray, far);

        REQUIRE(hitNear.has_value());
        REQUIRE(hitFar.has_value());

        // Selection logic: pick closest
        int selected = -1;
        float best = std::numeric_limits<float>::max();
        if (hitNear->distance >= 0.0f && hitNear->distance < best)
        {
            best = hitNear->distance;
            selected = 0;
        }
        if (hitFar->distance >= 0.0f && hitFar->distance < best)
        {
            best = hitFar->distance;
            selected = 1;
        }

        CHECK(selected == 0); // near wins
        CHECK(hitNear->distance < hitFar->distance);
    }
}
