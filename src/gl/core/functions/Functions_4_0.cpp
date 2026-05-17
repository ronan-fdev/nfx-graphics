#include "nfx/graphics/gl/core/functions/Functions_4_0.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_0::Functions_4_0()
        : Functions_3_3{}
    {}

    Functions_4_0::~Functions_4_0()
    {
        s_loaded = false;
    }

    GLvoid Functions_4_0::glBeginQueryIndexed(
        GLenum target, GLuint index, GLuint id, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBeginQueryIndexed(target, index, id), caller);
    }

    GLvoid Functions_4_0::glBindTransformFeedback(GLenum target, GLuint id, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindTransformFeedback(target, id), caller);
    }

    GLvoid Functions_4_0::glBlendEquationi(GLuint buf, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendEquationi(buf, mode), caller);
    }

    GLvoid Functions_4_0::glBlendEquationSeparatei(
        GLuint buf, GLenum modeRGB, GLenum modeAlpha, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendEquationSeparatei(buf, modeRGB, modeAlpha), caller);
    }

    GLvoid Functions_4_0::glBlendFunci(GLuint buf, GLenum src, GLenum dst, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendFunci(buf, src, dst), caller);
    }

    GLvoid Functions_4_0::glBlendFuncSeparatei(
        GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha), caller);
    }

    GLvoid Functions_4_0::glDeleteTransformFeedbacks(
        GLsizei n, const GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteTransformFeedbacks(n, ids), caller);
    }

    GLvoid Functions_4_0::glDrawArraysIndirect(
        GLenum mode, const GLvoid* indirect, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawArraysIndirect(mode, indirect), caller);
    }

    GLvoid Functions_4_0::glDrawElementsIndirect(
        GLenum mode, GLenum type, const GLvoid* indirect, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawElementsIndirect(mode, type, indirect), caller);
    }

    GLvoid Functions_4_0::glDrawTransformFeedback(GLenum mode, GLuint id, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawTransformFeedback(mode, id), caller);
    }

    GLvoid Functions_4_0::glDrawTransformFeedbackStream(
        GLenum mode, GLuint id, GLuint stream, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawTransformFeedbackStream(mode, id, stream), caller);
    }

    GLvoid Functions_4_0::glEndQueryIndexed(GLenum target, GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEndQueryIndexed(target, index), caller);
    }

    GLvoid Functions_4_0::glGenTransformFeedbacks(GLsizei n, GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenTransformFeedbacks(n, ids), caller);
    }

    GLvoid Functions_4_0::glGetActiveSubroutineName(
        GLuint program,
        GLenum shadertype,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name), caller);
    }

    GLvoid Functions_4_0::glGetActiveSubroutineUniformiv(
        GLuint program,
        GLenum shadertype,
        GLuint index,
        GLenum pname,
        GLint* values,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values), caller);
    }

    GLvoid Functions_4_0::glGetActiveSubroutineUniformName(
        GLuint program,
        GLenum shadertype,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name), caller);
    }

    GLvoid Functions_4_0::glGetProgramStageiv(
        GLuint program, GLenum shadertype, GLenum pname, GLint* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramStageiv(program, shadertype, pname, values), caller);
    }

    GLvoid Functions_4_0::glGetQueryIndexediv(
        GLenum target, GLuint index, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryIndexediv(target, index, pname, params), caller);
    }

    GLuint Functions_4_0::glGetSubroutineIndex(
        GLuint program, GLenum shadertype, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetSubroutineIndex(program, shadertype, name), caller);

        return ret;
    }

    GLint Functions_4_0::glGetSubroutineUniformLocation(
        GLuint program, GLenum shadertype, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetSubroutineUniformLocation(program, shadertype, name), caller);

        return ret;
    }

    GLvoid Functions_4_0::glGetUniformdv(
        GLuint program, GLint location, GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetUniformdv(program, location, params), caller);
    }

    GLvoid Functions_4_0::glGetUniformSubroutineuiv(
        GLenum shadertype, GLint location, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetUniformSubroutineuiv(shadertype, location, params), caller);
    }

    GLboolean Functions_4_0::glIsTransformFeedback(GLuint id, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsTransformFeedback(id), caller);

        return ret;
    }

    GLvoid Functions_4_0::glMinSampleShading(GLfloat value, [[maybe_unused]] [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMinSampleShading(value), caller);
    }

    GLvoid Functions_4_0::glPatchParameterfv(
        GLenum pname, const GLfloat* values, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPatchParameterfv(pname, values), caller);
    }

    GLvoid Functions_4_0::glPatchParameteri(GLenum pname, GLint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPatchParameteri(pname, value), caller);
    }

    GLvoid Functions_4_0::glPauseTransformFeedback([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPauseTransformFeedback(), caller);
    }

    GLvoid Functions_4_0::glResumeTransformFeedback([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glResumeTransformFeedback(), caller);
    }

    GLvoid Functions_4_0::glUniform1d(GLint location, GLdouble x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1d(location, x), caller);
    }

    GLvoid Functions_4_0::glUniform1dv(
        GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1dv(location, count, value), caller);
    }

    GLvoid Functions_4_0::glUniform2d(GLint location, GLdouble x, GLdouble y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2d(location, x, y), caller);
    }

    GLvoid Functions_4_0::glUniform2dv(
        GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2dv(location, count, value), caller);
    }

    GLvoid Functions_4_0::glUniform3d(
        GLint location, GLdouble x, GLdouble y, GLdouble z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3d(location, x, y, z), caller);
    }

    GLvoid Functions_4_0::glUniform3dv(
        GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3dv(location, count, value), caller);
    }

    GLvoid Functions_4_0::glUniform4d(
        GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4d(location, x, y, z, w), caller);
    }

    GLvoid Functions_4_0::glUniform4dv(
        GLint location, GLsizei count, const GLdouble* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4dv(location, count, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix2dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix2x3dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2x3dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix2x4dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix2x4dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix3dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix3x2dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3x2dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix3x4dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix3x4dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix4dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix4x2dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4x2dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformMatrix4x3dv(
        GLint location,
        GLsizei count,
        GLboolean transpose,
        const GLdouble* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformMatrix4x3dv(location, count, transpose, value), caller);
    }

    GLvoid Functions_4_0::glUniformSubroutinesuiv(
        GLenum shadertype, GLsizei count, const GLuint* indices, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniformSubroutinesuiv(shadertype, count, indices), caller);
    }

    bool Functions_4_0::initialize()
    {
        Functions_3_3::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBeginQueryIndexed =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint)>(loader.loadFunctionPtr("glBeginQueryIndexed"));
        _nfx_glBindTransformFeedback =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glBindTransformFeedback"));
        _nfx_glBlendEquationi =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glBlendEquationi"));
        _nfx_glBlendEquationSeparatei =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum)>(loader.loadFunctionPtr("glBlendEquationSeparatei"));
        _nfx_glBlendFunci =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum)>(loader.loadFunctionPtr("glBlendFunci"));
        _nfx_glBlendFuncSeparatei = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLenum, GLenum)>(
            loader.loadFunctionPtr("glBlendFuncSeparatei"));
        _nfx_glDeleteTransformFeedbacks =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteTransformFeedbacks"));
        _nfx_glDrawArraysIndirect =
            reinterpret_cast<GLvoid (*)(GLenum, const GLvoid*)>(loader.loadFunctionPtr("glDrawArraysIndirect"));
        _nfx_glDrawElementsIndirect = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glDrawElementsIndirect"));
        _nfx_glDrawTransformFeedback =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glDrawTransformFeedback"));
        _nfx_glDrawTransformFeedbackStream = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint)>(
            loader.loadFunctionPtr("glDrawTransformFeedbackStream"));
        _nfx_glEndQueryIndexed =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glEndQueryIndexed"));
        _nfx_glGenTransformFeedbacks =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenTransformFeedbacks"));
        _nfx_glGetActiveSubroutineName =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*)>(
                loader.loadFunctionPtr("glGetActiveSubroutineName"));
        _nfx_glGetActiveSubroutineUniformiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetActiveSubroutineUniformiv"));
        _nfx_glGetActiveSubroutineUniformName =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*)>(
                loader.loadFunctionPtr("glGetActiveSubroutineUniformName"));
        _nfx_glGetProgramStageiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetProgramStageiv"));
        _nfx_glGetQueryIndexediv =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetQueryIndexediv"));
        _nfx_glGetSubroutineIndex =
            reinterpret_cast<GLuint (*)(GLuint, GLenum, const GLchar*)>(loader.loadFunctionPtr("glGetSubroutineIndex"));
        _nfx_glGetSubroutineUniformLocation = reinterpret_cast<GLint (*)(GLuint, GLenum, const GLchar*)>(
            loader.loadFunctionPtr("glGetSubroutineUniformLocation"));
        _nfx_glGetUniformdv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLdouble*)>(loader.loadFunctionPtr("glGetUniformdv"));
        _nfx_glGetUniformSubroutineuiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLuint*)>(loader.loadFunctionPtr("glGetUniformSubroutineuiv"));
        _nfx_glIsTransformFeedback =
            reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsTransformFeedback"));
        _nfx_glMinSampleShading = reinterpret_cast<GLvoid (*)(GLfloat)>(loader.loadFunctionPtr("glMinSampleShading"));
        _nfx_glPatchParameterfv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLfloat*)>(loader.loadFunctionPtr("glPatchParameterfv"));
        _nfx_glPatchParameteri =
            reinterpret_cast<GLvoid (*)(GLenum, GLint)>(loader.loadFunctionPtr("glPatchParameteri"));
        _nfx_glPauseTransformFeedback =
            reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glPauseTransformFeedback"));
        _nfx_glResumeTransformFeedback =
            reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glResumeTransformFeedback"));
        _nfx_glUniform1d = reinterpret_cast<GLvoid (*)(GLint, GLdouble)>(loader.loadFunctionPtr("glUniform1d"));
        _nfx_glUniform1dv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLdouble*)>(loader.loadFunctionPtr("glUniform1dv"));
        _nfx_glUniform2d =
            reinterpret_cast<GLvoid (*)(GLint, GLdouble, GLdouble)>(loader.loadFunctionPtr("glUniform2d"));
        _nfx_glUniform2dv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLdouble*)>(loader.loadFunctionPtr("glUniform2dv"));
        _nfx_glUniform3d =
            reinterpret_cast<GLvoid (*)(GLint, GLdouble, GLdouble, GLdouble)>(loader.loadFunctionPtr("glUniform3d"));
        _nfx_glUniform3dv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLdouble*)>(loader.loadFunctionPtr("glUniform3dv"));
        _nfx_glUniform4d = reinterpret_cast<GLvoid (*)(GLint, GLdouble, GLdouble, GLdouble, GLdouble)>(
            loader.loadFunctionPtr("glUniform4d"));
        _nfx_glUniform4dv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLdouble*)>(loader.loadFunctionPtr("glUniform4dv"));
        _nfx_glUniformMatrix2dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix2dv"));
        _nfx_glUniformMatrix2x3dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix2x3dv"));
        _nfx_glUniformMatrix2x4dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix2x4dv"));
        _nfx_glUniformMatrix3dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix3dv"));
        _nfx_glUniformMatrix3x2dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix3x2dv"));
        _nfx_glUniformMatrix3x4dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix3x4dv"));
        _nfx_glUniformMatrix4dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix4dv"));
        _nfx_glUniformMatrix4x2dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix4x2dv"));
        _nfx_glUniformMatrix4x3dv = reinterpret_cast<GLvoid (*)(GLint, GLsizei, GLboolean, const GLdouble*)>(
            loader.loadFunctionPtr("glUniformMatrix4x3dv"));
        _nfx_glUniformSubroutinesuiv = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glUniformSubroutinesuiv"));

        return s_loaded = true;
    }

    void Functions_4_0::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_3_3::teardown();
    }

    void Functions_4_0::nullifyPointers()
    {
        _nfx_glBeginQueryIndexed = nullptr;
        _nfx_glBindTransformFeedback = nullptr;
        _nfx_glBlendEquationi = nullptr;
        _nfx_glBlendEquationSeparatei = nullptr;
        _nfx_glBlendFunci = nullptr;
        _nfx_glBlendFuncSeparatei = nullptr;
        _nfx_glDeleteTransformFeedbacks = nullptr;
        _nfx_glDrawArraysIndirect = nullptr;
        _nfx_glDrawElementsIndirect = nullptr;
        _nfx_glDrawTransformFeedback = nullptr;
        _nfx_glDrawTransformFeedbackStream = nullptr;
        _nfx_glEndQueryIndexed = nullptr;
        _nfx_glGenTransformFeedbacks = nullptr;
        _nfx_glGetActiveSubroutineName = nullptr;
        _nfx_glGetActiveSubroutineUniformiv = nullptr;
        _nfx_glGetActiveSubroutineUniformName = nullptr;
        _nfx_glGetProgramStageiv = nullptr;
        _nfx_glGetQueryIndexediv = nullptr;
        _nfx_glGetSubroutineIndex = nullptr;
        _nfx_glGetSubroutineUniformLocation = nullptr;
        _nfx_glGetUniformdv = nullptr;
        _nfx_glGetUniformSubroutineuiv = nullptr;
        _nfx_glIsTransformFeedback = nullptr;
        _nfx_glMinSampleShading = nullptr;
        _nfx_glPatchParameterfv = nullptr;
        _nfx_glPatchParameteri = nullptr;
        _nfx_glPauseTransformFeedback = nullptr;
        _nfx_glResumeTransformFeedback = nullptr;
        _nfx_glUniform1d = nullptr;
        _nfx_glUniform1dv = nullptr;
        _nfx_glUniform2d = nullptr;
        _nfx_glUniform2dv = nullptr;
        _nfx_glUniform3d = nullptr;
        _nfx_glUniform3dv = nullptr;
        _nfx_glUniform4d = nullptr;
        _nfx_glUniform4dv = nullptr;
        _nfx_glUniformMatrix2dv = nullptr;
        _nfx_glUniformMatrix2x3dv = nullptr;
        _nfx_glUniformMatrix2x4dv = nullptr;
        _nfx_glUniformMatrix3dv = nullptr;
        _nfx_glUniformMatrix3x2dv = nullptr;
        _nfx_glUniformMatrix3x4dv = nullptr;
        _nfx_glUniformMatrix4dv = nullptr;
        _nfx_glUniformMatrix4x2dv = nullptr;
        _nfx_glUniformMatrix4x3dv = nullptr;
        _nfx_glUniformSubroutinesuiv = nullptr;
    }
} // namespace nfx::graphics::gl
