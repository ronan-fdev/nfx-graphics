#pragma once

/**
 * \file Renderer.h
 * \brief Declares the frame renderer orchestrating an ordered list of render passes.
 */

#include "nfx/graphics/gl/core/buffers/ShaderStorageBuffer.h"
#include "nfx/graphics/gl/material/ibl/IblFrameBlock.h"
#include "nfx/graphics/gl/core/buffers/UniformBuffer.h"
#include "nfx/graphics/gl/pipeline/frame/FrameData.h"
#include "nfx/graphics/gl/pipeline/frame/RenderResources.h"
#include "nfx/graphics/gl/pipeline/passes/RenderPass.h"
#include "nfx/graphics/gl/pipeline/shadows/ShadowMatricesBlock.h"

#include <memory>
#include <optional>
#include <unordered_set>
#include <string_view>
#include <type_traits>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Executes an ordered sequence of render passes to produce one frame.
     *
     * Usage:
     * \code
     *   Renderer renderer;
     *   auto* pass = renderer.createPass<GeometryPass>("Opaque");
     *   renderer.initialize(resources);
     *   // per frame:
     *   renderer.setFrameData(frame);
     *   renderer.render();
     * \endcode
     */
    class Renderer final
    {
    public:
        /**
         * \brief Controls how permutation vs. frame-globals mismatches are reported.
         *
         * - Off    : no validation performed.
         * - Warn   : logs a one-time stderr warning per offending shader permutation (default).
         * - Strict : calls std::abort() on any mismatch (CI / test builds).
         */
        enum class ValidationMode
        {
            Off,
            Warn,
            Strict
        };

        Renderer() = default;

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        /**
         * \brief Creates a pass in-place, transfers ownership to the renderer and returns a non-owning pointer.
         *
         * The pass is initialized lazily before its first execution.
         * \tparam PassType Concrete pass type inheriting from RenderPass.
         * \tparam Args     Constructor argument types forwarded to PassType.
         * \param  args     Arguments forwarded to the PassType constructor.
         * \return Raw non-owning pointer. Lifetime is managed by the renderer.
         */
        template <typename PassType, typename... Args>
        PassType* createPass(Args&&... args)
        {
            static_assert(std::is_base_of_v<RenderPass, PassType>, "PassType must inherit from RenderPass");
            auto pass = std::unique_ptr<PassType>(new PassType(std::forward<Args>(args)...));
            PassType* ptr = pass.get();
            addPass(std::move(pass));
            return ptr;
        }

        /**
         * \brief Transfers ownership of an already-constructed pass to the renderer.
         */
        void addPass(std::unique_ptr<RenderPass> pass);

        /**
         * \brief Returns a pass by name, or nullptr when no pass matches.
         */
        [[nodiscard]] RenderPass* pass(std::string_view name) noexcept;
        [[nodiscard]] const RenderPass* pass(std::string_view name) const noexcept;

        /**
         * \brief Removes one pass by name.
         * \return True when a pass was removed.
         */
        bool removePass(std::string_view name);

        /**
         * \brief Removes all registered passes.
         */
        void clear() { m_passes.clear(); }

        [[nodiscard]] std::size_t count() const noexcept { return m_passes.size(); }

        /**
         * \brief Stores the resource bundle and initializes all registered passes.
         *
         * Must be called once after passes are registered and before render().
         * Passes added after initialize() are initialized lazily on first render().
         * \param resources Non-owning cache bundle used to resolve handles during rendering.
         */
        void initialize(RenderResources& resources);

        /**
         * \brief Stores frame-global payloads consumed during the next render() call.
         */
        void setFrameData(const FrameData& data) { m_frameData = data; }

        /**
         * \brief Clears any previously stored frame-global payload.
         */
        void resetFrameData() { m_frameData.reset(); }

        /**
         * \brief Sets permutation/frame-globals validation behavior.
         */
        void setValidationMode(ValidationMode mode) noexcept { m_validationMode = mode; }

        /**
         * \brief Executes all enabled passes in registration order.
         *
         * Calls initialize(), begin(), execute() and end() on each enabled pass.
         * Must be called after initialize() and setFrameData() each frame.
         */
        void render();

    private:
        void bindFrameScope();
        void validatePermutations();

        std::vector<std::unique_ptr<RenderPass>> m_passes;

        // Frame-globals state
        RenderResources* m_resources = nullptr;
        std::optional<FrameData> m_frameData;

        // GPU buffers
        std::optional<UniformBuffer<Camera::GpuData>> m_cameraUbo;
        std::optional<UniformBuffer<AmbientLight::GpuData>> m_ambientUbo;
        std::optional<UniformBuffer<DirectionalLight::GpuData>> m_directionalUbo;
        std::optional<UniformBuffer<ShadowMatricesBlockData>> m_shadowMatricesUbo;
        std::optional<UniformBuffer<IblFrameBlockData>> m_iblFrameUbo;
        std::optional<ShaderStorageBuffer<PunctualLight::GpuBlock>> m_punctualLightsSsbo;

        // Validation
        ValidationMode m_validationMode = ValidationMode::Warn;
        std::unordered_set<std::uint32_t> m_validatedPermutations;
    };
} // namespace nfx::graphics::gl
