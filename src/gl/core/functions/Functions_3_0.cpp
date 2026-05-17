#include "nfx/graphics/gl/core/functions/Functions_3_0.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_3_0::Functions_3_0()
        : Functions_2_1{}
    {}

    Functions_3_0::~Functions_3_0()
    {
        s_loaded = false;
    }

    GLvoid Functions_3_0::glBeginConditionalRender(GLuint id, GLenum mode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBeginConditionalRender(id, mode), caller);
    }

    GLvoid Functions_3_0::glBeginTransformFeedback(GLenum primitiveMode, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBeginTransformFeedback(primitiveMode), caller);
    }

    GLvoid Functions_3_0::glBindBufferBase(
        GLenum target, GLuint index, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindBufferBase(target, index, buffer), caller);
    }

    GLvoid Functions_3_0::glBindBufferRange(
        GLenum target,
        GLuint index,
        GLuint buffer,
        GLintptr offset,
        GLsizeiptr size,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindBufferRange(target, index, buffer, offset, size), caller);
    }

    GLvoid Functions_3_0::glBindFragDataLocation(
        GLuint program, GLuint color, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindFragDataLocation(program, color, name), caller);
    }

    GLvoid Functions_3_0::glBindFramebuffer(
        GLenum target, GLuint framebuffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindFramebuffer(target, framebuffer), caller);
    }

    GLvoid Functions_3_0::glBindRenderbuffer(
        GLenum target, GLuint renderbuffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindRenderbuffer(target, renderbuffer), caller);
    }

    GLvoid Functions_3_0::glBindVertexArray(GLuint array, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindVertexArray(array), caller);
    }

    GLvoid Functions_3_0::glBlitFramebuffer(
        GLint srcX0,
        GLint srcY0,
        GLint srcX1,
        GLint srcY1,
        GLint dstX0,
        GLint dstY0,
        GLint dstX1,
        GLint dstY1,
        GLbitfield mask,
        GLenum filter,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter), caller);
    }

    GLenum Functions_3_0::glCheckFramebufferStatus(GLenum target, [[maybe_unused]] const char* caller) const
    {
        GLenum ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glCheckFramebufferStatus(target), caller);

        return ret;
    }

    GLvoid Functions_3_0::glClampColor(GLenum target, GLenum clamp, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClampColor(target, clamp), caller);
    }

    GLvoid Functions_3_0::glClearBufferfi(
        GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearBufferfi(buffer, drawbuffer, depth, stencil), caller);
    }

    GLvoid Functions_3_0::glClearBufferfv(
        GLenum buffer, GLint drawbuffer, const GLfloat* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearBufferfv(buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_3_0::glClearBufferiv(
        GLenum buffer, GLint drawbuffer, const GLint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearBufferiv(buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_3_0::glClearBufferuiv(
        GLenum buffer, GLint drawbuffer, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearBufferuiv(buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_3_0::glColorMaski(
        GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorMaski(index, r, g, b, a), caller);
    }

    GLvoid Functions_3_0::glDeleteFramebuffers(
        GLsizei n, const GLuint* framebuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteFramebuffers(n, framebuffers), caller);
    }

    GLvoid Functions_3_0::glDeleteRenderbuffers(
        GLsizei n, const GLuint* renderbuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteRenderbuffers(n, renderbuffers), caller);
    }

    GLvoid Functions_3_0::glDeleteVertexArrays(
        GLsizei n, const GLuint* arrays, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteVertexArrays(n, arrays), caller);
    }

    GLvoid Functions_3_0::glDisablei(GLenum target, GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDisablei(target, index), caller);
    }

    GLvoid Functions_3_0::glEnablei(GLenum target, GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEnablei(target, index), caller);
    }

    GLvoid Functions_3_0::glEndConditionalRender([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEndConditionalRender(), caller);
    }

    GLvoid Functions_3_0::glEndTransformFeedback([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEndTransformFeedback(), caller);
    }

    GLvoid Functions_3_0::glFlushMappedBufferRange(
        GLenum target, GLintptr offset, GLsizeiptr length, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFlushMappedBufferRange(target, offset, length), caller);
    }

    GLvoid Functions_3_0::glFramebufferRenderbuffer(
        GLenum target,
        GLenum attachment,
        GLenum renderbuffertarget,
        GLuint renderbuffer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer), caller);
    }

    GLvoid Functions_3_0::glFramebufferTexture1D(
        GLenum target,
        GLenum attachment,
        GLenum textarget,
        GLuint texture,
        GLint level,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFramebufferTexture1D(target, attachment, textarget, texture, level), caller);
    }

    GLvoid Functions_3_0::glFramebufferTexture2D(
        GLenum target,
        GLenum attachment,
        GLenum textarget,
        GLuint texture,
        GLint level,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFramebufferTexture2D(target, attachment, textarget, texture, level), caller);
    }

    GLvoid Functions_3_0::glFramebufferTexture3D(
        GLenum target,
        GLenum attachment,
        GLenum textarget,
        GLuint texture,
        GLint level,
        GLint zoffset,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset), caller);
    }

    GLvoid Functions_3_0::glFramebufferTextureLayer(
        GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFramebufferTextureLayer(target, attachment, texture, level, layer), caller);
    }

    GLvoid Functions_3_0::glGenerateMipmap(GLenum target, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenerateMipmap(target), caller);
    }

    GLvoid Functions_3_0::glGetBooleani_v(
        GLenum target, GLuint index, GLboolean* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetBooleani_v(target, index, data), caller);
    }

    GLint Functions_3_0::glGetFragDataLocation(
        GLuint program, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetFragDataLocation(program, name), caller);

        return ret;
    }

    GLvoid Functions_3_0::glGetFramebufferAttachmentParameteriv(
        GLenum target, GLenum attachment, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params), caller);
    }

    GLvoid Functions_3_0::glGetIntegeri_v(
        GLenum target, GLuint index, GLint* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetIntegeri_v(target, index, data), caller);
    }

    GLvoid Functions_3_0::glGetRenderbufferParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetRenderbufferParameteriv(target, pname, params), caller);
    }

    const GLubyte* Functions_3_0::glGetStringi(GLenum name, GLuint index, [[maybe_unused]] const char* caller) const
    {
        const GLubyte* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetStringi(name, index), caller);

        return ret;
    }

    GLvoid Functions_3_0::glGetTexParameterIiv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTexParameterIiv(target, pname, params), caller);
    }

    GLvoid Functions_3_0::glGetTexParameterIuiv(
        GLenum target, GLenum pname, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTexParameterIuiv(target, pname, params), caller);
    }

    GLvoid Functions_3_0::glGetTransformFeedbackVarying(
        GLuint program,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLsizei* size,
        GLenum* type,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name), caller);
    }

    GLvoid Functions_3_0::glGetUniformuiv(
        GLuint program, GLint location, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetUniformuiv(program, location, params), caller);
    }

    GLvoid Functions_3_0::glGetVertexAttribIiv(
        GLuint index, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribIiv(index, pname, params), caller);
    }

    GLvoid Functions_3_0::glGetVertexAttribIuiv(
        GLuint index, GLenum pname, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexAttribIuiv(index, pname, params), caller);
    }

    GLboolean Functions_3_0::glIsEnabledi(GLenum target, GLuint index, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsEnabledi(target, index), caller);

        return ret;
    }

    GLboolean Functions_3_0::glIsFramebuffer(GLuint framebuffer, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsFramebuffer(framebuffer), caller);

        return ret;
    }

    GLboolean Functions_3_0::glIsRenderbuffer(GLuint renderbuffer, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsRenderbuffer(renderbuffer), caller);

        return ret;
    }

    GLboolean Functions_3_0::glIsVertexArray(GLuint array, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsVertexArray(array), caller);

        return ret;
    }

    GLvoid* Functions_3_0::glMapBufferRange(
        GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, [[maybe_unused]] const char* caller) const
    {
        GLvoid* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glMapBufferRange(target, offset, length, access), caller);

        return ret;
    }

    GLvoid Functions_3_0::glGenFramebuffers(GLsizei n, GLuint* framebuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenFramebuffers(n, framebuffers), caller);
    }

    GLvoid Functions_3_0::glGenRenderbuffers(
        GLsizei n, GLuint* renderbuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenRenderbuffers(n, renderbuffers), caller);
    }

    GLvoid Functions_3_0::glGenVertexArrays(GLsizei n, GLuint* arrays, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenVertexArrays(n, arrays), caller);
    }

    GLvoid Functions_3_0::glRenderbufferStorage(
        GLenum target, GLenum internalformat, GLsizei width, GLsizei height, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glRenderbufferStorage(target, internalformat, width, height), caller);
    }

    GLvoid Functions_3_0::glRenderbufferStorageMultisample(
        GLenum target,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glRenderbufferStorageMultisample(target, samples, internalformat, width, height), caller);
    }

    GLvoid Functions_3_0::glTexParameterIiv(
        GLenum target, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexParameterIiv(target, pname, params), caller);
    }

    GLvoid Functions_3_0::glTexParameterIuiv(
        GLenum target, GLenum pname, const GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexParameterIuiv(target, pname, params), caller);
    }

    GLvoid Functions_3_0::glTransformFeedbackVaryings(
        GLuint program,
        GLsizei count,
        const GLchar* const* varyings,
        GLenum bufferMode,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTransformFeedbackVaryings(program, count, varyings, bufferMode), caller);
    }

    GLvoid Functions_3_0::glUniform1ui(GLint location, GLuint v0, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1ui(location, v0), caller);
    }

    GLvoid Functions_3_0::glUniform1uiv(
        GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform1uiv(location, count, value), caller);
    }

    GLvoid Functions_3_0::glUniform2ui(GLint location, GLuint v0, GLuint v1, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2ui(location, v0, v1), caller);
    }

    GLvoid Functions_3_0::glUniform2uiv(
        GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform2uiv(location, count, value), caller);
    }

    GLvoid Functions_3_0::glUniform3ui(
        GLint location, GLuint v0, GLuint v1, GLuint v2, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3ui(location, v0, v1, v2), caller);
    }

    GLvoid Functions_3_0::glUniform3uiv(
        GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform3uiv(location, count, value), caller);
    }

    GLvoid Functions_3_0::glUniform4ui(
        GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4ui(location, v0, v1, v2, v3), caller);
    }

    GLvoid Functions_3_0::glUniform4uiv(
        GLint location, GLsizei count, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glUniform4uiv(location, count, value), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI1i(GLuint index, GLint x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI1i(index, x), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI1iv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI1iv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI1ui(GLuint index, GLuint x, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI1ui(index, x), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI1uiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI1uiv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI2i(GLuint index, GLint x, GLint y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI2i(index, x, y), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI2iv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI2iv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI2ui(
        GLuint index, GLuint x, GLuint y, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI2ui(index, x, y), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI2uiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI2uiv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI3i(
        GLuint index, GLint x, GLint y, GLint z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI3i(index, x, y, z), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI3iv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI3iv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI3ui(
        GLuint index, GLuint x, GLuint y, GLuint z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI3ui(index, x, y, z), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI3uiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI3uiv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4bv(GLuint index, const GLbyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4bv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4i(
        GLuint index, GLint x, GLint y, GLint z, GLint w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4i(index, x, y, z, w), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4iv(GLuint index, const GLint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4iv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4sv(GLuint index, const GLshort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4sv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4ubv(GLuint index, const GLubyte* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4ubv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4ui(
        GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4ui(index, x, y, z, w), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4uiv(GLuint index, const GLuint* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4uiv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribI4usv(
        GLuint index, const GLushort* v, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribI4usv(index, v), caller);
    }

    GLvoid Functions_3_0::glVertexAttribIPointer(
        GLuint index,
        GLint size,
        GLenum type,
        GLsizei stride,
        const GLvoid* pointer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribIPointer(index, size, type, stride, pointer), caller);
    }

    bool Functions_3_0::initialize()
    {
        Functions_2_1::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBeginConditionalRender =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glBeginConditionalRender"));
        _nfx_glBeginTransformFeedback =
            reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glBeginTransformFeedback"));
        _nfx_glBindBufferBase =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint)>(loader.loadFunctionPtr("glBindBufferBase"));
        _nfx_glBindBufferRange = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glBindBufferRange"));
        _nfx_glBindFragDataLocation = reinterpret_cast<GLvoid (*)(GLuint, GLuint, const GLchar*)>(
            loader.loadFunctionPtr("glBindFragDataLocation"));
        _nfx_glBindFramebuffer =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glBindFramebuffer"));
        _nfx_glBindRenderbuffer =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glBindRenderbuffer"));
        _nfx_glBindVertexArray = reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glBindVertexArray"));
        _nfx_glBlitFramebuffer =
            reinterpret_cast<GLvoid (*)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)>(
                loader.loadFunctionPtr("glBlitFramebuffer"));
        _nfx_glCheckFramebufferStatus =
            reinterpret_cast<GLenum (*)(GLenum)>(loader.loadFunctionPtr("glCheckFramebufferStatus"));
        _nfx_glClampColor = reinterpret_cast<GLvoid (*)(GLenum, GLenum)>(loader.loadFunctionPtr("glClampColor"));
        _nfx_glClearBufferfi =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, GLfloat, GLint)>(loader.loadFunctionPtr("glClearBufferfi"));
        _nfx_glClearBufferfv =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, const GLfloat*)>(loader.loadFunctionPtr("glClearBufferfv"));
        _nfx_glClearBufferiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, const GLint*)>(loader.loadFunctionPtr("glClearBufferiv"));
        _nfx_glClearBufferuiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLint, const GLuint*)>(loader.loadFunctionPtr("glClearBufferuiv"));
        _nfx_glColorMaski = reinterpret_cast<GLvoid (*)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean)>(
            loader.loadFunctionPtr("glColorMaski"));
        _nfx_glDeleteFramebuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteFramebuffers"));
        _nfx_glDeleteRenderbuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteRenderbuffers"));
        _nfx_glDeleteVertexArrays =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteVertexArrays"));
        _nfx_glDisablei = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glDisablei"));
        _nfx_glEnablei = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glEnablei"));
        _nfx_glEndConditionalRender = reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glEndConditionalRender"));
        _nfx_glEndTransformFeedback = reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glEndTransformFeedback"));
        _nfx_glFlushMappedBufferRange = reinterpret_cast<GLvoid (*)(GLenum, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glFlushMappedBufferRange"));
        _nfx_glFramebufferRenderbuffer = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLuint)>(
            loader.loadFunctionPtr("glFramebufferRenderbuffer"));
        _nfx_glFramebufferTexture1D = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLuint, GLint)>(
            loader.loadFunctionPtr("glFramebufferTexture1D"));
        _nfx_glFramebufferTexture2D = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLuint, GLint)>(
            loader.loadFunctionPtr("glFramebufferTexture2D"));
        _nfx_glFramebufferTexture3D = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLuint, GLint, GLint)>(
            loader.loadFunctionPtr("glFramebufferTexture3D"));
        _nfx_glFramebufferTextureLayer = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint, GLint, GLint)>(
            loader.loadFunctionPtr("glFramebufferTextureLayer"));
        _nfx_glGenerateMipmap = reinterpret_cast<GLvoid (*)(GLenum)>(loader.loadFunctionPtr("glGenerateMipmap"));
        _nfx_glGenFramebuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenFramebuffers"));
        _nfx_glGenRenderbuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenRenderbuffers"));
        _nfx_glGenVertexArrays =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenVertexArrays"));
        _nfx_glGetBooleani_v =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLboolean*)>(loader.loadFunctionPtr("glGetBooleani_v"));
        _nfx_glGetFragDataLocation =
            reinterpret_cast<GLint (*)(GLuint, const GLchar*)>(loader.loadFunctionPtr("glGetFragDataLocation"));
        _nfx_glGetFramebufferAttachmentParameteriv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetFramebufferAttachmentParameteriv"));
        _nfx_glGetIntegeri_v =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLint*)>(loader.loadFunctionPtr("glGetIntegeri_v"));
        _nfx_glGetRenderbufferParameteriv = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetRenderbufferParameteriv"));
        _nfx_glGetStringi =
            reinterpret_cast<const GLubyte* (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glGetStringi"));
        _nfx_glGetTexParameterIiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetTexParameterIiv"));
        _nfx_glGetTexParameterIuiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint*)>(loader.loadFunctionPtr("glGetTexParameterIuiv"));
        _nfx_glGetTransformFeedbackVarying =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*)>(
                loader.loadFunctionPtr("glGetTransformFeedbackVarying"));
        _nfx_glGetUniformuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLuint*)>(loader.loadFunctionPtr("glGetUniformuiv"));
        _nfx_glGetVertexAttribIiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetVertexAttribIiv"));
        _nfx_glGetVertexAttribIuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint*)>(loader.loadFunctionPtr("glGetVertexAttribIuiv"));
        _nfx_glIsEnabledi = reinterpret_cast<GLboolean (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glIsEnabledi"));
        _nfx_glIsFramebuffer = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsFramebuffer"));
        _nfx_glIsRenderbuffer = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsRenderbuffer"));
        _nfx_glIsVertexArray = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsVertexArray"));
        _nfx_glMapBufferRange = reinterpret_cast<GLvoid* (*)(GLenum, GLintptr, GLsizeiptr, GLbitfield)>(
            loader.loadFunctionPtr("glMapBufferRange"));
        _nfx_glRenderbufferStorage = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glRenderbufferStorage"));
        _nfx_glRenderbufferStorageMultisample = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glRenderbufferStorageMultisample"));
        _nfx_glTexParameterIiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLint*)>(loader.loadFunctionPtr("glTexParameterIiv"));
        _nfx_glTexParameterIuiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLuint*)>(loader.loadFunctionPtr("glTexParameterIuiv"));
        _nfx_glTransformFeedbackVaryings = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLchar* const*, GLenum)>(
            loader.loadFunctionPtr("glTransformFeedbackVaryings"));
        _nfx_glUniform1ui = reinterpret_cast<GLvoid (*)(GLint, GLuint)>(loader.loadFunctionPtr("glUniform1ui"));
        _nfx_glUniform1uiv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glUniform1uiv"));
        _nfx_glUniform2ui = reinterpret_cast<GLvoid (*)(GLint, GLuint, GLuint)>(loader.loadFunctionPtr("glUniform2ui"));
        _nfx_glUniform2uiv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glUniform2uiv"));
        _nfx_glUniform3ui =
            reinterpret_cast<GLvoid (*)(GLint, GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glUniform3ui"));
        _nfx_glUniform3uiv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glUniform3uiv"));
        _nfx_glUniform4ui =
            reinterpret_cast<GLvoid (*)(GLint, GLuint, GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glUniform4ui"));
        _nfx_glUniform4uiv =
            reinterpret_cast<GLvoid (*)(GLint, GLsizei, const GLuint*)>(loader.loadFunctionPtr("glUniform4uiv"));
        _nfx_glVertexAttribI1i =
            reinterpret_cast<GLvoid (*)(GLuint, GLint)>(loader.loadFunctionPtr("glVertexAttribI1i"));
        _nfx_glVertexAttribI1iv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttribI1iv"));
        _nfx_glVertexAttribI1ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glVertexAttribI1ui"));
        _nfx_glVertexAttribI1uiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttribI1uiv"));
        _nfx_glVertexAttribI2i =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint)>(loader.loadFunctionPtr("glVertexAttribI2i"));
        _nfx_glVertexAttribI2iv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttribI2iv"));
        _nfx_glVertexAttribI2ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glVertexAttribI2ui"));
        _nfx_glVertexAttribI2uiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttribI2uiv"));
        _nfx_glVertexAttribI3i =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint)>(loader.loadFunctionPtr("glVertexAttribI3i"));
        _nfx_glVertexAttribI3iv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttribI3iv"));
        _nfx_glVertexAttribI3ui =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glVertexAttribI3ui"));
        _nfx_glVertexAttribI3uiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttribI3uiv"));
        _nfx_glVertexAttribI4bv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLbyte*)>(loader.loadFunctionPtr("glVertexAttribI4bv"));
        _nfx_glVertexAttribI4i = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint)>(
            loader.loadFunctionPtr("glVertexAttribI4i"));
        _nfx_glVertexAttribI4iv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLint*)>(loader.loadFunctionPtr("glVertexAttribI4iv"));
        _nfx_glVertexAttribI4sv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLshort*)>(loader.loadFunctionPtr("glVertexAttribI4sv"));
        _nfx_glVertexAttribI4ubv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLubyte*)>(loader.loadFunctionPtr("glVertexAttribI4ubv"));
        _nfx_glVertexAttribI4ui = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint, GLuint, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribI4ui"));
        _nfx_glVertexAttribI4uiv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLuint*)>(loader.loadFunctionPtr("glVertexAttribI4uiv"));
        _nfx_glVertexAttribI4usv =
            reinterpret_cast<GLvoid (*)(GLuint, const GLushort*)>(loader.loadFunctionPtr("glVertexAttribI4usv"));
        _nfx_glVertexAttribIPointer = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glVertexAttribIPointer"));

        return s_loaded = true;
    }

    void Functions_3_0::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_2_1::teardown();
    }

    void Functions_3_0::nullifyPointers()
    {
        _nfx_glBeginConditionalRender = nullptr;
        _nfx_glBeginTransformFeedback = nullptr;
        _nfx_glBindBufferBase = nullptr;
        _nfx_glBindBufferRange = nullptr;
        _nfx_glBindFragDataLocation = nullptr;
        _nfx_glBindFramebuffer = nullptr;
        _nfx_glBindRenderbuffer = nullptr;
        _nfx_glBindVertexArray = nullptr;
        _nfx_glBlitFramebuffer = nullptr;
        _nfx_glCheckFramebufferStatus = nullptr;
        _nfx_glClampColor = nullptr;
        _nfx_glClearBufferfi = nullptr;
        _nfx_glClearBufferfv = nullptr;
        _nfx_glClearBufferiv = nullptr;
        _nfx_glClearBufferuiv = nullptr;
        _nfx_glColorMaski = nullptr;
        _nfx_glDeleteFramebuffers = nullptr;
        _nfx_glDeleteRenderbuffers = nullptr;
        _nfx_glDeleteVertexArrays = nullptr;
        _nfx_glDisablei = nullptr;
        _nfx_glEnablei = nullptr;
        _nfx_glEndConditionalRender = nullptr;
        _nfx_glEndTransformFeedback = nullptr;
        _nfx_glFlushMappedBufferRange = nullptr;
        _nfx_glFramebufferRenderbuffer = nullptr;
        _nfx_glFramebufferTexture1D = nullptr;
        _nfx_glFramebufferTexture2D = nullptr;
        _nfx_glFramebufferTexture3D = nullptr;
        _nfx_glFramebufferTextureLayer = nullptr;
        _nfx_glGenerateMipmap = nullptr;
        _nfx_glGenFramebuffers = nullptr;
        _nfx_glGenRenderbuffers = nullptr;
        _nfx_glGenVertexArrays = nullptr;
        _nfx_glGetBooleani_v = nullptr;
        _nfx_glGetFragDataLocation = nullptr;
        _nfx_glGetFramebufferAttachmentParameteriv = nullptr;
        _nfx_glGetIntegeri_v = nullptr;
        _nfx_glGetRenderbufferParameteriv = nullptr;
        _nfx_glGetStringi = nullptr;
        _nfx_glGetTexParameterIiv = nullptr;
        _nfx_glGetTexParameterIuiv = nullptr;
        _nfx_glGetTransformFeedbackVarying = nullptr;
        _nfx_glGetUniformuiv = nullptr;
        _nfx_glGetVertexAttribIiv = nullptr;
        _nfx_glGetVertexAttribIuiv = nullptr;
        _nfx_glIsEnabledi = nullptr;
        _nfx_glIsFramebuffer = nullptr;
        _nfx_glIsRenderbuffer = nullptr;
        _nfx_glIsVertexArray = nullptr;
        _nfx_glMapBufferRange = nullptr;
        _nfx_glRenderbufferStorage = nullptr;
        _nfx_glRenderbufferStorageMultisample = nullptr;
        _nfx_glTexParameterIiv = nullptr;
        _nfx_glTexParameterIuiv = nullptr;
        _nfx_glTransformFeedbackVaryings = nullptr;
        _nfx_glUniform1ui = nullptr;
        _nfx_glUniform1uiv = nullptr;
        _nfx_glUniform2ui = nullptr;
        _nfx_glUniform2uiv = nullptr;
        _nfx_glUniform3ui = nullptr;
        _nfx_glUniform3uiv = nullptr;
        _nfx_glUniform4ui = nullptr;
        _nfx_glUniform4uiv = nullptr;
        _nfx_glVertexAttribI1i = nullptr;
        _nfx_glVertexAttribI1iv = nullptr;
        _nfx_glVertexAttribI1ui = nullptr;
        _nfx_glVertexAttribI1uiv = nullptr;
        _nfx_glVertexAttribI2i = nullptr;
        _nfx_glVertexAttribI2iv = nullptr;
        _nfx_glVertexAttribI2ui = nullptr;
        _nfx_glVertexAttribI2uiv = nullptr;
        _nfx_glVertexAttribI3i = nullptr;
        _nfx_glVertexAttribI3iv = nullptr;
        _nfx_glVertexAttribI3ui = nullptr;
        _nfx_glVertexAttribI3uiv = nullptr;
        _nfx_glVertexAttribI4bv = nullptr;
        _nfx_glVertexAttribI4i = nullptr;
        _nfx_glVertexAttribI4iv = nullptr;
        _nfx_glVertexAttribI4sv = nullptr;
        _nfx_glVertexAttribI4ubv = nullptr;
        _nfx_glVertexAttribI4ui = nullptr;
        _nfx_glVertexAttribI4uiv = nullptr;
        _nfx_glVertexAttribI4usv = nullptr;
        _nfx_glVertexAttribIPointer = nullptr;
    }
} // namespace nfx::graphics::gl
