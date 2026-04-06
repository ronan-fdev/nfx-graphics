#include <doctest/doctest.h>

#include <nfx/graphics/gl/pipeline/Bindings.h>

#include <array>

using namespace nfx::graphics::gl;

TEST_SUITE("Bindings")
{
    TEST_CASE("UboBindings values are unique")
    {
        const std::array<GLuint, 7> slots = { UboBindings::CameraBlock,           UboBindings::AmbientLightBlock,
                                              UboBindings::DirectionalLightBlock, UboBindings::ShadowMatricesBlock,
                                              UboBindings::ShadowDepthBlock,      UboBindings::IblFrameBlock,
                                              UboBindings::MaterialBlock };

        for (std::size_t i = 0; i < slots.size(); ++i)
        {
            for (std::size_t j = i + 1; j < slots.size(); ++j)
            {
                CHECK(slots[i] != slots[j]);
            }
        }
    }

    TEST_CASE("TextureBindings aliases map to canonical slots")
    {
        CHECK(TextureBindings::DiffuseMap == TextureBindings::MaterialSlot0);
        CHECK(TextureBindings::NormalMap == TextureBindings::MaterialSlot1);
        CHECK(TextureBindings::SpecularMap == TextureBindings::MaterialSlot2);

        CHECK(TextureBindings::BaseColorMap == TextureBindings::MaterialSlot0);
        CHECK(TextureBindings::MetallicRoughnessMap == TextureBindings::MaterialSlot2);
        CHECK(TextureBindings::OcclusionMap == TextureBindings::MaterialSlot3);
        CHECK(TextureBindings::ArmMap == TextureBindings::MaterialSlot3);
    }

    TEST_CASE("TextureBindings frame-global ranges do not overlap")
    {
        const GLuint pointStart = TextureBindings::PointShadowMapBase;
        const GLuint pointEnd = pointStart + PipelineLimits::MaxPointShadows - 1;
        const GLuint spotStart = TextureBindings::SpotShadowMapBase;
        const GLuint spotEnd = spotStart + PipelineLimits::MaxSpotShadows - 1;

        CHECK(pointEnd < spotStart);
        CHECK(spotEnd < TextureBindings::DirectionalShadowMap);
        CHECK(TextureBindings::DirectionalShadowMap < TextureBindings::EnvMap);
        CHECK(TextureBindings::EnvMap < TextureBindings::IrradianceMap);
        CHECK(TextureBindings::IrradianceMap < TextureBindings::PrefilteredEnvMap);
        CHECK(TextureBindings::PrefilteredEnvMap < TextureBindings::BrdfLut);
        CHECK(TextureBindings::MaterialSlot3 < TextureBindings::BrdfLut);

        const std::array<GLuint, 9> canonicalSlots = {
            TextureBindings::DirectionalShadowMap, TextureBindings::EnvMap,        TextureBindings::IrradianceMap,
            TextureBindings::PrefilteredEnvMap,    TextureBindings::BrdfLut,       TextureBindings::MaterialSlot0,
            TextureBindings::MaterialSlot1,        TextureBindings::MaterialSlot2, TextureBindings::MaterialSlot3
        };

        for (std::size_t i = 0; i < canonicalSlots.size(); ++i)
        {
            for (std::size_t j = i + 1; j < canonicalSlots.size(); ++j)
            {
                CHECK(canonicalSlots[i] != canonicalSlots[j]);
            }
        }
    }

    TEST_CASE("TextureBindings built-in material slots stay below user range")
    {
        CHECK(TextureBindings::MaterialSlot0 < TextureBindings::UserMaterialFirstUnit);
        CHECK(TextureBindings::MaterialSlot1 < TextureBindings::UserMaterialFirstUnit);
        CHECK(TextureBindings::MaterialSlot2 < TextureBindings::UserMaterialFirstUnit);
        CHECK(TextureBindings::MaterialSlot3 < TextureBindings::UserMaterialFirstUnit);
        CHECK(TextureBindings::BrdfLut < TextureBindings::UserMaterialFirstUnit);

        CHECK(TextureBindings::UserMaterialFirstUnit <= TextureBindings::UserMaterialLastUnit);
    }
}
