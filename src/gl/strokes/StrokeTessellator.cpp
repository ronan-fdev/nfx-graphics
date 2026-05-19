#include "nfx/graphics/gl/strokes/StrokeTessellator.h"

#include "internal/runtime/Error.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numbers>
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

        [[nodiscard]] Point2 add(const Point2& a, const Point2& b) noexcept
        {
            return { a.x + b.x, a.y + b.y };
        }

        [[nodiscard]] Point2 sub(const Point2& a, const Point2& b) noexcept
        {
            return { a.x - b.x, a.y - b.y };
        }

        [[nodiscard]] Point2 scale(const Point2& p, float s) noexcept
        {
            return { p.x * s, p.y * s };
        }

        [[nodiscard]] float dot(const Point2& a, const Point2& b) noexcept
        {
            return a.x * b.x + a.y * b.y;
        }

        [[nodiscard]] float cross(const Point2& a, const Point2& b) noexcept
        {
            return a.x * b.y - a.y * b.x;
        }

        [[nodiscard]] Point2 normalize(const Point2& p) noexcept
        {
            const float len = std::sqrt(p.x * p.x + p.y * p.y);
            if (len <= 1.0e-6f)
            {
                return { 0.0f, 0.0f };
            }
            return { p.x / len, p.y / len };
        }

        [[nodiscard]] bool intersectLines(
            const Point2& p0, const Point2& d0, const Point2& p1, const Point2& d1, Point2& out)
        {
            const float denom = cross(d0, d1);
            if (std::fabs(denom) <= 1.0e-6f)
            {
                return false;
            }

            const Point2 delta = sub(p1, p0);
            const float t = cross(delta, d1) / denom;
            out = add(p0, scale(d0, t));
            return true;
        }

        [[nodiscard]] std::size_t roundSegments(float theta) noexcept
        {
            const float absTheta = std::fabs(theta);
            const float maxStep = 0.18f;
            const std::size_t count = static_cast<std::size_t>(std::ceil(absTheta / maxStep));
            return std::max<std::size_t>(6, count);
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
            Point2 left0;
            Point2 right0;
            Point2 left1;
            Point2 right1;
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

            seg.left0 = l0;
            seg.right0 = r0;
            seg.left1 = l1;
            seg.right1 = r1;

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
            mesh.indices.push_back(seg.r1);
            mesh.indices.push_back(seg.l0);
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

            const Point2 joinPoint = next.p0;
            const Point2 outerPrevLeft = prev.left1;
            const Point2 outerNextLeft = next.left0;
            const Point2 outerPrevRight = prev.right1;
            const Point2 outerNextRight = next.right0;

            const float turnCross = prev.dir.x * next.dir.y - prev.dir.y * next.dir.x;
            if (std::fabs(turnCross) <= 1.0e-6f)
            {
                continue;
            }

            const bool isLeftTurn = turnCross > 0.0f;
            const Point2& pOuter0 = isLeftTurn ? outerPrevRight : outerPrevLeft;
            const Point2& pOuter1 = isLeftTurn ? outerNextRight : outerNextLeft;
            const std::uint16_t outerPrev = isLeftTurn ? prev.r1 : prev.l1;
            const std::uint16_t outerNext = isLeftTurn ? next.r0 : next.l0;

            if (style.join == StrokeJoin::Bevel)
            {
                if (mesh.vertices.size() + 1 > kMaxU16IndexableVertices)
                {
                    logError(
                        "StrokeTessellator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        "Polyline stroke exceeds uint16 index capacity during Bevel join. Returning empty mesh");
                    return {};
                }

                const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(joinPoint, style));
                mesh.indices.push_back(outerPrev);
                mesh.indices.push_back(isLeftTurn ? outerNext : c);
                mesh.indices.push_back(isLeftTurn ? c : outerNext);
                continue;
            }

            if (style.join == StrokeJoin::Miter)
            {
                Point2 miterDir0 = prev.dir;
                Point2 miterDir1 = next.dir;
                Point2 miterPoint;
                const bool ok = intersectLines(pOuter0, miterDir0, pOuter1, miterDir1, miterPoint);
                if (!ok)
                {
                    if (mesh.vertices.size() + 1 > kMaxU16IndexableVertices)
                    {
                        logError(
                            "StrokeTessellator",
                            internal::runtime::ErrorLevel::Warn,
                            internal::runtime::ErrorKind::Recoverable,
                            "Polyline stroke exceeds uint16 index capacity during Miter fallback Bevel join. Returning "
                            "empty mesh");
                        return {};
                    }
                    const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
                    mesh.vertices.push_back(makeVertex(joinPoint, style));
                    mesh.indices.push_back(outerPrev);
                    mesh.indices.push_back(isLeftTurn ? outerNext : c);
                    mesh.indices.push_back(isLeftTurn ? c : outerNext);
                    continue;
                }

                const Point2 delta = sub(miterPoint, joinPoint);
                const float miterLen = std::sqrt(dot(delta, delta));

                const Point2 outerDir0 = normalize(sub(pOuter0, joinPoint));
                const Point2 outerDir1 = normalize(sub(pOuter1, joinPoint));
                const Point2 outerBisector = normalize(add(outerDir0, outerDir1));
                if ((outerBisector.x != 0.0f || outerBisector.y != 0.0f) && dot(delta, outerBisector) < 0.0f)
                {
                    miterPoint = add(joinPoint, scale(outerBisector, miterLen));
                }

                const float maxMiter = halfWidth * style.miterLimit;
                if (miterLen > maxMiter)
                {
                    if (mesh.vertices.size() + 1 > kMaxU16IndexableVertices)
                    {
                        logError(
                            "StrokeTessellator",
                            internal::runtime::ErrorLevel::Warn,
                            internal::runtime::ErrorKind::Recoverable,
                            "Polyline stroke exceeds uint16 index capacity during Miter fallback Bevel join. Returning "
                            "empty mesh");
                        return {};
                    }
                    const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
                    mesh.vertices.push_back(makeVertex(joinPoint, style));
                    mesh.indices.push_back(outerPrev);
                    mesh.indices.push_back(isLeftTurn ? outerNext : c);
                    mesh.indices.push_back(isLeftTurn ? c : outerNext);
                    continue;
                }

                if (mesh.vertices.size() + 2 > kMaxU16IndexableVertices)
                {
                    logError(
                        "StrokeTessellator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        "Polyline stroke exceeds uint16 index capacity during Miter join. Returning empty mesh");
                    return {};
                }

                const std::uint16_t m = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(miterPoint, style));
                const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(joinPoint, style));

                if (isLeftTurn)
                {
                    mesh.indices.push_back(outerPrev);
                    mesh.indices.push_back(m);
                    mesh.indices.push_back(c);

                    mesh.indices.push_back(c);
                    mesh.indices.push_back(m);
                    mesh.indices.push_back(outerNext);
                }
                else
                {
                    mesh.indices.push_back(outerPrev);
                    mesh.indices.push_back(c);
                    mesh.indices.push_back(m);

                    mesh.indices.push_back(c);
                    mesh.indices.push_back(outerNext);
                    mesh.indices.push_back(m);
                }
                continue;
            }

            if (style.join == StrokeJoin::Round)
            {
                const Point2 start = normalize(sub(pOuter0, joinPoint));
                const Point2 end = normalize(sub(pOuter1, joinPoint));
                const float theta = std::atan2(cross(start, end), dot(start, end));
                const std::size_t arcSegments = roundSegments(theta);

                if (mesh.vertices.size() + arcSegments > kMaxU16IndexableVertices)
                {
                    logError(
                        "StrokeTessellator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        "Polyline stroke exceeds uint16 index capacity during Round join. Returning empty mesh");
                    return {};
                }

                const std::uint16_t center = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(joinPoint, style));

                const std::uint16_t startBoundary = outerPrev;
                const std::uint16_t endBoundary = outerNext;

                const float angle0 = std::atan2(start.y, start.x);
                const float angle1 = std::atan2(end.y, end.x);
                float deltaAngle = angle1 - angle0;
                if (isLeftTurn && deltaAngle < 0.0f)
                {
                    deltaAngle += 2.0f * std::numbers::pi_v<float>;
                }
                else if (!isLeftTurn && deltaAngle > 0.0f)
                {
                    deltaAngle -= 2.0f * std::numbers::pi_v<float>;
                }

                std::uint16_t prevArc = startBoundary;
                for (std::size_t s = 1; s < arcSegments; ++s)
                {
                    const float t = static_cast<float>(s) / static_cast<float>(arcSegments);
                    const float angle = angle0 + deltaAngle * t;
                    const Point2 arcPoint{ joinPoint.x + std::cos(angle) * halfWidth,
                                           joinPoint.y + std::sin(angle) * halfWidth };
                    const std::uint16_t idx = static_cast<std::uint16_t>(mesh.vertices.size());
                    mesh.vertices.push_back(makeVertex(arcPoint, style));

                    mesh.indices.push_back(center);
                    mesh.indices.push_back(isLeftTurn ? prevArc : idx);
                    mesh.indices.push_back(isLeftTurn ? idx : prevArc);

                    prevArc = idx;
                }

                mesh.indices.push_back(center);
                mesh.indices.push_back(isLeftTurn ? prevArc : endBoundary);
                mesh.indices.push_back(isLeftTurn ? endBoundary : prevArc);
                continue;
            }

            if (mesh.vertices.size() + 1 > kMaxU16IndexableVertices)
            {
                logError(
                    "StrokeTessellator",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    "Polyline stroke exceeds uint16 index capacity. Returning empty mesh");
                return {};
            }

            const std::uint16_t c = static_cast<std::uint16_t>(mesh.vertices.size());
            mesh.vertices.push_back(makeVertex(joinPoint, style));
            mesh.indices.push_back(outerPrev);
            mesh.indices.push_back(isLeftTurn ? outerNext : c);
            mesh.indices.push_back(isLeftTurn ? c : outerNext);
        }

        if (!polyline.closed)
        {
            const SegmentData& first = segments.front();
            const SegmentData& last = segments.back();

            if (style.cap == StrokeCap::Square)
            {
                if (mesh.vertices.size() + 4 > kMaxU16IndexableVertices)
                {
                    logError(
                        "StrokeTessellator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        "Polyline stroke exceeds uint16 index capacity during Square cap. Returning empty mesh");
                    return {};
                }

                const Point2 startOffset = scale(first.dir, -halfWidth);
                const Point2 startLeftExt = add(first.left0, startOffset);
                const Point2 startRightExt = add(first.right0, startOffset);

                const std::uint16_t startLeftExtIdx = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(startLeftExt, style));
                const std::uint16_t startRightExtIdx = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(startRightExt, style));

                mesh.indices.push_back(startLeftExtIdx);
                mesh.indices.push_back(startRightExtIdx);
                mesh.indices.push_back(first.l0);
                mesh.indices.push_back(startRightExtIdx);
                mesh.indices.push_back(first.r0);
                mesh.indices.push_back(first.l0);

                const Point2 endOffset = scale(last.dir, halfWidth);
                const Point2 endLeftExt = add(last.left1, endOffset);
                const Point2 endRightExt = add(last.right1, endOffset);

                const std::uint16_t endLeftExtIdx = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(endLeftExt, style));
                const std::uint16_t endRightExtIdx = static_cast<std::uint16_t>(mesh.vertices.size());
                mesh.vertices.push_back(makeVertex(endRightExt, style));

                mesh.indices.push_back(last.l1);
                mesh.indices.push_back(last.r1);
                mesh.indices.push_back(endLeftExtIdx);
                mesh.indices.push_back(last.r1);
                mesh.indices.push_back(endRightExtIdx);
                mesh.indices.push_back(endLeftExtIdx);
            }
            else if (style.cap == StrokeCap::Round)
            {
                const std::size_t arcSegments = roundSegments(std::numbers::pi_v<float>);
                const std::size_t capVerticesPerEnd = arcSegments;
                if (mesh.vertices.size() + capVerticesPerEnd * 2 > kMaxU16IndexableVertices)
                {
                    logError(
                        "StrokeTessellator",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        "Polyline stroke exceeds uint16 index capacity during Round cap. Returning empty mesh");
                    return {};
                }

                auto emitRoundCap = [&](const Point2& center,
                                        const Point2& capDir,
                                        std::uint16_t startBoundary,
                                        std::uint16_t endBoundary,
                                        const char* overflowMsg) -> bool {
                    if (mesh.vertices.size() + capVerticesPerEnd > kMaxU16IndexableVertices)
                    {
                        logError(
                            "StrokeTessellator",
                            internal::runtime::ErrorLevel::Warn,
                            internal::runtime::ErrorKind::Recoverable,
                            overflowMsg);
                        return false;
                    }

                    const std::uint16_t centerIdx = static_cast<std::uint16_t>(mesh.vertices.size());
                    mesh.vertices.push_back(makeVertex(center, style));

                    const Point2 capLeft{ -capDir.y, capDir.x };
                    std::uint16_t prev = startBoundary;
                    for (std::size_t s = 1; s < arcSegments; ++s)
                    {
                        const float t = static_cast<float>(s) / static_cast<float>(arcSegments);
                        const float angle = -0.5f * std::numbers::pi_v<float> + std::numbers::pi_v<float> * t;
                        const Point2 arcPoint =
                            add(center,
                                add(scale(capDir, std::cos(angle) * halfWidth),
                                    scale(capLeft, std::sin(angle) * halfWidth)));

                        const std::uint16_t idx = static_cast<std::uint16_t>(mesh.vertices.size());
                        mesh.vertices.push_back(makeVertex(arcPoint, style));

                        mesh.indices.push_back(centerIdx);
                        mesh.indices.push_back(prev);
                        mesh.indices.push_back(idx);
                        prev = idx;
                    }

                    mesh.indices.push_back(centerIdx);
                    mesh.indices.push_back(prev);
                    mesh.indices.push_back(endBoundary);
                    return true;
                };

                if (!emitRoundCap(
                        first.p0,
                        scale(first.dir, -1.0f),
                        first.l0,
                        first.r0,
                        "Polyline stroke exceeds uint16 index capacity during Round cap. Returning empty mesh"))
                {
                    return {};
                }

                if (!emitRoundCap(
                        last.p1,
                        last.dir,
                        last.r1,
                        last.l1,
                        "Polyline stroke exceeds uint16 index capacity during Round cap. Returning empty mesh"))
                {
                    return {};
                }
            }
        }

        return mesh;
    }
} // namespace nfx::graphics::gl
