#include "nfx/graphics/gl/core/functions/Functions_4_1.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_1::Functions_4_1()
        : Functions_4_0{}
    {}

    Functions_4_1::~Functions_4_1()
    {
        s_loaded = false;
    }

    GLvoid Functions_4_1::glActiveShaderProgram(
        GLuint pipeline, GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glActiveShaderProgram(pipeline, program), caller);
    }

    GLvoid Functions_4_1::glBindProgramPipeline(GLuint pipeline, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindProgramPipeline(pipeline), caller);
    }

    GLvoid Functions_4_1::glClearDepthf(GLfloat d, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearDepthf(d), caller);
    }

    GLuint Functions_4_1::glCreateShaderProgramv(
        GLenum type, GLsizei count, const GLchar* const* strings, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glCreateShaderProgramv(type, count, strings), caller);

        return ret;
    }

    GLvoid Functions_4_1::glDeleteProgramPipelines(
        GLsizei n, const GLuint* pipelines, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteProgramPipelines(n, pipelines), caller);
    }

    GLvoid Functions_4_1::glDepthRangeArrayv(
        GLuint first, GLsizei count, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDepthRangeArrayv(first, count, v), caller);
    }

    GLvoid Functions_4_1::glDepthRangef(GLfloat n, GLfloat f, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDepthRangef(n, f), caller);
    }

    GLvoid Functions_4_1::glDepthRangeIndexed(
        GLuint index, GLdouble n, GLdouble f, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDepthRangeIndexed(index, n, f), caller);
    }

    GLvoid Functions_4_1::glGenProgramPipelines(GLsizei n, GLuint* pipelines, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenProgramPipelines(n, pipelines), caller);
    }

    GLvoid Functions_4_1::glGetDoublei_v(
        GLenum target, GLuint index, GLdouble* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetDoublei_v(target, index, data), caller);
    }

    GLvoid Functions_4_1::glGetFloati_v(
        GLenum target, GLuint index, GLfloat* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetFloati_v(target, index, data), caller);
    }

    GLvoid Functions_4_1::glGetProgramBinary(
        GLuint program,
        GLsizei bufSize,
        GLsizei* length,
        GLenum* binaryFormat,
        GLvoid* binary,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramBinary(program, bufSize, length, binaryFormat, binary), caller);
    }

    GLvoid Functions_4_1::glGetProgramPipelineInfoLog(
        GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog), caller);
    }

    GLvoid Functions_4_1::glGetProgramPipelineiv(
        GLuint pipeline, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramPipelineiv(pipeline, pname, params), caller);
    }

    GLvoid Functions_4_1::glGetShaderPrecisionFormat(
        GLenum shadertype,
        GLenum precisiontype,
        GLint* range,
        GLint* precision,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision), caller);
    }

    GLvoid Functions_4_1::glGetVertexAttribLdv(
        GLuint index, GLenum pname, GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribLdv(index, pname, params), caller);
    }

    GLboolean Functions_4_1::glIsProgramPipeline(GLuint pipeline, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsProgramPipeline(pipeline), caller);

        return ret;
    }

    GLvoid Functions_4_1::glProgramBinary(
        GLuint program,
        GLenum binaryFormat,
        const GLvoid* binary,
        GLsizei length,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramBinary(program, binaryFormat, binary, length), caller);
    }

    GLvoid Functions_4_1::glProgramParameteri(
        GLuint program, GLenum pname, GLint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramParameteri(program, pname, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1d(
        GLuint program, GLint location, GLdouble v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1d(program, location, v0), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1dv(
        GLuint program, GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1dv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1f(
        GLuint program, GLint location, GLfloat v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1f(program, location, v0), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1fv(
        GLuint program, GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1fv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1i(
        GLuint program, GLint location, GLint v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1i(program, location, v0), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1iv(
        GLuint program, GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1iv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1ui(
        GLuint program, GLint location, GLuint v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1ui(program, location, v0), caller);
    }

    GLvoid Functions_4_1::glProgramUniform1uiv(
        GLuint program, GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform1uiv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2d(
        GLuint program, GLint location, GLdouble v0, GLdouble v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2d(program, location, v0, v1), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2dv(
        GLuint program, GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2dv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2f(
        GLuint program, GLint location, GLfloat v0, GLfloat v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2f(program, location, v0, v1), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2fv(
        GLuint program, GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2fv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2i(
        GLuint program, GLint location, GLint v0, GLint v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2i(program, location, v0, v1), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2iv(
        GLuint program, GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2iv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2ui(
        GLuint program, GLint location, GLuint v0, GLuint v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2ui(program, location, v0, v1), caller);
    }

    GLvoid Functions_4_1::glProgramUniform2uiv(
        GLuint program, GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform2uiv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3d(
        GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3d(program, location, v0, v1, v2), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3dv(
        GLuint program, GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3dv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3f(
        GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3f(program, location, v0, v1, v2), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3fv(
        GLuint program, GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3fv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3i(
        GLuint program, GLint location, GLint v0, GLint v1, GLint v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3i(program, location, v0, v1, v2), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3iv(
        GLuint program, GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3iv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3ui(
        GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3ui(program, location, v0, v1, v2), caller);
    }

    GLvoid Functions_4_1::glProgramUniform3uiv(
        GLuint program, GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform3uiv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4d(
        GLuint program,
        GLint location,
        GLdouble v0,
        GLdouble v1,
        GLdouble v2,
        GLdouble v3,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4d(program, location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4dv(
        GLuint program, GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4dv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4f(
        GLuint program,
        GLint location,
        GLfloat v0,
        GLfloat v1,
        GLfloat v2,
        GLfloat v3,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4f(program, location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4fv(
        GLuint program, GLint location, GLsizei count, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4fv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4i(
        GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4i(program, location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4iv(
        GLuint program, GLint location, GLsizei count, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4iv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4ui(
        GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4ui(program, location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_4_1::glProgramUniform4uiv(
        GLuint program, GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniform4uiv(program, location, count, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix2dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix2fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2x3dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix2x3dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2x3fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix2x3fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2x4dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix2x4dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix2x4fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix2x4fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix3dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix3fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3x2dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix3x2dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3x2fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix3x2fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3x4dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix3x4dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix3x4fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix3x4fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix4dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProgramUniformMatrix4fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4x2dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix4x2dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4x2fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix4x2fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4x3dv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix4x3dv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glProgramUniformMatrix4x3fv(
        GLuint program,
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glProgramUniformMatrix4x3fv(program, location, count, transpose, value), caller);
    }

    GLvoid Functions_4_1::glReleaseShaderCompiler([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glReleaseShaderCompiler(), caller);
    }

    GLvoid Functions_4_1::glScissorArrayv(
        GLuint first, GLsizei count, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glScissorArrayv(first, count, v), caller);
    }

    GLvoid Functions_4_1::glScissorIndexed(
        GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glScissorIndexed(index, left, bottom, width, height), caller);
    }

    GLvoid Functions_4_1::glScissorIndexedv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glScissorIndexedv(index, v), caller);
    }

    GLvoid Functions_4_1::glShaderBinary(
        GLsizei count,
        const GLuint* shaders,
        GLenum binaryFormat,
        const GLvoid* binary,
        GLsizei length,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glShaderBinary(count, shaders, binaryFormat, binary, length), caller);
    }

    GLvoid Functions_4_1::glUseProgramStages(
        GLuint pipeline, GLbitfield stages, GLuint program, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUseProgramStages(pipeline, stages, program), caller);
    }

    GLvoid Functions_4_1::glValidateProgramPipeline(GLuint pipeline, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glValidateProgramPipeline(pipeline), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL1d(GLuint index, GLdouble x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL1d(index, x), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL1dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL1dv(index, v), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL2d(
        GLuint index, GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL2d(index, x, y), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL2dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL2dv(index, v), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL3d(
        GLuint index, GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL3d(index, x, y, z), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL3dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL3dv(index, v), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL4d(
        GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL4d(index, x, y, z, w), caller);
    }

    GLvoid Functions_4_1::glVertexAttribL4dv(GLuint index, const GLdouble* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribL4dv(index, v), caller);
    }

    GLvoid Functions_4_1::glVertexAttribLPointer(
        GLuint index,
        GLint size,
        GLenum type,
        GLsizei stride,
        const GLvoid* pointer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribLPointer(index, size, type, stride, pointer), caller);
    }

    GLvoid Functions_4_1::glViewportArrayv(
        GLuint first, GLsizei count, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glViewportArrayv(first, count, v), caller);
    }

    GLvoid Functions_4_1::glViewportIndexedf(
        GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glViewportIndexedf(index, x, y, w, h), caller);
    }

    GLvoid Functions_4_1::glViewportIndexedfv(GLuint index, const GLfloat* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glViewportIndexedfv(index, v), caller);
    }

    bool Functions_4_1::initialize()
    {
        Functions_4_0::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glActiveShaderProgram =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glActiveShaderProgram"));
        _nfx_glBindProgramPipeline =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glBindProgramPipeline"));
        _nfx_glClearDepthf = reinterpret_cast<GLvoid (*)(GLfloat)>(loader.loadFunctionPtr("glClearDepthf"));
        _nfx_glCreateShaderProgramv = reinterpret_cast<GLuint (*)(GLenum, GLsizei, const GLchar* const*)>(
            loader.loadFunctionPtr("glCreateShaderProgramv"));
        _nfx_glDeleteProgramPipelines =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteProgramPipelines"));
        _nfx_glDepthRangeArrayv = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, const GLdouble*)>(
            loader.loadFunctionPtr("glDepthRangeArrayv"));
        _nfx_glDepthRangef = reinterpret_cast<GLvoid (*)(GLfloat, GLfloat)>(loader.loadFunctionPtr("glDepthRangef"));
        _nfx_glDepthRangeIndexed =
            reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble)>(loader.loadFunctionPtr("glDepthRangeIndexed"));
        _nfx_glGenProgramPipelines =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenProgramPipelines"));
        _nfx_glGetDoublei_v =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLdouble*)>(loader.loadFunctionPtr("glGetDoublei_v"));
        _nfx_glGetFloati_v =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLfloat*)>(loader.loadFunctionPtr("glGetFloati_v"));
        _nfx_glGetProgramBinary = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLenum*, GLvoid*)>(
            loader.loadFunctionPtr("glGetProgramBinary"));
        _nfx_glGetProgramPipelineInfoLog = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetProgramPipelineInfoLog"));
        _nfx_glGetProgramPipelineiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetProgramPipelineiv"));
        _nfx_glGetShaderPrecisionFormat = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*, GLint*)>(
            loader.loadFunctionPtr("glGetShaderPrecisionFormat"));
        _nfx_glGetVertexAttribLdv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLdouble*)>(loader.loadFunctionPtr("glGetVertexAttribLdv"));
        _nfx_glIsProgramPipeline =
            reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsProgramPipeline"));
        _nfx_glProgramBinary = reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLvoid*, GLsizei)>(
            loader.loadFunctionPtr("glProgramBinary"));
        _nfx_glProgramParameteri =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint)>(loader.loadFunctionPtr("glProgramParameteri"));
        _nfx_glProgramUniform1d =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLdouble)>(loader.loadFunctionPtr("glProgramUniform1d"));
        _nfx_glProgramUniform1dv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLdouble*)>(
            loader.loadFunctionPtr("glProgramUniform1dv"));
        _nfx_glProgramUniform1f =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLfloat)>(loader.loadFunctionPtr("glProgramUniform1f"));
        _nfx_glProgramUniform1fv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLfloat*)>(
            loader.loadFunctionPtr("glProgramUniform1fv"));
        _nfx_glProgramUniform1i =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint)>(loader.loadFunctionPtr("glProgramUniform1i"));
        _nfx_glProgramUniform1iv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLint*)>(
            loader.loadFunctionPtr("glProgramUniform1iv"));
        _nfx_glProgramUniform1ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLuint)>(loader.loadFunctionPtr("glProgramUniform1ui"));
        _nfx_glProgramUniform1uiv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glProgramUniform1uiv"));
        _nfx_glProgramUniform2d = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glProgramUniform2d"));
        _nfx_glProgramUniform2dv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLdouble*)>(
            loader.loadFunctionPtr("glProgramUniform2dv"));
        _nfx_glProgramUniform2f =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLfloat, GLfloat)>(loader.loadFunctionPtr("glProgramUniform2f"));
        _nfx_glProgramUniform2fv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLfloat*)>(
            loader.loadFunctionPtr("glProgramUniform2fv"));
        _nfx_glProgramUniform2i =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint)>(loader.loadFunctionPtr("glProgramUniform2i"));
        _nfx_glProgramUniform2iv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLint*)>(
            loader.loadFunctionPtr("glProgramUniform2iv"));
        _nfx_glProgramUniform2ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLuint, GLuint)>(loader.loadFunctionPtr("glProgramUniform2ui"));
        _nfx_glProgramUniform2uiv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glProgramUniform2uiv"));
        _nfx_glProgramUniform3d = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glProgramUniform3d"));
        _nfx_glProgramUniform3dv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLdouble*)>(
            loader.loadFunctionPtr("glProgramUniform3dv"));
        _nfx_glProgramUniform3f = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glProgramUniform3f"));
        _nfx_glProgramUniform3fv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLfloat*)>(
            loader.loadFunctionPtr("glProgramUniform3fv"));
        _nfx_glProgramUniform3i = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint)>(
            loader.loadFunctionPtr("glProgramUniform3i"));
        _nfx_glProgramUniform3iv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLint*)>(
            loader.loadFunctionPtr("glProgramUniform3iv"));
        _nfx_glProgramUniform3ui = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLuint, GLuint, GLuint)>(
            loader.loadFunctionPtr("glProgramUniform3ui"));
        _nfx_glProgramUniform3uiv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glProgramUniform3uiv"));
        _nfx_glProgramUniform4d = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glProgramUniform4d"));
        _nfx_glProgramUniform4dv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLdouble*)>(
            loader.loadFunctionPtr("glProgramUniform4dv"));
        _nfx_glProgramUniform4f = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glProgramUniform4f"));
        _nfx_glProgramUniform4fv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLfloat*)>(
            loader.loadFunctionPtr("glProgramUniform4fv"));
        _nfx_glProgramUniform4i = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint, GLint)>(
            loader.loadFunctionPtr("glProgramUniform4i"));
        _nfx_glProgramUniform4iv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLint*)>(
            loader.loadFunctionPtr("glProgramUniform4iv"));
        _nfx_glProgramUniform4ui = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint)>(
            loader.loadFunctionPtr("glProgramUniform4ui"));
        _nfx_glProgramUniform4uiv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glProgramUniform4uiv"));
        _nfx_glProgramUniformMatrix2dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2dv"));
        _nfx_glProgramUniformMatrix2fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2fv"));
        _nfx_glProgramUniformMatrix2x3dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2x3dv"));
        _nfx_glProgramUniformMatrix2x3fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2x3fv"));
        _nfx_glProgramUniformMatrix2x4dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2x4dv"));
        _nfx_glProgramUniformMatrix2x4fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix2x4fv"));
        _nfx_glProgramUniformMatrix3dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3dv"));
        _nfx_glProgramUniformMatrix3fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3fv"));
        _nfx_glProgramUniformMatrix3x2dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3x2dv"));
        _nfx_glProgramUniformMatrix3x2fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3x2fv"));
        _nfx_glProgramUniformMatrix3x4dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3x4dv"));
        _nfx_glProgramUniformMatrix3x4fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix3x4fv"));
        _nfx_glProgramUniformMatrix4dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4dv"));
        _nfx_glProgramUniformMatrix4fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4fv"));
        _nfx_glProgramUniformMatrix4x2dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4x2dv"));
        _nfx_glProgramUniformMatrix4x2fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4x2fv"));
        _nfx_glProgramUniformMatrix4x3dv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4x3dv"));
        _nfx_glProgramUniformMatrix4x3fv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat*)>(
                loader.loadFunctionPtr("glProgramUniformMatrix4x3fv"));
        _nfx_glReleaseShaderCompiler =
            reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glReleaseShaderCompiler"));
        _nfx_glScissorArrayv =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLint*)>(loader.loadFunctionPtr("glScissorArrayv"));
        _nfx_glScissorIndexed = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glScissorIndexed"));
        _nfx_glScissorIndexedv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glScissorIndexedv"));
        _nfx_glShaderBinary = reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*, GLenum, const GLvoid*, GLsizei)>(
            loader.loadFunctionPtr("glShaderBinary"));
        _nfx_glUseProgramStages =
            reinterpret_cast<GLvoid (*)(GLuint, GLbitfield, GLuint)>(loader.loadFunctionPtr("glUseProgramStages"));
        _nfx_glValidateProgramPipeline =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glValidateProgramPipeline"));
        _nfx_glVertexAttribL1d =
            reinterpret_cast<GLvoid (*)(GLuint, GLdouble)>(loader.loadFunctionPtr("glVertexAttribL1d"));
        _nfx_glVertexAttribL1dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttribL1dv"));
        _nfx_glVertexAttribL2d =
            reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble)>(loader.loadFunctionPtr("glVertexAttribL2d"));
        _nfx_glVertexAttribL2dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttribL2dv"));
        _nfx_glVertexAttribL3d = reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glVertexAttribL3d"));
        _nfx_glVertexAttribL3dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttribL3dv"));
        _nfx_glVertexAttribL4d = reinterpret_cast<GLvoid (*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glVertexAttribL4d"));
        _nfx_glVertexAttribL4dv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLdouble*)>(loader.loadFunctionPtr("glVertexAttribL4dv"));
        _nfx_glVertexAttribLPointer = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glVertexAttribLPointer"));
        _nfx_glViewportArrayv =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLfloat*)>(loader.loadFunctionPtr("glViewportArrayv"));
        _nfx_glViewportIndexedf = reinterpret_cast<GLvoid (*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)>(
            loader.loadFunctionPtr("glViewportIndexedf"));
        _nfx_glViewportIndexedfv =
            reinterpret_cast<GLvoid (*)(GLuint index, const GLfloat*)>(loader.loadFunctionPtr("glViewportIndexedfv"));

        return s_loaded = true;
    }

    void Functions_4_1::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_4_0::teardown();
    }

    void Functions_4_1::nullifyPointers()
    {
        _nfx_glActiveShaderProgram = nullptr;
        _nfx_glBindProgramPipeline = nullptr;
        _nfx_glClearDepthf = nullptr;
        _nfx_glCreateShaderProgramv = nullptr;
        _nfx_glDeleteProgramPipelines = nullptr;
        _nfx_glDepthRangeArrayv = nullptr;
        _nfx_glDepthRangef = nullptr;
        _nfx_glDepthRangeIndexed = nullptr;
        _nfx_glGenProgramPipelines = nullptr;
        _nfx_glGetDoublei_v = nullptr;
        _nfx_glGetFloati_v = nullptr;
        _nfx_glGetProgramBinary = nullptr;
        _nfx_glGetProgramPipelineInfoLog = nullptr;
        _nfx_glGetProgramPipelineiv = nullptr;
        _nfx_glGetShaderPrecisionFormat = nullptr;
        _nfx_glGetVertexAttribLdv = nullptr;
        _nfx_glIsProgramPipeline = nullptr;
        _nfx_glProgramBinary = nullptr;
        _nfx_glProgramParameteri = nullptr;
        _nfx_glProgramUniform1d = nullptr;
        _nfx_glProgramUniform1dv = nullptr;
        _nfx_glProgramUniform1f = nullptr;
        _nfx_glProgramUniform1fv = nullptr;
        _nfx_glProgramUniform1i = nullptr;
        _nfx_glProgramUniform1iv = nullptr;
        _nfx_glProgramUniform1ui = nullptr;
        _nfx_glProgramUniform1uiv = nullptr;
        _nfx_glProgramUniform2d = nullptr;
        _nfx_glProgramUniform2dv = nullptr;
        _nfx_glProgramUniform2f = nullptr;
        _nfx_glProgramUniform2fv = nullptr;
        _nfx_glProgramUniform2i = nullptr;
        _nfx_glProgramUniform2iv = nullptr;
        _nfx_glProgramUniform2ui = nullptr;
        _nfx_glProgramUniform2uiv = nullptr;
        _nfx_glProgramUniform3d = nullptr;
        _nfx_glProgramUniform3dv = nullptr;
        _nfx_glProgramUniform3f = nullptr;
        _nfx_glProgramUniform3fv = nullptr;
        _nfx_glProgramUniform3i = nullptr;
        _nfx_glProgramUniform3iv = nullptr;
        _nfx_glProgramUniform3ui = nullptr;
        _nfx_glProgramUniform3uiv = nullptr;
        _nfx_glProgramUniform4d = nullptr;
        _nfx_glProgramUniform4dv = nullptr;
        _nfx_glProgramUniform4f = nullptr;
        _nfx_glProgramUniform4fv = nullptr;
        _nfx_glProgramUniform4i = nullptr;
        _nfx_glProgramUniform4iv = nullptr;
        _nfx_glProgramUniform4ui = nullptr;
        _nfx_glProgramUniform4uiv = nullptr;
        _nfx_glProgramUniformMatrix2dv = nullptr;
        _nfx_glProgramUniformMatrix2fv = nullptr;
        _nfx_glProgramUniformMatrix2x3dv = nullptr;
        _nfx_glProgramUniformMatrix2x3fv = nullptr;
        _nfx_glProgramUniformMatrix2x4dv = nullptr;
        _nfx_glProgramUniformMatrix2x4fv = nullptr;
        _nfx_glProgramUniformMatrix3dv = nullptr;
        _nfx_glProgramUniformMatrix3fv = nullptr;
        _nfx_glProgramUniformMatrix3x2dv = nullptr;
        _nfx_glProgramUniformMatrix3x2fv = nullptr;
        _nfx_glProgramUniformMatrix3x4dv = nullptr;
        _nfx_glProgramUniformMatrix3x4fv = nullptr;
        _nfx_glProgramUniformMatrix4dv = nullptr;
        _nfx_glProgramUniformMatrix4fv = nullptr;
        _nfx_glProgramUniformMatrix4x2dv = nullptr;
        _nfx_glProgramUniformMatrix4x2fv = nullptr;
        _nfx_glProgramUniformMatrix4x3dv = nullptr;
        _nfx_glProgramUniformMatrix4x3fv = nullptr;
        _nfx_glReleaseShaderCompiler = nullptr;
        _nfx_glScissorArrayv = nullptr;
        _nfx_glScissorIndexed = nullptr;
        _nfx_glScissorIndexedv = nullptr;
        _nfx_glShaderBinary = nullptr;
        _nfx_glUseProgramStages = nullptr;
        _nfx_glValidateProgramPipeline = nullptr;
        _nfx_glVertexAttribL1d = nullptr;
        _nfx_glVertexAttribL1dv = nullptr;
        _nfx_glVertexAttribL2d = nullptr;
        _nfx_glVertexAttribL2dv = nullptr;
        _nfx_glVertexAttribL3d = nullptr;
        _nfx_glVertexAttribL3dv = nullptr;
        _nfx_glVertexAttribL4d = nullptr;
        _nfx_glVertexAttribL4dv = nullptr;
        _nfx_glVertexAttribLPointer = nullptr;
        _nfx_glViewportArrayv = nullptr;
        _nfx_glViewportIndexedf = nullptr;
        _nfx_glViewportIndexedfv = nullptr;
    }
} // namespace nfx::graphics::gl
