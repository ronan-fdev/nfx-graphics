#include "nfx/graphics/gl/resources/Texture2DCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    Texture2DHandle Texture2DCache::upload(const Texture2D::Data& data)
    {
        Texture2D tex = Texture2D::fromMemory(data.pixels, data.width, data.height, data.params);
        if (!tex.isValid())
        {
            internal::runtime::logError(
                "Texture2DCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "upload: texture creation failed");
            return {};
        }
        return add(std::move(tex));
    }
} // namespace nfx::graphics::gl
