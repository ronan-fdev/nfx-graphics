#include "nfx/graphics/gl/core/functions/Functions_1_2.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_2::Functions_1_2()
        : Functions_1_1{}
    {}

    Functions_1_2::~Functions_1_2()
    {
        s_loaded = false;
    }

    GLvoid Functions_1_2::glBlendColor(
        GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendColor(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_2::glBlendEquation(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendEquation(mode), caller);
    }

    GLvoid Functions_1_2::glColorSubTable(
        GLenum target,
        GLsizei start,
        GLsizei count,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorSubTable(target, start, count, format, type, data), caller);
    }

    GLvoid Functions_1_2::glColorTable(
        GLenum target,
        GLenum internalformat,
        GLsizei width,
        GLenum format,
        GLenum type,
        const GLvoid* table,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorTable(target, internalformat, width, format, type, table), caller);
    }

    GLvoid Functions_1_2::glColorTableParameterfv(
        GLenum target, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorTableParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glColorTableParameteriv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorTableParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glConvolutionFilter1D(
        GLenum target,
        GLenum internalformat,
        GLsizei width,
        GLenum format,
        GLenum type,
        const GLvoid* image,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glConvolutionFilter1D(target, internalformat, width, format, type, image), caller);
    }

    GLvoid Functions_1_2::glConvolutionFilter2D(
        GLenum target,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        const GLvoid* image,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glConvolutionFilter2D(target, internalformat, height, width, format, type, image), caller);
    }

    GLvoid Functions_1_2::glConvolutionParameterf(
        GLenum target, GLenum pname, GLfloat params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glConvolutionParameterf(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glConvolutionParameterfv(
        GLenum target, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glConvolutionParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glConvolutionParameteri(
        GLenum target, GLenum pname, GLint params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glConvolutionParameteri(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glConvolutionParameteriv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glConvolutionParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glCopyColorSubTable(
        GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCopyColorSubTable(target, start, x, y, width), caller);
    }

    GLvoid Functions_1_2::glCopyColorTable(
        GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCopyColorTable(target, internalformat, x, y, width), caller);
    }

    GLvoid Functions_1_2::glCopyConvolutionFilter1D(
        GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCopyConvolutionFilter1D(target, internalformat, x, y, width), caller);
    }

    GLvoid Functions_1_2::glCopyConvolutionFilter2D(
        GLenum target,
        GLenum internalformat,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyConvolutionFilter2D(target, internalformat, x, y, width, height), caller);
    }

    GLvoid Functions_1_2::glCopyTexSubImage3D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height), caller);
    }

    GLvoid Functions_1_2::glDrawRangeElements(
        GLenum mode,
        GLuint start,
        GLuint end,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawRangeElements(mode, start, end, count, type, indices), caller);
    }

    GLvoid Functions_1_2::glGetColorTable(
        GLenum target, GLenum format, GLenum type, GLvoid* table, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetColorTable(target, format, type, table), caller);
    }

    GLvoid Functions_1_2::glGetColorTableParameterfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetColorTableParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetColorTableParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetColorTableParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetConvolutionFilter(
        GLenum target, GLenum format, GLenum type, GLvoid* image, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetConvolutionFilter(target, format, type, image), caller);
    }

    GLvoid Functions_1_2::glGetConvolutionParameterfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetConvolutionParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetConvolutionParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetConvolutionParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetHistogram(
        GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetHistogram(target, reset, format, type, values), caller);
    }

    GLvoid Functions_1_2::glGetHistogramParameterfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetHistogramParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetHistogramParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetHistogramParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetMinmax(
        GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetMinmax(target, reset, format, type, values), caller);
    }

    GLvoid Functions_1_2::glGetMinmaxParameterfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetMinmaxParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetMinmaxParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetMinmaxParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_2::glGetSeparableFilter(
        GLenum target,
        GLenum format,
        GLenum type,
        GLvoid* row,
        GLvoid* column,
        GLvoid* span,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSeparableFilter(target, format, type, row, column, span), caller);
    }

    GLvoid Functions_1_2::glHistogram(
        GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glHistogram(target, width, internalformat, sink), caller);
    }

    GLvoid Functions_1_2::glMinmax(
        GLenum target, GLenum internalformat, GLboolean sink, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMinmax(target, internalformat, sink), caller);
    }

    GLvoid Functions_1_2::glResetHistogram(GLenum target, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glResetHistogram(target), caller);
    }

    GLvoid Functions_1_2::glResetMinmax(GLenum target, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glResetMinmax(target), caller);
    }

    GLvoid Functions_1_2::glSeparableFilter2D(
        GLenum target,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        const GLvoid* row,
        const GLvoid* column,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glSeparableFilter2D(target, internalformat, width, height, format, type, row, column), caller);
    }

    GLvoid Functions_1_2::glTexImage3D(
        GLenum target,
        GLint level,
        GLint internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLint border,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels),
            caller);
    }

    GLvoid Functions_1_2::glTexSubImage3D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels),
            caller);
    }

    bool Functions_1_2::initialize()
    {
        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBlendColor =
            reinterpret_cast<GLvoid (*)(GLfloat, GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glBlendColor"));
        _nfx_glBlendEquation = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glBlendEquation"));
        _nfx_glColorSubTable = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glColorSubTable"));
        _nfx_glColorTable = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glColorTable"));
        _nfx_glColorTableParameterfv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLfloat*)>(
            loader.loadFunctionPtr("glColorTableParameterfv"));
        _nfx_glColorTableParameteriv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLint*)>(
            loader.loadFunctionPtr("glColorTableParameteriv"));
        _nfx_glConvolutionFilter1D =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid*)>(
                loader.loadFunctionPtr("glConvolutionFilter1D"));
        _nfx_glConvolutionFilter2D =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
                loader.loadFunctionPtr("glConvolutionFilter2D"));
        _nfx_glConvolutionParameterf =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLfloat)>(loader.loadFunctionPtr("glConvolutionParameterf"));
        _nfx_glConvolutionParameterfv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLfloat*)>(
            loader.loadFunctionPtr("glConvolutionParameterfv"));
        _nfx_glConvolutionParameteri =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint)>(loader.loadFunctionPtr("glConvolutionParameteri"));
        _nfx_glConvolutionParameteriv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLint*)>(
            loader.loadFunctionPtr("glConvolutionParameteriv"));
        _nfx_glCopyColorSubTable = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLint, GLint, GLsizei)>(
            loader.loadFunctionPtr("glCopyColorSubTable"));
        _nfx_glCopyColorTable = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint, GLint, GLsizei)>(
            loader.loadFunctionPtr("glCopyColorTable"));
        _nfx_glCopyConvolutionFilter1D = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint, GLint, GLsizei)>(
            loader.loadFunctionPtr("glCopyConvolutionFilter1D"));
        _nfx_glCopyConvolutionFilter2D = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glCopyConvolutionFilter2D"));
        _nfx_glCopyTexSubImage3D =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glCopyTexSubImage3D"));
        _nfx_glDrawRangeElements = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glDrawRangeElements"));
        _nfx_glGetColorTable =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLvoid*)>(loader.loadFunctionPtr("glGetColorTable"));
        _nfx_glGetColorTableParameterfv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLfloat*)>(
            loader.loadFunctionPtr("glGetColorTableParameterfv"));
        _nfx_glGetColorTableParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetColorTableParameteriv"));
        _nfx_glGetConvolutionFilter = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLvoid*)>(
            loader.loadFunctionPtr("glGetConvolutionFilter"));
        _nfx_glGetConvolutionParameterfv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLfloat*)>(
            loader.loadFunctionPtr("glGetConvolutionParameterfv"));
        _nfx_glGetConvolutionParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetConvolutionParameteriv"));
        _nfx_glGetHistogram = reinterpret_cast<GLvoid (*)(GLenum, GLboolean, GLenum, GLenum, GLvoid*)>(
            loader.loadFunctionPtr("glGetHistogram"));
        _nfx_glGetHistogramParameterfv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLfloat*)>(loader.loadFunctionPtr("glGetHistogramParameterfv"));
        _nfx_glGetHistogramParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetHistogramParameteriv"));
        _nfx_glGetMinmax = reinterpret_cast<GLvoid (*)(GLenum, GLboolean, GLenum, GLenum, GLvoid*)>(
            loader.loadFunctionPtr("glGetMinmax"));
        _nfx_glGetMinmaxParameterfv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLfloat*)>(loader.loadFunctionPtr("glGetMinmaxParameterfv"));
        _nfx_glGetMinmaxParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetMinmaxParameteriv"));
        _nfx_glGetSeparableFilter = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLvoid*, GLvoid*, GLvoid*)>(
            loader.loadFunctionPtr("glGetSeparableFilter"));
        _nfx_glHistogram =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLboolean)>(loader.loadFunctionPtr("glHistogram"));
        _nfx_glMinmax = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLboolean)>(loader.loadFunctionPtr("glMinmax"));
        _nfx_glResetHistogram = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glResetHistogram"));
        _nfx_glResetMinmax = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glResetMinmax"));
        _nfx_glSeparableFilter2D = reinterpret_cast<GLvoid (*)(
            GLenum target, GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*, const GLvoid*)>(
            loader.loadFunctionPtr("glSeparableFilter2D"));
        _nfx_glTexImage3D = reinterpret_cast<GLvoid (*)(
            GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glTexImage3D"));
        _nfx_glTexSubImage3D = reinterpret_cast<GLvoid (*)(
            GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glTexSubImage3D"));

        return s_loaded = true;
    }

    void Functions_1_2::teardown()
    {
        nullifyPointers();

        s_loaded = false;
    }

    void Functions_1_2::nullifyPointers()
    {
        _nfx_glBlendColor = nullptr;
        _nfx_glBlendEquation = nullptr;
        _nfx_glColorSubTable = nullptr;
        _nfx_glColorTable = nullptr;
        _nfx_glColorTableParameterfv = nullptr;
        _nfx_glColorTableParameteriv = nullptr;
        _nfx_glConvolutionFilter1D = nullptr;
        _nfx_glConvolutionFilter2D = nullptr;
        _nfx_glConvolutionParameterf = nullptr;
        _nfx_glConvolutionParameterfv = nullptr;
        _nfx_glConvolutionParameteri = nullptr;
        _nfx_glConvolutionParameteriv = nullptr;
        _nfx_glCopyColorSubTable = nullptr;
        _nfx_glCopyColorTable = nullptr;
        _nfx_glCopyConvolutionFilter1D = nullptr;
        _nfx_glCopyConvolutionFilter2D = nullptr;
        _nfx_glCopyTexSubImage3D = nullptr;
        _nfx_glDrawRangeElements = nullptr;
        _nfx_glGetColorTable = nullptr;
        _nfx_glGetColorTableParameterfv = nullptr;
        _nfx_glGetColorTableParameteriv = nullptr;
        _nfx_glGetConvolutionFilter = nullptr;
        _nfx_glGetConvolutionParameterfv = nullptr;
        _nfx_glGetConvolutionParameteriv = nullptr;
        _nfx_glGetHistogram = nullptr;
        _nfx_glGetHistogramParameterfv = nullptr;
        _nfx_glGetHistogramParameteriv = nullptr;
        _nfx_glGetMinmax = nullptr;
        _nfx_glGetMinmaxParameterfv = nullptr;
        _nfx_glGetMinmaxParameteriv = nullptr;
        _nfx_glGetSeparableFilter = nullptr;
        _nfx_glHistogram = nullptr;
        _nfx_glMinmax = nullptr;
        _nfx_glResetHistogram = nullptr;
        _nfx_glResetMinmax = nullptr;
        _nfx_glSeparableFilter2D = nullptr;
        _nfx_glTexImage3D = nullptr;
        _nfx_glTexSubImage3D = nullptr;
    }
} // namespace nfx::graphics::gl
