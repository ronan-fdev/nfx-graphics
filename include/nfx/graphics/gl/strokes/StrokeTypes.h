#pragma once

/**
 * \file StrokeTypes.h
 * \brief Declares CPU-side stroke tessellation input and output types.
 */

#include <cstddef>
#include <cstdint>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Supported stroke join styles.
     */
    enum class StrokeJoin
    {
        Miter,
        Bevel,
        Round
    };

    /**
     * \brief Supported stroke cap styles.
     */
    enum class StrokeCap
    {
        Butt,
        Square,
        Round
    };

    /**
     * \brief Per-stroke style parameters used by CPU tessellation.
     */
    struct StrokeStyle
    {
        float width = 1.0f;
        StrokeJoin join = StrokeJoin::Miter;
        float miterLimit = 4.0f;
        StrokeCap cap = StrokeCap::Butt;
        float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    };

    /**
     * \brief Polyline input consumed by the stroke tessellator.
     */
    struct StrokePolyline2D
    {
        const float* xy = nullptr;
        std::size_t pointCount = 0;
        bool closed = false;
    };

    /**
     * \brief One CPU-side stroke vertex.
     */
    struct StrokeVertex2D
    {
        float x = 0.0f;
        float y = 0.0f;
        std::uint8_t r = 255;
        std::uint8_t g = 255;
        std::uint8_t b = 255;
        std::uint8_t a = 255;
    };

    /**
     * \brief CPU-side tessellated triangle mesh for one stroke.
     */
    struct StrokeMesh2D
    {
        std::vector<StrokeVertex2D> vertices;
        std::vector<std::uint16_t> indices;
    };
} // namespace nfx::graphics::gl
