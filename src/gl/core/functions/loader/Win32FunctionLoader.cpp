#ifdef _WIN32

    #include "FunctionLoader.h"

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
            std::fprintf(stderr, "[nfx::graphics] WARNING: GL function not found: %s\n", p_name);
            return nullptr;
        }
    }
} // namespace nfx::graphics::gl

#endif //! _WIN32
