#pragma once

/**
 * \file Functions_4_2.h
 * \brief Declares the OpenGL 4.2 function wrapper interface.
 */

#include "Functions_4_1.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_2
     * \brief Exposes the OpenGL 4.2 function set.
     */
    class Functions_4_2 : public Functions_4_1
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_2();
        Functions_4_2(const Functions_4_2&) = delete;
        Functions_4_2& operator=(const Functions_4_2&) = delete;
        Functions_4_2(Functions_4_2&&) = delete;
        Functions_4_2& operator=(Functions_4_2&&) = delete;
        virtual ~Functions_4_2();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBindImageTexture function binds a level of a texture to an image unit.
         *
         * \param unit Specifies the index of the image unit to which to bind the texture.
         * \param texture Specifies the name of the texture to bind.
         * \param level Specifies the level of the texture to bind.
         * \param layered Specifies whether a layered texture binding is to be established.
         * \param layer Specifies the layer of the texture to bind.
         * \param access Specifies a token indicating the type of access that will be performed on the image.
         * Accepted values are GL_READ_ONLY, GL_WRITE_ONLY, and GL_READ_WRITE.
         * \param format Specifies the format that the elements of the image will be treated as for the purposes of
         * formatted stores and atomics.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindImageTexture(
            GLuint unit,
            GLuint texture,
            GLint level,
            GLboolean layered,
            GLint layer,
            GLenum access,
            GLenum format,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawArraysInstancedBaseInstance function renders multiple instances of a set of primitives
         * from array data with a base instance.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param baseinstance Specifies the base instance for use in fetching instanced vertex attributes.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawArraysInstancedBaseInstance(
            GLenum mode,
            GLint first,
            GLsizei count,
            GLsizei instancecount,
            GLuint baseinstance,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsInstancedBaseInstance function renders multiple instances of a set of primitives
         * by specifying indices of array data elements with a base instance.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param baseinstance Specifies the base instance for use in fetching instanced vertex attributes.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsInstancedBaseInstance(
            GLenum mode,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLsizei instancecount,
            GLuint baseinstance,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsInstancedBaseVertexBaseInstance function renders multiple instances of a set of
         * primitives by specifying indices of array data elements with a per-element offset and a base instance.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param basevertex Specifies a constant that should be added to each element of indices when choosing
         * elements from the enabled vertex arrays.
         * \param baseinstance Specifies the base instance for use in fetching instanced vertex attributes.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsInstancedBaseVertexBaseInstance(
            GLenum mode,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            GLsizei instancecount,
            GLint basevertex,
            GLuint baseinstance,
            const char* caller = nullptr) const;

        /**
         * \brief The glDrawTransformFeedbackInstanced function renders multiple instances of primitives using a count
         * derived from a transform feedback object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param id Specifies the name of a transform feedback object from which to retrieve a primitive
         * count.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawTransformFeedbackInstanced(
            GLenum mode, GLuint id, GLsizei instancecount, const char* caller = nullptr) const;

        /**
         * \brief The glDrawTransformFeedbackStreamInstanced function renders multiple instances of primitives using a
         * count derived from a specific stream of a transform feedback object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param id Specifies the name of a transform feedback object from which to retrieve a primitive
         * count.
         * \param stream Specifies the index of the transform feedback stream from which to retrieve a primitive
         * count.
         * \param instancecount Specifies the number of instances of the specified range of indices to be rendered.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawTransformFeedbackStreamInstanced(
            GLenum mode, GLuint id, GLuint stream, GLsizei instancecount, const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveAtomicCounterBufferiv function retrieves information about an active atomic counter
         * buffer.
         *
         * \param program Specifies the program object to be queried.
         * \param bufferIndex Specifies the index of the atomic counter buffer within the program object.
         * \param pname Specifies the symbolic name of an atomic counter buffer parameter.
         * Accepted values are GL_ATOMIC_COUNTER_BUFFER_BINDING,
         * GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS,
         * GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER,
         * GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER,
         * GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER,
         * GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER,
         * GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER,
         * GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER.
         * \param params Specifies a pointer to the location where the result of the query will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveAtomicCounterBufferiv(
            GLuint program, GLuint bufferIndex, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetInternalformativ function retrieves information about implementation-dependent support for
         * internal formats.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetInternalformati64v instead.
         *
         * \param target Specifies the target renderbuffer or texture.
         *  Accepted values are GL_RENDERBUFFER, GL_TEXTURE_1D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY,
         *  GL_TEXTURE_RECTANGLE, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE,
         * GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param internalformat Specifies the internal format about which to retrieve information.
         * \param pname  Specifies the type of information to query.
         *  Accepted values are GL_SAMPLES, GL_NUM_SAMPLE_COUNTS.
         * \param count  Specifies the size of the buffer whose address is given in params.
         * \param params Specifies the address of a buffer into which the query result will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetInternalformativ(
            GLenum target,
            GLenum internalformat,
            GLenum pname,
            GLsizei count,
            GLint* params,
            const char* caller = nullptr) const;

        /**
         * \brief The glMemoryBarrier function defines a barrier ordering memory transactions.
         *
         * \param barriers Specifies the barriers to insert.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, GL_ELEMENT_ARRAY_BARRIER_BIT,
         * GL_UNIFORM_BARRIER_BIT, GL_TEXTURE_FETCH_BARRIER_BIT, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
         * GL_COMMAND_BARRIER_BIT, GL_PIXEL_BUFFER_BARRIER_BIT, GL_TEXTURE_UPDATE_BARRIER_BIT,
         * GL_BUFFER_UPDATE_BARRIER_BIT, GL_FRAMEBUFFER_BARRIER_BIT, GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
         * GL_ATOMIC_COUNTER_BARRIER_BIT, GL_SHADER_STORAGE_BARRIER_BIT,
         * GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT, GL_QUERY_BUFFER_BARRIER_BIT, GL_ALL_BARRIER_BITS.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMemoryBarrier(GLbitfield barriers, const char* caller = nullptr) const;

        /**
         * \brief The glTexStorage1D function specifies the storage requirements for a one-dimensional texture.
         *
         * \param target Specifies the target of the operation. Must be GL_TEXTURE_1D.
         * \param levels Specifies the number of levels of texture.
         * \param internalformat Specifies the sized internal format to be used to store texture image data.
         * \param width  Specifies the width of the texture, in texels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexStorage1D(
            GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, const char* caller = nullptr) const;

        /**
         * \brief The glTexStorage2D function specifies the storage requirements for a two-dimensional texture.
         *
         * \param target Specifies the target of the operation. Must be GL_TEXTURE_2D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, or GL_TEXTURE_2D_MULTISAMPLE.
         * \param levels Specifies the number of levels of texture.
         * \param internalformat Specifies the sized internal format to be used to store texture image data.
         * \param width  Specifies the width of the texture, in texels.
         * \param height Specifies the height of the texture, in texels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexStorage2D(
            GLenum target,
            GLsizei levels,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexStorage3D function specifies the storage requirements for a three-dimensional texture.
         *
         * \param target Specifies the target of the operation. Must be GL_TEXTURE_3D, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, or GL_TEXTURE_2D_MULTISAMPLE.
         * \param levels Specifies the number of levels of texture.
         * \param internalformat Specifies the sized internal format to be used to store texture image data.
         * \param width  Specifies the width of the texture, in texels.
         * \param height Specifies the height of the texture, in texels.
         * \param depth  Specifies the depth of the texture, in texels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexStorage3D(
            GLenum target,
            GLsizei levels,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
