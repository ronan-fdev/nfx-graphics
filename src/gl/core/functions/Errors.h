#pragma once

#include "gl/core/Platform.h"
#include "internal/runtime/Error.h"

#include <cstdio>
#include <string>

#if defined(NFX_GRAPHICS_DEBUG_OPENGL)
inline std::string glEnumToString(const GLenum p_enum)
{
    std::string ret;

    switch (p_enum)
    {
        case GL_INT:
            ret = "GL_INT";
            break;
        case GL_UNSIGNED_INT:
            ret = "GL_UNSIGNED_INT";
            break;
        case GL_UNSIGNED_BYTE:
            ret = "GL_UNSIGNED_BYTE";
            break;
        case GL_FLOAT:
            ret = "GL_FLOAT";
            break;
        case GL_FLOAT_VEC2:
            ret = "GL_FLOAT_VEC2";
            break;
        case GL_FLOAT_VEC3:
            ret = "GL_FLOAT_VEC3";
            break;
        case GL_FLOAT_VEC4:
            ret = "GL_FLOAT_VEC4";
            break;
        case GL_FLOAT_MAT4:
            ret = "GL_FLOAT_MAT4";
            break;
        case GL_SAMPLER_2D:
            ret = "GL_SAMPLER_2D";
            break;
        case GL_INVALID_ENUM:
            ret = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            ret = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            ret = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            ret = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            ret = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            ret = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            ret = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            ret = "UNKNOWN";
            break;
    }

    return ret;
}

inline void checkOpenGLError(const char* glCall, const char* func, int line, const char* caller)
{
    (void)glCall;
    (void)func;
    (void)line;
    GLenum err = ::glGetError();
    if (err != GL_NO_ERROR)
    {
        char msg[320];
        std::snprintf(
            msg, sizeof(msg), "OpenGL error %s at %s:%d - for %s", glEnumToString(err).c_str(), func, line, glCall);
        nfx::graphics::internal::runtime::logError(
            "GLDebug", nfx::graphics::internal::runtime::ErrorLevel::Warn, "GLDebug", msg);
        if (caller)
        {
            char callerMsg[192];
            std::snprintf(callerMsg, sizeof(callerMsg), "called by %s", caller);
            nfx::graphics::internal::runtime::logError(
                "GLDebug", nfx::graphics::internal::runtime::ErrorLevel::Warn, "GLDebug", callerMsg);
        }
    }
}

    #define NFX_GRAPHICS_GL_CHECK_ERROR(glCall, caller)                                                                \
        do                                                                                                             \
        {                                                                                                              \
            glCall;                                                                                                    \
            checkOpenGLError(#glCall, __FILE__, __LINE__, caller);                                                     \
        } while (0)
#else
    #define NFX_GRAPHICS_GL_CHECK_ERROR(glCall, caller) glCall
#endif
