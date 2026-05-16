#pragma once

/**
 * \file Texture2DCache.h
 * \brief Declares the cache used to store 2D textures and upload them from pixel data.
 */

#include "nfx/graphics/gl/core/textures/Texture2D.h"
#include "ResourceCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of 2D textures keyed by Texture2DHandle.
     */
    class Texture2DCache final : public ResourceCache<Texture2DTag, Texture2D>
    {
    public:
        /**
         * \brief Uploads pixel data to the GPU and stores the resulting 2D texture.
         * \param data Source pixel data and creation parameters.
         * \return A stable handle referencing the cached texture.
         *
         * This forwards to Texture2D::fromMemory() and therefore expects 8-bit RGBA source pixels.
         * Uploads currently support only Texture2D::InternalFormat::RGBA8 and
         * Texture2D::InternalFormat::SRGB8_Alpha.
         */
        [[nodiscard]] Texture2DHandle upload(const Texture2D::Data& data);
    };
} // namespace nfx::graphics::gl
