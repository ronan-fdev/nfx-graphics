#include "nfx/graphics/gl/core/functions/Functions_1_3.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_3::Functions_1_3()
        : Functions_1_2{}
    {}

    Functions_1_3::~Functions_1_3() {}

    GLvoid Functions_1_3::glActiveTexture(GLenum texture, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glActiveTexture(texture), caller);
    }

    GLvoid Functions_1_3::glClientActiveTexture(GLenum texture, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClientActiveTexture(texture), caller);
    }

    GLvoid Functions_1_3::glCompressedTexImage1D(
        GLenum target,
        GLint level,
        GLenum internalformat,
        GLsizei width,
        GLint border,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data), caller);
    }

    GLvoid Functions_1_3::glCompressedTexImage2D(
        GLenum target,
        GLint level,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLint border,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data), caller);
    }

    GLvoid Functions_1_3::glCompressedTexImage3D(
        GLenum target,
        GLint level,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLint border,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data),
            caller);
    }

    GLvoid Functions_1_3::glCompressedTexSubImage1D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLsizei width,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data), caller);
    }

    GLvoid Functions_1_3::glCompressedTexSubImage2D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data),
            caller);
    }

    GLvoid Functions_1_3::glCompressedTexSubImage3D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTexSubImage3D(
                target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data),
            caller);
    }

    GLvoid Functions_1_3::glGetCompressedTexImage(
        GLenum target, GLint level, GLvoid* img, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetCompressedTexImage(target, level, img), caller);
    }

    GLvoid Functions_1_3::glLoadTransposeMatrixd(const GLdouble* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glLoadTransposeMatrixd(m), caller);
    }

    GLvoid Functions_1_3::glLoadTransposeMatrixf(const GLfloat* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glLoadTransposeMatrixf(m), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1d(GLenum target, GLdouble s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1d(target, s), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1dv(
        GLenum target, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1dv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1f(GLenum target, GLfloat s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1f(target, s), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1fv(GLenum target, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1fv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1i(GLenum target, GLint s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1i(target, s), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1iv(GLenum target, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1iv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1s(GLenum target, GLshort v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1s(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord1sv(GLenum target, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord1sv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2d(
        GLenum target, GLdouble s, GLdouble t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2d(target, s, t), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2dv(
        GLenum target, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2dv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2f(
        GLenum target, GLfloat s, GLfloat t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2f(target, s, t), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2fv(GLenum target, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2fv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2i(GLenum target, GLint s, GLint t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2i(target, s, t), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2iv(GLenum target, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2iv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2s(
        GLenum target, GLshort s, GLshort t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2s(target, s, t), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord2sv(GLenum target, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord2sv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3d(
        GLenum target, GLdouble s, GLdouble t, GLdouble r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3d(target, s, t, r), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3dv(
        GLenum target, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3dv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3f(
        GLenum target, GLfloat s, GLfloat t, GLfloat r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3f(target, s, t, r), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3fv(GLenum target, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3fv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3i(
        GLenum target, GLint s, GLint t, GLint r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3i(target, s, t, r), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3iv(GLenum target, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3iv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3s(
        GLenum target, GLshort s, GLshort t, GLshort r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3s(target, s, t, r), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord3sv(GLenum target, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord3sv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4d(
        GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4d(target, s, t, r, q), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4dv(
        GLenum target, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4dv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4f(
        GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4f(target, s, t, r, q), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4fv(GLenum target, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4fv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4i(
        GLenum target, GLint s, GLint t, GLint r, GLint q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4i(target, s, t, r, q), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4iv(GLenum target, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4iv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4s(
        GLenum target, GLshort s, GLshort t, GLshort r, GLshort q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4s(target, s, t, r, q), caller);
    }

    GLvoid Functions_1_3::glMultiTexCoord4sv(GLenum target, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoord4sv(target, v), caller);
    }

    GLvoid Functions_1_3::glMultTransposeMatrixd(const GLdouble* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultTransposeMatrixd(m), caller);
    }

    GLvoid Functions_1_3::glMultTransposeMatrixf(const GLfloat* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultTransposeMatrixf(m), caller);
    }

    GLvoid Functions_1_3::glSampleCoverage(GLfloat value, GLboolean invert, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSampleCoverage(value, invert), caller);
    }

    bool Functions_1_3::initialize()
    {
        Functions_1_2::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glActiveTexture = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glActiveTexture"));
        _nfx_glClientActiveTexture =
            reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glClientActiveTexture"));
        _nfx_glCompressedTexImage1D =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTexImage1D"));
        _nfx_glCompressedTexImage2D =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTexImage2D"));
        _nfx_glCompressedTexImage3D = reinterpret_cast<GLvoid (*)(
            GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glCompressedTexImage3D"));
        _nfx_glCompressedTexSubImage1D =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTexSubImage1D"));
        _nfx_glCompressedTexSubImage2D =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTexSubImage2D"));
        _nfx_glCompressedTexSubImage3D = reinterpret_cast<GLvoid (*)(
            GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glCompressedTexSubImage3D"));
        _nfx_glGetCompressedTexImage =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLvoid*)>(loader.loadFunctionPtr("glGetCompressedTexImage"));
        _nfx_glLoadTransposeMatrixd =
            reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glLoadTransposeMatrixd"));
        _nfx_glLoadTransposeMatrixf =
            reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glLoadTransposeMatrixf"));
        _nfx_glMultiTexCoord1d =
            reinterpret_cast<GLvoid (*)(GLenum, GLdouble)>(loader.loadFunctionPtr("glMultiTexCoord1d"));
        _nfx_glMultiTexCoord1dv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLdouble*)>(loader.loadFunctionPtr("glMultiTexCoord1dv"));
        _nfx_glMultiTexCoord1f =
            reinterpret_cast<GLvoid (*)(GLenum, GLfloat)>(loader.loadFunctionPtr("glMultiTexCoord1f"));
        _nfx_glMultiTexCoord1fv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glMultiTexCoord1fv"));
        _nfx_glMultiTexCoord1i =
            reinterpret_cast<GLvoid (*)(GLenum, GLint)>(loader.loadFunctionPtr("glMultiTexCoord1i"));
        _nfx_glMultiTexCoord1iv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLint*)>(loader.loadFunctionPtr("glMultiTexCoord1iv"));
        _nfx_glMultiTexCoord1s =
            reinterpret_cast<GLvoid (*)(GLenum, GLshort)>(loader.loadFunctionPtr("glMultiTexCoord1s"));
        _nfx_glMultiTexCoord1sv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLshort*)>(loader.loadFunctionPtr("glMultiTexCoord1sv"));
        _nfx_glMultiTexCoord2d =
            reinterpret_cast<GLvoid (*)(GLenum, GLdouble, GLdouble t)>(loader.loadFunctionPtr("glMultiTexCoord2d"));
        _nfx_glMultiTexCoord2dv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLdouble*)>(loader.loadFunctionPtr("glMultiTexCoord2dv"));
        _nfx_glMultiTexCoord2f =
            reinterpret_cast<GLvoid (*)(GLenum, GLfloat, GLfloat)>(loader.loadFunctionPtr("glMultiTexCoord2f"));
        _nfx_glMultiTexCoord2fv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glMultiTexCoord2fv"));
        _nfx_glMultiTexCoord2i =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint)>(loader.loadFunctionPtr("glMultiTexCoord2i"));
        _nfx_glMultiTexCoord2iv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLint*)>(loader.loadFunctionPtr("glMultiTexCoord2iv"));
        _nfx_glMultiTexCoord2s =
            reinterpret_cast<GLvoid (*)(GLenum, GLshort, GLshort)>(loader.loadFunctionPtr("glMultiTexCoord2s"));
        _nfx_glMultiTexCoord2sv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLshort*)>(loader.loadFunctionPtr("glMultiTexCoord2sv"));
        _nfx_glMultiTexCoord3d = reinterpret_cast<GLvoid (*)(GLenum, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glMultiTexCoord3d"));
        _nfx_glMultiTexCoord3dv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLdouble*)>(loader.loadFunctionPtr("glMultiTexCoord3dv"));
        _nfx_glMultiTexCoord3f = reinterpret_cast<GLvoid (*)(GLenum, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glMultiTexCoord3f"));
        _nfx_glMultiTexCoord3fv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glMultiTexCoord3fv"));
        _nfx_glMultiTexCoord3i =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint, GLint)>(loader.loadFunctionPtr("glMultiTexCoord3i"));
        _nfx_glMultiTexCoord3iv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLint*)>(loader.loadFunctionPtr("glMultiTexCoord3iv"));
        _nfx_glMultiTexCoord3s = reinterpret_cast<GLvoid (*)(GLenum, GLshort, GLshort, GLshort)>(
            loader.loadFunctionPtr("glMultiTexCoord3s"));
        _nfx_glMultiTexCoord3sv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLshort*)>(loader.loadFunctionPtr("glMultiTexCoord3sv"));
        _nfx_glMultiTexCoord4d = reinterpret_cast<GLvoid (*)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glMultiTexCoord4d"));
        _nfx_glMultiTexCoord4dv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLdouble*)>(loader.loadFunctionPtr("glMultiTexCoord4dv"));
        _nfx_glMultiTexCoord4f = reinterpret_cast<GLvoid (*)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glMultiTexCoord4f"));
        _nfx_glMultiTexCoord4fv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glMultiTexCoord4fv"));
        _nfx_glMultiTexCoord4i = reinterpret_cast<GLvoid (*)(GLenum, GLint, GLint, GLint, GLint)>(
            loader.loadFunctionPtr("glMultiTexCoord4i"));
        _nfx_glMultiTexCoord4iv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLint*)>(loader.loadFunctionPtr("glMultiTexCoord4iv"));
        _nfx_glMultiTexCoord4s = reinterpret_cast<GLvoid (*)(GLenum, GLshort, GLshort, GLshort, GLshort)>(
            loader.loadFunctionPtr("glMultiTexCoord4s"));
        _nfx_glMultiTexCoord4sv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLshort*)>(loader.loadFunctionPtr("glMultiTexCoord4sv"));
        _nfx_glMultTransposeMatrixd =
            reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glMultTransposeMatrixd"));
        _nfx_glMultTransposeMatrixf =
            reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glMultTransposeMatrixf"));
        _nfx_glSampleCoverage =
            reinterpret_cast<GLvoid (*)(GLfloat, GLboolean)>(loader.loadFunctionPtr("glSampleCoverage"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
