#pragma once

/**
 * \file FontCache.h
 * \brief Declares the cache used to store Font resources.
 */

#include "nfx/graphics/gl/text/Font.h"
#include "ResourceCache.h"

#include <cstdio>

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of fonts keyed by FontHandle.
     */
    class FontCache final : public ResourceCache<FontTag, Font>
    {
    public:
        /**
         * \brief Stores one runtime font resource and returns its handle.
         * \param font Runtime font resource.
         * \return A stable handle referencing the cached font, or invalid handle on failure.
         */
        [[nodiscard]] FontHandle create(Font font)
        {
            if (!font.atlas.isValid())
            {
                std::fprintf(stderr, "[FontCache] create: invalid atlas handle\n");
                return {};
            }
            return add(std::move(font));
        }
    };
} // namespace nfx::graphics::gl
