#include "nfx/graphics/gl/core/functions/Functions_4_4.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_4::Functions_4_4()
        : Functions_4_3{}
    {}

    Functions_4_4::~Functions_4_4()
    {
        s_loaded = false;
    }

    GLvoid Functions_4_4::glBindBuffersBase(
        GLenum target, GLuint first, GLsizei count, const GLuint* buffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindBuffersBase(target, first, count, buffers), caller);
    }

    GLvoid Functions_4_4::glBindBuffersRange(
        GLenum target,
        GLuint first,
        GLsizei count,
        const GLuint* buffers,
        const GLintptr* offsets,
        const GLsizeiptr* sizes,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindBuffersRange(target, first, count, buffers, offsets, sizes), caller);
    }

    GLvoid Functions_4_4::glBindImageTextures(
        GLuint first, GLsizei count, const GLuint* textures, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindImageTextures(first, count, textures), caller);
    }

    GLvoid Functions_4_4::glBindSamplers(
        GLuint first, GLsizei count, const GLuint* samplers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindSamplers(first, count, samplers), caller);
    }

    GLvoid Functions_4_4::glBindTextures(
        GLuint first, GLsizei count, const GLuint* textures, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindTextures(first, count, textures), caller);
    }

    GLvoid Functions_4_4::glBindVertexBuffers(
        GLuint first,
        GLsizei count,
        const GLuint* buffers,
        const GLintptr* offsets,
        const GLsizei* strides,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindVertexBuffers(first, count, buffers, offsets, strides), caller);
    }

    GLvoid Functions_4_4::glBufferStorage(
        GLenum target, GLsizeiptr size, const GLvoid* data, GLbitfield flags, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBufferStorage(target, size, data, flags), caller);
    }

    GLvoid Functions_4_4::glClearTexImage(
        GLuint texture,
        GLint level,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearTexImage(texture, level, format, type, data), caller);
    }

    GLvoid Functions_4_4::glClearTexSubImage(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glClearTexSubImage(
                texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data),
            caller);
    }

    bool Functions_4_4::initialize()
    {
        Functions_4_3::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBindBuffersBase = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei, const GLuint*)>(
            loader.loadFunctionPtr("glBindBuffersBase"));
        _nfx_glBindBuffersRange =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei, const GLuint*, const GLintptr*, const GLsizeiptr*)>(
                loader.loadFunctionPtr("glBindBuffersRange"));
        _nfx_glBindImageTextures =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glBindImageTextures"));
        _nfx_glBindSamplers =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glBindSamplers"));
        _nfx_glBindTextures =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glBindTextures"));
        _nfx_glBindVertexBuffers =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLuint*, const GLintptr*, const GLsizei*)>(
                loader.loadFunctionPtr("glBindVertexBuffers"));
        _nfx_glBufferStorage = reinterpret_cast<GLvoid (*)(GLenum, GLsizeiptr, const GLvoid*, GLbitfield)>(
            loader.loadFunctionPtr("glBufferStorage"));
        _nfx_glClearTexImage = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glClearTexImage"));
        _nfx_glClearTexSubImage = reinterpret_cast<GLvoid (*)(
            GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glClearTexSubImage"));

        return s_loaded = true;
    }

    void Functions_4_4::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_4_3::teardown();
    }

    void Functions_4_4::nullifyPointers()
    {
        _nfx_glBindBuffersBase = nullptr;
        _nfx_glBindBuffersRange = nullptr;
        _nfx_glBindImageTextures = nullptr;
        _nfx_glBindSamplers = nullptr;
        _nfx_glBindTextures = nullptr;
        _nfx_glBindVertexBuffers = nullptr;
        _nfx_glBufferStorage = nullptr;
        _nfx_glClearTexImage = nullptr;
        _nfx_glClearTexSubImage = nullptr;
    }
} // namespace nfx::graphics::gl
