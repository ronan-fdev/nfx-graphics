#pragma once

/**
 * \file Bindings.h
 * \brief Declares binding point conventions shared by the GL pipeline, materials and shaders.
 */

#include "nfx/graphics/gl/core/GlTypes.h"

namespace nfx::graphics::gl
{
    // clang-format off
    /**
     * \brief Binding indices used by uniform buffers.
     */
    struct UboBindings
    {
        // Global pipeline
        static constexpr GLuint CameraBlock           = 0;  ///< Camera matrices and position
        static constexpr GLuint AmbientLightBlock     = 1;  ///< Primary ambient light
        static constexpr GLuint DirectionalLightBlock = 2;  ///< DirectionalLight UBO
        static constexpr GLuint ShadowMatricesBlock   = 3;  ///< ShadowMatrices UBO
        static constexpr GLuint ShadowDepthBlock      = 4;  ///< ShadowDepth UBO
        static constexpr GLuint IblFrameBlock         = 5;  ///< IBL frame-global flags

        // Per-material
        static constexpr GLuint MaterialBlock         = 16; ///< MaterialBlockData (base color, specular, shininess, emissive/env)
    };

    /**
     * \brief Binding indices used by shader storage buffers.
     */
    struct SsboBindings
    {
        static constexpr GLuint PunctualLightsBlock   = 0;  ///< LightBlock (point + spot)
    };

    /**
     * \brief Pipeline capacity limits shared by the shadow and light subsystems.
     */
    struct PipelineLimits
    {
        static constexpr GLuint MaxPointShadows       = 4;
        static constexpr GLuint MaxSpotShadows        = 4;
    };

    /**
     * \brief Texture unit conventions used by the built-in materials and render passes.
     */
    struct TextureBindings
    {
        // Frame-global shadow texture units
        static constexpr GLuint PointShadowMapBase    = 4;  ///< Units 4-7  (up to MaxPointShadows)
        static constexpr GLuint SpotShadowMapBase     = 8;  ///< Units 8-11 (up to MaxSpotShadows)
        static constexpr GLuint DirectionalShadowMap  = 12; ///< Directional shadow map
        static constexpr GLuint EnvMap                = 13; ///< Environment cube map for reflection/refraction
        static constexpr GLuint IrradianceMap         = 14; ///< Diffuse irradiance cubemap for IBL
        static constexpr GLuint PrefilteredEnvMap     = 15; ///< Prefiltered specular cubemap for IBL

        // Built-in material maps
        static constexpr GLuint MaterialSlot0         = 16; ///< Blinn-Phong: uDiffuseMap  / PBR: uBaseColorMap
        static constexpr GLuint MaterialSlot1         = 17; ///< All:         uNormalMap
        static constexpr GLuint MaterialSlot2         = 18; ///< Blinn-Phong: uSpecularMap / PBR: uMetallicRoughnessMap
        static constexpr GLuint MaterialSlot3         = 19; ///< PBR: uOcclusionMap / uArmMap
        static constexpr GLuint BrdfLut               = 20; ///< 2D BRDF integration LUT for split-sum IBL

        // Blinn-Phong aliases
        static constexpr GLuint DiffuseMap            = MaterialSlot0;
        static constexpr GLuint NormalMap             = MaterialSlot1;
        static constexpr GLuint SpecularMap           = MaterialSlot2;

        // PBR metallic-roughness aliases
        static constexpr GLuint BaseColorMap          = MaterialSlot0;
        static constexpr GLuint MetallicRoughnessMap  = MaterialSlot2;
        static constexpr GLuint OcclusionMap          = MaterialSlot3;
        static constexpr GLuint ArmMap                = MaterialSlot3;

        // User/custom sampler sandbox
        static constexpr GLuint UserMaterialFirstUnit = 22; ///< First texture unit for user/custom samplers
        static constexpr GLuint UserMaterialLastUnit  = 31; ///< Last  texture unit for user/custom samplers (inclusive)
    };
    // clang-format on
} // namespace nfx::graphics::gl
