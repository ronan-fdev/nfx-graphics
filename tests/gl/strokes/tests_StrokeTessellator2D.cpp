#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <vector>

using namespace nfx::graphics::gl;

TEST_SUITE("StrokeTessellator2D")
{
    TEST_CASE("stroke style defaults are valid")
    {
        const StrokeTessellator2D tess;
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
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.width = 0.0f;
        CHECK_FALSE(tess.isValidStrokeStyle(style));

        style.width = 1.0f;
        style.miterLimit = 0.0f;
        CHECK_FALSE(tess.isValidStrokeStyle(style));
    }

    TEST_CASE("invalid polyline returns empty mesh")
    {
        const StrokeTessellator2D tess;
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
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.width = 0.5f;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK_FALSE(mesh.vertices.empty());
        CHECK_FALSE(mesh.indices.empty());
    }

    TEST_CASE("sub-unit positive width tessellates")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.width = 0.5f;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK_FALSE(mesh.vertices.empty());
        CHECK_FALSE(mesh.indices.empty());
    }

    TEST_CASE("sub-unit positive width tessellates for closed polyline")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.width = 0.5f;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, 1.5f };
        const StrokePolyline2D polyline{ points, 3, true };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK_FALSE(mesh.vertices.empty());
        CHECK_FALSE(mesh.indices.empty());
        CHECK((mesh.indices.size() % 3) == 0);
    }

    TEST_CASE("sub-unit positive width tessellates with round join and cap")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.width = 0.5f;
        style.join = StrokeJoin::Round;
        style.cap = StrokeCap::Round;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f, 2.0f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK_FALSE(mesh.vertices.empty());
        CHECK_FALSE(mesh.indices.empty());
    }

    TEST_CASE("single segment tessellates to one quad")
    {
        const StrokeTessellator2D tess;
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
        const StrokeTessellator2D tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 8);
        CHECK(mesh.indices.size() == 12);
    }

    TEST_CASE("right angle polyline adds one bevel join triangle")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Bevel;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 9);
        CHECK(mesh.indices.size() == 15);
    }

    TEST_CASE("right turn join keeps front-facing winding")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Bevel;

        // Right turn at (1, 0): first segment along +X, second along -Y
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        REQUIRE(mesh.vertices.size() == 9);
        REQUIRE(mesh.indices.size() == 15);

        const std::uint16_t i0 = mesh.indices[12];
        const std::uint16_t i1 = mesh.indices[13];
        const std::uint16_t i2 = mesh.indices[14];

        const auto& a = mesh.vertices[i0];
        const auto& b = mesh.vertices[i1];
        const auto& c = mesh.vertices[i2];

        const float abx = b.x - a.x;
        const float aby = b.y - a.y;
        const float acx = c.x - a.x;
        const float acy = c.y - a.y;
        const float crossZ = abx * acy - aby * acx;

        // Segment quads are emitted CCW. Join triangles must keep same winding
        CHECK(crossZ > 0.0f);
    }

    TEST_CASE("closed polyline creates joins at all corners")
    {
        const StrokeTessellator2D tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, true };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() >= 15);
        CHECK(mesh.indices.size() >= 27);
        CHECK((mesh.indices.size() % 3) == 0);
    }

    TEST_CASE("coincident points are skipped")
    {
        const StrokeTessellator2D tess;
        const StrokeStyle style;
        const float points[] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 4);
        CHECK(mesh.indices.size() == 6);
    }

    TEST_CASE("overflow of uint16 vertex budget returns empty mesh")
    {
        const StrokeTessellator2D tess;
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

    TEST_CASE("miter join inserts corner vertex near analytical intersection")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Miter;
        style.miterLimit = 8.0f;

        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() >= 9);
        CHECK(mesh.indices.size() >= 15);

        bool foundMiter = false;
        for (const auto& v : mesh.vertices)
        {
            // Miter join: analytical intersection of outer tangent lines offset by halfWidth=0.5
            // For segments (0,0)->(1,0) and (1,0)->(2,1), the outer-side intersection point is ≈ (1.207, -0.5)
            if (v.x == doctest::Approx(1.20710678f).epsilon(0.001f) && v.y == doctest::Approx(-0.5f).epsilon(0.001f))
            {
                foundMiter = true;
                break;
            }
        }
        CHECK(foundMiter);
    }

    TEST_CASE("sharp miter join falls back to bevel when limit is exceeded")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Miter;
        style.miterLimit = 1.1f;

        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.01f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 9);
        CHECK(mesh.indices.size() == 15);

        bool foundCenter = false;
        for (const auto& v : mesh.vertices)
        {
            if (v.x == doctest::Approx(1.0f).epsilon(0.001f) && v.y == doctest::Approx(0.0f).epsilon(0.001f))
            {
                foundCenter = true;
                break;
            }
        }
        CHECK(foundCenter);
    }

    TEST_CASE("round join emits arc vertices around the corner")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Round;

        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() > 9);
        CHECK(mesh.indices.size() > 15);

        bool foundArcPoint = false;
        for (const auto& v : mesh.vertices)
        {
            // Quarter-circle arc at -45° on the outer side: joinPoint=(1,0), radius=0.5
            // Expected arc point: (1 + 0.5*cos(45°), 0 - 0.5*sin(45°)) ≈ (1.3536, -0.3536)
            if (v.x == doctest::Approx(1.3535534f).epsilon(0.05f) && v.y == doctest::Approx(-0.3535534f).epsilon(0.05f))
            {
                foundArcPoint = true;
                break;
            }
        }
        CHECK(foundArcPoint);
    }

    TEST_CASE("round join near U-turn emits half-circle arc")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.join = StrokeJoin::Round;

        // Near U-turn at (1, 0): almost opposite direction with tiny positive Y to keep left-turn sign stable
        const float points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.001f };
        const StrokePolyline2D polyline{ points, 3, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() > 9);
        CHECK(mesh.indices.size() > 15);

        bool foundHalfCircleMid = false;
        for (const auto& v : mesh.vertices)
        {
            // Midpoint of the expected near-semicircle arc (radius=0.5) is around (1.5, 0.0)
            if (v.x == doctest::Approx(1.5f).epsilon(0.08f) && v.y == doctest::Approx(0.0f).epsilon(0.08f))
            {
                foundHalfCircleMid = true;
                break;
            }
        }
        CHECK(foundHalfCircleMid);
    }

    TEST_CASE("square caps extend stroke by half width at both ends")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.cap = StrokeCap::Square;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() == 8);
        CHECK(mesh.indices.size() == 18);

        bool hasStartLeftExt = false;
        bool hasStartRightExt = false;
        bool hasEndLeftExt = false;
        bool hasEndRightExt = false;

        for (const auto& v : mesh.vertices)
        {
            if (v.x == doctest::Approx(-0.5f).epsilon(0.001f) && v.y == doctest::Approx(0.5f).epsilon(0.001f))
            {
                hasStartLeftExt = true;
            }
            if (v.x == doctest::Approx(-0.5f).epsilon(0.001f) && v.y == doctest::Approx(-0.5f).epsilon(0.001f))
            {
                hasStartRightExt = true;
            }
            if (v.x == doctest::Approx(2.5f).epsilon(0.001f) && v.y == doctest::Approx(0.5f).epsilon(0.001f))
            {
                hasEndLeftExt = true;
            }
            if (v.x == doctest::Approx(2.5f).epsilon(0.001f) && v.y == doctest::Approx(-0.5f).epsilon(0.001f))
            {
                hasEndRightExt = true;
            }
        }

        CHECK(hasStartLeftExt);
        CHECK(hasStartRightExt);
        CHECK(hasEndLeftExt);
        CHECK(hasEndRightExt);
    }

    TEST_CASE("round caps add semicircle geometry at both endpoints")
    {
        const StrokeTessellator2D tess;
        StrokeStyle style;
        style.cap = StrokeCap::Round;

        const float points[] = { 0.0f, 0.0f, 2.0f, 0.0f };
        const StrokePolyline2D polyline{ points, 2, false };

        const StrokeMesh2D mesh = tess.tessellate(polyline, style);
        CHECK(mesh.vertices.size() > 22);
        CHECK(mesh.indices.size() > 60);
        CHECK(mesh.indices.size() == (mesh.vertices.size() - 2) * 3);

        bool hasStartCenter = false;
        bool hasEndCenter = false;
        bool extendsBeforeStart = false;
        bool extendsAfterEnd = false;

        for (const auto& v : mesh.vertices)
        {
            if (v.x == doctest::Approx(0.0f).epsilon(0.001f) && v.y == doctest::Approx(0.0f).epsilon(0.001f))
            {
                hasStartCenter = true;
            }
            if (v.x == doctest::Approx(2.0f).epsilon(0.001f) && v.y == doctest::Approx(0.0f).epsilon(0.001f))
            {
                hasEndCenter = true;
            }
            if (v.x < -0.1f)
            {
                extendsBeforeStart = true;
            }
            if (v.x > 2.1f)
            {
                extendsAfterEnd = true;
            }
        }

        CHECK(hasStartCenter);
        CHECK(hasEndCenter);
        CHECK(extendsBeforeStart);
        CHECK(extendsAfterEnd);
    }
}
