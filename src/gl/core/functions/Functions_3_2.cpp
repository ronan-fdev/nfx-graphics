#include "nfx/graphics/gl/core/functions/Functions_3_2.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_3_2::Functions_3_2()
        : Functions_3_1{}
    {}

    Functions_3_2::~Functions_3_2()
    {
        s_loaded = false;
    }

    GLenum Functions_3_2::glClientWaitSync(
        GLsync sync, GLbitfield flags, GLuint64 timeout, [[maybe_unused]] const char* caller) const
    {
        GLenum ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glClientWaitSync(sync, flags, timeout), caller);

        return ret;
    }

    GLvoid Functions_3_2::glDeleteSync(GLsync sync, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteSync(sync), caller);
    }

    GLvoid Functions_3_2::glDrawElementsBaseVertex(
        GLenum mode,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLint basevertex,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDrawElementsBaseVertex(mode, count, type, indices, basevertex), caller);
    }

    GLvoid Functions_3_2::glDrawElementsInstancedBaseVertex(
        GLenum mode,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLsizei instancecount,
        GLint basevertex,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex), caller);
    }

    GLvoid Functions_3_2::glDrawRangeElementsBaseVertex(
        GLenum mode,
        GLuint start,
        GLuint end,
        GLsizei count,
        GLenum type,
        const GLvoid* indices,
        GLint basevertex,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex), caller);
    }

    GLsync Functions_3_2::glFenceSync(GLenum condition, GLbitfield flags, [[maybe_unused]] const char* caller) const
    {
        GLsync ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glFenceSync(condition, flags), caller);

        return ret;
    }

    GLint Functions_3_2::glGetFragDataIndex(
        GLuint program, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetFragDataIndex(program, name), caller);

        return ret;
    }

    GLvoid Functions_3_2::glFramebufferTexture(
        GLenum target, GLenum attachment, GLuint texture, GLint level, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFramebufferTexture(target, attachment, texture, level), caller);
    }

    GLvoid Functions_3_2::glGetBufferParameteri64v(
        GLenum target, GLenum pname, GLint64* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetBufferParameteri64v(target, pname, params), caller);
    }

    GLvoid Functions_3_2::glGetInteger64i_v(
        GLenum target, GLuint index, GLint64* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetInteger64i_v(target, index, data), caller);
    }

    GLvoid Functions_3_2::glGetInteger64v(GLenum pname, GLint64* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetInteger64v(pname, data), caller);
    }

    GLvoid Functions_3_2::glGetMultisamplefv(
        GLenum pname, GLuint index, GLfloat* val, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetMultisamplefv(pname, index, val), caller);
    }

    GLvoid Functions_3_2::glGetSynciv(
        GLsync sync, GLenum pname, GLsizei count, GLsizei* length, GLint* values, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSynciv(sync, pname, count, length, values), caller);
    }

    GLboolean Functions_3_2::glIsSync(GLsync sync, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsSync(sync), caller);

        return ret;
    }

    GLvoid Functions_3_2::glMultiDrawElementsBaseVertex(
        GLenum mode,
        const GLsizei* count,
        GLenum type,
        const GLvoid* const* indices,
        GLsizei drawcount,
        const GLint* basevertex,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex), caller);
    }

    GLvoid Functions_3_2::glProvokingVertex(GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glProvokingVertex(mode), caller);
    }

    GLvoid Functions_3_2::glSampleMaski(GLuint maskNumber, GLbitfield mask, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSampleMaski(maskNumber, mask), caller);
    }

    GLvoid Functions_3_2::glTexImage2DMultisample(
        GLenum target,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLboolean fixedsamplelocations,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations), caller);
    }

    GLvoid Functions_3_2::glTexImage3DMultisample(
        GLenum target,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLboolean fixedsamplelocations,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations),
            caller);
    }

    GLvoid Functions_3_2::glWaitSync(
        GLsync sync, GLbitfield flags, GLuint64 timeout, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glWaitSync(sync, flags, timeout), caller);
    }

    bool Functions_3_2::initialize()
    {
        Functions_3_1::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glClientWaitSync =
            reinterpret_cast<GLenum (*)(GLsync, GLbitfield, GLuint64)>(loader.loadFunctionPtr("glClientWaitSync"));
        _nfx_glDeleteSync = reinterpret_cast<GLvoid (*)(GLsync)>(loader.loadFunctionPtr("glDeleteSync"));
        _nfx_glDrawElementsBaseVertex = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, const GLvoid*, GLint)>(
            loader.loadFunctionPtr("glDrawElementsBaseVertex"));
        _nfx_glDrawElementsInstancedBaseVertex =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, const GLvoid*, GLsizei, GLint)>(
                loader.loadFunctionPtr("glDrawElementsInstancedBaseVertex"));
        _nfx_glDrawRangeElementsBaseVertex =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid*, GLint)>(
                loader.loadFunctionPtr("glDrawRangeElementsBaseVertex"));
        _nfx_glFenceSync = reinterpret_cast<GLsync (*)(GLenum, GLbitfield)>(loader.loadFunctionPtr("glFenceSync"));
        _nfx_glFramebufferTexture =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint, GLint)>(loader.loadFunctionPtr("glFramebufferTexture"));
        _nfx_glGetBufferParameteri64v =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint64*)>(loader.loadFunctionPtr("glGetBufferParameteri64v"));
        _nfx_glGetFragDataIndex =
            reinterpret_cast<GLint (*)(GLuint, const GLchar*)>(loader.loadFunctionPtr("glGetFragDataIndex"));
        _nfx_glGetInteger64i_v =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLint64*)>(loader.loadFunctionPtr("glGetInteger64i_v"));
        _nfx_glGetInteger64v =
            reinterpret_cast<GLvoid (*)(GLenum, GLint64*)>(loader.loadFunctionPtr("glGetInteger64v"));
        _nfx_glGetMultisamplefv =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLfloat*)>(loader.loadFunctionPtr("glGetMultisamplefv"));
        _nfx_glGetSynciv = reinterpret_cast<GLvoid (*)(GLsync, GLenum, GLsizei, GLsizei*, GLint*)>(
            loader.loadFunctionPtr("glGetSynciv"));
        _nfx_glIsSync = reinterpret_cast<GLboolean (*)(GLsync)>(loader.loadFunctionPtr("glIsSync"));
        _nfx_glMultiDrawElementsBaseVertex =
            reinterpret_cast<GLvoid (*)(GLenum, const GLsizei*, GLenum, const GLvoid* const*, GLsizei, const GLint*)>(
                loader.loadFunctionPtr("glMultiDrawElementsBaseVertex"));
        _nfx_glProvokingVertex = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glProvokingVertex"));
        _nfx_glSampleMaski =
            reinterpret_cast<GLvoid (*)(GLuint maskNumber, GLbitfield)>(loader.loadFunctionPtr("glSampleMaski"));
        _nfx_glTexImage2DMultisample =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTexImage2DMultisample"));
        _nfx_glTexImage3DMultisample =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTexImage3DMultisample"));
        _nfx_glWaitSync =
            reinterpret_cast<GLvoid (*)(GLsync, GLbitfield, GLuint64)>(loader.loadFunctionPtr("glWaitSync"));

        return s_loaded = true;
    }

    void Functions_3_2::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_3_1::teardown();
    }

    void Functions_3_2::nullifyPointers()
    {
        _nfx_glClientWaitSync = nullptr;
        _nfx_glDeleteSync = nullptr;
        _nfx_glDrawElementsBaseVertex = nullptr;
        _nfx_glDrawElementsInstancedBaseVertex = nullptr;
        _nfx_glDrawRangeElementsBaseVertex = nullptr;
        _nfx_glFenceSync = nullptr;
        _nfx_glFramebufferTexture = nullptr;
        _nfx_glGetBufferParameteri64v = nullptr;
        _nfx_glGetFragDataIndex = nullptr;
        _nfx_glGetInteger64i_v = nullptr;
        _nfx_glGetInteger64v = nullptr;
        _nfx_glGetMultisamplefv = nullptr;
        _nfx_glGetSynciv = nullptr;
        _nfx_glIsSync = nullptr;
        _nfx_glMultiDrawElementsBaseVertex = nullptr;
        _nfx_glProvokingVertex = nullptr;
        _nfx_glSampleMaski = nullptr;
        _nfx_glTexImage2DMultisample = nullptr;
        _nfx_glTexImage3DMultisample = nullptr;
        _nfx_glWaitSync = nullptr;
    }
} // namespace nfx::graphics::gl
