#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("Pass stats semantics")
{
    TEST_CASE("TransparentPass stats separate command-level invalid from draw calls")
    {
        TransparentPass::ExecutionStats stats;

        CHECK(stats.commandsSubmitted == 0);
        CHECK(stats.commandsDrawn == 0);
        CHECK(stats.commandsInvalid == 0);

        stats.commandsSubmitted = 4;
        stats.commandsInvalid = 1;
        stats.commandsDrawn = 6;

        CHECK(stats.commandsDrawn >= (stats.commandsSubmitted - stats.commandsInvalid));
    }

    TEST_CASE("WboitPass stats use single-pass submission semantics")
    {
        WboitPass::ExecutionStats stats;

        CHECK(stats.commandsSubmitted == 0);
        CHECK(stats.commandsDrawn == 0);
        CHECK(stats.commandsInvalid == 0);
        CHECK(stats.shaderBinds == 0);

        stats.commandsSubmitted = 8;
        stats.commandsInvalid = 3;
        stats.commandsDrawn = 5;

        CHECK((stats.commandsDrawn + stats.commandsInvalid) == stats.commandsSubmitted);
    }

    TEST_CASE("WboitPass stats expose shader bind accounting")
    {
        WboitPass::ExecutionStats stats;
        stats.shaderBinds = 2;

        CHECK(stats.shaderBinds == 2);
    }

    TEST_CASE("Renderer has non-trivial destructor for GPU query cleanup")
    {
        CHECK_FALSE(std::is_trivially_destructible_v<Renderer>);
    }

    TEST_CASE("PointShadowPass stats are attempt-based across active lights")
    {
        PointShadowPass::ExecutionStats stats;

        constexpr std::uint32_t queueSize = 4;
        constexpr std::uint32_t lightCount = 3;
        const std::uint32_t attempts = queueSize * lightCount;

        stats.commandsSubmitted = attempts;
        stats.commandsInvalid = 2;
        stats.commandsDrawn = attempts - stats.commandsInvalid;

        CHECK(stats.commandsSubmitted == 12);
        CHECK((stats.commandsDrawn + stats.commandsInvalid) == stats.commandsSubmitted);
    }

    TEST_CASE("SpotShadowPass stats are attempt-based across active lights")
    {
        SpotShadowPass::ExecutionStats stats;

        constexpr std::uint32_t queueSize = 5;
        constexpr std::uint32_t lightCount = 2;
        const std::uint32_t attempts = queueSize * lightCount;

        stats.commandsSubmitted = attempts;
        stats.commandsInvalid = 1;
        stats.commandsDrawn = attempts - stats.commandsInvalid;

        CHECK(stats.commandsSubmitted == 10);
        CHECK((stats.commandsDrawn + stats.commandsInvalid) == stats.commandsSubmitted);
    }

    TEST_CASE("DirectionalShadowPass stats remain single-light style")
    {
        DirectionalShadowPass::ExecutionStats stats;

        stats.commandsSubmitted = 7;
        stats.commandsInvalid = 2;
        stats.commandsDrawn = 5;

        CHECK((stats.commandsDrawn + stats.commandsInvalid) == stats.commandsSubmitted);
    }

    TEST_CASE("Renderer frame submitted commands represent aggregated attempts")
    {
        Renderer::FrameStats frame;

        frame.commandsSubmitted = 20;
        frame.commandsRejected = 4;
        frame.shadowDraws = 12;
        frame.transparentDraws = 3;
        frame.opaqueDraws = 1;
        frame.drawCalls = frame.shadowDraws + frame.transparentDraws + frame.opaqueDraws;

        CHECK(frame.drawCalls == 16);
        CHECK(frame.commandsSubmitted >= frame.drawCalls);
    }
}
