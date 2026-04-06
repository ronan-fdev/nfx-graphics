#include <doctest/doctest.h>

#include <nfx/Graphics.h>

namespace gl = nfx::graphics::gl;

TEST_SUITE("ViewportRect")
{
    TEST_CASE("default viewport is valid and one pixel wide/high")
    {
        const gl::ViewportRect viewport;
        CHECK(viewport.x == 0);
        CHECK(viewport.y == 0);
        CHECK(viewport.width == 1);
        CHECK(viewport.height == 1);
        CHECK(viewport.isValid());
        CHECK(viewport.right() == 1);
        CHECK(viewport.top() == 1);
    }

    TEST_CASE("zero or negative dimensions are invalid")
    {
        CHECK(!gl::ViewportRect{ 0, 0, 0, 1 }.isValid());
        CHECK(!gl::ViewportRect{ 0, 0, 1, 0 }.isValid());
        CHECK(!gl::ViewportRect{ 0, 0, -1, 1 }.isValid());
        CHECK(!gl::ViewportRect{ 0, 0, 1, -1 }.isValid());
    }

    TEST_CASE("right and top edges are exclusive")
    {
        const gl::ViewportRect viewport{ 10, 20, 640, 480 };
        CHECK(viewport.isValid());
        CHECK(viewport.right() == 650);
        CHECK(viewport.top() == 500);
    }
}
