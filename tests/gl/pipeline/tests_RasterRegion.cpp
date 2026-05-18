#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("RasterRegion")
{
    TEST_CASE("raster region default policies are deterministic")
    {
        const RasterRegionState state;
        CHECK(state.viewportPolicy == ViewportPolicy::InheritView);
        CHECK_FALSE(state.explicitViewport.has_value());
        CHECK(state.scissorPolicy == ScissorPolicy::Disabled);
        CHECK_FALSE(state.explicitScissor.has_value());
    }

    TEST_CASE("resolved raster state defaults to disabled scissor")
    {
        const ResolvedRasterState state;
        CHECK_FALSE(state.scissorEnabled);
        CHECK(state.viewport.isValid());
        CHECK(state.scissor.isValid());
    }

    TEST_CASE("resolution result helper reflects status")
    {
        RasterResolutionResult ok;
        CHECK(ok.ok());
        CHECK(ok.status == RasterResolutionStatus::Ok);
        CHECK(ok.disposition == RasterResolutionDisposition::Continue);

        RasterResolutionResult failed;
        failed.status = RasterResolutionStatus::InvalidSurfaceExtent;
        failed.disposition = RasterResolutionDisposition::SkipPass;
        CHECK_FALSE(failed.ok());
    }

    TEST_CASE("resolution input aggregates target view and policy")
    {
        RasterResolutionInput input;
        input.targetExtent = { 1920, 1080 };
        input.viewViewport = { 0, 0, 1280, 720 };
        input.policy.viewportPolicy = ViewportPolicy::FullTarget;
        input.policy.scissorPolicy = ScissorPolicy::MatchViewport;

        CHECK(input.targetExtent.isValid());
        CHECK(input.viewViewport.isValid());
        CHECK(input.policy.viewportPolicy == ViewportPolicy::FullTarget);
        CHECK(input.policy.scissorPolicy == ScissorPolicy::MatchViewport);
    }
}
