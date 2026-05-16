#pragma once

/**
 * \file DirectionalShadowPass.h
 * \brief Declares the depth-only render pass used to generate a directional shadow map.
 */

#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/pipeline/shadows/ShadowMap.h"
#include "RenderPass.h"

#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief Depth-only render pass producing one 2D shadow map from a directional light point of view.
     */
    class DirectionalShadowPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Per-frame execution counters produced by DirectionalShadowPass::execute().
         */
        struct ExecutionStats
        {
            std::uint32_t commandsSubmitted = 0; ///< Number of queued shadow commands
            std::uint32_t commandsDrawn = 0;     ///< Number of shadow draw calls effectively executed
            std::uint32_t commandsInvalid = 0;   ///< Number of commands rejected due to invalid mesh
            std::uint32_t vaoBinds = 0;          ///< Number of mesh VAO binds applied
            std::uint32_t vboBinds = 0;          ///< Number of vertex-buffer binding changes applied
            std::uint32_t fboBinds = 0;          ///< Number of framebuffer bind calls applied
            std::uint32_t instancedDraws = 0;    ///< Number of draw calls using instanceCount > 1
        };

        /**
         * \brief Submits one draw command to the directional shadow queue.
         * \param cmd Draw command to enqueue for the next shadow pass execution.
         */
        void submit(RenderCommand cmd) { m_queue.submit(cmd); }

        /**
         * \brief Sets the light-space matrix used for shadow rendering.
         * \param m Light-space matrix stored in column-major order.
         *
         * Call this every frame after updating the directional light transform.
         */
        void setLightSpaceMatrix(const float m[16]) noexcept;

        /**
         * \brief Sets the shadow map resolution and the cache owning the depth texture.
         * \param texCache Texture cache that will own the produced depth texture.
         * \param width Shadow map width in pixels.
         * \param height Shadow map height in pixels.
         *
         * Must be called before Renderer::initialize() or Renderer::render().
         */
        void setResolution(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Returns the shadow map data produced by this pass.
         * \return Depth texture handle plus light-space matrix.
         *
         * The returned data is valid after Renderer::initialize() or after the first Renderer::render().
         */
        [[nodiscard]] ShadowMapData shadowMap() const noexcept;

        /**
         * \brief Returns the depth texture output of the pass.
         */
        [[nodiscard]] virtual Texture2DHandle depthOutput() const noexcept override { return m_shadowHandle; }

        /**
         * \brief Returns the framebuffer used by the pass when initialized.
         */
        [[nodiscard]] virtual const Framebuffer* outputFramebuffer() const noexcept override
        {
            return m_shadowHandle.isValid() ? &m_framebuffer : nullptr;
        }

        /**
         * \brief Returns the shadow map width in pixels.
         */
        [[nodiscard]] virtual int outputWidth() const noexcept override { return m_width; }

        /**
         * \brief Returns the shadow map height in pixels.
         */
        [[nodiscard]] virtual int outputHeight() const noexcept override { return m_height; }

        /**
         * \brief Returns execution counters from the most recent execute() call.
         */
        [[nodiscard]] const ExecutionStats& executionStats() const noexcept { return m_executionStats; }

        /**
         * \brief Builds a light-space matrix (projection * view) for directional shadow mapping.
         * \param out Output light-space matrix stored in column-major order.
         * \param direction Normalized world-space light direction.
         * \param targetX Shadow target center X.
         * \param targetY Shadow target center Y.
         * \param targetZ Shadow target center Z.
         * \param sceneRadius Radius used to size the orthographic shadow frustum.
         * \param nearPlane Near clipping plane of the light projection.
         * \param farPlane Far clipping plane of the light projection.
         *
         * The light is placed at target + (-direction * distance) looking at target.
         */
        static void buildLightSpaceMatrix(
            float out[16],
            const float direction[3],
            float targetX,
            float targetY,
            float targetZ,
            float sceneRadius,
            float nearPlane,
            float farPlane) noexcept
        {
            const float lx = targetX - direction[0] * (sceneRadius + nearPlane);
            const float ly = targetY - direction[1] * (sceneRadius + nearPlane);
            const float lz = targetZ - direction[2] * (sceneRadius + nearPlane);

            float view[16], proj[16];
            math::mat4LookAt(view, lx, ly, lz, targetX, targetY, targetZ);
            math::mat4Ortho(proj, -sceneRadius, sceneRadius, -sceneRadius, sceneRadius, nearPlane, farPlane);
            math::mat4Mul(out, proj, view);
        }

    private:
        explicit DirectionalShadowPass(std::string name = "DirectionalShadowPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        // Single mat4 used by the depth shader (binding ShadowDepth=4)
        struct ShadowDepthUBO
        {
            float matrix[16];
        };

        RenderQueue m_queue;
        Framebuffer m_framebuffer;
        Texture2DHandle m_shadowHandle;       ///< depth texture owned by Texture2DCache
        Texture2DCache* m_texCache = nullptr; ///< non-owning, set in initialize()
        ShaderProgram m_depthShader;          ///< depth-only vert+frag
        RenderState m_shadowState;
        UniformBuffer<ShadowDepthUBO> m_depthUbo; ///< binding ShadowDepth=4
        ShadowDepthUBO m_depthData{};             ///< current light-space matrix

        int m_width = 1024;
        int m_height = 1024;
        bool m_dirty = true; ///< resolution changed - reallocate depth texture
        ExecutionStats m_executionStats;

        GLint m_savedViewport[4] = {};
    };
} // namespace nfx::graphics::gl
