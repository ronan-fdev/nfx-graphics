#include "nfx/graphics/gl/resources/TextureCubeCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    TextureCubeHandle TextureCubeCache::upload(const TextureCube::FaceData faces[6], const TextureCube::Params& params)
    {
        TextureCube tex = TextureCube::fromMemory(faces, params);
        if (!tex.isValid())
        {
            internal::runtime::logError(
                "TextureCubeCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "upload: cube map creation failed");
            return {};
        }
        return add(std::move(tex));
    }
} // namespace nfx::graphics::gl
