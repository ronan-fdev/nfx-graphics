#pragma once

/**
 * \file Functions_4_6.h
 * \brief Declares the OpenGL 4.6 function wrapper interface.
 */

#include "Functions_4_5.h"

namespace nfx::graphics::gl
{
    class Functions;

    /**
     * \class Functions_4_6
     * \brief Exposes the OpenGL 4.6 function set.
     */
    class Functions_4_6 : public Functions_4_5
    {
        friend class Functions;

        static inline bool s_loaded;

    public:
        explicit Functions_4_6();
        Functions_4_6(const Functions_4_6&) = delete;
        Functions_4_6& operator=(const Functions_4_6&) = delete;
        Functions_4_6(Functions_4_6&&) = delete;
        Functions_4_6& operator=(Functions_4_6&&) = delete;
        virtual ~Functions_4_6();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glMultiDrawArraysIndirectCount function renders multiple sets of primitives from array data,
         * with the draw count sourced from a buffer.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param indirect Specifies a byte offset (cast to a pointer type) into the buffer bound to
         * GL_DRAW_INDIRECT_BUFFER from which the draw parameters are sourced.
         * \param drawcount Specifies the byte offset into the buffer bound to GL_PARAMETER_BUFFER_ARB from which
         * the draw count is sourced.
         * \param maxdrawcount Specifies the maximum number of draws that are expected to be stored in the buffer.
         * \param stride Specifies the byte stride between successive sets of draw parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawArraysIndirectCount(
            GLenum mode,
            const GLvoid* indirect,
            GLintptr drawcount,
            GLsizei maxdrawcount,
            GLsizei stride,
            const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawElementsIndirectCount function renders multiple sets of primitives by specifying
         * indices of array data elements, with the draw count sourced from a buffer.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT.
         * \param indirect Specifies a byte offset (cast to a pointer type) into the buffer bound to
         * GL_DRAW_INDIRECT_BUFFER from which the draw parameters are sourced.
         * \param drawcount Specifies the byte offset into the buffer bound to GL_PARAMETER_BUFFER_ARB from which
         * the draw count is sourced.
         * \param maxdrawcount Specifies the maximum number of draws that are expected to be stored in the buffer.
         * \param stride Specifies the byte stride between successive sets of draw parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawElementsIndirectCount(
            GLenum mode,
            GLenum type,
            const GLvoid* indirect,
            GLintptr drawcount,
            GLsizei maxdrawcount,
            GLsizei stride,
            const char* caller = nullptr) const;

        /**
         * \brief The glPolygonOffsetClamp function sets the scale and units used to calculate depth values, and
         * clamps the resulting depth value.
         *
         * \param factor Specifies a scale factor that is used to create a variable depth offset for each polygon.
         * \param units Specifies a multiplier used to create a constant depth offset.
         * \param clamp Specifies the maximum depth offset.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp, const char* caller = nullptr) const;

        /**
         * \brief The glSpecializeShader function specializes a shader for a particular set of specialization
         * constants.
         *
         * \param shader  Specifies the name of the shader object to be specialized.
         * \param pEntryPoint  Specifies the name of the entry point in the shader to use for this
         * shader.
         * \param numSpecializationConstants Specifies the number of specialization constants.
         * \param pConstantIndex  Specifies an array of specialization constant indices.
         * \param pConstantValue  Specifies an array of values for the specialization constants.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glSpecializeShader(
            GLuint shader,
            const GLchar* pEntryPoint,
            GLuint numSpecializationConstants,
            const GLuint* pConstantIndex,
            const GLuint* pConstantValue,
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
