#include "nfx/graphics/gl/resources/ShaderCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    ShaderHandle ShaderCache::compile(std::initializer_list<ShaderProgram::ShaderSource> sources)
    {
        ShaderProgram program = ShaderProgram::fromSources(sources);
        if (!program.isValid())
        {
            internal::runtime::logError(
                "ShaderCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "compile: shader compilation or linking failed");
            return {};
        }
        return add(std::move(program));
    }
} // namespace nfx::graphics::gl
