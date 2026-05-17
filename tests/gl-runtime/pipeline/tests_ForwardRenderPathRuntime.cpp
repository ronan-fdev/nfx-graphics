#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/pipeline/ForwardRenderPath.h>
#include <nfx/graphics/gl/pipeline/frame/RenderResources.h>
#include <nfx/graphics/gl/pipeline/passes/GeometryPass.h>
#include <nfx/graphics/gl/resources/MaterialCache.h>
#include <nfx/graphics/gl/resources/MeshCache.h>
#include <nfx/graphics/gl/resources/SamplerCache.h>
#include <nfx/graphics/gl/resources/ShaderCache.h>
#include <nfx/graphics/gl/resources/Texture2DCache.h>
#include <nfx/graphics/gl/resources/TextureCubeCache.h>

#include "../test_helpers/GLContextFixture.h"
#include "../../gl/test_helpers/StderrCapture.h"

#include <cstdlib>
#include <cstring>

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

    [[nodiscard]] bool isX11HeadlessSoftwareSession() noexcept
    {
#ifdef __linux__
        const char* display = std::getenv("DISPLAY");
        const char* software = std::getenv("LIBGL_ALWAYS_SOFTWARE");

        // On Xvfb + Mesa software, PresentPass can fail with MIT-SHM BadMatch.
        // We keep Present enabled elsewhere and bypass it only in this headless setup.
        return display != nullptr && display[0] != '\0' && software != nullptr && std::strcmp(software, "1") == 0;
#else
        return false;
#endif
    }

    void disablePresentPassWhenX11Headless(nfx::graphics::gl::ForwardRenderPath& path)
    {
        if (!isX11HeadlessSoftwareSession())
        {
            return;
        }

        auto* present = path.renderer().pass("Present");
        REQUIRE(present != nullptr);
        present->setEnabled(false);
    }
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
        disablePresentPassWhenX11Headless(path);

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
        disablePresentPassWhenX11Headless(path);

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
        disablePresentPassWhenX11Headless(path);

        nfx::graphics::gl::FrameData frame;
        path.render(frame, 320, 200);
        CHECK(path.geometryPass().outputWidth() == 320);
        CHECK(path.geometryPass().outputHeight() == 200);

        path.render(frame, 640, 360);
        CHECK(path.geometryPass().outputWidth() == 640);
        CHECK(path.geometryPass().outputHeight() == 360);
        CHECK(path.stats().totalFrames == 2);
    }
}
