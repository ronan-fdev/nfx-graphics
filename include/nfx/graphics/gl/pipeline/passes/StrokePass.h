#pragma once

/**
 * \file StrokePass.h
 * \brief Declares a render pass owning CPU-tessellated stroke items rendered in 3D world space.
 */

#include "nfx/graphics/gl/core/buffers/Buffer.h"
#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/strokes/StrokeTessellator.h"
#include "nfx/graphics/math/Mat4.h"
#include "RenderPass.h"

#include <cstddef>
#include <span>
#include <string>
#include <vector>

namespace nfx::graphics::gl
{
    struct StrokeItemTag
    {
    };

    using StrokeItemHandle = Handle<StrokeItemTag>;

    /**
     * \brief Pass-level stroke item input.
     */
    struct StrokeItemDesc2D
    {
        std::span<const float> xy;  ///< Packed local XY pairs on the stroke plane: [x0, y0, x1, y1, ...]
        std::size_t pointCount = 0; ///< Number of points in \\p xy
        bool closed = false;        ///< True to close the polyline
        StrokeStyle style{};        ///< Stroke style used by CPU tessellation
        math::Mat4 transform = math::Mat4::identity(); ///< Local-to-world transform applied at draw time
    };

    /**
     * \brief Render pass storing and drawing tessellated stroke geometry in world space.
     */
    class StrokePass final : public RenderPass
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
         * \brief Adds one stroke item and tessellates it on the CPU.
         * \param desc Stroke item descriptor.
         * \return Handle of the created stroke item, or invalid handle on failure.
         */
        [[nodiscard]] StrokeItemHandle addStroke(const StrokeItemDesc2D& desc);

        /**
         * \brief Removes one stroke item.
         * \param handle Stroke item handle.
         */
        void remove(StrokeItemHandle handle);

        /**
         * \brief Removes all stroke items.
         */
        void clear();

        /**
         * \brief Returns number of stroke items currently tracked by the pass.
         * \return Number of stroke items.
         */
        [[nodiscard]] std::size_t strokeCount() const noexcept { return m_items.size(); }

    private:
        explicit StrokePass(std::string name = "StrokePass")
            : RenderPass{ std::move(name) }
        {
            setRasterRegionState({ ViewportPolicy::InheritView, {}, ScissorPolicy::Disabled, {} });
        }

        bool initialize() override;
        void begin() override;
        void execute(RenderResources& resources) override;
        void end() override;

    private:
        struct StrokeItem
        {
            StrokeItemHandle handle;
            math::Mat4 transform = math::Mat4::identity();
            StrokeMesh2D mesh;
            std::vector<float> gpuVerts;
        };

        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        Framebuffer m_targetFbo;
        bool m_targetBound = false;

        ShaderProgram m_shader;
        Buffer m_vbo{ Buffer::Target::VertexAttributesArray };
        VertexArray m_vao;

        StrokeTessellator m_tessellator;
        std::vector<StrokeItem> m_items;
        std::uint64_t m_nextId = 1;
    };
} // namespace nfx::graphics::gl
