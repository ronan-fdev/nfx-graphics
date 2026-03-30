#pragma once

/**
 * \file PointShadowMap.h
 * \brief Declares the point-light shadow map data returned by PointShadowPass.
 */

#include "nfx/graphics/gl/resources/TextureCubeCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Point-light shadow map data combining a depth cube map with its sampling parameters.
     */
    struct PointShadowMap
    {
        TextureCubeHandle texture; ///< Depth cube map in TextureCubeCache
        float lightPos[3] = {};    ///< World-space position of the point light
        float nearPlane = 0.05f;   ///< Near plane used during depth capture
        float farPlane = 25.f;     ///< Far plane used during depth capture
    };
} // namespace nfx::graphics::gl
