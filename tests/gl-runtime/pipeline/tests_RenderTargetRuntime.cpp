#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/pipeline/RenderTarget.h>

#include "../test_helpers/GLContextFixture.h"

#ifndef NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS
    #error "GL runtime tests require NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS"
#endif

TEST_SUITE("RenderTargetRuntime")
{
    TEST_CASE("Color render target allocates valid complete framebuffer")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::RenderTarget target;
        target.resize({ .width = 320,
                        .height = 200,
                        .depthOnly = false,
                        .colorFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8,
                        .depthFormat = nfx::graphics::gl::Texture2D::InternalFormat::Depth24 });

        CHECK(target.isValid());
        CHECK(target.isComplete());
        CHECK(target.width() == 320);
        CHECK(target.height() == 200);
        CHECK(target.texture().isValid());
        CHECK(target.texture().width() == 320);
        CHECK(target.texture().height() == 200);
        CHECK_FALSE(target.specification().depthOnly);
    }

    TEST_CASE("Depth-only render target allocates valid complete framebuffer")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::RenderTarget target;
        target.resize({ .width = 256,
                        .height = 256,
                        .depthOnly = true,
                        .colorFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8,
                        .depthFormat = nfx::graphics::gl::Texture2D::InternalFormat::Depth24 });

        CHECK(target.isValid());
        CHECK(target.isComplete());
        CHECK(target.width() == 256);
        CHECK(target.height() == 256);
        CHECK(target.texture().isValid());
        CHECK(target.texture().width() == 256);
        CHECK(target.texture().height() == 256);
        CHECK(target.specification().depthOnly);
    }

    TEST_CASE("Depth24Stencil8 attachment path stays complete")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::RenderTarget target;
        target.resize({ .width = 640,
                        .height = 360,
                        .depthOnly = false,
                        .colorFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8,
                        .depthFormat = nfx::graphics::gl::Texture2D::InternalFormat::Depth24Stencil8 });

        CHECK(target.isValid());
        CHECK(target.isComplete());
        CHECK(target.specification().depthFormat == nfx::graphics::gl::Texture2D::InternalFormat::Depth24Stencil8);
    }

    TEST_CASE("resize(int,int) updates existing target dimensions")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::RenderTarget target(128, 96);
        REQUIRE(target.isValid());
        REQUIRE(target.isComplete());

        target.resize(512, 384);

        CHECK(target.isValid());
        CHECK(target.isComplete());
        CHECK(target.width() == 512);
        CHECK(target.height() == 384);
        CHECK(target.texture().width() == 512);
        CHECK(target.texture().height() == 384);
    }

    TEST_CASE("invalid resize keeps previous valid allocation")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::RenderTarget target(320, 180);
        REQUIRE(target.isValid());
        REQUIRE(target.isComplete());

        target.resize(0, 180);

        CHECK(target.isValid());
        CHECK(target.isComplete());
        CHECK(target.width() == 320);
        CHECK(target.height() == 180);
        CHECK(target.texture().width() == 320);
        CHECK(target.texture().height() == 180);
    }
}
