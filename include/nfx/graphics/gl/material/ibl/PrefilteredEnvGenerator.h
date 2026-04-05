#pragma once

/**
 * \file PrefilteredEnvGenerator.h
 * \brief Declares the GPU-side prefiltered environment cubemap generator used by PBR specular IBL.
 */

#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/core/textures/TextureCube.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Generates a prefiltered specular environment cubemap from an environment cubemap.
     *
     * Uses GGX importance sampling to produce a mip chain where each level corresponds
     * to a roughness value. Used by the PBR split-sum specular IBL term.
     *
     * Compiles the required shader once on construction. A valid and current
     * OpenGL context must exist on the calling thread during construction and
     * when calling generate().
     */
    class PrefilteredEnvGenerator final
    {
    public:
        /**
         * \brief Describes the prefiltered environment cubemap to generate.
         */
        struct Desc
        {
            int size = 256;        ///< Base face size in pixels.
            int numMips = 5;       ///< Number of mip levels. Each level maps to a roughness in [0, 1].
            int sampleCount = 512; ///< Number of GGX importance samples per face per mip level.
        };

        /**
         * \brief Generates a prefiltered specular cubemap from an environment cubemap with explicit descriptor.
         * \param envMap Source environment cubemap.
         * \param desc Output prefiltered cubemap description.
         * \return Generated prefiltered cubemap, or an invalid cubemap on failure.
         */
        /**
         * \brief Compiles the prefiltered environment shader. Requires an active GL context.
         */
        PrefilteredEnvGenerator();

        /**
         * \brief Returns whether the generator was successfully initialized.
         * \return True when the internal shader compiled successfully.
         */
        [[nodiscard]] bool isValid() const noexcept;

        [[nodiscard]] TextureCube generate(const TextureCube& envMap, const Desc& desc) const;

        /**
         * \brief Generates a prefiltered specular cubemap from an environment cubemap with default descriptor.
         * \param envMap Source environment cubemap.
         * \return Generated prefiltered cubemap, or an invalid cubemap on failure.
         */
        [[nodiscard]] TextureCube generate(const TextureCube& envMap) const { return generate(envMap, Desc{}); }

    private:
        mutable ShaderProgram m_shader;
    };
} // namespace nfx::graphics::gl
