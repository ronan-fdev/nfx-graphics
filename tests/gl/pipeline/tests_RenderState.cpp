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
}
