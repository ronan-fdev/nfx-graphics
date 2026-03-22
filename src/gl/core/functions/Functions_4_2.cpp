#include "nfx/graphics/gl/core/functions/Functions_4_2.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_2::Functions_4_2()
        : Functions_4_1{}
    {}

    Functions_4_2::~Functions_4_2() {}

    GLvoid Functions_4_2::glBindImageTexture(
        GLuint unit,
        GLuint texture,
        GLint level,
        GLboolean layered,
        GLint layer,
        GLenum access,
        GLenum format,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glBindImageTexture(unit, texture, level, layered, layer, access, format), caller);
    }

    GLvoid Functions_4_2::glDrawArraysInstancedBaseInstance(
        GLenum mode,
        GLint first,
        GLsizei count,
        GLsizei instancecount,
        GLuint baseinstanceconst,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstanceconst), caller);
    }

    GLvoid Functions_4_2::glDrawElementsInstancedBaseInstance(
        GLenum mode,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLsizei instancecount,
        GLuint baseinstance,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance), caller);
    }

    GLvoid Functions_4_2::glDrawElementsInstancedBaseVertexBaseInstance(
        GLenum mode,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLsizei instancecount,
        GLint basevertex,
        GLuint baseinstance,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawElementsInstancedBaseVertexBaseInstance(
                mode, count, type, indices, instancecount, basevertex, baseinstance),
            caller);
    }

    GLvoid Functions_4_2::glDrawTransformFeedbackInstanced(
        GLenum mode, GLuint id, GLsizei instancecount, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawTransformFeedbackInstanced(mode, id, instancecount), caller);
    }

    GLvoid Functions_4_2::glDrawTransformFeedbackStreamInstanced(
        GLenum mode, GLuint id, GLuint stream, GLsizei instancecount, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount), caller);
    }

    GLvoid Functions_4_2::glGetActiveAtomicCounterBufferiv(
        GLuint program, GLuint bufferIndex, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params), caller);
    }

    GLvoid Functions_4_2::glGetInternalformativ(
        GLenum target,
        GLenum internalformat,
        GLenum pname,
        GLsizei count,
        GLint* params,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetInternalformativ(target, internalformat, pname, count, params), caller);
    }

    GLvoid Functions_4_2::glMemoryBarrier(GLbitfield barriers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMemoryBarrier(barriers), caller);
    }

    GLvoid Functions_4_2::glTexStorage1D(
        GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexStorage1D(target, levels, internalformat, width), caller);
    }

    GLvoid Functions_4_2::glTexStorage2D(
        GLenum target,
        GLsizei levels,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexStorage2D(target, levels, internalformat, width, height), caller);
    }

    GLvoid Functions_4_2::glTexStorage3D(
        GLenum target,
        GLsizei levels,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexStorage3D(target, levels, internalformat, width, height, depth), caller);
    }

    bool Functions_4_2::initialize()
    {
        Functions_4_1::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBindImageTexture = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum)>(
            loader.loadFunctionPtr("glBindImageTexture"));
        _nfx_glDrawArraysInstancedBaseInstance = reinterpret_cast<GLvoid (*)(GLenum, GLint, GLsizei, GLsizei, GLuint)>(
            loader.loadFunctionPtr("glDrawArraysInstancedBaseInstance"));
        _nfx_glDrawElementsInstancedBaseInstance =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, const GLvoid*, GLsizei, GLuint)>(
                loader.loadFunctionPtr("glDrawElementsInstancedBaseInstance"));
        _nfx_glDrawElementsInstancedBaseVertexBaseInstance =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, const GLvoid*, GLsizei, GLint, GLuint)>(
                loader.loadFunctionPtr("glDrawElementsInstancedBaseVertexBaseInstance"));
        _nfx_glDrawTransformFeedbackInstanced = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei)>(
            loader.loadFunctionPtr("glDrawTransformFeedbackInstanced"));
        _nfx_glDrawTransformFeedbackStreamInstanced = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint, GLsizei)>(
            loader.loadFunctionPtr("glDrawTransformFeedbackStreamInstanced"));
        _nfx_glGetActiveAtomicCounterBufferiv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetActiveAtomicCounterBufferiv"));
        _nfx_glGetInternalformativ = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLsizei, GLint*)>(
            loader.loadFunctionPtr("glGetInternalformativ"));
        _nfx_glMemoryBarrier = reinterpret_cast<GLvoid (*)(GLbitfield)>(loader.loadFunctionPtr("glMemoryBarrier"));
        _nfx_glTexStorage1D =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei)>(loader.loadFunctionPtr("glTexStorage1D"));
        _nfx_glTexStorage2D = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glTexStorage2D"));
        _nfx_glTexStorage3D = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glTexStorage3D"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
