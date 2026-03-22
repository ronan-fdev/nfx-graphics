#pragma once

/**
 * \file Functions_4_1.h
 * \brief Declares the OpenGL 4.1 function wrapper interface.
 */

#include "Functions_4_0.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_1
     * \brief Exposes the OpenGL 4.1 function set.
     */
    class Functions_4_1 : public Functions_4_0
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_1();
        Functions_4_1(const Functions_4_1&) = delete;
        Functions_4_1& operator=(const Functions_4_1&) = delete;
        Functions_4_1(Functions_4_1&&) = delete;
        Functions_4_1& operator=(Functions_4_1&&) = delete;
        virtual ~Functions_4_1();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glActiveShaderProgram function sets the active program object for a program pipeline object.
         *
         * \param pipeline Specifies the name of the program pipeline object.
         * \param program Specifies the name of the program object to be made active.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glActiveShaderProgram(GLuint pipeline, GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glBindProgramPipeline function binds a program pipeline to the context.
         *
         * \param pipeline Specifies the name of the program pipeline object to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindProgramPipeline(GLuint pipeline, const char* caller = nullptr) const;

        /**
         * \brief The glClearDepthf function specifies the clear value for the depth buffer.
         *
         * \param d Specifies the depth value used when the depth buffer is cleared.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearDepthf(GLfloat d, const char* caller = nullptr) const;

        /**
         * \brief The glCreateShaderProgramv function creates a program object from a list of null-terminated source
         * code strings.
         *
         * \param type Specifies the type of shader to create.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER.
         * \param count Specifies the number of source code strings in the array.
         * \param strings Specifies an array of pointers to source code strings.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The name of the created program object.
         */
        GLuint glCreateShaderProgramv(
            GLenum type, GLsizei count, const GLchar* const* strings, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteProgramPipelines function deletes named program pipeline objects.
         *
         * \param n Specifies the number of program pipeline objects to be deleted.
         * \param pipelines Specifies an array of program pipeline objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteProgramPipelines(GLsizei n, const GLuint* pipelines, const char* caller = nullptr) const;

        /**
         * \brief The glDepthRangeArrayv function specifies the depth range for a set of viewports.
         *
         * \param first Specifies the first viewport to set the depth range for.
         * \param count Specifies the number of viewports to set the depth range for.
         * \param v Specifies an array of pairs of double-precision values representing the near and far depth
         * ranges.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glDepthRangef function specifies the depth range for all viewports.
         *
         * \param n Specifies the near depth range.
         * \param f Specifies the far depth range.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthRangef(GLfloat n, GLfloat f, const char* caller = nullptr) const;

        /**
         * \brief The glDepthRangeIndexed function specifies the depth range for a specific viewport.
         *
         * \param index Specifies the index of the viewport to set the depth range for.
         * \param n Specifies the near depth range.
         * \param f Specifies the far depth range.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f, const char* caller = nullptr) const;

        /**
         * \brief The glGenProgramPipelines function generates program pipeline object names.
         *
         * \param n Specifies the number of program pipeline object names to generate.
         * \param pipelines Specifies an array in which the generated program pipeline object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenProgramPipelines(GLsizei n, GLuint* pipelines, const char* caller = nullptr) const;

        /**
         * \brief The glGetDoublei_v function retrieves double-precision values of a specified parameter for a
         * specific index.
         *
         * \param target Specifies the symbolic name of the parameter to query.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING.
         * \param index Specifies the index of the parameter to query.
         * \param data Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetDoublei_v(GLenum target, GLuint index, GLdouble* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetFloati_v function retrieves float values of a specified parameter for a specific index.
         *
         * \param target Specifies the symbolic name of the parameter to query.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING.
         * \param index Specifies the index of the parameter to query.
         * \param data Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetFloati_v(GLenum target, GLuint index, GLfloat* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramBinary function retrieves a binary representation of a program object.
         *
         * \param program Specifies the name of the program object to retrieve the binary representation for.
         * \param bufSize Specifies the size of the buffer to receive the binary representation.
         * \param length Specifies a pointer to the variable to receive the length of the binary representation.
         * \param binaryFormat Specifies a pointer to the variable to receive the format of the binary representation.
         * \param binary Specifies a pointer to the buffer to receive the binary representation.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramBinary(
            GLuint program,
            GLsizei bufSize,
            GLsizei* length,
            GLenum* binaryFormat,
            GLvoid* binary,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramPipelineInfoLog function retrieves the information log for a program pipeline
         * object.
         *
         * \param pipeline Specifies the name of the program pipeline object.
         * \param bufSize Specifies the size of the buffer to receive the information log.
         * \param length Specifies a pointer to the variable to receive the length of the information log.
         * \param infoLog Specifies a pointer to the buffer to receive the information log.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramPipelineInfoLog(
            GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramPipelineiv function retrieves parameters of a program pipeline object.
         *
         * \param pipeline Specifies the name of the program pipeline object.
         * \param pname Specifies the symbolic name of the parameter to query.
         * Accepted values are GL_ACTIVE_PROGRAM, GL_FRAGMENT_SHADER, GL_VERTEX_SHADER,
         * GL_GEOMETRY_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER, GL_INFO_LOG_LENGTH,
         * GL_VALIDATE_STATUS.
         * \param params Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetShaderPrecisionFormat function retrieves the range and precision for numeric formats
         * supported by the shader compiler.
         *
         * \param shadertype Specifies the type of shader to query.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param precisiontype Specifies the numeric format to query.
         * Accepted values are GL_LOW_FLOAT, GL_MEDIUM_FLOAT, GL_HIGH_FLOAT, GL_LOW_INT,
         * GL_MEDIUM_INT, GL_HIGH_INT.
         * \param range Specifies a pointer to an array to receive the range of the numeric format.
         * \param precision Specifies a pointer to a variable to receive the precision of the numeric format.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetShaderPrecisionFormat(
            GLenum shadertype,
            GLenum precisiontype,
            GLint* range,
            GLint* precision,
            const char* caller = nullptr) const;

        /**
         * \brief The glShaderBinary function loads precompiled binary shaders.
         * \deprecated Deprecated in OpenGL 4.6. Use glSpecializeShader instead.
         *
         * \param count Specifies the number of shader objects to be loaded.
         * \param shaders Specifies an array of shader objects to be loaded.
         * \param binaryFormat Specifies the format of the precompiled binary.
         * Accepted values are GL_SHADER_BINARY_FORMAT_SPIR_V, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB.
         * \param binary Specifies a pointer to the precompiled binary.
         * \param length Specifies the length of the precompiled binary.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glShaderBinary(
            GLsizei count,
            const GLuint* shaders,
            GLenum binaryFormat,
            const GLvoid* binary,
            GLsizei length,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribLdv function retrieves the double-precision value of a vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to query.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to query.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_ARRAY_LONG, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to the variable to receive the value of the vertex attribute parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glIsProgramPipeline function determines if a name corresponds to a program pipeline object.
         *
         * \param pipeline Specifies a value that may be the name of a program pipeline object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if pipeline is a program pipeline object, GL_FALSE otherwise.
         */
        GLboolean glIsProgramPipeline(GLuint pipeline, const char* caller = nullptr) const;

        /**
         * \brief The glProgramBinary function loads a program object with a binary representation.
         *
         * \param program Specifies the name of the program object to load the binary representation into.
         * \param binaryFormat Specifies the format of the binary representation.
         * Accepted values are implementation-dependent.
         * \param binary Specifies a pointer to the binary representation.
         * \param length Specifies the length of the binary representation.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramBinary(
            GLuint program,
            GLenum binaryFormat,
            const GLvoid* binary,
            GLsizei length,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramParameteri function sets a program object parameter.
         *
         * \param program Specifies the name of the program object to set the parameter for.
         * \param pname Specifies the symbolic name of the parameter to set.
         * Accepted values are GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_PROGRAM_SEPARABLE.
         * \param value Specifies the value to set the parameter to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramParameteri(GLuint program, GLenum pname, GLint value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1d function specifies the value of a double uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1d(GLuint program, GLint location, GLdouble v0, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1dv function specifies the value of a double uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1dv(
            GLuint program, GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1f function specifies the value of a float uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1f(GLuint program, GLint location, GLfloat v0, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1fv function specifies the value of a float uniform variable array for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1fv(
            GLuint program, GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1i function specifies the value of an integer uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1i(GLuint program, GLint location, GLint v0, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1iv function specifies the value of an integer uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1iv(
            GLuint program, GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1ui function specifies the value of an unsigned integer uniform variable for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1ui(GLuint program, GLint location, GLuint v0, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform1uiv function specifies the value of an unsigned integer uniform variable array
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform1uiv(
            GLuint program, GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2d function specifies the value of a vec2 double uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2d(
            GLuint program, GLint location, GLdouble v0, GLdouble v1, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2dv function specifies the value of a vec2 double uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2dv(
            GLuint program, GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2f function specifies the value of a vec2 float uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2f(
            GLuint program, GLint location, GLfloat v0, GLfloat v1, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2fv function specifies the value of a vec2 float uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2fv(
            GLuint program, GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2i function specifies the value of a vec2 integer uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2i(
            GLuint program, GLint location, GLint v0, GLint v1, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2iv function specifies the value of a vec2 integer uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2iv(
            GLuint program, GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2ui function specifies the value of a vec2 unsigned integer uniform variable for
         * a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2ui(
            GLuint program, GLint location, GLuint v0, GLuint v1, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform2uiv function specifies the value of a vec2 unsigned integer uniform variable
         * array for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform2uiv(
            GLuint program, GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3d function specifies the value of a vec3 double uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3d(
            GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3dv function specifies the value of a vec3 double uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3dv(
            GLuint program, GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3f function specifies the value of a vec3 float uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3f(
            GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3fv function specifies the value of a vec3 float uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3fv(
            GLuint program, GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3i function specifies the value of a vec3 integer uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3i(
            GLuint program, GLint location, GLint v0, GLint v1, GLint v2, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3iv function specifies the value of a vec3 integer uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3iv(
            GLuint program, GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3ui function specifies the value of a vec3 unsigned integer uniform variable for
         * a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3ui(
            GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform3uiv function specifies the value of a vec3 unsigned integer uniform variable
         * array for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform3uiv(
            GLuint program, GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4d function specifies the value of a vec4 double uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param v3 Specifies the new w value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4d(
            GLuint program,
            GLint location,
            GLdouble v0,
            GLdouble v1,
            GLdouble v2,
            GLdouble v3,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4dv function specifies the value of a vec4 double uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4dv(
            GLuint program, GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4f function specifies the value of a vec4 float uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param v3 Specifies the new w value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4f(
            GLuint program,
            GLint location,
            GLfloat v0,
            GLfloat v1,
            GLfloat v2,
            GLfloat v3,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4fv function specifies the value of a vec4 float uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4fv(
            GLuint program, GLint location, GLsizei count, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4i function specifies the value of a vec4 integer uniform variable for a program
         * object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param v3 Specifies the new w value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4i(
            GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4iv function specifies the value of a vec4 integer uniform variable array for a
         * program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4iv(
            GLuint program, GLint location, GLsizei count, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniform4ui function specifies the value of a vec4 unsigned integer uniform variable for
         * a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new x value to be used for the specified uniform variable.
         * \param v1 Specifies the new y value to be used for the specified uniform variable.
         * \param v2 Specifies the new z value to be used for the specified uniform variable.
         * \param v3 Specifies the new w value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4ui(
            GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char* caller = nullptr)
            const;

        /**
         * \brief The glProgramUniform4uiv function specifies the value of a vec4 unsigned integer uniform variable
         * array for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniform4uiv(
            GLuint program, GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2dv function specifies the value of a 2x2 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2fv function specifies the value of a 2x2 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2x3dv function specifies the value of a 2x3 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2x3dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2x3fv function specifies the value of a 2x3 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2x3fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2x4dv function specifies the value of a 2x4 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2x4dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix2x4fv function specifies the value of a 2x4 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix2x4fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3dv function specifies the value of a 3x3 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3fv function specifies the value of a 3x3 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3x2dv function specifies the value of a 3x2 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3x2dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3x2fv function specifies the value of a 3x2 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3x2fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3x4dv function specifies the value of a 3x4 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3x4dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix3x4fv function specifies the value of a 3x4 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix3x4fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4dv function specifies the value of a 4x4 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4fv function specifies the value of a 4x4 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4x2dv function specifies the value of a 4x2 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4x2dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4x2fv function specifies the value of a 4x2 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4x2fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4x3dv function specifies the value of a 4x3 double matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4x3dv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glProgramUniformMatrix4x3fv function specifies the value of a 4x3 float matrix uniform variable
         * for a program object.
         *
         * \param program Specifies the name of the program object.
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glProgramUniformMatrix4x3fv(
            GLuint program,
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLfloat* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glReleaseShaderCompiler function releases resources allocated by the shader compiler.
         * \deprecated Deprecated in OpenGL 4.6. Use glReleaseShaderCompilerKHR instead.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glReleaseShaderCompiler(const char* caller = nullptr) const;

        /**
         * \brief The glScissorArrayv function defines the scissor box for multiple viewports.
         *
         * \param first Specifies the index of the first viewport whose scissor box to modify.
         * \param count Specifies the number of scissor boxes to modify.
         * \param v Specifies a pointer to an array of integers containing the scissor box parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScissorArrayv(GLuint first, GLsizei count, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glScissorIndexed function defines the scissor box for a specific viewport.
         *
         * \param index Specifies the index of the viewport whose scissor box to modify.
         * \param left Specifies the left coordinate of the scissor box.
         * \param bottom Specifies the bottom coordinate of the scissor box.
         * \param width Specifies the width of the scissor box.
         * \param height Specifies the height of the scissor box.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScissorIndexed(
            GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height, const char* caller = nullptr) const;

        /**
         * \brief The glScissorIndexedv function defines the scissor box for a specific viewport.
         *
         * \param index Specifies the index of the viewport whose scissor box to modify.
         * \param v Specifies a pointer to an array of integers containing the scissor box parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glScissorIndexedv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glUseProgramStages function binds stages of a program object to a program pipeline object.
         *
         * \param pipeline Specifies the name of the program pipeline object.
         * \param stages Specifies a bitfield identifying the program stages to bind.
         * Accepted values are GL_VERTEX_SHADER_BIT, GL_FRAGMENT_SHADER_BIT, GL_GEOMETRY_SHADER_BIT,
         * GL_TESS_CONTROL_SHADER_BIT, GL_TESS_EVALUATION_SHADER_BIT, GL_COMPUTE_SHADER_BIT,
         * GL_ALL_SHADER_BITS.
         * \param program Specifies the name of the program object to bind to the pipeline.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUseProgramStages(
            GLuint pipeline, GLbitfield stages, GLuint program, const char* caller = nullptr) const;

        /**
         * \brief The glValidateProgramPipeline function validates a program pipeline object.
         *
         * \param pipeline Specifies the name of the program pipeline object to validate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glValidateProgramPipeline(GLuint pipeline, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL1d function specifies the value of a double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param x Specifies the new value to be used for the specified vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL1d(GLuint index, GLdouble x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL1dv function specifies the value of a double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param v Specifies a pointer to an array containing the new value to be used for the specified vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL1dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL2d function specifies the value of a vec2 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param x Specifies the new x value to be used for the specified vertex attribute.
         * \param y Specifies the new y value to be used for the specified vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL2dv function specifies the value of a vec2 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param v Specifies a pointer to an array containing the new values to be used for the specified
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL2dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL3d function specifies the value of a vec3 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param x Specifies the new x value to be used for the specified vertex attribute.
         * \param y Specifies the new y value to be used for the specified vertex attribute.
         * \param z Specifies the new z value to be used for the specified vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL3dv function specifies the value of a vec3 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param v Specifies a pointer to an array containing the new values to be used for the specified
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL3dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL4d function specifies the value of a vec4 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param x Specifies the new x value to be used for the specified vertex attribute.
         * \param y Specifies the new y value to be used for the specified vertex attribute.
         * \param z Specifies the new z value to be used for the specified vertex attribute.
         * \param w Specifies the new w value to be used for the specified vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL4d(
            GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribL4dv function specifies the value of a vec4 double vertex attribute.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param v Specifies a pointer to an array containing the new values to be used for the specified
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribL4dv(GLuint index, const GLdouble* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribLPointer function defines an array of double vertex attribute data.
         *
         * \param index Specifies the index of the vertex attribute to be modified.
         * \param size Specifies the number of components per vertex attribute.
         * Accepted values are 1, 2, 3, and 4.
         * \param type Specifies the data type of each component in the array.
         * Accepted value is GL_DOUBLE.
         * \param stride Specifies the byte offset between consecutive vertex attributes.
         * \param pointer Specifies a pointer to the first component of the first vertex attribute in the array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribLPointer(
            GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr)
            const;

        /**
         * \brief The glViewportArrayv function sets the viewport parameters for multiple viewports.
         *
         * \param first Specifies the index of the first viewport to set.
         * \param count Specifies the number of viewports to set.
         * \param v Specifies a pointer to an array containing the viewport parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glViewportArrayv(GLuint first, GLsizei count, const GLfloat* v, const char* caller = nullptr) const;

        /**
         * \brief The glViewportIndexedf function sets the viewport parameters for a specific viewport.
         *
         * \param index Specifies the index of the viewport to set.
         * \param x Specifies the x coordinate of the lower left corner of the viewport.
         * \param y Specifies the y coordinate of the lower left corner of the viewport.
         * \param w Specifies the width of the viewport.
         * \param h Specifies the height of the viewport.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glViewportIndexedf(
            GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const char* caller = nullptr) const;

        /**
         * \brief The glViewportIndexedfv function sets the viewport parameters for a specific viewport.
         *
         * \param index Specifies the index of the viewport to set.
         * \param v Specifies a pointer to an array containing the viewport parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glViewportIndexedfv(GLuint index, const GLfloat* v, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
