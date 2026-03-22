#pragma once

/**
 * \file Functions.h
 * \brief Declares the complete OpenGL function table exposed by the nfx::graphics::gl context wrapper.
 */

#include "functions/Functions_4_6.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions
     * \brief The complete OpenGL function table exposed by a Context.
     *
     * This is the type returned by Context::functions(). It inherits the full
     * OpenGL 1.0 - 4.6 function set and is the only GL-function type that
     * consumers of nfx::graphics should depend on.
     *
     * Functions not supported by the active context will have null function
     * pointers; use Context::isVersionSupported() before calling them.
     */
    class Functions final : public Functions_4_6
    {
        friend class Context;

    private:
        Functions() = default;
        virtual ~Functions() = default;
    };
} // namespace nfx::graphics::gl
