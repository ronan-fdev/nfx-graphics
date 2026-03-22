#pragma once

/**
 * \file Functions_1_1.h
 * \brief Declares the OpenGL 1.1 function wrapper interface.
 */

#include "Functions_1_0.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_1
     * \brief Exposes the OpenGL 1.1 function set.
     */
    class Functions_1_1 : public Functions_1_0
    {
    public:
        explicit Functions_1_1();
        Functions_1_1(const Functions_1_1&) = delete;
        Functions_1_1& operator=(const Functions_1_1&) = delete;
        Functions_1_1(Functions_1_1&&) = delete;
        Functions_1_1& operator=(Functions_1_1&&) = delete;
        virtual ~Functions_1_1();

        /**
         * \brief The glAreTexturesResident function determines if textures are loaded in texture memory.
         *
         * \param n  Specifies the number of textures to be queried.
         * \param textures Specifies an array containing the names of the textures to be queried.
         * \param residences Specifies an array in which the texture residence status is returned.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if all textures are resident, GL_FALSE otherwise.
         */
        GLboolean glAreTexturesResident(
            GLsizei n, const GLuint* textures, GLboolean* residences, const char* caller = nullptr) const;

        /**
         * \brief The glArrayElement function specifies an array element.
         * \deprecated Deprecated in OpenGL 3.0. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param index Specifies the index of the array element to be specified.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glArrayElement(GLint index, const char* caller = nullptr) const;

        /**
         * \brief The glBindTexture function binds a named texture to a texturing target.
         *
         * \param target Specifies the target to which the texture is bound.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, and GL_TEXTURE_3D.
         * \param texture Specifies the name of a texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindTexture(GLenum target, GLuint texture, const char* caller = nullptr) const;

        /**
         * \brief The glColorPointer function defines an array of colors.
         *
         * \param size Specifies the number of components per color. Must be 3 or 4.
         * \param type Specifies the data type of each color component.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT, GL_FLOAT, and GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive colors. If stride is 0, the colors are
         * understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first component of the first color element in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorPointer(
            GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvf function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment.
         * Accepted values are GL_TEXTURE_ENV and GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter.
         * Accepted values are GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and
         * GL_COMBINE_RGB.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvf(GLenum target, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvfv function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment.
         * Accepted values are GL_TEXTURE_ENV and GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter.
         * Accepted values are GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and
         * GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvfv(GLenum target, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnvi function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment.
         * Accepted values are GL_TEXTURE_ENV and GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter.
         * Accepted values are GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and
         * GL_COMBINE_RGB.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnvi(GLenum target, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTexEnviv function sets the texture environment parameters.
         *
         * \param target Specifies a texture environment.
         * Accepted values are GL_TEXTURE_ENV and GL_TEXTURE_FILTER_CONTROL.
         * \param pname Specifies the symbolic name of a texture environment parameter.
         * Accepted values are GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR, GL_TEXTURE_LOD_BIAS, and
         * GL_COMBINE_RGB.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexEnviv(GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGend function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGend(GLenum coord, GLenum pname, GLdouble param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGendv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGendv(GLenum coord, GLenum pname, const GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGenf function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGenf(GLenum coord, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGenfv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexGeni function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param param Specifies the value of pname.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGeni(GLenum coord, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glTexGeniv function sets the texture coordinate generation parameters.
         *
         * \param coord Specifies a texture coordinate.
         * Accepted values are GL_S, GL_T, GL_R, and GL_Q.
         * \param pname Specifies the symbolic name of a texture coordinate generation parameter.
         * Accepted values are GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, and GL_EYE_PLANE.
         * \param params Specifies a pointer to an array where the value or values of pname are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexGeniv(GLenum coord, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glCopyTexImage1D function copies pixels into a one-dimensional texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_1D and GL_PROXY_TEXTURE_1D.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the internal format of the texture.
         * \param x  Specifies the window x coordinate of the left corner of the row of pixels to be
         * copied.
         * \param y  Specifies the window y coordinate of the left corner of the row of pixels to be
         * copied.
         * \param width  Specifies the width of the texture image.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTexImage1D(
            GLenum target,
            GLint level,
            GLenum internalformat,
            GLint x,
            GLint y,
            GLsizei width,
            GLint border,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyTexImage2D function copies pixels into a two-dimensional texture image.
         *
         * \param target Specifies the target texture.
         *  Accepted values are GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY,
         * GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_PROXY_TEXTURE_CUBE_MAP.
         * \param level  Specifies the level-of-detail number. Level 0 is the base image level. Level n is
         * the nth mipmap reduction image.
         * \param internalformat Specifies the internal format of the texture.
         * \param x  Specifies the window x coordinate of the left corner of the row of pixels to be
         * copied.
         * \param y  Specifies the window y coordinate of the left corner of the row of pixels to be
         * copied.
         * \param width  Specifies the width of the texture image.
         * \param height Specifies the height of the texture image.
         * \param border Specifies the width of the border. Must be either 0 or 1.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTexImage2D(
            GLenum target,
            GLint level,
            GLenum internalformat,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            GLint border,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyTexSubImage1D function copies a subimage of a one-dimensional texture.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param x Specifies the window x coordinate of the left corner of the row of pixels to be copied.
         * \param y Specifies the window y coordinate of the left corner of the row of pixels to be copied.
         * \param width Specifies the width of the texture subimage.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTexSubImage1D(
            GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char* caller = nullptr)
            const;

        /**
         * \brief The glCopyTexSubImage2D function copies a subimage of a two-dimensional texture.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D,
         * GL_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_PROXY_TEXTURE_CUBE_MAP.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param yoffset Specifies a texel offset in the y direction within the texture array.
         * \param x Specifies the window x coordinate of the left corner of the row of pixels to be copied.
         * \param y Specifies the window y coordinate of the left corner of the row of pixels to be copied.
         * \param width Specifies the width of the texture subimage.
         * \param height Specifies the height of the texture subimage.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyTexSubImage2D(
            GLenum target,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glDeleteTextures function deletes named textures.
         *
         * \param n Specifies the number of textures to be deleted.
         * \param textures Specifies an array containing the names of the textures to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteTextures(GLsizei n, const GLuint* textures, const char* caller = nullptr) const;

        /**
         * \brief The glDisableClientState function disables a client-side capability.
         *
         * \param array Specifies the capability to disable.
         * Accepted values are GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, GL_INDEX_ARRAY,
         * GL_TEXTURE_COORD_ARRAY, GL_EDGE_FLAG_ARRAY, and GL_FOG_COORD_ARRAY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDisableClientState(GLenum array, const char* caller = nullptr) const;

        /**
         * \brief The glDrawArrays function renders primitives from array data.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP,
         * GL_TRIANGLE_FAN, and GL_TRIANGLES.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawArrays(GLenum mode, GLint first, GLsizei count, const char* caller = nullptr) const;

        /**
         * \brief The glDrawElements function renders primitives from array data.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP,
         * GL_TRIANGLE_FAN, and GL_TRIANGLES.
         * \param count Specifies the number of elements to be rendered.
         * \param type Specifies the type of the values in indices.
         * Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
         * \param indices Specifies a pointer to the location where the indices are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElements(
            GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, const char* caller = nullptr) const;

        /**
         * \brief The glEdgeFlagPointer function defines an array of edge flags.
         * \deprecated Deprecated in OpenGL 3.0. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param stride Specifies the byte offset between consecutive edge flags. If stride is 0, the edge flags are
         * understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first edge flag in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEdgeFlagPointer(GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glEnableClientState function enables a client-side capability.
         *
         * \param array Specifies the capability to enable.
         * Accepted values are GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, GL_INDEX_ARRAY,
         * GL_TEXTURE_COORD_ARRAY, GL_EDGE_FLAG_ARRAY, and GL_FOG_COORD_ARRAY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnableClientState(GLenum array, const char* caller = nullptr) const;

        /**
         * \brief The glGenTextures function generates texture names.
         *
         * \param n Specifies the number of texture names to be generated.
         * \param textures Specifies an array in which the generated texture names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenTextures(GLsizei n, GLuint* textures, const char* caller = nullptr) const;

        /**
         * \brief The glGetPointerv function returns the address of the specified pointer.
         *
         * \param pname Specifies the array or buffer pointer to be returned.
         * Accepted values are GL_VERTEX_ARRAY_POINTER, GL_NORMAL_ARRAY_POINTER,
         * GL_COLOR_ARRAY_POINTER, GL_INDEX_ARRAY_POINTER, GL_TEXTURE_COORD_ARRAY_POINTER, GL_EDGE_FLAG_ARRAY_POINTER,
         * GL_FEEDBACK_BUFFER_POINTER, and GL_SELECTION_BUFFER_POINTER.
         * \param params Specifies a pointer to a location in which the returned pointer is stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetPointerv(GLenum pname, GLvoid** params, const char* caller = nullptr) const;

        /**
         * \brief The glIndexPointer function defines an array of color indices.
         * \deprecated Deprecated in OpenGL 3.0. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param type Specifies the data type of each color index in the array.
         * Accepted values are GL_UNSIGNED_BYTE, GL_SHORT, GL_INT, GL_FLOAT, and GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive color indices. If stride is 0, the color
         * indices are understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first color index in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexPointer(GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glIndexub function sets the current color index.
         *
         * \param c Specifies the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexub(GLubyte c, const char* caller = nullptr) const;

        /**
         * \brief The glIndexubv function sets the current color index.
         *
         * \param c Specifies a pointer to an array that contains the new value for the current color index.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glIndexubv(const GLubyte* c, const char* caller = nullptr) const;

        /**
         * \brief The glInterleavedArrays function specifies and enables an array of interleaved vertex attributes.
         * \deprecated Deprecated in OpenGL 3.0. Use vertex buffer objects (VBOs) and vertex array objects (VAOs)
         * instead.
         *
         * \param format Specifies the format of the interleaved array. Accepted values are GL_V2F, GL_V3F,
         * GL_C4UB_V2F, GL_C4UB_V3F, GL_C3F_V3F, GL_N3F_V3F, GL_C4F_N3F_V3F, GL_T2F_V3F, GL_T4F_V4F, GL_T2F_C4UB_V3F,
         * GL_T2F_C3F_V3F, GL_T2F_N3F_V3F, GL_T2F_C4F_N3F_V3F, GL_T4F_C4F_N3F_V4F.
         * \param stride Specifies the byte offset between consecutive attributes. If stride is 0, the attributes
         * are understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first attribute in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInterleavedArrays(
            GLenum format, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glIsTexture function determines if a name corresponds to a texture.
         *
         * \param texture Specifies a value that may be the name of a texture.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if texture is a texture name, GL_FALSE otherwise.
         */
        GLboolean glIsTexture(GLuint texture, const char* caller = nullptr) const;

        /**
         * \brief The glNormalPointer function defines an array of normals.
         *
         * \param type Specifies the data type of each normal coordinate in the array.
         * Accepted values are GL_BYTE, GL_SHORT, GL_INT, GL_FLOAT, and GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive normals. If stride is 0, the normals are
         * understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first normal in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormalPointer(GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glPolygonOffset function sets the scale and units used to calculate depth values.
         *
         * \param factor Specifies a scale factor that is used to create a variable depth offset for each polygon.
         * The initial value is 0.
         * \param units Is multiplied by an implementation-specific value to create a constant depth offset. The
         * initial value is 0.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPolygonOffset(GLfloat factor, GLfloat units, const char* caller = nullptr) const;

        /**
         * \brief The glPopClientAttrib function pops the client attribute stack.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPopClientAttrib(const char* caller = nullptr) const;

        /**
         * \brief The glPrioritizeTextures function sets the residence priority of textures.
         *
         * \param n Specifies the number of textures to be prioritized.
         * \param textures Specifies an array containing the names of the textures to be prioritized.
         * \param priorities Specifies an array containing the residence priority of each texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPrioritizeTextures(
            GLsizei n, const GLuint* textures, const GLclampf* priorities, const char* caller = nullptr) const;

        /**
         * \brief The glPushClientAttrib function pushes the client attribute stack.
         *
         * \param mask Specifies a mask that indicates which attributes to save.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPushClientAttrib(GLbitfield mask, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordPointer function defines an array of texture coordinates.
         *
         * \param size Specifies the number of coordinates per element. Must be 1, 2, 3, or 4.
         * \param type Specifies the data type of each texture coordinate.
         * Accepted values are GL_SHORT, GL_INT, GL_FLOAT, and GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive texture coordinates. If stride is 0, the
         * texture coordinates are understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first texture coordinate in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordPointer(
            GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;

        /**
         * \brief The glTexSubImage1D function specifies a one-dimensional texture subimage.
         *
         * \param target Specifies the target texture. Accepted values are GL_TEXTURE_1D.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param width Specifies the width of the texture subimage.
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
        GLvoid glTexSubImage1D(
            GLenum target,
            GLint level,
            GLint xoffset,
            GLsizei width,
            GLenum format,
            GLenum type,
            const GLvoid* pixels,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexSubImage2D function specifies a two-dimensional texture subimage.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY,
         * GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_PROXY_TEXTURE_CUBE_MAP.
         * \param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth
         * mipmap reduction image.
         * \param xoffset Specifies a texel offset in the x direction within the texture array.
         * \param yoffset Specifies a texel offset in the y direction within the texture array.
         * \param width Specifies the width of the texture subimage.
         * \param height Specifies the height of the texture subimage.
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
        GLvoid glTexSubImage2D(
            GLenum target,
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
         * \brief The glVertexPointer function defines an array of vertex data.
         *
         * \param size Specifies the number of coordinates per vertex. Must be 2, 3, or 4.
         * \param type Specifies the data type of each coordinate.
         * Accepted values are GL_SHORT, GL_INT, GL_FLOAT, and GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive vertices. If stride is 0, the vertices are
         * understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first coordinate of the first vertex in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexPointer(
            GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
