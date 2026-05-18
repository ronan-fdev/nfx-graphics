#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("ScissorRect")
{
    TEST_CASE("default rect is valid 1x1 at origin")
    {
        const ScissorRect rect;
        CHECK(rect.x == 0);
        CHECK(rect.y == 0);
        CHECK(rect.width == 1);
        CHECK(rect.height == 1);
        CHECK(rect.isValid());
        CHECK(rect.right() == 1);
        CHECK(rect.top() == 1);
    }

    TEST_CASE("invalid dimensions are rejected")
    {
        CHECK_FALSE((ScissorRect{ 0, 0, 0, 1 }).isValid());
        CHECK_FALSE((ScissorRect{ 0, 0, 1, 0 }).isValid());
        CHECK_FALSE((ScissorRect{ 0, 0, -1, 1 }).isValid());
        CHECK_FALSE((ScissorRect{ 0, 0, 1, -1 }).isValid());
    }

    TEST_CASE("right and top are exclusive edges")
    {
        const ScissorRect rect{ 10, 20, 30, 40 };
        CHECK(rect.right() == 40);
        CHECK(rect.top() == 60);
    }
}
