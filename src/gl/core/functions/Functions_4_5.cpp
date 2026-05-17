#include "nfx/graphics/gl/core/functions/Functions_4_5.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_5::Functions_4_5()
        : Functions_4_4{}
    {}

    Functions_4_5::~Functions_4_5()
    {
        s_loaded = false;
    }

    GLvoid Functions_4_5::glBindTextureUnit(GLuint unit, GLuint texture, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindTextureUnit(unit, texture), caller);
    }

    GLvoid Functions_4_5::glBlitNamedFramebuffer(
        GLuint readFramebuffer,
        GLuint drawFramebuffer,
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
            _nfx_glBlitNamedFramebuffer(
                readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter),
            caller);
    }

    GLenum Functions_4_5::glCheckNamedFramebufferStatus(
        GLuint framebuffer, GLenum target, [[maybe_unused]] const char* caller) const
    {
        GLenum ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glCheckNamedFramebufferStatus(framebuffer, target), caller);

        return ret;
    }

    GLvoid Functions_4_5::glClearNamedBufferData(
        GLuint buffer,
        GLenum internalformat,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearNamedBufferData(buffer, internalformat, format, type, data), caller);
    }

    GLvoid Functions_4_5::glClearNamedBufferSubData(
        GLuint buffer,
        GLenum internalformat,
        GLintptr offset,
        GLsizeiptr size,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data), caller);
    }

    GLvoid Functions_4_5::glClearNamedFramebufferfi(
        GLuint framebuffer,
        GLenum buffer,
        GLint drawbuffer,
        GLfloat depth,
        GLint stencil,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil), caller);
    }

    GLvoid Functions_4_5::glClearNamedFramebufferfv(
        GLuint framebuffer,
        GLenum buffer,
        GLint drawbuffer,
        const GLfloat* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_4_5::glClearNamedFramebufferiv(
        GLuint framebuffer,
        GLenum buffer,
        GLint drawbuffer,
        const GLint* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_4_5::glClearNamedFramebufferuiv(
        GLuint framebuffer,
        GLenum buffer,
        GLint drawbuffer,
        const GLuint* value,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value), caller);
    }

    GLvoid Functions_4_5::glClipControl(GLenum origin, GLenum depth, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClipControl(origin, depth), caller);
    }

    GLvoid Functions_4_5::glCompressedTextureSubImage1D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLsizei width,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data), caller);
    }

    GLvoid Functions_4_5::glCompressedTextureSubImage2D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTextureSubImage2D(
                texture, level, xoffset, yoffset, width, height, format, imageSize, data),
            caller);
    }

    GLvoid Functions_4_5::glCompressedTextureSubImage3D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLenum format,
        GLsizei imageSize,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCompressedTextureSubImage3D(
                texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data),
            caller);
    }

    GLvoid Functions_4_5::glCopyNamedBufferSubData(
        GLuint readBuffer,
        GLuint writeBuffer,
        GLintptr readOffset,
        GLintptr writeOffset,
        GLsizeiptr size,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size), caller);
    }

    GLvoid Functions_4_5::glCopyTextureSubImage1D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint x,
        GLint y,
        GLsizei width,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCopyTextureSubImage1D(texture, level, xoffset, x, y, width), caller);
    }

    GLvoid Functions_4_5::glCopyTextureSubImage2D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height), caller);
    }

    GLvoid Functions_4_5::glCopyTextureSubImage3D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height), caller);
    }

    GLvoid Functions_4_5::glCreateBuffers(GLsizei n, GLuint* buffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateBuffers(n, buffers), caller);
    }

    GLvoid Functions_4_5::glCreateFramebuffers(
        GLsizei n, GLuint* framebuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateFramebuffers(n, framebuffers), caller);
    }

    GLvoid Functions_4_5::glCreateProgramPipelines(
        GLsizei n, GLuint* pipelines, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateProgramPipelines(n, pipelines), caller);
    }

    GLvoid Functions_4_5::glCreateQueries(
        GLenum target, GLsizei n, GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateQueries(target, n, ids), caller);
    }

    GLvoid Functions_4_5::glCreateRenderbuffers(
        GLsizei n, GLuint* renderbuffers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateRenderbuffers(n, renderbuffers), caller);
    }

    GLvoid Functions_4_5::glCreateSamplers(GLsizei n, GLuint* samplers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateSamplers(n, samplers), caller);
    }

    GLvoid Functions_4_5::glCreateTextures(
        GLenum target, GLsizei n, GLuint* textures, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateTextures(target, n, textures), caller);
    }

    GLvoid Functions_4_5::glCreateTransformFeedbacks(GLsizei n, GLuint* ids, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateTransformFeedbacks(n, ids), caller);
    }

    GLvoid Functions_4_5::glCreateVertexArrays(GLsizei n, GLuint* arrays, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glCreateVertexArrays(n, arrays), caller);
    }

    GLvoid Functions_4_5::glDisableVertexArrayAttrib(
        GLuint vaobj, GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDisableVertexArrayAttrib(vaobj, index), caller);
    }

    GLvoid Functions_4_5::glEnableVertexArrayAttrib(
        GLuint vaobj, GLuint index, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glEnableVertexArrayAttrib(vaobj, index), caller);
    }

    GLvoid Functions_4_5::glFlushMappedNamedBufferRange(
        GLuint buffer, GLintptr offset, GLsizeiptr length, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFlushMappedNamedBufferRange(buffer, offset, length), caller);
    }

    GLvoid Functions_4_5::glGenerateTextureMipmap(GLuint texture, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenerateTextureMipmap(texture), caller);
    }

    GLvoid Functions_4_5::glGetCompressedTextureImage(
        GLuint texture, GLint level, GLsizei bufSize, GLvoid* pixels, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetCompressedTextureImage(texture, level, bufSize, pixels), caller);
    }

    GLvoid Functions_4_5::glGetCompressedTextureSubImage(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLsizei bufSize,
        GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetCompressedTextureSubImage(
                texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels),
            caller);
    }

    GLenum Functions_4_5::glGetGraphicsResetStatus([[maybe_unused]] const char* caller) const
    {
        GLenum ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetGraphicsResetStatus(), caller);

        return ret;
    }

    GLvoid Functions_4_5::glGetNamedBufferParameteri64v(
        GLuint buffer, GLenum pname, GLint64* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedBufferParameteri64v(buffer, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetNamedBufferParameteriv(
        GLuint buffer, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedBufferParameteriv(buffer, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetNamedBufferPointerv(
        GLuint buffer, GLenum pname, GLvoid** params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedBufferPointerv(buffer, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetNamedBufferSubData(
        GLuint buffer, GLintptr offset, GLsizeiptr size, GLvoid* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedBufferSubData(buffer, offset, size, data), caller);
    }

    GLvoid Functions_4_5::glGetNamedFramebufferAttachmentParameteriv(
        GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetNamedFramebufferParameteriv(
        GLuint framebuffer, GLenum pname, GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedFramebufferParameteriv(framebuffer, pname, param), caller);
    }

    GLvoid Functions_4_5::glGetNamedRenderbufferParameteriv(
        GLuint renderbuffer, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetNamedRenderbufferParameteriv(renderbuffer, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetnCompressedTexImage(
        GLenum target, GLint lod, GLsizei bufSize, GLvoid* pixels, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnCompressedTexImage(target, lod, bufSize, pixels), caller);
    }

    GLvoid Functions_4_5::glGetnTexImage(
        GLenum target,
        GLint level,
        GLenum format,
        GLenum type,
        GLsizei bufSize,
        GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnTexImage(target, level, format, type, bufSize, pixels), caller);
    }

    GLvoid Functions_4_5::glGetnUniformdv(
        GLuint program, GLint location, GLsizei bufSize, GLdouble* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnUniformdv(program, location, bufSize, params), caller);
    }

    GLvoid Functions_4_5::glGetnUniformfv(
        GLuint program, GLint location, GLsizei bufSize, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnUniformfv(program, location, bufSize, params), caller);
    }

    GLvoid Functions_4_5::glGetnUniformiv(
        GLuint program, GLint location, GLsizei bufSize, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnUniformiv(program, location, bufSize, params), caller);
    }

    GLvoid Functions_4_5::glGetnUniformuiv(
        GLuint program, GLint location, GLsizei bufSize, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetnUniformuiv(program, location, bufSize, params), caller);
    }

    GLvoid Functions_4_5::glGetQueryBufferObjecti64v(
        GLuint id, GLuint buffer, GLenum pname, GLintptr offset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryBufferObjecti64v(id, buffer, pname, offset), caller);
    }

    GLvoid Functions_4_5::glGetQueryBufferObjectiv(
        GLuint id, GLuint buffer, GLenum pname, GLintptr offset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryBufferObjectiv(id, buffer, pname, offset), caller);
    }

    GLvoid Functions_4_5::glGetQueryBufferObjectui64v(
        GLuint id, GLuint buffer, GLenum pname, GLintptr offset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryBufferObjectui64v(id, buffer, pname, offset), caller);
    }

    GLvoid Functions_4_5::glGetQueryBufferObjectuiv(
        GLuint id, GLuint buffer, GLenum pname, GLintptr offset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryBufferObjectuiv(id, buffer, pname, offset), caller);
    }

    GLvoid Functions_4_5::glGetTextureImage(
        GLuint texture,
        GLint level,
        GLenum format,
        GLenum type,
        GLsizei bufSize,
        GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureImage(texture, level, format, type, bufSize, pixels), caller);
    }

    GLvoid Functions_4_5::glGetTextureLevelParameterfv(
        GLuint texture, GLint level, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureLevelParameterfv(texture, level, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureLevelParameteriv(
        GLuint texture, GLint level, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureLevelParameteriv(texture, level, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureParameterfv(
        GLuint texture, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureParameterfv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureParameterIiv(
        GLuint texture, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureParameterIiv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureParameterIuiv(
        GLuint texture, GLenum pname, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureParameterIuiv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureParameteriv(
        GLuint texture, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTextureParameteriv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glGetTextureSubImage(
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
        GLsizei bufSize,
        void* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetTextureSubImage(
                texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels),
            caller);
    }

    GLvoid Functions_4_5::glGetTransformFeedbacki64_v(
        GLuint xfb, GLenum pname, GLuint index, GLint64* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTransformFeedbacki64_v(xfb, pname, index, param), caller);
    }

    GLvoid Functions_4_5::glGetTransformFeedbackiv(
        GLuint xfb, GLenum pname, GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTransformFeedbackiv(xfb, pname, param), caller);
    }

    GLvoid Functions_4_5::glGetTransformFeedbacki_v(
        GLuint xfb, GLenum pname, GLuint index, GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetTransformFeedbacki_v(xfb, pname, index, param), caller);
    }

    GLvoid Functions_4_5::glGetVertexArrayIndexed64iv(
        GLuint vaobj, GLuint index, GLenum pname, GLint64* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexArrayIndexed64iv(vaobj, index, pname, param), caller);
    }

    GLvoid Functions_4_5::glGetVertexArrayIndexediv(
        GLuint vaobj, GLuint index, GLenum pname, GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexArrayIndexediv(vaobj, index, pname, param), caller);
    }

    GLvoid Functions_4_5::glGetVertexArrayiv(
        GLuint vaobj, GLenum pname, GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetVertexArrayiv(vaobj, pname, param), caller);
    }

    GLvoid Functions_4_5::glInvalidateNamedFramebufferData(
        GLuint framebuffer,
        GLsizei numAttachments,
        const GLenum* attachments,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments), caller);
    }

    GLvoid Functions_4_5::glInvalidateNamedFramebufferSubData(
        GLuint framebuffer,
        GLsizei numAttachments,
        const GLenum* attachments,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height),
            caller);
    }

    GLvoid* Functions_4_5::glMapNamedBuffer(GLuint buffer, GLenum access, [[maybe_unused]] const char* caller) const
    {
        GLvoid* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glMapNamedBuffer(buffer, access), caller);

        return ret;
    }

    GLvoid* Functions_4_5::glMapNamedBufferRange(
        GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, [[maybe_unused]] const char* caller) const
    {
        GLvoid* ret{ nullptr };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glMapNamedBufferRange(buffer, offset, length, access), caller);

        return ret;
    }

    GLvoid Functions_4_5::glMemoryBarrierByRegion(GLbitfield barriers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMemoryBarrierByRegion(barriers), caller);
    }

    GLvoid Functions_4_5::glNamedBufferData(
        GLuint buffer, GLsizei size, const GLvoid* data, GLenum usage, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedBufferData(buffer, size, data, usage), caller);
    }

    GLvoid Functions_4_5::glNamedBufferStorage(
        GLuint buffer, GLsizei size, const GLvoid* data, GLbitfield flags, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedBufferStorage(buffer, size, data, flags), caller);
    }

    GLvoid Functions_4_5::glNamedBufferSubData(
        GLuint buffer, GLintptr offset, GLsizei size, const GLvoid* data, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedBufferSubData(buffer, offset, size, data), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferDrawBuffer(
        GLuint framebuffer, GLenum buf, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedFramebufferDrawBuffer(framebuffer, buf), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferDrawBuffers(
        GLuint framebuffer, GLsizei n, const GLenum* bufs, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedFramebufferDrawBuffers(framebuffer, n, bufs), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferParameteri(
        GLuint framebuffer, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedFramebufferParameteri(framebuffer, pname, param), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferReadBuffer(
        GLuint framebuffer, GLenum src, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedFramebufferReadBuffer(framebuffer, src), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferRenderbuffer(
        GLuint framebuffer,
        GLenum attachment,
        GLenum renderbuffertarget,
        GLuint renderbuffer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferTexture(
        GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNamedFramebufferTexture(framebuffer, attachment, texture, level), caller);
    }

    GLvoid Functions_4_5::glNamedFramebufferTextureLayer(
        GLuint framebuffer,
        GLenum attachment,
        GLuint texture,
        GLint level,
        GLint layer,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer), caller);
    }

    GLvoid Functions_4_5::glNamedRenderbufferStorage(
        GLuint renderbuffer,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glNamedRenderbufferStorage(renderbuffer, internalformat, width, height), caller);
    }

    GLvoid Functions_4_5::glNamedRenderbufferStorageMultisample(
        GLuint renderbuffer,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height), caller);
    }

    GLvoid Functions_4_5::glReadnPixels(
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        GLsizei bufSize,
        GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glReadnPixels(x, y, width, height, format, type, bufSize, data), caller);
    }

    GLvoid Functions_4_5::glTextureBarrier([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureBarrier(), caller);
    }

    GLvoid Functions_4_5::glTextureBuffer(
        GLuint texture, GLenum internalformat, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureBuffer(texture, internalformat, buffer), caller);
    }

    GLvoid Functions_4_5::glTextureBufferRange(
        GLuint texture,
        GLenum internalformat,
        GLuint buffer,
        GLintptr offset,
        GLsizeiptr size,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureBufferRange(texture, internalformat, buffer, offset, size), caller);
    }

    GLvoid Functions_4_5::glTextureParameterf(
        GLuint texture, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameterf(texture, pname, param), caller);
    }

    GLvoid Functions_4_5::glTextureParameterfv(
        GLuint texture, GLenum pname, const GLfloat* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameterfv(texture, pname, param), caller);
    }

    GLvoid Functions_4_5::glTextureParameteri(
        GLuint texture, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameteri(texture, pname, param), caller);
    }

    GLvoid Functions_4_5::glTextureParameterIiv(
        GLuint texture, GLenum pname, const GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameterIiv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glTextureParameterIuiv(
        GLuint texture, GLenum pname, const GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameterIuiv(texture, pname, params), caller);
    }

    GLvoid Functions_4_5::glTextureParameteriv(
        GLuint texture, GLenum pname, const GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureParameteriv(texture, pname, param), caller);
    }

    GLvoid Functions_4_5::glTextureStorage1D(
        GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureStorage1D(texture, levels, internalformat, width), caller);
    }

    GLvoid Functions_4_5::glTextureStorage2D(
        GLuint texture,
        GLsizei levels,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTextureStorage2D(texture, levels, internalformat, width, height), caller);
    }

    GLvoid Functions_4_5::glTextureStorage2DMultisample(
        GLuint texture,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLboolean fixedsamplelocations,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations),
            caller);
    }

    GLvoid Functions_4_5::glTextureStorage3D(
        GLuint texture,
        GLsizei levels,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureStorage3D(texture, levels, internalformat, width, height, depth), caller);
    }

    GLvoid Functions_4_5::glTextureStorage3DMultisample(
        GLuint texture,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        GLboolean fixedsamplelocations,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureStorage3DMultisample(
                texture, samples, internalformat, width, height, depth, fixedsamplelocations),
            caller);
    }

    GLvoid Functions_4_5::glTextureSubImage1D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLsizei width,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels), caller);
    }

    GLvoid Functions_4_5::glTextureSubImage2D(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLsizei width,
        GLsizei height,
        GLenum format,
        GLenum type,
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels), caller);
    }

    GLvoid Functions_4_5::glTextureSubImage3D(
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
        const GLvoid* pixels,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureSubImage3D(
                texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels),
            caller);
    }

    GLvoid Functions_4_5::glTransformFeedbackBufferBase(
        GLuint xfb, GLuint index, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTransformFeedbackBufferBase(xfb, index, buffer), caller);
    }

    GLvoid Functions_4_5::glTransformFeedbackBufferRange(
        GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, [[maybe_unused]] const char* caller)
        const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTransformFeedbackBufferRange(xfb, index, buffer, offset, size), caller);
    }

    GLboolean Functions_4_5::glUnmapNamedBuffer(GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glUnmapNamedBuffer(buffer), caller);

        return ret;
    }

    GLvoid Functions_4_5::glVertexArrayAttribBinding(
        GLuint vaobj, GLuint attribindex, GLuint bindingindex, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexArrayAttribBinding(vaobj, attribindex, bindingindex), caller);
    }

    GLvoid Functions_4_5::glVertexArrayAttribFormat(
        GLuint vaobj,
        GLuint attribindex,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLuint relativeoffset,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset), caller);
    }

    GLvoid Functions_4_5::glVertexArrayAttribIFormat(
        GLuint vaobj,
        GLuint attribindex,
        GLint size,
        GLenum type,
        GLuint relativeoffset,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset), caller);
    }

    GLvoid Functions_4_5::glVertexArrayAttribLFormat(
        GLuint vaobj,
        GLuint attribindex,
        GLint size,
        GLenum type,
        GLuint relativeoffset,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset), caller);
    }

    GLvoid Functions_4_5::glVertexArrayBindingDivisor(
        GLuint vaobj, GLuint bindingindex, GLuint divisor, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexArrayBindingDivisor(vaobj, bindingindex, divisor), caller);
    }

    GLvoid Functions_4_5::glVertexArrayElementBuffer(
        GLuint vaobj, GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexArrayElementBuffer(vaobj, buffer), caller);
    }

    GLvoid Functions_4_5::glVertexArrayVertexBuffer(
        GLuint vaobj,
        GLuint bindingindex,
        GLuint buffer,
        GLintptr offset,
        GLsizei stride,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride), caller);
    }

    GLvoid Functions_4_5::glVertexArrayVertexBuffers(
        GLuint vaobj,
        GLuint first,
        GLsizei count,
        const GLuint* buffers,
        const GLintptr* offsets,
        const GLsizei* strides,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides), caller);
    }

    bool Functions_4_5::initialize()
    {
        Functions_4_4::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBindTextureUnit =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glBindTextureUnit"));
        _nfx_glBlitNamedFramebuffer = reinterpret_cast<GLvoid (*)(
            GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)>(
            loader.loadFunctionPtr("glBlitNamedFramebuffer"));
        _nfx_glCheckNamedFramebufferStatus =
            reinterpret_cast<GLenum (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glCheckNamedFramebufferStatus"));
        _nfx_glClearNamedBufferData = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glClearNamedBufferData"));
        _nfx_glClearNamedBufferSubData =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const GLvoid*)>(
                loader.loadFunctionPtr("glClearNamedBufferSubData"));
        _nfx_glClearNamedFramebufferfi = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint, GLfloat, GLint)>(
            loader.loadFunctionPtr("glClearNamedFramebufferfi"));
        _nfx_glClearNamedFramebufferfv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint, const GLfloat*)>(
            loader.loadFunctionPtr("glClearNamedFramebufferfv"));
        _nfx_glClearNamedFramebufferiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint, const GLint*)>(
            loader.loadFunctionPtr("glClearNamedFramebufferiv"));
        _nfx_glClearNamedFramebufferuiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint, const GLuint*)>(
            loader.loadFunctionPtr("glClearNamedFramebufferuiv"));
        _nfx_glClipControl = reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glClipControl"));
        _nfx_glCompressedTextureSubImage1D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTextureSubImage1D"));
        _nfx_glCompressedTextureSubImage2D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*)>(
                loader.loadFunctionPtr("glCompressedTextureSubImage2D"));
        _nfx_glCompressedTextureSubImage3D = reinterpret_cast<GLvoid (*)(
            GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*)>(
            loader.loadFunctionPtr("glCompressedTextureSubImage3D"));
        _nfx_glCopyNamedBufferSubData = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glCopyNamedBufferSubData"));
        _nfx_glCopyTextureSubImage1D = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei)>(
            loader.loadFunctionPtr("glCopyTextureSubImage1D"));
        _nfx_glCopyTextureSubImage2D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glCopyTextureSubImage2D"));
        _nfx_glCopyTextureSubImage3D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glCopyTextureSubImage3D"));
        _nfx_glCreateBuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateBuffers"));
        _nfx_glCreateFramebuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateFramebuffers"));
        _nfx_glCreateProgramPipelines =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateProgramPipelines"));
        _nfx_glCreateQueries =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateQueries"));
        _nfx_glCreateRenderbuffers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateRenderbuffers"));
        _nfx_glCreateSamplers =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateSamplers"));
        _nfx_glCreateTextures =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateTextures"));
        _nfx_glCreateTransformFeedbacks =
            reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glCreateTransformFeedbacks"));
        _nfx_glCreateVertexArrays =
            reinterpret_cast<GLvoid (*)(GLsizei n, GLuint*)>(loader.loadFunctionPtr("glCreateVertexArrays"));
        _nfx_glDisableVertexArrayAttrib =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glDisableVertexArrayAttrib"));
        _nfx_glEnableVertexArrayAttrib =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glEnableVertexArrayAttrib"));
        _nfx_glFlushMappedNamedBufferRange = reinterpret_cast<GLvoid (*)(GLuint, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glFlushMappedNamedBufferRange"));
        _nfx_glGenerateTextureMipmap =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glGenerateTextureMipmap"));
        _nfx_glGetCompressedTextureImage = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLvoid*)>(
            loader.loadFunctionPtr("glGetCompressedTextureImage"));
        _nfx_glGetCompressedTextureSubImage = reinterpret_cast<GLvoid (*)(
            GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, GLvoid*)>(
            loader.loadFunctionPtr("glGetCompressedTextureSubImage"));
        _nfx_glGetGraphicsResetStatus =
            reinterpret_cast<GLenum (*)()>(loader.loadFunctionPtr("glGetGraphicsResetStatus"));
        _nfx_glGetNamedBufferParameteri64v = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint64*)>(
            loader.loadFunctionPtr("glGetNamedBufferParameteri64v"));
        _nfx_glGetNamedBufferParameteriv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetNamedBufferParameteriv"));
        _nfx_glGetNamedBufferPointerv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLvoid**)>(loader.loadFunctionPtr("glGetNamedBufferPointerv"));
        _nfx_glGetNamedBufferSubData = reinterpret_cast<GLvoid (*)(GLuint, GLintptr, GLsizeiptr, GLvoid*)>(
            loader.loadFunctionPtr("glGetNamedBufferSubData"));
        _nfx_glGetNamedFramebufferAttachmentParameteriv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetNamedFramebufferAttachmentParameteriv"));
        _nfx_glGetNamedFramebufferParameteriv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetNamedFramebufferParameteriv"));
        _nfx_glGetNamedRenderbufferParameteriv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetNamedRenderbufferParameteriv"));
        _nfx_glGetnCompressedTexImage = reinterpret_cast<GLvoid (*)(GLenum, GLint, GLsizei, GLvoid*)>(
            loader.loadFunctionPtr("glGetnCompressedTexImage"));
        _nfx_glGetnTexImage = reinterpret_cast<GLvoid (*)(GLenum, GLint, GLenum, GLenum, GLsizei, GLvoid*)>(
            loader.loadFunctionPtr("glGetnTexImage"));
        _nfx_glGetnUniformdv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLdouble*)>(loader.loadFunctionPtr("glGetnUniformdv"));
        _nfx_glGetnUniformfv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLfloat*)>(loader.loadFunctionPtr("glGetnUniformfv"));
        _nfx_glGetnUniformiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLint*)>(loader.loadFunctionPtr("glGetnUniformiv"));
        _nfx_glGetnUniformuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLsizei, GLuint*)>(loader.loadFunctionPtr("glGetnUniformuiv"));
        _nfx_glGetQueryBufferObjecti64v = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLintptr)>(
            loader.loadFunctionPtr("glGetQueryBufferObjecti64v"));
        _nfx_glGetQueryBufferObjectiv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLintptr)>(
            loader.loadFunctionPtr("glGetQueryBufferObjectiv"));
        _nfx_glGetQueryBufferObjectui64v = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLintptr)>(
            loader.loadFunctionPtr("glGetQueryBufferObjectui64v"));
        _nfx_glGetQueryBufferObjectuiv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLintptr)>(
            loader.loadFunctionPtr("glGetQueryBufferObjectuiv"));
        _nfx_glGetTextureImage = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLenum, GLsizei, GLvoid*)>(
            loader.loadFunctionPtr("glGetTextureImage"));
        _nfx_glGetTextureLevelParameterfv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLfloat*)>(
            loader.loadFunctionPtr("glGetTextureLevelParameterfv"));
        _nfx_glGetTextureLevelParameteriv = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetTextureLevelParameteriv"));
        _nfx_glGetTextureParameterfv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLfloat*)>(loader.loadFunctionPtr("glGetTextureParameterfv"));
        _nfx_glGetTextureParameterIiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetTextureParameterIiv"));
        _nfx_glGetTextureParameterIuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint*)>(loader.loadFunctionPtr("glGetTextureParameterIuiv"));
        _nfx_glGetTextureParameteriv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetTextureParameteriv"));
        _nfx_glGetTextureSubImage = reinterpret_cast<GLvoid (*)(
            GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void*)>(
            loader.loadFunctionPtr("glGetTextureSubImage"));
        _nfx_glGetTransformFeedbacki64_v = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLint64*)>(
            loader.loadFunctionPtr("glGetTransformFeedbacki64_v"));
        _nfx_glGetTransformFeedbackiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetTransformFeedbackiv"));
        _nfx_glGetTransformFeedbacki_v = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLint*)>(
            loader.loadFunctionPtr("glGetTransformFeedbacki_v"));
        _nfx_glGetVertexArrayIndexed64iv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLint64*)>(
            loader.loadFunctionPtr("glGetVertexArrayIndexed64iv"));
        _nfx_glGetVertexArrayIndexediv = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetVertexArrayIndexediv"));
        _nfx_glGetVertexArrayiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetVertexArrayiv"));
        _nfx_glInvalidateNamedFramebufferData = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLenum*)>(
            loader.loadFunctionPtr("glInvalidateNamedFramebufferData"));
        _nfx_glInvalidateNamedFramebufferSubData =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLenum*, GLint, GLint, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glInvalidateNamedFramebufferSubData"));
        _nfx_glMapNamedBuffer =
            reinterpret_cast<GLvoid* (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glMapNamedBuffer"));
        _nfx_glMapNamedBufferRange = reinterpret_cast<GLvoid* (*)(GLuint, GLintptr, GLsizeiptr, GLbitfield)>(
            loader.loadFunctionPtr("glMapNamedBufferRange"));
        _nfx_glMemoryBarrierByRegion =
            reinterpret_cast<GLvoid (*)(GLbitfield)>(loader.loadFunctionPtr("glMemoryBarrierByRegion"));
        _nfx_glNamedBufferData = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLvoid*, GLenum)>(
            loader.loadFunctionPtr("glNamedBufferData"));
        _nfx_glNamedBufferStorage = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLvoid*, GLbitfield)>(
            loader.loadFunctionPtr("glNamedBufferStorage"));
        _nfx_glNamedBufferSubData = reinterpret_cast<GLvoid (*)(GLuint, GLintptr, GLsizei, const void*)>(
            loader.loadFunctionPtr("glNamedBufferSubData"));
        _nfx_glNamedFramebufferDrawBuffer =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glNamedFramebufferDrawBuffer"));
        _nfx_glNamedFramebufferDrawBuffers = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, const GLenum*)>(
            loader.loadFunctionPtr("glNamedFramebufferDrawBuffers"));
        _nfx_glNamedFramebufferParameteri =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint)>(loader.loadFunctionPtr("glNamedFramebufferParameteri"));
        _nfx_glNamedFramebufferReadBuffer =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glNamedFramebufferReadBuffer"));
        _nfx_glNamedFramebufferRenderbuffer = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLuint)>(
            loader.loadFunctionPtr("glNamedFramebufferRenderbuffer"));
        _nfx_glNamedFramebufferTexture = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLint)>(
            loader.loadFunctionPtr("glNamedFramebufferTexture"));
        _nfx_glNamedFramebufferTextureLayer = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLint, GLint)>(
            loader.loadFunctionPtr("glNamedFramebufferTextureLayer"));
        _nfx_glNamedRenderbufferStorage = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glNamedRenderbufferStorage"));
        _nfx_glNamedRenderbufferStorageMultisample =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glNamedRenderbufferStorageMultisample"));
        _nfx_glReadnPixels =
            reinterpret_cast<GLvoid (*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, GLvoid*)>(
                loader.loadFunctionPtr("glReadnPixels"));
        _nfx_glTextureBarrier = reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glTextureBarrier"));
        _nfx_glTextureBuffer =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint)>(loader.loadFunctionPtr("glTextureBuffer"));
        _nfx_glTextureBufferRange = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glTextureBufferRange"));
        _nfx_glTextureParameterf =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLfloat)>(loader.loadFunctionPtr("glTextureParameterf"));
        _nfx_glTextureParameterfv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLfloat*)>(
            loader.loadFunctionPtr("glTextureParameterfv"));
        _nfx_glTextureParameteri =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint)>(loader.loadFunctionPtr("glTextureParameteri"));
        _nfx_glTextureParameterIiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLint*)>(loader.loadFunctionPtr("glTextureParameterIiv"));
        _nfx_glTextureParameterIuiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLuint*)>(
            loader.loadFunctionPtr("glTextureParameterIuiv"));
        _nfx_glTextureParameteriv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLint*)>(loader.loadFunctionPtr("glTextureParameteriv"));
        _nfx_glTextureStorage1D = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei)>(
            loader.loadFunctionPtr("glTextureStorage1D"));
        _nfx_glTextureStorage2D = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glTextureStorage2D"));
        _nfx_glTextureStorage2DMultisample =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTextureStorage2DMultisample"));
        _nfx_glTextureStorage3D = reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glTextureStorage3D"));
        _nfx_glTextureStorage3DMultisample =
            reinterpret_cast<GLvoid (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTextureStorage3DMultisample"));
        _nfx_glTextureSubImage1D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid*)>(
                loader.loadFunctionPtr("glTextureSubImage1D"));
        _nfx_glTextureSubImage2D =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
                loader.loadFunctionPtr("glTextureSubImage2D"));
        _nfx_glTextureSubImage3D = reinterpret_cast<GLvoid (*)(
            GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(
            loader.loadFunctionPtr("glTextureSubImage3D"));
        _nfx_glTransformFeedbackBufferBase = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(
            loader.loadFunctionPtr("glTransformFeedbackBufferBase"));
        _nfx_glTransformFeedbackBufferRange =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr)>(
                loader.loadFunctionPtr("glTransformFeedbackBufferRange"));
        _nfx_glUnmapNamedBuffer = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glUnmapNamedBuffer"));
        _nfx_glVertexArrayAttribBinding =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glVertexArrayAttribBinding"));
        _nfx_glVertexArrayAttribFormat = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexArrayAttribFormat"));
        _nfx_glVertexArrayAttribIFormat = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLint, GLenum, GLuint)>(
            loader.loadFunctionPtr("glVertexArrayAttribIFormat"));
        _nfx_glVertexArrayAttribLFormat = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLint, GLenum, GLuint)>(
            loader.loadFunctionPtr("glVertexArrayAttribLFormat"));
        _nfx_glVertexArrayBindingDivisor =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glVertexArrayBindingDivisor"));
        _nfx_glVertexArrayElementBuffer =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glVertexArrayElementBuffer"));
        _nfx_glVertexArrayVertexBuffer = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint, GLintptr, GLsizei)>(
            loader.loadFunctionPtr("glVertexArrayVertexBuffer"));
        _nfx_glVertexArrayVertexBuffers =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLsizei, const GLuint*, const GLintptr*, const GLsizei*)>(
                loader.loadFunctionPtr("glVertexArrayVertexBuffers"));

        return s_loaded = true;
    }

    void Functions_4_5::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_4_4::teardown();
    }

    void Functions_4_5::nullifyPointers()
    {
        _nfx_glBindTextureUnit = nullptr;
        _nfx_glBlitNamedFramebuffer = nullptr;
        _nfx_glCheckNamedFramebufferStatus = nullptr;
        _nfx_glClearNamedBufferData = nullptr;
        _nfx_glClearNamedBufferSubData = nullptr;
        _nfx_glClearNamedFramebufferfi = nullptr;
        _nfx_glClearNamedFramebufferfv = nullptr;
        _nfx_glClearNamedFramebufferiv = nullptr;
        _nfx_glClearNamedFramebufferuiv = nullptr;
        _nfx_glClipControl = nullptr;
        _nfx_glCompressedTextureSubImage1D = nullptr;
        _nfx_glCompressedTextureSubImage2D = nullptr;
        _nfx_glCompressedTextureSubImage3D = nullptr;
        _nfx_glCopyNamedBufferSubData = nullptr;
        _nfx_glCopyTextureSubImage1D = nullptr;
        _nfx_glCopyTextureSubImage2D = nullptr;
        _nfx_glCopyTextureSubImage3D = nullptr;
        _nfx_glCreateBuffers = nullptr;
        _nfx_glCreateFramebuffers = nullptr;
        _nfx_glCreateProgramPipelines = nullptr;
        _nfx_glCreateQueries = nullptr;
        _nfx_glCreateRenderbuffers = nullptr;
        _nfx_glCreateSamplers = nullptr;
        _nfx_glCreateTextures = nullptr;
        _nfx_glCreateTransformFeedbacks = nullptr;
        _nfx_glCreateVertexArrays = nullptr;
        _nfx_glDisableVertexArrayAttrib = nullptr;
        _nfx_glEnableVertexArrayAttrib = nullptr;
        _nfx_glFlushMappedNamedBufferRange = nullptr;
        _nfx_glGenerateTextureMipmap = nullptr;
        _nfx_glGetCompressedTextureImage = nullptr;
        _nfx_glGetCompressedTextureSubImage = nullptr;
        _nfx_glGetGraphicsResetStatus = nullptr;
        _nfx_glGetNamedBufferParameteri64v = nullptr;
        _nfx_glGetNamedBufferParameteriv = nullptr;
        _nfx_glGetNamedBufferPointerv = nullptr;
        _nfx_glGetNamedBufferSubData = nullptr;
        _nfx_glGetNamedFramebufferAttachmentParameteriv = nullptr;
        _nfx_glGetNamedFramebufferParameteriv = nullptr;
        _nfx_glGetNamedRenderbufferParameteriv = nullptr;
        _nfx_glGetnCompressedTexImage = nullptr;
        _nfx_glGetnTexImage = nullptr;
        _nfx_glGetnUniformdv = nullptr;
        _nfx_glGetnUniformfv = nullptr;
        _nfx_glGetnUniformiv = nullptr;
        _nfx_glGetnUniformuiv = nullptr;
        _nfx_glGetQueryBufferObjecti64v = nullptr;
        _nfx_glGetQueryBufferObjectiv = nullptr;
        _nfx_glGetQueryBufferObjectui64v = nullptr;
        _nfx_glGetQueryBufferObjectuiv = nullptr;
        _nfx_glGetTextureImage = nullptr;
        _nfx_glGetTextureLevelParameterfv = nullptr;
        _nfx_glGetTextureLevelParameteriv = nullptr;
        _nfx_glGetTextureParameterfv = nullptr;
        _nfx_glGetTextureParameterIiv = nullptr;
        _nfx_glGetTextureParameterIuiv = nullptr;
        _nfx_glGetTextureParameteriv = nullptr;
        _nfx_glGetTextureSubImage = nullptr;
        _nfx_glGetTransformFeedbacki64_v = nullptr;
        _nfx_glGetTransformFeedbackiv = nullptr;
        _nfx_glGetTransformFeedbacki_v = nullptr;
        _nfx_glGetVertexArrayIndexed64iv = nullptr;
        _nfx_glGetVertexArrayIndexediv = nullptr;
        _nfx_glGetVertexArrayiv = nullptr;
        _nfx_glInvalidateNamedFramebufferData = nullptr;
        _nfx_glInvalidateNamedFramebufferSubData = nullptr;
        _nfx_glMapNamedBuffer = nullptr;
        _nfx_glMapNamedBufferRange = nullptr;
        _nfx_glMemoryBarrierByRegion = nullptr;
        _nfx_glNamedBufferData = nullptr;
        _nfx_glNamedBufferStorage = nullptr;
        _nfx_glNamedBufferSubData = nullptr;
        _nfx_glNamedFramebufferDrawBuffer = nullptr;
        _nfx_glNamedFramebufferDrawBuffers = nullptr;
        _nfx_glNamedFramebufferParameteri = nullptr;
        _nfx_glNamedFramebufferReadBuffer = nullptr;
        _nfx_glNamedFramebufferRenderbuffer = nullptr;
        _nfx_glNamedFramebufferTexture = nullptr;
        _nfx_glNamedFramebufferTextureLayer = nullptr;
        _nfx_glNamedRenderbufferStorage = nullptr;
        _nfx_glNamedRenderbufferStorageMultisample = nullptr;
        _nfx_glReadnPixels = nullptr;
        _nfx_glTextureBarrier = nullptr;
        _nfx_glTextureBuffer = nullptr;
        _nfx_glTextureBufferRange = nullptr;
        _nfx_glTextureParameterf = nullptr;
        _nfx_glTextureParameterfv = nullptr;
        _nfx_glTextureParameteri = nullptr;
        _nfx_glTextureParameteriv = nullptr;
        _nfx_glTextureParameterIiv = nullptr;
        _nfx_glTextureParameterIuiv = nullptr;
        _nfx_glTextureStorage1D = nullptr;
        _nfx_glTextureStorage2D = nullptr;
        _nfx_glTextureStorage3D = nullptr;
        _nfx_glTextureStorage2DMultisample = nullptr;
        _nfx_glTextureStorage3DMultisample = nullptr;
        _nfx_glTextureSubImage1D = nullptr;
        _nfx_glTextureSubImage2D = nullptr;
        _nfx_glTextureSubImage3D = nullptr;
        _nfx_glTransformFeedbackBufferBase = nullptr;
        _nfx_glTransformFeedbackBufferRange = nullptr;
        _nfx_glUnmapNamedBuffer = nullptr;
        _nfx_glVertexArrayAttribBinding = nullptr;
        _nfx_glVertexArrayAttribFormat = nullptr;
        _nfx_glVertexArrayAttribIFormat = nullptr;
        _nfx_glVertexArrayAttribLFormat = nullptr;
        _nfx_glVertexArrayBindingDivisor = nullptr;
        _nfx_glVertexArrayElementBuffer = nullptr;
        _nfx_glVertexArrayVertexBuffer = nullptr;
        _nfx_glVertexArrayVertexBuffers = nullptr;
    }
} // namespace nfx::graphics::gl
