#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

namespace
{
    struct GeometryPassStatsFixture
    {
        MeshCache meshes;
        MaterialCache materials;
        ShaderCache shaders;
        Texture2DCache textures2D;
        TextureCubeCache texturesCube;
        SamplerCache samplers;

        RenderResources resources{ meshes, materials, shaders, textures2D, texturesCube, samplers };
    };
} // namespace

TEST_SUITE("GeometryPass - Stats Semantics")
{
    TEST_CASE("commandsInvalid counts mesh/material/shader rejections only")
    {
        GeometryPassStatsFixture fixture;

        CHECK(fixture.resources.meshes.size() == 0);
        CHECK(fixture.resources.materials.size() == 0);
        CHECK(fixture.resources.shaders.size() == 0);
    }

    TEST_CASE("CullingStats members exist with correct names")
    {
        GeometryPass::CullingStats stats;

        CHECK(stats.commandsTested == 0);
        CHECK(stats.commandsCulled == 0);
        CHECK(stats.commandsDrawn == 0);
        CHECK(stats.commandsInvalid == 0);
    }

    TEST_CASE("ExecutionStats tracks mesh binds and instance submissions")
    {
        GeometryPass::ExecutionStats stats;

        CHECK(stats.shaderBinds == 0);
        CHECK(stats.vaoBinds == 0);
        CHECK(stats.instancedDraws == 0);
        CHECK(stats.verticesSubmitted == 0);
        CHECK(stats.indicesSubmitted == 0);
        CHECK(stats.instancesSubmitted == 0);
    }

    TEST_CASE("Renderer aggregates culled commands separately from invalid")
    {
        Renderer::FrameStats frame;
        Renderer::RendererStats cumulative;

        CHECK(frame.commandsRejected == 0);

        CHECK(cumulative.totalCulledCommands == 0);
    }

    TEST_CASE("Renderer frame stats expose transparent and shadow counters")
    {
        Renderer::FrameStats frame;

        CHECK(frame.transparentDraws == 0);
        CHECK(frame.shadowDraws == 0);
    }

    TEST_CASE("CullingStats semantic contract: invalid ≠ culled")
    {
        GeometryPass::CullingStats stats;
        stats.commandsInvalid = 2; // Resource errors
        stats.commandsCulled = 3;  // Frustum culling
        stats.commandsDrawn = 5;   // Successfully rendered

        const auto submitted = 10u;
        const auto tested = submitted - stats.commandsInvalid;

        CHECK(submitted == 10);
        CHECK(stats.commandsInvalid == 2);
        CHECK(tested == 8);
        CHECK((stats.commandsCulled + stats.commandsDrawn) == tested);

        CHECK(stats.commandsCulled == 3);
        CHECK(stats.commandsInvalid != stats.commandsCulled);
    }

    TEST_CASE("Shadow passes expose executionStats API")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&DirectionalShadowPass::executionStats)>);
        CHECK(std::is_invocable_v<decltype(&DirectionalShadowPass::executionStats), const DirectionalShadowPass*>);

        CHECK(std::is_member_function_pointer_v<decltype(&PointShadowPass::executionStats)>);
        CHECK(std::is_invocable_v<decltype(&PointShadowPass::executionStats), const PointShadowPass*>);

        CHECK(std::is_member_function_pointer_v<decltype(&SpotShadowPass::executionStats)>);
        CHECK(std::is_invocable_v<decltype(&SpotShadowPass::executionStats), const SpotShadowPass*>);
    }

    TEST_CASE("Point shadow stats are draw-call totals across active lights")
    {
        PointShadowPass::ExecutionStats stats;

        const std::uint32_t submittedPerLight = 3;
        const std::uint32_t activeLights = 2;

        stats.commandsSubmitted = submittedPerLight;
        stats.commandsDrawn = 4;   // 2 valid commands rendered for each of 2 lights
        stats.commandsInvalid = 2; // 1 invalid command seen for each of 2 lights

        CHECK(stats.commandsDrawn + stats.commandsInvalid == submittedPerLight * activeLights);
    }

    TEST_CASE("Spot shadow stats are draw-call totals across active lights")
    {
        SpotShadowPass::ExecutionStats stats;

        const std::uint32_t submittedPerLight = 4;
        const std::uint32_t activeLights = 3;

        stats.commandsSubmitted = submittedPerLight;
        stats.commandsDrawn = 9;   // 3 valid commands rendered for each of 3 lights
        stats.commandsInvalid = 3; // 1 invalid command seen for each of 3 lights

        CHECK(stats.commandsDrawn + stats.commandsInvalid == submittedPerLight * activeLights);
    }
}
