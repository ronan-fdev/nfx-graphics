#include <doctest/doctest.h>

#include <nfx/graphics/gl/material/Material.h>
#include <nfx/graphics/gl/material/MaterialBlock.h>
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
    TEST_CASE("Size matches std140 expectation (32 bytes)")
    {
        CHECK(sizeof(MaterialBlockData) == 32);
    }

    TEST_CASE("Layout offsets and alignment match std140 expectations")
    {
        CHECK(alignof(MaterialBlockData) >= alignof(float));
        CHECK(offsetof(MaterialBlockData, baseColor_alpha) == 0);
        CHECK(offsetof(MaterialBlockData, specColor_shine) == 16);
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
}
