#pragma once

/**
 * \file TextureCubeCache.h
 * \brief Declares the cache used to store cube map textures and upload them from face data.
 */

#include "nfx/graphics/gl/core/textures/TextureCube.h"
#include "ResourceCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of cube map textures keyed by TextureCubeHandle.
     */
    class TextureCubeCache final : public ResourceCache<TextureCubeTag, TextureCube>
    {
    public:
        /**
         * \brief Uploads six face images to the GPU and stores the resulting cube map.
         * \param faces Array of six face descriptions ordered as expected by TextureCube::fromMemory().
         * \param params Sampling and storage parameters used to create the cube map.
         * \return A stable handle referencing the cached cube map texture.
         *
         * This forwards to TextureCube::fromMemory(). Faces must be square, share identical dimensions,
         * and this upload path currently supports only TextureCube::InternalFormat::RGBA8.
         */
        [[nodiscard]] TextureCubeHandle upload(const TextureCube::FaceData faces[6], const TextureCube::Params& params);
    };
} // namespace nfx::graphics::gl
