#ifdef _WIN32

    #include "FunctionLoader.h"
    #include "internal/runtime/Error.h"

    #include <windows.h>
    #include <cstdio>

namespace nfx::graphics::gl
{
    FunctionLoader::FunctionLoader() {}

    FunctionLoader::~FunctionLoader() {}

    void* FunctionLoader::loadFunctionPtr(const char* p_name) const
    {
        auto procAddress = ::wglGetProcAddress(p_name);

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

#endif //! _WIN32
