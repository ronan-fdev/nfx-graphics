#pragma once

/**
 * \file Functions_4_4.h
 * \brief Declares the OpenGL 4.4 function wrapper interface.
 */

#include "Functions_4_3.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_4
     * \brief Exposes the OpenGL 4.4 function set.
     */
    class Functions_4_4 : public Functions_4_3
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_4();
        Functions_4_4(const Functions_4_4&) = delete;
        Functions_4_4& operator=(const Functions_4_4&) = delete;
        Functions_4_4(Functions_4_4&&) = delete;
        Functions_4_4& operator=(Functions_4_4&&) = delete;
        virtual ~Functions_4_4();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBindBuffersBase function binds a range of buffer objects to a specified binding point.
         *
         * \param target Specifies the target to which the buffers are bound.
         * Accepted values are GL_ATOMIC_COUNTER_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER,
         * GL_UNIFORM_BUFFER, and GL_SHADER_STORAGE_BUFFER.
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which buffers are to be bound.
         * \param buffers Specifies an array of names of buffer objects to be bound.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindBuffersBase(
            GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const char* caller = nullptr) const;

        /**
         * \brief The glBindBuffersRange function binds a range of buffer objects to a specified binding point with
         * specified offsets and sizes.
         *
         * \param target Specifies the target to which the buffers are bound.
         * Accepted values are GL_ATOMIC_COUNTER_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER,
         * GL_UNIFORM_BUFFER, and GL_SHADER_STORAGE_BUFFER.
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which buffers are to be bound.
         * \param buffers Specifies an array of names of buffer objects to be bound.
         * \param offsets Specifies an array of offsets within the buffers.
         * \param sizes Specifies an array of sizes of the buffers.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindBuffersRange(
            GLenum target,
            GLuint first,
            GLsizei count,
            const GLuint* buffers,
            const GLintptr* offsets,
            const GLsizeiptr* sizes,
            const char* caller = nullptr) const;

        /**
         * \brief The glBindImageTextures function binds a range of image textures to a specified binding point.
         *
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which textures are to be bound.
         * \param textures Specifies an array of names of texture objects to be bound.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindImageTextures(
            GLuint first, GLsizei count, const GLuint* textures, const char* caller = nullptr) const;

        /**
         * \brief The glBindSamplers function binds a range of sampler objects to a specified binding point.
         *
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which samplers are to be bound.
         * \param samplers Specifies an array of names of sampler objects to be bound.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindSamplers(GLuint first, GLsizei count, const GLuint* samplers, const char* caller = nullptr) const;

        /**
         * \brief The glBindTextures function binds a range of texture objects to a specified binding point.
         *
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which textures are to be bound.
         * \param textures Specifies an array of names of texture objects to be bound.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindTextures(GLuint first, GLsizei count, const GLuint* textures, const char* caller = nullptr) const;

        /**
         * \brief The glBindVertexBuffers function binds a range of vertex buffer objects to a specified binding point
         * with specified offsets and strides.
         *
         * \param first Specifies the index of the first binding point within the array specified by target.
         * \param count Specifies the number of consecutive binding points to which buffers are to be bound.
         * \param buffers Specifies an array of names of buffer objects to be bound.
         * \param offsets Specifies an array of offsets within the buffers.
         * \param strides Specifies an array of strides within the buffers.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindVertexBuffers(
            GLuint first,
            GLsizei count,
            const GLuint* buffers,
            const GLintptr* offsets,
            const GLsizei* strides,
            const char* caller = nullptr) const;

        /**
         * \brief The glBufferStorage function creates and initializes a buffer object's immutable data store.
         * \deprecated Deprecated in OpenGL 4.6. Use glBufferStorageEXT instead.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         * GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER,
         * GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER,
         * GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER,
         * GL_UNIFORM_BUFFER.
         * \param size Specifies the size in bytes of the buffer object's new data store.
         * \param data Specifies a pointer to data that will be copied into the data store.
         * \param flags Specifies the intended usage of the buffer's data store.
         * Accepted values are GL_DYNAMIC_STORAGE_BIT, GL_MAP_READ_BIT, GL_MAP_WRITE_BIT,
         * GL_MAP_PERSISTENT_BIT, GL_MAP_COHERENT_BIT, GL_CLIENT_STORAGE_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBufferStorage(
            GLenum target, GLsizeiptr size, const GLvoid* data, GLbitfield flags, const char* caller = nullptr) const;

        /**
         * \brief The glClearTexImage function fills a texture image with a specified value.
         *
         * \param texture Specifies the name of the texture object to be cleared.
         * \param level Specifies the level of the texture object to be cleared.
         * \param format Specifies the format of the data in the texture image.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the type of the data in the texture image.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data Specifies a pointer to the data to be used to clear the texture image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearTexImage(
            GLuint texture, GLint level, GLenum format, GLenum type, const GLvoid* data, const char* caller = nullptr)
            const;

        /**
         * \brief The glClearTexSubImage function fills a subregion of a texture image with a specified value.
         *
         * \param texture Specifies the name of the texture object to be cleared.
         * \param level Specifies the level of the texture object to be cleared.
         * \param xoffset Specifies the x offset of the subregion to be cleared.
         * \param yoffset Specifies the y offset of the subregion to be cleared.
         * \param zoffset Specifies the z offset of the subregion to be cleared.
         * \param width Specifies the width of the subregion to be cleared.
         * \param height Specifies the height of the subregion to be cleared.
         * \param depth Specifies the depth of the subregion to be cleared.
         * \param format Specifies the format of the data in the texture image.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the type of the data in the texture image.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data Specifies a pointer to the data to be used to clear the texture image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearTexSubImage(
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
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
