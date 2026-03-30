#pragma once

/**
 * \file Unlit.h
 * \brief Declares an unlit material descriptor used for constant-color rendering.
 */

#include "nfx/graphics/gl/resources/MaterialCache.h"
#include "nfx/graphics/gl/resources/ShaderCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Unlit material descriptor for solid-color rendering without lighting or shadows.
     *
     * Useful for light position markers, debug geometry, wireframes and any
     * object that should appear at constant brightness regardless of scene
     * lighting.
     *
     * Vertex contract: layout(location=0) vec3 aPosition.
     * Reads CameraBlock (binding=0) and uModel uniform.
     */
    struct UnlitMaterial
    {
        UniformVec3 color = { 1.f, 1.f, 1.f }; ///< Solid color applied by the material
        float alpha = 1.f;                     ///< Final alpha value used when rendering

        /**
         * \brief Builds a runtime Material from the descriptor.
         * \param shaderCache Shader cache used to resolve the required shader program.
         * \param materialCache Material cache used to store the resulting runtime material.
         * \return Handle to the created runtime material, or an invalid handle on failure.
         */
        [[nodiscard]] MaterialHandle build(ShaderCache& shaderCache, MaterialCache& materialCache) const;

        /**
         * \brief Applies the descriptor values to an existing runtime Material.
         * \param mat Material instance to update.
         */
        void apply(Material& mat) const;
    };
} // namespace nfx::graphics::gl
