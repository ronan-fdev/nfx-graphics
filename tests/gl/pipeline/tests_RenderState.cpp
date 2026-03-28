#include <doctest/doctest.h>

#include <nfx/graphics/gl/pipeline/RenderState.h>

using namespace nfx::graphics::gl;

TEST_SUITE("RenderState")
{
    TEST_CASE("Default state matches expected baseline")
    {
        const RenderState state{};

        CHECK(state.depthTest);
        CHECK(state.depthWrite);
        CHECK(state.depthFunc == RenderState::DepthFunc::Less);

        CHECK_FALSE(state.blend);
        CHECK(state.blendSrc == RenderState::BlendFactor::SrcAlpha);
        CHECK(state.blendDst == RenderState::BlendFactor::OneMinusSrcAlpha);
        CHECK(state.blendSrcAlpha == RenderState::BlendFactor::SrcAlpha);
        CHECK(state.blendDstAlpha == RenderState::BlendFactor::OneMinusSrcAlpha);
        CHECK(state.blendOp == RenderState::BlendOp::Add);
        CHECK(state.blendOpAlpha == RenderState::BlendOp::Add);

        CHECK(state.cullFace);
        CHECK(state.cullMode == RenderState::CullFace::Back);
        CHECK(state.frontFace == RenderState::FrontFace::CCW);

        CHECK(state.colorWrite);
        CHECK(state.colorWriteR);
        CHECK(state.colorWriteG);
        CHECK(state.colorWriteB);
        CHECK(state.colorWriteA);

        CHECK_FALSE(state.polygonOffset);
        CHECK(state.polygonOffsetFactor == doctest::Approx(1.0f));
        CHECK(state.polygonOffsetUnits == doctest::Approx(1.0f));
    }

    TEST_CASE("Enum values map to OpenGL constants")
    {
        CHECK(static_cast<unsigned int>(RenderState::DepthFunc::Less) == static_cast<unsigned int>(LESS));
        CHECK(static_cast<unsigned int>(RenderState::BlendFactor::SrcAlpha) == static_cast<unsigned int>(SRC_ALPHA));
        CHECK(
            static_cast<unsigned int>(RenderState::BlendFactor::OneMinusSrcAlpha) ==
            static_cast<unsigned int>(ONE_MINUS_SRC_ALPHA));
        CHECK(static_cast<unsigned int>(RenderState::BlendOp::Add) == static_cast<unsigned int>(FUNC_ADD));
        CHECK(static_cast<unsigned int>(RenderState::CullFace::Back) == static_cast<unsigned int>(BACK));
        CHECK(static_cast<unsigned int>(RenderState::FrontFace::CCW) == static_cast<unsigned int>(CCW));
    }

    TEST_CASE("opaque preset: depth test and write enabled, no blend, cull back")
    {
        const RenderState s = RenderState::opaque();

        CHECK(s.depthTest == true);
        CHECK(s.depthWrite == true);
        CHECK(s.depthFunc == RenderState::DepthFunc::Less);
        CHECK(s.blend == false);
        CHECK(s.cullFace == true);
        CHECK(s.cullMode == RenderState::CullFace::Back);
        CHECK(s.frontFace == RenderState::FrontFace::CCW);
        CHECK(s.colorWrite == true);
        CHECK(s.polygonOffset == false);
    }

    TEST_CASE("transparent preset: depth test, no depth write, alpha blend, no cull")
    {
        const RenderState s = RenderState::transparent();

        CHECK(s.depthTest == true);
        CHECK(s.depthWrite == false);
        CHECK(s.depthFunc == RenderState::DepthFunc::Less);
        CHECK(s.blend == true);
        CHECK(s.blendSrc == RenderState::BlendFactor::SrcAlpha);
        CHECK(s.blendDst == RenderState::BlendFactor::OneMinusSrcAlpha);
        CHECK(s.cullFace == false);
        CHECK(s.colorWrite == true);
        CHECK(s.polygonOffset == false);
    }

    TEST_CASE("opaque and transparent differ on depthWrite, blend and cullFace")
    {
        const RenderState opaque = RenderState::opaque();
        const RenderState transparent = RenderState::transparent();

        CHECK(opaque.depthWrite != transparent.depthWrite);
        CHECK(opaque.blend != transparent.blend);
        CHECK(opaque.cullFace != transparent.cullFace);
    }

    TEST_CASE("default RenderState matches opaque preset")
    {
        const RenderState defaults;
        const RenderState opaque = RenderState::opaque();

        CHECK(defaults.depthTest == opaque.depthTest);
        CHECK(defaults.depthWrite == opaque.depthWrite);
        CHECK(defaults.depthFunc == opaque.depthFunc);
        CHECK(defaults.blend == opaque.blend);
        CHECK(defaults.cullFace == opaque.cullFace);
        CHECK(defaults.cullMode == opaque.cullMode);
        CHECK(defaults.frontFace == opaque.frontFace);
        CHECK(defaults.colorWrite == opaque.colorWrite);
        CHECK(defaults.polygonOffset == opaque.polygonOffset);
    }
}
