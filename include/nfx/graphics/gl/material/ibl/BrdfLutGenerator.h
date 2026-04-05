#pragma once

/**
 * \file BrdfLutGenerator.h
 * \brief Declares the GPU-side BRDF LUT generator used by PBR split-sum IBL.
 */

#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/core/textures/Texture2D.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Generates the BRDF integration LUT for split-sum specular IBL.
     *
     * Compiles the required shader once on construction. A valid and current
     * OpenGL context must exist on the calling thread during construction and
     * when calling generate().
     */
    class BrdfLutGenerator final
    {
    public:
        /**
         * \brief Describes the BRDF LUT texture to generate.
         */
        struct Desc
        {
            int width = 512;
            int height = 512;
        };

        /**
         * \brief Generates the BRDF integration LUT texture with explicit descriptor.
         * \param desc Output texture description.
         * \return Generated BRDF LUT texture, or an invalid texture on failure.
         */
        /**
         * \brief Compiles the BRDF LUT shader. Requires an active GL context.
         */
        BrdfLutGenerator();

        /**
         * \brief Returns whether the generator was successfully initialized.
         * \return True when the internal shader compiled successfully.
         */
        [[nodiscard]] bool isValid() const noexcept;

        [[nodiscard]] Texture2D generate(const Desc& desc) const;

        /**
         * \brief Generates the BRDF integration LUT texture with default descriptor.
         * \return Generated BRDF LUT texture, or an invalid texture on failure.
         */
        [[nodiscard]] Texture2D generate() const { return generate(Desc{}); }

    private:
        mutable ShaderProgram m_shader;
    };
} // namespace nfx::graphics::gl
