#include "nfx/graphics/gl/core/functions/Functions_3_1.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_3_1::Functions_3_1()
        : Functions_3_0{}
    {}

    Functions_3_1::~Functions_3_1() {}

    GLvoid Functions_3_1::glCopyBufferSubData(
        GLenum readTarget,
        GLenum writeTarget,
        GLintptr readOffset,
        GLintptr writeOffset,
        GLsizeiptr size,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size), caller);
    }

    GLvoid Functions_3_1::glDrawArraysInstanced(
        GLenum mode, GLint first, GLsizei count, GLsizei instancecount, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawArraysInstanced(mode, first, count, instancecount), caller);
    }

    GLvoid Functions_3_1::glDrawElementsInstanced(
        GLenum mode,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLsizei instancecount,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawElementsInstanced(mode, count, type, indices, instancecount), caller);
    }

    GLvoid Functions_3_1::glGetActiveUniformBlockiv(
        GLuint program,
        GLuint uniformBlockIndex,
        GLenum pname,
        GLint* params,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params), caller);
    }

    GLvoid Functions_3_1::glGetActiveUniformBlockName(
        GLuint program,
        GLuint uniformBlockIndex,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* uniformBlockName,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName), caller);
    }

    GLvoid Functions_3_1::glGetActiveUniformName(
        GLuint program,
        GLuint uniformIndex,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* uniformName,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName), caller);
    }

    GLvoid Functions_3_1::glGetActiveUniformsiv(
        GLuint program,
        GLsizei uniformCount,
        const GLuint* uniformIndices,
        GLenum pname,
        GLint* params,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params), caller);
    }

    GLuint Functions_3_1::glGetUniformBlockIndex(
        GLuint program, const GLchar* uniformBlockName, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetUniformBlockIndex(program, uniformBlockName), caller);

        return ret;
    }

    GLvoid Functions_3_1::glGetUniformIndices(
        GLuint program,
        GLsizei uniformCount,
        const GLchar* const* uniformNames,
        GLuint* uniformIndices,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices), caller);
    }

    GLvoid Functions_3_1::glPrimitiveRestartIndex(GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPrimitiveRestartIndex(index), caller);
    }

    GLvoid Functions_3_1::glTexBuffer(
        GLenum target, GLenum internalformat, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexBuffer(target, internalformat, buffer), caller);
    }

    GLvoid Functions_3_1::glUniformBlockBinding(
        GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding), caller);
    }

    bool Functions_3_1::initialize()
    {
        Functions_3_0::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glCopyBufferSubData = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glCopyBufferSubData"));
        _nfx_glDrawArraysInstanced = reinterpret_cast<GLvoid (*)(GLenum, GLint, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glDrawArraysInstanced"));
        _nfx_glDrawElementsInstanced = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, const GLvoid*, GLsizei)>(
            loader.loadFunctionPtr("glDrawElementsInstanced"));
        _nfx_glGetActiveUniformBlockiv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetActiveUniformBlockiv"));
        _nfx_glGetActiveUniformBlockName = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetActiveUniformBlockName"));
        _nfx_glGetActiveUniformName = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetActiveUniformName"));
        _nfx_glGetActiveUniformsiv = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLuint*, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetActiveUniformsiv"));
        _nfx_glGetUniformBlockIndex =
            reinterpret_cast<GLuint (*)(GLuint, const GLchar*)>(loader.loadFunctionPtr("glGetUniformBlockIndex"));
        _nfx_glGetUniformIndices = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLchar* const*, GLuint*)>(
            loader.loadFunctionPtr("glGetUniformIndices"));
        _nfx_glPrimitiveRestartIndex =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glPrimitiveRestartIndex"));
        _nfx_glTexBuffer = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint)>(loader.loadFunctionPtr("glTexBuffer"));
        _nfx_glUniformBlockBinding =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glUniformBlockBinding"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
