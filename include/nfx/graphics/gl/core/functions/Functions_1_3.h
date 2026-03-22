#pragma once

/**
 * \file Functions_1_3.h
 * \brief Declares the OpenGL 1.3 function wrapper interface.
 */

#include "Functions_1_2.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_3
     * \brief Exposes the OpenGL 1.3 function set.
     */
    class Functions_1_3 : public Functions_1_2
    {
        static inline bool s_loaded;

    public:
        explicit Functions_1_3();
        Functions_1_3(const Functions_1_3&) = delete;
        Functions_1_3& operator=(const Functions_1_3&) = delete;
        Functions_1_3(Functions_1_3&&) = delete;
        Functions_1_3& operator=(Functions_1_3&&) = delete;
        virtual ~Functions_1_3();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glActiveTexture function selects which texture unit subsequent texture state calls will affect.
         *
         * \param texture Specifies which texture unit to make active.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glActiveTexture(GLenum texture, const char* caller = nullptr) const;

        /**
         * \brief The glClientActiveTexture function selects which texture unit subsequent vertex array calls will
         * affect.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param texture Specifies which texture unit to make active.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClientActiveTexture(GLenum texture, const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTexImage1D function specifies a one-dimensional compressed texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_1D and GL_PROXY_TEXTURE_1D.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the format of the compressed image data.
         * \param width  Specifies the width of the texture image.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data  Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexImage1D(
            GLenum target,
            GLint level,
            GLenum internalformat,
            GLsizei width,
            GLint border,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTexImage2D function specifies a two-dimensional compressed texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY,
         * GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, and GL_PROXY_TEXTURE_CUBE_MAP.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the format of the compressed image data.
         * \param width  Specifies the width of the texture image.
         * \param height Specifies the height of the texture image.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data  Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexImage2D(
            GLenum target,
            GLint level,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLint border,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTexImage3D function specifies a three-dimensional compressed texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_3D, GL_PROXY_TEXTURE_3D, GL_TEXTURE_2D_ARRAY,
         * GL_PROXY_TEXTURE_2D_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY, and GL_PROXY_TEXTURE_CUBE_MAP_ARRAY.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the format of the compressed image data.
         * \param width  Specifies the width of the texture image.
         * \param height Specifies the height of the texture image.
         * \param depth  Specifies the depth of the texture image.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data  Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexImage3D(
            GLenum target,
            GLint level,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            GLint border,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTexSubImage1D function specifies a one-dimensional compressed texture subimage.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_1D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param width Specifies the width of the texture subimage.
         * \param format Specifies the format of the compressed image data.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexSubImage1D(
            GLenum target,
            GLint level,
            GLint xoffset,
            GLsizei width,
            GLenum format,
            GLsizei imageSize,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCompressedTexSubImage2D function specifies a two-dimensional compressed texture subimage.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_2D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Z.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param yoffset Specifies a texel offset in the y direction within the texture array.
         * \param width Specifies the width of the texture subimage.
         * \param height Specifies the height of the texture subimage.
         * \param format Specifies the format of the compressed image data.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexSubImage2D(
            GLenum target,
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
         * \brief The glCompressedTexSubImage3D function specifies a three-dimensional compressed texture subimage.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_3D, GL_TEXTURE_2D_ARRAY, and GL_TEXTURE_CUBE_MAP_ARRAY.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param yoffset Specifies a texel offset in the y direction within the texture array.
         * \param zoffset Specifies a texel offset in the z direction within the texture array.
         * \param width Specifies the width of the texture subimage.
         * \param height Specifies the height of the texture subimage.
         * \param depth Specifies the depth of the texture subimage.
         * \param format Specifies the format of the compressed image data.
         * \param imageSize Specifies the number of bytes of compressed image data.
         * \param data Specifies a pointer to the compressed image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompressedTexSubImage3D(
            GLenum target,
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
         * \brief The glGetCompressedTexImage function retrieves a compressed texture image.
         * \deprecated Deprecated in OpenGL 3.0. Use glGetTextureSubImage instead.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
         * GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_ARRAY.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap
         * reduction image.
         * \param img Specifies a pointer to a buffer in which to return the compressed texture image.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetCompressedTexImage(GLenum target, GLint level, GLvoid* img, const char* caller = nullptr) const;

        /**
         * \brief The glLoadTransposeMatrixd function replaces the current matrix with the specified double-precision
         * matrix.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and uniform buffer objects (UBOs) instead.
         *
         * \param m Specifies a pointer to 16 consecutive values, which are used as the elements of a 4x4
         * column-major matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadTransposeMatrixd(const GLdouble* m, const char* caller = nullptr) const;

        /**
         * \brief The glLoadTransposeMatrixf function replaces the current matrix with the specified single-precision
         * matrix.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and uniform buffer objects (UBOs) instead.
         *
         * \param m Specifies a pointer to 16 consecutive values, which are used as the elements of a 4x4
         * column-major matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadTransposeMatrixf(const GLfloat* m, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1d function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1d(GLenum target, GLdouble s, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1dv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of one double-precision value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1dv(GLenum target, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1f function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1f(GLenum target, GLfloat s, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1fv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of one single-precision value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1fv(GLenum target, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1i function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1i(GLenum target, GLint s, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1iv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of one integer value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1iv(GLenum target, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1s function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1s(GLenum target, GLshort s, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord1sv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of one short value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord1sv(GLenum target, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2d function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2dv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of two double-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2dv(GLenum target, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2f function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2fv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of two single-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2fv(GLenum target, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2i function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2i(GLenum target, GLint s, GLint t, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2iv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of two integer values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2iv(GLenum target, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2s function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2s(GLenum target, GLshort s, GLshort t, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord2sv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of two short values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord2sv(GLenum target, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3d function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3dv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of three double-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3dv(GLenum target, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3f function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3fv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of three single-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3fv(GLenum target, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3i function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3iv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of three integer values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3iv(GLenum target, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3s function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord3sv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of three short values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord3sv(GLenum target, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4d function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param q Specifies the q coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4d(
            GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4dv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of four double-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4dv(GLenum target, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4f function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param q Specifies the q coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4f(
            GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4fv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of four single-precision values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4fv(GLenum target, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4i function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param q Specifies the q coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4iv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of four integer values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4iv(GLenum target, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4s function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param s Specifies the s coordinate.
         * \param t Specifies the t coordinate.
         * \param r Specifies the r coordinate.
         * \param q Specifies the q coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4s(
            GLenum target, GLshort s, GLshort t, GLshort r, GLshort q, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoord4sv function sets the current texture coordinates for the specified texture unit.
         * \deprecated Deprecated in OpenGL 3.1. Use vertex array objects (VAOs) instead.
         *
         * \param target Specifies which texture unit to set the coordinates for.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ..., up to GL_TEXTURE31.
         * \param v Specifies a pointer to an array of four short values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoord4sv(GLenum target, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glMultTransposeMatrixd function replaces the current matrix with the specified double-precision
         * matrix.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and uniform buffer objects (UBOs) instead.
         *
         * \param m Specifies a pointer to 16 consecutive values, which are used as the elements of a 4x4
         * column-major matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultTransposeMatrixd(const GLdouble* m, const char* caller = nullptr) const;

        /**
         * \brief The glMultTransposeMatrixf function replaces the current matrix with the specified single-precision
         * matrix.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and uniform buffer objects (UBOs) instead.
         *
         * \param m Specifies a pointer to 16 consecutive values, which are used as the elements of a 4x4
         * column-major matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultTransposeMatrixf(const GLfloat* m, const char* caller = nullptr) const;

        /**
         * \brief The glSampleCoverage function specifies multisample coverage parameters.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and multisample textures instead.
         *
         * \param value Specifies a single floating-point sample coverage value. The initial value is 1.0.
         * \param invert Specifies a boolean flag indicating whether the coverage masks should be inverted. The
         * initial value is GL_FALSE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSampleCoverage(GLfloat value, GLboolean invert, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
