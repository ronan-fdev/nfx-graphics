#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("SurfaceExtent")
{
    TEST_CASE("default extent is invalid")
    {
        const SurfaceExtent extent;
        CHECK(extent.width == 0);
        CHECK(extent.height == 0);
        CHECK_FALSE(extent.isValid());
    }

    TEST_CASE("strictly positive dimensions are valid")
    {
        CHECK((SurfaceExtent{ 1, 1 }).isValid());
        CHECK((SurfaceExtent{ 1280, 720 }).isValid());
        CHECK_FALSE((SurfaceExtent{ 0, 720 }).isValid());
        CHECK_FALSE((SurfaceExtent{ 1280, 0 }).isValid());
        CHECK_FALSE((SurfaceExtent{ -1, 720 }).isValid());
    }
}
