#include "nfx/graphics/gl/core/functions/Functions_1_0.h"

#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_0::Functions_1_0() {}

    Functions_1_0::~Functions_1_0() {}

    GLvoid Functions_1_0::glAccum(GLenum op, GLfloat value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glAccum(op, value), caller);
    }

    GLvoid Functions_1_0::glAlphaFunc(GLenum func, GLclampf ref, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glAlphaFunc(func, ref), caller);
    }

    GLvoid Functions_1_0::glBegin(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glBegin(mode), caller);
    }

    GLvoid Functions_1_0::glBitmap(
        GLsizei width,
        GLsizei height,
        GLfloat xorig,
        GLfloat yorig,
        GLfloat xmove,
        GLfloat ymove,
        const GLubyte* bitmap,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap), caller);
    }

    GLvoid Functions_1_0::glBlendFunc(GLenum sfactor, GLenum dfactor, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glBlendFunc(sfactor, dfactor), caller);
    }

    GLvoid Functions_1_0::glCallList(GLuint list, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCallList(list), caller);
    }

    GLvoid Functions_1_0::glCallLists(
        GLsizei n, GLenum type, const GLvoid* lists, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCallLists(n, type, lists), caller);
    }

    GLvoid Functions_1_0::glClear(GLbitfield mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClear(mask), caller);
    }

    GLvoid Functions_1_0::glClearAccum(
        GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClearAccum(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glClearColor(
        GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClearColor(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glClearDepth(GLdouble depth, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClearDepth(depth), caller);
    }

    GLvoid Functions_1_0::glClearIndex(GLfloat c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClearIndex(c), caller);
    }

    GLvoid Functions_1_0::glClearStencil(GLint s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClearStencil(s), caller);
    }

    GLvoid Functions_1_0::glClipPlane(GLenum plane, const GLdouble* equation, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glClipPlane(plane, equation), caller);
    }

    GLvoid Functions_1_0::glColor3b(GLbyte red, GLbyte green, GLbyte blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3b(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3bv(const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3bv(v), caller);
    }

    GLvoid Functions_1_0::glColor3d(
        GLdouble red, GLdouble green, GLdouble blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3d(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3dv(v), caller);
    }

    GLvoid Functions_1_0::glColor3f(GLfloat red, GLfloat green, GLfloat blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3f(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3fv(v), caller);
    }

    GLvoid Functions_1_0::glColor3i(GLint red, GLint green, GLint blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3i(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3iv(v), caller);
    }

    GLvoid Functions_1_0::glColor3s(GLshort red, GLshort green, GLshort blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3s(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3sv(v), caller);
    }

    GLvoid Functions_1_0::glColor3ub(
        GLubyte red, GLubyte green, GLubyte blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3ub(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3ubv(const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3ubv(v), caller);
    }

    GLvoid Functions_1_0::glColor3ui(GLuint red, GLuint green, GLuint blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3ui(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3uiv(const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3uiv(v), caller);
    }

    GLvoid Functions_1_0::glColor3us(
        GLushort red, GLushort green, GLushort blue, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3us(red, green, blue), caller);
    }

    GLvoid Functions_1_0::glColor3usv(const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor3usv(v), caller);
    }

    GLvoid Functions_1_0::glColor4b(
        GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4b(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4bv(const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4bv(v), caller);
    }

    GLvoid Functions_1_0::glColor4d(
        GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4d(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4dv(v), caller);
    }

    GLvoid Functions_1_0::glColor4f(
        GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4f(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4fv(v), caller);
    }

    GLvoid Functions_1_0::glColor4i(
        GLint red, GLint green, GLint blue, GLint alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4i(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4iv(v), caller);
    }

    GLvoid Functions_1_0::glColor4s(
        GLshort red, GLshort green, GLshort blue, GLshort alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4s(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4sv(v), caller);
    }

    GLvoid Functions_1_0::glColor4ub(
        GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4ub(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4ubv(const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4ubv(v), caller);
    }

    GLvoid Functions_1_0::glColor4ui(
        GLuint red, GLuint green, GLuint blue, GLuint alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4ui(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4uiv(const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4uiv(v), caller);
    }

    GLvoid Functions_1_0::glColor4us(
        GLushort red, GLushort green, GLushort blue, GLushort alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4us(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glColor4usv(const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColor4usv(v), caller);
    }

    GLvoid Functions_1_0::glColorMaterial(GLenum face, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColorMaterial(face, mode), caller);
    }

    GLvoid Functions_1_0::glColorMask(
        GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glColorMask(red, green, blue, alpha), caller);
    }

    GLvoid Functions_1_0::glCopyPixels(
        GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCopyPixels(x, y, width, height, type), caller);
    }

    GLvoid Functions_1_0::glCullFace(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glCullFace(mode), caller);
    }

    GLvoid Functions_1_0::glDeleteLists(GLuint list, GLsizei range, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDeleteLists(list, range), caller);
    }

    GLvoid Functions_1_0::glDepthFunc(GLenum func, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDepthFunc(func), caller);
    }

    GLvoid Functions_1_0::glDepthMask(GLboolean flag, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDepthMask(flag), caller);
    }

    GLvoid Functions_1_0::glDepthRange(GLdouble n, GLdouble f, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDepthRange(n, f), caller);
    }

    GLvoid Functions_1_0::glDisable(GLenum cap, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDisable(cap), caller);
    }

    GLvoid Functions_1_0::glDrawBuffer(GLenum buf, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDrawBuffer(buf), caller);
    }

    GLvoid Functions_1_0::glDrawPixels(
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glDrawPixels(width, height, format, type, pixels), caller);
    }

    GLvoid Functions_1_0::glEdgeFlag(GLboolean flag, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEdgeFlag(flag), caller);
    }

    GLvoid Functions_1_0::glEdgeFlagv(const GLboolean* flag, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEdgeFlagv(flag), caller);
    }

    GLvoid Functions_1_0::glEnable(GLenum cap, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEnable(cap), caller);
    }

    GLvoid Functions_1_0::glEnd([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEnd(), caller);
    }

    GLvoid Functions_1_0::glEndList([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEndList(), caller);
    }

    GLvoid Functions_1_0::glEvalCoord1d(GLdouble u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord1d(u), caller);
    }

    GLvoid Functions_1_0::glEvalCoord1dv(const GLdouble* u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord1dv(u), caller);
    }

    GLvoid Functions_1_0::glEvalCoord1f(GLfloat u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord1f(u), caller);
    }

    GLvoid Functions_1_0::glEvalCoord1fv(const GLfloat* u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord1fv(u), caller);
    }

    GLvoid Functions_1_0::glEvalCoord2d(GLdouble u, GLdouble v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord2d(u, v), caller);
    }

    GLvoid Functions_1_0::glEvalCoord2dv(const GLdouble* u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord2dv(u), caller);
    }

    GLvoid Functions_1_0::glEvalCoord2f(GLfloat u, GLfloat v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord2f(u, v), caller);
    }

    GLvoid Functions_1_0::glEvalCoord2fv(const GLfloat* u, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalCoord2fv(u), caller);
    }

    GLvoid Functions_1_0::glEvalMesh1(GLenum mode, GLint i1, GLint i2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalMesh1(mode, i1, i2), caller);
    }

    GLvoid Functions_1_0::glEvalMesh2(
        GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalMesh2(mode, i1, i2, j1, j2), caller);
    }

    GLvoid Functions_1_0::glEvalPoint1(GLint i, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalPoint1(i), caller);
    }

    GLvoid Functions_1_0::glEvalPoint2(GLint i, GLint j, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glEvalPoint2(i, j), caller);
    }

    GLvoid Functions_1_0::glFeedbackBuffer(
        GLsizei size, GLenum type, GLfloat* buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFeedbackBuffer(size, type, buffer), caller);
    }

    GLvoid Functions_1_0::glFinish([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFinish(), caller);
    }

    GLvoid Functions_1_0::glFlush([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFlush(), caller);
    }

    GLvoid Functions_1_0::glFogf(GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFogf(pname, param), caller);
    }

    GLvoid Functions_1_0::glFogfv(GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFogfv(pname, params), caller);
    }

    GLvoid Functions_1_0::glFogi(GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFogi(pname, param), caller);
    }

    GLvoid Functions_1_0::glFogiv(GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFogiv(pname, params), caller);
    }

    GLvoid Functions_1_0::glFrontFace(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFrontFace(mode), caller);
    }

    GLvoid Functions_1_0::glFrustum(
        GLdouble left,
        GLdouble right,
        GLdouble bottom,
        GLdouble top,
        GLdouble zNear,
        GLdouble zFar,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glFrustum(left, right, bottom, top, zNear, zFar), caller);
    }

    GLuint Functions_1_0::glGenLists(GLsizei range, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glGenLists(range), caller);

        return ret;
    }

    GLvoid Functions_1_0::glGetBooleanv(GLenum pname, GLboolean* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetBooleanv(pname, data), caller);
    }

    GLvoid Functions_1_0::glGetClipPlane(GLenum plane, GLdouble* equation, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetClipPlane(plane, equation), caller);
    }

    GLvoid Functions_1_0::glGetDoublev(GLenum pname, GLdouble* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetDoublev(pname, data), caller);
    }

    GLenum Functions_1_0::glGetError([[maybe_unused]] const char* caller) const
    {
        GLenum ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glGetError(), caller);

        return ret;
    }

    GLvoid Functions_1_0::glGetFloatv(GLenum pname, GLfloat* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetFloatv(pname, data), caller);
    }

    GLvoid Functions_1_0::glGetIntegerv(GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetIntegerv(pname, params), caller);
    }

    GLvoid Functions_1_0::glGetLightfv(
        GLenum light, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetLightfv(light, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetLightiv(
        GLenum light, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetLightiv(light, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetMapdv(
        GLenum target, GLenum query, GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetMapdv(target, query, v), caller);
    }

    GLvoid Functions_1_0::glGetMapfv(GLenum target, GLenum query, GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetMapfv(target, query, v), caller);
    }

    GLvoid Functions_1_0::glGetMapiv(GLenum target, GLenum query, GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetMapiv(target, query, v), caller);
    }

    GLvoid Functions_1_0::glGetMaterialfv(
        GLenum face, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetMaterialfv(face, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetMaterialiv(
        GLenum face, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetMaterialiv(face, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetPixelMapfv(GLenum map, GLfloat* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetPixelMapfv(map, values), caller);
    }

    GLvoid Functions_1_0::glGetPixelMapuiv(GLenum map, GLuint* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetPixelMapuiv(map, values), caller);
    }

    GLvoid Functions_1_0::glGetPixelMapusv(GLenum map, GLushort* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetPixelMapusv(map, values), caller);
    }

    GLvoid Functions_1_0::glGetPolygonStipple(GLubyte* mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetPolygonStipple(mask), caller);
    }

    const GLubyte* Functions_1_0::glGetString(GLenum name, [[maybe_unused]] const char* caller) const
    {
        const GLubyte* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glGetString(name), caller);

        return ret;
    }

    GLvoid Functions_1_0::glGetTexEnvfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexEnvfv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexEnviv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexEnviv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexGendv(
        GLenum coord, GLenum pname, GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexGendv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexGenfv(
        GLenum coord, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexGenfv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexGeniv(
        GLenum coord, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexGeniv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexImage(
        GLenum target, GLint level, GLenum format, GLenum type, void* pixels, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexImage(target, level, format, type, pixels), caller);
    }

    GLvoid Functions_1_0::glGetTexLevelParameterfv(
        GLenum target, GLint level, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexLevelParameterfv(target, level, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexLevelParameteriv(
        GLenum target, GLint level, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexLevelParameteriv(target, level, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexParameterfv(
        GLenum target, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glGetTexParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glGetTexParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glHint(GLenum target, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glHint(target, mode), caller);
    }

    GLvoid Functions_1_0::glIndexd(GLdouble c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexd(c), caller);
    }

    GLvoid Functions_1_0::glIndexdv(const GLdouble* c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexdv(c), caller);
    }

    GLvoid Functions_1_0::glIndexf(GLfloat c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexf(c), caller);
    }

    GLvoid Functions_1_0::glIndexfv(const GLfloat* c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexfv(c), caller);
    }

    GLvoid Functions_1_0::glIndexi(GLint c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexi(c), caller);
    }

    GLvoid Functions_1_0::glIndexiv(const GLint* c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexiv(c), caller);
    }

    GLvoid Functions_1_0::glIndexMask(GLuint mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexMask(mask), caller);
    }

    GLvoid Functions_1_0::glIndexs(GLshort c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexs(c), caller);
    }

    GLvoid Functions_1_0::glIndexsv(const GLshort* c, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glIndexsv(c), caller);
    }

    GLvoid Functions_1_0::glInitNames([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glInitNames(), caller);
    }

    GLboolean Functions_1_0::glIsEnabled(GLenum cap, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glIsEnabled(cap), caller);

        return ret;
    }

    GLboolean Functions_1_0::glIsList(GLuint list, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glIsList(list), caller);

        return ret;
    }

    GLvoid Functions_1_0::glLightf(GLenum light, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightf(light, pname, param), caller);
    }

    GLvoid Functions_1_0::glLightfv(
        GLenum light, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightfv(light, pname, params), caller);
    }

    GLvoid Functions_1_0::glLighti(GLenum light, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLighti(light, pname, param), caller);
    }

    GLvoid Functions_1_0::glLightiv(
        GLenum light, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightiv(light, pname, params), caller);
    }

    GLvoid Functions_1_0::glLightModelf(GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightModelf(pname, param), caller);
    }

    GLvoid Functions_1_0::glLightModelfv(GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightModelfv(pname, params), caller);
    }

    GLvoid Functions_1_0::glLightModeli(GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightModeli(pname, param), caller);
    }

    GLvoid Functions_1_0::glLightModeliv(GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLightModeliv(pname, params), caller);
    }

    GLvoid Functions_1_0::glLineStipple(GLint factor, GLushort pattern, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLineStipple(factor, pattern), caller);
    }

    GLvoid Functions_1_0::glLineWidth(GLfloat width, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLineWidth(width), caller);
    }

    GLvoid Functions_1_0::glListBase(GLuint base, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glListBase(base), caller);
    }

    GLvoid Functions_1_0::glLoadIdentity([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLoadIdentity(), caller);
    }

    GLvoid Functions_1_0::glLoadMatrixd(const GLdouble* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLoadMatrixd(m), caller);
    }

    GLvoid Functions_1_0::glLoadMatrixf(const GLfloat* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLoadMatrixf(m), caller);
    }

    GLvoid Functions_1_0::glLoadName(GLuint name, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLoadName(name), caller);
    }

    GLvoid Functions_1_0::glLogicOp(GLenum opcode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glLogicOp(opcode), caller);
    }

    GLvoid Functions_1_0::glMap1d(
        GLenum target,
        GLdouble u1,
        GLdouble u2,
        GLint stride,
        GLint order,
        const GLdouble* points,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMap1d(target, u1, u2, stride, order, points), caller);
    }

    GLvoid Functions_1_0::glMap1f(
        GLenum target,
        GLfloat u1,
        GLfloat u2,
        GLint stride,
        GLint order,
        const GLfloat* points,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMap1f(target, u1, u2, stride, order, points), caller);
    }

    GLvoid Functions_1_0::glMap2d(
        GLenum target,
        GLdouble u1,
        GLdouble u2,
        GLint ustride,
        GLint uorder,
        GLdouble v1,
        GLdouble v2,
        GLint vstride,
        GLint vorder,
        const GLdouble* points,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points), caller);
    }

    GLvoid Functions_1_0::glMap2f(
        GLenum target,
        GLfloat u1,
        GLfloat u2,
        GLint ustride,
        GLint uorder,
        GLfloat v1,
        GLfloat v2,
        GLint vstride,
        GLint vorder,
        const GLfloat* points,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points), caller);
    }

    GLvoid Functions_1_0::glMapGrid1d(GLint un, GLdouble u1, GLdouble u2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMapGrid1d(un, u1, u2), caller);
    }

    GLvoid Functions_1_0::glMapGrid1f(GLint un, GLfloat u1, GLfloat u2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMapGrid1f(un, u1, u2), caller);
    }

    GLvoid Functions_1_0::glMapGrid2d(
        GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMapGrid2d(un, u1, u2, vn, v1, v2), caller);
    }

    GLvoid Functions_1_0::glMapGrid2f(
        GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMapGrid2f(un, u1, u2, vn, v1, v2), caller);
    }

    GLvoid Functions_1_0::glMaterialf(
        GLenum face, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMaterialf(face, pname, param), caller);
    }

    GLvoid Functions_1_0::glMaterialfv(
        GLenum face, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMaterialfv(face, pname, params), caller);
    }

    GLvoid Functions_1_0::glMateriali(GLenum face, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMateriali(face, pname, param), caller);
    }

    GLvoid Functions_1_0::glMaterialiv(
        GLenum face, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMaterialiv(face, pname, params), caller);
    }

    GLvoid Functions_1_0::glMatrixMode(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMatrixMode(mode), caller);
    }

    GLvoid Functions_1_0::glMultMatrixd(const GLdouble* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMultMatrixd(m), caller);
    }

    GLvoid Functions_1_0::glMultMatrixf(const GLfloat* m, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glMultMatrixf(m), caller);
    }

    GLvoid Functions_1_0::glNewList(GLuint list, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNewList(list, mode), caller);
    }

    GLvoid Functions_1_0::glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3b(nx, ny, nz), caller);
    }

    GLvoid Functions_1_0::glNormal3bv(const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3bv(v), caller);
    }

    GLvoid Functions_1_0::glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3d(nx, ny, nz), caller);
    }

    GLvoid Functions_1_0::glNormal3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3dv(v), caller);
    }

    GLvoid Functions_1_0::glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3f(nx, ny, nz), caller);
    }

    GLvoid Functions_1_0::glNormal3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3fv(v), caller);
    }

    GLvoid Functions_1_0::glNormal3i(GLint nx, GLint ny, GLint nz, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3i(nx, ny, nz), caller);
    }

    GLvoid Functions_1_0::glNormal3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3iv(v), caller);
    }

    GLvoid Functions_1_0::glNormal3s(GLshort nx, GLshort ny, GLshort nz, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3s(nx, ny, nz), caller);
    }

    GLvoid Functions_1_0::glNormal3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glNormal3sv(v), caller);
    }

    GLvoid Functions_1_0::glOrtho(
        GLdouble left,
        GLdouble right,
        GLdouble bottom,
        GLdouble top,
        GLdouble zNear,
        GLdouble zFar,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glOrtho(left, right, bottom, top, zNear, zFar), caller);
    }

    GLvoid Functions_1_0::glPassThrough(GLfloat token, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPassThrough(token), caller);
    }

    GLvoid Functions_1_0::glPixelMapfv(
        GLenum map, GLint mapsize, const GLfloat* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelMapfv(map, mapsize, values), caller);
    }

    GLvoid Functions_1_0::glPixelMapuiv(
        GLenum map, GLint mapsize, const GLuint* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelMapuiv(map, mapsize, values), caller);
    }

    GLvoid Functions_1_0::glPixelMapusv(
        GLenum map, GLint mapsize, const GLushort* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelMapusv(map, mapsize, values), caller);
    }

    GLvoid Functions_1_0::glPixelStoref(GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelStoref(pname, param), caller);
    }

    GLvoid Functions_1_0::glPixelStorei(GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelStorei(pname, param), caller);
    }

    GLvoid Functions_1_0::glPixelTransferf(GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelTransferf(pname, param), caller);
    }

    GLvoid Functions_1_0::glPixelTransferi(GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelTransferi(pname, param), caller);
    }

    GLvoid Functions_1_0::glPixelZoom(GLfloat xfactor, GLfloat yfactor, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPixelZoom(xfactor, yfactor), caller);
    }

    GLvoid Functions_1_0::glPointSize(GLfloat size, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPointSize(size), caller);
    }

    GLvoid Functions_1_0::glPolygonMode(GLenum face, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPolygonMode(face, mode), caller);
    }

    GLvoid Functions_1_0::glPolygonStipple(const GLubyte* mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPolygonStipple(mask), caller);
    }

    GLvoid Functions_1_0::glPopAttrib([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPopAttrib(), caller);
    }

    GLvoid Functions_1_0::glPopMatrix([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPopMatrix(), caller);
    }

    GLvoid Functions_1_0::glPopName([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPopName(), caller);
    }

    GLvoid Functions_1_0::glPushAttrib(GLbitfield mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPushAttrib(mask), caller);
    }

    GLvoid Functions_1_0::glPushMatrix([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPushMatrix(), caller);
    }

    GLvoid Functions_1_0::glPushName(GLuint name, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glPushName(name), caller);
    }

    GLvoid Functions_1_0::glRasterPos2d(GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2d(x, y), caller);
    }

    GLvoid Functions_1_0::glRasterPos2dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2dv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos2f(GLfloat x, GLfloat y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2f(x, y), caller);
    }

    GLvoid Functions_1_0::glRasterPos2fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2fv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos2i(GLint x, GLint y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2i(x, y), caller);
    }

    GLvoid Functions_1_0::glRasterPos2iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2iv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos2s(GLshort x, GLshort y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2s(x, y), caller);
    }

    GLvoid Functions_1_0::glRasterPos2sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos2sv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos3d(GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3d(x, y, z), caller);
    }

    GLvoid Functions_1_0::glRasterPos3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3dv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos3f(GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3f(x, y, z), caller);
    }

    GLvoid Functions_1_0::glRasterPos3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3fv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos3i(GLint x, GLint y, GLint z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3i(x, y, z), caller);
    }

    GLvoid Functions_1_0::glRasterPos3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3iv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos3s(GLshort x, GLshort y, GLshort z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3s(x, y, z), caller);
    }

    GLvoid Functions_1_0::glRasterPos3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos3sv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos4d(
        GLdouble x, GLdouble y, GLdouble z, GLdouble w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4d(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glRasterPos4dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4dv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos4f(
        GLfloat x, GLfloat y, GLfloat z, GLfloat w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4f(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glRasterPos4fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4fv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos4i(GLint x, GLint y, GLint z, GLint w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4i(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glRasterPos4iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4iv(v), caller);
    }

    GLvoid Functions_1_0::glRasterPos4s(
        GLshort x, GLshort y, GLshort z, GLshort w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4s(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glRasterPos4sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRasterPos4sv(v), caller);
    }

    GLvoid Functions_1_0::glReadBuffer(GLenum src, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glReadBuffer(src), caller);
    }

    GLvoid Functions_1_0::glReadPixels(
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        void* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glReadPixels(x, y, width, height, format, type, pixels), caller);
    }

    GLvoid Functions_1_0::glRectd(
        GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectd(x1, y1, x2, y2), caller);
    }

    GLvoid Functions_1_0::glRectdv(const GLdouble* v1, const GLdouble* v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectdv(v1, v2), caller);
    }

    GLvoid Functions_1_0::glRectf(
        GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectf(x1, y1, x2, y2), caller);
    }

    GLvoid Functions_1_0::glRectfv(const GLfloat* v1, const GLfloat* v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectfv(v1, v2), caller);
    }

    GLvoid Functions_1_0::glRecti(GLint x1, GLint y1, GLint x2, GLint y2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRecti(x1, y1, x2, y2), caller);
    }

    GLvoid Functions_1_0::glRectiv(const GLint* v1, const GLint* v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectiv(v1, v2), caller);
    }

    GLvoid Functions_1_0::glRects(
        GLshort x1, GLshort y1, GLshort x2, GLshort y2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRects(x1, y1, x2, y2), caller);
    }

    GLvoid Functions_1_0::glRectsv(const GLshort* v1, const GLshort* v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRectsv(v1, v2), caller);
    }

    GLint Functions_1_0::glRenderMode(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = ::glRenderMode(mode), caller);

        return ret;
    }

    GLvoid Functions_1_0::glRotated(
        GLdouble angle, GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRotated(angle, x, y, z), caller);
    }

    GLvoid Functions_1_0::glRotatef(
        GLfloat angle, GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glRotatef(angle, x, y, z), caller);
    }

    GLvoid Functions_1_0::glScaled(GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glScaled(x, y, z), caller);
    }

    GLvoid Functions_1_0::glScalef(GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glScalef(x, y, z), caller);
    }

    GLvoid Functions_1_0::glScissor(
        GLint x, GLint y, GLsizei width, GLsizei height, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glScissor(x, y, width, height), caller);
    }

    GLvoid Functions_1_0::glSelectBuffer(GLsizei size, GLuint* buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glSelectBuffer(size, buffer), caller);
    }

    GLvoid Functions_1_0::glShadeModel(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glShadeModel(mode), caller);
    }

    GLvoid Functions_1_0::glStencilFunc(GLenum func, GLint ref, GLuint mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glStencilFunc(func, ref, mask), caller);
    }

    GLvoid Functions_1_0::glStencilMask(GLuint mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glStencilMask(mask), caller);
    }

    GLvoid Functions_1_0::glStencilOp(
        GLenum fail, GLenum zfail, GLenum zpass, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glStencilOp(fail, zfail, zpass), caller);
    }

    GLvoid Functions_1_0::glTexCoord1d(GLdouble s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1d(s), caller);
    }

    GLvoid Functions_1_0::glTexCoord1dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1dv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord1f(GLfloat s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1f(s), caller);
    }

    GLvoid Functions_1_0::glTexCoord1fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1fv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord1i(GLint s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1i(s), caller);
    }

    GLvoid Functions_1_0::glTexCoord1iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1iv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord1s(GLshort s, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1s(s), caller);
    }

    GLvoid Functions_1_0::glTexCoord1sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord1sv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord2d(GLdouble s, GLdouble t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2d(s, t), caller);
    }

    GLvoid Functions_1_0::glTexCoord2dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2dv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord2f(GLfloat s, GLfloat t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2f(s, t), caller);
    }

    GLvoid Functions_1_0::glTexCoord2fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2fv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord2i(GLint s, GLint t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2i(s, t), caller);
    }

    GLvoid Functions_1_0::glTexCoord2iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2iv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord2s(GLshort s, GLshort t, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2s(s, t), caller);
    }

    GLvoid Functions_1_0::glTexCoord2sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2sv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord3d(GLdouble s, GLdouble t, GLdouble r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3d(s, t, r), caller);
    }

    GLvoid Functions_1_0::glTexCoord3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3dv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord3f(GLfloat s, GLfloat t, GLfloat r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3f(s, t, r), caller);
    }

    GLvoid Functions_1_0::glTexCoord3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord2fv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord3i(GLint s, GLint t, GLint r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3i(s, t, r), caller);
    }

    GLvoid Functions_1_0::glTexCoord3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3iv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord3s(GLshort s, GLshort t, GLshort r, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3s(s, t, r), caller);
    }

    GLvoid Functions_1_0::glTexCoord3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord3sv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord4d(
        GLdouble s, GLdouble t, GLdouble r, GLdouble q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4d(s, t, r, q), caller);
    }

    GLvoid Functions_1_0::glTexCoord4dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4dv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord4f(
        GLfloat s, GLfloat t, GLfloat r, GLfloat q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4f(s, t, r, q), caller);
    }

    GLvoid Functions_1_0::glTexCoord4fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4fv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord4i(GLint s, GLint t, GLint r, GLint q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4i(s, t, r, q), caller);
    }

    GLvoid Functions_1_0::glTexCoord4iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4iv(v), caller);
    }

    GLvoid Functions_1_0::glTexCoord4s(
        GLshort s, GLshort t, GLshort r, GLshort q, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4s(s, t, r, q), caller);
    }

    GLvoid Functions_1_0::glTexCoord4sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexCoord4sv(v), caller);
    }

    GLvoid Functions_1_0::glTexEnvf(
        GLenum target, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvf(target, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexEnvfv(
        GLenum target, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvfv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexEnvi(GLenum target, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnvi(target, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexEnviv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexEnviv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexGend(
        GLenum coord, GLenum pname, GLdouble param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGend(coord, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexGendv(
        GLenum coord, GLenum pname, const GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGendv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexGenf(
        GLenum coord, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGenf(coord, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexGenfv(
        GLenum coord, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGenfv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexGeni(GLenum coord, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGeni(coord, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexGeniv(
        GLenum coord, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexGeniv(coord, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexImage1D(
        GLenum target,
        GLint level,
        GLint internalformat,
        GLsizei width,
        GLint border,
        GLenum format,
        GLenum type,
        const void* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glTexImage1D(target, level, internalformat, width, border, format, type, pixels), caller);
    }

    GLvoid Functions_1_0::glTexImage2D(
        GLenum target,
        GLint level,
        GLint internalformat,
        GLsizei width,
        GLsizei height,
        GLint border,
        GLenum format,
        GLenum type,
        const void* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            ::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels), caller);
    }

    GLvoid Functions_1_0::glTexParameterf(
        GLenum target, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexParameterf(target, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexParameterfv(
        GLenum target, GLenum pname, const GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexParameterfv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glTexParameteri(
        GLenum target, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexParameteri(target, pname, param), caller);
    }

    GLvoid Functions_1_0::glTexParameteriv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTexParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_0::glTranslated(GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTranslated(x, y, z), caller);
    }

    GLvoid Functions_1_0::glTranslatef(GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glTranslatef(x, y, z), caller);
    }

    GLvoid Functions_1_0::glVertex2d(GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2d(x, y), caller);
    }

    GLvoid Functions_1_0::glVertex2dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2dv(v), caller);
    }

    GLvoid Functions_1_0::glVertex2f(GLfloat x, GLfloat y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2f(x, y), caller);
    }

    GLvoid Functions_1_0::glVertex2fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2fv(v), caller);
    }

    GLvoid Functions_1_0::glVertex2i(GLint x, GLint y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2i(x, y), caller);
    }

    GLvoid Functions_1_0::glVertex2iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2iv(v), caller);
    }

    GLvoid Functions_1_0::glVertex2s(GLshort x, GLshort y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2s(x, y), caller);
    }

    GLvoid Functions_1_0::glVertex2sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex2sv(v), caller);
    }

    GLvoid Functions_1_0::glVertex3d(GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3d(x, y, z), caller);
    }

    GLvoid Functions_1_0::glVertex3dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3dv(v), caller);
    }

    GLvoid Functions_1_0::glVertex3f(GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3f(x, y, z), caller);
    }

    GLvoid Functions_1_0::glVertex3fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3fv(v), caller);
    }

    GLvoid Functions_1_0::glVertex3i(GLint x, GLint y, GLint z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3i(x, y, z), caller);
    }

    GLvoid Functions_1_0::glVertex3iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3iv(v), caller);
    }

    GLvoid Functions_1_0::glVertex3s(GLshort x, GLshort y, GLshort z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3s(x, y, z), caller);
    }

    GLvoid Functions_1_0::glVertex3sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex3sv(v), caller);
    }

    GLvoid Functions_1_0::glVertex4d(
        GLdouble x, GLdouble y, GLdouble z, GLdouble w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4d(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glVertex4dv(const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4dv(v), caller);
    }

    GLvoid Functions_1_0::glVertex4f(
        GLfloat x, GLfloat y, GLfloat z, GLfloat w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4f(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glVertex4fv(const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4fv(v), caller);
    }

    GLvoid Functions_1_0::glVertex4i(GLint x, GLint y, GLint z, GLint w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4i(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glVertex4iv(const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4iv(v), caller);
    }

    GLvoid Functions_1_0::glVertex4s(
        GLshort x, GLshort y, GLshort z, GLshort w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4s(x, y, z, w), caller);
    }

    GLvoid Functions_1_0::glVertex4sv(const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glVertex4sv(v), caller);
    }

    GLvoid Functions_1_0::glViewport(
        GLint x, GLint y, GLsizei width, GLsizei height, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(::glViewport(x, y, width, height), caller);
    }
} // namespace nfx::graphics::gl
