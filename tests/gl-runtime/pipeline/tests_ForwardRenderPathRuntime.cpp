#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/pipeline/ForwardRenderPath.h>
#include <nfx/graphics/gl/pipeline/frame/RenderResources.h>
#include <nfx/graphics/gl/pipeline/passes/RenderPass.h>
#include <nfx/graphics/gl/pipeline/passes/GeometryPass.h>
#include <nfx/graphics/gl/resources/MaterialCache.h>
#include <nfx/graphics/gl/resources/MeshCache.h>
#include <nfx/graphics/gl/resources/SamplerCache.h>
#include <nfx/graphics/gl/resources/ShaderCache.h>
#include <nfx/graphics/gl/resources/Texture2DCache.h>
#include <nfx/graphics/gl/resources/TextureCubeCache.h>

#include "../test_helpers/GLContextFixture.h"
#include "../test_helpers/HeadlessDetection.h"
#include "../../gl/test_helpers/StderrCapture.h"

#ifndef NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS
    #error "GL runtime tests require NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS"
#endif

namespace
{
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

    struct AutoWiredOverlayPass final : nfx::graphics::gl::RenderPass
    {
        explicit AutoWiredOverlayPass(std::string name)
            : RenderPass(std::move(name))
        {}

        nfx::graphics::gl::Texture2DHandle wiredColor;
        nfx::graphics::gl::Texture2DHandle wiredDepth;
        int executeCalls = 0;

        [[nodiscard]] bool setAutoWiredTargets(
            nfx::graphics::gl::Texture2DHandle color, nfx::graphics::gl::Texture2DHandle depth) override
        {
            wiredColor = color;
            wiredDepth = depth;
            return true;
        }

    private:
        bool initialize() override { return true; }
        void begin() override { resetRuntimeStats(); }
        void execute(nfx::graphics::gl::RenderResources&) override { ++executeCalls; }
        void end() override {}
    };

} // namespace

TEST_SUITE("ForwardRenderPathRuntime")
{
    TEST_CASE("render(viewport) rejects out-of-surface viewport with recoverable warning")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        path.initialize(resources.resources);

        nfx::graphics::gl::FrameData frame;
        const nfx::graphics::gl::ViewportRect invalidViewport{ 0, 0, 2048, 2048 };

        nfx::tests::StderrCapture capture;
        path.render(frame, 1280, 720, invalidViewport);

        const std::string out = capture.str();
        CHECK(
            out.find("[ForwardRenderPath] WARN(RECOVERABLE): render: viewport (0,0,2048,2048) outside surface "
                     "(1280,720), skipping") != std::string::npos);
        CHECK(path.stats().totalFrames == 0);
        CHECK(path.geometryPass().outputWidth() == 0);
        CHECK(path.geometryPass().outputHeight() == 0);
    }

    TEST_CASE("render(viewport) executes when viewport is inside surface")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        path.initialize(resources.resources);
        nfx::tests::disablePresentPassWhenX11Headless(path);

        nfx::graphics::gl::FrameData frame;
        const nfx::graphics::gl::ViewportRect viewport{ 0, 0, 640, 360 };

        path.render(frame, 1280, 720, viewport);

        CHECK(path.stats().totalFrames == 1);
        CHECK(path.frameStats().passesExecuted >= 1);
        CHECK(path.geometryPass().outputWidth() == 1280);
        CHECK(path.geometryPass().outputHeight() == 720);
    }

    TEST_CASE("render(width,height) clamps invalid extents to 1x1")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        path.initialize(resources.resources);
        nfx::tests::disablePresentPassWhenX11Headless(path);

        nfx::graphics::gl::FrameData frame;
        path.render(frame, 0, -42);

        CHECK(path.stats().totalFrames == 1);
        CHECK(path.geometryPass().outputWidth() == 1);
        CHECK(path.geometryPass().outputHeight() == 1);
    }

    TEST_CASE("render(width,height) resizes geometry output when surface changes")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        path.initialize(resources.resources);
        nfx::tests::disablePresentPassWhenX11Headless(path);

        nfx::graphics::gl::FrameData frame;
        path.render(frame, 320, 200);
        CHECK(path.geometryPass().outputWidth() == 320);
        CHECK(path.geometryPass().outputHeight() == 200);

        path.render(frame, 640, 360);
        CHECK(path.geometryPass().outputWidth() == 640);
        CHECK(path.geometryPass().outputHeight() == 360);
        CHECK(path.stats().totalFrames == 2);
    }

    TEST_CASE("custom overlay auto-wiring runs without unknown overlay warnings")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        auto* overlay = path.addOverlay<AutoWiredOverlayPass>("AutoWiredOverlay");
        REQUIRE(overlay != nullptr);

        path.initialize(resources.resources);
        nfx::tests::disablePresentPassWhenX11Headless(path);

        nfx::tests::StderrCapture capture;
        path.render(nfx::graphics::gl::FrameData{}, 640, 360, nfx::graphics::gl::ViewportRect{ 0, 0, 640, 360 });

        const std::string out = capture.str();
        CHECK(out.find("has no known auto-wiring path") == std::string::npos);
        CHECK(overlay->wiredColor.isValid());
        CHECK(overlay->wiredDepth.isValid());
        CHECK(overlay->executeCalls >= 1);
    }

    TEST_CASE("custom overlay auto-wiring survives resize with explicit viewport render")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        ResourceFixture resources;
        nfx::graphics::gl::ForwardRenderPath path;
        auto* overlay = path.addOverlay<AutoWiredOverlayPass>("AutoWiredOverlayResize");
        REQUIRE(overlay != nullptr);

        path.initialize(resources.resources);
        nfx::tests::disablePresentPassWhenX11Headless(path);

        path.render(nfx::graphics::gl::FrameData{}, 320, 200, nfx::graphics::gl::ViewportRect{ 0, 0, 160, 100 });
        const auto colorA = overlay->wiredColor;
        const auto depthA = overlay->wiredDepth;

        path.render(nfx::graphics::gl::FrameData{}, 960, 540, nfx::graphics::gl::ViewportRect{ 50, 30, 480, 270 });

        CHECK(overlay->wiredColor.isValid());
        CHECK(overlay->wiredDepth.isValid());
        CHECK(overlay->wiredColor != colorA);
        CHECK(overlay->wiredDepth != depthA);
        CHECK(overlay->executeCalls >= 2);
    }
}
