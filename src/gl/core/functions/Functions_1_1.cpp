#include "nfx/graphics/gl/core/functions/Functions_1_1.h"

#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_1::Functions_1_1()
        : Functions_1_0{}
    {}

    Functions_1_1::~Functions_1_1() {}

    GLboolean Functions_1_1::glAreTexturesResident(
        GLsizei n, const GLuint* textures, GLboolean* residences, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glAreTexturesResident(n, textures, residences), caller);

        return ret;
    }

    GLvoid Functions_1_1::glArrayElement(GLint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glArrayElement(index), caller);
    }

    GLvoid Functions_1_1::glBindTexture(GLenum target, GLuint texture, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glBindTexture(target, texture), caller);
    }

    GLvoid Functions_1_1::glColorPointer(
        GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColorPointer(size, type, stride, pointer), caller);
    }

    GLvoid Functions_1_1::glTexEnvf(
        GLenum target, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvf(target, pname, param), caller);
    }

    GLvoid Functions_1_1::glTexEnvfv(
        GLenum target, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvfv(target, pname, params), caller);
    }

    GLvoid Functions_1_1::glTexEnvi(GLenum target, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvi(target, pname, param), caller);
    }

    GLvoid Functions_1_1::glTexEnviv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnviv(target, pname, params), caller);
    }

    GLvoid Functions_1_1::glTexGend(
        GLenum coord, GLenum pname, GLdouble param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGend(coord, pname, param), caller);
    }

    GLvoid Functions_1_1::glTexGendv(
        GLenum coord, GLenum pname, const GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGendv(coord, pname, params), caller);
    }

    GLvoid Functions_1_1::glTexGenf(
        GLenum coord, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGenf(coord, pname, param), caller);
    }

    GLvoid Functions_1_1::glTexGenfv(
        GLenum coord, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGenfv(coord, pname, params), caller);
    }

    GLvoid Functions_1_1::glTexGeni(GLenum coord, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGeni(coord, pname, param), caller);
    }

    GLvoid Functions_1_1::glTexGeniv(
        GLenum coord, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGeniv(coord, pname, params), caller);
    }

    GLvoid Functions_1_1::glCopyTexImage1D(
        GLenum target,
        GLint level,
        GLenum internalformat,
        GLint x,
        GLint y,
        GLsizei width,
        GLint border,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCopyTexImage1D(target, level, internalformat, x, y, width, border), caller);
    }

    GLvoid Functions_1_1::glCopyTexImage2D(
        GLenum target,
        GLint level,
        GLenum internalformat,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        GLint border,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border), caller);
    }

    GLvoid Functions_1_1::glCopyTexSubImage1D(
        GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCopyTexSubImage1D(target, level, xoffset, x, y, width), caller);
    }

    GLvoid Functions_1_1::glCopyTexSubImage2D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height), caller);
    }

    GLvoid Functions_1_1::glDeleteTextures(GLsizei n, const GLuint* textures, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDeleteTextures(n, textures), caller);
    }

    GLvoid Functions_1_1::glDisableClientState(GLenum array, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDisableClientState(array), caller);
    }

    GLvoid Functions_1_1::glDrawArrays(
        GLenum mode, GLint first, GLsizei count, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDrawArrays(mode, first, count), caller);
    }

    GLvoid Functions_1_1::glDrawElements(
        GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDrawElements(mode, count, type, indices), caller);
    }

    GLvoid Functions_1_1::glEdgeFlagPointer(
        GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEdgeFlagPointer(stride, pointer), caller);
    }

    GLvoid Functions_1_1::glEnableClientState(GLenum array, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEnableClientState(array), caller);
    }

    GLvoid Functions_1_1::glGenTextures(GLsizei n, GLuint* textures, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGenTextures(n, textures), caller);
    }

    GLvoid Functions_1_1::glGetPointerv(GLenum pname, GLvoid** params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetPointerv(pname, params), caller);
    }

    GLvoid Functions_1_1::glIndexPointer(
        GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexPointer(type, stride, pointer), caller);
    }

    GLvoid Functions_1_1::glIndexub(GLubyte c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexub(c), caller);
    }

    GLvoid Functions_1_1::glIndexubv(const GLubyte* c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexubv(c), caller);
    }

    GLvoid Functions_1_1::glInterleavedArrays(
        GLenum format, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glInterleavedArrays(format, stride, pointer), caller);
    }

    GLboolean Functions_1_1::glIsTexture(GLuint texture, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glIsTexture(texture), caller);

        return ret;
    }

    GLvoid Functions_1_1::glNormalPointer(
        GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormalPointer(type, stride, pointer), caller);
    }

    GLvoid Functions_1_1::glPolygonOffset(GLfloat factor, GLfloat units, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPolygonOffset(factor, units), caller);
    }

    GLvoid Functions_1_1::glPopClientAttrib([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPopClientAttrib(), caller);
    }

    GLvoid Functions_1_1::glPrioritizeTextures(
        GLsizei n, const GLuint* textures, const GLclampf* priorities, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPrioritizeTextures(n, textures, priorities), caller);
    }

    GLvoid Functions_1_1::glPushClientAttrib(GLbitfield mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPushClientAttrib(mask), caller);
    }

    GLvoid Functions_1_1::glTexCoordPointer(
        GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoordPointer(size, type, stride, pointer), caller);
    }

    GLvoid Functions_1_1::glTexSubImage1D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLsizei width,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexSubImage1D(target, level, xoffset, width, format, type, pixels), caller);
    }

    GLvoid Functions_1_1::glTexSubImage2D(
        GLenum target,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels), caller);
    }

    GLvoid Functions_1_1::glVertexPointer(
        GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertexPointer(size, type, stride, pointer), caller);
    }
} // namespace nfx::graphics::gl
