#ifdef __linux__

    #include "FunctionLoader.h"

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
            std::fprintf(stderr, "[nfx::graphics] WARNING: GL function not found: %s\n", p_name);
            return nullptr;
        }
    }
} // namespace nfx::graphics::gl

#endif //! __linux__
