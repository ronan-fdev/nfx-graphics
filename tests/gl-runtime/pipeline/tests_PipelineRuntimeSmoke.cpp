#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/pipeline/Renderer.h>
#include <nfx/graphics/gl/pipeline/frame/RenderResources.h>
#include <nfx/graphics/gl/pipeline/passes/RenderPass.h>
#include <nfx/graphics/gl/pipeline/passes/StrokePass.h>
#include <nfx/graphics/gl/resources/MaterialCache.h>
#include <nfx/graphics/gl/resources/MeshCache.h>
#include <nfx/graphics/gl/resources/SamplerCache.h>
#include <nfx/graphics/gl/resources/ShaderCache.h>
#include <nfx/graphics/gl/resources/Texture2DCache.h>
#include <nfx/graphics/gl/resources/TextureCubeCache.h>

#include "../test_helpers/GLContextFixture.h"
#include "../test_helpers/HeadlessDetection.h"
#include "../../gl/test_helpers/StderrCapture.h"

#include <array>
#include <cstddef>
#include <string>
#include <utility>

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

    struct RasterStateCapturePass final : nfx::graphics::gl::RenderPass
    {
        explicit RasterStateCapturePass(std::string name, const nfx::graphics::gl::RasterRegionState& state)
            : RenderPass(std::move(name))
        {
            setRasterRegionState(state);
        }

        int beginCalls = 0;
        int executeCalls = 0;
        int endCalls = 0;
        std::array<GLint, 4> viewport = { 0, 0, 0, 0 };
        std::array<GLint, 4> scissor = { 0, 0, 0, 0 };
        bool scissorEnabled = false;

    protected:
        bool initialize() override { return true; }

        void begin() override { ++beginCalls; }

        void execute(nfx::graphics::gl::RenderResources&) override
        {
            const auto& gl = nfx::graphics::gl::Context::current().functions();
            gl.glGetIntegerv(GL_VIEWPORT, viewport.data());
            gl.glGetIntegerv(GL_SCISSOR_BOX, scissor.data());
            scissorEnabled = (gl.glIsEnabled(GL_SCISSOR_TEST) == GL_TRUE);
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

    [[nodiscard]] std::pair<nfx::graphics::gl::Texture2DHandle, nfx::graphics::gl::Texture2DHandle>
    makeOffscreenTargets(ResourceFixture& resources, int width = 256, int height = 256)
    {
        nfx::graphics::gl::Texture2D::Params colorParams;
        colorParams.generateMipmaps = false;
        colorParams.minFilter = nfx::graphics::gl::Texture2D::Filter::Linear;
        colorParams.magFilter = nfx::graphics::gl::Texture2D::Filter::Linear;
        colorParams.internalFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8;

        nfx::graphics::gl::Texture2D::Params depthParams;
        depthParams.generateMipmaps = false;
        depthParams.minFilter = nfx::graphics::gl::Texture2D::Filter::Nearest;
        depthParams.magFilter = nfx::graphics::gl::Texture2D::Filter::Nearest;
        depthParams.internalFormat = nfx::graphics::gl::Texture2D::InternalFormat::Depth24;

        auto color = nfx::graphics::gl::Texture2D::allocate(width, height, colorParams);
        auto depth = nfx::graphics::gl::Texture2D::allocate(width, height, depthParams);

        return { resources.textures2D.add(std::move(color)), resources.textures2D.add(std::move(depth)) };
    }

    void setStrokePassTargetWhenX11Headless(nfx::graphics::gl::StrokePass& pass, ResourceFixture& resources)
    {
        if (!nfx::tests::isX11HeadlessSoftwareSession())
        {
            return;
        }

        const auto [targetColor, targetDepth] = makeOffscreenTargets(resources);
        pass.setTargetTextures(targetColor, targetDepth);
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

    TEST_CASE("Explicit raster-region viewport and scissor are applied during runtime render")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        nfx::graphics::gl::RasterRegionState raster;
        raster.viewportPolicy = nfx::graphics::gl::ViewportPolicy::Explicit;
        raster.explicitViewport = nfx::graphics::gl::ViewportRect{ 17, 19, 111, 77 };
        raster.scissorPolicy = nfx::graphics::gl::ScissorPolicy::Explicit;
        raster.explicitScissor = nfx::graphics::gl::ScissorRect{ 23, 29, 41, 31 };

        auto* pass = renderer.createPass<RasterStateCapturePass>("raster-capture-explicit", raster);
        REQUIRE(pass != nullptr);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});

        // Should not override explicit raster state owned by the pass
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 0, 0, 256, 256 });
        renderer.render();

        CHECK(pass->executeCalls == 1);
        CHECK(pass->viewport[0] == 17);
        CHECK(pass->viewport[1] == 19);
        CHECK(pass->viewport[2] == 111);
        CHECK(pass->viewport[3] == 77);
        CHECK(pass->scissorEnabled);
        CHECK(pass->scissor[0] == 23);
        CHECK(pass->scissor[1] == 29);
        CHECK(pass->scissor[2] == 41);
        CHECK(pass->scissor[3] == 31);
    }

    TEST_CASE("Disabled scissor policy disables GL scissor test during runtime render")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        nfx::graphics::gl::RasterRegionState raster;
        raster.viewportPolicy = nfx::graphics::gl::ViewportPolicy::InheritView;
        raster.scissorPolicy = nfx::graphics::gl::ScissorPolicy::Disabled;

        auto* pass = renderer.createPass<RasterStateCapturePass>("raster-capture-no-scissor", raster);
        REQUIRE(pass != nullptr);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 5, 7, 200, 120 });
        renderer.render();

        CHECK(pass->executeCalls == 1);
        CHECK_FALSE(pass->scissorEnabled);
    }

    TEST_CASE("Explicit raster policy is stable across pass order without global viewport override")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        const auto& gl = nfx::graphics::gl::Context::current().functions();
        gl.glViewport(0, 0, 256, 256);

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        nfx::graphics::gl::RasterRegionState first;
        first.viewportPolicy = nfx::graphics::gl::ViewportPolicy::Explicit;
        first.explicitViewport = nfx::graphics::gl::ViewportRect{ 0, 0, 32, 32 };
        first.scissorPolicy = nfx::graphics::gl::ScissorPolicy::Disabled;

        nfx::graphics::gl::RasterRegionState second;
        second.viewportPolicy = nfx::graphics::gl::ViewportPolicy::Explicit;
        second.explicitViewport = nfx::graphics::gl::ViewportRect{ 64, 64, 128, 128 };
        second.scissorPolicy = nfx::graphics::gl::ScissorPolicy::Disabled;

        auto* passA = renderer.createPass<RasterStateCapturePass>("raster-stability-a", first);
        auto* passB = renderer.createPass<RasterStateCapturePass>("raster-stability-b", second);
        REQUIRE(passA != nullptr);
        REQUIRE(passB != nullptr);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});

        nfx::tests::StderrCapture capture;
        renderer.render();

        const std::string output = capture.str();
        CHECK(output.find("raster resolution failed") == std::string::npos);
        CHECK(passA->executeCalls == 1);
        CHECK(passB->executeCalls == 1);
        CHECK(renderer.frameStats().passesExecuted == 2);
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

    TEST_CASE("StrokePass emits at least one draw call under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        auto* pass = renderer.createPass<nfx::graphics::gl::StrokePass>("stroke-pass");
        REQUIRE(pass != nullptr);
        setStrokePassTargetWhenX11Headless(*pass, resources);

        const float points[] = { 0.0f, 0.0f, 64.0f, 0.0f, 64.0f, 64.0f };
        nfx::graphics::gl::StrokeItemDesc2D stroke;
        stroke.xy = std::span<const float>{ points, 6 };
        stroke.pointCount = 3;
        stroke.closed = false;
        stroke.style.join = nfx::graphics::gl::StrokeJoin::Round;
        stroke.style.cap = nfx::graphics::gl::StrokeCap::Round;
        const auto handle = pass->addStroke(stroke);
        REQUIRE(handle.isValid());

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 0, 0, 256, 256 });
        renderer.render();

        CHECK(renderer.frameStats().passesExecuted >= 1);
        CHECK(renderer.frameStats().drawCalls >= 1);
    }

    TEST_CASE("StrokePass applies viewport origin under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        auto* pass = renderer.createPass<nfx::graphics::gl::StrokePass>("stroke-pass-viewport-origin");
        REQUIRE(pass != nullptr);
        setStrokePassTargetWhenX11Headless(*pass, resources);

        const float points[] = { 0.0f, 0.0f, 64.0f, 0.0f, 64.0f, 64.0f };
        nfx::graphics::gl::StrokeItemDesc2D stroke;
        stroke.xy = std::span<const float>{ points, 6 };
        stroke.pointCount = 3;
        stroke.closed = false;
        const auto handle = pass->addStroke(stroke);
        REQUIRE(handle.isValid());

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        const nfx::graphics::gl::ViewportRect viewport{ 13, 21, 192, 144 };
        renderer.setViewport(viewport);
        renderer.render();

        GLint glViewportState[4] = { 0, 0, 0, 0 };
        const auto& gl = nfx::graphics::gl::Context::current().functions();
        gl.glGetIntegerv(GL_VIEWPORT, glViewportState);

        CHECK(glViewportState[0] == viewport.x);
        CHECK(glViewportState[1] == viewport.y);
        CHECK(glViewportState[2] == viewport.width);
        CHECK(glViewportState[3] == viewport.height);
    }

    TEST_CASE("StrokePass with no valid stroke emits zero draw calls under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        auto* pass = renderer.createPass<nfx::graphics::gl::StrokePass>("stroke-pass-empty");
        REQUIRE(pass != nullptr);
        setStrokePassTargetWhenX11Headless(*pass, resources);

        const float invalidPoints[] = { 0.0f, 0.0f };
        nfx::graphics::gl::StrokeItemDesc2D invalidStroke;
        invalidStroke.xy = std::span<const float>{ invalidPoints, 2 };
        invalidStroke.pointCount = 1;
        invalidStroke.closed = false;

        const auto handle = pass->addStroke(invalidStroke);
        CHECK_FALSE(handle.isValid());
        CHECK(pass->strokeCount() == 0);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 0, 0, 256, 256 });
        renderer.render();

        CHECK(renderer.frameStats().passesExecuted >= 1);
        CHECK(renderer.frameStats().drawCalls == 0);
        CHECK(pass->runtimeStats().drawCalls == 0);
    }

    TEST_CASE("StrokePass draw count is stable across frames under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        auto* pass = renderer.createPass<nfx::graphics::gl::StrokePass>("stroke-pass-stable");
        REQUIRE(pass != nullptr);
        setStrokePassTargetWhenX11Headless(*pass, resources);

        const float points[] = { 0.0f, 0.0f, 64.0f, 0.0f, 64.0f, 64.0f };
        nfx::graphics::gl::StrokeItemDesc2D stroke;
        stroke.xy = std::span<const float>{ points, 6 };
        stroke.pointCount = 3;
        stroke.closed = false;
        const auto handle = pass->addStroke(stroke);
        REQUIRE(handle.isValid());

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 0, 0, 256, 256 });

        renderer.render();
        CHECK(pass->runtimeStats().drawCalls == 1);

        renderer.render();
        CHECK(pass->runtimeStats().drawCalls == 1);

        renderer.render();
        CHECK(pass->runtimeStats().drawCalls == 1);
    }

    TEST_CASE("StrokePass remove reduces draw count under real GL context")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderer renderer;
        ResourceFixture resources;

        auto* pass = renderer.createPass<nfx::graphics::gl::StrokePass>("stroke-pass-remove");
        REQUIRE(pass != nullptr);
        setStrokePassTargetWhenX11Headless(*pass, resources);

        const float points[] = { 0.0f, 0.0f, 64.0f, 0.0f, 64.0f, 64.0f };
        nfx::graphics::gl::StrokeItemDesc2D stroke;
        stroke.xy = std::span<const float>{ points, 6 };
        stroke.pointCount = 3;
        stroke.closed = false;

        const auto h1 = pass->addStroke(stroke);
        const auto h2 = pass->addStroke(stroke);
        REQUIRE(h1.isValid());
        REQUIRE(h2.isValid());
        CHECK(pass->strokeCount() == 2);

        renderer.initialize(resources.resources);
        renderer.setFrameData(nfx::graphics::gl::FrameData{});
        renderer.setViewport(nfx::graphics::gl::ViewportRect{ 0, 0, 256, 256 });

        renderer.render();
        CHECK(pass->runtimeStats().drawCalls == 2);

        pass->remove(h1);
        CHECK(pass->strokeCount() == 1);

        renderer.render();
        CHECK(pass->runtimeStats().drawCalls == 1);
    }
}
