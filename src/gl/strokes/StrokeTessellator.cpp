#include "nfx/graphics/gl/strokes/StrokeTessellator.h"

#include "internal/runtime/Error.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nfx::graphics::gl
{
    namespace
    {
        constexpr std::size_t kMaxU16IndexableVertices = 65535;

        struct Point2
        {
            float x = 0.0f;
            float y = 0.0f;
        };

        [[nodiscard]] bool nearlyEqual(float a, float b) noexcept
        {
            return std::fabs(a - b) <= 1.0e-6f;
        }

        [[nodiscard]] bool samePoint(const Point2& a, const Point2& b) noexcept
        {
            return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y);
        }

        [[nodiscard]] std::uint8_t toU8(float v) noexcept
        {
            const float clamped = std::clamp(v, 0.0f, 1.0f);
            return static_cast<std::uint8_t>(std::lround(clamped * 255.0f));
        }

        [[nodiscard]] StrokeVertex2D makeVertex(const Point2& p, const StrokeStyle& style) noexcept
        {
            StrokeVertex2D v;
            v.x = p.x;
            v.y = p.y;
            v.r = toU8(style.color[0]);
            v.g = toU8(style.color[1]);
            v.b = toU8(style.color[2]);
            v.a = toU8(style.color[3]);
            return v;
        }

        [[nodiscard]] bool computeDirAndNormal(
            const Point2& a, const Point2& b, float halfWidth, Point2& dir, Point2& normal)
        {
            const float dx = b.x - a.x;
            const float dy = b.y - a.y;
            const float len = std::sqrt(dx * dx + dy * dy);
            if (len <= 1.0e-6f)
            {
                return false;
            }

            dir = { dx / len, dy / len };
            normal = { -dir.y * halfWidth, dir.x * halfWidth };
            return true;
        }
    } // namespace

    bool StrokeTessellator::isValidStrokeStyle(const StrokeStyle& style) const noexcept
    {
        if (style.width <= 0.0f)
        {
            return false;
        }
        if (style.miterLimit < 1.0f)
        {
            return false;
        }
        return true;
    }

    StrokeMesh2D StrokeTessellator::tessellate(const StrokePolyline2D& polyline, const StrokeStyle& style) const
    {
        StrokeMesh2D mesh;
        if (!isValidStrokeStyle(style))
        {
            return mesh;
        }
        if (polyline.xy == nullptr)
        {
            return mesh;
        }
        if (polyline.pointCount < 2)
        {
            return mesh;
        }

        std::vector<Point2> points;
        points.reserve(polyline.pointCount + (polyline.closed ? 1 : 0));
        for (std::size_t i = 0; i < polyline.pointCount; ++i)
        {
            const Point2 p{ polyline.xy[i * 2], polyline.xy[i * 2 + 1] };
            if (!points.empty() && samePoint(points.back(), p))
            {
                continue;
            }
            points.push_back(p);
        }

        if (polyline.closed)
        {
            if (points.size() >= 2 && !samePoint(points.front(), points.back()))
            {
                points.push_back(points.front());
            }
        }

        if (points.size() < 2)
        {
            return mesh;
        }

        const float halfWidth = style.width * 0.5f;
        const std::size_t segCount = points.size() - 1;

        struct SegmentData
        {
            Point2 p0;
            Point2 p1;
            Point2 dir;
            Point2 normal;
            std::uint16_t l0 = 0;
            std::uint16_t r0 = 0;
            std::uint16_t l1 = 0;
            std::uint16_t r1 = 0;
        };

        std::vector<SegmentData> segments;
        segments.reserve(segCount);

        for (std::size_t i = 0; i < segCount; ++i)
        {
            SegmentData seg;
            seg.p0 = points[i];
            seg.p1 = points[i + 1];
            if (!computeDirAndNormal(seg.p0, seg.p1, halfWidth, seg.dir, seg.normal))
            {
                continue;
            }

            const Point2 l0{ seg.p0.x + seg.normal.x, seg.p0.y + seg.normal.y };
            const Point2 r0{ seg.p0.x - seg.normal.x, seg.p0.y - seg.normal.y };
            const Point2 l1{ seg.p1.x + seg.normal.x, seg.p1.y + seg.normal.y };
            const Point2 r1{ seg.p1.x - seg.normal.x, seg.p1.y - seg.normal.y };

            if (mesh.vertices.size() + 4 > kMaxU16IndexableVertices)
            {
                logError(
                    "StrokeTessellator",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    "Polyline stroke exceeds uint16 index capacity during segment expansion. Returning empty mesh");
                return {};
            }

            seg.l0 = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(l0, style));
            seg.r0 = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(r0, style));
            seg.l1 = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(l1, style));
            seg.r1 = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(r1, style));

            mesh.indices.push_back(seg.l0);
            mesh.indices.push_back(seg.r0);
            mesh.indices.push_back(seg.l1);
            mesh.indices.push_back(seg.r0);
            mesh.indices.push_back(seg.r1);
            mesh.indices.push_back(seg.l1);

            segments.push_back(seg);
        }

        if (segments.empty())
        {
            return mesh;
        }

        const std::size_t joinStart = polyline.closed ? 0 : 1;
        const std::size_t joinEndExclusive = polyline.closed ? segments.size() : (segments.size());

        for (std::size_t i = joinStart; i < joinEndExclusive; ++i)
        {
            const SegmentData& prev =
                polyline.closed ? segments[(i + segments.size() - 1) % segments.size()] : segments[i - 1];
            const SegmentData& next = segments[i];

            const float cross = prev.dir.x * next.dir.y - prev.dir.y * next.dir.x;
            if (std::fabs(cross) <= 1.0e-6f)
            {
                continue;
            }

            if (mesh.vertices.size() + 1 > kMaxU16IndexableVertices)
            {
                logError(
                    "StrokeTessellator",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    "Polyline stroke exceeds uint16 index capacity during segment expansion. Returning empty mesh");
                return {};
            }

            const Point2 center = next.p0;
            const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(center, style));

            if (cross > 0.0f)
            {
                mesh.indices.push_back(prev.l1);
                mesh.indices.push_back(next.l0);
                mesh.indices.push_back(c);
            }
            else
            {
                mesh.indices.push_back(prev.r1);
                mesh.indices.push_back(c);
                mesh.indices.push_back(next.r0);
            }
        }

        return mesh;
    }
} // namespace nfx::graphics::gl
