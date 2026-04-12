#include <doctest/doctest.h>

#include <nfx/graphics/gl/material/Material.h>
#include <nfx/graphics/gl/material/MaterialBlock.h>
#include <nfx/graphics/gl/material/BlinnPhong.h>
#include <nfx/graphics/gl/material/Pbr.h>
#include <nfx/graphics/gl/pipeline/Bindings.h>
#include <nfx/graphics/gl/pipeline/RenderState.h>
#include <nfx/graphics/gl/resources/Handle.h>

using namespace nfx::graphics::gl;

namespace
{
    // Construct a material with a sentinel shader handle (non-zero, no GL object)
    Material makeMaterial()
    {
        return Material::create(ShaderHandle{ 1 }, RenderState{});
    }
} // namespace

TEST_SUITE("MaterialBlockData")
{
    TEST_CASE("Size matches std140 expectation (48 bytes)")
    {
        CHECK(sizeof(MaterialBlockData) == 48);
    }

    TEST_CASE("Layout offsets and alignment match std140 expectations")
    {
        CHECK(alignof(MaterialBlockData) >= alignof(float));
        CHECK(offsetof(MaterialBlockData, baseColor_alpha) == 0);
        CHECK(offsetof(MaterialBlockData, specColor_shine) == 16);
        CHECK(offsetof(MaterialBlockData, emissive_env) == 32);
    }

    TEST_CASE("Default base color is white, alpha 1")
    {
        MaterialBlockData block;
        CHECK(block.baseColor_alpha[0] == doctest::Approx(1.f));
        CHECK(block.baseColor_alpha[1] == doctest::Approx(1.f));
        CHECK(block.baseColor_alpha[2] == doctest::Approx(1.f));
        CHECK(block.baseColor_alpha[3] == doctest::Approx(1.f));
    }

    TEST_CASE("Default specular color is white, shininess 32")
    {
        MaterialBlockData block;
        CHECK(block.specColor_shine[0] == doctest::Approx(1.f));
        CHECK(block.specColor_shine[1] == doctest::Approx(1.f));
        CHECK(block.specColor_shine[2] == doctest::Approx(1.f));
        CHECK(block.specColor_shine[3] == doctest::Approx(32.f));
    }

    TEST_CASE("Default emissive is black, env intensity 1")
    {
        MaterialBlockData block;
        CHECK(block.emissive_env[0] == doctest::Approx(0.f));
        CHECK(block.emissive_env[1] == doctest::Approx(0.f));
        CHECK(block.emissive_env[2] == doctest::Approx(0.f));
        CHECK(block.emissive_env[3] == doctest::Approx(1.f));
    }
}

TEST_SUITE("Material")
{
    TEST_CASE("create() stores the shader handle")
    {
        auto mat = makeMaterial();
        CHECK(mat.shader() == ShaderHandle{ 1 });
    }

    TEST_CASE("create() stores the render state")
    {
        RenderState state;
        state.depthTest = false;
        state.blend = true;
        state.cullFace = false;

        auto mat = Material::create(ShaderHandle{ 1 }, state);
        CHECK(mat.renderState().depthTest == false);
        CHECK(mat.renderState().blend == true);
        CHECK(mat.renderState().cullFace == false);
    }

    TEST_CASE("setRenderState() replaces the stored state")
    {
        auto mat = makeMaterial();
        CHECK(mat.renderState().depthTest == true); // default

        RenderState s;
        s.depthTest = false;
        mat.setRenderState(s);
        CHECK(mat.renderState().depthTest == false);
    }

    TEST_CASE("setUniform int / hasUniform / uniform")
    {
        auto mat = makeMaterial();
        CHECK(!mat.hasUniform("uFlag"));

        mat.setUniform("uFlag", 1);
        CHECK(mat.hasUniform("uFlag"));

        const Uniform* u = mat.uniform("uFlag");
        REQUIRE(u != nullptr);
        CHECK(std::get<int>(*u) == 1);
    }

    TEST_CASE("setUniform float")
    {
        auto mat = makeMaterial();
        mat.setUniform("uTime", 3.14f);
        const Uniform* u = mat.uniform("uTime");
        REQUIRE(u != nullptr);
        CHECK(std::get<float>(*u) == doctest::Approx(3.14f));
    }

    TEST_CASE("setUniformVec3 raw pointer stores UniformVec3")
    {
        auto mat = makeMaterial();
        const float v[3] = { 0.1f, 0.2f, 0.3f };
        mat.setUniformVec3("uColor", v);

        const Uniform* u = mat.uniform("uColor");
        REQUIRE(u != nullptr);
        const auto& vec = std::get<UniformVec3>(*u);
        CHECK(vec[0] == doctest::Approx(0.1f));
        CHECK(vec[1] == doctest::Approx(0.2f));
        CHECK(vec[2] == doctest::Approx(0.3f));
    }

    TEST_CASE("setUniformMat3 raw pointer copies all 9 values")
    {
        auto mat = makeMaterial();
        const float m[9] = {
            1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f,
        };
        mat.setUniformMat3("uN", m);

        const Uniform* u = mat.uniform("uN");
        REQUIRE(u != nullptr);
        const auto& mat3 = std::get<UniformMat3>(*u);
        for (int i = 0; i < 9; ++i)
        {
            CHECK(mat3[static_cast<std::size_t>(i)] == doctest::Approx(m[i]));
        }
    }

    TEST_CASE("setUniformMat4 raw pointer copies all 16 values")
    {
        auto mat = makeMaterial();
        const float m[16] = {
            1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 4.f,
        };
        mat.setUniformMat4("uM", m);

        const Uniform* u = mat.uniform("uM");
        REQUIRE(u != nullptr);
        const auto& mat4 = std::get<UniformMat4>(*u);
        for (int i = 0; i < 16; ++i)
        {
            CHECK(mat4[static_cast<std::size_t>(i)] == doctest::Approx(m[i]));
        }
    }

    TEST_CASE("setUniform overwrites existing value")
    {
        auto mat = makeMaterial();
        mat.setUniform("uVal", 1);
        mat.setUniform("uVal", 2);

        const Uniform* u = mat.uniform("uVal");
        REQUIRE(u != nullptr);
        CHECK(std::get<int>(*u) == 2);
    }

    TEST_CASE("clearUniform removes one entry")
    {
        auto mat = makeMaterial();
        mat.setUniform("uA", 1);
        mat.setUniform("uB", 2);

        mat.clearUniform("uA");
        CHECK(!mat.hasUniform("uA"));
        CHECK(mat.hasUniform("uB"));
    }

    TEST_CASE("clearUniform on missing key is a no-op")
    {
        auto mat = makeMaterial();
        CHECK_NOTHROW(mat.clearUniform("uNonexistent"));
    }

    TEST_CASE("clearUniforms removes all entries")
    {
        auto mat = makeMaterial();
        mat.setUniform("uA", 1);
        mat.setUniform("uB", 2.f);
        mat.clearUniforms();

        CHECK(!mat.hasUniform("uA"));
        CHECK(!mat.hasUniform("uB"));
    }

    TEST_CASE("uniform() returns nullptr for unknown name")
    {
        auto mat = makeMaterial();
        CHECK(mat.uniform("uMissing") == nullptr);
    }

    TEST_CASE("setTexture(name) / hasTexture")
    {
        auto mat = makeMaterial();
        CHECK(!mat.hasTexture("uDiffuseMap"));

        mat.setTexture("uDiffuseMap", Texture2DHandle{ 42 });
        CHECK(mat.hasTexture("uDiffuseMap"));
    }

    TEST_CASE("clearTexture removes one named binding")
    {
        auto mat = makeMaterial();
        mat.setTexture("uAlbedo", Texture2DHandle{ 1 });
        mat.setTexture("uNormal", Texture2DHandle{ 2 });

        mat.clearTexture("uAlbedo");
        CHECK(!mat.hasTexture("uAlbedo"));
        CHECK(mat.hasTexture("uNormal"));
    }

    TEST_CASE("clearTexture on missing key is a no-op")
    {
        auto mat = makeMaterial();
        CHECK_NOTHROW(mat.clearTexture("uNonexistent"));
    }

    TEST_CASE("clearTextures removes all named bindings")
    {
        auto mat = makeMaterial();
        mat.setTexture("uA", Texture2DHandle{ 1 });
        mat.setTexture("uB", Texture2DHandle{ 2 });
        mat.clearTextures();

        CHECK(!mat.hasTexture("uA"));
        CHECK(!mat.hasTexture("uB"));
    }

    TEST_CASE("setTextureUnit / hasTextureUnit")
    {
        auto mat = makeMaterial();
        CHECK(!mat.hasTextureUnit(TextureBindings::MaterialSlot0));

        mat.setTextureUnit(TextureBindings::MaterialSlot0, Texture2DHandle{ 42 });
        CHECK(mat.hasTextureUnit(TextureBindings::MaterialSlot0));
    }

    TEST_CASE("clearTextureUnit removes one explicit binding")
    {
        auto mat = makeMaterial();
        mat.setTextureUnit(TextureBindings::MaterialSlot0, Texture2DHandle{ 1 });
        mat.setTextureUnit(TextureBindings::MaterialSlot1, Texture2DHandle{ 2 });

        mat.clearTextureUnit(TextureBindings::MaterialSlot0);
        CHECK(!mat.hasTextureUnit(TextureBindings::MaterialSlot0));
        CHECK(mat.hasTextureUnit(TextureBindings::MaterialSlot1));
    }

    TEST_CASE("clearTextureUnits removes all explicit bindings")
    {
        auto mat = makeMaterial();
        mat.setTextureUnit(TextureBindings::MaterialSlot0, Texture2DHandle{ 1 });
        mat.setTextureUnit(TextureBindings::MaterialSlot1, Texture2DHandle{ 2 });

        mat.clearTextureUnits();
        CHECK(!mat.hasTextureUnit(TextureBindings::MaterialSlot0));
        CHECK(!mat.hasTextureUnit(TextureBindings::MaterialSlot1));
    }

    TEST_CASE("named and fixed-unit bindings are independent")
    {
        auto mat = makeMaterial();
        mat.setTexture("uCustom", Texture2DHandle{ 1 });
        mat.setTextureUnit(TextureBindings::MaterialSlot0, Texture2DHandle{ 2 });

        CHECK(mat.hasTexture("uCustom"));
        CHECK(mat.hasTextureUnit(TextureBindings::MaterialSlot0));

        mat.clearTextures();
        CHECK(!mat.hasTexture("uCustom"));
        CHECK(mat.hasTextureUnit(TextureBindings::MaterialSlot0));

        mat.clearTextureUnits();
        CHECK(!mat.hasTextureUnit(TextureBindings::MaterialSlot0));
    }

    TEST_CASE("setTextureUnit rejects units in dynamic user range")
    {
        auto mat = makeMaterial();
        mat.setTextureUnit(TextureBindings::UserMaterialFirstUnit, Texture2DHandle{ 77 });
        CHECK(!mat.hasTextureUnit(TextureBindings::UserMaterialFirstUnit));
    }

    TEST_CASE("dynamic user range does not overlap built-in material slots")
    {
        CHECK(
            static_cast<GLuint>(TextureBindings::MaterialSlot0) <
            static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit));
        CHECK(
            static_cast<GLuint>(TextureBindings::MaterialSlot1) <
            static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit));
        CHECK(
            static_cast<GLuint>(TextureBindings::MaterialSlot2) <
            static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit));
        CHECK(
            static_cast<GLuint>(TextureBindings::MaterialSlot3) <
            static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit));
        CHECK(
            static_cast<GLuint>(TextureBindings::BrdfLut) <
            static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit));
    }

    TEST_CASE("Material is move-constructible")
    {
        auto mat = makeMaterial();
        mat.setUniform("uX", 99);

        auto mat2 = std::move(mat);
        CHECK(mat2.shader() == ShaderHandle{ 1 });
        CHECK(mat2.hasUniform("uX"));
    }

    TEST_CASE("Material is move-assignable")
    {
        auto mat = makeMaterial();
        mat.setUniform("uY", 7);

        auto mat2 = makeMaterial();
        mat2 = std::move(mat);
        CHECK(mat2.hasUniform("uY"));
    }

    TEST_SUITE("BlinnPhongMaterial")
    {
        TEST_CASE("apply() selects transparent state when alpha < 1")
        {
            BlinnPhongMaterial bp;
            bp.alpha = 0.5f;

            auto mat = makeMaterial();
            bp.apply(mat);

            CHECK(mat.renderState().blend == true);
        }

        TEST_CASE("apply() selects opaque state when alpha >= 1")
        {
            BlinnPhongMaterial bp;
            bp.alpha = 1.25f;

            auto mat = makeMaterial();
            bp.apply(mat);

            CHECK(mat.renderState().blend == false);
        }

        TEST_CASE("apply() binds all provided texture maps to fixed slots")
        {
            BlinnPhongMaterial bp;
            bp.diffuseMap = Texture2DHandle{ 11 };
            bp.normalMap = Texture2DHandle{ 12 };
            bp.specularMap = Texture2DHandle{ 13 };

            auto mat = makeMaterial();
            bp.apply(mat);

            CHECK(mat.hasTextureUnit(TextureBindings::DiffuseMap));
            CHECK(mat.hasTextureUnit(TextureBindings::NormalMap));
            CHECK(mat.hasTextureUnit(TextureBindings::SpecularMap));
        }

        TEST_CASE("apply() clears fixed slot bindings when handles are invalid")
        {
            auto mat = makeMaterial();
            mat.setTextureUnit(TextureBindings::DiffuseMap, Texture2DHandle{ 21 });
            mat.setTextureUnit(TextureBindings::NormalMap, Texture2DHandle{ 22 });
            mat.setTextureUnit(TextureBindings::SpecularMap, Texture2DHandle{ 23 });

            BlinnPhongMaterial bp;
            bp.diffuseMap = {};
            bp.normalMap = {};
            bp.specularMap = {};

            bp.apply(mat);

            CHECK(!mat.hasTextureUnit(TextureBindings::DiffuseMap));
            CHECK(!mat.hasTextureUnit(TextureBindings::NormalMap));
            CHECK(!mat.hasTextureUnit(TextureBindings::SpecularMap));
        }

        TEST_SUITE("PbrMaterial")
        {
            TEST_CASE("apply() uses fixed slots for baseColor/normal/arm")
            {
                PbrMaterial p;
                p.baseColorMap = Texture2DHandle{ 101 };
                p.normalMap = Texture2DHandle{ 102 };
                p.armMap = Texture2DHandle{ 103 };

                auto mat = makeMaterial();
                p.apply(mat);

                CHECK(mat.hasTextureUnit(TextureBindings::BaseColorMap));
                CHECK(mat.hasTextureUnit(TextureBindings::NormalMap));
                CHECK(mat.hasTextureUnit(TextureBindings::ArmMap));
            }

            TEST_CASE("apply() uses fixed slots for metallicRoughness/occlusion when ARM is absent")
            {
                PbrMaterial p;
                p.baseColorMap = Texture2DHandle{ 111 };
                p.normalMap = Texture2DHandle{ 112 };
                p.metallicRoughnessMap = Texture2DHandle{ 113 };
                p.occlusionMap = Texture2DHandle{ 114 };

                auto mat = makeMaterial();
                p.apply(mat);

                CHECK(mat.hasTextureUnit(TextureBindings::BaseColorMap));
                CHECK(mat.hasTextureUnit(TextureBindings::NormalMap));
                CHECK(mat.hasTextureUnit(TextureBindings::MetallicRoughnessMap));
                CHECK(mat.hasTextureUnit(TextureBindings::OcclusionMap));
            }

            TEST_CASE("apply() clears separate slots when ARM map is used")
            {
                auto mat = makeMaterial();
                mat.setTextureUnit(TextureBindings::MetallicRoughnessMap, Texture2DHandle{ 201 });
                mat.setTextureUnit(TextureBindings::OcclusionMap, Texture2DHandle{ 202 });

                PbrMaterial p;
                p.armMap = Texture2DHandle{ 203 };
                p.apply(mat);

                CHECK(mat.hasTextureUnit(TextureBindings::ArmMap));
                CHECK(!mat.hasTextureUnit(TextureBindings::MetallicRoughnessMap));
            }

            TEST_CASE("apply() clears shared slot when ARM and occlusion are absent")
            {
                auto mat = makeMaterial();
                mat.setTextureUnit(TextureBindings::ArmMap, Texture2DHandle{ 301 });

                PbrMaterial p;
                p.metallicRoughnessMap = Texture2DHandle{ 302 };
                p.apply(mat);

                CHECK(!mat.hasTextureUnit(TextureBindings::ArmMap));
                CHECK(mat.hasTextureUnit(TextureBindings::MetallicRoughnessMap));
                CHECK(!mat.hasTextureUnit(TextureBindings::OcclusionMap));
            }
        }
    }
}
