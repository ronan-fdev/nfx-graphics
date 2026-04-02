#pragma once

/**
 * \file MaterialBlock.h
 * \brief Declares the std140-compatible CPU mirror of the MaterialBlock uniform buffer object.
 */

#include <cstdint>

namespace nfx::graphics::gl
{
    struct MaterialBlockData
    {
        float baseColor_alpha[4] = { 1.f, 1.f, 1.f, 1.f };  ///< rgb = diffuse/base color  , a = alpha
        float specColor_shine[4] = { 1.f, 1.f, 1.f, 32.f }; ///< rgb = specular color      , w = shininess
        float emissive_env[4] = { 0.f, 0.f, 0.f, 1.f };     ///< rgb = emissive (default 0), w = envIntensity
    };

    static_assert(sizeof(MaterialBlockData) == 48, "MaterialBlockData must be 48 bytes (std140)");
} // namespace nfx::graphics::gl
