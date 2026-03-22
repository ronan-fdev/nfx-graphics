#pragma once

/**
 * \file Functions_3_2.h
 * \brief Declares the OpenGL 3.2 function wrapper interface.
 */

#include "Functions_3_1.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_3_2
     * \brief Exposes the OpenGL 3.2 function set.
     */
    class Functions_3_2 : public Functions_3_1
    {
        static inline bool s_loaded;

    public:
        explicit Functions_3_2();
        Functions_3_2(const Functions_3_2&) = delete;
        Functions_3_2& operator=(const Functions_3_2&) = delete;
        Functions_3_2(Functions_3_2&&) = delete;
        Functions_3_2& operator=(Functions_3_2&&) = delete;
        virtual ~Functions_3_2();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glClientWaitSync function causes the client to block and wait for a sync object to become
         * signaled.
         * \deprecated Deprecated in OpenGL 4.5. Use glClientWaitSyncKHR instead.
         *
         * \param sync Specifies the sync object whose status to wait on.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param flags Specifies a bitfield controlling the command flushing behavior.
         * Accepted values are 0.
         * \param timeout Specifies the timeout that the client should wait before returning.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The glClientWaitSync function returns a status value indicating the result of the wait.
         * Possible return values are GL_ALREADY_SIGNALED, GL_TIMEOUT_EXPIRED, GL_CONDITION_SATISFIED, and
         * GL_WAIT_FAILED.
         */
        GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteSync function deletes a sync object.
         * \deprecated Deprecated in OpenGL 4.5. Use glDeleteSyncKHR instead.
         *
         * \param sync Specifies the sync object to be deleted.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteSync(GLsync sync, const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsBaseVertex function renders primitives from array data with a per-element offset.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param basevertex Specifies a constant that should be added to each element of indices when choosing
         * elements from the enabled vertex arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsBaseVertex(
            GLenum mode,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLint basevertex,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsInstancedBaseVertex function renders multiple instances of a set of primitives
         * from array data with a per-element offset.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param basevertex Specifies a constant that should be added to each element of indices when choosing
         * elements from the enabled vertex arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsInstancedBaseVertex(
            GLenum mode,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLsizei instancecount,
            GLint basevertex,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawRangeElementsBaseVertex function renders primitives from array data with a per-element
         * offset, specifying a range of indices.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES.
         * \param start Specifies the minimum array index contained in indices.
         * \param end Specifies the maximum array index contained in indices.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param basevertex Specifies a constant that should be added to each element of indices when choosing
         * elements from the enabled vertex arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawRangeElementsBaseVertex(
            GLenum mode,
            GLuint start,
            GLuint end,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLint basevertex,
            const char* caller = nullptr) const;

        /**
         * \brief The glFenceSync function creates a new sync object and inserts it into the GL command stream.
         * \deprecated Deprecated in OpenGL 4.5. Use glFenceSyncKHR instead.
         *
         * \param condition Specifies the condition that must be met to set the sync object to the signaled state.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param flags Specifies a bitfield controlling the behavior of the sync object.
         * Accepted values are 0.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The glFenceSync function returns a handle to the new sync object.
         */
        GLsync glFenceSync(GLenum condition, GLbitfield flags, const char* caller = nullptr) const;

        /**
         * \brief The glGetFragDataIndex function retrieves the index of a user-defined varying out variable.
         *
         * \param program Specifies the name of the program containing varying out variable whose index is to be
         * queried.
         * \param name Specifies the name of the user-defined varying out variable whose index is to be queried.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The index of the user-defined varying out variable.
         */
        GLint glGetFragDataIndex(GLuint program, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferTexture function attaches a level of a texture object as a logical buffer to the
         * currently bound framebuffer object.
         *
         * \param target Specifies the framebuffer target.
         * \param attachment Specifies the attachment point of the framebuffer.
         * \param texture Specifies the texture object to attach.
         * \param level Specifies the mipmap level of the texture object to attach.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferTexture(
            GLenum target, GLenum attachment, GLuint texture, GLint level, const char* caller = nullptr) const;

        /**
         * \brief The glGetBufferParameteri64v function returns a parameter from a buffer object.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         * GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
         * GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param pname Specifies the symbolic name of a buffer object parameter.
         * Accepted values are GL_BUFFER_ACCESS, GL_BUFFER_ACCESS_FLAGS, GL_BUFFER_IMMUTABLE_STORAGE,
         * GL_BUFFER_MAPPED, GL_BUFFER_MAP_LENGTH, GL_BUFFER_MAP_OFFSET, GL_BUFFER_SIZE, GL_BUFFER_STORAGE_FLAGS,
         * GL_BUFFER_USAGE.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBufferParameteri64v(
            GLenum target, GLenum pname, GLint64* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetInteger64i_v function returns the value of a selected parameter.
         *
         * \param target Specifies the symbolic name of a parameter.
         * Accepted values are GL_MAX_COMPUTE_WORK_GROUP_COUNT, GL_MAX_COMPUTE_WORK_GROUP_SIZE,
         * GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, GL_MAX_COMPUTE_UNIFORM_BLOCKS,
         * GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, GL_MAX_COMPUTE_IMAGE_UNIFORMS, GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
         * GL_MAX_COMPUTE_ATOMIC_COUNTERS, GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
         * GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB, GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB,
         * GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB, GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB.
         * \param index Specifies the index of the parameter to be returned.
         * \param data Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetInteger64i_v(GLenum target, GLuint index, GLint64* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetInteger64v function returns the value of a selected parameter.
         *
         * \param pname Specifies the symbolic name of a parameter.
         * Accepted values are GL_MAX_COMPUTE_WORK_GROUP_COUNT, GL_MAX_COMPUTE_WORK_GROUP_SIZE,
         * GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, GL_MAX_COMPUTE_UNIFORM_BLOCKS,
         * GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, GL_MAX_COMPUTE_IMAGE_UNIFORMS, GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
         * GL_MAX_COMPUTE_ATOMIC_COUNTERS, GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
         * GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB, GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB,
         * GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB, GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB.
         * \param data Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetInteger64v(GLenum pname, GLint64* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetMultisamplefv function retrieves the location of a sample.
         *
         * \param pname Specifies the sample parameter name.
         * Accepted values are GL_SAMPLE_POSITION.
         * \param index Specifies the index of the sample.
         * \param val Specifies a pointer to a variable that will receive the sample location.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMultisamplefv(GLenum pname, GLuint index, GLfloat* val, const char* caller = nullptr) const;

        /**
         * \brief The glGetSynciv function returns properties of a sync object.
         * \deprecated Deprecated in OpenGL 4.5. Use glGetSyncivKHR instead.
         *
         * \param sync Specifies the sync object whose properties are to be queried.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param pname Specifies the parameter whose value to retrieve.
         * Accepted values are GL_OBJECT_TYPE, GL_SYNC_CONDITION, GL_SYNC_STATUS, GL_SYNC_FLAGS.
         * \param count Specifies the size of the buffer whose address is given in values.
         * \param length Specifies the address of a variable to receive the number of integers placed in values.
         * \param values Specifies the address of an array to receive the values of the queried parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSynciv(
            GLsync sync, GLenum pname, GLsizei count, GLsizei* length, GLint* values, const char* caller = nullptr)
            const;

        /**
         * \brief The glIsSync function determines if a name corresponds to a sync object.
         * \deprecated Deprecated in OpenGL 4.5. Use glIsSyncKHR instead.
         *
         * \param sync Specifies a value that may be the name of a sync object.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if sync is a sync object, GL_FALSE otherwise.
         */
        GLboolean glIsSync(GLsync sync, const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawElementsBaseVertex function renders multiple sets of primitives by specifying indices
         * of array data elements with a per-element offset.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES.
         * \param count Specifies an array of the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT.
         * \param indices Specifies an array of pointers to the location where the indices are stored.
         * \param drawcount Specifies the size of the count and indices arrays.
         * \param basevertex Specifies an array of constants that should be added to each element of indices when
         * choosing elements from the enabled vertex arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawElementsBaseVertex(
            GLenum mode,
            const GLsizei* count,
            GLenum type,
            const GLvoid* const* indices,
            GLsizei drawcount,
            const GLint* basevertex,
            const char* caller = nullptr) const;

        /**
         * \brief The glProvokingVertex function specifies the vertex to be used as the source of data for flat
         * shading.
         *
         * \param mode Specifies the provoking vertex mode.
         * Accepted values are GL_FIRST_VERTEX_CONVENTION, GL_LAST_VERTEX_CONVENTION.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProvokingVertex(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glSampleMaski function specifies the sample coverage mask for a sample.
         *
         * \param maskNumber Specifies the index of the sample coverage mask to update.
         * \param mask Specifies the bitfield to enable and disable coverage of individual samples.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSampleMaski(GLuint maskNumber, GLbitfield mask, const char* caller = nullptr) const;

        /**
         * \brief The glTexImage2DMultisample function specifies a two-dimensional multisample texture.
         *
         * \param target  Specifies the target of the operation. Must be GL_TEXTURE_2D_MULTISAMPLE.
         * \param samples  Specifies the number of samples in the multisample texture's image.
         * \param internalformat Specifies the internal format to be used to store the multisample texture's
         * image. Accepted values are GL_R8, GL_R8_SNORM, GL_R16, GL_R16_SNORM, GL_RG8, GL_RG8_SNORM, GL_RG16,
         * GL_RG16_SNORM, GL_R3_G3_B2, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB8_SNORM, GL_RGB10, GL_RGB12, GL_RGB16_SNORM,
         * GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGBA8_SNORM, GL_RGB10_A2, GL_RGB10_A2UI, GL_RGBA12, GL_RGBA16,
         * GL_SRGB8, GL_SRGB8_ALPHA8, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F, GL_R32F, GL_RG32F, GL_RGB32F,
         * GL_RGBA32F, GL_R11F_G11F_B10F, GL_RGB9_E5, GL_R8I, GL_R8UI, GL_R16I, GL_R16UI, GL_R32I, GL_R32UI, GL_RG8I,
         * GL_RG8UI, GL_RG16I, GL_RG16UI, GL_RG32I, GL_RG32UI, GL_RGB8I, GL_RGB8UI, GL_RGB16I, GL_RGB16UI, GL_RGB32I,
         * GL_RGB32UI, GL_RGBA8I, GL_RGBA8UI, GL_RGBA16I, GL_RGBA16UI, GL_RGBA32I, GL_RGBA32UI, GL_DEPTH_COMPONENT16,
         * GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8,
         * GL_STENCIL_INDEX1, GL_STENCIL_INDEX4, GL_STENCIL_INDEX8, GL_STENCIL_INDEX16.
         * \param width  Specifies the width of the multisample texture's image.
         * \param height  Specifies the height of the multisample texture's image.
         * \param fixedsamplelocations Specifies whether the image will use identical sample locations and the same
         * number of samples for all texels in the image.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTexImage2DMultisample(
            GLenum target,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexImage3DMultisample function specifies a three-dimensional multisample texture.
         *
         * \param target  Specifies the target of the operation. Must be GL_TEXTURE_3D_MULTISAMPLE.
         * \param samples  Specifies the number of samples in the multisample texture's image.
         * \param internalformat Specifies the internal format to be used to store the multisample texture's
         * image. Accepted values are GL_R8, GL_R8_SNORM, GL_R16, GL_R16_SNORM, GL_RG8, GL_RG8_SNORM, GL_RG16,
         * GL_RG16_SNORM, GL_R3_G3_B2, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB8_SNORM, GL_RGB10, GL_RGB12, GL_RGB16_SNORM,
         * GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGBA8_SNORM, GL_RGB10_A2, GL_RGB10_A2UI, GL_RGBA12, GL_RGBA16,
         * GL_SRGB8, GL_SRGB8_ALPHA8, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F, GL_R32F, GL_RG32F, GL_RGB32F,
         * GL_RGBA32F, GL_R11F_G11F_B10F, GL_RGB9_E5, GL_R8I, GL_R8UI, GL_R16I, GL_R16UI, GL_R32I, GL_R32UI, GL_RG8I,
         * GL_RG8UI, GL_RG16I, GL_RG16UI, GL_RG32I, GL_RG32UI, GL_RGB8I, GL_RGB8UI, GL_RGB16I, GL_RGB16UI, GL_RGB32I,
         * GL_RGB32UI, GL_RGBA8I, GL_RGBA8UI, GL_RGBA16I, GL_RGBA16UI, GL_RGBA32I, GL_RGBA32UI, GL_DEPTH_COMPONENT16,
         * GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8,
         * GL_STENCIL_INDEX1, GL_STENCIL_INDEX4, GL_STENCIL_INDEX8, GL_STENCIL_INDEX16.
         * \param width  Specifies the width of the multisample texture's image.
         * \param height  Specifies the height of the multisample texture's image.
         * \param depth  Specifies the depth of the multisample texture's image.
         * \param fixedsamplelocations Specifies whether the image will use identical sample locations and the same
         * number of samples for all texels in the image.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTexImage3DMultisample(
            GLenum target,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glWaitSync function causes the GL server to block and wait for a sync object to become signaled.
         * \deprecated Deprecated in OpenGL 4.5. Use glWaitSyncKHR instead.
         *
         * \param sync Specifies the sync object whose status to wait on.
         * Accepted values are GL_SYNC_GPU_COMMANDS_COMPLETE.
         * \param flags Specifies a bitfield controlling the command flushing behavior.
         * Accepted values are 0.
         * \param timeout Specifies the timeout that the server should wait before returning.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
