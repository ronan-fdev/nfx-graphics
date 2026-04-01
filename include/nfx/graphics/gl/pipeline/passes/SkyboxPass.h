#pragma once

/**
 * \file SkyboxPass.h
 * \brief Declares the render pass drawing a cubemap skybox into a target framebuffer.
 */

#include "RenderPass.h"

#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/resources/Handle.h"
#include "nfx/graphics/gl/resources/TextureCubeCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Render pass drawing a cubemap skybox as the scene background.
     *
     * The pass should be added after the geometry pass so the skybox only fills pixels not already
     * covered by opaque geometry.
     */
    class SkyboxPass : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Sets the target textures receiving the skybox.
         * \param color Target color texture, typically GeometryPass::colorOutput().
         * \param depth Optional target depth texture, typically GeometryPass::depthOutput().
         */
        void setTargetTextures(Texture2DHandle color, Texture2DHandle depth = {}) noexcept
        {
            m_targetColor = color;
            m_targetDepth = depth;
        }

        /**
         * \brief Sets the cubemap displayed as the skybox.
         * \param cache Cube texture cache owning the cubemap.
         * \param handle Cubemap texture handle.
         */
        void setCubemap(TextureCubeCache& cache, TextureCubeHandle handle) noexcept
        {
            m_cubeCache = &cache;
            m_cubemap = handle;
        }

    private:
        explicit SkyboxPass(std::string name = "SkyboxPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        Framebuffer m_targetFbo;
        Texture2DHandle m_targetColor;
        Texture2DHandle m_targetDepth;
        bool m_targetBound = false;
        TextureCubeHandle m_cubemap;
        TextureCubeCache* m_cubeCache = nullptr;
        ShaderProgram m_shader;
        VertexArray m_vao;
    };
} // namespace nfx::graphics::gl
