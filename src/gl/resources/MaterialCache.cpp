#include "nfx/graphics/gl/resources/MaterialCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    MaterialHandle MaterialCache::create(ShaderHandle shader, RenderState state)
    {
        if (!shader.isValid())
        {
            internal::runtime::logError(
                "MaterialCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: shader handle is invalid");
            return {};
        }
        return add(Material::create(shader, state));
    }
} // namespace nfx::graphics::gl
