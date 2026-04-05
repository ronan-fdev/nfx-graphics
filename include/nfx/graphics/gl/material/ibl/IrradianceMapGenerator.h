#pragma once

/**
 * \file IrradianceMapGenerator.h
 * \brief Declares the GPU-side irradiance cubemap generator used by PBR diffuse IBL.
 */

#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/core/textures/TextureCube.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Generates a diffuse irradiance cubemap from an environment cubemap.
     *
     * Convolves the environment cubemap over the hemisphere to produce the irradiance
     * map used by the PBR diffuse IBL term.
     *
     * Compiles the required shader once on construction. A valid and current
     * OpenGL context must exist on the calling thread during construction and
     * when calling generate().
     */
    class IrradianceMapGenerator final
    {
    public:
        /**
         * \brief Describes the irradiance cubemap to generate.
         */
        struct Desc
        {
            int size = 64; ///< Face size in pixels. 32-128 is typical.
        };

        /**
         * \brief Generates a diffuse irradiance cubemap from an environment cubemap with explicit descriptor.
         * \param envMap Source environment cubemap.
         * \param desc Output irradiance cubemap description.
         * \return Generated irradiance cubemap, or an invalid cubemap on failure.
         */
        /**
         * \brief Compiles the irradiance convolution shader. Requires an active GL context.
         */
        IrradianceMapGenerator();

        /**
         * \brief Returns whether the generator was successfully initialized.
         * \return True when the internal shader compiled successfully.
         */
        [[nodiscard]] bool isValid() const noexcept;

        [[nodiscard]] TextureCube generate(const TextureCube& envMap, const Desc& desc) const;

        /**
         * \brief Generates a diffuse irradiance cubemap from an environment cubemap with default descriptor.
         * \param envMap Source environment cubemap.
         * \return Generated irradiance cubemap, or an invalid cubemap on failure.
         */
        [[nodiscard]] TextureCube generate(const TextureCube& envMap) const { return generate(envMap, Desc{}); }

    private:
        mutable ShaderProgram m_shader;
    };
} // namespace nfx::graphics::gl
