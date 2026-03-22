#pragma once

/**
 * \file Functions_1_2.h
 * \brief Declares the OpenGL 1.2 function wrapper interface.
 */

#include "Functions_1_1.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_2
     * \brief Exposes the OpenGL 1.2 function set.
     */
    class Functions_1_2 : public Functions_1_1
    {
        static inline bool s_loaded;

    public:
        explicit Functions_1_2();
        Functions_1_2(const Functions_1_2&) = delete;
        Functions_1_2& operator=(const Functions_1_2&) = delete;
        Functions_1_2(Functions_1_2&&) = delete;
        Functions_1_2& operator=(Functions_1_2&&) = delete;
        virtual ~Functions_1_2();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glBlendColor function sets the blend color.
         *
         * \param red Specifies the red component of the blend color.
         * \param green Specifies the green component of the blend color.
         * \param blue Specifies the blue component of the blend color.
         * \param alpha Specifies the alpha component of the blend color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendColor(
            GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char* caller = nullptr) const;

        /**
         * \brief The glBlendEquation function sets the blend equation.
         *
         * \param mode Specifies the blend equation.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, and
         * GL_MAX.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendEquation(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glColorSubTable function respecifies a portion of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param start Specifies the starting index of the portion to be replaced.
         * \param count Specifies the number of entries in the portion to be replaced.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param data Specifies a pointer to the new pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorSubTable(
            GLenum target,
            GLsizei start,
            GLsizei count,
            GLenum format,
            GLenum type,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glColorTable function specifies a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         *  Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param internalformat Specifies the internal format of the color table.
         * \param width  Specifies the width of the color table.
         * \param format Specifies the format of the pixel data.
         *  Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR,
         * GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type  Specifies the data type of the pixel data.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_FLOAT.
         * \param table  Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorTable(
            GLenum target,
            GLenum internalformat,
            GLsizei width,
            GLenum format,
            GLenum type,
            const GLvoid* table,
            const char* caller = nullptr) const;

        /**
         * \brief The glColorTableParameterfv function sets the parameters of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param pname Specifies the symbolic name of a color table parameter.
         * Accepted values are GL_COLOR_TABLE_SCALE and GL_COLOR_TABLE_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorTableParameterfv(
            GLenum target, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glColorTableParameteriv function sets the parameters of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param pname Specifies the symbolic name of a color table parameter.
         * Accepted values are GL_COLOR_TABLE_SCALE and GL_COLOR_TABLE_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorTableParameteriv(
            GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionFilter1D function defines a one-dimensional convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         *  Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param internalformat Specifies the internal format of the convolution filter.
         * \param width  Specifies the width of the convolution filter.
         * \param format Specifies the format of the pixel data.
         *  Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR,
         * GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type  Specifies the data type of the pixel data.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_FLOAT.
         * \param image  Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionFilter1D(
            GLenum target,
            GLenum internalformat,
            GLsizei width,
            GLenum format,
            GLenum type,
            const GLvoid* image,
            const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionFilter2D function defines a two-dimensional convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         *  Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param internalformat Specifies the internal format of the convolution filter.
         * \param width  Specifies the width of the convolution filter.
         * \param height Specifies the height of the convolution filter.
         * \param format Specifies the format of the pixel data.
         *  Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR,
         * GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type  Specifies the data type of the pixel data.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_FLOAT.
         * \param image  Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionFilter2D(
            GLenum target,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            const GLvoid* image,
            const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionParameterf function sets the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params, const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionParameterfv function sets the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionParameterfv(
            GLenum target, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionParameteri function sets the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionParameteri(GLenum target, GLenum pname, GLint params, const char* caller = nullptr) const;

        /**
         * \brief The glConvolutionParameteriv function sets the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glConvolutionParameteriv(
            GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glCopyColorSubTable function respecifies a portion of a color table using pixels from the frame
         * buffer.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param start Specifies the starting index of the portion to be replaced.
         * \param x Specifies the window x coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param y Specifies the window y coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param width Specifies the width of the color table.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyColorSubTable(
            GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, const char* caller = nullptr) const;

        /**
         * \brief The glCopyColorTable function respecifies a color table using pixels from the frame buffer.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         *  Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param internalformat Specifies the internal format of the color table.
         * \param x  Specifies the window x coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param y  Specifies the window y coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param width  Specifies the width of the color table.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyColorTable(
            GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char* caller = nullptr) const;

        /**
         * \brief The glCopyConvolutionFilter1D function respecifies a one-dimensional convolution filter using pixels
         * from the frame buffer.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         *  Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param internalformat Specifies the internal format of the convolution filter.
         * \param x  Specifies the window x coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param y  Specifies the window y coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param width  Specifies the width of the convolution filter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyConvolutionFilter1D(
            GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char* caller = nullptr) const;

        /**
         * \brief The glCopyConvolutionFilter2D function respecifies a two-dimensional convolution filter using pixels
         * from the frame buffer.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         *  Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param internalformat Specifies the internal format of the convolution filter.
         * \param x  Specifies the window x coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param y  Specifies the window y coordinate of the lower-left corner of the rectangular region
         * of pixels to be copied.
         * \param width  Specifies the width of the convolution filter.
         * \param height Specifies the height of the convolution filter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyConvolutionFilter2D(
            GLenum target,
            GLenum internalformat,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyTexSubImage3D function copies a subimage from the frame buffer to a 3D texture.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_3D, GL_TEXTURE_2D_ARRAY, and GL_TEXTURE_CUBE_MAP_ARRAY.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies the x offset within the texture array.
         * \param yoffset Specifies the y offset within the texture array.
         * \param zoffset Specifies the z offset within the texture array.
         * \param x Specifies the window x coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param y Specifies the window y coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param width Specifies the width of the texture subimage.
         * \param height Specifies the height of the texture subimage.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTexSubImage3D(
            GLenum target,
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
         * \brief The glDrawRangeElements function renders primitives from array data.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP,
         * GL_TRIANGLE_FAN, and GL_TRIANGLES.
         * \param start Specifies the minimum array index contained in indices.
         * \param end Specifies the maximum array index contained in indices.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in indices.
         * Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawRangeElements(
            GLenum mode,
            GLuint start,
            GLuint end,
            GLsizei count,
            GLenum type,
            const GLvoid* indices,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetColorTable function retrieves the contents of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param table Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetColorTable(
            GLenum target, GLenum format, GLenum type, GLvoid* table, const char* caller = nullptr) const;

        /**
         * \brief The glGetColorTableParameterfv function retrieves the parameters of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param pname Specifies the symbolic name of a color table parameter.
         * Accepted values are GL_COLOR_TABLE_SCALE and GL_COLOR_TABLE_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetColorTableParameterfv(
            GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetColorTableParameteriv function retrieves the parameters of a color table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target color table.
         * Accepted values are GL_COLOR_TABLE, GL_POST_CONVOLUTION_COLOR_TABLE, and
         * GL_POST_COLOR_MATRIX_COLOR_TABLE.
         * \param pname Specifies the symbolic name of a color table parameter.
         * Accepted values are GL_COLOR_TABLE_SCALE and GL_COLOR_TABLE_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetColorTableParameteriv(
            GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetConvolutionFilter function retrieves the contents of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param image Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetConvolutionFilter(
            GLenum target, GLenum format, GLenum type, GLvoid* image, const char* caller = nullptr) const;

        /**
         * \brief The glGetConvolutionParameterfv function retrieves the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetConvolutionParameterfv(
            GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetConvolutionParameteriv function retrieves the parameters of a convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the convolution operation.
         * Accepted values are GL_CONVOLUTION_1D and GL_CONVOLUTION_2D.
         * \param pname Specifies the symbolic name of a convolution filter parameter.
         * Accepted values are GL_CONVOLUTION_BORDER_MODE, GL_CONVOLUTION_FILTER_SCALE, and
         * GL_CONVOLUTION_FILTER_BIAS.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetConvolutionParameteriv(
            GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetHistogram function retrieves the contents of a histogram table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target histogram table.
         * Accepted values are GL_HISTOGRAM and GL_PROXY_HISTOGRAM.
         * \param reset Specifies whether the histogram table is reset after the values are retrieved.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param values Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetHistogram(
            GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values, const char* caller = nullptr)
            const;

        /**
         * \brief The glGetHistogramParameterfv function retrieves the parameters of a histogram table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target histogram table.
         * Accepted values are GL_HISTOGRAM and GL_PROXY_HISTOGRAM.
         * \param pname Specifies the symbolic name of a histogram table parameter.
         * Accepted values are GL_HISTOGRAM_WIDTH, GL_HISTOGRAM_FORMAT, GL_HISTOGRAM_RED_SIZE,
         * GL_HISTOGRAM_GREEN_SIZE, GL_HISTOGRAM_BLUE_SIZE, GL_HISTOGRAM_ALPHA_SIZE, GL_HISTOGRAM_LUMINANCE_SIZE, and
         * GL_HISTOGRAM_SINK.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetHistogramParameterfv(
            GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetHistogramParameteriv function retrieves the parameters of a histogram table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target histogram table.
         * Accepted values are GL_HISTOGRAM and GL_PROXY_HISTOGRAM.
         * \param pname Specifies the symbolic name of a histogram table parameter.
         * Accepted values are GL_HISTOGRAM_WIDTH, GL_HISTOGRAM_FORMAT, GL_HISTOGRAM_RED_SIZE,
         * GL_HISTOGRAM_GREEN_SIZE, GL_HISTOGRAM_BLUE_SIZE, GL_HISTOGRAM_ALPHA_SIZE, GL_HISTOGRAM_LUMINANCE_SIZE, and
         * GL_HISTOGRAM_SINK.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetHistogramParameteriv(
            GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetMinmax function retrieves the minimum and maximum values of a minmax table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target minmax table.
         * Accepted values are GL_MINMAX and GL_PROXY_MINMAX.
         * \param reset Specifies whether the minmax table is reset after the values are retrieved.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param values Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMinmax(
            GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values, const char* caller = nullptr)
            const;

        /**
         * \brief The glGetMinmaxParameterfv function retrieves the parameters of a minmax table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target minmax table.
         * Accepted values are GL_MINMAX and GL_PROXY_MINMAX.
         * \param pname Specifies the symbolic name of a minmax table parameter.
         * Accepted values are GL_MINMAX_FORMAT and GL_MINMAX_SINK.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetMinmaxParameteriv function retrieves the parameters of a minmax table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target minmax table.
         * Accepted values are GL_MINMAX and GL_PROXY_MINMAX.
         * \param pname Specifies the symbolic name of a minmax table parameter.
         * Accepted values are GL_MINMAX_FORMAT and GL_MINMAX_SINK.
         * \param params Specifies a pointer to the parameter values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSeparableFilter function retrieves the contents of a separable filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the separable filter operation.
         * Accepted values are GL_SEPARABLE_2D.
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA,
         * GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_FLOAT.
         * \param row Specifies a pointer to the row filter data.
         * \param column Specifies a pointer to the column filter data.
         * \param span Specifies a pointer to the span filter data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSeparableFilter(
            GLenum target,
            GLenum format,
            GLenum type,
            GLvoid* row,
            GLvoid* column,
            GLvoid* span,
            const char* caller = nullptr) const;

        /**
         * \brief The glHistogram function defines a histogram table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target histogram table.
         *  Accepted values are GL_HISTOGRAM and GL_PROXY_HISTOGRAM.
         * \param width  Specifies the width of the histogram table.
         * \param internalformat Specifies the internal format of the histogram table.
         * \param sink  Specifies whether pixel data is discarded after the histogram table is updated.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glHistogram(
            GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, const char* caller = nullptr) const;

        /**
         * \brief The glMinmax function defines a minmax table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target minmax table.
         *  Accepted values are GL_MINMAX and GL_PROXY_MINMAX.
         * \param internalformat Specifies the internal format of the minmax table.
         * \param sink  Specifies whether pixel data is discarded after the minmax table is updated.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMinmax(GLenum target, GLenum internalformat, GLboolean sink, const char* caller = nullptr) const;

        /**
         * \brief The glResetHistogram function resets a histogram table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target histogram table.
         * Accepted values are GL_HISTOGRAM and GL_PROXY_HISTOGRAM.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glResetHistogram(GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glResetMinmax function resets a minmax table.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target minmax table.
         * Accepted values are GL_MINMAX and GL_PROXY_MINMAX.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glResetMinmax(GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glSeparableFilter2D function defines a two-dimensional separable convolution filter.
         * \deprecated Deprecated in OpenGL 3.0. Use shaders and textures instead.
         *
         * \param target Specifies the target of the separable filter operation.
         *  Accepted values are GL_SEPARABLE_2D.
         * \param internalformat Specifies the internal format of the separable filter.
         * \param width  Specifies the width of the separable filter.
         * \param height Specifies the height of the separable filter.
         * \param format Specifies the format of the pixel data.
         *  Accepted values are GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR,
         * GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type  Specifies the data type of the pixel data.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_FLOAT.
         * \param row  Specifies a pointer to the row filter data.
         * \param column Specifies a pointer to the column filter data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSeparableFilter2D(
            GLenum target,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            const GLvoid* row,
            const GLvoid* column,
            const char* caller = nullptr) const;

        /**
         * \brief  The glTexImage3D function specifies a three-dimensional texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_3D, GL_PROXY_TEXTURE_3D, GL_TEXTURE_2D_ARRAY,
         * GL_PROXY_TEXTURE_2D_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY, and GL_PROXY_TEXTURE_CUBE_MAP_ARRAY.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the number of color components in the texture.
         * \param width  Specifies the width of the texture image.
         * \param height Specifies the height of the texture image.
         * \param depth  Specifies the depth of the texture image.
         * \param border Specifies the width of the border.
         *  Must be either 0 or 1.
         * \param format Specifies the format of the pixel data.
         *  Accepted values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA,
         * GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER,
         * GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX.
         * \param type  Specifies the data type of the pixel data.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         * GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV,
         * GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV,
         * GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2,
         * GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_24_8, GL_UNSIGNED_INT_10F_11F_11F_REV,
         * GL_UNSIGNED_INT_5_9_9_9_REV, GL_FLOAT_32_UNSIGNED_INT_24_8_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexImage3D(
            GLenum target,
            GLint level,
            GLint internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            GLint border,
            GLenum format,
            GLenum type,
            const GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexSubImage3D function specifies a three-dimensional texture subimage.
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
         * \param format Specifies the format of the pixel data.
         * Accepted values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER,
         * GL_BGRA_INTEGER, GL_STENCIL_INDEX.
         * \param type Specifies the data type of the pixel data.
         * Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
         * GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8,
         * GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV,
         * GL_UNSIGNED_INT_24_8, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV,
         * GL_FLOAT_32_UNSIGNED_INT_24_8_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexSubImage3D(
            GLenum target,
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
    };
} // namespace nfx::graphics::gl
