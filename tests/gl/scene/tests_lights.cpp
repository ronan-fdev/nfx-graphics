#include <doctest/doctest.h>

#include <nfx/graphics/gl/scene/lights/AmbientLight.h>
#include <nfx/graphics/gl/scene/lights/DirectionalLight.h>

#include <cstddef>

using namespace nfx::graphics::gl;
namespace math = nfx::graphics::math;

TEST_SUITE("AmbientLight")
{
    TEST_CASE("GpuData layout size is std140-friendly")
    {
        CHECK(sizeof(AmbientLight::GpuData) == 16);
        CHECK(offsetof(AmbientLight::GpuData, colorIntensity) == 0);
    }

    TEST_CASE("Default constructor initializes with sane defaults")
    {
        AmbientLight light;
        CHECK(light.color[0] == doctest::Approx(0.05f));
        CHECK(light.color[1] == doctest::Approx(0.05f));
        CHECK(light.color[2] == doctest::Approx(0.05f));
        CHECK(light.intensity == doctest::Approx(1.0f));
    }

    TEST_CASE("toGpuData packs color and intensity")
    {
        AmbientLight light;
        light.color[0] = 0.25f;
        light.color[1] = 0.5f;
        light.color[2] = 0.75f;
        light.intensity = 2.0f;

        const auto gpu = light.toGpuData();
        CHECK(gpu.colorIntensity[0] == doctest::Approx(0.25f));
        CHECK(gpu.colorIntensity[1] == doctest::Approx(0.5f));
        CHECK(gpu.colorIntensity[2] == doctest::Approx(0.75f));
        CHECK(gpu.colorIntensity[3] == doctest::Approx(2.0f));
    }

    TEST_CASE("Zero intensity produces black light")
    {
        AmbientLight light;
        light.intensity = 0.0f;
        const auto gpu = light.toGpuData();
        CHECK(gpu.colorIntensity[3] == doctest::Approx(0.0f));
    }

    TEST_CASE("toGpuData raw and typed overloads are equivalent")
    {
        const float rawColor[3] = { 0.11f, 0.22f, 0.33f };
        const math::Vec3 typedColor{ 0.11f, 0.22f, 0.33f };
        const float intensity = 1.7f;

        const auto rawGpu = AmbientLight::toGpuData(rawColor, intensity);
        const auto typedGpu = AmbientLight::toGpuData(typedColor, intensity);

        CHECK(typedGpu.colorIntensity[0] == doctest::Approx(rawGpu.colorIntensity[0]));
        CHECK(typedGpu.colorIntensity[1] == doctest::Approx(rawGpu.colorIntensity[1]));
        CHECK(typedGpu.colorIntensity[2] == doctest::Approx(rawGpu.colorIntensity[2]));
        CHECK(typedGpu.colorIntensity[3] == doctest::Approx(rawGpu.colorIntensity[3]));
    }
}

TEST_SUITE("DirectionalLight")
{
    TEST_CASE("GpuData layout size is std140-friendly")
    {
        CHECK(sizeof(DirectionalLight::GpuData) == 32);
        CHECK(offsetof(DirectionalLight::GpuData, direction) == 0);
        CHECK(offsetof(DirectionalLight::GpuData, colorIntensity) == 16);
    }

    TEST_CASE("Default constructor initializes with sane defaults")
    {
        DirectionalLight light;
        CHECK(light.color[0] == doctest::Approx(1.0f));
        CHECK(light.color[1] == doctest::Approx(1.0f));
        CHECK(light.color[2] == doctest::Approx(1.0f));
        CHECK(light.intensity == doctest::Approx(1.0f));
    }

    TEST_CASE("toGpuData packs direction color and intensity")
    {
        DirectionalLight light;
        light.color[0] = 0.2f;
        light.color[1] = 0.4f;
        light.color[2] = 0.6f;
        light.intensity = 3.0f;

        const float direction[3] = { 0.0f, -1.0f, 0.0f };
        const auto gpu = light.toGpuData(direction);

        CHECK(gpu.direction[0] == doctest::Approx(0.0f));
        CHECK(gpu.direction[1] == doctest::Approx(-1.0f));
        CHECK(gpu.direction[2] == doctest::Approx(0.0f));
        CHECK(gpu.direction[3] == doctest::Approx(0.0f));
        CHECK(gpu.colorIntensity[0] == doctest::Approx(0.2f));
        CHECK(gpu.colorIntensity[1] == doctest::Approx(0.4f));
        CHECK(gpu.colorIntensity[2] == doctest::Approx(0.6f));
        CHECK(gpu.colorIntensity[3] == doctest::Approx(3.0f));
    }

    TEST_CASE("toGpuData w component always zero")
    {
        DirectionalLight light;
        const float direction[3] = { 1.0f, 0.0f, 0.0f };
        const auto gpu = light.toGpuData(direction);
        CHECK(gpu.direction[0] == doctest::Approx(1.0f));
        CHECK(gpu.direction[1] == doctest::Approx(0.0f));
        CHECK(gpu.direction[2] == doctest::Approx(0.0f));
        CHECK(gpu.direction[3] == doctest::Approx(0.0f));
    }

    TEST_CASE("toGpuData raw and typed direction overloads are equivalent")
    {
        DirectionalLight light;
        light.color[0] = 0.7f;
        light.color[1] = 0.5f;
        light.color[2] = 0.3f;
        light.intensity = 2.2f;

        const float rawDirection[3] = { 0.25f, -0.5f, 0.75f };
        const math::Vec3 typedDirection{ 0.25f, -0.5f, 0.75f };

        const auto rawGpu = light.toGpuData(rawDirection);
        const auto typedGpu = light.toGpuData(typedDirection);

        for (int i = 0; i < 4; ++i)
        {
            CHECK(typedGpu.direction[i] == doctest::Approx(rawGpu.direction[i]));
            CHECK(typedGpu.colorIntensity[i] == doctest::Approx(rawGpu.colorIntensity[i]));
        }
    }
}
