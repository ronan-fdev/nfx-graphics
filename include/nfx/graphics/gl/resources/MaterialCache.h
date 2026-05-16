#pragma once

/**
 * \file MaterialCache.h
 * \brief Declares the cache used to store runtime Material instances.
 */

#include "nfx/graphics/gl/material/Material.h"
#include "ResourceCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of materials keyed by MaterialHandle.
     */
    class MaterialCache final : public ResourceCache<MaterialTag, Material>
    {
    public:
        /**
         * \brief Creates a material and stores it in the cache.
         * \param shader Shader handle used by the material.
         * \param state Render state applied when binding the material.
         * \return A stable handle referencing the cached material, or an invalid handle when shader is invalid.
         */
        [[nodiscard]] MaterialHandle create(ShaderHandle shader, RenderState state);
    };
} // namespace nfx::graphics::gl
