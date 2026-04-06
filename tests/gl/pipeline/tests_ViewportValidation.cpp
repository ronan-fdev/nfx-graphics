#include <doctest/doctest.h>

#include "gl/pipeline/detail/ViewportValidation.h"

namespace gl = nfx::graphics::gl;

TEST_SUITE("ViewportValidation")
{
    TEST_CASE("viewport fully inside surface is valid")
    {
        CHECK(gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1280, 720 }, 1280, 720));
        CHECK(gl::detail::isViewportInsideSurface(gl::ViewportRect{ 100, 50, 300, 200 }, 1280, 720));
    }

    TEST_CASE("viewport outside or invalid is rejected")
    {
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ -1, 0, 10, 10 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, -1, 10, 10 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 1200, 700, 200, 30 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 0, 10 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 10, 0 }, 1280, 720));
    }

    TEST_CASE("policy is reject at surface bounds (no implicit clamp)")
    {
        CHECK(gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1280, 720 }, 1280, 720));

        // Extending by one pixel outside the surface must be rejected
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1281, 720 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1280, 721 }, 1280, 720));
    }

    TEST_CASE("edge semantics are strict and deterministic")
    {
        // One pixel in the bottom-right corner is valid: right/top are exclusive
        CHECK(gl::detail::isViewportInsideSurface(gl::ViewportRect{ 1279, 719, 1, 1 }, 1280, 720));

        // Starting exactly at the right/top edge with positive size is outside
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 1280, 0, 1, 1 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 720, 1, 1 }, 1280, 720));

        // Width/height that spill over one axis are rejected
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 1279, 0, 2, 1 }, 1280, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 719, 1, 2 }, 1280, 720));
    }

    TEST_CASE("surface extent must be valid")
    {
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1, 1 }, 0, 720));
        CHECK(!gl::detail::isViewportInsideSurface(gl::ViewportRect{ 0, 0, 1, 1 }, 1280, 0));
    }
}
