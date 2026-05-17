#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/pipeline/Renderer.h>
#include <nfx/graphics/gl/pipeline/frame/RenderResources.h>
#include <nfx/graphics/gl/pipeline/passes/RenderPass.h>
#include <nfx/graphics/gl/resources/MaterialCache.h>
#include <nfx/graphics/gl/resources/MeshCache.h>
#include <nfx/graphics/gl/resources/SamplerCache.h>
#include <nfx/graphics/gl/resources/ShaderCache.h>
#include <nfx/graphics/gl/resources/Texture2DCache.h>
#include <nfx/graphics/gl/resources/TextureCubeCache.h>

#include "../test_helpers/GLContextFixture.h"
#include "../../gl/test_helpers/StderrCapture.h"

#ifndef NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS
    #error "GL runtime tests require NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS"
#endif

namespace
{
    struct CountingPass final : nfx::graphics::gl::RenderPass
    {
        explicit CountingPass(std::string name)
            : RenderPass(std::move(name))
        {}

        int beginCalls = 0;
        int executeCalls = 0;
        int endCalls = 0;

    protected:
        bool initialize() override { return true; }

        void begin() override { ++beginCalls; }

        void execute(nfx::graphics::gl::RenderResources&) override { ++executeCalls; }

        void end() override { ++endCalls; }
    };

    struct ViewportCapturePass final : nfx::graphics::gl::RenderPass
    {
        explicit ViewportCapturePass(std::string name)
            : RenderPass(std::move(name))
        {}

        int beginCalls = 0;
        int executeCalls = 0;
        int endCalls = 0;
        const nfx::graphics::gl::ViewportRect* observedViewport = nullptr;

    protected:
        bool initialize() override { return true; }

        void begin() override
        {
            observedViewport = currentViewport();
            ++beginCalls;
        }

        void execute(nfx::graphics::gl::RenderResources&) override
        {
            observedViewport = currentViewport();
            ++executeCalls;
        }

        void end() override { ++endCalls; }
    };

    struct ResourceFixture
    {
        nfx::graphics::gl::MeshCache meshes;
        nfx::graphics::gl::MaterialCache materials;
        nfx::graphics::gl::ShaderCache shaders;
        nfx::graphics::gl::Texture2DCache textures2D;
        nfx::graphics::gl::TextureCubeCache texturesCube;
        nfx::graphics::gl::SamplerCache samplers;

        nfx::graphics::gl::RenderResources resources{ meshes, materials, shaders, textures2D, texturesCube, samplers };
    };

    [[nodiscard]] std::size_t countSubstringOccurrences(const std::string& text, const std::string& needle)
    {
        if (needle.empty())
        {
            return 0;
        }

        std::size_t count = 0;
        std::size_t pos = 0;
        while ((pos = text.find(needle, pos)) != std::string::npos)
        {
            ++count;
            pos += needle.size();
        }
        return count;
    }
} // namespace

TEST_SUITE("PipelineRuntime")
{
    TEST_CASE("Enabled pass executes under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;
        auto* pass = renderer.createPass<CountingPass>("enabled-pass");
        REQUIRE(pass != nullptr);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.render();

        CHECK(pass->beginCalls == 1);
        CHECK(pass->executeCalls == 1);
        CHECK(pass->endCalls == 1);
        CHECK(renderer.frameStats().passesExecuted == 1);
    }

    TEST_CASE("Disabled pass does not execute under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;
        auto* pass = renderer.createPass<CountingPass>("disabled-pass");
        REQUIRE(pass != nullptr);

        pass->setEnabled(false);
        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.render();

        CHECK(pass->beginCalls == 0);
        CHECK(pass->executeCalls == 0);
        CHECK(pass->endCalls == 0);
        CHECK(renderer.frameStats().passesExecuted == 0);
    }

    TEST_CASE("Lazy-init pass on second render under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        renderer.initialize(resources.resources);

        auto* pass = renderer.createPass<CountingPass>("lazy-pass");
        REQUIRE(pass != nullptr);

        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.render();

        CHECK(pass->beginCalls == 1);
        CHECK(pass->executeCalls == 1);
        CHECK(pass->endCalls == 1);
        CHECK(renderer.frameStats().passesExecuted == 1);
        CHECK(renderer.stats().totalPasses == 1);
    }

    TEST_CASE("Viewport is propagated to passes during runtime render")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;
        auto* pass = renderer.createPass<ViewportCapturePass>("viewport-pass");
        REQUIRE(pass != nullptr);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});

        const nfx::graphics::gl::ViewportRect viewport{ 12, 34, 640, 360 };
        renderer.setViewport(viewport);
        renderer.render();

        REQUIRE(pass->observedViewport != nullptr);
        CHECK(pass->observedViewport->x == viewport.x);
        CHECK(pass->observedViewport->y == viewport.y);
        CHECK(pass->observedViewport->width == viewport.width);
        CHECK(pass->observedViewport->height == viewport.height);

        renderer.resetViewport();
        renderer.render();

        CHECK(pass->observedViewport == nullptr);
        CHECK(pass->beginCalls == 2);
        CHECK(pass->executeCalls == 2);
        CHECK(pass->endCalls == 2);
    }

    TEST_CASE("validatePermutations logs a warning once under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;
        renderer.initialize(resources.resources);
        renderer.setValidationMode(nfx::graphics::gl::Renderer::ValidationMode::Warn);

        nfx::graphics::gl::FrameData frame;
        frame.hasEnvMap = true;
        frame.envMap = nfx::graphics::gl::TextureCubeHandle{ 42 };
        renderer.setFrameData(frame);

        const std::string warningMsg =
            "[Renderer] WARN(INVARIANT): hasEnvMap=true but envMap does not resolve to a cached cubemap";

        nfx::tests::StderrCapture capture;
        renderer.render();
        renderer.render();

        const std::string output = capture.str();
        CHECK(countSubstringOccurrences(output, warningMsg) == 1);
        CHECK(renderer.stats().totalFrames == 2);
    }
}
