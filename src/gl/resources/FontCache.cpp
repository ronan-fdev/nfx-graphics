#include "nfx/graphics/gl/resources/FontCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    FontHandle FontCache::create(Font font)
    {
        if (!font.atlas.isValid())
        {
            internal::runtime::logError(
                "FontCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: invalid atlas handle");
            return {};
        }
        return add(std::move(font));
    }
} // namespace nfx::graphics::gl
