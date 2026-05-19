#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("StrokeTessellator")
{
    TEST_CASE("stroke style defaults are valid")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        CHECK(style.width == doctest::Approx(1.0f));
        CHECK(style.join == StrokeJoin::Miter);
        CHECK(style.miterLimit == doctest::Approx(4.0f));
        CHECK(style.cap == StrokeCap::Butt);
        CHECK(style.color[0] == doctest::Approx(1.0f));
        CHECK(style.color[1] == doctest::Approx(1.0f));
        CHECK(style.color[2] == doctest::Approx(1.0f));
        CHECK(style.color[3] == doctest::Approx(1.0f));
        CHECK(tess.isValidStrokeStyle(style));
    }

    TEST_CASE("invalid stroke style is rejected")
    {
        const StrokeTessellator tess;
        StrokeStyle style;
        style.width = 0.0f;
        CHECK_FALSE(tess.isValidStrokeStyle(style));

        style.width = 1.0f;
        style.miterLimit = 0.0f;
        CHECK_FALSE(tess.isValidStrokeStyle(style));
    }

    TEST_CASE("invalid polyline returns empty mesh")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;

        CHECK(tess.tessellate({}, style).vertices.empty());
        CHECK(tess.tessellate({}, style).indices.empty());

        const float onePoint[] = { 0.0f, 0.0f };
        const StrokePolyline2D polyline{ onePoint, 1, false };
        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.empty());
        CHECK(mesh.indices.empty());
    }
}
