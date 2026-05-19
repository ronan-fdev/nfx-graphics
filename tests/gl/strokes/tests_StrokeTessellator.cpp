#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <vector>

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

    TEST_CASE("sub-unit positive width tessellates")
    {
        const StrokeTessellator tess;
        StrokeStyle style;
        style.width = 0.5f;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK_FALSE(mesh.vertices.empty());
        CHECK_FALSE(mesh.indices.empty());
    }

    TEST_CASE("single segment tessellates to one quad")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        REQUIRE(mesh.vertices.size() == 4);
        REQUIRE(mesh.indices.size() == 6);

        CHECK(mesh.vertices[0].x == doctest::Approx(0.0f));
        CHECK(mesh.vertices[0].y == doctest::Approx(0.5f));
        CHECK(mesh.vertices[1].x == doctest::Approx(0.0f));
        CHECK(mesh.vertices[1].y == doctest::Approx(-0.5f));
        CHECK(mesh.vertices[2].x == doctest::Approx(2.0f));
        CHECK(mesh.vertices[2].y == doctest::Approx(0.5f));
        CHECK(mesh.vertices[3].x == doctest::Approx(2.0f));
        CHECK(mesh.vertices[3].y == doctest::Approx(-0.5f));
    }

    TEST_CASE("two aligned segments tessellate without bevel join")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 8);
        CHECK(mesh.indices.size() == 12);
    }

    TEST_CASE("right angle polyline adds one bevel join triangle")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 9);
        CHECK(mesh.indices.size() == 15);
    }

    TEST_CASE("closed polyline creates joins at all corners")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, true };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 15);
        CHECK(mesh.indices.size() == 27);
    }

    TEST_CASE("coincident points are skipped")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 4);
        CHECK(mesh.indices.size() == 6);
    }

    TEST_CASE("overflow of uint16 vertex budget returns empty mesh")
    {
        const StrokeTessellator tess;
        const StrokeStyle style;

        constexpr std::size_t pointCount = 17000;
        std::vector<float> xy(pointCount * 2, 0.0f);
        for (std::size_t i = 0; i < pointCount; ++i)
        {
            xy[i * 2] = static_cast<float>(i);
            xy[i * 2 + 1] = 0.0f;
        }

        const StrokePolyline2D polyline{ xy.data(), pointCount, false };
        const StrokeMesh2D mesh = tess.tessellate(polyline, style);

        CHECK(mesh.vertices.empty());
        CHECK(mesh.indices.empty());
    }
}
