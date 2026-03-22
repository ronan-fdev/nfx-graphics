#pragma once

/**
 * \file Functions_2_0.h
 * \brief Declares the OpenGL 2.0 function wrapper interface.
 */

#include "Functions_1_5.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_2_0
     * \brief Exposes the OpenGL 2.0 function set.
     */
    class Functions_2_0 : public Functions_1_5
    {
        static inline bool s_loaded;

    public:
        explicit Functions_2_0();
        Functions_2_0(const Functions_2_0&) = delete;
        Functions_2_0& operator=(const Functions_2_0&) = delete;
        Functions_2_0(Functions_2_0&&) = delete;
        Functions_2_0& operator=(Functions_2_0&&) = delete;
        virtual ~Functions_2_0();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glAttachShader function attaches a shader object to a program object.
         *
         * \param program Specifies the program object to which a shader object will be attached.
         * \param shader Specifies the shader object that is to be attached.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glAttachShader(GLuint program, GLuint shader, const char* caller = nullptr) const;

        /**
         * \brief The glBindAttribLocation function binds a user-defined varying out variable to a generic vertex
         * attribute index.
         *
         * \param program Specifies the program object in which the attribute variable is to be bound.
         * \param index Specifies the index of the generic vertex attribute to be bound.
         * \param name Specifies a null-terminated string containing the name of the vertex shader attribute
         * variable to be bound.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindAttribLocation(
            GLuint program, GLuint index, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glBlendEquationSeparate function sets the RGB and alpha blend equations separately.
         *
         * \param modeRGB Specifies how the red, green, and blue blending factors are computed.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.
         * \param modeAlpha Specifies how the alpha blending factor is computed.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha, const char* caller = nullptr) const;

        /**
         * \brief The glCompileShader function compiles a shader object.
         *
         * \param shader Specifies the shader object to be compiled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCompileShader(GLuint shader, const char* caller = nullptr) const;

        /**
         * \brief The glCreateProgram function creates a program object.
         *
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The glCreateProgram function returns a non-zero value by which the program object can be referenced.
         */
        GLuint glCreateProgram(const char* caller = nullptr) const;

        /**
         * \brief The glCreateShader function creates a shader object.
         *
         * \param type Specifies the type of shader to be created.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The glCreateShader function returns a non-zero value by which the shader object can be referenced.
         */
        GLuint glCreateShader(GLenum type, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteProgram function deletes a program object.
         *
         * \param program Specifies the program object to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteProgram(GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteShader function deletes a shader object.
         *
         * \param shader Specifies the shader object to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteShader(GLuint shader, const char* caller = nullptr) const;

        /**
         * \brief The glDetachShader function detaches a shader object from a program object.
         *
         * \param program Specifies the program object from which to detach the shader object.
         * \param shader Specifies the shader object to be detached.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDetachShader(GLuint program, GLuint shader, const char* caller = nullptr) const;

        /**
         * \brief The glDisableVertexAttribArray function disables a generic vertex attribute array.
         *
         * \param index Specifies the index of the generic vertex attribute to be disabled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDisableVertexAttribArray(GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glDrawBuffers function specifies a list of color buffers to be drawn into.
         *
         * \param n Specifies the number of buffers in bufs.
         * \param bufs Specifies an array of symbolic constants specifying the buffers into which fragment colors
         * or data values will be written. Accepted values are GL_NONE, GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT,
         * GL_BACK_RIGHT, GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, GL_FRONT_AND_BACK, GL_AUX0, GL_AUX1, GL_AUX2, GL_AUX3.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawBuffers(GLsizei n, const GLenum* bufs, const char* caller = nullptr) const;

        /**
         * \brief The glEnableVertexAttribArray function enables a generic vertex attribute array.
         *
         * \param index Specifies the index of the generic vertex attribute to be enabled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnableVertexAttribArray(GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveAttrib function returns information about an active attribute variable for the
         * specified program object.
         *
         * \param program Specifies the program object to be queried.
         * \param index Specifies the index of the attribute variable to be queried.
         * \param bufSize Specifies the maximum number of characters that can be written into name.
         * \param length Specifies a pointer to a variable that will receive the length of the attribute variable
         * name.
         * \param size Specifies a pointer to a variable that will receive the size of the attribute variable.
         * \param type Specifies a pointer to a variable that will receive the data type of the attribute variable.
         * Possible values are GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4, GL_FLOAT_MAT2,
         * GL_FLOAT_MAT3, GL_FLOAT_MAT4, GL_FLOAT_MAT2x3, GL_FLOAT_MAT2x4, GL_FLOAT_MAT3x2, GL_FLOAT_MAT3x4,
         * GL_FLOAT_MAT4x2, GL_FLOAT_MAT4x3.
         * \param name Specifies an array of characters that will receive the attribute variable name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveAttrib(
            GLuint program,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLint* size,
            GLenum* type,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveUniform function returns information about an active uniform variable for the
         * specified program object.
         *
         * \param program Specifies the program object to be queried.
         * \param index Specifies the index of the uniform variable to be queried.
         * \param bufSize Specifies the maximum number of characters that can be written into name.
         * \param length Specifies a pointer to a variable that will receive the length of the uniform variable name.
         * \param size Specifies a pointer to a variable that will receive the size of the uniform variable.
         * \param type Specifies a pointer to a variable that will receive the data type of the uniform variable.
         * Possible values are GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4, GL_INT,
         * GL_INT_VEC2, GL_INT_VEC3, GL_INT_VEC4, GL_BOOL, GL_BOOL_VEC2, GL_BOOL_VEC3, GL_BOOL_VEC4, GL_FLOAT_MAT2,
         * GL_FLOAT_MAT3, GL_FLOAT_MAT4, GL_SAMPLER_1D, GL_SAMPLER_2D, GL_SAMPLER_3D, GL_SAMPLER_CUBE,
         * GL_SAMPLER_1D_SHADOW, GL_SAMPLER_2D_SHADOW.
         * \param name Specifies an array of characters that will receive the uniform variable name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveUniform(
            GLuint program,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLint* size,
            GLenum* type,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetAttachedShaders function returns the shader objects attached to a program object.
         *
         * \param program Specifies the program object to be queried.
         * \param maxCount Specifies the size of the array for storing the returned object names.
         * \param count Specifies a pointer to a variable that will receive the number of objects returned.
         * \param shaders Specifies an array that will receive the names of attached shader objects.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetAttachedShaders(
            GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders, const char* caller = nullptr) const;

        /**
         * \brief The glGetAttribLocation function returns the location of an attribute variable.
         *
         * \param program Specifies the program object to be queried.
         * \param name Specifies the name of the attribute variable whose location is to be queried.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The location of the attribute variable.
         */
        GLint glGetAttribLocation(GLuint program, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramInfoLog function returns the information log for a program object.
         *
         * \param program Specifies the program object to be queried.
         * \param bufSize Specifies the size of the buffer for storing the returned information log.
         * \param length Specifies a pointer to a variable that will receive the length of the information log.
         * \param infoLog Specifies an array that will receive the information log.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramInfoLog(
            GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramiv function returns a parameter from a program object.
         *
         * \param program Specifies the program object to be queried.
         * \param pname Specifies the parameter to be queried.
         * Accepted values are GL_DELETE_STATUS, GL_LINK_STATUS, GL_VALIDATE_STATUS,
         * GL_INFO_LOG_LENGTH, GL_ATTACHED_SHADERS, GL_ACTIVE_ATTRIBUTES, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
         * GL_ACTIVE_UNIFORMS, GL_ACTIVE_UNIFORM_MAX_LENGTH.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramiv(GLuint program, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetShaderInfoLog function returns the information log for a shader object.
         *
         * \param shader Specifies the shader object to be queried.
         * \param bufSize Specifies the size of the buffer for storing the returned information log.
         * \param length Specifies a pointer to a variable that will receive the length of the information log.
         * \param infoLog Specifies an array that will receive the information log.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetShaderInfoLog(
            GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog, const char* caller = nullptr) const;

        /**
         * \brief The glGetShaderiv function returns a parameter from a shader object.
         *
         * \param shader Specifies the shader object to be queried.
         * \param pname Specifies the parameter to be queried.
         * Accepted values are GL_SHADER_TYPE, GL_DELETE_STATUS, GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH,
         * GL_SHADER_SOURCE_LENGTH.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetShaderiv(GLuint shader, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetShaderSource function returns the source code string for a shader object.
         *
         * \param shader Specifies the shader object to be queried.
         * \param bufSize Specifies the size of the buffer for storing the returned source code string.
         * \param length Specifies a pointer to a variable that will receive the length of the source code string.
         * \param source Specifies an array that will receive the source code string.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetShaderSource(
            GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformfv function returns the value of a uniform variable for the specified program
         * object.
         *
         * \param program Specifies the program object to be queried.
         * \param location Specifies the location of the uniform variable to be queried.
         * \param params Specifies a pointer to a variable that will receive the value of the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformfv(GLuint program, GLint location, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformiv function returns the value of a uniform variable for the specified program
         * object.
         *
         * \param program Specifies the program object to be queried.
         * \param location Specifies the location of the uniform variable to be queried.
         * \param params Specifies a pointer to a variable that will receive the value of the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformiv(GLuint program, GLint location, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformLocation function returns the location of a uniform variable.
         *
         * \param program Specifies the program object to be queried.
         * \param name Specifies the name of the uniform variable whose location is to be queried.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The location of the uniform variable.
         */
        GLint glGetUniformLocation(GLuint program, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribdv function returns the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to a variable that will receive the value of the vertex attribute
         * parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribfv function returns the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to a variable that will receive the value of the vertex attribute
         * parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribiv function returns the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to a variable that will receive the value of the vertex attribute
         * parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribPointerv function returns the pointer to a generic vertex attribute array.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_POINTER.
         * \param pointer Specifies a pointer to a variable that will receive the pointer value.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribPointerv(
            GLuint index, GLenum pname, GLvoid** pointer, const char* caller = nullptr) const;

        /**
         * \brief The glIsProgram function determines if a name corresponds to a program object.
         *
         * \param program Specifies a value that may be the name of a program object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if program is a program object, GL_FALSE otherwise.
         */
        GLboolean glIsProgram(GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glIsShader function determines if a name corresponds to a shader object.
         *
         * \param shader Specifies a value that may be the name of a shader object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if shader is a shader object, GL_FALSE otherwise.
         */
        GLboolean glIsShader(GLuint shader, const char* caller = nullptr) const;

        /**
         * \brief The glLinkProgram function links a program object.
         *
         * \param program Specifies the program object to be linked.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glLinkProgram(GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glShaderSource function sets the source code in a shader object.
         *
         * \param shader Specifies the shader object whose source code is to be replaced.
         * \param count Specifies the number of elements in the string and length arrays.
         * \param string Specifies an array of pointers to strings containing the source code to be loaded into the
         * shader.
         * \param length Specifies an array of string lengths.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glShaderSource(
            GLuint shader,
            GLsizei count,
            const GLchar* const* string,
            const GLint* length,
            const char* caller = nullptr) const;

        /**
         * \brief The glStencilFuncSeparate function sets the stencil test function for front and/or back faces.
         *
         * \param face Specifies whether front and/or back stencil state is updated.
         * Accepted values are GL_FRONT, GL_BACK, GL_FRONT_AND_BACK.
         * \param func Specifies the test function.
         * Accepted values are GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL,
         * GL_NOTEQUAL, GL_ALWAYS.
         * \param ref Specifies the reference value for the stencil test.
         * \param mask Specifies a mask that is ANDed with both the reference value and the stored stencil value
         * when the test is done.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilFuncSeparate(
            GLenum face, GLenum func, GLint ref, GLuint mask, const char* caller = nullptr) const;

        /**
         * \brief The glStencilMaskSeparate function controls the front and/or back writing of individual bits in the
         * stencil planes.
         *
         * \param face Specifies whether front and/or back stencil writing is enabled.
         * Accepted values are GL_FRONT, GL_BACK, GL_FRONT_AND_BACK.
         * \param mask Specifies a bit mask to enable and disable writing of individual bits in the stencil planes.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilMaskSeparate(GLenum face, GLuint mask, const char* caller = nullptr) const;

        /**
         * \brief The glStencilOpSeparate function sets the stencil test actions for front and/or back faces.
         *
         * \param face Specifies whether front and/or back stencil state is updated.
         * Accepted values are GL_FRONT, GL_BACK, GL_FRONT_AND_BACK.
         * \param sfail Specifies the action to take when the stencil test fails.
         * Accepted values are GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR,
         * GL_DECR_WRAP, GL_INVERT.
         * \param dpfail Specifies the action to take when the stencil test passes, but the depth test fails.
         * Accepted values are GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR,
         * GL_DECR_WRAP, GL_INVERT.
         * \param dppass Specifies the action to take when both the stencil test and the depth test pass.
         * Accepted values are GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR,
         * GL_DECR_WRAP, GL_INVERT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glStencilOpSeparate(
            GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1f function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1f(GLint location, GLfloat v0, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1fv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1fv(GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1i function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1i(GLint location, GLint v0, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1iv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1iv(GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2f function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2f(GLint location, GLfloat v0, GLfloat v1, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2fv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2fv(GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2i function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2i(GLint location, GLint v0, GLint v1, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2iv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2iv(GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3f function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3fv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3fv(GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3i function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3i(GLint location, GLint v0, GLint v1, GLint v2, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3iv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3iv(GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4f function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param v3 Specifies the fourth new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4f(
            GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4fv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4fv(GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4i function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param v3 Specifies the fourth new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4iv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4iv(GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix2fv function specifies the value of a 2x2 matrix uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3fv function specifies the value of a 3x3 matrix uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4fv function specifies the value of a 4x4 matrix uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4fv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUseProgram function installs a program object as part of the current rendering state.
         *
         * \param program Specifies the handle of the program object to be used.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUseProgram(GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glValidateProgram function checks to see whether the executables contained in a program can
         * execute given the current OpenGL state.
         *
         * \param program Specifies the handle of the program object to be validated.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glValidateProgram(GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1d function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1d instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1d(GLuint index, GLdouble x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1dv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1dv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new value to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1f function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1f instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1f(GLuint index, GLfloat x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1fv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1fv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new value to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1fv(GLuint index, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1s function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1s instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1s(GLuint index, GLshort x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib1sv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL1sv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new value to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib1sv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2d function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2d instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2dv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2dv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2f function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2f instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2fv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2fv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2fv(GLuint index, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2s function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2s instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2s(GLuint index, GLshort x, GLshort y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib2sv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL2sv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib2sv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3d function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3d instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3dv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3dv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3f function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3f instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3fv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3fv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3fv(GLuint index, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3s function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3s instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib3sv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL3sv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib3sv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4bv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4bv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4bv(GLuint index, const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4d function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4d instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4d(
            GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4dv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4dv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4f function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4f instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4f(
            GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4fv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4fv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4fv(GLuint index, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4iv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4iv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4iv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nbv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nbv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nbv(GLuint index, const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Niv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Niv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Niv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nsv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nsv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nsv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nub function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nub instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nub(
            GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nubv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nubv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nubv(GLuint index, const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nuiv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nuiv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nuiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4Nusv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4Nusv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4Nusv(GLuint index, const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4s function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4s instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4s(
            GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4sv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4sv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4sv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4ubv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4ubv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4ubv(GLuint index, const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4uiv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4uiv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4uiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttrib4usv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 3.0. Use glVertexAttribL4usv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttrib4usv(GLuint index, const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribPointer function defines an array of generic vertex attribute data.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param size Specifies the number of components per generic vertex attribute.
         * Accepted values are 1, 2, 3, 4.
         * \param type Specifies the data type of each component in the array.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT, GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV,
         * GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted
         * directly as fixed-point values (GL_FALSE) when they are accessed.
         * \param stride Specifies the byte offset between consecutive generic vertex attributes. If stride is 0,
         * the generic vertex attributes are understood to be tightly packed in the array.
         * \param pointer Specifies a pointer to the first component of the first generic vertex attribute in the
         * array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribPointer(
            GLuint index,
            GLint size,
            GLenum type,
            GLboolean normalized,
            GLsizei stride,
            const GLvoid* pointer,
            const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
