#include "nfx/graphics/gl/core/functions/Functions_1_5.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_1_5::Functions_1_5()
        : Functions_1_4{}
    {}

    Functions_1_5::~Functions_1_5() {}

    GLvoid Functions_1_5::glBeginQuery(GLenum target, GLuint id, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBeginQuery(target, id), caller);
    }

    GLvoid Functions_1_5::glBindBuffer(GLenum target, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindBuffer(target, buffer), caller);
    }

    GLvoid Functions_1_5::glBufferData(
        GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBufferData(target, size, data, usage), caller);
    }

    GLvoid Functions_1_5::glBufferSubData(
        GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBufferSubData(target, offset, size, data), caller);
    }

    GLvoid Functions_1_5::glDeleteBuffers(GLsizei n, const GLuint* buffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteBuffers(n, buffers), caller);
    }

    GLvoid Functions_1_5::glDeleteQueries(GLsizei n, const GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteQueries(n, ids), caller);
    }

    GLvoid Functions_1_5::glEndQuery(GLenum target, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEndQuery(target), caller);
    }

    GLvoid Functions_1_5::glGenBuffers(GLsizei n, GLuint* buffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenBuffers(n, buffers), caller);
    }

    GLvoid Functions_1_5::glGenQueries(GLsizei n, GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenQueries(n, ids), caller);
    }

    GLvoid Functions_1_5::glGetBufferParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetBufferParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_1_5::glGetBufferPointerv(
        GLenum target, GLenum pname, GLvoid** params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetBufferPointerv(target, pname, params), caller);
    }

    GLvoid Functions_1_5::glGetBufferSubData(
        GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetBufferSubData(target, offset, size, data), caller);
    }

    GLvoid Functions_1_5::glGetQueryiv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryiv(target, pname, params), caller);
    }

    GLvoid Functions_1_5::glGetQueryObjectiv(
        GLuint id, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryObjectiv(id, pname, params), caller);
    }

    GLvoid Functions_1_5::glGetQueryObjectuiv(
        GLuint id, GLenum pname, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryObjectuiv(id, pname, params), caller);
    }

    GLboolean Functions_1_5::glIsBuffer(GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsBuffer(buffer), caller);

        return ret;
    }

    GLboolean Functions_1_5::glIsQuery(GLuint id, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsQuery(id), caller);

        return ret;
    }

    GLvoid* Functions_1_5::glMapBuffer(GLenum target, GLenum access, [[maybe_unused]] const char* caller) const
    {
        GLvoid* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glMapBuffer(target, access), caller);

        return ret;
    }

    GLboolean Functions_1_5::glUnmapBuffer(GLenum target, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glUnmapBuffer(target), caller);

        return ret;
    }

    bool Functions_1_5::initialize()
    {
        Functions_1_4::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBeginQuery = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glBeginQuery"));
        _nfx_glBindBuffer = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glBindBuffer"));
        _nfx_glBufferData = reinterpret_cast<GLvoid (*)(GLenum, GLsizeiptr, const GLvoid*, GLenum)>(
            loader.loadFunctionPtr("glBufferData"));
        _nfx_glBufferSubData = reinterpret_cast<GLvoid (*)(GLenum, GLintptr, GLsizeiptr, const GLvoid*)>(
            loader.loadFunctionPtr("glBufferSubData"));
        _nfx_glDeleteBuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteBuffers"));
        _nfx_glDeleteQueries =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteQueries"));
        _nfx_glEndQuery = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glEndQuery"));
        _nfx_glGenBuffers = reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenBuffers"));
        _nfx_glGenQueries = reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenQueries"));
        _nfx_glGetBufferParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetBufferParameteriv"));
        _nfx_glGetBufferPointerv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLvoid**)>(loader.loadFunctionPtr("glGetBufferPointerv"));
        _nfx_glGetBufferSubData = reinterpret_cast<GLvoid (*)(GLenum, GLintptr, GLsizeiptr, GLvoid*)>(
            loader.loadFunctionPtr("glGetBufferSubData"));
        _nfx_glGetQueryiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetQueryiv"));
        _nfx_glGetQueryObjectiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetQueryObjectiv"));
        _nfx_glGetQueryObjectuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint*)>(loader.loadFunctionPtr("glGetQueryObjectuiv"));
        _nfx_glIsBuffer = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsBuffer"));
        _nfx_glIsQuery = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsQuery"));
        _nfx_glMapBuffer = reinterpret_cast<GLvoid* (*)(GLenum, GLenum)>(loader.loadFunctionPtr("glMapBuffer"));
        _nfx_glUnmapBuffer = reinterpret_cast<GLboolean (*)(GLenum)>(loader.loadFunctionPtr("glUnmapBuffer"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
