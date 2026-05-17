#include "nfx/graphics/gl/core/functions/Functions_4_6.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

#include <cstdio>

namespace nfx::graphics::gl
{
    Functions_4_6::Functions_4_6()
        : Functions_4_5{}
    {}

    Functions_4_6::~Functions_4_6()
    {
        s_loaded = false;
    }

    GLvoid Functions_4_6::glMultiDrawArraysIndirectCount(
        GLenum mode,
        const GLvoid* indirect,
        GLintptr drawcount,
        GLsizei maxdrawcount,
        GLsizei stride,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride), caller);
    }

    GLvoid Functions_4_6::glMultiDrawElementsIndirectCount(
        GLenum mode,
        GLenum type,
        const GLvoid* indirect,
        GLintptr drawcount,
        GLsizei maxdrawcount,
        GLsizei stride,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride), caller);
    }

    GLvoid Functions_4_6::glPolygonOffsetClamp(
        GLfloat factor, GLfloat units, GLfloat clamp, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPolygonOffsetClamp(factor, units, clamp), caller);
    }

    GLvoid Functions_4_6::glSpecializeShader(
        GLuint shader,
        const GLchar* pEntryPoint,
        GLuint numSpecializationConstants,
        const GLuint* pConstantIndex,
        const GLuint* pConstantValue,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue),
            caller);
    }

    bool Functions_4_6::initialize()
    {
        Functions_4_5::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glMultiDrawArraysIndirectCount =
            reinterpret_cast<GLvoid (*)(GLenum, const GLvoid*, GLintptr, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glMultiDrawArraysIndirectCount"));
        _nfx_glMultiDrawElementsIndirectCount =
            reinterpret_cast<GLvoid (*)(GLenum mode, GLenum, const GLvoid*, GLintptr, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glMultiDrawElementsIndirectCount"));
        _nfx_glPolygonOffsetClamp =
            reinterpret_cast<GLvoid (*)(GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glPolygonOffsetClamp"));
        _nfx_glSpecializeShader =
            reinterpret_cast<GLvoid (*)(GLuint, const GLchar*, GLuint, const GLuint*, const GLuint*)>(
                loader.loadFunctionPtr("glSpecializeShader"));

        return s_loaded = true;
    }

    void Functions_4_6::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_4_5::teardown();
    }

    void Functions_4_6::nullifyPointers()
    {
        _nfx_glMultiDrawArraysIndirectCount = nullptr;
        _nfx_glMultiDrawElementsIndirectCount = nullptr;
        _nfx_glPolygonOffsetClamp = nullptr;
        _nfx_glSpecializeShader = nullptr;
    }
} // namespace nfx::graphics::gl
