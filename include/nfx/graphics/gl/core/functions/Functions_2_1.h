#pragma once

/**
 * \file Functions_2_1.h
 * \brief Declares the OpenGL 2.1 function wrapper interface.
 */

#include "Functions_2_0.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_2_1
     * \brief Exposes the OpenGL 2.1 function set.
     */
    class Functions_2_1 : public Functions_2_0
    {
        static inline bool s_loaded;

    public:
        explicit Functions_2_1();
        Functions_2_1(const Functions_2_1&) = delete;
        Functions_2_1& operator=(const Functions_2_1&) = delete;
        Functions_2_1(Functions_2_1&&) = delete;
        Functions_2_1& operator=(Functions_2_1&&) = delete;
        virtual ~Functions_2_1();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glUniformMatrix2x3fv function specifies the value of a 2x3 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix2x3fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2x3fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix2x4fv function specifies the value of a 2x4 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix2x4fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2x4fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3x2fv function specifies the value of a 3x2 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix3x2fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3x2fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3x4fv function specifies the value of a 3x4 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix3x4fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3x4fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4x2fv function specifies the value of a 4x2 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix4x2fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4x2fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4x3fv function specifies the value of a 4x3 matrix uniform variable for the
         * current program object.
         * \deprecated Deprecated in OpenGL 4.1. Use glProgramUniformMatrix4x3fv instead.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of count values that will be used to update the specified
         * uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4x3fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
