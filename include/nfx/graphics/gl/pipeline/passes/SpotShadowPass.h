#pragma once

/**
 * \file SpotShadowPass.h
 * \brief Declares the depth-only render pass generating 2D shadow maps for spot lights.
 */

#include "nfx/graphics/gl/core/buffers/UniformBuffer.h"
#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/pipeline/shadows/ShadowMap.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/scene/lights/SpotLight.h"
#include "RenderPass.h"

#include <array>
#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief Depth-only pass producing one 2D shadow map per spot light.
     */
    class SpotShadowPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Per-frame execution counters produced by SpotShadowPass::execute().
         */
        struct ExecutionStats
        {
            std::uint32_t commandsSubmitted = 0; ///< Number of submitted command attempts across all active lights
            std::uint32_t commandsDrawn = 0;     ///< Number of shadow draw calls executed across all active lights
            std::uint32_t commandsInvalid = 0;   ///< Number of rejected command attempts across all active lights
            std::uint32_t vaoBinds = 0;          ///< Number of mesh VAO binds applied
            std::uint32_t vboBinds = 0;          ///< Number of vertex-buffer binding changes applied
            std::uint32_t fboBinds = 0;          ///< Number of framebuffer bind calls applied
            std::uint32_t instancedDraws = 0;    ///< Number of draw calls using instanceCount > 1
        };

        /**
         * \brief Submits one draw command to the spot shadow queue.
         * \param cmd Draw command to enqueue for the next shadow pass execution.
         */
        void submit(RenderCommand cmd) { m_queue.submit(cmd); }

        /**
         * \brief Registers a spot light for shadow rendering during the next frame.
         * \param spot Spot light descriptor.
         *
         * Must be called before Renderer::render(). The list resets each frame in begin().
         */
        void addLight(const SpotLight& spot) noexcept;

        /**
         * \brief Sets the resolution used for all spot shadow maps.
         * \param texCache Texture cache owning the depth textures.
         * \param width Shadow map width in pixels.
         * \param height Shadow map height in pixels.
         *
         * Call before Renderer::initialize().
         */
        void setResolution(Texture2DCache& texCache, int width, int height);

        /**
         * \brief Returns the currently active spot shadow maps.
         * \return Array of active shadow maps; index matches the order of addLight() calls.
         */
        [[nodiscard]] const std::array<ShadowMapData, PipelineLimits::MaxSpotShadows>& shadowMaps() const noexcept
        {
            return m_shadowMaps;
        }

        /**
         * \brief Returns the number of active spot lights for the current frame.
         */
        [[nodiscard]] int lightCount() const noexcept { return m_lightCount; }

        /**
         * \brief Returns execution counters from the most recent execute() call.
         */
        [[nodiscard]] const ExecutionStats& executionStats() const noexcept { return m_executionStats; }

    private:
        explicit SpotShadowPass(std::string name = "SpotShadowPass")
            : RenderPass{ std::move(name) }
        {}

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        // Single mat4 uploaded to ShadowDepth=4 for each spot depth render
        struct ShadowDepthUBO
        {
            float matrix[16];
        };

        RenderQueue m_queue;
        ShaderProgram m_depthShader;
        RenderState m_shadowState;
        UniformBuffer<ShadowDepthUBO> m_depthUbo; ///< binding ShadowDepth=4

        std::array<Framebuffer, PipelineLimits::MaxSpotShadows> m_framebuffers;
        std::array<Texture2DHandle, PipelineLimits::MaxSpotShadows> m_depthHandles;
        std::array<ShadowMapData, PipelineLimits::MaxSpotShadows> m_shadowMaps;

        Texture2DCache* m_texCache = nullptr;
        int m_width = 1024;
        int m_height = 1024;
        bool m_dirty = true;

        // Per-frame state
        int m_lightCount = 0;   ///< Committed at begin() from m_pendingCount
        int m_pendingCount = 0; ///< Incremented by addLight() before renderer.render()
        std::array<SpotLight, PipelineLimits::MaxSpotShadows> m_lights;
        ExecutionStats m_executionStats;

        GLint m_savedViewport[4] = {};
    };
} // namespace nfx::graphics::gl
