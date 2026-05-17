#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/Context.h>
#include <nfx/graphics/gl/core/framebuffers/Renderbuffer.h>
#include <nfx/graphics/gl/core/shaders/ShaderProgram.h>
#include <nfx/graphics/gl/core/textures/Sampler.h>
#include <nfx/graphics/gl/core/textures/Texture2D.h>
#include <nfx/graphics/gl/core/textures/TextureCube.h>

#include "../test_helpers/GLContextFixture.h"

#ifndef NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS
    #error "GL runtime tests require NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS"
#endif

TEST_SUITE("CoreRuntime")
{
    TEST_CASE("Texture2D allocate creates a valid runtime texture")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Texture2D::Params params;
        params.internalFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8;
        params.generateMipmaps = false;

        const auto tex = nfx::graphics::gl::Texture2D::allocate(4, 4, params);
        CHECK(tex.isValid());
        CHECK(tex.width() == 4);
        CHECK(tex.height() == 4);
    }

    TEST_CASE("TextureCube allocate creates a valid runtime cubemap")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::TextureCube::Params params;
        params.internalFormat = nfx::graphics::gl::TextureCube::InternalFormat::RGBA8;
        params.generateMipmaps = false;
        params.mipLevels = 1;

        const auto cube = nfx::graphics::gl::TextureCube::allocate(4, params);
        CHECK(cube.isValid());
        CHECK(cube.size() == 4);
    }

    TEST_CASE("Renderbuffer allocate creates a valid runtime renderbuffer")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        nfx::graphics::gl::Renderbuffer rb;
        rb.allocate(nfx::graphics::gl::Renderbuffer::Format::Depth24, 4, 4);

        CHECK(rb.isValid());
        CHECK(rb.width() == 4);
        CHECK(rb.height() == 4);
    }

    TEST_CASE("Sampler create allocates a valid runtime sampler")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        const auto sampler = nfx::graphics::gl::Sampler::create();
        CHECK(sampler.isValid());
    }

    TEST_CASE("ShaderProgram fromSources creates a valid runtime graphics program")
    {
        nfx::tests::GLContextFixture fixture;
        REQUIRE(fixture.available());
        REQUIRE(nfx::graphics::gl::Context::initialize());
        REQUIRE(nfx::graphics::gl::Context::isInitialized());

        const auto program = nfx::graphics::gl::ShaderProgram::fromSources(
            { { nfx::graphics::gl::ShaderProgram::Stage::Vertex,
                "#version 450 core\n"
                "layout(location = 0) in vec3 aPos;\n"
                "void main(){ gl_Position = vec4(aPos, 1.0); }\n" },
              { nfx::graphics::gl::ShaderProgram::Stage::Fragment,
                "#version 450 core\n"
                "out vec4 FragColor;\n"
                "void main(){ FragColor = vec4(1.0, 0.0, 0.0, 1.0); }\n" } });

        CHECK(program.isValid());
    }
}
