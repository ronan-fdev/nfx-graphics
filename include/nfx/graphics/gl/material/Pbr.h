#pragma once

/**
 * \file Pbr.h
 * \brief Declares a minimal metallic-roughness PBR material descriptor.
 */

#include "nfx/graphics/gl/core/shaders/Uniforms.h"
#include "Material.h"

namespace nfx::graphics::gl
{
    struct RenderResources;

    /**
     * \brief Describes the parameters of a lit metallic-roughness PBR material.
     */
    struct PbrMaterial
    {
        UniformVec3 baseColor = { 1.f, 1.f, 1.f }; ///< Base color multiplier
        UniformVec3 emissive = { 0.f, 0.f, 0.f };  ///< Emissive color contribution

        float alpha = 1.f;      ///< Final alpha value used when rendering
        float metallic = 0.f;   ///< Scalar metallic fallback when no texture is bound
        float roughness = 0.5f; ///< Scalar roughness fallback when no texture is bound
        float ao = 1.f;         ///< Scalar ambient occlusion fallback when no texture is bound

        Texture2DHandle baseColorMap = {};         ///< Optional base color texture
        Texture2DHandle normalMap = {};            ///< Optional tangent-space normal map
        Texture2DHandle armMap = {};               ///< Optional packed ARM texture (R=ao, G=roughness, B=metallic)
        Texture2DHandle metallicRoughnessMap = {}; ///< Optional metallic-roughness texture (G=roughness, B=metallic)
        Texture2DHandle occlusionMap = {};         ///< Optional ambient occlusion map (R channel)

        bool hasShadow = false; ///< Activates HAS_SHADOW permutation - shadow map is bound by FrameData

        bool hasEnvMap = false;     ///< Activates HAS_ENV_MAP permutation - environment map is bound by FrameData
        bool useIblSplitSum = true; ///< Uses split-sum IBL when frame-global IBL resources are available
        float envIntensity = 1.f;   ///< Reflection strength multiplier used when HAS_ENV_MAP is enabled

        /**
         * \brief Builds or retrieves a runtime Material from the descriptor.
         * \param resources Render resource bundle used to resolve caches required to build/update the material.
         * \return Handle to the created runtime material, or an invalid handle on failure.
         */
        [[nodiscard]] MaterialHandle build(RenderResources& resources) const;

        /**
         * \brief Applies the descriptor values to an existing runtime Material.
         * \param mat Material instance to update.
         */
        void apply(Material& mat) const;
    };
} // namespace nfx::graphics::gl
