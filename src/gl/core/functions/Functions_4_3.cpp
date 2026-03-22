#include "nfx/graphics/gl/core/functions/Functions_4_3.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_4_3::Functions_4_3()
        : Functions_4_2{}
    {}

    Functions_4_3::~Functions_4_3() {}

    GLvoid Functions_4_3::glBindVertexBuffer(
        GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindVertexBuffer(bindingindex, buffer, offset, stride), caller);
    }

    GLvoid Functions_4_3::glClearBufferData(
        GLenum target,
        GLenum internalformat,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glClearBufferData(target, internalformat, format, type, data), caller);
    }

    GLvoid Functions_4_3::glClearBufferSubData(
        GLenum target,
        GLenum internalformat,
        GLintptr offset,
        GLsizeiptr size,
        GLenum format,
        GLenum type,
        const GLvoid* data,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glClearBufferSubData(target, internalformat, offset, size, format, type, data), caller);
    }

    GLvoid Functions_4_3::glCopyImageSubData(
        GLuint srcName,
        GLenum srcTarget,
        GLint srcLevel,
        GLint srcX,
        GLint srcY,
        GLint srcZ,
        GLuint dstName,
        GLenum dstTarget,
        GLint dstLevel,
        GLint dstX,
        GLint dstY,
        GLint dstZ,
        GLsizei srcWidth,
        GLsizei srcHeight,
        GLsizei srcDepth,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glCopyImageSubData(
                srcName,
                srcTarget,
                srcLevel,
                srcX,
                srcY,
                srcZ,
                dstName,
                dstTarget,
                dstLevel,
                dstX,
                dstY,
                dstZ,
                srcWidth,
                srcHeight,
                srcDepth),
            caller);
    }

    GLvoid Functions_4_3::glDebugMessageCallback(
        GLDEBUGPROC callback, const GLvoid* userParam, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDebugMessageCallback(callback, userParam), caller);
    }

    GLvoid Functions_4_3::glDebugMessageControl(
        GLenum source,
        GLenum type,
        GLenum severity,
        GLsizei count,
        const GLuint* ids,
        GLboolean enabled,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDebugMessageControl(source, type, severity, count, ids, enabled), caller);
    }

    GLvoid Functions_4_3::glDebugMessageInsert(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* buf,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDebugMessageInsert(source, type, id, severity, length, buf), caller);
    }

    GLvoid Functions_4_3::glDispatchCompute(
        GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z), caller);
    }

    GLvoid Functions_4_3::glDispatchComputeIndirect(GLintptr indirect, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDispatchComputeIndirect(indirect), caller);
    }

    GLvoid Functions_4_3::glFramebufferParameteri(
        GLenum target, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glFramebufferParameteri(target, pname, param), caller);
    }

    GLuint Functions_4_3::glGetDebugMessageLog(
        GLuint count,
        GLsizei bufSize,
        GLenum* sources,
        GLenum* types,
        GLuint* ids,
        GLenum* severities,
        GLsizei* lengths,
        GLchar* messageLog,
        [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(
            ret = _nfx_glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog),
            caller);

        return ret;
    }

    GLvoid Functions_4_3::glGetFramebufferParameteriv(
        GLenum target, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetFramebufferParameteriv(target, pname, params), caller);
    }

    GLvoid Functions_4_3::glGetInternalformati64v(
        GLenum target,
        GLenum internalformat,
        GLenum pname,
        GLsizei count,
        GLint64* params,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetInternalformati64v(target, internalformat, pname, count, params), caller);
    }

    GLvoid Functions_4_3::glGetObjectLabel(
        GLenum identifier,
        GLuint name,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* label,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetObjectLabel(identifier, name, bufSize, length, label), caller);
    }

    GLvoid Functions_4_3::glGetObjectPtrLabel(
        const GLvoid* ptr, GLsizei bufSize, GLsizei* length, GLchar* label, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetObjectPtrLabel(ptr, bufSize, length, label), caller);
    }

    GLvoid Functions_4_3::glGetProgramInterfaceiv(
        GLuint program, GLenum programInterface, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetProgramInterfaceiv(program, programInterface, pname, params), caller);
    }

    GLuint Functions_4_3::glGetProgramResourceIndex(
        GLuint program, GLenum programInterface, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLuint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetProgramResourceIndex(program, programInterface, name), caller);

        return ret;
    }

    GLvoid Functions_4_3::glGetProgramResourceiv(
        GLuint program,
        GLenum programInterface,
        GLuint index,
        GLsizei propCount,
        const GLenum* props,
        GLsizei count,
        GLsizei* length,
        GLint* params,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params),
            caller);
    }

    GLint Functions_4_3::glGetProgramResourceLocation(
        GLuint program, GLenum programInterface, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glGetProgramResourceLocation(program, programInterface, name), caller);

        return ret;
    }

    GLint Functions_4_3::glGetProgramResourceLocationIndex(
        GLuint program, GLenum programInterface, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        GLint ret{ 0 };

        NFX_GRAPHICS_GL_CHECK_ERROR(
            ret = _nfx_glGetProgramResourceLocationIndex(program, programInterface, name), caller);

        return ret;
    }

    GLvoid Functions_4_3::glGetProgramResourceName(
        GLuint program,
        GLenum programInterface,
        GLuint index,
        GLsizei bufSize,
        GLsizei* length,
        GLchar* name,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glGetProgramResourceName(program, programInterface, index, bufSize, length, name), caller);
    }

    GLvoid Functions_4_3::glInvalidateBufferData(GLuint buffer, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glInvalidateBufferData(buffer), caller);
    }

    GLvoid Functions_4_3::glInvalidateBufferSubData(
        GLuint buffer, GLintptr offset, GLsizeiptr length, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glInvalidateBufferSubData(buffer, offset, length), caller);
    }

    GLvoid Functions_4_3::glInvalidateFramebuffer(
        GLenum target, GLsizei numAttachments, const GLenum* attachments, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glInvalidateFramebuffer(target, numAttachments, attachments), caller);
    }

    GLvoid Functions_4_3::glInvalidateSubFramebuffer(
        GLenum target,
        GLsizei numAttachments,
        const GLenum* attachments,
        GLint x,
        GLint y,
        GLsizei width,
        GLsizei height,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height), caller);
    }

    GLvoid Functions_4_3::glInvalidateTexImage(GLuint texture, GLint level, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glInvalidateTexImage(texture, level), caller);
    }

    GLvoid Functions_4_3::glInvalidateTexSubImage(
        GLuint texture,
        GLint level,
        GLint xoffset,
        GLint yoffset,
        GLint zoffset,
        GLsizei width,
        GLsizei height,
        GLsizei depth,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth), caller);
    }

    GLvoid Functions_4_3::glMultiDrawArraysIndirect(
        GLenum mode,
        const GLvoid* indirect,
        GLsizei drawcount,
        GLsizei stride,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiDrawArraysIndirect(mode, indirect, drawcount, stride), caller);
    }

    GLvoid Functions_4_3::glMultiDrawElementsIndirect(
        GLenum mode,
        GLenum type,
        const GLvoid* indirect,
        GLsizei drawcount,
        GLsizei stride,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride), caller);
    }

    GLvoid Functions_4_3::glObjectLabel(
        GLenum identifier, GLuint name, GLsizei length, const GLchar* label, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glObjectLabel(identifier, name, length, label), caller);
    }

    GLvoid Functions_4_3::glObjectPtrLabel(
        const GLvoid* ptr, GLsizei length, const GLchar* label, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glObjectPtrLabel(ptr, length, label), caller);
    }

    GLvoid Functions_4_3::glPopDebugGroup([[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPopDebugGroup(), caller);
    }

    GLvoid Functions_4_3::glPushDebugGroup(
        GLenum source, GLuint id, GLsizei length, const GLchar* message, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glPushDebugGroup(source, id, length, message), caller);
    }

    GLvoid Functions_4_3::glShaderStorageBlockBinding(
        GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding), caller);
    }

    GLvoid Functions_4_3::glTexBufferRange(
        GLenum target,
        GLenum internalformat,
        GLuint buffer,
        GLintptr offset,
        GLsizeiptr size,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexBufferRange(target, internalformat, buffer, offset, size), caller);
    }

    GLvoid Functions_4_3::glTexStorage2DMultisample(
        GLenum target,
        GLsizei samples,
        GLenum internalformat,
        GLsizei width,
        GLsizei height,
        GLboolean fixedsamplelocations,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations),
            caller);
    }

    GLvoid Functions_4_3::glTexStorage3DMultisample(
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
            _nfx_glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations),
            caller);
    }

    GLvoid Functions_4_3::glTextureView(
        GLuint texture,
        GLenum target,
        GLuint origtexture,
        GLenum internalformat,
        GLuint minlevel,
        GLuint numlevels,
        GLuint minlayer,
        GLuint numlayers,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers),
            caller);
    }

    GLvoid Functions_4_3::glVertexAttribBinding(
        GLuint attribindex, GLuint bindingindex, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribBinding(attribindex, bindingindex), caller);
    }

    GLvoid Functions_4_3::glVertexAttribFormat(
        GLuint attribindex,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLuint relativeoffset,
        [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(
            _nfx_glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset), caller);
    }

    GLvoid Functions_4_3::glVertexAttribIFormat(
        GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribIFormat(attribindex, size, type, relativeoffset), caller);
    }

    GLvoid Functions_4_3::glVertexAttribLFormat(
        GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribLFormat(attribindex, size, type, relativeoffset), caller);
    }

    GLvoid Functions_4_3::glVertexBindingDivisor(
        GLuint bindingindex, GLuint divisor, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexBindingDivisor(bindingindex, divisor), caller);
    }

    bool Functions_4_3::initialize()
    {
        Functions_4_2::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBindVertexBuffer = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLintptr, GLsizei)>(
            loader.loadFunctionPtr("glBindVertexBuffer"));
        _nfx_glClearBufferData = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLenum, const void*)>(
            loader.loadFunctionPtr("glClearBufferData"));
        _nfx_glClearBufferSubData =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void*)>(
                loader.loadFunctionPtr("glClearBufferSubData"));
        _nfx_glCopyImageSubData = reinterpret_cast<GLvoid (*)(
            GLuint,
            GLenum,
            GLint,
            GLint,
            GLint,
            GLint,
            GLuint,
            GLenum,
            GLint,
            GLint,
            GLint,
            GLint,
            GLsizei,
            GLsizei,
            GLsizei)>(loader.loadFunctionPtr("glCopyImageSubData"));
        _nfx_glDebugMessageCallback =
            reinterpret_cast<GLvoid (*)(GLDEBUGPROC, const GLvoid*)>(loader.loadFunctionPtr("glDebugMessageCallback"));
        _nfx_glDebugMessageControl =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint*, GLboolean)>(
                loader.loadFunctionPtr("glDebugMessageControl"));
        _nfx_glDebugMessageInsert =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*)>(
                loader.loadFunctionPtr("glDebugMessageInsert"));
        _nfx_glDispatchCompute =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glDispatchCompute"));
        _nfx_glDispatchComputeIndirect =
            reinterpret_cast<GLvoid (*)(GLintptr)>(loader.loadFunctionPtr("glDispatchComputeIndirect"));
        _nfx_glFramebufferParameteri =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint)>(loader.loadFunctionPtr("glFramebufferParameteri"));
        _nfx_glGetDebugMessageLog =
            reinterpret_cast<GLuint (*)(GLuint, GLsizei, GLenum*, GLenum*, GLuint*, GLenum*, GLsizei*, GLchar*)>(
                loader.loadFunctionPtr("glGetDebugMessageLog"));
        _nfx_glGetFramebufferParameteriv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLint*)>(loader.loadFunctionPtr("glGetFramebufferParameteriv"));
        _nfx_glGetInternalformati64v = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLenum, GLsizei, GLint64*)>(
            loader.loadFunctionPtr("glGetInternalformati64v"));
        _nfx_glGetObjectLabel = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetObjectLabel"));
        _nfx_glGetObjectPtrLabel = reinterpret_cast<GLvoid (*)(const GLvoid*, GLsizei, GLsizei*, GLchar*)>(
            loader.loadFunctionPtr("glGetObjectPtrLabel"));
        _nfx_glGetProgramInterfaceiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLenum, GLint*)>(
            loader.loadFunctionPtr("glGetProgramInterfaceiv"));
        _nfx_glGetProgramResourceIndex = reinterpret_cast<GLuint (*)(GLuint, GLenum, const GLchar*)>(
            loader.loadFunctionPtr("glGetProgramResourceIndex"));
        _nfx_glGetProgramResourceiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLsizei, const GLenum*, GLsizei, GLsizei*, GLint*)>(
                loader.loadFunctionPtr("glGetProgramResourceiv"));
        _nfx_glGetProgramResourceLocation = reinterpret_cast<GLint (*)(GLuint, GLenum, const GLchar* name)>(
            loader.loadFunctionPtr("glGetProgramResourceLocation"));
        _nfx_glGetProgramResourceLocationIndex = reinterpret_cast<GLint (*)(GLuint, GLenum, const GLchar*)>(
            loader.loadFunctionPtr("glGetProgramResourceLocationIndex"));
        _nfx_glGetProgramResourceName =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*)>(
                loader.loadFunctionPtr("glGetProgramResourceName"));
        _nfx_glInvalidateBufferData =
            reinterpret_cast<GLvoid (*)(GLuint)>(loader.loadFunctionPtr("glInvalidateBufferData"));
        _nfx_glInvalidateBufferSubData = reinterpret_cast<GLvoid (*)(GLuint, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glInvalidateBufferSubData"));
        _nfx_glInvalidateFramebuffer = reinterpret_cast<GLvoid (*)(GLenum, GLsizei, const GLenum*)>(
            loader.loadFunctionPtr("glInvalidateFramebuffer"));
        _nfx_glInvalidateSubFramebuffer =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, const GLenum*, GLint, GLint, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glInvalidateSubFramebuffer"));
        _nfx_glInvalidateTexImage =
            reinterpret_cast<GLvoid (*)(GLuint, GLint)>(loader.loadFunctionPtr("glInvalidateTexImage"));
        _nfx_glInvalidateTexSubImage =
            reinterpret_cast<GLvoid (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei)>(
                loader.loadFunctionPtr("glInvalidateTexSubImage"));
        _nfx_glMultiDrawArraysIndirect = reinterpret_cast<GLvoid (*)(GLenum, const void*, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glMultiDrawArraysIndirect"));
        _nfx_glMultiDrawElementsIndirect = reinterpret_cast<GLvoid (*)(GLenum, GLenum, const void*, GLsizei, GLsizei)>(
            loader.loadFunctionPtr("glMultiDrawElementsIndirect"));
        _nfx_glObjectLabel = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei, const GLchar*)>(
            loader.loadFunctionPtr("glObjectLabel"));
        _nfx_glObjectPtrLabel = reinterpret_cast<GLvoid (*)(const GLvoid*, GLsizei, const GLchar*)>(
            loader.loadFunctionPtr("glObjectPtrLabel"));
        _nfx_glPopDebugGroup = reinterpret_cast<GLvoid (*)()>(loader.loadFunctionPtr("glPopDebugGroup"));
        _nfx_glPushDebugGroup = reinterpret_cast<GLvoid (*)(GLenum, GLuint, GLsizei, const GLchar*)>(
            loader.loadFunctionPtr("glPushDebugGroup"));
        _nfx_glShaderStorageBlockBinding =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint)>(loader.loadFunctionPtr("glShaderStorageBlockBinding"));
        _nfx_glTexBufferRange = reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr)>(
            loader.loadFunctionPtr("glTexBufferRange"));
        _nfx_glTexStorage2DMultisample =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTexStorage2DMultisample"));
        _nfx_glTexStorage3DMultisample =
            reinterpret_cast<GLvoid (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean)>(
                loader.loadFunctionPtr("glTexStorage3DMultisample"));
        _nfx_glTextureView =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint)>(
                loader.loadFunctionPtr("glTextureView"));
        _nfx_glVertexAttribBinding =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glVertexAttribBinding"));
        _nfx_glVertexAttribFormat = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribFormat"));
        _nfx_glVertexAttribIFormat = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribIFormat"));
        _nfx_glVertexAttribLFormat = reinterpret_cast<GLvoid (*)(GLuint, GLint, GLenum, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribLFormat"));
        _nfx_glVertexBindingDivisor =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glVertexBindingDivisor"));

        return s_loaded = true;
    }
} // namespace nfx::graphics::gl
