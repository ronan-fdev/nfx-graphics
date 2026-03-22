#pragma once

/**
 * \file Functions_3_1.h
 * \brief Declares the OpenGL 3.1 function wrapper interface.
 */

#include "Functions_3_0.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_3_1
     * \brief Exposes the OpenGL 3.1 function set.
     */
    class Functions_3_1 : public Functions_3_0
    {
        static inline bool s_loaded;

    public:
        explicit Functions_3_1();
        Functions_3_1(const Functions_3_1&) = delete;
        Functions_3_1& operator=(const Functions_3_1&) = delete;
        Functions_3_1(Functions_3_1&&) = delete;
        Functions_3_1& operator=(Functions_3_1&&) = delete;
        virtual ~Functions_3_1();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glCopyBufferSubData function copies part of the data store of a buffer object to the data store
         * of another buffer object.
         *
         * \param readTarget Specifies the target from which data should be read.
         * Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         * GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
         * GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param writeTarget Specifies the target to which data should be written.
         * Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         * GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
         * GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param readOffset Specifies the offset into the source buffer object's data store from which data should
         * be read.
         * \param writeOffset Specifies the offset into the destination buffer object's data store to which data
         * should be written.
         * \param size Specifies the size in bytes of the data to be copied.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyBufferSubData(
            GLenum readTarget,
            GLenum writeTarget,
            GLintptr readOffset,
            GLintptr writeOffset,
            GLsizeiptr size,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawArraysInstanced function renders multiple instances of a set of primitives from array
         * data.
         * \deprecated Deprecated in OpenGL 4.5. Use glDrawArraysInstancedBaseInstance instead.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawArraysInstanced(
            GLenum mode, GLint first, GLsizei count, GLsizei instancecount, const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsInstanced function renders multiple instances of a set of primitives by specifying
         * indices of array data elements.
         * \deprecated Deprecated in OpenGL 4.5. Use glDrawElementsInstancedBaseInstance instead.
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
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsInstanced(
            GLenum mode,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLsizei instancecount,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveUniformBlockiv function retrieves information about an active uniform block.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformBlockIndex Specifies the index of the uniform block within the program object.
         * \param pname  Specifies the symbolic name of a uniform block parameter.
         *  Accepted values are GL_UNIFORM_BLOCK_BINDING, GL_UNIFORM_BLOCK_DATA_SIZE,
         * GL_UNIFORM_BLOCK_NAME_LENGTH, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
         * GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER,
         *  GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER.
         * \param params Specifies a pointer to the location where the result of the query will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveUniformBlockiv(
            GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveUniformBlockName function retrieves the name of an active uniform block.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformBlockIndex Specifies the index of the uniform block within the program object.
         * \param bufSize Specifies the size of the buffer used to store the uniform block name.
         * \param length Specifies a pointer to the location where the length of the uniform block name will
         * be stored.
         * \param uniformBlockName Specifies a pointer to the buffer where the uniform block name will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveUniformBlockName(
            GLuint program,
            GLuint uniformBlockIndex,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* uniformBlockName,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveUniformName function retrieves the name of an active uniform variable.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformIndex Specifies the index of the uniform variable within the program object.
         * \param bufSize Specifies the size of the buffer used to store the uniform name.
         * \param length Specifies a pointer to the location where the length of the uniform name will be stored.
         * \param uniformName Specifies a pointer to the buffer where the uniform name will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveUniformName(
            GLuint program,
            GLuint uniformIndex,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* uniformName,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveUniformsiv function retrieves information about active uniform variables.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformCount Specifies the number of elements in the uniformIndices array.
         * \param uniformIndices Specifies an array of indices of the uniform variables within the program object.
         * \param pname  Specifies the symbolic name of a uniform parameter.
         *  Accepted values are GL_UNIFORM_TYPE, GL_UNIFORM_SIZE, GL_UNIFORM_NAME_LENGTH,
         * GL_UNIFORM_BLOCK_INDEX, GL_UNIFORM_OFFSET, GL_UNIFORM_ARRAY_STRIDE, GL_UNIFORM_MATRIX_STRIDE,
         * GL_UNIFORM_IS_ROW_MAJOR.
         * \param params Specifies a pointer to the location where the result of the query will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveUniformsiv(
            GLuint program,
            GLsizei uniformCount,
            const GLuint* uniformIndices,
            GLenum pname,
            GLint* params,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformBlockIndex function retrieves the index of a named uniform block.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformBlockName Specifies the name of the uniform block whose index is to be queried.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The index of the uniform block within the program object.
         */
        GLuint glGetUniformBlockIndex(
            GLuint program, const GLchar* uniformBlockName, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformIndices function retrieves the indices of a list of uniform variable names.
         *
         * \param program Specifies the program object to be queried.
         * \param uniformCount Specifies the number of elements in the uniformNames array.
         * \param uniformNames Specifies an array of pointers to strings containing the names of the uniform
         * variables whose indices are to be queried.
         * \param uniformIndices Specifies an array that will receive the indices of the uniform variables.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformIndices(
            GLuint program,
            GLsizei uniformCount,
            const GLchar* const* uniformNames,
            GLuint* uniformIndices,
            const char* caller = nullptr) const;

        /**
         * \brief The glPrimitiveRestartIndex function specifies the primitive restart index.
         * \deprecated Deprecated in OpenGL 4.5. Use glPrimitiveRestartIndexNV instead.
         *
         * \param index Specifies the value to be interpreted as the primitive restart index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPrimitiveRestartIndex(GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glTexBuffer function attaches a buffer object's data store to a buffer texture.
         * \deprecated Deprecated in OpenGL 4.5. Use glTexBufferRange instead.
         *
         * \param target Specifies the target of the operation. Must be GL_TEXTURE_BUFFER.
         * \param internalformat Specifies the internal format of the data in the buffer texture.
         *  Accepted values are GL_R8, GL_R8_SNORM, GL_R16, GL_R16_SNORM, GL_RG8, GL_RG8_SNORM,
         * GL_RG16, GL_RG16_SNORM, GL_R3_G3_B2, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB8_SNORM, GL_RGB10, GL_RGB12,
         * GL_RGB16_SNORM, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGBA8_SNORM, GL_RGB10_A2, GL_RGB10_A2UI,
         * GL_RGBA12, GL_RGBA16, GL_SRGB8, GL_SRGB8_ALPHA8, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F, GL_R32F, GL_RG32F,
         * GL_RGB32F, GL_RGBA32F, GL_R11F_G11F_B10F, GL_RGB9_E5, GL_R8I, GL_R8UI, GL_R16I, GL_R16UI, GL_R32I, GL_R32UI,
         * GL_RG8I, GL_RG8UI, GL_RG16I, GL_RG16UI, GL_RG32I, GL_RG32UI, GL_RGB8I, GL_RGB8UI, GL_RGB16I, GL_RGB16UI,
         * GL_RGB32I, GL_RGB32UI, GL_RGBA8I, GL_RGBA8UI, GL_RGBA16I, GL_RGBA16UI, GL_RGBA32I, GL_RGBA32UI,
         * GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8,
         *  GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX1, GL_STENCIL_INDEX4, GL_STENCIL_INDEX8,
         * GL_STENCIL_INDEX16.
         * \param buffer Specifies the name of the buffer object whose storage to attach to the buffer
         * texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glUniformBlockBinding function assigns a binding point to an active uniform block.
         *
         * \param program  Specifies the program object in which the block is defined.
         * \param uniformBlockIndex Specifies the index of the uniform block within the program object.
         * \param uniformBlockBinding Specifies the binding point to which the uniform block should be assigned.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformBlockBinding(
            GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
