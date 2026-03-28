#pragma once

/**
 * \file RenderResources.h
 * \brief Declares RenderResources - a bundle of cache references used by the renderer to resolve handles.
 */

#include "nfx/graphics/gl/resources/MaterialCache.h"
#include "nfx/graphics/gl/resources/MeshCache.h"
#include "nfx/graphics/gl/resources/SamplerCache.h"
#include "nfx/graphics/gl/resources/ShaderCache.h"
#include "nfx/graphics/gl/resources/Texture2DCache.h"
#include "nfx/graphics/gl/resources/TextureCubeCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Bundle of non-owning cache references passed to the renderer.
     *
     * References are used because every cache is required to resolve queued draw commands.
     * This bundle does not own any cache; all referenced services must outlive the calls that use it.
     */
    struct RenderResources
    {
        MeshCache& meshes;
        MaterialCache& materials;
        ShaderCache& shaders;
        Texture2DCache& textures2D;
        TextureCubeCache& texturesCube;
        SamplerCache& samplers;
    };

} // namespace nfx::graphics::gl
