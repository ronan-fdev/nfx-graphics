#pragma once

/**
 * \file ImagePlanePass.h
 * \brief Declares ImagePlanePass, an overlay pass rendering a textured quad in world space.
 */

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/resources/Texture2DCache.h"
#include "nfx/graphics/math/Mat4.h"
#include "RenderPass.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Overlay pass rendering a textured quad at a given world-space transform.
     *
     * The quad is a unit plane in local XY space ([-0.5, 0.5] on X and Y, Z=0 in local space).
     * Transform, opacity, and depth testing are configurable per frame.
     */
    class ImagePlanePass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the geometry color and depth targets that receive the overlay.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Target depth texture for depth testing, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Sets the image texture rendered on the plane.
         * \param handle Texture handle from the Texture2DCache used by the active RenderResources.
         */
        void setImage(Texture2DHandle handle) noexcept { m_imageHandle = handle; }

        /**
         * \brief Sets the world-space model matrix for the plane.
         * \param mat Column-major 4x4 model matrix.
         */
        void setTransform(const float (&mat)[16]) noexcept
        {
            for (int i = 0; i < 16; ++i)
            {
                m_transform[i] = mat[i];
            }
        }

        /**
         * \brief Sets the world-space model matrix for the plane.
         * \param mat Column-major 4x4 model matrix.
         */
        void setTransform(const math::Mat4& mat) noexcept
        {
            for (int i = 0; i < 16; ++i)
            {
                m_transform[i] = mat[i];
            }
        }

        /**
         * \brief Sets the global opacity multiplied with the image alpha.
         * \param opacity Value in [0, 1]. Values outside that range are clamped at draw time.
         */
        void setOpacity(float opacity) noexcept { m_opacity = opacity; }

        /**
         * \brief Enables or disables depth testing against the geometry depth buffer.
         * \param enabled When true, the plane is occluded by geometry in front of it.
         */
        void setDepthTest(bool enabled) noexcept { m_depthTest = enabled; }

    private:
        explicit ImagePlanePass(std::string name = "ImagePlane")
            : RenderPass{ std::move(name) }
        {
            setRasterRegionState({ ViewportPolicy::InheritView, {}, ScissorPolicy::Disabled, {} });
        }

        bool initialize() override;
        void begin() override;
        void execute(RenderResources& resources) override;
        void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;

        Texture2DHandle m_imageHandle;
        ShaderProgram m_shader;
        VertexArray m_vao;

        float m_transform[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
        float m_opacity = 1.0f;
        bool m_depthTest = true;
    };
} // namespace nfx::graphics::gl
