#pragma once

/**
 * \file Polygon2DPass.h
 * \brief Declares an overlay pass rendering filled convex 2D polygons in screen space.
 */

#include "nfx/graphics/gl/core/buffers/Buffer.h"
#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/resources/Handle.h"
#include "RenderPass.h"

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Opaque handle identifying one polygon item owned by Polygon2DPass.
     */
    struct Polygon2DTag
    {
    };

    using Polygon2DHandle = Handle<Polygon2DTag>;

    /**
     * \brief Per-item style for 2D filled polygons.
     */
    struct Polygon2DStyle
    {
        float color[3] = { 1.0f, 1.0f, 1.0f };
        float alpha = 1.0f;
    };

    /**
     * \brief Overlay pass rendering filled convex polygons in pixel-space.
     *
     * Coordinates use screen pixels with origin at top-left.
     *
     * Typical usage:
     * - buttons/panels via addRect()
     * - hexagons/circles via addConvexPolygon() using precomputed points
     *
     * This pass is convex-only by design. Concave shapes should be triangulated beforehand
     * (submit each triangle as a 3-point convex polygon).
     */
    class Polygon2DPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures used by this pass.
         * \param color Target color texture.
         * \param depth Optional target depth texture.
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Adds one filled convex polygon from packed XY pairs.
         * \param xyPairs Packed XY pairs: [x0,y0, x1,y1, ...].
         * \param style Polygon style.
         * \return Handle of the created item, or invalid handle on failure.
         *
         * Requirements:
         * - at least 3 points
         * - convex winding (clockwise or counter-clockwise)
         * - no self-intersection
         */
        Polygon2DHandle addConvexPolygon(std::span<const float> xyPairs, const Polygon2DStyle& style = {});

        /**
         * \brief Adds one axis-aligned filled rectangle.
         * \param x Left coordinate in pixels.
         * \param y Top coordinate in pixels.
         * \param w Width in pixels.
         * \param h Height in pixels.
         * \param style Rectangle style.
         * \return Handle of the created item, or invalid handle on failure.
         */
        Polygon2DHandle addRect(float x, float y, float w, float h, const Polygon2DStyle& style = {});

        /**
         * \brief Removes one polygon item.
         * \param handle Polygon item handle.
         */
        void remove(Polygon2DHandle handle);

        /**
         * \brief Removes all polygon items.
         */
        void clear();

        /**
         * \brief Returns number of polygon items tracked by the pass.
         * \return Number of items.
         */
        [[nodiscard]] std::size_t polygonCount() const noexcept { return m_items.size(); }

    private:
        explicit Polygon2DPass(std::string name = "Polygon2DPass")
            : RenderPass{ std::move(name) }
        {}

        bool initialize() override;
        void begin() override;
        void execute(RenderResources& resources) override;
        void end() override;

    private:
        struct PolygonItem
        {
            Polygon2DHandle handle;
            std::vector<float> xyPairs;
            Polygon2DStyle style;
        };

        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;

        ShaderProgram m_shader;
        Buffer m_vbo{ Buffer::Target::VertexAttributesArray };
        VertexArray m_vao;

        std::vector<PolygonItem> m_items;
        std::uint64_t m_nextId = 1;
    };
} // namespace nfx::graphics::gl
