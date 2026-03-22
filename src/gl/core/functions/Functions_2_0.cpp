#include "nfx/graphics/gl/core/functions/Functions_2_0.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_2_0::Functions_2_0()
        : Functions_1_5{}
    {}

    Functions_2_0::~Functions_2_0() {}

    GLvoid Functions_2_0::glAttachShader(GLuint program, GLuint shader, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glAttachShader(program, shader), caller);
    }

    GLvoid Functions_2_0::glBindAttribLocation(
        GLuint program, GLuint index, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindAttribLocation(program, index, name), caller);
    }

    GLvoid Functions_2_0::glBlendEquationSeparate(
        GLenum modeRGB, GLenum modeAlpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendEquationSeparate(modeRGB, modeAlpha), caller);
    }

    GLvoid Functions_2_0::glCompileShader(GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCompileShader(program), caller);
    }

    GLuint Functions_2_0::glCreateProgram([[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };
        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glCreateProgram(), caller);
        return ret;
    }

    GLuint Functions_2_0::glCreateShader(GLenum type, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };
        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glCreateShader(type), caller);
        return ret;
    }

    GLvoid Functions_2_0::glDeleteProgram(GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteProgram(program), caller);
    }

    GLvoid Functions_2_0::glDeleteShader(GLuint shader, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteShader(shader), caller);
    }

    GLvoid Functions_2_0::glDetachShader(GLuint program, GLuint shader, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDetachShader(program, shader), caller);
    }

    GLvoid Functions_2_0::glDisableVertexAttribArray(GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDisableVertexAttribArray(index), caller);
    }

    GLvoid Functions_2_0::glDrawBuffers(GLsizei n, const GLenum* bufs, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawBuffers(n, bufs), caller);
    }

    GLvoid Functions_2_0::glEnableVertexAttribArray(GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEnableVertexAttribArray(index), caller);
    }

    GLvoid Functions_2_0::glGetActiveAttrib(
        GLuint program,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLint* size,
        GLenum* type,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetActiveAttrib(program, index, bufSize, length, size, type, name), caller);
    }

    GLvoid Functions_2_0::glGetActiveUniform(
        GLuint program,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLint* size,
        GLenum* type,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetActiveUniform(program, index, bufSize, length, size, type, name), caller);
    }

    GLvoid Functions_2_0::glGetAttachedShaders(
        GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetAttachedShaders(program, maxCount, count, shaders), caller);
    }

    GLint Functions_2_0::glGetAttribLocation(
        GLuint program, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };
        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetAttribLocation(program, name), caller);
        return ret;
    }

    GLvoid Functions_2_0::glGetProgramInfoLog(
        GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramInfoLog(program, bufsize, length, infolog), caller);
    }

    GLvoid Functions_2_0::glGetProgramiv(
        GLuint program, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramiv(program, pname, params), caller);
    }

    GLvoid Functions_2_0::glGetShaderInfoLog(
        GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetShaderInfoLog(shader, bufsize, length, infolog), caller);
    }

    GLvoid Functions_2_0::glGetShaderiv(
        GLuint shader, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetShaderiv(shader, pname, params), caller);
    }

    GLvoid Functions_2_0::glGetShaderSource(
        GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetShaderSource(shader, bufSize, length, source), caller);
    }

    GLvoid Functions_2_0::glGetUniformfv(
        GLuint program, GLint location, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetUniformfv(program, location, params), caller);
    }

    GLvoid Functions_2_0::glGetUniformiv(
        GLuint program, GLint location, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetUniformiv(program, location, params), caller);
    }

    GLint Functions_2_0::glGetUniformLocation(
        GLuint program, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };
        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetUniformLocation(program, name), caller);
        return ret;
    }

    GLvoid Functions_2_0::glGetVertexAttribPointerv(
        GLuint index, GLenum pname, GLvoid** pointer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribPointerv(index, pname, pointer), caller);
    }

    GLvoid Functions_2_0::glGetVertexAttribdv(
        GLuint index, GLenum pname, GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribdv(index, pname, params), caller);
    }

    GLvoid Functions_2_0::glGetVertexAttribfv(
        GLuint index, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribfv(index, pname, params), caller);
    }

    GLvoid Functions_2_0::glGetVertexAttribiv(
        GLuint index, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribiv(index, pname, params), caller);
    }

    GLboolean Functions_2_0::glIsProgram(GLuint program, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsProgram(program), caller);

        return ret;
    }

    GLboolean Functions_2_0::glIsShader(GLuint shader, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsShader(shader), caller);

        return ret;
    }

    GLvoid Functions_2_0::glLinkProgram(GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glLinkProgram(program), caller);
    }

    GLvoid Functions_2_0::glShaderSource(
        GLuint shader,
        GLsizei count,
        const GLchar* const* string,
        const GLint* length,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glShaderSource(shader, count, string, length), caller);
    }

    GLvoid Functions_2_0::glStencilFuncSeparate(
        GLenum face, GLenum func, GLint ref, GLuint mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glStencilFuncSeparate(face, func, ref, mask), caller);
    }

    GLvoid Functions_2_0::glStencilMaskSeparate(GLenum face, GLuint mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glStencilMaskSeparate(face, mask), caller);
    }

    GLvoid Functions_2_0::glStencilOpSeparate(
        GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glStencilOpSeparate(face, sfail, dpfail, dppass), caller);
    }

    GLvoid Functions_2_0::glUniform1f(GLint location, GLfloat v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1f(location, v0), caller);
    }

    GLvoid Functions_2_0::glUniform1fv(
        GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1fv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform1i(GLint location, GLint v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1i(location, v0), caller);
    }

    GLvoid Functions_2_0::glUniform1iv(
        GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1iv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform2f(GLint location, GLfloat v0, GLfloat v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2f(location, v0, v1), caller);
    }

    GLvoid Functions_2_0::glUniform2fv(
        GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2fv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform2i(GLint location, GLint v0, GLint v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2i(location, v0, v1), caller);
    }

    GLvoid Functions_2_0::glUniform2iv(
        GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2iv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform3f(
        GLint location, GLfloat v0, GLfloat v1, GLfloat v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3f(location, v0, v1, v2), caller);
    }

    GLvoid Functions_2_0::glUniform3fv(
        GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3fv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform3i(
        GLint location, GLint v0, GLint v1, GLint v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3i(location, v0, v1, v2), caller);
    }

    GLvoid Functions_2_0::glUniform3iv(
        GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3iv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform4f(
        GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4f(location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_2_0::glUniform4fv(
        GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4fv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniform4i(
        GLint location, GLint v0, GLint v1, GLint v2, GLint v3, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4i(location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_2_0::glUniform4iv(
        GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4iv(location, count, value), caller);
    }

    GLvoid Functions_2_0::glUniformMatrix2fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_0::glUniformMatrix3fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_0::glUniformMatrix4fv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4fv(location, count, transpose, value), caller);
    }

    GLvoid Functions_2_0::glUseProgram(GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUseProgram(program), caller);
    }

    GLvoid Functions_2_0::glValidateProgram(GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glValidateProgram(program), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1d(GLuint index, GLdouble x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1d(index, x), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1dv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1f(GLuint index, GLfloat x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1f(index, x), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1fv(GLuint index, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1fv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1s(GLuint index, GLshort x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1s(index, x), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib1sv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib1sv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2d(
        GLuint index, GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2d(index, x, y), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2dv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2f(
        GLuint index, GLfloat x, GLfloat y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2f(index, x, y), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2fv(GLuint index, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2fv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2s(
        GLuint index, GLshort x, GLshort y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2s(index, x, y), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib2sv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib2sv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3d(
        GLuint index, GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3d(index, x, y, z), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3dv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3f(
        GLuint index, GLfloat x, GLfloat y, GLfloat z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3f(index, x, y, z), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3fv(GLuint index, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3fv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3s(
        GLuint index, GLshort x, GLshort y, GLshort z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3s(index, x, y, z), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib3sv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib3sv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4bv(GLuint index, const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4bv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4d(
        GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4d(index, x, y, z, w), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4dv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4f(
        GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4f(index, x, y, z, w), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4fv(GLuint index, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4fv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4iv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4iv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nbv(GLuint index, const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nbv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Niv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Niv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nsv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nsv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nub(
        GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nub(index, x, y, z, w), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nubv(GLuint index, const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nubv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nuiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nuiv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4Nusv(
        GLuint index, const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4Nusv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4s(
        GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4s(index, x, y, z, w), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4sv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4sv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4ubv(GLuint index, const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4ubv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4uiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4uiv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttrib4usv(GLuint index, const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttrib4usv(index, v), caller);
    }

    GLvoid Functions_2_0::glVertexAttribPointer(
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const GLvoid* pointer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribPointer(index, size, type, normalized, stride, pointer), caller);
    }

    bool Functions_2_0::initialize()
    {
        Functions_1_5::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glAttachShader = reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glAttachShader"));
        _nfx_glBindAttribLocation =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, const GLchar*)>(loader.loadFunctionPtr("glBindAttribLocation"));
        _nfx_glBlendEquationSeparate =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum)>(loader.loadFunctionPtr("glBlendEquationSeparate"));
        _nfx_glCompileShader = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glCompileShader"));
        _nfx_glCreateProgram = reinterpret_cast<GLuint (*)(GLvoid)>(loader.loadFunctionPtr("glCreateProgram"));
        _nfx_glCreateShader = reinterpret_cast<GLuint (*)(GLenum)>(loader.loadFunctionPtr("glCreateShader"));
        _nfx_glDeleteProgram = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glDeleteProgram"));
        _nfx_glDeleteShader = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glDeleteShader"));
        _nfx_glDetachShader = reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glDetachShader"));
        _nfx_glDisableVertexAttribArray =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glDisableVertexAttribArray"));
        _nfx_glDrawBuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLenum*)>(loader.loadFunctionPtr("glDrawBuffers"));
        _nfx_glEnableVertexAttribArray =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glEnableVertexAttribArray"));
        _nfx_glGetActiveAttrib =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*)>(
                loader.loadFunctionPtr("glGetActiveAttrib"));
        _nfx_glGetActiveUniform =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*)>(
                loader.loadFunctionPtr("glGetActiveUniform"));
        _nfx_glGetAttachedShaders = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLuint*)>(
            loader.loadFunctionPtr("glGetAttachedShaders"));
        _nfx_glGetAttribLocation =
            reinterpret_cast<GLint (*)(GLuint, const GLchar*)>(loader.loadFunctionPtr("glGetAttribLocation"));
        _nfx_glGetProgramInfoLog = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetProgramInfoLog"));
        _nfx_glGetProgramiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetProgramiv"));
        _nfx_glGetShaderInfoLog = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetShaderInfoLog"));
        _nfx_glGetShaderiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum pname, GLint*)>(loader.loadFunctionPtr("glGetShaderiv"));
        _nfx_glGetShaderSource = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetShaderSource"));
        _nfx_glGetUniformfv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLfloat*)>(loader.loadFunctionPtr("glGetUniformfv"));
        _nfx_glGetUniformiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint*)>(loader.loadFunctionPtr("glGetUniformiv"));
        _nfx_glGetUniformLocation =
            reinterpret_cast<GLint (*)(GLuint, const GLchar*)>(loader.loadFunctionPtr("glGetUniformLocation"));
        _nfx_glGetVertexAttribdv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLdouble*)>(loader.loadFunctionPtr("glGetVertexAttribdv"));
        _nfx_glGetVertexAttribfv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLfloat*)>(loader.loadFunctionPtr("glGetVertexAttribfv"));
        _nfx_glGetVertexAttribiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetVertexAttribiv"));
        _nfx_glGetVertexAttribPointerv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLvoid**)>(loader.loadFunctionPtr("glGetVertexAttribPointerv"));
        _nfx_glIsProgram = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsProgram"));
        _nfx_glIsShader = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsShader"));
        _nfx_glLinkProgram = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glLinkProgram"));
        _nfx_glShaderSource = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLchar* const*, const GLint*)>(
            loader.loadFunctionPtr("glShaderSource"));
        _nfx_glStencilFuncSeparate = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint, GLuint)>(
            loader.loadFunctionPtr("glStencilFuncSeparate"));
        _nfx_glStencilMaskSeparate =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glStencilMaskSeparate"));
        _nfx_glStencilOpSeparate =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLenum)>(loader.loadFunctionPtr("glStencilOpSeparate"));
        _nfx_glUniform1f = reinterpret_cast<GLvoid (*)(GLint, GLfloat)>(loader.loadFunctionPtr("glUniform1f"));
        _nfx_glUniform1fv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLfloat*)>(loader.loadFunctionPtr("glUniform1fv"));
        _nfx_glUniform1i = reinterpret_cast<GLvoid (*)(GLint, GLint)>(loader.loadFunctionPtr("glUniform1i"));
        _nfx_glUniform1iv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLint*)>(loader.loadFunctionPtr("glUniform1iv"));
        _nfx_glUniform2f = reinterpret_cast<GLvoid (*)(GLint, GLfloat, GLfloat)>(loader.loadFunctionPtr("glUniform2f"));
        _nfx_glUniform2fv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLfloat*)>(loader.loadFunctionPtr("glUniform2fv"));
        _nfx_glUniform2i = reinterpret_cast<GLvoid (*)(GLint, GLint, GLint)>(loader.loadFunctionPtr("glUniform2i"));
        _nfx_glUniform2iv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLint*)>(loader.loadFunctionPtr("glUniform2iv"));
        _nfx_glUniform3f =
            reinterpret_cast<GLvoid (*)(GLint, GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glUniform3f"));
        _nfx_glUniform3fv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLfloat*)>(loader.loadFunctionPtr("glUniform3fv"));
        _nfx_glUniform3i =
            reinterpret_cast<GLvoid (*)(GLint, GLint, GLint, GLint)>(loader.loadFunctionPtr("glUniform3i"));
        _nfx_glUniform3iv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLint*)>(loader.loadFunctionPtr("glUniform3iv"));
        _nfx_glUniform4f = reinterpret_cast<GLvoid (*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glUniform4f"));
        _nfx_glUniform4fv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLfloat*)>(loader.loadFunctionPtr("glUniform4fv"));
        _nfx_glUniform4i =
            reinterpret_cast<GLvoid (*)(GLint, GLint, GLint, GLint, GLint)>(loader.loadFunctionPtr("glUniform4i"));
        _nfx_glUniform4iv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLint*)>(loader.loadFunctionPtr("glUniform4iv"));
        _nfx_glUniformMatrix2fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix2fv"));
        _nfx_glUniformMatrix3fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix3fv"));
        _nfx_glUniformMatrix4fv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLfloat*)>(
            loader.loadFunctionPtr("glUniformMatrix4fv"));
        _nfx_glUseProgram = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glUseProgram"));
        _nfx_glValidateProgram = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glValidateProgram"));
        _nfx_glVertexAttrib1d =
            reinterpret_cast<GLvoid (*)(GLuint, GLdouble)>(loader.loadFunctionPtr("glVertexAttrib1d"));
        _nfx_glVertexAttrib1dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttrib1dv"));
        _nfx_glVertexAttrib1f =
            reinterpret_cast<GLvoid (*)(GLuint, GLfloat)>(loader.loadFunctionPtr("glVertexAttrib1f"));
        _nfx_glVertexAttrib1fv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLfloat*)>(loader.loadFunctionPtr("glVertexAttrib1fv"));
        _nfx_glVertexAttrib1s =
            reinterpret_cast<GLvoid (*)(GLuint, GLshort)>(loader.loadFunctionPtr("glVertexAttrib1s"));
        _nfx_glVertexAttrib1sv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttrib1sv"));
        _nfx_glVertexAttrib2d =
            reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble)>(loader.loadFunctionPtr("glVertexAttrib2d"));
        _nfx_glVertexAttrib2dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttrib2dv"));
        _nfx_glVertexAttrib2f =
            reinterpret_cast<GLvoid (*)(GLuint, GLfloat, GLfloat)>(loader.loadFunctionPtr("glVertexAttrib2f"));
        _nfx_glVertexAttrib2fv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLfloat*)>(loader.loadFunctionPtr("glVertexAttrib2fv"));
        _nfx_glVertexAttrib2s =
            reinterpret_cast<GLvoid (*)(GLuint, GLshort, GLshort)>(loader.loadFunctionPtr("glVertexAttrib2s"));
        _nfx_glVertexAttrib2sv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttrib2sv"));
        _nfx_glVertexAttrib3d = reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glVertexAttrib3d"));
        _nfx_glVertexAttrib3dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttrib3dv"));
        _nfx_glVertexAttrib3f =
            reinterpret_cast<GLvoid (*)(GLuint, GLfloat, GLfloat, GLfloat)>(loader.loadFunctionPtr("glVertexAttrib3f"));
        _nfx_glVertexAttrib3fv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLfloat*)>(loader.loadFunctionPtr("glVertexAttrib3fv"));
        _nfx_glVertexAttrib3s =
            reinterpret_cast<GLvoid (*)(GLuint, GLshort, GLshort, GLshort)>(loader.loadFunctionPtr("glVertexAttrib3s"));
        _nfx_glVertexAttrib3sv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttrib3sv"));
        _nfx_glVertexAttrib4bv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLbyte*)>(loader.loadFunctionPtr("glVertexAttrib4bv"));
        _nfx_glVertexAttrib4d = reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glVertexAttrib4d"));
        _nfx_glVertexAttrib4dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttrib4dv"));
        _nfx_glVertexAttrib4f = reinterpret_cast<GLvoid (*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glVertexAttrib4f"));
        _nfx_glVertexAttrib4fv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLfloat*)>(loader.loadFunctionPtr("glVertexAttrib4fv"));
        _nfx_glVertexAttrib4iv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttrib4iv"));
        _nfx_glVertexAttrib4Nbv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLbyte*)>(loader.loadFunctionPtr("glVertexAttrib4Nbv"));
        _nfx_glVertexAttrib4Niv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttrib4Niv"));
        _nfx_glVertexAttrib4Nsv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttrib4Nsv"));
        _nfx_glVertexAttrib4Nub = reinterpret_cast<GLvoid (*)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte)>(
            loader.loadFunctionPtr("glVertexAttrib4Nub"));
        _nfx_glVertexAttrib4Nubv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLubyte*)>(loader.loadFunctionPtr("glVertexAttrib4Nubv"));
        _nfx_glVertexAttrib4Nuiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttrib4Nuiv"));
        _nfx_glVertexAttrib4Nusv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLushort*)>(loader.loadFunctionPtr("glVertexAttrib4Nusv"));
        _nfx_glVertexAttrib4s = reinterpret_cast<GLvoid (*)(GLuint, GLshort, GLshort, GLshort, GLshort)>(
            loader.loadFunctionPtr("glVertexAttrib4s"));
        _nfx_glVertexAttrib4sv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttrib4sv"));
        _nfx_glVertexAttrib4ubv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLubyte*)>(loader.loadFunctionPtr("glVertexAttrib4ubv"));
        _nfx_glVertexAttrib4uiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttrib4uiv"));
        _nfx_glVertexAttrib4usv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLushort*)>(loader.loadFunctionPtr("glVertexAttrib4usv"));
        _nfx_glVertexAttribPointer =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glVertexAttribPointer"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
