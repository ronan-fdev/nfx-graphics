#pragma once

/**
 * \file BlinnPhong.h
 * \brief Declares a Blinn-Phong material descriptor and helpers to build runtime Material instances.
 */

#include "nfx/graphics/gl/core/shaders/Uniforms.h"
#include "Material.h"

namespace nfx::graphics::gl
{
    struct RenderResources;

    /**
     * \brief Describes the parameters of a lit Blinn-Phong material.
     */
    struct BlinnPhongMaterial
    {
        UniformVec3 diffuseColor = { 1.f, 1.f, 1.f };  ///< Base diffuse reflectance color
        UniformVec3 specularColor = { 1.f, 1.f, 1.f }; ///< Specular reflectance color

        float shininess = 32.f; ///< Specular highlight exponent
        float alpha = 1.f;      ///< Final alpha value used when rendering

        Texture2DHandle diffuseMap = {};  ///< Optional albedo texture
        Texture2DHandle normalMap = {};   ///< Optional tangent-space normal map
        Texture2DHandle specularMap = {}; ///< Optional specular intensity map.

        bool hasShadow = false; ///< Activates HAS_SHADOW permutation - shadow map is bound by FrameData

        bool hasEnvMap = false;   ///< Activates HAS_ENV_MAP permutation - environment map is bound by FrameData
        float envIntensity = 1.f; ///< Reflection strength multiplier used when HAS_ENV_MAP is enabled

        /**
         * \brief Builds a runtime Material from the descriptor.
         *
         * Shader permutation features are selected at build time.
         * Rebuild the material when those feature toggles
         * change.
         *
         * \param resources Render resource bundle used to resolve caches required to build/update the material.
         * \return Handle to the created runtime material, or an invalid handle on failure.
         */
        [[nodiscard]] MaterialHandle build(RenderResources& resources) const;
        /**
         * \brief Applies the descriptor values to an existing runtime Material.
         *
         * This updates material parameters/state but does not switch shader permutation.
         *
         * \param mat Material instance to update.
         */
        void apply(Material& mat) const;
    };
} // namespace nfx::graphics::gl
