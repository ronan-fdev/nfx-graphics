#include <doctest/doctest.h>

#include <nfx/Graphics.h>
#include <type_traits>

namespace gl = nfx::graphics::gl;

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

    TEST_CASE("All overlay types inherit from RenderPass")
    {
        CHECK((std::is_base_of_v<gl::RenderPass, gl::GridPass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::AxesPass>));
        CHECK((std::is_base_of_v<gl::RenderPass, gl::ImagePlanePass>));
    }
}
