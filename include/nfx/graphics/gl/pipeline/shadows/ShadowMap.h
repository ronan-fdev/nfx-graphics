#pragma once

/**
 * \file ShadowMap.h
 * \brief Declares the directional or spot shadow map data returned by shadow passes.
 */

#include "nfx/graphics/gl/resources/Texture2DCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Shadow map data combining a depth texture with its light-space matrix.
     */
    struct ShadowMapData
    {
        Texture2DHandle texture;    ///< Depth texture in Texture2DCache
        float lightSpaceMatrix[16]; ///< proj * view from light POV
    };
} // namespace nfx::graphics::gl
