#pragma once

/**
 * \file Functions_1_0.h
 * \brief Declares the OpenGL 1.0 function wrapper interface.
 */

#include "nfx/graphics/gl/core/GlTypes.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_0
     * \brief Exposes the OpenGL 1.0 function set.
     */
    class Functions_1_0
    {
    public:
        explicit Functions_1_0();
        Functions_1_0(const Functions_1_0&) = delete;
        Functions_1_0& operator=(const Functions_1_0&) = delete;
        Functions_1_0(Functions_1_0&&) = delete;
        Functions_1_0& operator=(Functions_1_0&&) = delete;
        virtual ~Functions_1_0();

        /**
         * \brief The glAccum function operates on the accumulation buffer.
         *
         * \param op Specifies the accumulation buffer operation. Accepted symbolic constants are GL_ACCUM,
         * GL_LOAD, GL_RETURN, GL_MULT, and GL_ADD.
         * \param value A floating-point value used in the accumulation buffer operation. The op parameter
         * determines how value is used.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \details The glAccum function performs operations on the accumulation buffer, which is used for a variety of
         * advanced rendering techniques such as full-scene anti-aliasing, motion blur, and depth of field effects. The
         * specific operation performed depends on the value of the op parameter. For example, GL_ACCUM adds the value
         * to the current contents of the accumulation buffer, while GL_LOAD replaces the contents with the value.
         */
        GLvoid glAccum(GLenum op, GLfloat value, const char* caller = nullptr) const;

        /**
         * \brief The glAlphaFunc function enables your application to set the alpha test function.
         *
         * \param func Specifies the alpha comparison function. Accepted symbolic constants are GL_NEVER, GL_LESS,
         * GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, and GL_ALWAYS.
         * \param ref Specifies the reference value to which incoming alpha values are compared. This value is
         * clamped to the range 0 through 1, where 0 represents the lowest possible alpha value and 1 the highest
         * possible value. The default reference is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glAlphaFunc(GLenum func, GLclampf ref, const char* caller = nullptr) const;

        /**
         * \brief The glBegin function delimits the vertices of a primitive or a group of like primitives.
         *
         * \param mode Specifies the primitive or primitives that will be created from vertices presented between
         * GLBegin and the subsequent glEnd. Accepted symbolic constants are GL_POINTS, GL_LINES, GL_LINE_STRIP,
         * GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS, GL_QUAD_STRIP, and GL_POLYGON.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBegin(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glBitmap function draws a bitmap at the current raster position.
         *
         * \param width Specifies the width of the bitmap image.
         * \param height Specifies the height of the bitmap image.
         * \param xorig Specifies the x-coordinate of the bitmap's origin.
         * \param yorig Specifies the y-coordinate of the bitmap's origin.
         * \param xmove Specifies the x offset to be added to the current raster position after the bitmap is drawn.
         * \param ymove Specifies the y offset to be added to the current raster position after the bitmap is drawn.
         * \param bitmap Specifies a pointer to the bitmap image data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBitmap(
            GLsizei width,
            GLsizei height,
            GLfloat xorig,
            GLfloat yorig,
            GLfloat xmove,
            GLfloat ymove,
            const GLubyte* bitmap,
            const char* caller = nullptr) const;

        /**
         * \brief The glBlendFunc function specifies pixel arithmetic.
         *
         * \param sfactor Specifies how the red, green, blue, and alpha source blending factors are computed. The
         * initial value is GL_ONE.
         * \param dfactor Specifies how the red, green, blue, and alpha destination blending factors are computed. The
         * initial value is GL_ZERO.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendFunc(GLenum sfactor, GLenum dfactor, const char* caller = nullptr) const;

        /**
         * \brief The glCallList function executes a display list.
         *
         * \param list Specifies the integer name of the display list to be executed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCallList(GLuint list, const char* caller = nullptr) const;

        /**
         * \brief The glCallLists function executes a list of display lists.
         *
         * \param n Specifies the number of display lists to be executed.
         * \param type Specifies the type of values in lists. Symbolic constants GL_BYTE, GL_UNSIGNED_BYTE,
         * GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, and GL_2_BYTES, GL_3_BYTES, GL_4_BYTES are
         * accepted.
         * \param lists Specifies a pointer to an array of names to be executed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCallLists(GLsizei n, GLenum type, const GLvoid* lists, const char* caller = nullptr) const;

        /**
         * \brief The glClear function clears buffers to preset values.
         *
         * \param mask Bitwise OR of masks that indicate the buffers to be cleared. The four masks are
         * GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_ACCUM_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClear(GLbitfield mask, const char* caller = nullptr) const;

        /**
         * \brief The glClearAccum function sets the clear values for the accumulation buffer.
         *
         * \param red Specifies the red value used when the accumulation buffer is cleared. The initial value is 0.
         * \param green Specifies the green value used when the accumulation buffer is cleared. The initial value is 0.
         * \param blue Specifies the blue value used when the accumulation buffer is cleared. The initial value is 0.
         * \param alpha Specifies the alpha value used when the accumulation buffer is cleared. The initial value is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearAccum(
            GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char* caller = nullptr) const;

        /**
         * \brief The glClearColor function specifies clear values for the color buffers.
         *
         * \param red Specifies the red value used when the color buffers are cleared. The initial value is 0.
         * \param green Specifies the green value used when the color buffers are cleared. The initial value is 0.
         * \param blue Specifies the blue value used when the color buffers are cleared. The initial value is 0.
         * \param alpha Specifies the alpha value used when the color buffers are cleared. The initial value is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearColor(
            GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha, const char* caller = nullptr) const;

        /**
         * \brief The glClearDepth function specifies the clear value for the depth buffer.
         *
         * \param depth Specifies the depth value used when the depth buffer is cleared. The initial value is 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearDepth(GLdouble depth, const char* caller = nullptr) const;

        /**
         * \brief The glClearIndex function specifies the clear value for the color index buffers.
         *
         * \param c Specifies the index used when the color index buffers are cleared. The initial value is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearIndex(GLfloat c, const char* caller = nullptr) const;

        /**
         * \brief The glClearStencil function specifies the clear value for the stencil buffer.
         *
         * \param s Specifies the index used when the stencil buffer is cleared. The initial value is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearStencil(GLint s, const char* caller = nullptr) const;

        /**
         * \brief The glClipPlane function specifies a plane against which all geometry is clipped.
         *
         * \param plane Specifies which clipping plane is being positioned. Symbolic names of the form
         * GL_CLIP_PLANEi, where i is an integer between 0 and GL_MAX_CLIP_PLANES - 1, are accepted.
         * \param equation Specifies the address of an array of four double-precision floating-point values. These
         * values are interpreted as a plane equation.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClipPlane(GLenum plane, const GLdouble* equation, const char* caller = nullptr) const;

        /**
         * \brief The glColor3b function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3b(GLbyte red, GLbyte green, GLbyte blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3bv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3bv(const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3d function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3d(GLdouble red, GLdouble green, GLdouble blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3dv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3f function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3f(GLfloat red, GLfloat green, GLfloat blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3fv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3i function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3i(GLint red, GLint green, GLint blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3iv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3s function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3s(GLshort red, GLshort green, GLshort blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3sv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3ub function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3ub(GLubyte red, GLubyte green, GLubyte blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3ubv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3ubv(const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3ui function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3ui(GLuint red, GLuint green, GLuint blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3uiv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3uiv(const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor3us function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3us(GLushort red, GLushort green, GLushort blue, const char* caller = nullptr) const;

        /**
         * \brief The glColor3usv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, and blue components of the
         * current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor3usv(const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4b function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4bv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4bv(const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4d function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4d(
            GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4dv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4f function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4fv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4i function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4i(GLint red, GLint green, GLint blue, GLint alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4iv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4s function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4sv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4ub function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4ubv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4ubv(const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4ui function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4uiv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4uiv(const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glColor4us function sets the current color.
         *
         * \param red Specifies the red component of the current color.
         * \param green Specifies the green component of the current color.
         * \param blue Specifies the blue component of the current color.
         * \param alpha Specifies the alpha component of the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4us(
            GLushort red, GLushort green, GLushort blue, GLushort alpha, const char* caller = nullptr) const;

        /**
         * \brief The glColor4usv function sets the current color.
         *
         * \param v Specifies a pointer to an array that contains the red, green, blue, and alpha components of
         * the current color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColor4usv(const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glColorMaterial function specifies which material parameters track the current color.
         *
         * \param face Specifies whether front, back, or both front and back material parameters should track the
         * current color. Accepted values are GL_FRONT, GL_BACK, and GL_FRONT_AND_BACK.
         * \param mode Specifies which of several material parameters track the current color. Accepted values are
         * GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR, GL_EMISSION, and GL_AMBIENT_AND_DIFFUSE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorMaterial(GLenum face, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glColorMask function enables and disables writing of frame buffer color components.
         *
         * \param red Specifies whether the red component is enabled for writing. If GL_FALSE, the red component
         * is not written. If GL_TRUE, the red component is written.
         * \param green Specifies whether the green component is enabled for writing. If GL_FALSE, the green
         * component is not written. If GL_TRUE, the green component is written.
         * \param blue Specifies whether the blue component is enabled for writing. If GL_FALSE, the blue component
         * is not written. If GL_TRUE, the blue component is written.
         * \param alpha Specifies whether the alpha component is enabled for writing. If GL_FALSE, the alpha
         * component is not written. If GL_TRUE, the alpha component is written.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorMask(
            GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, const char* caller = nullptr) const;

        /**
         * \brief The glCopyPixels function copies pixels in the frame buffer.
         *
         * \param x Specifies the window x coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param y Specifies the window y coordinate of the lower-left corner of the rectangular region of
         * pixels to be copied.
         * \param width Specifies the width of the rectangular region of pixels to be copied.
         * \param height Specifies the height of the rectangular region of pixels to be copied.
         * \param type Specifies the type of pixel data to be copied. Accepted values are GL_COLOR, GL_DEPTH, and
         * GL_STENCIL.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyPixels(
            GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, const char* caller = nullptr) const;

        /**
         * \brief The glCullFace function specifies whether front- or back-facing facets can be culled.
         *
         * \param mode Specifies whether front- or back-facing facets are candidates for culling. Accepted values
         * are GL_FRONT, GL_BACK, and GL_FRONT_AND_BACK. The initial value is GL_BACK.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCullFace(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteLists function deletes a contiguous group of display lists.
         *
         * \param list Specifies the integer name of the first display list to delete.
         * \param range Specifies the number of display lists to delete.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteLists(GLuint list, GLsizei range, const char* caller = nullptr) const;

        /**
         * \brief The glDepthFunc function specifies the value used for depth buffer comparisons.
         *
         * \param func Specifies the depth comparison function. Accepted values are GL_NEVER, GL_LESS, GL_EQUAL,
         * GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, and GL_ALWAYS. The initial value is GL_LESS.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthFunc(GLenum func, const char* caller = nullptr) const;

        /**
         * \brief The glDepthMask function enables or disables writing into the depth buffer.
         *
         * \param flag Specifies whether the depth buffer is enabled for writing. If GL_FALSE, depth buffer writing
         * is disabled. If GL_TRUE, depth buffer writing is enabled. The initial value is GL_TRUE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthMask(GLboolean flag, const char* caller = nullptr) const;

        /**
         * \brief The glDepthRange function specifies mapping of depth values from normalized device
         * coordinates to window coordinates.
         *
         * \param n Specifies the mapping of the near clipping plane to window coordinates. The initial value is
         * 0.
         * \param f Specifies the mapping of the far clipping plane to window coordinates. The initial value
         * is 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthRange(GLdouble n, GLdouble f, const char* caller = nullptr) const;

        /**
         * \brief The glDisable function disables server-side GL capabilities.
         *
         * \param cap Specifies a symbolic constant indicating a GL capability. Accepted values include GL_BLEND,
         * GL_CULL_FACE, GL_DEPTH_TEST, GL_DITHER, GL_LIGHTING, GL_LINE_SMOOTH, GL_POLYGON_SMOOTH, GL_SCISSOR_TEST,
         * GL_STENCIL_TEST, and others.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDisable(GLenum cap, const char* caller = nullptr) const;

        /**
         * \brief The glDrawBuffer function specifies which color buffers are to be drawn into.
         *
         * \param buf Specifies up to four color buffers to be drawn into. Accepted values are GL_NONE,
         * GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT, GL_BACK_RIGHT, GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, and
         * GL_AUXi, where i is between 0 and GL_AUX_BUFFERS - 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawBuffer(GLenum buf, const char* caller = nullptr) const;

        /**
         * \brief The glDrawPixels function writes a block of pixels to the frame buffer.
         *
         * \param width Specifies the width of the pixel rectangle.
         * \param height Specifies the height of the pixel rectangle.
         * \param format Specifies the format of the pixel data. Accepted values are GL_COLOR_INDEX,
         * GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and
         * GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data. Accepted values are GL_UNSIGNED_BYTE, GL_BYTE,
         * GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, and GL_FLOAT.
         * \param pixels Specifies a pointer to the pixel data.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawPixels(
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            const GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glEdgeFlag function sets the current edge flag.
         *
         * \param flag Specifies the current edge flag value. If GL_TRUE, edges are boundary edges. If GL_FALSE,
         * edges are non-boundary edges.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEdgeFlag(GLboolean flag, const char* caller = nullptr) const;

        /**
         * \brief The glEdgeFlagv function sets the current edge flag.
         *
         * \param flag Specifies a pointer to an array that contains the edge flag value. If the value is GL_TRUE,
         * edges are boundary edges. If the value is GL_FALSE, edges are non-boundary edges.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEdgeFlagv(const GLboolean* flag, const char* caller = nullptr) const;

        /**
         * \brief The glEnable function enables server-side GL capabilities.
         *
         * \param cap Specifies a symbolic constant indicating a GL capability. Accepted values include GL_BLEND,
         * GL_CULL_FACE, GL_DEPTH_TEST, GL_DITHER, GL_LIGHTING, GL_LINE_SMOOTH, GL_POLYGON_SMOOTH, GL_SCISSOR_TEST,
         * GL_STENCIL_TEST, and others.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnable(GLenum cap, const char* caller = nullptr) const;

        /**
         * \brief The glEnd function marks the end of a glBegin call.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnd(const char* caller = nullptr) const;

        /**
         * \brief The glEndList function creates or replaces a display list.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEndList(const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord1d function evaluates a one-dimensional map at a specified domain coordinate.
         *
         * \param u Specifies a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord1d(GLdouble u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord1dv function evaluates a one-dimensional map at a specified domain
         * coordinate.
         *
         * \param u Specifies a pointer to an array containing a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord1dv(const GLdouble* u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord1f function evaluates a one-dimensional map at a specified domain coordinate.
         *
         * \param u Specifies a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord1f(GLfloat u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord1fv function evaluates a one-dimensional map at a specified domain
         * coordinate.
         *
         * \param u Specifies a pointer to an array containing a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord1fv(const GLfloat* u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord2d function evaluates a two-dimensional map at specified domain coordinates.
         *
         * \param u Specifies a domain coordinate.
         * \param v Specifies a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord2d(GLdouble u, GLdouble v, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord2dv function evaluates a two-dimensional map at specified domain coordinates.
         *
         * \param u Specifies a pointer to an array containing the domain coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord2dv(const GLdouble* u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord2f function evaluates a two-dimensional map at specified domain coordinates.
         *
         * \param u Specifies a domain coordinate.
         * \param v Specifies a domain coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord2f(GLfloat u, GLfloat v, const char* caller = nullptr) const;

        /**
         * \brief The glEvalCoord2fv function evaluates a two-dimensional map at specified domain coordinates.
         *
         * \param u Specifies a pointer to an array containing the domain coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalCoord2fv(const GLfloat* u, const char* caller = nullptr) const;

        /**
         * \brief The glEvalMesh1 function computes a one-dimensional grid of points or lines.
         *
         * \param mode Specifies whether to compute a grid of points or lines. Accepted values are GL_POINT and
         * GL_LINE.
         * \param i1 Specifies the first integer value for grid domain variable i.
         * \param i2 Specifies the last integer value for grid domain variable i.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalMesh1(GLenum mode, GLint i1, GLint i2, const char* caller = nullptr) const;

        /**
         * \brief The glEvalMesh2 function computes a two-dimensional grid of points or lines.
         *
         * \param mode Specifies whether to compute a grid of points or lines. Accepted values are GL_POINT and
         * GL_LINE.
         * \param i1 Specifies the first integer value for grid domain variable i.
         * \param i2 Specifies the last integer value for grid domain variable i.
         * \param j1 Specifies the first integer value for grid domain variable j.
         * \param j2 Specifies the last integer value for grid domain variable j.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2, const char* caller = nullptr) const;

        /**
         * \brief The glEvalPoint1 function generates and evaluates a single point in a one-dimensional grid.
         *
         * \param i Specifies the integer value for grid domain variable i.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalPoint1(GLint i, const char* caller = nullptr) const;

        /**
         * \brief The glEvalPoint2 function generates and evaluates a single point in a two-dimensional grid.
         *
         * \param i Specifies the integer value for grid domain variable i.
         * \param j Specifies the integer value for grid domain variable j.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEvalPoint2(GLint i, GLint j, const char* caller = nullptr) const;

        /**
         * \brief The glFeedbackBuffer function returns information about primitives that would have been
         * drawn.
         *
         * \param size Specifies the maximum number of values that can be stored in the buffer.
         * \param type Specifies the type of information to be returned. Accepted values are GL_2D, GL_3D,
         * GL_3D_COLOR, GL_3D_COLOR_TEXTURE, and GL_4D_COLOR_TEXTURE.
         * \param buffer Specifies a pointer to an array of floating-point values into which feedback data is placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer, const char* caller = nullptr) const;

        /**
         * \brief The glFinish function forces the execution of all previously issued GL commands.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFinish(const char* caller = nullptr) const;

        /**
         * \brief The glFlush function forces the execution of all previously issued GL commands to complete
         * in finite time.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFlush(const char* caller = nullptr) const;

        /**
         * \brief The glFogf function sets the fog parameters.
         *
         * \param pname Specifies a single-valued fog parameter. Accepted values are GL_FOG_MODE, GL_FOG_DENSITY,
         * GL_FOG_START, GL_FOG_END, and GL_FOG_INDEX.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogf(GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glFogfv function sets the fog parameters.
         *
         * \param pname Specifies a fog parameter. Accepted values are GL_FOG_MODE, GL_FOG_DENSITY, GL_FOG_START,
         * GL_FOG_END, GL_FOG_INDEX, GL_FOG_COLOR.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogfv(GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glFogi function sets the fog parameters.
         *
         * \param pname Specifies a single-valued fog parameter. Accepted values are GL_FOG_MODE, GL_FOG_DENSITY,
         * GL_FOG_START, GL_FOG_END, and GL_FOG_INDEX.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogi(GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glFogiv function sets the fog parameters.
         *
         * \param pname Specifies a fog parameter. Accepted values are GL_FOG_MODE, GL_FOG_DENSITY, GL_FOG_START,
         * GL_FOG_END, GL_FOG_INDEX, GL_FOG_COLOR.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFogiv(GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glFrontFace function defines the front- and back-facing polygons.
         *
         * \param mode Specifies the orientation of front-facing polygons. Accepted values are GL_CW and GL_CCW.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFrontFace(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glFrustum function multiplies the current matrix by a perspective matrix.
         *
         * \param left Specifies the coordinate for the left vertical clipping plane.
         * \param right Specifies the coordinate for the right vertical clipping plane.
         * \param bottom Specifies the coordinate for the bottom horizontal clipping plane.
         * \param top Specifies the coordinate for the top horizontal clipping plane.
         * \param zNear Specifies the distance to the near depth clipping plane. Must be positive.
         * \param zFar Specifies the distance to the far depth clipping plane. Must be positive.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFrustum(
            GLdouble left,
            GLdouble right,
            GLdouble bottom,
            GLdouble top,
            GLdouble zNear,
            GLdouble zFar,
            const char* caller = nullptr) const;

        /**
         * \brief The glGenLists function generates a contiguous set of empty display lists.
         *
         * \param range Specifies the number of contiguous empty display lists to be generated.
         * \param caller Optional parameter to specify the caller function or context.
         * \return The integer name of the first display list.
         */
        GLuint glGenLists(GLsizei range, const char* caller = nullptr) const;

        /**
         * \brief The glGetBooleanv function returns the boolean value or values of a selected parameter.
         *
         * \param pname Specifies the parameter value to be returned.
         * \param data Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBooleanv(GLenum pname, GLboolean* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetClipPlane function returns the coefficients of the specified clipping plane.
         *
         * \param plane Specifies a clipping plane. Accepted values are GL_CLIP_PLANEi, where i is an integer
         * between 0 and GL_MAX_CLIP_PLANES - 1.
         * \param equation Specifies an array in which the returned coefficients are placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetClipPlane(GLenum plane, GLdouble* equation, const char* caller = nullptr) const;

        /**
         * \brief The glGetDoublev function returns the double value or values of a selected parameter.
         *
         * \param pname Specifies the parameter value to be returned.
         * \param data Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetDoublev(GLenum pname, GLdouble* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetError function returns error information.
         *
         * \param caller Optional parameter to specify the caller function or context.
         * \return The value of the error flag.
         */
        GLenum glGetError(const char* caller = nullptr) const;

        /**
         * \brief The glGetFloatv function returns the float value or values of a selected parameter.
         *
         * \param pname Specifies the parameter value to be returned.
         * \param data Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetFloatv(GLenum pname, GLfloat* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetIntegerv function returns the integer value or values of a selected parameter.
         *
         * \param pname Specifies the parameter value to be returned.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetIntegerv(GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetLightfv function returns the float value or values of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a light source parameter for which the value or values will be returned.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetLightfv(GLenum light, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetLightiv function returns the integer value or values of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a light source parameter for which the value or values will be returned.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetLightiv(GLenum light, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetMapdv function returns the double value or values of a selected evaluator
         * parameter.
         *
         * \param target Specifies the evaluator target. Accepted values are GL_MAP1_VERTEX_3, GL_MAP1_VERTEX_4,
         * GL_MAP1_INDEX, GL_MAP1_COLOR_4, GL_MAP1_NORMAL, GL_MAP1_TEXTURE_COORD_1, GL_MAP1_TEXTURE_COORD_2,
         * GL_MAP1_TEXTURE_COORD_3, GL_MAP1_TEXTURE_COORD_4, GL_MAP2_VERTEX_3, GL_MAP2_VERTEX_4, GL_MAP2_INDEX,
         * GL_MAP2_COLOR_4, GL_MAP2_NORMAL, GL_MAP2_TEXTURE_COORD_1, GL_MAP2_TEXTURE_COORD_2, GL_MAP2_TEXTURE_COORD_3,
         * and GL_MAP2_TEXTURE_COORD_4.
         * \param query Specifies the information to be returned. Accepted values are GL_COEFF, GL_ORDER, and
         * GL_DOMAIN.
         * \param v Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMapdv(GLenum target, GLenum query, GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glGetMapfv function returns the float value or values of a selected evaluator parameter.
         *
         * \param target Specifies the evaluator target. Accepted values are GL_MAP1_VERTEX_3, GL_MAP1_VERTEX_4,
         * GL_MAP1_INDEX, GL_MAP1_COLOR_4, GL_MAP1_NORMAL, GL_MAP1_TEXTURE_COORD_1, GL_MAP1_TEXTURE_COORD_2,
         * GL_MAP1_TEXTURE_COORD_3, GL_MAP1_TEXTURE_COORD_4, GL_MAP2_VERTEX_3, GL_MAP2_VERTEX_4, GL_MAP2_INDEX,
         * GL_MAP2_COLOR_4, GL_MAP2_NORMAL, GL_MAP2_TEXTURE_COORD_1, GL_MAP2_TEXTURE_COORD_2, GL_MAP2_TEXTURE_COORD_3,
         * and GL_MAP2_TEXTURE_COORD_4.
         * \param query Specifies the information to be returned. Accepted values are GL_COEFF, GL_ORDER, and
         * GL_DOMAIN.
         * \param v Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMapfv(GLenum target, GLenum query, GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glGetMapiv function returns the integer value or values of a selected evaluator
         * parameter.
         *
         * \param target Specifies the evaluator target. Accepted values are GL_MAP1_VERTEX_3, GL_MAP1_VERTEX_4,
         * GL_MAP1_INDEX, GL_MAP1_COLOR_4, GL_MAP1_NORMAL, GL_MAP1_TEXTURE_COORD_1, GL_MAP1_TEXTURE_COORD_2,
         * GL_MAP1_TEXTURE_COORD_3, GL_MAP1_TEXTURE_COORD_4, GL_MAP2_VERTEX_3, GL_MAP2_VERTEX_4, GL_MAP2_INDEX,
         * GL_MAP2_COLOR_4, GL_MAP2_NORMAL, GL_MAP2_TEXTURE_COORD_1, GL_MAP2_TEXTURE_COORD_2, GL_MAP2_TEXTURE_COORD_3,
         * and GL_MAP2_TEXTURE_COORD_4.
         * \param query Specifies the information to be returned. Accepted values are GL_COEFF, GL_ORDER, and
         * GL_DOMAIN.
         * \param v Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMapiv(GLenum target, GLenum query, GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glGetMaterialfv function returns the float value or values of a material parameter.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be returned. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMaterialfv(GLenum face, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetMaterialiv function returns the integer value or values of a material parameter.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be returned. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetMaterialiv(GLenum face, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetPixelMapfv function returns the float values of a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param values Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetPixelMapfv(GLenum map, GLfloat* values, const char* caller = nullptr) const;

        /**
         * \brief The glGetPixelMapuiv function returns the unsigned integer values of a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param values Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetPixelMapuiv(GLenum map, GLuint* values, const char* caller = nullptr) const;

        /**
         * \brief The glGetPixelMapusv function returns the unsigned short values of a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param values Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetPixelMapusv(GLenum map, GLushort* values, const char* caller = nullptr) const;

        /**
         * \brief The glGetPolygonStipple function returns the stipple pattern for polygons.
         *
         * \param mask Specifies a pointer to an array in which the returned stipple pattern will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetPolygonStipple(GLubyte* mask, const char* caller = nullptr) const;

        /**
         * \brief The glGetString function returns a string describing the current OpenGL connection.
         *
         * \param name Specifies a symbolic constant, one of GL_VENDOR, GL_RENDERER, GL_VERSION, or GL_EXTENSIONS.
         * \param caller Optional parameter to specify the caller function or context.
         * \return A string describing the current OpenGL connection.
         */
        const GLubyte* glGetString(GLenum name, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexEnvfv function returns the float value or values of a texture environment
         * parameter.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexEnvfv(GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexEnviv function returns the integer value or values of a texture environment
         * parameter.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexEnviv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexGendv function returns the double value or values of a texture coordinate
         * generation parameter.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexGenfv function returns the float value or values of a texture coordinate
         * generation parameter.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexGeniv function returns the integer value or values of a texture coordinate
         * generation parameter.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexGeniv(GLenum coord, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexImage function returns a texture image.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and
         * GL_TEXTURE_3D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param format Specifies the format of the pixel data. Accepted values are GL_RED, GL_GREEN, GL_BLUE,
         * GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data. Accepted values are GL_UNSIGNED_BYTE, GL_BYTE,
         * GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, and GL_FLOAT.
         * \param pixels Specifies a pointer to a buffer in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexImage(
            GLenum target, GLint level, GLenum format, GLenum type, void* pixels, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexLevelParameterfv function returns the float value or values of a texture
         * parameter for a specific level of detail.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and
         * GL_TEXTURE_3D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param pname Specifies the symbolic name of a texture parameter. Accepted values are GL_TEXTURE_WIDTH,
         * GL_TEXTURE_HEIGHT, GL_TEXTURE_DEPTH, GL_TEXTURE_INTERNAL_FORMAT, GL_TEXTURE_BORDER_COLOR, and
         * GL_TEXTURE_BORDER.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexLevelParameterfv(
            GLenum target, GLint level, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexLevelParameteriv function returns the integer value or values of a texture
         * parameter for a specific level of detail.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and
         * GL_TEXTURE_3D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param pname Specifies the symbolic name of a texture parameter. Accepted values are GL_TEXTURE_WIDTH,
         * GL_TEXTURE_HEIGHT, GL_TEXTURE_DEPTH, GL_TEXTURE_INTERNAL_FORMAT, GL_TEXTURE_BORDER_COLOR, and
         * GL_TEXTURE_BORDER.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexLevelParameteriv(
            GLenum target, GLint level, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexParameterfv function returns the float value or values of a texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and
         * GL_TEXTURE_3D.
         * \param pname Specifies the symbolic name of a texture parameter. Accepted values are
         * GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, and GL_TEXTURE_PRIORITY.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexParameteriv function returns the integer value or values of a texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and
         * GL_TEXTURE_3D.
         * \param pname Specifies the symbolic name of a texture parameter. Accepted values are
         * GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, and GL_TEXTURE_PRIORITY.
         * \param params Specifies a pointer to an array in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexParameteriv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glHint function specifies implementation-specific hints.
         *
         * \param target Specifies a symbolic constant indicating the behavior to be controlled. Accepted values are
         * GL_PERSPECTIVE_CORRECTION_HINT, GL_POINT_SMOOTH_HINT, GL_LINE_SMOOTH_HINT, GL_POLYGON_SMOOTH_HINT,
         * GL_FOG_HINT, and GL_GENERATE_MIPMAP_HINT.
         * \param mode Specifies a symbolic constant indicating the desired behavior. Accepted values are
         * GL_FASTEST, GL_NICEST, and GL_DONT_CARE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glHint(GLenum target, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glIndexd function sets the current color index.
         *
         * \param c Specifies the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexd(GLdouble c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexdv function sets the current color index.
         *
         * \param c Specifies a pointer to an array that contains the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexdv(const GLdouble* c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexf function sets the current color index.
         *
         * \param c Specifies the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexf(GLfloat c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexfv function sets the current color index.
         *
         * \param c Specifies a pointer to an array that contains the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexfv(const GLfloat* c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexi function sets the current color index.
         *
         * \param c Specifies the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexi(GLint c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexiv function sets the current color index.
         *
         * \param c Specifies a pointer to an array that contains the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexiv(const GLint* c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexMask function controls the writing of individual bits in the color index buffers.
         *
         * \param mask Specifies a bit mask to enable and disable the writing of individual bits in the color index
         * buffers. Initially, the mask is all 1's.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexMask(GLuint mask, const char* caller = nullptr) const;

        /**
         * \brief The glIndexs function sets the current color index.
         *
         * \param c Specifies the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexs(GLshort c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexsv function sets the current color index.
         *
         * \param c Specifies a pointer to an array that contains the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexsv(const GLshort* c, const char* caller = nullptr) const;

        /**
         * \brief The glInitNames function initializes the name stack to its default empty state.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInitNames(const char* caller = nullptr) const;

        /**
         * \brief The glIsEnabled function tests whether a capability is enabled.
         *
         * \param cap Specifies a symbolic constant indicating a GL capability. Accepted values include GL_BLEND,
         * GL_CULL_FACE, GL_DEPTH_TEST, GL_DITHER, GL_LIGHTING, GL_LINE_SMOOTH, GL_POLYGON_SMOOTH, GL_SCISSOR_TEST,
         * GL_STENCIL_TEST, and others.
         * \param caller Optional parameter to specify the caller function or context.
         * \return GL_TRUE if the specified capability is enabled, or GL_FALSE if it is not.
         */
        GLboolean glIsEnabled(GLenum cap, const char* caller = nullptr) const;

        /**
         * \brief The glIsList function determines if a name corresponds to a display list.
         *
         * \param list Specifies a potential display list name.
         * \param caller Optional parameter to specify the caller function or context.
         * \return GL_TRUE if list is the name of a display list, or GL_FALSE if it is not.
         */
        GLboolean glIsList(GLuint list, const char* caller = nullptr) const;

        /**
         * \brief The glLightf function sets the value of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a single-valued light source parameter for light. Accepted values are
         * GL_SPOT_EXPONENT, GL_SPOT_CUTOFF, GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, and
         * GL_QUADRATIC_ATTENUATION.
         * \param param Specifies the value that parameter pname of light will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightf(GLenum light, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glLightfv function sets the value of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a light source parameter for light. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_POSITION, GL_SPOT_DIRECTION, GL_SPOT_EXPONENT, GL_SPOT_CUTOFF, GL_CONSTANT_ATTENUATION,
         * GL_LINEAR_ATTENUATION, and GL_QUADRATIC_ATTENUATION.
         * \param params Specifies a pointer to an array that contains the values that parameter pname of light will
         * be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightfv(GLenum light, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glLighti function sets the value of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a single-valued light source parameter for light. Accepted values are
         * GL_SPOT_EXPONENT, GL_SPOT_CUTOFF, GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, and
         * GL_QUADRATIC_ATTENUATION.
         * \param param Specifies the value that parameter pname of light will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLighti(GLenum light, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glLightiv function sets the value of a light source parameter.
         *
         * \param light Specifies a light source. Accepted values are GL_LIGHTi, where i is a value between 0 and
         * GL_MAX_LIGHTS - 1.
         * \param pname Specifies a light source parameter for light. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_POSITION, GL_SPOT_DIRECTION, GL_SPOT_EXPONENT, GL_SPOT_CUTOFF, GL_CONSTANT_ATTENUATION,
         * GL_LINEAR_ATTENUATION, and GL_QUADRATIC_ATTENUATION.
         * \param params Specifies a pointer to an array that contains the values that parameter pname of light will
         * be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightiv(GLenum light, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glLightModelf function sets the value of a lighting model parameter.
         *
         * \param pname Specifies a single-valued lighting model parameter. Accepted values are
         * GL_LIGHT_MODEL_LOCAL_VIEWER, GL_LIGHT_MODEL_TWO_SIDE, and GL_LIGHT_MODEL_COLOR_CONTROL.
         * \param param Specifies the value that parameter pname will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightModelf(GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glLightModelfv function sets the value of a lighting model parameter.
         *
         * \param pname Specifies a lighting model parameter. Accepted values are GL_LIGHT_MODEL_AMBIENT,
         * GL_LIGHT_MODEL_LOCAL_VIEWER, GL_LIGHT_MODEL_TWO_SIDE, and GL_LIGHT_MODEL_COLOR_CONTROL.
         * \param params Specifies a pointer to an array that contains the values that parameter pname will be set
         * to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightModelfv(GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glLightModeli function sets the value of a lighting model parameter.
         *
         * \param pname Specifies a single-valued lighting model parameter. Accepted values are
         * GL_LIGHT_MODEL_LOCAL_VIEWER, GL_LIGHT_MODEL_TWO_SIDE, and GL_LIGHT_MODEL_COLOR_CONTROL.
         * \param param Specifies the value that parameter pname will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightModeli(GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glLightModeliv function sets the value of a lighting model parameter.
         *
         * \param pname Specifies a lighting model parameter. Accepted values are GL_LIGHT_MODEL_AMBIENT,
         * GL_LIGHT_MODEL_LOCAL_VIEWER, GL_LIGHT_MODEL_TWO_SIDE, and GL_LIGHT_MODEL_COLOR_CONTROL.
         * \param params Specifies a pointer to an array that contains the values that parameter pname will be set
         * to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLightModeliv(GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glLineStipple function specifies the line stipple pattern.
         *
         * \param factor Specifies a multiplier for each bit in the line stipple pattern. If factor is 3, for
         * example, each bit in the pattern is used three times before the next bit in the pattern is used. factor is
         * clamped to the range [1, 256] and defaults to 1.
         * \param pattern Specifies a 16-bit integer whose bit pattern determines which fragments of a line will be
         * drawn when the line is rasterized. Bit zero is used first; the default pattern is all 1's.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLineStipple(GLint factor, GLushort pattern, const char* caller = nullptr) const;

        /**
         * \brief The glLineWidth function specifies the width of rasterized lines.
         *
         * \param width Specifies the width of rasterized lines. The initial value is 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLineWidth(GLfloat width, const char* caller = nullptr) const;

        /**
         * \brief The glListBase function sets the display-list base for glCallLists.
         *
         * \param base Specifies an integer offset that will be added to glCallLists names.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glListBase(GLuint base, const char* caller = nullptr) const;

        /**
         * \brief The glLoadIdentity function replaces the current matrix with the identity matrix.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadIdentity(const char* caller = nullptr) const;

        /**
         * \brief The glLoadMatrixd function replaces the current matrix with the specified matrix.
         *
         * \param m Specifies a pointer to an array of 16 double-precision floating-point values that make up
         * the new matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadMatrixd(const GLdouble* m, const char* caller = nullptr) const;

        /**
         * \brief The glLoadMatrixf function replaces the current matrix with the specified matrix.
         *
         * \param m Specifies a pointer to an array of 16 single-precision floating-point values that make up
         * the new matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadMatrixf(const GLfloat* m, const char* caller = nullptr) const;

        /**
         * \brief The glLoadName function loads a name onto the name stack.
         *
         * \param name Specifies a name that will replace the top value on the name stack.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLoadName(GLuint name, const char* caller = nullptr) const;

        /**
         * \brief The glLogicOp function specifies a logical pixel operation for color index rendering.
         *
         * \param opcode Specifies a symbolic constant that selects a logical operation. Accepted values are
         * GL_CLEAR, GL_SET, GL_COPY, GL_COPY_INVERTED, GL_NOOP, GL_INVERT, GL_AND, GL_NAND, GL_OR, GL_NOR, GL_XOR,
         * GL_EQUIV, GL_AND_REVERSE, GL_AND_INVERTED, GL_OR_REVERSE, and GL_OR_INVERTED.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLogicOp(GLenum opcode, const char* caller = nullptr) const;

        /**
         * \brief The glMap1d function defines a one-dimensional evaluator.
         *
         * \param target Specifies the kind of values that are generated by the evaluator. Accepted values are
         * GL_MAP1_VERTEX_3, GL_MAP1_VERTEX_4, GL_MAP1_INDEX, GL_MAP1_COLOR_4, GL_MAP1_NORMAL, GL_MAP1_TEXTURE_COORD_1,
         * GL_MAP1_TEXTURE_COORD_2, GL_MAP1_TEXTURE_COORD_3, and GL_MAP1_TEXTURE_COORD_4.
         * \param u1 Specifies the linear mapping of u, as presented to glEvalCoord1, to the variable u1 in the
         * domain of the evaluator function.
         * \param u2 Specifies the linear mapping of u, as presented to glEvalCoord1, to the variable u2 in the
         * domain of the evaluator function.
         * \param stride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param order Specifies the number of control points. Must be positive.
         * \param points Specifies a pointer to the array of control points.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMap1d(
            GLenum target,
            GLdouble u1,
            GLdouble u2,
            GLint stride,
            GLint order,
            const GLdouble* points,
            const char* caller = nullptr) const;

        /**
         * \brief The glMap1f function defines a one-dimensional evaluator.
         *
         * \param target Specifies the kind of values that are generated by the evaluator. Accepted values are
         * GL_MAP1_VERTEX_3, GL_MAP1_VERTEX_4, GL_MAP1_INDEX, GL_MAP1_COLOR_4, GL_MAP1_NORMAL, GL_MAP1_TEXTURE_COORD_1,
         * GL_MAP1_TEXTURE_COORD_2, GL_MAP1_TEXTURE_COORD_3, and GL_MAP1_TEXTURE_COORD_4.
         * \param u1 Specifies the linear mapping of u, as presented to glEvalCoord1, to the variable u1 in the
         * domain of the evaluator function.
         * \param u2 Specifies the linear mapping of u, as presented to glEvalCoord1, to the variable u2 in the
         * domain of the evaluator function.
         * \param stride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param order Specifies the number of control points. Must be positive.
         * \param points Specifies a pointer to the array of control points.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMap1f(
            GLenum target,
            GLfloat u1,
            GLfloat u2,
            GLint stride,
            GLint order,
            const GLfloat* points,
            const char* caller = nullptr) const;

        /**
         * \brief The glMap2d function defines a two-dimensional evaluator.
         *
         * \param target Specifies the kind of values that are generated by the evaluator. Accepted values are
         * GL_MAP2_VERTEX_3, GL_MAP2_VERTEX_4, GL_MAP2_INDEX, GL_MAP2_COLOR_4, GL_MAP2_NORMAL, GL_MAP2_TEXTURE_COORD_1,
         * GL_MAP2_TEXTURE_COORD_2, GL_MAP2_TEXTURE_COORD_3, and GL_MAP2_TEXTURE_COORD_4.
         * \param u1 Specifies the linear mapping of u, as presented to glEvalCoord2, to the variable u1 in the
         * domain of the evaluator function.
         * \param u2 Specifies the linear mapping of u, as presented to glEvalCoord2, to the variable u2 in the
         * domain of the evaluator function.
         * \param ustride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param uorder Specifies the number of control points in the u dimension. Must be positive.
         * \param v1 Specifies the linear mapping of v, as presented to glEvalCoord2, to the variable v1 in the
         * domain of the evaluator function.
         * \param v2 Specifies the linear mapping of v, as presented to glEvalCoord2, to the variable v2 in the
         * domain of the evaluator function.
         * \param vstride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param vorder Specifies the number of control points in the v dimension. Must be positive.
         * \param points Specifies a pointer to the array of control points.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMap2d(
            GLenum target,
            GLdouble u1,
            GLdouble u2,
            GLint ustride,
            GLint uorder,
            GLdouble v1,
            GLdouble v2,
            GLint vstride,
            GLint vorder,
            const GLdouble* points,
            const char* caller = nullptr) const;

        /**
         * \brief The glMap2f function defines a two-dimensional evaluator.
         *
         * \param target Specifies the kind of values that are generated by the evaluator. Accepted values are
         * GL_MAP2_VERTEX_3, GL_MAP2_VERTEX_4, GL_MAP2_INDEX, GL_MAP2_COLOR_4, GL_MAP2_NORMAL, GL_MAP2_TEXTURE_COORD_1,
         * GL_MAP2_TEXTURE_COORD_2, GL_MAP2_TEXTURE_COORD_3, and GL_MAP2_TEXTURE_COORD_4.
         * \param u1 Specifies the linear mapping of u, as presented to glEvalCoord2, to the variable u1 in the
         * domain of the evaluator function.
         * \param u2 Specifies the linear mapping of u, as presented to glEvalCoord2, to the variable u2 in the
         * domain of the evaluator function.
         * \param ustride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param uorder Specifies the number of control points in the u dimension. Must be positive.
         * \param v1 Specifies the linear mapping of v, as presented to glEvalCoord2, to the variable v1 in the
         * domain of the evaluator function.
         * \param v2 Specifies the linear mapping of v, as presented to glEvalCoord2, to the variable v2 in the
         * domain of the evaluator function.
         * \param vstride Specifies the number of floats or doubles between the beginning of one control point and the
         * beginning of the next one in the data structure referenced in points.
         * \param vorder Specifies the number of control points in the v dimension. Must be positive.
         * \param points Specifies a pointer to the array of control points.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMap2f(
            GLenum target,
            GLfloat u1,
            GLfloat u2,
            GLint ustride,
            GLint uorder,
            GLfloat v1,
            GLfloat v2,
            GLint vstride,
            GLint vorder,
            const GLfloat* points,
            const char* caller = nullptr) const;

        /**
         * \brief The glMapGrid1d function defines a one-dimensional grid in the domain of the evaluator.
         *
         * \param un Specifies the number of partitions in the grid range.
         * \param u1 Specifies the linear mapping of grid domain variable u to the variable u1 in the domain of
         * the evaluator function.
         * \param u2 Specifies the linear mapping of grid domain variable u to the variable u2 in the domain of
         * the evaluator function.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMapGrid1d(GLint un, GLdouble u1, GLdouble u2, const char* caller = nullptr) const;

        /**
         * \brief The glMapGrid1f function defines a one-dimensional grid in the domain of the evaluator.
         *
         * \param un Specifies the number of partitions in the grid range.
         * \param u1 Specifies the linear mapping of grid domain variable u to the variable u1 in the domain of
         * the evaluator function.
         * \param u2 Specifies the linear mapping of grid domain variable u to the variable u2 in the domain of
         * the evaluator function.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMapGrid1f(GLint un, GLfloat u1, GLfloat u2, const char* caller = nullptr) const;

        /**
         * \brief The glMapGrid2d function defines a two-dimensional grid in the domain of the evaluator.
         *
         * \param un Specifies the number of partitions in the grid range in the u dimension.
         * \param u1 Specifies the linear mapping of grid domain variable u to the variable u1 in the domain of
         * the evaluator function.
         * \param u2 Specifies the linear mapping of grid domain variable u to the variable u2 in the domain of
         * the evaluator function.
         * \param vn Specifies the number of partitions in the grid range in the v dimension.
         * \param v1 Specifies the linear mapping of grid domain variable v to the variable v1 in the domain of
         * the evaluator function.
         * \param v2 Specifies the linear mapping of grid domain variable v to the variable v2 in the domain of
         * the evaluator function.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMapGrid2d(
            GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2, const char* caller = nullptr) const;

        /**
         * \brief The glMapGrid2f function defines a two-dimensional grid in the domain of the evaluator.
         *
         * \param un Specifies the number of partitions in the grid range in the u dimension.
         * \param u1 Specifies the linear mapping of grid domain variable u to the variable u1 in the domain of
         * the evaluator function.
         * \param u2 Specifies the linear mapping of grid domain variable u to the variable u2 in the domain of
         * the evaluator function.
         * \param vn Specifies the number of partitions in the grid range in the v dimension.
         * \param v1 Specifies the linear mapping of grid domain variable v to the variable v1 in the domain of
         * the evaluator function.
         * \param v2 Specifies the linear mapping of grid domain variable v to the variable v2 in the domain of
         * the evaluator function.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMapGrid2f(
            GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2, const char* caller = nullptr) const;

        /**
         * \brief The glMaterialf function specifies a single-valued material parameter for the face or faces
         * of a specified material.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be updated. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param param Specifies the value that parameter pname will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMaterialf(GLenum face, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glMaterialfv function specifies a material parameter for the face or faces of a
         * specified material.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be updated. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param params Specifies a pointer to an array that contains the values that parameter pname will be set
         * to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMaterialfv(GLenum face, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glMateriali function specifies a single-valued material parameter for the face or faces
         * of a specified material.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be updated. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param param Specifies the value that parameter pname will be set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMateriali(GLenum face, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glMaterialiv function specifies a material parameter for the face or faces of a
         * specified material.
         *
         * \param face Specifies which face or faces are being updated. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param pname Specifies the material parameter to be updated. Accepted values are GL_AMBIENT, GL_DIFFUSE,
         * GL_SPECULAR, GL_EMISSION, GL_SHININESS, GL_AMBIENT_AND_DIFFUSE, and GL_COLOR_INDEXES.
         * \param params Specifies a pointer to an array that contains the values that parameter pname will be set
         * to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMaterialiv(GLenum face, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glMatrixMode function specifies which matrix is the current matrix.
         *
         * \param mode Specifies which matrix stack is the target for subsequent matrix operations. Accepted values
         * are GL_MODELVIEW, GL_PROJECTION, and GL_TEXTURE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMatrixMode(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glMultMatrixd function multiplies the current matrix with the specified matrix.
         *
         * \param m Specifies a pointer to an array of 16 double-precision floating-point values that make up
         * the matrix to be multiplied with the current matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultMatrixd(const GLdouble* m, const char* caller = nullptr) const;

        /**
         * \brief The glMultMatrixf function multiplies the current matrix with the specified matrix.
         *
         * \param m Specifies a pointer to an array of 16 single-precision floating-point values that make up
         * the matrix to be multiplied with the current matrix.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultMatrixf(const GLfloat* m, const char* caller = nullptr) const;

        /**
         * \brief The glNewList function creates or replaces a display list.
         *
         * \param list Specifies the display list name.
         * \param mode Specifies the compilation mode, which can be GL_COMPILE or GL_COMPILE_AND_EXECUTE.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNewList(GLuint list, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3b function sets the current normal vector.
         *
         * \param nx Specifies the x-coordinate of the new current normal vector.
         * \param ny Specifies the y-coordinate of the new current normal vector.
         * \param nz Specifies the z-coordinate of the new current normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3bv function sets the current normal vector.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the new current
         * normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3bv(const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3d function sets the current normal vector.
         *
         * \param nx Specifies the x-coordinate of the new current normal vector.
         * \param ny Specifies the y-coordinate of the new current normal vector.
         * \param nz Specifies the z-coordinate of the new current normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3dv function sets the current normal vector.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the new current
         * normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3f function sets the current normal vector.
         *
         * \param nx Specifies the x-coordinate of the new current normal vector.
         * \param ny Specifies the y-coordinate of the new current normal vector.
         * \param nz Specifies the z-coordinate of the new current normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3fv function sets the current normal vector.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the new current
         * normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3i function sets the current normal vector.
         *
         * \param nx Specifies the x-coordinate of the new current normal vector.
         * \param ny Specifies the y-coordinate of the new current normal vector.
         * \param nz Specifies the z-coordinate of the new current normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3i(GLint nx, GLint ny, GLint nz, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3iv function sets the current normal vector.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the new current
         * normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3s function sets the current normal vector.
         *
         * \param nx Specifies the x-coordinate of the new current normal vector.
         * \param ny Specifies the y-coordinate of the new current normal vector.
         * \param nz Specifies the z-coordinate of the new current normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3s(GLshort nx, GLshort ny, GLshort nz, const char* caller = nullptr) const;

        /**
         * \brief The glNormal3sv function sets the current normal vector.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the new current
         * normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormal3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glOrtho function multiplies the current matrix by an orthographic matrix.
         *
         * \param left Specifies the coordinate for the left vertical clipping plane.
         * \param right Specifies the coordinate for the right vertical clipping plane.
         * \param bottom Specifies the coordinate for the bottom horizontal clipping plane.
         * \param top Specifies the coordinate for the top horizontal clipping plane.
         * \param zNear Specifies the distance to the near depth clipping plane. Must be positive.
         * \param zFar Specifies the distance to the far depth clipping plane. Must be positive.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glOrtho(
            GLdouble left,
            GLdouble right,
            GLdouble bottom,
            GLdouble top,
            GLdouble zNear,
            GLdouble zFar,
            const char* caller = nullptr) const;

        /**
         * \brief The glPassThrough function inserts a marker in the feedback buffer.
         *
         * \param token Specifies a marker value to be placed in the feedback buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPassThrough(GLfloat token, const char* caller = nullptr) const;

        /**
         * \brief The glPixelMapfv function maps the values in a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param mapsize Specifies the size of the pixel map.
         * \param values Specifies a pointer to an array of mapsize values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelMapfv(GLenum map, GLint mapsize, const GLfloat* values, const char* caller = nullptr) const;

        /**
         * \brief The glPixelMapuiv function maps the values in a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param mapsize Specifies the size of the pixel map.
         * \param values Specifies a pointer to an array of mapsize values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelMapuiv(GLenum map, GLint mapsize, const GLuint* values, const char* caller = nullptr) const;

        /**
         * \brief The glPixelMapusv function maps the values in a pixel map.
         *
         * \param map Specifies the pixel map. Accepted values are GL_PIXEL_MAP_I_TO_I, GL_PIXEL_MAP_S_TO_S,
         * GL_PIXEL_MAP_I_TO_R, GL_PIXEL_MAP_I_TO_G, GL_PIXEL_MAP_I_TO_B, GL_PIXEL_MAP_I_TO_A, GL_PIXEL_MAP_R_TO_R,
         * GL_PIXEL_MAP_G_TO_G, GL_PIXEL_MAP_B_TO_B, and GL_PIXEL_MAP_A_TO_A.
         * \param mapsize Specifies the size of the pixel map.
         * \param values Specifies a pointer to an array of mapsize values.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelMapusv(GLenum map, GLint mapsize, const GLushort* values, const char* caller = nullptr) const;

        /**
         * \brief The glPixelStoref function sets pixel storage modes.
         *
         * \param pname Specifies the symbolic name of the parameter to be set. Accepted values are
         * GL_PACK_SWAP_BYTES, GL_PACK_LSB_FIRST, GL_PACK_ROW_LENGTH, GL_PACK_SKIP_ROWS, GL_PACK_SKIP_PIXELS,
         * GL_PACK_ALIGNMENT, GL_UNPACK_SWAP_BYTES, GL_UNPACK_LSB_FIRST, GL_UNPACK_ROW_LENGTH, GL_UNPACK_SKIP_ROWS,
         * GL_UNPACK_SKIP_PIXELS, and GL_UNPACK_ALIGNMENT.
         * \param param Specifies the value that pname is set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelStoref(GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glPixelStorei function sets pixel storage modes.
         *
         * \param pname Specifies the symbolic name of the parameter to be set. Accepted values are
         * GL_PACK_SWAP_BYTES, GL_PACK_LSB_FIRST, GL_PACK_ROW_LENGTH, GL_PACK_SKIP_ROWS, GL_PACK_SKIP_PIXELS,
         * GL_PACK_ALIGNMENT, GL_UNPACK_SWAP_BYTES, GL_UNPACK_LSB_FIRST, GL_UNPACK_ROW_LENGTH, GL_UNPACK_SKIP_ROWS,
         * GL_UNPACK_SKIP_PIXELS, and GL_UNPACK_ALIGNMENT.
         * \param param Specifies the value that pname is set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelStorei(GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glPixelTransferf function sets pixel transfer modes.
         *
         * \param pname Specifies the symbolic name of the pixel transfer parameter to be set. Accepted values are
         * GL_MAP_COLOR, GL_MAP_STENCIL, GL_INDEX_SHIFT, GL_INDEX_OFFSET, GL_RED_SCALE, GL_RED_BIAS, GL_GREEN_SCALE,
         * GL_GREEN_BIAS, GL_BLUE_SCALE, GL_BLUE_BIAS, GL_ALPHA_SCALE, GL_ALPHA_BIAS, GL_DEPTH_SCALE, GL_DEPTH_BIAS,
         * GL_POST_COLOR_MATRIX_RED_SCALE, GL_POST_COLOR_MATRIX_GREEN_SCALE, GL_POST_COLOR_MATRIX_BLUE_SCALE,
         * GL_POST_COLOR_MATRIX_ALPHA_SCALE, GL_POST_COLOR_MATRIX_RED_BIAS, GL_POST_COLOR_MATRIX_GREEN_BIAS,
         * GL_POST_COLOR_MATRIX_BLUE_BIAS, GL_POST_COLOR_MATRIX_ALPHA_BIAS, GL_POST_CONVOLUTION_RED_SCALE,
         * GL_POST_CONVOLUTION_GREEN_SCALE, GL_POST_CONVOLUTION_BLUE_SCALE, GL_POST_CONVOLUTION_ALPHA_SCALE,
         * GL_POST_CONVOLUTION_RED_BIAS, GL_POST_CONVOLUTION_GREEN_BIAS, GL_POST_CONVOLUTION_BLUE_BIAS, and
         * GL_POST_CONVOLUTION_ALPHA_BIAS.
         * \param param Specifies the value that pname is set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelTransferf(GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glPixelTransferi function sets pixel transfer modes.
         *
         * \param pname Specifies the symbolic name of the pixel transfer parameter to be set. Accepted values are
         * GL_MAP_COLOR, GL_MAP_STENCIL, GL_INDEX_SHIFT, GL_INDEX_OFFSET, GL_RED_SCALE, GL_RED_BIAS, GL_GREEN_SCALE,
         * GL_GREEN_BIAS, GL_BLUE_SCALE, GL_BLUE_BIAS, GL_ALPHA_SCALE, GL_ALPHA_BIAS, GL_DEPTH_SCALE, GL_DEPTH_BIAS,
         * GL_POST_COLOR_MATRIX_RED_SCALE, GL_POST_COLOR_MATRIX_GREEN_SCALE, GL_POST_COLOR_MATRIX_BLUE_SCALE,
         * GL_POST_COLOR_MATRIX_ALPHA_SCALE, GL_POST_COLOR_MATRIX_RED_BIAS, GL_POST_COLOR_MATRIX_GREEN_BIAS,
         * GL_POST_COLOR_MATRIX_BLUE_BIAS, GL_POST_COLOR_MATRIX_ALPHA_BIAS, GL_POST_CONVOLUTION_RED_SCALE,
         * GL_POST_CONVOLUTION_GREEN_SCALE, GL_POST_CONVOLUTION_BLUE_SCALE, GL_POST_CONVOLUTION_ALPHA_SCALE,
         * GL_POST_CONVOLUTION_RED_BIAS, GL_POST_CONVOLUTION_GREEN_BIAS, GL_POST_CONVOLUTION_BLUE_BIAS, and
         * GL_POST_CONVOLUTION_ALPHA_BIAS.
         * \param param Specifies the value that pname is set to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelTransferi(GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glPixelZoom function specifies the pixel zoom factors.
         *
         * \param xfactor Specifies the x zoom factor.
         * \param yfactor Specifies the y zoom factor.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPixelZoom(GLfloat xfactor, GLfloat yfactor, const char* caller = nullptr) const;

        /**
         * \brief The glPointSize function specifies the diameter of rasterized points.
         *
         * \param size Specifies the diameter of rasterized points. The initial value is 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPointSize(GLfloat size, const char* caller = nullptr) const;

        /**
         * \brief The glPolygonMode function sets the polygon rasterization mode.
         *
         * \param face Specifies the polygons that mode applies to. Accepted values are GL_FRONT, GL_BACK, and
         * GL_FRONT_AND_BACK.
         * \param mode Specifies how polygons will be rasterized. Accepted values are GL_POINT, GL_LINE, and
         * GL_FILL. The initial value is GL_FILL for both front- and back-facing polygons.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPolygonMode(GLenum face, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glPolygonStipple function sets the polygon stipple pattern.
         *
         * \param mask Specifies a pointer to a 32x32 stipple pattern that will be unpacked from memory in the same
         * way that glDrawPixels unpacks pixels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPolygonStipple(const GLubyte* mask, const char* caller = nullptr) const;

        /**
         * \brief The glPopAttrib function pops the current attribute stack.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPopAttrib(const char* caller = nullptr) const;

        /**
         * \brief The glPopMatrix function pops the current matrix stack.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPopMatrix(const char* caller = nullptr) const;

        /**
         * \brief The glPopName function pops the current name stack.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPopName(const char* caller = nullptr) const;

        /**
         * \brief The glPushAttrib function pushes the current attribute stack.
         *
         * \param mask Specifies a mask that indicates which attributes to save. The initial value is
         * GL_CURRENT_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPushAttrib(GLbitfield mask, const char* caller = nullptr) const;

        /**
         * \brief The glPushMatrix function pushes the current matrix stack.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPushMatrix(const char* caller = nullptr) const;

        /**
         * \brief The glPushName function pushes the current name stack.
         *
         * \param name Specifies a name that will be pushed onto the name stack.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPushName(GLuint name, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2d function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2d(GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2dv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2f function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2f(GLfloat x, GLfloat y, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2fv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2i function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2i(GLint x, GLint y, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2iv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2s function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2s(GLshort x, GLshort y, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos2sv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos2sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3d function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3d(GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3dv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3f function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3f(GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3fv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3i function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3i(GLint x, GLint y, GLint z, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3iv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3s function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3s(GLshort x, GLshort y, GLshort z, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos3sv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4d function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param w Specifies the w-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4dv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4f function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param w Specifies the w-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4fv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4i function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param w Specifies the w-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4i(GLint x, GLint y, GLint z, GLint w, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4iv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4s function sets the raster position.
         *
         * \param x Specifies the x-coordinate of the raster position.
         * \param y Specifies the y-coordinate of the raster position.
         * \param z Specifies the z-coordinate of the raster position.
         * \param w Specifies the w-coordinate of the raster position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w, const char* caller = nullptr) const;

        /**
         * \brief The glRasterPos4sv function sets the raster position.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the raster
         * position.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRasterPos4sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glReadBuffer function specifies a color buffer as the source for subsequent read
         * operations.
         *
         * \param src Specifies a color buffer. Accepted values are GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT,
         * GL_BACK_RIGHT, GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, and GL_AUXi, where i is between 0 and GL_AUX_BUFFERS
         * - 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glReadBuffer(GLenum src, const char* caller = nullptr) const;

        /**
         * \brief The glReadPixels function reads a block of pixels from the frame buffer.
         *
         * \param x Specifies the window x coordinate of the first pixel that is read from the frame buffer.
         * \param y Specifies the window y coordinate of the first pixel that is read from the frame buffer.
         * \param width Specifies the width of the pixel rectangle.
         * \param height Specifies the height of the pixel rectangle.
         * \param format Specifies the format of the pixel data. Accepted values are GL_COLOR_INDEX,
         * GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and
         * GL_LUMINANCE_ALPHA.
         * \param type Specifies the data type of the pixel data. Accepted values are GL_UNSIGNED_BYTE, GL_BYTE,
         * GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, and GL_FLOAT.
         * \param pixels Specifies a pointer to a buffer in which the returned data will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glReadPixels(
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            GLenum format,
            GLenum type,
            void* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glRectd function draws a rectangle.
         *
         * \param x1 Specifies the x coordinate of one vertex.
         * \param y1 Specifies the y coordinate of one vertex.
         * \param x2 Specifies the x coordinate of the opposite vertex.
         * \param y2 Specifies the y coordinate of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, const char* caller = nullptr) const;

        /**
         * \brief The glRectdv function draws a rectangle.
         *
         * \param v1 Specifies a pointer to an array containing the x and y coordinates of one vertex.
         * \param v2 Specifies a pointer to an array containing the x and y coordinates of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectdv(const GLdouble* v1, const GLdouble* v2, const char* caller = nullptr) const;

        /**
         * \brief The glRectf function draws a rectangle.
         *
         * \param x1 Specifies the x coordinate of one vertex.
         * \param y1 Specifies the y coordinate of one vertex.
         * \param x2 Specifies the x coordinate of the opposite vertex.
         * \param y2 Specifies the y coordinate of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, const char* caller = nullptr) const;

        /**
         * \brief The glRectfv function draws a rectangle.
         *
         * \param v1 Specifies a pointer to an array containing the x and y coordinates of one vertex.
         * \param v2 Specifies a pointer to an array containing the x and y coordinates of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectfv(const GLfloat* v1, const GLfloat* v2, const char* caller = nullptr) const;

        /**
         * \brief The glRecti function draws a rectangle.
         *
         * \param x1 Specifies the x coordinate of one vertex.
         * \param y1 Specifies the y coordinate of one vertex.
         * \param x2 Specifies the x coordinate of the opposite vertex.
         * \param y2 Specifies the y coordinate of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRecti(GLint x1, GLint y1, GLint x2, GLint y2, const char* caller = nullptr) const;

        /**
         * \brief The glRectiv function draws a rectangle.
         *
         * \param v1 Specifies a pointer to an array containing the x and y coordinates of one vertex.
         * \param v2 Specifies a pointer to an array containing the x and y coordinates of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectiv(const GLint* v1, const GLint* v2, const char* caller = nullptr) const;

        /**
         * \brief The glRects function draws a rectangle.
         *
         * \param x1 Specifies the x coordinate of one vertex.
         * \param y1 Specifies the y coordinate of one vertex.
         * \param x2 Specifies the x coordinate of the opposite vertex.
         * \param y2 Specifies the y coordinate of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2, const char* caller = nullptr) const;

        /**
         * \brief The glRectsv function draws a rectangle.
         *
         * \param v1 Specifies a pointer to an array containing the x and y coordinates of one vertex.
         * \param v2 Specifies a pointer to an array containing the x and y coordinates of the opposite vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRectsv(const GLshort* v1, const GLshort* v2, const char* caller = nullptr) const;

        /**
         * \brief The glRenderMode function sets the rasterization mode.
         *
         * \param mode Specifies the rasterization mode. Accepted values are GL_RENDER, GL_SELECT, and GL_FEEDBACK.
         * \param caller Optional parameter to specify the caller function or context.
         * \return The function returns different values depending on the mode. In GL_RENDER mode, it returns
         * 0. In GL_SELECT mode, it returns the number of hit records. In GL_FEEDBACK mode, it returns the number of
         * values placed in the feedback buffer.
         */
        GLint glRenderMode(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glRotated function multiplies the current matrix by a rotation matrix.
         *
         * \param angle Specifies the angle of rotation, in degrees.
         * \param x Specifies the x coordinate of a vector.
         * \param y Specifies the y coordinate of a vector.
         * \param z Specifies the z coordinate of a vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glRotatef function multiplies the current matrix by a rotation matrix.
         *
         * \param angle Specifies the angle of rotation, in degrees.
         * \param x Specifies the x coordinate of a vector.
         * \param y Specifies the y coordinate of a vector.
         * \param z Specifies the z coordinate of a vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glScaled function multiplies the current matrix by a general scaling matrix.
         *
         * \param x Specifies the x coordinate of a scaling vector.
         * \param y Specifies the y coordinate of a scaling vector.
         * \param z Specifies the z coordinate of a scaling vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScaled(GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glScalef function multiplies the current matrix by a general scaling matrix.
         *
         * \param x Specifies the x coordinate of a scaling vector.
         * \param y Specifies the y coordinate of a scaling vector.
         * \param z Specifies the z coordinate of a scaling vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScalef(GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glScissor function defines a scissor box.
         *
         * \param x Specifies the x coordinate for the lower left corner of the scissor box.
         * \param y Specifies the y coordinate for the lower left corner of the scissor box.
         * \param width Specifies the width of the scissor box.
         * \param height Specifies the height of the scissor box.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScissor(GLint x, GLint y, GLsizei width, GLsizei height, const char* caller = nullptr) const;

        /**
         * \brief The glSelectBuffer function establishes a buffer for selection mode values.
         *
         * \param size Specifies the size of the buffer.
         * \param buffer Specifies a pointer to an array of unsigned integers to be used as the selection buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSelectBuffer(GLsizei size, GLuint* buffer, const char* caller = nullptr) const;

        /**
         * \brief The glShadeModel function selects flat or smooth shading.
         *
         * \param mode Specifies a symbolic value representing a shading technique. Accepted values are GL_FLAT and
         * GL_SMOOTH.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glShadeModel(GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glStencilFunc function sets the stencil test function.
         *
         * \param func Specifies the test function. Accepted values are GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER,
         * GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, and GL_ALWAYS.
         * \param ref Specifies the reference value for the stencil test. ref is clamped to the range [0, 2^n -
         * 1], where n is the number of bitplanes in the stencil buffer.
         * \param mask Specifies a mask that is ANDed with both the reference value and the stored stencil value
         * when the test is done. The initial value is all 1's.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilFunc(GLenum func, GLint ref, GLuint mask, const char* caller = nullptr) const;

        /**
         * \brief The glStencilMask function controls the writing of individual bits in the stencil planes.
         *
         * \param mask Specifies a bit mask to enable and disable writing of individual bits in the stencil planes.
         * Initially, the mask is all 1's.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilMask(GLuint mask, const char* caller = nullptr) const;

        /**
         * \brief The glStencilOp function sets the stencil test actions.
         *
         * \param fail Specifies the action to take when the stencil test fails. Accepted values are GL_KEEP,
         * GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, and GL_INVERT.
         * \param zfail Specifies the stencil action when the stencil test passes, but the depth test fails.
         * Accepted values are the same as for fail.
         * \param zpass Specifies the stencil action when both the stencil test and the depth test pass, or when the
         * stencil test passes and either there is no depth buffer or depth testing is not enabled. Accepted values are
         * the same as for fail.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilOp(GLenum fail, GLenum zfail, GLenum zpass, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1d function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1d(GLdouble s, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1dv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s coordinate of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1f function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1f(GLfloat s, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1fv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s coordinate of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1i function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1i(GLint s, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1iv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s coordinate of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1s function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1s(GLshort s, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord1sv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s coordinate of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord1sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2d function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2d(GLdouble s, GLdouble t, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2dv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s and t coordinates of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2f function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2f(GLfloat s, GLfloat t, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2fv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s and t coordinates of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2i function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2i(GLint s, GLint t, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2iv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s and t coordinates of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2s function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2s(GLshort s, GLshort t, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord2sv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s and t coordinates of the current texture
         * coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord2sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3d function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3d(GLdouble s, GLdouble t, GLdouble r, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3dv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, and r coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3f function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3f(GLfloat s, GLfloat t, GLfloat r, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3fv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, and r coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3i function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3i(GLint s, GLint t, GLint r, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3iv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, and r coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3s function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3s(GLshort s, GLshort t, GLshort r, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord3sv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, and r coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4d function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param q Specifies the q coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4dv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, r, and q coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4f function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param q Specifies the q coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4fv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, r, and q coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4i function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param q Specifies the q coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4i(GLint s, GLint t, GLint r, GLint q, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4iv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, r, and q coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4s function sets the current texture coordinates.
         *
         * \param s Specifies the s coordinate of the current texture coordinates.
         * \param t Specifies the t coordinate of the current texture coordinates.
         * \param r Specifies the r coordinate of the current texture coordinates.
         * \param q Specifies the q coordinate of the current texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoord4sv function sets the current texture coordinates.
         *
         * \param v Specifies a pointer to an array that contains the s, t, r, and q coordinates of the current
         * texture coordinates.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoord4sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvf function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvf(GLenum target, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvfv function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvfv(GLenum target, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvi function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvi(GLenum target, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnviv function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment. Accepted values are GL_TEXTURE_ENV and
         * GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter. Accepted values are
         * GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnviv(GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGend function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGend(GLenum coord, GLenum pname, GLdouble param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGendv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGendv(GLenum coord, GLenum pname, const GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGenf function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGenf(GLenum coord, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGenfv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGeni function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGeni(GLenum coord, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGeniv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate. Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter. Accepted values
         * are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGeniv(GLenum coord, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief  The glTexImage1D function specifies a one-dimensional texture image.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D and
         * GL_PROXY_TEXTURE_1D.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the number of color components in the texture.
         * \param width  Specifies the width of the texture image. Must be 0 or 2^n + 2*border for some
         * integer n.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param format Specifies the format of the pixel data. Accepted values are GL_RED, GL_RG, GL_RGB,
         * GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER,
         * GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX.
         * \param type  Specifies the data type of the pixel data. Accepted values are GL_UNSIGNED_BYTE,
         * GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT,
         * GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_24_8,
         * GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV, GL_FLOAT_32_UNSIGNED_INT_24_8_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexImage1D(
            GLenum target,
            GLint level,
            GLint internalformat,
            GLsizei width,
            GLint border,
            GLenum format,
            GLenum type,
            const void* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief  The glTexImage2D function specifies a two-dimensional texture image.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_2D,
         * GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE,
         * GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_PROXY_TEXTURE_CUBE_MAP.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the number of color components in the texture.
         * \param width  Specifies the width of the texture image. Must be 0 or 2^n + 2*border for some
         * integer n.
         * \param height Specifies the height of the texture image. Must be 0 or 2^m + 2*border for some
         * integer m.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param format Specifies the format of the pixel data. Accepted values are GL_RED, GL_RG, GL_RGB,
         * GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER,
         * GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX.
         * \param type  Specifies the data type of the pixel data. Accepted values are GL_UNSIGNED_BYTE,
         * GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT,
         * GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         * GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         * GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         * GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_24_8,
         * GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV, GL_FLOAT_32_UNSIGNED_INT_24_8_REV.
         * \param pixels Specifies a pointer to the image data in memory.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexImage2D(
            GLenum target,
            GLint level,
            GLint internalformat,
            GLsizei width,
            GLsizei height,
            GLint border,
            GLenum format,
            GLenum type,
            const void* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexParameterf function sets the texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D,
         * GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_RECTANGLE, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, and GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a single-valued texture parameter. Accepted values are
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_PRIORITY, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL,
         * GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_TEXTURE_MODE,
         * GL_GENERATE_MIPMAP, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexParameterf(GLenum target, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTexParameterfv function sets the texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D,
         * GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_RECTANGLE, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, and GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a single-valued texture parameter. Accepted values are
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_PRIORITY, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL,
         * GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_TEXTURE_MODE,
         * GL_GENERATE_MIPMAP, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexParameteri function sets the texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D,
         * GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_RECTANGLE, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, and GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a single-valued texture parameter. Accepted values are
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_PRIORITY, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL,
         * GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_TEXTURE_MODE,
         * GL_GENERATE_MIPMAP, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexParameteri(GLenum target, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTexParameteriv function sets the texture parameter.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D,
         * GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_RECTANGLE, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, and GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a single-valued texture parameter. Accepted values are
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_PRIORITY, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL,
         * GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_DEPTH_TEXTURE_MODE,
         * GL_GENERATE_MIPMAP, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B,
         * GL_TEXTURE_SWIZZLE_A, GL_TEXTURE_SWIZZLE_RGBA.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexParameteriv(GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTranslated function multiplies the current matrix by a translation matrix.
         *
         * \param x Specifies the x coordinate of a translation vector.
         * \param y Specifies the y coordinate of a translation vector.
         * \param z Specifies the z coordinate of a translation vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTranslated(GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glTranslatef function multiplies the current matrix by a translation matrix.
         *
         * \param x Specifies the x coordinate of a translation vector.
         * \param y Specifies the y coordinate of a translation vector.
         * \param z Specifies the z coordinate of a translation vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTranslatef(GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2d function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2d(GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2dv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2f function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2f(GLfloat x, GLfloat y, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2fv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2i function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2i(GLint x, GLint y, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2iv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2s function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2s(GLshort x, GLshort y, const char* caller = nullptr) const;

        /**
         * \brief The glVertex2sv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x and y coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex2sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3d function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3d(GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3dv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3f function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3f(GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3fv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3i function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3i(GLint x, GLint y, GLint z, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3iv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3s function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3s(GLshort x, GLshort y, GLshort z, const char* caller = nullptr) const;

        /**
         * \brief The glVertex3sv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, and z coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex3sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4d function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param w Specifies the w coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4dv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4dv(const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4f function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param w Specifies the w coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4fv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4fv(const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4i function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param w Specifies the w coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4i(GLint x, GLint y, GLint z, GLint w, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4iv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4iv(const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4s function specifies a vertex.
         *
         * \param x Specifies the x coordinate of the vertex.
         * \param y Specifies the y coordinate of the vertex.
         * \param z Specifies the z coordinate of the vertex.
         * \param w Specifies the w coordinate of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w, const char* caller = nullptr) const;

        /**
         * \brief The glVertex4sv function specifies a vertex.
         *
         * \param v Specifies a pointer to an array that contains the x, y, z, and w coordinates of the vertex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertex4sv(const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glViewport function sets the viewport.
         *
         * \param x Specifies the x coordinate of the lower left corner of the viewport rectangle, in pixels.
         * The initial value is 0.
         * \param y Specifies the y coordinate of the lower left corner of the viewport rectangle, in pixels.
         * The initial value is 0.
         * \param width Specifies the width of the viewport. When a GL context is first attached to a window, width
         * and height are set to the dimensions of that window.
         * \param height Specifies the height of the viewport. When a GL context is first attached to a window, width
         * and height are set to the dimensions of that window.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glViewport(GLint x, GLint y, GLsizei width, GLsizei height, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
