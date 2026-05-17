#include "nfx/graphics/gl/core/functions/Functions_2_1.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_2_1::Functions_2_1()
        : Functions_2_0{}
    {}

    Functions_2_1::~Functions_2_1()
    {
        s_loaded = false;
    }

    GLvoid Functions_2_1::glUniformMatrix2x3fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2x3fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_1::glUniformMatrix2x4fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2x4fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_1::glUniformMatrix3x2fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3x2fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_1::glUniformMatrix3x4fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3x4fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_1::glUniformMatrix4x2fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4x2fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_1::glUniformMatrix4x3fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4x3fv(location, count, transpose, value), caller);
    }

    bool Functions_2_1::initialize()
    {
        Functions_2_0::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glUniformMatrix2x3fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix2x3fv"));
        _nfx_glUniformMatrix2x4fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix2x4fv"));
        _nfx_glUniformMatrix3x2fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix3x2fv"));
        _nfx_glUniformMatrix3x4fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix3x4fv"));
        _nfx_glUniformMatrix4x2fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix4x2fv"));
        _nfx_glUniformMatrix4x3fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix4x3fv"));

        return s_loaded = true;
    }

    void Functions_2_1::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_2_0::teardown();
    }

    void Functions_2_1::nullifyPointers()
    {
        _nfx_glUniformMatrix2x3fv = nullptr;
        _nfx_glUniformMatrix2x4fv = nullptr;
        _nfx_glUniformMatrix3x2fv = nullptr;
        _nfx_glUniformMatrix3x4fv = nullptr;
        _nfx_glUniformMatrix4x2fv = nullptr;
        _nfx_glUniformMatrix4x3fv = nullptr;
    }
} // namespace nfx::graphics::gl
