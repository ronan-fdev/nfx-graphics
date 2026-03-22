#pragma once

/**
 * \file Functions_4_5.h
 * \brief Declares the OpenGL 4.5 function wrapper interface.
 */

#include "Functions_4_4.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_5
     * \brief Exposes the OpenGL 4.5 function set.
     */
    class Functions_4_5 : public Functions_4_4
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_5();
        Functions_4_5(const Functions_4_5&) = delete;
        Functions_4_5& operator=(const Functions_4_5&) = delete;
        Functions_4_5(Functions_4_5&&) = delete;
        Functions_4_5& operator=(Functions_4_5&&) = delete;
        virtual ~Functions_4_5();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glBindTextureUnit function binds a texture to a texture unit.
         *
         * \param unit Specifies the index of the texture unit to which to bind the texture.
         * \param texture Specifies the name of the texture to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindTextureUnit(GLuint unit, GLuint texture, const char* caller = nullptr) const;

        /**
         * \brief The glBlitNamedFramebuffer function copies a block of pixels from one framebuffer object to another.
         *
         * \param readFramebuffer Specifies the source framebuffer object.
         * \param drawFramebuffer Specifies the destination framebuffer object.
         * \param srcX0  Specifies the x coordinate of the lower left corner of the source rectangle.
         * \param srcY0  Specifies the y coordinate of the lower left corner of the source rectangle.
         * \param srcX1  Specifies the x coordinate of the upper right corner of the source rectangle.
         * \param srcY1  Specifies the y coordinate of the upper right corner of the source rectangle.
         * \param dstX0  Specifies the x coordinate of the lower left corner of the destination rectangle.
         * \param dstY0  Specifies the y coordinate of the lower left corner of the destination rectangle.
         * \param dstX1  Specifies the x coordinate of the upper right corner of the destination rectangle.
         * \param dstY1  Specifies the y coordinate of the upper right corner of the destination rectangle.
         * \param mask  Specifies the bitwise OR of the flags indicating which buffers are to be copied.
         *  Accepted values are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, and
         * GL_STENCIL_BUFFER_BIT.
         * \param filter Specifies the interpolation method to be applied if the image is stretched.
         *  Accepted values are GL_NEAREST and GL_LINEAR.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlitNamedFramebuffer(
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
            const char* caller = nullptr) const;

        /**
         * \brief The glCheckNamedFramebufferStatus function checks the completeness status of a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param target Specifies the target of the framebuffer object.
         * Accepted values are GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, and GL_DRAW_FRAMEBUFFER.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The completeness status of the framebuffer object.
         * Possible return values are GL_FRAMEBUFFER_COMPLETE, GL_FRAMEBUFFER_UNDEFINED,
         * GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
         * GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, GL_FRAMEBUFFER_UNSUPPORTED,
         * GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, and GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS.
         */
        GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedBufferData function fills a buffer object's data store with a fixed value.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param internalformat Specifies the internal format of the data in the buffer object.
         * \param format Specifies the format of the data in the buffer object.
         *  Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL.
         * \param type  Specifies the type of the data in the buffer object.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         *  GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         *  GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         *  GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         *  GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         *  GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data  Specifies a pointer to the data to be used to clear the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedBufferData(
            GLuint buffer,
            GLenum internalformat,
            GLenum format,
            GLenum type,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedBufferSubData function fills a subregion of a buffer object's data store with a
         * fixed value.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param internalformat Specifies the internal format of the data in the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size  Specifies the size of the subregion to be filled.
         * \param format Specifies the format of the data in the buffer object.
         *  Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL.
         * \param type  Specifies the type of the data in the buffer object.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         *  GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         *  GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         *  GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         *  GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         *  GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data  Specifies a pointer to the data to be used to clear the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedBufferSubData(
            GLuint buffer,
            GLenum internalformat,
            GLintptr offset,
            GLsizeiptr size,
            GLenum format,
            GLenum type,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedFramebufferfi function clears a specified buffer of a framebuffer object to a fixed
         * value.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_DEPTH_STENCIL_ATTACHMENT.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param depth Specifies the depth value to clear the buffer to.
         * \param stencil Specifies the stencil value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedFramebufferfi(
            GLuint framebuffer,
            GLenum buffer,
            GLint drawbuffer,
            GLfloat depth,
            GLint stencil,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedFramebufferfv function clears a specified buffer of a framebuffer object to a fixed
         * value.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR, GL_DEPTH.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedFramebufferfv(
            GLuint framebuffer,
            GLenum buffer,
            GLint drawbuffer,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedFramebufferiv function clears a specified buffer of a framebuffer object to a fixed
         * value.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR, GL_STENCIL.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedFramebufferiv(
            GLuint framebuffer,
            GLenum buffer,
            GLint drawbuffer,
            const GLint* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearNamedFramebufferuiv function clears a specified buffer of a framebuffer object to a fixed
         * value.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearNamedFramebufferuiv(
            GLuint framebuffer,
            GLenum buffer,
            GLint drawbuffer,
            const GLuint* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glClipControl function controls the clipping volume behavior.
         *
         * \param origin Specifies the clip space origin.
         * Accepted values are GL_LOWER_LEFT and GL_UPPER_LEFT.
         * \param depth Specifies the depth range.
         * Accepted values are GL_NEGATIVE_ONE_TO_ONE and GL_ZERO_TO_ONE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClipControl(GLenum origin, GLenum depth, const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTextureSubImage1D function specifies a one-dimensional compressed texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param format Specifies the format of the data in the texture image.
         * Accepted values are GL_COMPRESSED_RED, GL_COMPRESSED_RG, GL_COMPRESSED_RGB,
         * GL_COMPRESSED_RGBA, GL_COMPRESSED_SRGB, GL_COMPRESSED_SRGB_ALPHA, GL_COMPRESSED_RED_RGTC1,
         * GL_COMPRESSED_SIGNED_RED_RGTC1, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RG_RGTC2,
         * GL_COMPRESSED_RGBA_BPTC_UNORM, GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
         * GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT.
         * \param imageSize Specifies the size of the compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTextureSubImage1D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLsizei width,
            GLenum format,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTextureSubImage2D function specifies a two-dimensional compressed texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param format Specifies the format of the data in the texture image.
         * Accepted values are GL_COMPRESSED_RED, GL_COMPRESSED_RG, GL_COMPRESSED_RGB,
         * GL_COMPRESSED_RGBA, GL_COMPRESSED_SRGB, GL_COMPRESSED_SRGB_ALPHA, GL_COMPRESSED_RED_RGTC1,
         * GL_COMPRESSED_SIGNED_RED_RGTC1, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RG_RGTC2,
         * GL_COMPRESSED_RGBA_BPTC_UNORM, GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
         * GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT.
         * \param imageSize Specifies the size of the compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTextureSubImage2D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTextureSubImage3D function specifies a three-dimensional compressed texture
         * subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param depth Specifies the depth of the subregion.
         * \param format Specifies the format of the data in the texture image.
         * Accepted values are GL_COMPRESSED_RED, GL_COMPRESSED_RG, GL_COMPRESSED_RGB,
         * GL_COMPRESSED_RGBA, GL_COMPRESSED_SRGB, GL_COMPRESSED_SRGB_ALPHA, GL_COMPRESSED_RED_RGTC1,
         * GL_COMPRESSED_SIGNED_RED_RGTC1, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RG_RGTC2,
         * GL_COMPRESSED_RGBA_BPTC_UNORM, GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
         * GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT.
         * \param imageSize Specifies the size of the compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTextureSubImage3D(
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
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyNamedBufferSubData function copies a subregion of a buffer object's data store.
         *
         * \param readBuffer Specifies the name of the source buffer object.
         * \param writeBuffer Specifies the name of the destination buffer object.
         * \param readOffset Specifies the offset within the source buffer object.
         * \param writeOffset Specifies the offset within the destination buffer object.
         * \param size Specifies the size of the subregion to be copied.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyNamedBufferSubData(
            GLuint readBuffer,
            GLuint writeBuffer,
            GLintptr readOffset,
            GLintptr writeOffset,
            GLsizeiptr size,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyTextureSubImage1D function copies a one-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param x Specifies the x coordinate of the source region.
         * \param y Specifies the y coordinate of the source region.
         * \param width Specifies the width of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTextureSubImage1D(
            GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char* caller = nullptr)
            const;

        /**
         * \brief The glCopyTextureSubImage2D function copies a two-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param x Specifies the x coordinate of the source region.
         * \param y Specifies the y coordinate of the source region.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTextureSubImage2D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyTextureSubImage3D function copies a three-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param x Specifies the x coordinate of the source region.
         * \param y Specifies the y coordinate of the source region.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTextureSubImage3D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLint zoffset,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glCreateBuffers function creates buffer objects.
         *
         * \param n Specifies the number of buffer objects to be created.
         * \param buffers Specifies an array in which the names of the created buffer objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateBuffers(GLsizei n, GLuint* buffers, const char* caller = nullptr) const;

        /**
         * \brief The glCreateFramebuffers function creates framebuffer objects.
         *
         * \param n  Specifies the number of framebuffer objects to be created.
         * \param framebuffers Specifies an array in which the names of the created framebuffer objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateFramebuffers(GLsizei n, GLuint* framebuffers, const char* caller = nullptr) const;

        /**
         * \brief The glCreateProgramPipelines function creates program pipeline objects.
         *
         * \param n Specifies the number of program pipeline objects to be created.
         * \param pipelines Specifies an array in which the names of the created program pipeline objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateProgramPipelines(GLsizei n, GLuint* pipelines, const char* caller = nullptr) const;

        /**
         * \brief The glCreateQueries function creates query objects.
         *
         * \param target Specifies the target type of the queries to be created.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_TIME_ELAPSED, GL_TIMESTAMP, GL_PRIMITIVES_GENERATED,
         * GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN.
         * \param n Specifies the number of query objects to be created.
         * \param ids Specifies an array in which the names of the created query objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateQueries(GLenum target, GLsizei n, GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glCreateRenderbuffers function creates renderbuffer objects.
         *
         * \param n  Specifies the number of renderbuffer objects to be created.
         * \param renderbuffers Specifies an array in which the names of the created renderbuffer objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers, const char* caller = nullptr) const;

        /**
         * \brief The glCreateSamplers function creates sampler objects.
         *
         * \param n Specifies the number of sampler objects to be created.
         * \param samplers Specifies an array in which the names of the created sampler objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateSamplers(GLsizei n, GLuint* samplers, const char* caller = nullptr) const;

        /**
         * \brief The glCreateTextures function creates texture objects.
         *
         * \param target Specifies the target to which the texture objects are bound.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY,
         * GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param n Specifies the number of texture objects to be created.
         * \param textures Specifies an array in which the names of the created texture objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateTextures(GLenum target, GLsizei n, GLuint* textures, const char* caller = nullptr) const;

        /**
         * \brief The glCreateTransformFeedbacks function creates transform feedback objects.
         *
         * \param n Specifies the number of transform feedback objects to be created.
         * \param ids Specifies an array in which the names of the created transform feedback objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateTransformFeedbacks(GLsizei n, GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glCreateVertexArrays function creates vertex array objects.
         *
         * \param n Specifies the number of vertex array objects to be created.
         * \param arrays Specifies an array in which the names of the created vertex array objects are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCreateVertexArrays(GLsizei n, GLuint* arrays, const char* caller = nullptr) const;

        /**
         * \brief The glDisableVertexArrayAttrib function disables a vertex attribute array.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param index Specifies the index of the vertex attribute to be disabled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDisableVertexArrayAttrib(GLuint vaobj, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glEnableVertexArrayAttrib function enables a vertex attribute array.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param index Specifies the index of the vertex attribute to be enabled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnableVertexArrayAttrib(GLuint vaobj, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glFlushMappedNamedBufferRange function flushes a range of a mapped buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param length Specifies the length of the range to be flushed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFlushMappedNamedBufferRange(
            GLuint buffer, GLintptr offset, GLsizeiptr length, const char* caller = nullptr) const;

        /**
         * \brief The glGenerateTextureMipmap function generates mipmaps for a specified texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenerateTextureMipmap(GLuint texture, const char* caller = nullptr) const;

        /**
         * \brief The glGetCompressedTextureImage function retrieves a compressed texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param bufSize Specifies the size of the buffer to receive the compressed image.
         * \param pixels Specifies a pointer to the buffer to receive the compressed image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetCompressedTextureImage(
            GLuint texture, GLint level, GLsizei bufSize, GLvoid* pixels, const char* caller = nullptr) const;

        /**
         * \brief The glGetCompressedTextureSubImage function retrieves a subregion of a compressed texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param depth Specifies the depth of the subregion.
         * \param bufSize Specifies the size of the buffer to receive the compressed image.
         * \param pixels Specifies a pointer to the buffer to receive the compressed image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetCompressedTextureSubImage(
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
            const char* caller = nullptr) const;

        /**
         * \brief The glGetGraphicsResetStatus function retrieves the graphics reset status.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetGraphicsResetStatusARB instead.
         *
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The graphics reset status.
         * Possible return values are GL_NO_ERROR, GL_GUILTY_CONTEXT_RESET, GL_INNOCENT_CONTEXT_RESET, and
         * GL_UNKNOWN_CONTEXT_RESET.
         */
        GLenum glGetGraphicsResetStatus(const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedBufferParameteri64v function retrieves a 64-bit parameter from a buffer object.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the buffer parameter to be retrieved.
         * Accepted values are GL_BUFFER_SIZE, GL_BUFFER_USAGE, GL_BUFFER_ACCESS_FLAGS,
         * GL_BUFFER_MAP_LENGTH, GL_BUFFER_MAP_OFFSET.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedBufferParameteri64v(
            GLuint buffer, GLenum pname, GLint64* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedBufferParameteriv function retrieves a parameter from a buffer object.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the buffer parameter to be retrieved.
         * Accepted values are GL_BUFFER_SIZE, GL_BUFFER_USAGE, GL_BUFFER_ACCESS_FLAGS,
         * GL_BUFFER_MAP_LENGTH, GL_BUFFER_MAP_OFFSET.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedBufferParameteriv(
            GLuint buffer, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedBufferPointerv function retrieves a pointer from a buffer object.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the buffer parameter to be retrieved.
         * Accepted value is GL_BUFFER_MAP_POINTER.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedBufferPointerv(
            GLuint buffer, GLenum pname, GLvoid** params, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedBufferSubData function retrieves a subregion of a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size Specifies the size of the subregion to be retrieved.
         * \param data Specifies a pointer to the buffer to receive the data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedBufferSubData(
            GLuint buffer, GLintptr offset, GLsizeiptr size, GLvoid* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedFramebufferAttachmentParameteriv function retrieves a parameter from a framebuffer
         * attachment.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param attachment Specifies the attachment within the framebuffer object.
         * Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param pname Specifies the symbolic name of the attachment parameter to be retrieved.
         * Accepted values are GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
         * GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
         * GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER,
         * GL_FRAMEBUFFER_ATTACHMENT_LAYERED, GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING,
         * GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedFramebufferAttachmentParameteriv(
            GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedFramebufferParameteriv function retrieves a parameter from a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param pname Specifies the symbolic name of the framebuffer parameter to be retrieved.
         * Accepted values are GL_FRAMEBUFFER_DEFAULT_WIDTH, GL_FRAMEBUFFER_DEFAULT_HEIGHT,
         * GL_FRAMEBUFFER_DEFAULT_LAYERS, GL_FRAMEBUFFER_DEFAULT_SAMPLES, GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,
         * GL_FRAMEBUFFER_DEFAULT_COLOR_ENCODING, GL_FRAMEBUFFER_DEFAULT_COMPONENT_TYPE,
         * GL_FRAMEBUFFER_DEFAULT_RED_SIZE, GL_FRAMEBUFFER_DEFAULT_GREEN_SIZE, GL_FRAMEBUFFER_DEFAULT_BLUE_SIZE,
         * GL_FRAMEBUFFER_DEFAULT_ALPHA_SIZE, GL_FRAMEBUFFER_DEFAULT_DEPTH_SIZE, GL_FRAMEBUFFER_DEFAULT_STENCIL_SIZE.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedFramebufferParameteriv(
            GLuint framebuffer, GLenum pname, GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetNamedRenderbufferParameteriv function retrieves a parameter from a renderbuffer object.
         *
         * \param renderbuffer Specifies the name of the renderbuffer object.
         * \param pname Specifies the symbolic name of the renderbuffer parameter to be retrieved.
         * Accepted values are GL_RENDERBUFFER_WIDTH, GL_RENDERBUFFER_HEIGHT,
         * GL_RENDERBUFFER_INTERNAL_FORMAT, GL_RENDERBUFFER_RED_SIZE, GL_RENDERBUFFER_GREEN_SIZE,
         * GL_RENDERBUFFER_BLUE_SIZE, GL_RENDERBUFFER_ALPHA_SIZE, GL_RENDERBUFFER_DEPTH_SIZE,
         * GL_RENDERBUFFER_STENCIL_SIZE, GL_RENDERBUFFER_SAMPLES.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetNamedRenderbufferParameteriv(
            GLuint renderbuffer, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetnCompressedTexImage function retrieves a compressed texture image with a specified buffer
         * size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnCompressedTexImageARB instead.
         *
         * \param target Specifies the target to which the texture object is bound.
         * \param lod Specifies the level of detail number of the texture object.
         * \param bufSize Specifies the size of the buffer to receive the compressed image.
         * \param pixels Specifies a pointer to the buffer to receive the compressed image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnCompressedTexImage(
            GLenum target, GLint lod, GLsizei bufSize, GLvoid* pixels, const char* caller = nullptr) const;

        /**
         * \brief The glGetnTexImage function retrieves a texture image with a specified buffer size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnTexImageARB instead.
         *
         * \param target Specifies the target to which the texture object is bound.
         * \param level Specifies the level of detail number of the texture object.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param bufSize Specifies the size of the buffer to receive the image.
         * \param pixels Specifies a pointer to the buffer to receive the image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnTexImage(
            GLenum target,
            GLint level,
            GLenum format,
            GLenum type,
            GLsizei bufSize,
            GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetnUniformdv function retrieves the value of a double uniform variable with a specified
         * buffer size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnUniformdvARB instead.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be retrieved.
         * \param bufSize Specifies the size of the buffer to receive the value.
         * \param params Specifies a pointer to the buffer to receive the value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnUniformdv(
            GLuint program, GLint location, GLsizei bufSize, GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetnUniformfv function retrieves the value of a float uniform variable with a specified buffer
         * size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnUniformfvARB instead.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be retrieved.
         * \param bufSize Specifies the size of the buffer to receive the value.
         * \param params Specifies a pointer to the buffer to receive the value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnUniformfv(
            GLuint program, GLint location, GLsizei bufSize, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetnUniformiv function retrieves the value of an integer uniform variable with a specified
         * buffer size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnUniformivARB instead.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be retrieved.
         * \param bufSize Specifies the size of the buffer to receive the value.
         * \param params Specifies a pointer to the buffer to receive the value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnUniformiv(
            GLuint program, GLint location, GLsizei bufSize, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetnUniformuiv function retrieves the value of an unsigned integer uniform variable with a
         * specified buffer size.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetnUniformuivARB instead.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be retrieved.
         * \param bufSize Specifies the size of the buffer to receive the value.
         * \param params Specifies a pointer to the buffer to receive the value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetnUniformuiv(
            GLuint program, GLint location, GLsizei bufSize, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryBufferObjecti64v function retrieves a 64-bit integer parameter from a query object and
         * stores it in a buffer object.
         *
         * \param id Specifies the name of the query object.
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the query object parameter to be retrieved.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_NO_WAIT, GL_QUERY_RESULT_AVAILABLE.
         * \param offset Specifies the offset within the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryBufferObjecti64v(
            GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryBufferObjectiv function retrieves an integer parameter from a query object and stores
         * it in a buffer object.
         *
         * \param id Specifies the name of the query object.
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the query object parameter to be retrieved.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_NO_WAIT, GL_QUERY_RESULT_AVAILABLE.
         * \param offset Specifies the offset within the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryBufferObjectiv(
            GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryBufferObjectui64v function retrieves a 64-bit unsigned integer parameter from a query
         * object and stores it in a buffer object.
         *
         * \param id Specifies the name of the query object.
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the query object parameter to be retrieved.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_NO_WAIT, GL_QUERY_RESULT_AVAILABLE.
         * \param offset Specifies the offset within the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryBufferObjectui64v(
            GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryBufferObjectuiv function retrieves an unsigned integer parameter from a query object
         * and stores it in a buffer object.
         *
         * \param id Specifies the name of the query object.
         * \param buffer Specifies the name of the buffer object.
         * \param pname Specifies the symbolic name of the query object parameter to be retrieved.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_NO_WAIT, GL_QUERY_RESULT_AVAILABLE.
         * \param offset Specifies the offset within the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryBufferObjectuiv(
            GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureImage function retrieves a texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param bufSize Specifies the size of the buffer to receive the image.
         * \param pixels Specifies a pointer to the buffer to receive the image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureImage(
            GLuint texture,
            GLint level,
            GLenum format,
            GLenum type,
            GLsizei bufSize,
            GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureLevelParameterfv function retrieves a floating-point parameter from a texture level.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param pname Specifies the symbolic name of the texture level parameter to be retrieved.
         * Accepted values are GL_TEXTURE_WIDTH, GL_TEXTURE_HEIGHT, GL_TEXTURE_DEPTH,
         * GL_TEXTURE_INTERNAL_FORMAT, GL_TEXTURE_RED_SIZE, GL_TEXTURE_GREEN_SIZE, GL_TEXTURE_BLUE_SIZE,
         * GL_TEXTURE_ALPHA_SIZE, GL_TEXTURE_DEPTH_SIZE, GL_TEXTURE_STENCIL_SIZE, GL_TEXTURE_SHARED_SIZE,
         * GL_TEXTURE_RED_TYPE, GL_TEXTURE_GREEN_TYPE, GL_TEXTURE_BLUE_TYPE, GL_TEXTURE_ALPHA_TYPE,
         * GL_TEXTURE_DEPTH_TYPE, GL_TEXTURE_COMPRESSED, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, GL_TEXTURE_BUFFER_OFFSET,
         * GL_TEXTURE_BUFFER_SIZE.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureLevelParameterfv(
            GLuint texture, GLint level, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureLevelParameteriv function retrieves an integer parameter from a texture level.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param pname Specifies the symbolic name of the texture level parameter to be retrieved.
         * Accepted values are GL_TEXTURE_WIDTH, GL_TEXTURE_HEIGHT, GL_TEXTURE_DEPTH,
         * GL_TEXTURE_INTERNAL_FORMAT, GL_TEXTURE_RED_SIZE, GL_TEXTURE_GREEN_SIZE, GL_TEXTURE_BLUE_SIZE,
         * GL_TEXTURE_ALPHA_SIZE, GL_TEXTURE_DEPTH_SIZE, GL_TEXTURE_STENCIL_SIZE, GL_TEXTURE_SHARED_SIZE,
         * GL_TEXTURE_RED_TYPE, GL_TEXTURE_GREEN_TYPE, GL_TEXTURE_BLUE_TYPE, GL_TEXTURE_ALPHA_TYPE,
         * GL_TEXTURE_DEPTH_TYPE, GL_TEXTURE_COMPRESSED, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, GL_TEXTURE_BUFFER_OFFSET,
         * GL_TEXTURE_BUFFER_SIZE.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureLevelParameteriv(
            GLuint texture, GLint level, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureParameterfv function retrieves a floating-point parameter from a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be retrieved.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE,
         * GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureParameterfv(
            GLuint texture, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureParameterIiv function retrieves an integer parameter from a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be retrieved.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE,
         * GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureParameterIiv(
            GLuint texture, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureParameterIuiv function retrieves an unsigned integer parameter from a texture
         * object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be retrieved.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE,
         * GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureParameterIuiv(
            GLuint texture, GLenum pname, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureParameteriv function retrieves an integer parameter from a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be retrieved.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE,
         * GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTextureSubImage function retrieves a subregion of a texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param depth Specifies the depth of the subregion.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param bufSize Specifies the size of the buffer to receive the image.
         * \param pixels Specifies a pointer to the buffer to receive the image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTextureSubImage(
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
            const char* caller = nullptr) const;

        /**
         * \brief The glGetTransformFeedbacki64_v function retrieves a 64-bit integer parameter from a transform
         * feedback object.
         *
         * \param xfb Specifies the name of the transform feedback object.
         * \param pname Specifies the symbolic name of the transform feedback parameter to be retrieved.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING.
         * \param index Specifies the index of the transform feedback parameter to be retrieved.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTransformFeedbacki64_v(
            GLuint xfb, GLenum pname, GLuint index, GLint64* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetTransformFeedbackiv function retrieves a parameter from a transform feedback object.
         *
         * \param xfb Specifies the name of the transform feedback object.
         * \param pname Specifies the symbolic name of the transform feedback parameter to be retrieved.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetTransformFeedbacki_v function retrieves an integer parameter from a transform feedback
         * object.
         *
         * \param xfb Specifies the name of the transform feedback object.
         * \param pname Specifies the symbolic name of the transform feedback parameter to be retrieved.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING.
         * \param index Specifies the index of the transform feedback parameter to be retrieved.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTransformFeedbacki_v(
            GLuint xfb, GLenum pname, GLuint index, GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexArrayIndexed64iv function retrieves a 64-bit integer parameter from a vertex array
         * object.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param index Specifies the index of the vertex array parameter to be retrieved.
         * \param pname Specifies the symbolic name of the vertex array parameter to be retrieved.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_ENABLED, GL_VERTEX_ATTRIB_ARRAY_SIZE,
         * GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
         * GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_LONG, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_RELATIVE_OFFSET.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexArrayIndexed64iv(
            GLuint vaobj, GLuint index, GLenum pname, GLint64* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexArrayIndexediv function retrieves an integer parameter from a vertex array object.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param index Specifies the index of the vertex array parameter to be retrieved.
         * \param pname Specifies the symbolic name of the vertex array parameter to be retrieved.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_ENABLED, GL_VERTEX_ATTRIB_ARRAY_SIZE,
         * GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
         * GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_LONG, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_RELATIVE_OFFSET.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexArrayIndexediv(
            GLuint vaobj, GLuint index, GLenum pname, GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexArrayiv function retrieves a parameter from a vertex array object.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param pname Specifies the symbolic name of the vertex array parameter to be retrieved.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_ENABLED, GL_VERTEX_ATTRIB_ARRAY_SIZE,
         * GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
         * GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_LONG, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_RELATIVE_OFFSET.
         * \param param Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateNamedFramebufferData function invalidates the content of a framebuffer object's
         * attachments.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param numAttachments Specifies the number of attachments to invalidate.
         * \param attachments Specifies an array of attachments to invalidate.
         *  Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateNamedFramebufferData(
            GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateNamedFramebufferSubData function invalidates the content of a subregion of a
         * framebuffer object's attachments.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param numAttachments Specifies the number of attachments to invalidate.
         * \param attachments Specifies an array of attachments to invalidate.
         *  Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param x  Specifies the x coordinate of the subregion.
         * \param y  Specifies the y coordinate of the subregion.
         * \param width  Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateNamedFramebufferSubData(
            GLuint framebuffer,
            GLsizei numAttachments,
            const GLenum* attachments,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glMapNamedBuffer function maps a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param access Specifies the access policy for the mapping.
         * Accepted values are GL_READ_ONLY, GL_WRITE_ONLY, and GL_READ_WRITE.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return A pointer to the mapped data store.
         */
        GLvoid* glMapNamedBuffer(GLuint buffer, GLenum access, const char* caller = nullptr) const;

        /**
         * \brief The glMapNamedBufferRange function maps a range of a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param length Specifies the length of the range to be mapped.
         * \param access Specifies the access policy for the mapping.
         * Accepted values are GL_MAP_READ_BIT, GL_MAP_WRITE_BIT, GL_MAP_PERSISTENT_BIT,
         * GL_MAP_COHERENT_BIT, GL_MAP_INVALIDATE_RANGE_BIT, GL_MAP_INVALIDATE_BUFFER_BIT,
         * GL_MAP_FLUSH_EXPLICIT_BIT, and GL_MAP_UNSYNCHRONIZED_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return A pointer to the mapped data store.
         */
        GLvoid* glMapNamedBufferRange(
            GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, const char* caller = nullptr) const;

        /**
         * \brief The glMemoryBarrierByRegion function defines a barrier ordering memory transactions.
         *
         * \param barriers Specifies the barriers to be synchronized.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, GL_ELEMENT_ARRAY_BARRIER_BIT,
         * GL_UNIFORM_BARRIER_BIT, GL_TEXTURE_FETCH_BARRIER_BIT, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
         * GL_COMMAND_BARRIER_BIT, GL_PIXEL_BUFFER_BARRIER_BIT, GL_TEXTURE_UPDATE_BARRIER_BIT,
         * GL_BUFFER_UPDATE_BARRIER_BIT, GL_FRAMEBUFFER_BARRIER_BIT, GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
         * GL_ATOMIC_COUNTER_BARRIER_BIT, GL_SHADER_STORAGE_BARRIER_BIT,
         * GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT, GL_QUERY_BUFFER_BARRIER_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMemoryBarrierByRegion(GLbitfield barriers, const char* caller = nullptr) const;

        /**
         * \brief The glNamedBufferData function creates and initializes a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param size Specifies the size in bytes of the buffer object's new data store.
         * \param data Specifies a pointer to data that will be copied into the data store.
         * \param usage Specifies the expected usage pattern of the data store.
         * Accepted values are GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW,
         * GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedBufferData(
            GLuint buffer, GLsizei size, const GLvoid* data, GLenum usage, const char* caller = nullptr) const;

        /**
         * \brief The glNamedBufferStorage function creates and initializes a buffer object's immutable data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param size Specifies the size in bytes of the buffer object's new data store.
         * \param data Specifies a pointer to data that will be copied into the data store.
         * \param flags Specifies the intended usage of the buffer's data store.
         * Accepted values are GL_DYNAMIC_STORAGE_BIT, GL_MAP_READ_BIT, GL_MAP_WRITE_BIT,
         * GL_MAP_PERSISTENT_BIT, GL_MAP_COHERENT_BIT, GL_CLIENT_STORAGE_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedBufferStorage(
            GLuint buffer, GLsizei size, const GLvoid* data, GLbitfield flags, const char* caller = nullptr) const;

        /**
         * \brief The glNamedBufferSubData function updates a subregion of a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size Specifies the size of the subregion to be updated.
         * \param data Specifies a pointer to the data to be copied into the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedBufferSubData(
            GLuint buffer, GLintptr offset, GLsizei size, const GLvoid* data, const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferDrawBuffer function specifies the color buffer to be drawn into.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param buf Specifies the color buffer to be drawn into.
         * Accepted values are GL_NONE, GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT, GL_BACK_RIGHT,
         * GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, GL_COLOR_ATTACHMENTi.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf, const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferDrawBuffers function specifies a list of color buffers to be drawn into.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param n  Specifies the number of buffers in the list.
         * \param bufs Specifies an array of color buffers to be drawn into.
         * Accepted values are GL_NONE, GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT, GL_BACK_RIGHT,
         * GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, GL_COLOR_ATTACHMENTi.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferDrawBuffers(
            GLuint framebuffer, GLsizei n, const GLenum* bufs, const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferParameteri function sets a named parameter of a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param pname Specifies the parameter to be set.
         * Accepted values are GL_FRAMEBUFFER_DEFAULT_WIDTH, GL_FRAMEBUFFER_DEFAULT_HEIGHT,
         * GL_FRAMEBUFFER_DEFAULT_LAYERS, GL_FRAMEBUFFER_DEFAULT_SAMPLES, GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS.
         * \param param Specifies the value to set the parameter to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferParameteri(
            GLuint framebuffer, GLenum pname, GLint param, [[maybe_unused]] const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferReadBuffer function specifies the color buffer to be read from.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param src Specifies the color buffer to be read from.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src, const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferRenderbuffer function attaches a renderbuffer to a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param attachment Specifies the attachment point of the framebuffer.
         *  Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param renderbuffertarget Specifies the renderbuffer target.
         *  Accepted value is GL_RENDERBUFFER.
         * \param renderbuffer Specifies the name of the renderbuffer object.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferRenderbuffer(
            GLuint framebuffer,
            GLenum attachment,
            GLenum renderbuffertarget,
            GLuint renderbuffer,
            const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferTexture function attaches a texture to a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the mipmap level of the texture image to be attached.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferTexture(
            GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, const char* caller = nullptr) const;

        /**
         * \brief The glNamedFramebufferTextureLayer function attaches a texture layer to a framebuffer object.
         *
         * \param framebuffer Specifies the name of the framebuffer object.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the mipmap level of the texture image to be attached.
         * \param layer Specifies the layer of the texture image to be attached.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedFramebufferTextureLayer(
            GLuint framebuffer,
            GLenum attachment,
            GLuint texture,
            GLint level,
            GLint layer,
            const char* caller = nullptr) const;

        /**
         * \brief The glNamedRenderbufferStorage function establishes data storage, format, and dimensions of a
         * renderbuffer object's image.
         *
         * \param renderbuffer Specifies the name of the renderbuffer object.
         * \param internalformat Specifies the internal format to be used for the renderbuffer object's image.
         *  Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the renderbuffer, in pixels.
         * \param height Specifies the height of the renderbuffer, in pixels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedRenderbufferStorage(
            GLuint renderbuffer,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glNamedRenderbufferStorageMultisample function establishes data storage, format, and dimensions
         * of a multisample renderbuffer object's image.
         *
         * \param renderbuffer Specifies the name of the renderbuffer object.
         * \param samples Specifies the number of samples to be used for the renderbuffer object's image.
         * \param internalformat Specifies the internal format to be used for the renderbuffer object's image.
         *  Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the renderbuffer, in pixels.
         * \param height Specifies the height of the renderbuffer, in pixels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNamedRenderbufferStorageMultisample(
            GLuint renderbuffer,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glReadnPixels function reads a block of pixels from the framebuffer.
         * \deprecated Deprecated in OpenGL 4.6. Use glReadnPixelsARB instead.
         *
         * \param x Specifies the x coordinate of the first pixel to be read.
         * \param y Specifies the y coordinate of the first pixel to be read.
         * \param width Specifies the width of the pixel rectangle.
         * \param height Specifies the height of the pixel rectangle.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param bufSize Specifies the size of the buffer to receive the pixel data.
         * \param data Specifies a pointer to the buffer to receive the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glReadnPixels(
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            GLsizei bufSize,
            GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureBarrier function ensures that writes to a texture are completed before subsequent reads
         * to that texture.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureBarrier(const char* caller = nullptr) const;

        /**
         * \brief The glTextureBuffer function attaches a buffer object's data store to a buffer texture.
         *
         * \param texture Specifies the name of the texture object.
         * \param internalformat Specifies the internal format of the data in the buffer texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB32F, GL_RGB32I, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F,
         * GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI.
         * \param buffer Specifies the name of the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureBuffer(
            GLuint texture, GLenum internalformat, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glTextureBufferRange function attaches a range of a buffer object's data store to a buffer
         * texture.
         *
         * \param texture Specifies the name of the texture object.
         * \param internalformat Specifies the internal format of the data in the buffer texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB32F, GL_RGB32I, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F,
         * GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI.
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size  Specifies the size of the range to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureBufferRange(
            GLuint texture,
            GLenum internalformat,
            GLuint buffer,
            GLintptr offset,
            GLsizeiptr size,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameterf function sets a floating-point parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameterf(GLuint texture, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameterfv function sets a floating-point parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies a pointer to the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameterfv(
            GLuint texture, GLenum pname, const GLfloat* param, const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameteri function sets an integer parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameteri(GLuint texture, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameterIiv function sets an integer parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param params Specifies a pointer to the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameterIiv(
            GLuint texture, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameterIuiv function sets an unsigned integer parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param params Specifies a pointer to the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameterIuiv(
            GLuint texture, GLenum pname, const GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTextureParameteriv function sets an integer parameter of a texture object.
         *
         * \param texture Specifies the name of the texture object.
         * \param pname Specifies the symbolic name of the texture parameter to be set.
         * Accepted values are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD,
         * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_PRIORITY,
         * GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_STENCIL_TEXTURE_MODE,
         * GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies a pointer to the value of the texture parameter to be set.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureParameteriv(
            GLuint texture, GLenum pname, const GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glTextureStorage1D function specifies the storage requirements for a one-dimensional texture.
         *
         * \param texture Specifies the name of the texture object.
         * \param levels Specifies the number of mipmap levels.
         * \param internalformat Specifies the internal format of the texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureStorage1D(
            GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, const char* caller = nullptr) const;

        /**
         * \brief The glTextureStorage2D function specifies the storage requirements for a two-dimensional texture.
         *
         * \param texture Specifies the name of the texture object.
         * \param levels Specifies the number of mipmap levels.
         * \param internalformat Specifies the internal format of the texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the texture.
         * \param height Specifies the height of the texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureStorage2D(
            GLuint texture,
            GLsizei levels,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureStorage2DMultisample function specifies the storage requirements for a two-dimensional
         * multisample texture.
         *
         * \param texture  Specifies the name of the texture object.
         * \param samples  Specifies the number of samples in the multisample texture.
         * \param internalformat Specifies the internal format of the data in the multisample texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the multisample texture.
         * \param height  Specifies the height of the multisample texture.
         * \param fixedsamplelocations Specifies whether the sample locations are fixed.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureStorage2DMultisample(
            GLuint texture,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureStorage3D function specifies the storage requirements for a three-dimensional texture.
         *
         * \param texture Specifies the name of the texture object.
         * \param levels Specifies the number of mipmap levels.
         * \param internalformat Specifies the internal format of the texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the texture.
         * \param height Specifies the height of the texture.
         * \param depth  Specifies the depth of the texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureStorage3D(
            GLuint texture,
            GLsizei levels,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureStorage3DMultisample function specifies the storage requirements for a
         * three-dimensional multisample texture.
         *
         * \param texture  Specifies the name of the texture object.
         * \param samples  Specifies the number of samples in the multisample texture.
         * \param internalformat Specifies the internal format of the data in the multisample texture.
         * Accepted values are GL_R8, GL_R16, GL_R16F, GL_R32F, GL_R8I, GL_R16I, GL_R32I,
         * GL_R8UI, GL_R16UI, GL_R32UI, GL_RG8, GL_RG16, GL_RG16F, GL_RG32F, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG8UI,
         * GL_RG16UI, GL_RG32UI, GL_RGB8, GL_RGB16, GL_RGB16F, GL_RGB32F, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB8UI,
         * GL_RGB16UI, GL_RGB32UI, GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I,
         * GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32,
         * GL_DEPTH_COMPONENT32F, GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, GL_STENCIL_INDEX8.
         * \param width  Specifies the width of the multisample texture.
         * \param height  Specifies the height of the multisample texture.
         * \param depth  Specifies the depth of the multisample texture.
         * \param fixedsamplelocations Specifies whether the sample locations are fixed.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureStorage3DMultisample(
            GLuint texture,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureSubImage1D function specifies a one-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureSubImage1D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLsizei width,
            GLenum format,
            GLenum type,
            const GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureSubImage2D function specifies a two-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureSubImage2D(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            const GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureSubImage3D function specifies a three-dimensional texture subimage.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param depth Specifies the depth of the subregion.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         * GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureSubImage3D(
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
            const char* caller = nullptr) const;

        /**
         * \brief The glTransformFeedbackBufferBase function binds a buffer object to a transform feedback buffer
         * binding point.
         *
         * \param xfb Specifies the name of the transform feedback object.
         * \param index Specifies the index of the transform feedback buffer binding point.
         * \param buffer Specifies the name of the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTransformFeedbackBufferBase(
            GLuint xfb, GLuint index, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glTransformFeedbackBufferRange function binds a range of a buffer object to a transform feedback
         * buffer binding point.
         *
         * \param xfb Specifies the name of the transform feedback object.
         * \param index Specifies the index of the transform feedback buffer binding point.
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size Specifies the size of the range to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTransformFeedbackBufferRange(
            GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char* caller = nullptr)
            const;

        /**
         * \brief The glUnmapNamedBuffer function unmaps a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if the data store was successfully unmapped, GL_FALSE otherwise.
         */
        GLboolean glUnmapNamedBuffer(GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayAttribBinding function associates a vertex attribute with a vertex buffer binding
         * point.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param attribindex Specifies the index of the vertex attribute to associate.
         * \param bindingindex Specifies the index of the vertex buffer binding point to associate with the vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayAttribBinding(
            GLuint vaobj, GLuint attribindex, GLuint bindingindex, const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayAttribFormat function specifies the organization of data in a vertex attribute
         * array.
         *
         * \param vaobj  Specifies the name of the vertex array object.
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT,
         * GL_INT, GL_UNSIGNED_INT, GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED,
         * GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, and
         * GL_UNSIGNED_INT_10F_11F_11F_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayAttribFormat(
            GLuint vaobj,
            GLuint attribindex,
            GLint size,
            GLenum type,
            GLboolean normalized,
            GLuint relativeoffset,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayAttribIFormat function specifies the organization of integer data in a vertex
         * attribute array.
         *
         * \param vaobj  Specifies the name of the vertex array object.
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT,
         * GL_INT, GL_UNSIGNED_INT, GL_INT_2_10_10_10_REV, and GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayAttribIFormat(
            GLuint vaobj,
            GLuint attribindex,
            GLint size,
            GLenum type,
            GLuint relativeoffset,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayAttribLFormat function specifies the organization of double data in a vertex
         * attribute array.
         *
         * \param vaobj  Specifies the name of the vertex array object.
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         * Accepted value is GL_DOUBLE.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayAttribLFormat(
            GLuint vaobj,
            GLuint attribindex,
            GLint size,
            GLenum type,
            GLuint relativeoffset,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayBindingDivisor function modifies the rate at which generic vertex attributes
         * advance during instanced rendering.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param bindingindex Specifies the index of the binding whose divisor to modify.
         * \param divisor Specifies the number of instances that will pass between updates of the generic
         * attribute at slot bindingindex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayBindingDivisor(
            GLuint vaobj, GLuint bindingindex, GLuint divisor, const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayElementBuffer function binds a buffer object to a vertex array object's element
         * array buffer binding point.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param buffer Specifies the name of the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayVertexBuffer function binds a buffer object to a vertex array object's vertex
         * buffer binding point.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param bindingindex Specifies the index of the vertex buffer binding point.
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset of the first element of the buffer.
         * \param stride Specifies the distance between elements within the buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayVertexBuffer(
            GLuint vaobj,
            GLuint bindingindex,
            GLuint buffer,
            GLintptr offset,
            GLsizei stride,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexArrayVertexBuffers function binds multiple buffer objects to a vertex array object's
         * vertex buffer binding points.
         *
         * \param vaobj Specifies the name of the vertex array object.
         * \param first Specifies the index of the first binding point to which a buffer object is to be bound.
         * \param count Specifies the number of buffer objects to be bound.
         * \param buffers Specifies an array of names of buffer objects to be bound.
         * \param offsets Specifies an array of offsets within the buffer objects.
         * \param strides Specifies an array of strides within the buffer objects.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexArrayVertexBuffers(
            GLuint vaobj,
            GLuint first,
            GLsizei count,
            const GLuint* buffers,
            const GLintptr* offsets,
            const GLsizei* strides,
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
