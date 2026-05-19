#include <doctest/doctest.h>

#include <nfx/Graphics.h>
#include "../test_helpers/StderrCapture.h"

#include <type_traits>

namespace gl = nfx::graphics::gl;
using nfx::tests::StderrCapture;

TEST_SUITE("ForwardRenderPath - Overlay Wiring Contract")
{
    TEST_CASE("GridPass overlay has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::GridPass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::GridPass::setTargetTextures),
              gl::GridPass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("AxesPass overlay has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::AxesPass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::AxesPass::setTargetTextures),
              gl::AxesPass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("ImagePlanePass overlay has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::ImagePlanePass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::ImagePlanePass::setTargetTextures),
              gl::ImagePlanePass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("TextPass overlay has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::TextPass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::TextPass::setTargetTextures),
              gl::TextPass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("Polygon2DPass overlay has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::Polygon2DPass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::Polygon2DPass::setTargetTextures),
              gl::Polygon2DPass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("StrokePass has public setTargetTextures(color, depth) method")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&gl::StrokePass::setTargetTextures)>);
        CHECK(std::is_invocable_v<
              decltype(&gl::StrokePass::setTargetTextures),
              gl::StrokePass*,
              gl::Texture2DHandle,
              gl::Texture2DHandle>);
    }

    TEST_CASE("All overlay types inherit from RenderPass")
    {
        CHECK((std::is_base_of_v<gl::RenderPass, gl::GridPass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::AxesPass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::ImagePlanePass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::TextPass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::Polygon2DPass>));
    }

    TEST_CASE("setSkybox overrides previously enabled environment with recoverable warning")
    {
        gl::ForwardRenderPath path;
        gl::TextureCubeCache cubemapCache;

        path.enableEnvironment(2.0f);

        StderrCapture capture;
        path.setSkybox(cubemapCache, gl::TextureCubeHandle{ 7 });

        CHECK(capture.str() == "[ForwardRenderPath] WARN(RECOVERABLE): setSkybox() overrides enableEnvironment()\n");
    }

    TEST_CASE("enableEnvironment is ignored after skybox with recoverable warning")
    {
        gl::ForwardRenderPath path;
        gl::TextureCubeCache cubemapCache;

        path.setSkybox(cubemapCache, gl::TextureCubeHandle{ 7 });

        StderrCapture capture;
        path.enableEnvironment(2.0f);

        CHECK(
            capture.str() ==
            "[ForwardRenderPath] WARN(RECOVERABLE): enableEnvironment() ignored: setSkybox() already set\n");
    }
}
