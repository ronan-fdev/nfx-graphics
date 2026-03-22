#pragma once

namespace nfx::graphics::gl
{
    class FunctionLoader final
    {
    public:
        explicit FunctionLoader();
        FunctionLoader(const FunctionLoader&) = delete;
        FunctionLoader& operator=(const FunctionLoader&) = delete;
        FunctionLoader(FunctionLoader&&) = delete;
        FunctionLoader& operator=(FunctionLoader&&) = delete;
        ~FunctionLoader();

    public:
        void* loadFunctionPtr(const char* p_name) const;
    };
} // namespace nfx::graphics::gl
