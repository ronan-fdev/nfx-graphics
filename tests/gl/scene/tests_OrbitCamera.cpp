#include <doctest/doctest.h>

#include <nfx/graphics/gl/scene/cameras/OrbitCamera.h>

#include <cstddef>
#include <cmath>

using namespace nfx::graphics::gl;
namespace math = nfx::graphics::math;

TEST_SUITE("Camera")
{
    TEST_CASE("GpuData layout is std140-friendly")
    {
        CHECK(sizeof(Camera::GpuData) == 224);
        CHECK(offsetof(Camera::GpuData, view) == 0);
        CHECK(offsetof(Camera::GpuData, proj) == 64);
        CHECK(offsetof(Camera::GpuData, viewProj) == 128);
        CHECK(offsetof(Camera::GpuData, position) == 192);
        CHECK(offsetof(Camera::GpuData, direction) == 208);
    }

    TEST_CASE("toGpuData copies matrices and viewProj stores proj * view")
    {
        float view[16], proj[16], viewProj[16];
        math::mat4LookAt(view, 3.f, 2.f, 5.f, 0.f, 0.f, 0.f);
        math::mat4Perspective(proj, 0.785f, 1.f, 0.1f, 100.f);
        math::mat4Mul(viewProj, proj, view);

        const float position[3] = { 3.f, 2.f, 5.f };
        const float direction[3] = { 0.f, 0.f, -1.f };

        const auto gpu = Camera::toGpuData(view, proj, viewProj, position, direction);

        for (int i = 0; i < 16; ++i)
        {
            CHECK(gpu.view[i] == doctest::Approx(view[i]));
            CHECK(gpu.proj[i] == doctest::Approx(proj[i]));
        }

        // viewProj must equal proj * view - verifies the caller's precomputation contract
        float expected[16];
        math::mat4Mul(expected, proj, view);
        for (int i = 0; i < 16; ++i)
        {
            CHECK(gpu.viewProj[i] == doctest::Approx(expected[i]).epsilon(1e-5f));
        }

        CHECK(gpu.position[0] == doctest::Approx(3.f));
        CHECK(gpu.position[1] == doctest::Approx(2.f));
        CHECK(gpu.position[2] == doctest::Approx(5.f));
        CHECK(gpu.direction[0] == doctest::Approx(0.f));
        CHECK(gpu.direction[1] == doctest::Approx(0.f));
        CHECK(gpu.direction[2] == doctest::Approx(-1.f));
        CHECK(gpu._pad0 == doctest::Approx(0.f));
        CHECK(gpu._pad1 == doctest::Approx(0.f));
    }

    TEST_CASE("toGpuData typed overload matches raw overload")
    {
        math::Mat4 view, proj, viewProj;
        math::mat4LookAt(view, 3.f, 2.f, 5.f, 0.f, 0.f, 0.f);
        math::mat4Perspective(proj, 0.785f, 1.f, 0.1f, 100.f);
        math::mat4Mul(viewProj, proj, view);

        const math::Vec3 position{ 3.f, 2.f, 5.f };
        const math::Vec3 direction{ 0.f, 0.f, -1.f };

        const auto rawGpu =
            Camera::toGpuData(view.data(), proj.data(), viewProj.data(), position.data(), direction.data());
        const auto typedGpu = Camera::toGpuData(view, proj, viewProj, position, direction);

        for (int i = 0; i < 16; ++i)
        {
            CHECK(typedGpu.view[i] == doctest::Approx(rawGpu.view[i]));
            CHECK(typedGpu.proj[i] == doctest::Approx(rawGpu.proj[i]));
            CHECK(typedGpu.viewProj[i] == doctest::Approx(rawGpu.viewProj[i]));
        }
        CHECK(typedGpu.position[0] == doctest::Approx(rawGpu.position[0]));
        CHECK(typedGpu.position[1] == doctest::Approx(rawGpu.position[1]));
        CHECK(typedGpu.position[2] == doctest::Approx(rawGpu.position[2]));
        CHECK(typedGpu.direction[0] == doctest::Approx(rawGpu.direction[0]));
        CHECK(typedGpu.direction[1] == doctest::Approx(rawGpu.direction[1]));
        CHECK(typedGpu.direction[2] == doctest::Approx(rawGpu.direction[2]));
    }

    TEST_CASE("member toGpuData packs camera CPU state")
    {
        Camera cam{};

        for (int i = 0; i < 16; ++i)
        {
            cam.view[i] = static_cast<float>(i + 1);
            cam.proj[i] = static_cast<float>(101 + i);
            cam.viewProj[i] = static_cast<float>(201 + i);
        }
        cam.position[0] = 3.f;
        cam.position[1] = -2.f;
        cam.position[2] = 7.f;
        cam.direction[0] = 0.25f;
        cam.direction[1] = -0.5f;
        cam.direction[2] = 0.75f;

        const auto gpu = cam.toGpuData();

        for (int i = 0; i < 16; ++i)
        {
            CHECK(gpu.view[i] == doctest::Approx(cam.view[i]));
            CHECK(gpu.proj[i] == doctest::Approx(cam.proj[i]));
            CHECK(gpu.viewProj[i] == doctest::Approx(cam.viewProj[i]));
        }
        CHECK(gpu.position[0] == doctest::Approx(cam.position[0]));
        CHECK(gpu.position[1] == doctest::Approx(cam.position[1]));
        CHECK(gpu.position[2] == doctest::Approx(cam.position[2]));
        CHECK(gpu.direction[0] == doctest::Approx(cam.direction[0]));
        CHECK(gpu.direction[1] == doctest::Approx(cam.direction[1]));
        CHECK(gpu.direction[2] == doctest::Approx(cam.direction[2]));
        CHECK(gpu._pad0 == doctest::Approx(0.f));
        CHECK(gpu._pad1 == doctest::Approx(0.f));
    }
}

TEST_SUITE("OrbitCamera")
{
    TEST_CASE("default state places eye along +Z at distance from target")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = 0.f;
        // orient = identity -> offsetLocal {0, 0, distance} is unchanged -> eye = {0, 0, 8}
        const auto gpu = cam.toGpuData(std::numbers::pi_v<float> / 2.f, 1.f);

        CHECK(gpu.position[0] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.position[1] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.position[2] == doctest::Approx(cam.distance).epsilon(1e-4f));
        CHECK(gpu.direction[0] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.direction[1] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.direction[2] == doctest::Approx(-1.f).epsilon(1e-4f));
    }

    TEST_CASE("orbit updates azimuth and elevation by orbitSpeed * delta")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = 0.f;

        cam.orbit(100.f, 50.f);

        CHECK(cam.azimuth == doctest::Approx(-100.f * cam.orbitSpeed));
        CHECK(cam.elevation == doctest::Approx(50.f * cam.orbitSpeed));
    }

    TEST_CASE("pan translates target in current view plane")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = 0.f;
        cam.distance = 8.f;
        cam.target[0] = 0.f;
        cam.target[1] = 0.f;
        cam.target[2] = 0.f;

        cam.pan(10.f, 0.f);
        CHECK(cam.target[0] == doctest::Approx(-10.f * cam.distance * cam.panSpeed));
        CHECK(cam.target[1] == doctest::Approx(0.f));
        CHECK(cam.target[2] == doctest::Approx(0.f));
    }

    TEST_CASE("pan amount scales with distance")
    {
        OrbitCamera nearCam;
        nearCam.distance = 2.f;
        nearCam.target[0] = nearCam.target[1] = nearCam.target[2] = 0.f;
        nearCam.pan(10.f, 0.f);
        const float nearDeltaX = std::fabs(nearCam.target[0]);

        OrbitCamera farCam;
        farCam.distance = 8.f;
        farCam.target[0] = farCam.target[1] = farCam.target[2] = 0.f;
        farCam.pan(10.f, 0.f);
        const float farDeltaX = std::fabs(farCam.target[0]);

        CHECK(farDeltaX == doctest::Approx(nearDeltaX * 4.0f));
    }

    TEST_CASE("pan vertical input moves target on +Y in default orientation")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = 0.f;
        cam.distance = 8.f;
        cam.target[0] = cam.target[1] = cam.target[2] = 0.f;

        cam.pan(0.f, 10.f);

        CHECK(cam.target[0] == doctest::Approx(0.f));
        CHECK(cam.target[1] == doctest::Approx(10.f * cam.distance * cam.panSpeed));
        CHECK(cam.target[2] == doctest::Approx(0.f));
    }

    TEST_CASE("zoom reduces distance proportionally to current distance")
    {
        OrbitCamera cam;
        cam.distance = 8.f;

        cam.zoom(1.f); // 8 - 1 * 8 * 0.1 = 7.2
        CHECK(cam.distance == doctest::Approx(7.2f));
    }

    TEST_CASE("zoom is clamped to DistanceMin and DistanceMax")
    {
        OrbitCamera cam;

        cam.distance = 1.f;
        cam.zoom(1e6f);
        CHECK(cam.distance == doctest::Approx(OrbitCamera::DistanceMin));

        cam.distance = 9000.f;
        cam.zoom(-1e6f);
        CHECK(cam.distance == doctest::Approx(OrbitCamera::DistanceMax));
    }

    TEST_CASE("azimuth pi/2 rotates eye to +X axis")
    {
        OrbitCamera cam;
        cam.azimuth = std::numbers::pi_v<float> / 2.f;
        cam.elevation = 0.f;
        cam.distance = 5.f;
        // quatAngleAxis(π/2, 0,1,0) applied to {0,0,5} -> {5, 0, 0}
        const auto gpu = cam.toGpuData(std::numbers::pi_v<float> / 2.f, 1.f);

        CHECK(gpu.position[0] == doctest::Approx(5.f).epsilon(1e-4f));
        CHECK(gpu.position[1] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.position[2] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.direction[0] == doctest::Approx(-1.f).epsilon(1e-4f));
        CHECK(gpu.direction[1] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.direction[2] == doctest::Approx(0.f).epsilon(1e-4f));
    }

    TEST_CASE("elevation pi/6 lifts eye above horizon")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = std::numbers::pi_v<float> / 6.f;
        cam.distance = 1.f;
        // el = quatAngleAxis(-π/6, 1,0,0) applied to {0,0,1}
        // rotating around -X by π/6: y' = sin(π/6)*1 = 0.5, z' = cos(π/6)*1 ≈ 0.866
        const auto gpu = cam.toGpuData(std::numbers::pi_v<float> / 2.f, 1.f);

        CHECK(gpu.position[0] == doctest::Approx(0.f).epsilon(1e-4f));
        CHECK(gpu.position[1] == doctest::Approx(std::sin(std::numbers::pi_v<float> / 6.f)).epsilon(1e-4f));
        CHECK(gpu.position[2] == doctest::Approx(std::cos(std::numbers::pi_v<float> / 6.f)).epsilon(1e-4f));
    }

    TEST_CASE("non-zero target offsets eye position")
    {
        OrbitCamera cam;
        cam.azimuth = 0.f;
        cam.elevation = 0.f;
        cam.distance = 4.f;
        cam.target[0] = 1.f;
        cam.target[1] = 2.f;
        cam.target[2] = 3.f;

        const auto gpu = cam.toGpuData(std::numbers::pi_v<float> / 2.f, 1.f);

        CHECK(gpu.position[0] == doctest::Approx(1.f).epsilon(1e-4f));
        CHECK(gpu.position[1] == doctest::Approx(2.f).epsilon(1e-4f));
        CHECK(gpu.position[2] == doctest::Approx(7.f).epsilon(1e-4f)); // target.z + distance
    }

    TEST_CASE("direction is a unit vector")
    {
        OrbitCamera cam;
        cam.azimuth = 0.3f;
        cam.elevation = 0.7f;
        cam.distance = 6.f;

        const auto gpu = cam.toGpuData(1.f, 1.6f);

        const float len = std::sqrt(
            gpu.direction[0] * gpu.direction[0] + gpu.direction[1] * gpu.direction[1] +
            gpu.direction[2] * gpu.direction[2]);
        CHECK(len == doctest::Approx(1.f).epsilon(1e-5f));
    }

    TEST_CASE("toGpuData remains finite for extreme aspect ratios")
    {
        OrbitCamera cam;
        const auto gpuNarrow = cam.toGpuData(0.9f, 0.05f);
        const auto gpuWide = cam.toGpuData(0.9f, 20.0f);

        for (int i = 0; i < 16; ++i)
        {
            CHECK(std::isfinite(gpuNarrow.proj[i]));
            CHECK(std::isfinite(gpuWide.proj[i]));
        }
    }

    TEST_CASE("toGpuData keeps viewProj consistent with proj * view")
    {
        OrbitCamera cam;
        cam.azimuth = 0.33f;
        cam.elevation = 0.21f;
        cam.distance = 6.5f;
        cam.target[0] = 1.5f;
        cam.target[1] = -0.3f;
        cam.target[2] = 2.0f;

        const auto gpu = cam.toGpuData(0.95f, 1.77f, 0.2f, 250.f);

        float expected[16]{};
        math::mat4Mul(expected, gpu.proj, gpu.view);

        for (int i = 0; i < 16; ++i)
        {
            CHECK(gpu.viewProj[i] == doctest::Approx(expected[i]).epsilon(1e-5f));
        }
    }

    TEST_CASE("toGpuData remains finite for borderline valid near/far inputs")
    {
        OrbitCamera cam;
        const auto gpu = cam.toGpuData(0.9f, 1e-4f, 1e-4f, 2e-4f);

        for (int i = 0; i < 16; ++i)
        {
            CHECK(std::isfinite(gpu.proj[i]));
            CHECK(std::isfinite(gpu.viewProj[i]));
        }
    }

    TEST_CASE("toGpuData at minimum distance keeps direction normalized")
    {
        OrbitCamera cam;
        cam.distance = OrbitCamera::DistanceMin;

        const auto gpu = cam.toGpuData(1.0f, 1.0f);
        const float len = std::sqrt(
            gpu.direction[0] * gpu.direction[0] + gpu.direction[1] * gpu.direction[1] +
            gpu.direction[2] * gpu.direction[2]);
        CHECK(len == doctest::Approx(1.f).epsilon(1e-5f));
    }
}
