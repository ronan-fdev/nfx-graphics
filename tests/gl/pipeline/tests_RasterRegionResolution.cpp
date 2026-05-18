#include <doctest/doctest.h>

#include "gl/pipeline/detail/RasterRegionResolution.h"

namespace gl = nfx::graphics::gl;

TEST_SUITE("RasterRegionResolution")
{
    TEST_CASE("inherit view viewport")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 1280, 720 };
        in.viewViewport = { 100, 50, 300, 200 };
        in.policy.viewportPolicy = gl::ViewportPolicy::InheritView;

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.viewport.x == 100);
        CHECK(out.state.viewport.y == 50);
        CHECK(out.state.viewport.width == 300);
        CHECK(out.state.viewport.height == 200);
    }

    TEST_CASE("full target viewport")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 10, 10, 100, 100 };
        in.policy.viewportPolicy = gl::ViewportPolicy::FullTarget;

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.viewport.x == 0);
        CHECK(out.state.viewport.y == 0);
        CHECK(out.state.viewport.width == 640);
        CHECK(out.state.viewport.height == 360);
    }

    TEST_CASE("explicit viewport")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.viewportPolicy = gl::ViewportPolicy::Explicit;
        in.policy.explicitViewport = gl::ViewportRect{ 20, 30, 200, 100 };

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.viewport.x == 20);
        CHECK(out.state.viewport.y == 30);
        CHECK(out.state.viewport.width == 200);
        CHECK(out.state.viewport.height == 100);
    }

    TEST_CASE("disabled scissor")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.scissorPolicy = gl::ScissorPolicy::Disabled;

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK_FALSE(out.state.scissorEnabled);
    }

    TEST_CASE("match viewport scissor")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 7, 9, 100, 80 };
        in.policy.viewportPolicy = gl::ViewportPolicy::InheritView;
        in.policy.scissorPolicy = gl::ScissorPolicy::MatchViewport;

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.scissorEnabled);
        CHECK(out.state.scissor.x == 7);
        CHECK(out.state.scissor.y == 9);
        CHECK(out.state.scissor.width == 100);
        CHECK(out.state.scissor.height == 80);
    }

    TEST_CASE("inherit view scissor")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 11, 13, 120, 90 };
        in.policy.viewportPolicy = gl::ViewportPolicy::FullTarget;
        in.policy.scissorPolicy = gl::ScissorPolicy::InheritView;

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.scissorEnabled);
        CHECK(out.state.scissor.x == 11);
        CHECK(out.state.scissor.y == 13);
        CHECK(out.state.scissor.width == 120);
        CHECK(out.state.scissor.height == 90);
    }

    TEST_CASE("explicit scissor")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.scissorPolicy = gl::ScissorPolicy::Explicit;
        in.policy.explicitScissor = gl::ScissorRect{ 4, 5, 6, 7 };

        const auto out = gl::detail::resolveRasterState(in);
        REQUIRE(out.ok());
        CHECK(out.state.scissorEnabled);
        CHECK(out.state.scissor.x == 4);
        CHECK(out.state.scissor.y == 5);
        CHECK(out.state.scissor.width == 6);
        CHECK(out.state.scissor.height == 7);
    }

    TEST_CASE("invalid surface fails")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 0, 360 };
        in.viewViewport = { 0, 0, 10, 10 };

        const auto out = gl::detail::resolveRasterState(in, gl::RasterValidationMode::Warn);
        CHECK_FALSE(out.ok());
        CHECK(out.status == gl::RasterResolutionStatus::InvalidSurfaceExtent);
        CHECK(out.disposition == gl::RasterResolutionDisposition::SkipPass);
    }

    TEST_CASE("invalid explicit viewport fails")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.viewportPolicy = gl::ViewportPolicy::Explicit;
        in.policy.explicitViewport = gl::ViewportRect{ 630, 10, 20, 10 };

        const auto out = gl::detail::resolveRasterState(in, gl::RasterValidationMode::Warn);
        CHECK_FALSE(out.ok());
        CHECK(out.status == gl::RasterResolutionStatus::InvalidExplicitViewport);
        CHECK(out.disposition == gl::RasterResolutionDisposition::SkipPass);
    }

    TEST_CASE("invalid explicit scissor fails")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.scissorPolicy = gl::ScissorPolicy::Explicit;
        in.policy.explicitScissor = gl::ScissorRect{ 639, 0, 2, 1 };

        const auto out = gl::detail::resolveRasterState(in, gl::RasterValidationMode::Warn);
        CHECK_FALSE(out.ok());
        CHECK(out.status == gl::RasterResolutionStatus::InvalidExplicitScissor);
        CHECK(out.disposition == gl::RasterResolutionDisposition::SkipPass);
    }

    TEST_CASE("edge-aligned rectangles are valid")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 1280, 720 };
        in.viewViewport = { 1279, 719, 1, 1 };
        in.policy.viewportPolicy = gl::ViewportPolicy::InheritView;
        in.policy.scissorPolicy = gl::ScissorPolicy::MatchViewport;

        const auto out = gl::detail::resolveRasterState(in);
        CHECK(out.ok());
    }

    TEST_CASE("strict mode escalates failure disposition")
    {
        gl::RasterResolutionInput in;
        in.targetExtent = { 640, 360 };
        in.viewViewport = { 0, 0, 640, 360 };
        in.policy.viewportPolicy = gl::ViewportPolicy::Explicit;

        const auto out = gl::detail::resolveRasterState(in, gl::RasterValidationMode::Strict);
        CHECK_FALSE(out.ok());
        CHECK(out.status == gl::RasterResolutionStatus::MissingExplicitViewport);
        CHECK(out.disposition == gl::RasterResolutionDisposition::AbortFrame);
    }
}
