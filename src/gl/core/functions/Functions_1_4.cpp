#include "nfx/graphics/gl/core/functions/Functions_1_4.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_4::Functions_1_4()
        : Functions_1_3{}
    {}

    Functions_1_4::~Functions_1_4() {}

    GLvoid Functions_1_4::glBlendFuncSeparate(
        GLenum sfactorRGB,
        GLenum dfactorRGB,
        GLenum sfactorAlpha,
        GLenum dfactorAlpha,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha), caller);
    }

    GLvoid Functions_1_4::glFogCoordd(GLdouble coord, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFogCoordd(coord), caller);
    }

    GLvoid Functions_1_4::glFogCoorddv(const GLdouble* coord, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFogCoorddv(coord), caller);
    }

    GLvoid Functions_1_4::glFogCoordf(GLfloat coord, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFogCoordf(coord), caller);
    }

    GLvoid Functions_1_4::glFogCoordfv(const GLfloat* coord, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFogCoordfv(coord), caller);
    }

    GLvoid Functions_1_4::glFogCoordPointer(
        GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFogCoordPointer(type, stride, pointer), caller);
    }

    GLvoid Functions_1_4::glMultiDrawArrays(
        GLenum mode,
        const GLint* first,
        const GLsizei* count,
        GLsizei drawcount,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiDrawArrays(mode, first, count, drawcount), caller);
    }

    GLvoid Functions_1_4::glMultiDrawElements(
        GLenum mode,
        const GLsizei* count,
        GLenum type,
        const GLvoid* const* indices,
        GLsizei drawcount,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiDrawElements(mode, count, type, indices, drawcount), caller);
    }

    GLvoid Functions_1_4::glPointParameterf(GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPointParameterf(pname, param), caller);
    }

    GLvoid Functions_1_4::glPointParameterfv(
        GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPointParameterfv(pname, params), caller);
    }

    GLvoid Functions_1_4::glPointParameteri(GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPointParameteri(pname, param), caller);
    }

    GLvoid Functions_1_4::glPointParameteriv(
        GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPointParameteriv(pname, params), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3b(
        GLbyte red, GLbyte green, GLbyte blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3b(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3bv(const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3bv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3d(
        GLdouble red, GLdouble green, GLdouble blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3d(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3dv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3f(
        GLfloat red, GLfloat green, GLfloat blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3f(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3fv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3i(
        GLint red, GLint green, GLint blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3i(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3iv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3s(
        GLshort red, GLshort green, GLshort blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3s(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3sv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3ub(
        GLubyte red, GLubyte green, GLubyte blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3ub(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3ubv(const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3ubv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3ui(
        GLuint red, GLuint green, GLuint blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3ui(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3uiv(const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3uiv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3us(
        GLushort red, GLushort green, GLushort blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3us(red, green, blue), caller);
    }

    GLvoid Functions_1_4::glSecondaryColor3usv(const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColor3usv(v), caller);
    }

    GLvoid Functions_1_4::glSecondaryColorPointer(
        GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColorPointer(size, type, stride, pointer), caller);
    }

    GLvoid Functions_1_4::glWindowPos2d(GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2d(x, y), caller);
    }

    GLvoid Functions_1_4::glWindowPos2dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2dv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos2f(GLfloat x, GLfloat y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2f(x, y), caller);
    }

    GLvoid Functions_1_4::glWindowPos2fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2fv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos2i(GLint x, GLint y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2i(x, y), caller);
    }

    GLvoid Functions_1_4::glWindowPos2iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2iv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos2s(GLshort x, GLshort y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2s(x, y), caller);
    }

    GLvoid Functions_1_4::glWindowPos2sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos2sv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos3d(GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3d(x, y, z), caller);
    }

    GLvoid Functions_1_4::glWindowPos3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3dv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos3f(GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3f(x, y, z), caller);
    }

    GLvoid Functions_1_4::glWindowPos3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3fv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos3i(GLint x, GLint y, GLint z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3i(x, y, z), caller);
    }

    GLvoid Functions_1_4::glWindowPos3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3iv(v), caller);
    }

    GLvoid Functions_1_4::glWindowPos3s(GLshort x, GLshort y, GLshort z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3s(x, y, z), caller);
    }

    GLvoid Functions_1_4::glWindowPos3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWindowPos3sv(v), caller);
    }

    bool Functions_1_4::initialize()
    {
        Functions_1_3::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBlendFuncSeparate =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLenum)>(loader.loadFunctionPtr("glBlendFuncSeparate"));
        _nfx_glFogCoordd = reinterpret_cast<GLvoid (*)(GLdouble)>(loader.loadFunctionPtr("glFogCoordd"));
        _nfx_glFogCoorddv = reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glFogCoorddv"));
        _nfx_glFogCoordf = reinterpret_cast<GLvoid (*)(GLfloat)>(loader.loadFunctionPtr("glFogCoordf"));
        _nfx_glFogCoordfv = reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glFogCoordfv"));
        _nfx_glFogCoordPointer =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, const GLvoid*)>(loader.loadFunctionPtr("glFogCoordPointer"));
        _nfx_glMultiDrawArrays = reinterpret_cast<GLvoid (*)(GLenum, const GLint*, const GLsizei*, GLsizei)>(
            loader.loadFunctionPtr("glMultiDrawArrays"));
        _nfx_glMultiDrawElements =
            reinterpret_cast<GLvoid (*)(GLenum, const GLsizei*, GLenum, const GLvoid* const*, GLsizei)>(
                loader.loadFunctionPtr("glMultiDrawElements"));
        _nfx_glPointParameterf =
            reinterpret_cast<GLvoid (*)(GLenum, GLfloat)>(loader.loadFunctionPtr("glPointParameterf"));
        _nfx_glPointParameterfv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glPointParameterfv"));
        _nfx_glPointParameteri =
            reinterpret_cast<GLvoid (*)(GLenum, GLint)>(loader.loadFunctionPtr("glPointParameteri"));
        _nfx_glPointParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLint*)>(loader.loadFunctionPtr("glPointParameteriv"));
        _nfx_glSecondaryColor3b =
            reinterpret_cast<GLvoid (*)(GLbyte, GLbyte, GLbyte)>(loader.loadFunctionPtr("glSecondaryColor3b"));
        _nfx_glSecondaryColor3bv =
            reinterpret_cast<GLvoid (*)(const GLbyte*)>(loader.loadFunctionPtr("glSecondaryColor3bv"));
        _nfx_glSecondaryColor3d =
            reinterpret_cast<GLvoid (*)(GLdouble, GLdouble, GLdouble)>(loader.loadFunctionPtr("glSecondaryColor3d"));
        _nfx_glSecondaryColor3dv =
            reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glSecondaryColor3dv"));
        _nfx_glSecondaryColor3f =
            reinterpret_cast<GLvoid (*)(GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glSecondaryColor3f"));
        _nfx_glSecondaryColor3fv =
            reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glSecondaryColor3fv"));
        _nfx_glSecondaryColor3i =
            reinterpret_cast<GLvoid (*)(GLint, GLint, GLint)>(loader.loadFunctionPtr("glSecondaryColor3i"));
        _nfx_glSecondaryColor3iv =
            reinterpret_cast<GLvoid (*)(const GLint*)>(loader.loadFunctionPtr("glSecondaryColor3iv"));
        _nfx_glSecondaryColor3s =
            reinterpret_cast<GLvoid (*)(GLshort, GLshort, GLshort)>(loader.loadFunctionPtr("glSecondaryColor3s"));
        _nfx_glSecondaryColor3sv =
            reinterpret_cast<GLvoid (*)(const GLshort*)>(loader.loadFunctionPtr("glSecondaryColor3sv"));
        _nfx_glSecondaryColor3ub =
            reinterpret_cast<GLvoid (*)(GLubyte, GLubyte, GLubyte)>(loader.loadFunctionPtr("glSecondaryColor3ub"));
        _nfx_glSecondaryColor3ubv =
            reinterpret_cast<GLvoid (*)(const GLubyte*)>(loader.loadFunctionPtr("glSecondaryColor3ubv"));
        _nfx_glSecondaryColor3ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glSecondaryColor3ui"));
        _nfx_glSecondaryColor3uiv =
            reinterpret_cast<GLvoid (*)(const GLuint*)>(loader.loadFunctionPtr("glSecondaryColor3uiv"));
        _nfx_glSecondaryColor3us =
            reinterpret_cast<GLvoid (*)(GLushort, GLushort, GLushort)>(loader.loadFunctionPtr("glSecondaryColor3us"));
        _nfx_glSecondaryColor3usv =
            reinterpret_cast<GLvoid (*)(const GLushort*)>(loader.loadFunctionPtr("glSecondaryColor3usv"));
        _nfx_glSecondaryColorPointer = reinterpret_cast<GLvoid (*)(GLint, GLenum, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glSecondaryColorPointer"));
        _nfx_glWindowPos2d = reinterpret_cast<GLvoid (*)(GLdouble, GLdouble)>(loader.loadFunctionPtr("glWindowPos2d"));
        _nfx_glWindowPos2dv = reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glWindowPos2dv"));
        _nfx_glWindowPos2f = reinterpret_cast<GLvoid (*)(GLfloat, GLfloat)>(loader.loadFunctionPtr("glWindowPos2f"));
        _nfx_glWindowPos2fv = reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glWindowPos2fv"));
        _nfx_glWindowPos2i = reinterpret_cast<GLvoid (*)(GLint, GLint)>(loader.loadFunctionPtr("glWindowPos2i"));
        _nfx_glWindowPos2iv = reinterpret_cast<GLvoid (*)(const GLint*)>(loader.loadFunctionPtr("glWindowPos2iv"));
        _nfx_glWindowPos2s = reinterpret_cast<GLvoid (*)(GLshort, GLshort)>(loader.loadFunctionPtr("glWindowPos2s"));
        _nfx_glWindowPos2sv = reinterpret_cast<GLvoid (*)(const GLshort*)>(loader.loadFunctionPtr("glWindowPos2sv"));
        _nfx_glWindowPos3d =
            reinterpret_cast<GLvoid (*)(GLdouble, GLdouble, GLdouble)>(loader.loadFunctionPtr("glWindowPos3d"));
        _nfx_glWindowPos3dv = reinterpret_cast<GLvoid (*)(const GLdouble*)>(loader.loadFunctionPtr("glWindowPos3dv"));
        _nfx_glWindowPos3f =
            reinterpret_cast<GLvoid (*)(GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glWindowPos3f"));
        _nfx_glWindowPos3fv = reinterpret_cast<GLvoid (*)(const GLfloat*)>(loader.loadFunctionPtr("glWindowPos3fv"));
        _nfx_glWindowPos3i = reinterpret_cast<GLvoid (*)(GLint, GLint, GLint)>(loader.loadFunctionPtr("glWindowPos3i"));
        _nfx_glWindowPos3iv = reinterpret_cast<GLvoid (*)(const GLint*)>(loader.loadFunctionPtr("glWindowPos3iv"));
        _nfx_glWindowPos3s =
            reinterpret_cast<GLvoid (*)(GLshort, GLshort, GLshort)>(loader.loadFunctionPtr("glWindowPos3s"));
        _nfx_glWindowPos3sv = reinterpret_cast<GLvoid (*)(const GLshort*)>(loader.loadFunctionPtr("glWindowPos3sv"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
