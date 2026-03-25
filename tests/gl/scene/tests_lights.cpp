#include <doctest/doctest.h>

#include <nfx/graphics/gl/scene/lights/AmbientLight.h>
#include <nfx/graphics/gl/scene/lights/DirectionalLight.h>
#include <nfx/graphics/gl/scene/lights/PointLight.h>
#include <nfx/graphics/gl/scene/lights/SpotLight.h>

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

TEST_SUITE("PointLight")
{
    TEST_CASE("create raw and typed overloads are equivalent")
    {
        const auto raw = PointLight::create(1.0f, 2.0f, 3.0f, 0.1f, 0.2f, 0.3f, 4.0f, 5.0f);
        const auto typed =
            PointLight::create(math::Vec3{ 1.0f, 2.0f, 3.0f }, math::Vec3{ 0.1f, 0.2f, 0.3f }, 4.0f, 5.0f);

        CHECK(typed.position[0] == doctest::Approx(raw.position[0]));
        CHECK(typed.position[1] == doctest::Approx(raw.position[1]));
        CHECK(typed.position[2] == doctest::Approx(raw.position[2]));
        CHECK(typed.color[0] == doctest::Approx(raw.color[0]));
        CHECK(typed.color[1] == doctest::Approx(raw.color[1]));
        CHECK(typed.color[2] == doctest::Approx(raw.color[2]));
        CHECK(typed.intensity == doctest::Approx(raw.intensity));
        CHECK(typed.radius == doctest::Approx(raw.radius));
    }

    TEST_CASE("toGpuData raw and typed overloads are equivalent")
    {
        const float rawPosition[3] = { 1.0f, 2.0f, 3.0f };
        const float rawColor[3] = { 0.1f, 0.2f, 0.3f };
        const math::Vec3 typedPosition{ 1.0f, 2.0f, 3.0f };
        const math::Vec3 typedColor{ 0.1f, 0.2f, 0.3f };

        const auto rawGpu = PointLight::toGpuData(rawPosition, rawColor, 4.0f, 5.0f, 12.0f);
        const auto typedGpu = PointLight::toGpuData(typedPosition, typedColor, 4.0f, 5.0f, 12.0f);

        for (int i = 0; i < 4; ++i)
        {
            CHECK(typedGpu.position[i] == doctest::Approx(rawGpu.position[i]));
            CHECK(typedGpu.direction[i] == doctest::Approx(rawGpu.direction[i]));
            CHECK(typedGpu.colorIntensity[i] == doctest::Approx(rawGpu.colorIntensity[i]));
            CHECK(typedGpu.params[i] == doctest::Approx(rawGpu.params[i]));
        }
    }

    TEST_CASE("create factory initializes fields")
    {
        const auto light = PointLight::create(1.0f, 2.0f, 3.0f, 0.1f, 0.2f, 0.3f, 4.0f, 5.0f);
        CHECK(light.position[0] == doctest::Approx(1.0f));
        CHECK(light.position[1] == doctest::Approx(2.0f));
        CHECK(light.position[2] == doctest::Approx(3.0f));
        CHECK(light.color[0] == doctest::Approx(0.1f));
        CHECK(light.color[1] == doctest::Approx(0.2f));
        CHECK(light.color[2] == doctest::Approx(0.3f));
        CHECK(light.intensity == doctest::Approx(4.0f));
        CHECK(light.radius == doctest::Approx(5.0f));
    }
}

TEST_SUITE("SpotLight")
{
    TEST_CASE("create raw and typed overloads are equivalent")
    {
        const auto raw =
            SpotLight::create(1.0f, 2.0f, 3.0f, 0.0f, -2.0f, 0.0f, 0.1f, 0.2f, 0.3f, 4.0f, 0.25f, 0.5f, 6.0f, 12.0f);
        const auto typed = SpotLight::create(
            math::Vec3{ 1.0f, 2.0f, 3.0f },
            math::Vec3{ 0.0f, -2.0f, 0.0f },
            math::Vec3{ 0.1f, 0.2f, 0.3f },
            4.0f,
            0.25f,
            0.5f,
            6.0f,
            12.0f);

        CHECK(typed.position[0] == doctest::Approx(raw.position[0]));
        CHECK(typed.position[1] == doctest::Approx(raw.position[1]));
        CHECK(typed.position[2] == doctest::Approx(raw.position[2]));
        CHECK(typed.direction[0] == doctest::Approx(raw.direction[0]));
        CHECK(typed.direction[1] == doctest::Approx(raw.direction[1]));
        CHECK(typed.direction[2] == doctest::Approx(raw.direction[2]));
        CHECK(typed.color[0] == doctest::Approx(raw.color[0]));
        CHECK(typed.color[1] == doctest::Approx(raw.color[1]));
        CHECK(typed.color[2] == doctest::Approx(raw.color[2]));
        CHECK(typed.intensity == doctest::Approx(raw.intensity));
        CHECK(typed.innerAngle == doctest::Approx(raw.innerAngle));
        CHECK(typed.outerAngle == doctest::Approx(raw.outerAngle));
        CHECK(typed.radius == doctest::Approx(raw.radius));
        CHECK(typed.shadowFarPlane == doctest::Approx(raw.shadowFarPlane));
    }

    TEST_CASE("toGpuData raw and typed overloads are equivalent")
    {
        const float rawPosition[3] = { 0.0f, 1.0f, 2.0f };
        const float rawDirection[3] = { 0.0f, -2.0f, 0.0f };
        const float rawColor[3] = { 0.5f, 0.6f, 0.7f };

        const math::Vec3 typedPosition{ 0.0f, 1.0f, 2.0f };
        const math::Vec3 typedDirection{ 0.0f, -2.0f, 0.0f };
        const math::Vec3 typedColor{ 0.5f, 0.6f, 0.7f };

        const auto rawGpu = SpotLight::toGpuData(rawPosition, rawDirection, rawColor, 3.0f, 0.25f, 0.5f, 8.0f, 20.0f);
        const auto typedGpu =
            SpotLight::toGpuData(typedPosition, typedDirection, typedColor, 3.0f, 0.25f, 0.5f, 8.0f, 20.0f);

        for (int i = 0; i < 4; ++i)
        {
            CHECK(typedGpu.position[i] == doctest::Approx(rawGpu.position[i]));
            CHECK(typedGpu.direction[i] == doctest::Approx(rawGpu.direction[i]));
            CHECK(typedGpu.colorIntensity[i] == doctest::Approx(rawGpu.colorIntensity[i]));
            CHECK(typedGpu.params[i] == doctest::Approx(rawGpu.params[i]));
        }
    }

    TEST_CASE("create factory initializes fields")
    {
        const auto light =
            SpotLight::create(1.0f, 2.0f, 3.0f, 0.0f, -2.0f, 0.0f, 0.1f, 0.2f, 0.3f, 4.0f, 0.25f, 0.5f, 6.0f, 12.0f);
        CHECK(light.direction[0] == doctest::Approx(0.0f));
        CHECK(light.direction[1] == doctest::Approx(-2.0f));
        CHECK(light.direction[2] == doctest::Approx(0.0f));
        CHECK(light.innerAngle == doctest::Approx(0.25f));
        CHECK(light.outerAngle == doctest::Approx(0.5f));
        CHECK(light.radius == doctest::Approx(6.0f));
        CHECK(light.shadowFarPlane == doctest::Approx(12.0f));
    }

    TEST_CASE("toGpuData normalizes direction and stores type")
    {
        const auto light =
            SpotLight::create(0.0f, 1.0f, 2.0f, 0.0f, -2.0f, 0.0f, 0.5f, 0.6f, 0.7f, 3.0f, 0.25f, 0.5f, 8.0f, 20.0f);
        const auto gpu = light.toGpuData();

        CHECK(gpu.position[0] == doctest::Approx(0.0f));
        CHECK(gpu.position[1] == doctest::Approx(1.0f));
        CHECK(gpu.position[2] == doctest::Approx(2.0f));
        CHECK(gpu.position[3] == doctest::Approx(8.0f));

        CHECK(gpu.direction[0] == doctest::Approx(0.0f));
        CHECK(gpu.direction[1] == doctest::Approx(-1.0f));
        CHECK(gpu.direction[2] == doctest::Approx(0.0f));
        CHECK(gpu.direction[3] == doctest::Approx(static_cast<float>(static_cast<int>(PunctualLight::Type::Spot))));

        CHECK(gpu.colorIntensity[0] == doctest::Approx(0.5f));
        CHECK(gpu.colorIntensity[1] == doctest::Approx(0.6f));
        CHECK(gpu.colorIntensity[2] == doctest::Approx(0.7f));
        CHECK(gpu.colorIntensity[3] == doctest::Approx(3.0f));

        CHECK(gpu.params[0] == doctest::Approx(std::cos(0.25f)));
        CHECK(gpu.params[1] == doctest::Approx(std::cos(0.5f)));
        CHECK(gpu.params[2] == doctest::Approx(20.0f));
        CHECK(gpu.params[3] == doctest::Approx(0.0f));
    }
}

TEST_SUITE("PunctualLight")
{
    TEST_CASE("GpuData layout size is std430-friendly")
    {
        CHECK(sizeof(PunctualLight::GpuData) == 64);
        CHECK(offsetof(PunctualLight::GpuData, position) == 0);
        CHECK(offsetof(PunctualLight::GpuData, direction) == 16);
        CHECK(offsetof(PunctualLight::GpuData, colorIntensity) == 32);
        CHECK(offsetof(PunctualLight::GpuData, params) == 48);
    }

    TEST_CASE("GpuBlock layout keeps count header and light payload alignment")
    {
        CHECK(offsetof(PunctualLight::GpuBlock, count) == 0);
        CHECK(offsetof(PunctualLight::GpuBlock, lights) == 16);
        CHECK(
            sizeof(PunctualLight::GpuBlock) ==
            static_cast<std::size_t>(16 + PunctualLight::MaxLights * sizeof(PunctualLight::GpuData)));
    }
}
