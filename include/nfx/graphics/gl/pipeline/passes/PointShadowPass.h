#pragma once

/**
 * \file PointShadowPass.h
 * \brief Declares the depth-only render pass generating cube-map shadows for point lights.
 */

#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/pipeline/shadows/PointShadowMap.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/scene/lights/PointLight.h"
#include "RenderPass.h"

#include <array>
#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief Depth-only pass producing one cube map shadow per point light.
     *
     * Each point light is rendered in a single draw call using a geometry shader that
     * amplifies every triangle to all 6 cube faces via gl_Layer (layered rendering).
     */
    class PointShadowPass final : public RenderPass
    {
        friend class Renderer;

    public:
        /**
         * \brief Per-frame execution counters produced by PointShadowPass::execute().
         */
        struct ExecutionStats
        {
            std::uint32_t commandsSubmitted = 0; ///< Number of submitted command attempts across all active lights
            std::uint32_t commandsDrawn = 0;     ///< Number of draw calls executed across all active lights
            std::uint32_t commandsInvalid = 0;   ///< Number of rejected command attempts across all active lights
            std::uint32_t vaoBinds = 0;          ///< Number of mesh VAO binds applied
            std::uint32_t vboBinds = 0;          ///< Number of vertex-buffer binding changes applied
            std::uint32_t fboBinds = 0;          ///< Number of framebuffer bind calls applied
            std::uint32_t instancedDraws = 0;    ///< Number of draw calls using instanceCount > 1
        };

        /**
         * \brief Submits one draw command to the point shadow queue.
         * \param cmd Draw command to enqueue for the next shadow pass execution.
         */
        void submit(RenderCommand cmd) { m_queue.submit(cmd); }

        /**
         * \brief Registers a point light for shadow rendering during the next frame.
         * \param point Point light descriptor.
         *
         * Must be called before Renderer::render(). The list resets each frame in begin().
         */
        void addLight(const PointLight& point) noexcept;

        /**
         * \brief Sets the resolution used for all point shadow cube maps.
         * \param texCache Texture cache owning the cube map textures.
         * \param size Cube face size in pixels.
         *
         * Call before Renderer::initialize().
         */
        void setResolution(TextureCubeCache& texCache, int size);

        /**
         * \brief Returns the currently active point shadow maps.
         * \return Array of active shadow maps; index matches the order of addLight() calls.
         */
        [[nodiscard]] const std::array<PointShadowMap, PipelineLimits::MaxPointShadows>& shadowMaps() const noexcept
        {
            return m_shadowMaps;
        }

        /**
         * \brief Returns the number of active point lights for the current frame.
         */
        [[nodiscard]] int lightCount() const noexcept { return m_lightCount; }

        /**
         * \brief Returns execution counters from the most recent execute() call.
         */
        [[nodiscard]] const ExecutionStats& executionStats() const noexcept { return m_executionStats; }

    private:
        explicit PointShadowPass(std::string name = "PointShadowPass")
            : RenderPass{ std::move(name) }
        {
            setRasterRegionState({ ViewportPolicy::FullTarget, {}, ScissorPolicy::Disabled, {} });
        }

        virtual bool initialize() override;
        virtual void begin() override;
        virtual void execute(RenderResources& resources) override;
        virtual void end() override;

    private:
        // UBO uploaded once per light: 6 face matrices + packed light position / far plane
        struct ShadowDepthUBO
        {
            float matrices[6][16]; // 6 × mat4, std140 column-major
            float lightPos[3];
            float farPlane;
        };

        RenderQueue m_queue;
        ShaderProgram m_depthShader;
        RenderState m_shadowState;
        UniformBuffer<ShadowDepthUBO> m_depthUbo;

        std::array<Framebuffer, PipelineLimits::MaxPointShadows> m_framebuffers;
        std::array<TextureCubeHandle, PipelineLimits::MaxPointShadows> m_cubeHandles;
        std::array<PointShadowMap, PipelineLimits::MaxPointShadows> m_shadowMaps;

        TextureCubeCache* m_texCache = nullptr;
        int m_size = 512;
        bool m_dirty = true;

        // Per-frame state
        int m_lightCount = 0;
        int m_pendingCount = 0;
        ExecutionStats m_executionStats;

        GLint m_savedViewport[4] = {};
    };
} // namespace nfx::graphics::gl
