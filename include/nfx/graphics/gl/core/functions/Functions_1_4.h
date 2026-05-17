#pragma once

/**
 * \file Functions_1_4.h
 * \brief Declares the OpenGL 1.4 function wrapper interface.
 */

#include "Functions_1_3.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_4
     * \brief Exposes the OpenGL 1.4 function set.
     */
    class Functions_1_4 : public Functions_1_3
    {
        static inline bool s_loaded;

    public:
        explicit Functions_1_4();
        Functions_1_4(const Functions_1_4&) = delete;
        Functions_1_4& operator=(const Functions_1_4&) = delete;
        Functions_1_4(Functions_1_4&&) = delete;
        Functions_1_4& operator=(Functions_1_4&&) = delete;
        virtual ~Functions_1_4();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBlendFuncSeparate function specifies pixel arithmetic for RGB and alpha components separately.
         *
         * \param sfactorRGB Specifies how the red, green, and blue blending factors are computed.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE.
         * \param dfactorRGB Specifies how the red, green, and blue destination blending factors are computed.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA.
         * \param sfactorAlpha Specifies how the alpha source blending factor is computed.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
         * GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA.
         * \param dfactorAlpha Specifies how the alpha destination blending factor is computed.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
         * GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendFuncSeparate(
            GLenum sfactorRGB,
            GLenum dfactorRGB,
            GLenum sfactorAlpha,
            GLenum dfactorAlpha,
            const char* caller = nullptr) const;

        /**
         * \brief The glFogCoordd function sets the current fog coordinate.
         *
         * \param coord Specifies the fog coordinate value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogCoordd(GLdouble coord, const char* caller = nullptr) const;

        /**
         * \brief The glFogCoorddv function sets the current fog coordinate.
         *
         * \param coord Specifies a pointer to the fog coordinate value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogCoorddv(const GLdouble* coord, const char* caller = nullptr) const;

        /**
         * \brief The glFogCoordf function sets the current fog coordinate.
         *
         * \param coord Specifies the fog coordinate value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogCoordf(GLfloat coord, const char* caller = nullptr) const;

        /**
         * \brief The glFogCoordfv function sets the current fog coordinate.
         *
         * \param coord Specifies a pointer to the fog coordinate value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogCoordfv(const GLfloat* coord, const char* caller = nullptr) const;

        /**
         * \brief The glFogCoordPointer function defines an array of fog coordinates.
         * \deprecated Deprecated in OpenGL 3.2. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param type Specifies the data type of each fog coordinate in the array.
         * Accepted values are GL_FLOAT, GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive fog coordinates.
         * \param pointer Specifies a pointer to the first fog coordinate in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogCoordPointer(
            GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawArrays function renders multiple sets of primitives from array data.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP,
         * GL_TRIANGLE_FAN, GL_TRIANGLES.
         * \param first Specifies an array of starting indices in the enabled arrays.
         * \param count Specifies an array of the number of indices to be rendered.
         * \param drawcount Specifies the size of the first and count arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawArrays(
            GLenum mode,
            const GLint* first,
            const GLsizei* count,
            GLsizei drawcount,
            const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawElements function renders multiple sets of primitives by specifying indices of array
         * data elements.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP,
         * GL_TRIANGLE_FAN, GL_TRIANGLES.
         * \param count Specifies an array of the number of elements to be rendered.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT.
         * \param indices Specifies an array of pointers to the location where the indices are stored.
         * \param drawcount Specifies the size of the count and indices arrays.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawElements(
            GLenum mode,
            const GLsizei* count,
            GLenum type,
            const GLvoid* const* indices,
            GLsizei drawcount,
            const char* caller = nullptr) const;

        /**
         * \brief The glPointParameterf function sets the parameters for point sprites.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and point size arrays instead.
         *
         * \param pname Specifies the symbolic name of the point parameter.
         * Accepted values are GL_POINT_SIZE_MIN, GL_POINT_SIZE_MAX, GL_POINT_FADE_THRESHOLD_SIZE,
         * GL_POINT_DISTANCE_ATTENUATION.
         * \param param Specifies the value to be assigned to pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPointParameterf(GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glPointParameterfv function sets the parameters for point sprites.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and point size arrays instead.
         *
         * \param pname Specifies the symbolic name of the point parameter.
         * Accepted values are GL_POINT_SIZE_MIN, GL_POINT_SIZE_MAX, GL_POINT_FADE_THRESHOLD_SIZE,
         * GL_POINT_DISTANCE_ATTENUATION.
         * \param params Specifies a pointer to the value or values to be assigned to pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPointParameterfv(GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glPointParameteri function sets the parameters for point sprites.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and point size arrays instead.
         *
         * \param pname Specifies the symbolic name of the point parameter.
         * Accepted values are GL_POINT_SIZE_MIN, GL_POINT_SIZE_MAX, GL_POINT_FADE_THRESHOLD_SIZE,
         * GL_POINT_DISTANCE_ATTENUATION.
         * \param param Specifies the value to be assigned to pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPointParameteri(GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glPointParameteriv function sets the parameters for point sprites.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and point size arrays instead.
         *
         * \param pname Specifies the symbolic name of the point parameter.
         * Accepted values are GL_POINT_SIZE_MIN, GL_POINT_SIZE_MAX, GL_POINT_FADE_THRESHOLD_SIZE,
         * GL_POINT_DISTANCE_ATTENUATION.
         * \param params Specifies a pointer to the value or values to be assigned to pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPointParameteriv(GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3b function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3bv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3bv(const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3d function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3dv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3f function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3fv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3i function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3i(GLint red, GLint green, GLint blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3iv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3s function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3s(GLshort red, GLshort green, GLshort blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3sv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3ub function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3ubv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3ubv(const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3ui function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3uiv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3uiv(const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3us function sets the current secondary color.
         *
         * \param red Specifies the red component of the secondary color.
         * \param green Specifies the green component of the secondary color.
         * \param blue Specifies the blue component of the secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3us(GLushort red, GLushort green, GLushort blue, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColor3usv function sets the current secondary color.
         *
         * \param v Specifies a pointer to an array of three elements: red, green, and blue.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColor3usv(const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColorPointer function defines an array of secondary colors.
         * \deprecated Deprecated in OpenGL 3.2. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param size Specifies the number of components per secondary color.
         * Must be 3.
         * \param type Specifies the data type of each secondary color component.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive secondary colors.
         * \param pointer Specifies a pointer to the first component of the first secondary color element in the
         * array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColorPointer(
            GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        GLvoid glWindowPos2d(GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2dv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of two elements: x and y.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2f function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2f(GLfloat x, GLfloat y, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2fv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of two elements: x and y.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2i function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2i(GLint x, GLint y, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2iv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of two elements: x and y.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2s function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2s(GLshort x, GLshort y, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos2sv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of two elements: x and y.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos2sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3d function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param z Specifies the z coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3d(GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3dv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of three elements: x, y, and z.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3f function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param z Specifies the z coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3f(GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3fv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of three elements: x, y, and z.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3i function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param z Specifies the z coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3i(GLint x, GLint y, GLint z, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3iv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of three elements: x, y, and z.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3s function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param x Specifies the x coordinate of the raster position.
         * \param y Specifies the y coordinate of the raster position.
         * \param z Specifies the z coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3s(GLshort x, GLshort y, GLshort z, const char* caller = nullptr) const;

        /**
         * \brief The glWindowPos3sv function sets the current raster position.
         * \deprecated Deprecated in OpenGL 3.2. Use shaders and vertex attributes instead.
         *
         * \param v Specifies a pointer to an array of three elements: x, y, and z.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glWindowPos3sv(const GLshort* v, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
