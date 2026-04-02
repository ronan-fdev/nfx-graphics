#include <doctest/doctest.h>

#include "gl/material/ShaderFeatures.h"

using namespace nfx::graphics::gl;

TEST_SUITE("ShaderFeatures")
{
    TEST_CASE("None produces no defines")
    {
        const auto defines = toDefines(ShaderFeature::None);
        CHECK(defines.empty());
    }

    TEST_CASE("Each flag produces exactly one define")
    {
        CHECK(toDefines(ShaderFeature::HasDiffuseMap).size() == 1);
        CHECK(toDefines(ShaderFeature::HasNormalMap).size() == 1);
        CHECK(toDefines(ShaderFeature::HasSpecularMap).size() == 1);
        CHECK(toDefines(ShaderFeature::HasShadow).size() == 1);
        CHECK(toDefines(ShaderFeature::HasEnvMap).size() == 1);
    }

    TEST_CASE("Each flag maps to the expected define string")
    {
        CHECK(toDefines(ShaderFeature::HasDiffuseMap)[0] == "HAS_DIFFUSE_MAP");
        CHECK(toDefines(ShaderFeature::HasNormalMap)[0] == "HAS_NORMAL_MAP");
        CHECK(toDefines(ShaderFeature::HasSpecularMap)[0] == "HAS_SPECULAR_MAP");
        CHECK(toDefines(ShaderFeature::HasShadow)[0] == "HAS_SHADOW");
        CHECK(toDefines(ShaderFeature::HasEnvMap)[0] == "HAS_ENV_MAP");
    }

    TEST_CASE("Union and has report active flags")
    {
        const auto features = ShaderFeature::HasDiffuseMap | ShaderFeature::HasNormalMap;
        CHECK(has(features, ShaderFeature::HasDiffuseMap));
        CHECK(has(features, ShaderFeature::HasNormalMap));
        CHECK(!has(features, ShaderFeature::HasSpecularMap));
        CHECK(!has(features, ShaderFeature::HasShadow));
        CHECK(!has(features, ShaderFeature::HasEnvMap));
    }

    TEST_CASE("Intersection keeps only common flags")
    {
        const auto lhs = ShaderFeature::HasDiffuseMap | ShaderFeature::HasNormalMap | ShaderFeature::HasShadow;
        const auto rhs = ShaderFeature::HasNormalMap | ShaderFeature::HasSpecularMap;
        const auto common = lhs & rhs;

        CHECK(!has(common, ShaderFeature::HasDiffuseMap));
        CHECK(has(common, ShaderFeature::HasNormalMap));
        CHECK(!has(common, ShaderFeature::HasSpecularMap));
        CHECK(!has(common, ShaderFeature::HasShadow));
        CHECK(!has(common, ShaderFeature::HasEnvMap));
    }

    TEST_CASE("toDefines returns defines in stable feature order")
    {
        const auto features = ShaderFeature::HasShadow | ShaderFeature::HasDiffuseMap | ShaderFeature::HasSpecularMap |
                              ShaderFeature::HasEnvMap;
        const auto defines = toDefines(features);

        REQUIRE(defines.size() == 4);
        CHECK(defines[0] == "HAS_DIFFUSE_MAP");
        CHECK(defines[1] == "HAS_SPECULAR_MAP");
        CHECK(defines[2] == "HAS_SHADOW");
        CHECK(defines[3] == "HAS_ENV_MAP");
    }

    TEST_CASE("All flags active produces all five defines")
    {
        const auto features = ShaderFeature::HasDiffuseMap | ShaderFeature::HasNormalMap |
                              ShaderFeature::HasSpecularMap | ShaderFeature::HasShadow | ShaderFeature::HasEnvMap;
        const auto defines = toDefines(features);

        REQUIRE(defines.size() == 5);
        CHECK(defines[0] == "HAS_DIFFUSE_MAP");
        CHECK(defines[1] == "HAS_NORMAL_MAP");
        CHECK(defines[2] == "HAS_SPECULAR_MAP");
        CHECK(defines[3] == "HAS_SHADOW");
        CHECK(defines[4] == "HAS_ENV_MAP");
    }

    TEST_CASE("has() returns false for None against any flag")
    {
        CHECK(!has(ShaderFeature::None, ShaderFeature::HasDiffuseMap));
        CHECK(!has(ShaderFeature::None, ShaderFeature::HasNormalMap));
        CHECK(!has(ShaderFeature::None, ShaderFeature::HasSpecularMap));
        CHECK(!has(ShaderFeature::None, ShaderFeature::HasShadow));
        CHECK(!has(ShaderFeature::None, ShaderFeature::HasEnvMap));
    }

    TEST_CASE("Flags are independent bitmask values")
    {
        // No two flags share a bit
        const auto all = ShaderFeature::HasDiffuseMap | ShaderFeature::HasNormalMap | ShaderFeature::HasSpecularMap |
                         ShaderFeature::HasShadow | ShaderFeature::HasEnvMap;
        CHECK(toDefines(all).size() == 5);
    }

    TEST_CASE("toDebugString returns None for ShaderFeature::None")
    {
        CHECK(toDebugString(ShaderFeature::None) == "None");
    }

    TEST_CASE("toDebugString returns single flag name")
    {
        CHECK(toDebugString(ShaderFeature::HasShadow) == "HasShadow");
        CHECK(toDebugString(ShaderFeature::HasEnvMap) == "HasEnvMap");
        CHECK(toDebugString(ShaderFeature::HasDiffuseMap) == "HasDiffuseMap");
    }

    TEST_CASE("toDebugString combines flags with pipe separator")
    {
        const auto features = ShaderFeature::HasShadow | ShaderFeature::HasEnvMap;
        CHECK(toDebugString(features) == "HasShadow|HasEnvMap");
    }

    TEST_CASE("toDebugString follows stable feature order")
    {
        const auto features = ShaderFeature::HasEnvMap | ShaderFeature::HasDiffuseMap | ShaderFeature::HasShadow;
        CHECK(toDebugString(features) == "HasDiffuseMap|HasShadow|HasEnvMap");
    }
}
