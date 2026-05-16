#ifdef __linux__

    #include "FunctionLoader.h"
    #include "internal/runtime/Error.h"

    #include <GL/glx.h>
    #include <cstdio>

namespace nfx::graphics::gl
{
    FunctionLoader::FunctionLoader() {}

    FunctionLoader::~FunctionLoader() {}

    void* FunctionLoader::loadFunctionPtr(const char* p_name) const
    {
        auto procAddress = ::glXGetProcAddress(reinterpret_cast<const GLubyte*>(p_name));

        if (procAddress)
        {
            return reinterpret_cast<void*>(procAddress);
        }
        else
        {
            char msg[160];
            std::snprintf(msg, sizeof(msg), "GL function not found: %s", p_name);
            internal::runtime::logError(
                "FunctionLoader", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::External, msg);
            return nullptr;
        }
    }
} // namespace nfx::graphics::gl

#endif //! __linux__
