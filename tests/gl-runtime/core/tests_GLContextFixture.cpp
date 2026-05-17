#include <doctest/doctest.h>

#include "../test_helpers/GLContextFixture.h"
#include <nfx/graphics/gl/core/Context.h>

#ifndef NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS
    #error "GL runtime tests require NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS"
#endif

TEST_SUITE("GLContextFixture")
{
    TEST_CASE("Context::initialize succeeds with a real current GL context")
    {
        nfx::tests::GLContextFixture fixture;
        CHECK(fixture.available());

        CHECK(nfx::graphics::gl::Context::initialize());
        CHECK(nfx::graphics::gl::Context::isInitialized());

        const auto& ctx = nfx::graphics::gl::Context::current();
        CHECK(ctx.majorVersion() >= 4);
        CHECK(ctx.maxTextureImageUnits() > 0);
        CHECK(ctx.maxVertexAttribs() > 0);
    }
}
