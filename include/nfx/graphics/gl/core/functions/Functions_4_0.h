#pragma once

/**
 * \file Functions_4_0.h
 * \brief Declares the OpenGL 4.0 function wrapper interface.
 */

#include "Functions_3_3.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_0
     * \brief Exposes the OpenGL 4.0 function set.
     */
    class Functions_4_0 : public Functions_3_3
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_0();
        Functions_4_0(const Functions_4_0&) = delete;
        Functions_4_0& operator=(const Functions_4_0&) = delete;
        Functions_4_0(Functions_4_0&&) = delete;
        Functions_4_0& operator=(Functions_4_0&&) = delete;
        virtual ~Functions_4_0();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBeginQueryIndexed function begins a query object on an indexed target.
         *
         * \param target Specifies the target type of query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
         * GL_TIME_ELAPSED.
         * \param index Specifies the index of the query object target.
         * \param id Specifies the name of a query object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBeginQueryIndexed(GLenum target, GLuint index, GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glBindTransformFeedback function binds a transform feedback object.
         *
         * \param target Specifies the target to which the transform feedback object is bound.
         * Accepted values are GL_TRANSFORM_FEEDBACK.
         * \param id Specifies the name of the transform feedback object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindTransformFeedback(GLenum target, GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glBlendEquationi function sets the blend equation for a specific draw buffer.
         *
         * \param buf Specifies the index of the draw buffer.
         * \param mode Specifies the blend equation mode.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendEquationi(GLuint buf, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glBlendEquationSeparatei function sets the RGB and alpha blend equations separately for a
         * specific draw buffer.
         *
         * \param buf Specifies the index of the draw buffer.
         * \param modeRGB Specifies the RGB blend equation mode.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.
         * \param modeAlpha Specifies the alpha blend equation mode.
         * Accepted values are GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendEquationSeparatei(
            GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char* caller = nullptr) const;

        /**
         * \brief The glBlendFunci function sets the blend functions for a specific draw buffer.
         *
         * \param buf Specifies the index of the draw buffer.
         * \param src Specifies the source blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param dst Specifies the destination blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendFunci(GLuint buf, GLenum src, GLenum dst, const char* caller = nullptr) const;

        /**
         * \brief The glBlendFuncSeparatei function sets the RGB and alpha blend functions separately for a specific
         * draw buffer.
         *
         * \param buf Specifies the index of the draw buffer.
         * \param srcRGB Specifies the source RGB blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param dstRGB Specifies the destination RGB blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param srcAlpha Specifies the source alpha blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param dstAlpha Specifies the destination alpha blend function.
         * Accepted values are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
         * GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
         * GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA,
         * GL_SRC_ALPHA_SATURATE, GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlendFuncSeparatei(
            GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char* caller = nullptr)
            const;

        /**
         * \brief The glDeleteTransformFeedbacks function deletes named transform feedback objects.
         *
         * \param n Specifies the number of transform feedback objects to be deleted.
         * \param ids Specifies an array of transform feedback objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glDrawArraysIndirect function renders primitives from array data, taking parameters from memory.
         * \deprecated Deprecated in OpenGL 4.6. Use glMultiDrawArraysIndirect instead.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param indirect Specifies a pointer to the location where the parameters are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawArraysIndirect(GLenum mode, const GLvoid* indirect, const char* caller = nullptr) const;

        /**
         * \brief The glDrawElementsIndirect function renders indexed primitives from array data, taking parameters
         * from memory.
         * \deprecated Deprecated in OpenGL 4.6. Use glMultiDrawElementsIndirect instead.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param type Specifies the type of the values in the index array.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT.
         * \param indirect Specifies a pointer to the location where the parameters are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawElementsIndirect(
            GLenum mode, GLenum type, const GLvoid* indirect, const char* caller = nullptr) const;

        /**
         * \brief The glDrawTransformFeedback function renders primitives using a transform feedback object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param id Specifies the name of the transform feedback object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawTransformFeedback(GLenum mode, GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glDrawTransformFeedbackStream function renders primitives using a specific stream from a
         * transform feedback object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param id Specifies the name of the transform feedback object.
         * \param stream Specifies the index of the stream to use.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream, const char* caller = nullptr) const;

        /**
         * \brief The glEndQueryIndexed function ends a query object on an indexed target.
         *
         * \param target Specifies the target type of query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
         * GL_TIME_ELAPSED.
         * \param index Specifies the index of the query object target.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEndQueryIndexed(GLenum target, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glGenTransformFeedbacks function generates transform feedback object names.
         *
         * \param n Specifies the number of transform feedback object names to generate.
         * \param ids Specifies an array in which the generated transform feedback object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenTransformFeedbacks(GLsizei n, GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveSubroutineName function retrieves the name of an active subroutine.
         *
         * \param program Specifies the name of the program containing the subroutine.
         * \param shadertype Specifies the shader stage from which to query the subroutine.
         * \param index Specifies the index of the subroutine.
         * \param bufSize Specifies the size of the buffer to receive the subroutine name.
         * \param length Specifies a pointer to the length of the subroutine name.
         * \param name Specifies a pointer to the buffer to receive the subroutine name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveSubroutineName(
            GLuint program,
            GLenum shadertype,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetActiveSubroutineUniformiv function retrieves the value of a subroutine uniform parameter.
         *
         * \param program Specifies the name of the program containing the subroutine uniform.
         * \param shadertype Specifies the shader stage from which to query the subroutine uniform.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param index Specifies the index of the subroutine uniform.
         * \param pname Specifies the symbolic name of the subroutine uniform parameter.
         * Accepted values are GL_NUM_COMPATIBLE_SUBROUTINES, GL_COMPATIBLE_SUBROUTINES,
         * GL_UNIFORM_SIZE, GL_UNIFORM_NAME_LENGTH.
         * \param values Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveSubroutineUniformiv(
            GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values, const char* caller = nullptr)
            const;

        /**
         * \brief The glGetActiveSubroutineUniformName function retrieves the name of a subroutine uniform.
         *
         * \param program Specifies the name of the program containing the subroutine uniform.
         * \param shadertype Specifies the shader stage from which to query the subroutine uniform.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param index Specifies the index of the subroutine uniform.
         * \param bufSize Specifies the size of the buffer to receive the subroutine uniform name.
         * \param length Specifies a pointer to the length of the subroutine uniform name.
         * \param name Specifies a pointer to the buffer to receive the subroutine uniform name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetActiveSubroutineUniformName(
            GLuint program,
            GLenum shadertype,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramStageiv function retrieves information about a program object stage.
         *
         * \param program Specifies the name of the program object.
         * \param shadertype Specifies the shader stage from which to query information.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param pname Specifies the symbolic name of the parameter to query.
         * Accepted values are GL_ACTIVE_SUBROUTINES, GL_ACTIVE_SUBROUTINE_UNIFORMS,
         * GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, GL_ACTIVE_SUBROUTINE_MAX_LENGTH,
         * GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH.
         * \param values Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramStageiv(
            GLuint program, GLenum shadertype, GLenum pname, GLint* values, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryIndexediv function retrieves parameters of a query object target.
         *
         * \param target Specifies the target type of query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
         * GL_TIME_ELAPSED.
         * \param index Specifies the index of the query object target.
         * \param pname Specifies the symbolic name of the query object parameter.
         * Accepted values are GL_CURRENT_QUERY, GL_QUERY_COUNTER_BITS.
         * \param params Specifies a pointer to the variable to receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryIndexediv(
            GLenum target, GLuint index, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSubroutineIndex function retrieves the index of a subroutine.
         *
         * \param program Specifies the name of the program containing the subroutine.
         * \param shadertype Specifies the shader stage from which to query the subroutine.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param name Specifies the name of the subroutine.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The index of the subroutine.
         */
        GLuint glGetSubroutineIndex(
            GLuint program, GLenum shadertype, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetSubroutineUniformLocation function retrieves the location of a subroutine uniform.
         *
         * \param program Specifies the name of the program containing the subroutine uniform.
         * \param shadertype Specifies the shader stage from which to query the subroutine uniform.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param name Specifies the name of the subroutine uniform.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The location of the subroutine uniform.
         */
        GLint glGetSubroutineUniformLocation(
            GLuint program, GLenum shadertype, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformdv function retrieves the double value of a uniform variable.
         *
         * \param program Specifies the name of the program containing the uniform variable.
         * \param location Specifies the location of the uniform variable.
         * \param params Specifies a pointer to the variable to receive the value of the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformdv(GLuint program, GLint location, GLdouble* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformSubroutineuiv function retrieves the value of a subroutine uniform for a shader
         * stage.
         *
         * \param shadertype Specifies the shader stage from which to query the subroutine uniform.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param location Specifies the location of the subroutine uniform.
         * \param params Specifies a pointer to the variable to receive the value of the subroutine uniform.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformSubroutineuiv(
            GLenum shadertype, GLint location, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glIsTransformFeedback function determines if a name corresponds to a transform feedback object.
         *
         * \param id Specifies a value that may be the name of a transform feedback object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if id is a transform feedback object, GL_FALSE otherwise.
         */
        GLboolean glIsTransformFeedback(GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glMinSampleShading function specifies the minimum rate at which sample shading takes place.
         *
         * \param value Specifies the minimum rate at which sample shading takes place.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMinSampleShading(GLfloat value, const char* caller = nullptr) const;

        /**
         * \brief The glPatchParameterfv function specifies the float value of a patch parameter.
         *
         * \param pname Specifies the symbolic name of the patch parameter.
         * Accepted values are GL_PATCH_VERTICES, GL_PATCH_DEFAULT_INNER_LEVEL,
         * GL_PATCH_DEFAULT_OUTER_LEVEL.
         * \param values Specifies a pointer to the value of the patch parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPatchParameterfv(GLenum pname, const GLfloat* values, const char* caller = nullptr) const;

        /**
         * \brief The glPatchParameteri function specifies the integer value of a patch parameter.
         *
         * \param pname Specifies the symbolic name of the patch parameter.
         * Accepted values are GL_PATCH_VERTICES, GL_PATCH_DEFAULT_INNER_LEVEL,
         * GL_PATCH_DEFAULT_OUTER_LEVEL.
         * \param value Specifies the value of the patch parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPatchParameteri(GLenum pname, GLint value, const char* caller = nullptr) const;

        /**
         * \brief The glPauseTransformFeedback function pauses transform feedback operations.
         * \deprecated Deprecated in OpenGL 4.6. Use glPauseTransformFeedbackEXT instead.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPauseTransformFeedback(const char* caller = nullptr) const;

        /**
         * \brief The glResumeTransformFeedback function resumes transform feedback operations.
         * \deprecated Deprecated in OpenGL 4.6. Use glResumeTransformFeedbackEXT instead.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glResumeTransformFeedback(const char* caller = nullptr) const;

        /**
         * \brief The glUniform1d function specifies the value of a double uniform variable for the current program
         * object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param x Specifies the new value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1d(GLint location, GLdouble x, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1dv function specifies the value of a double uniform variable array for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1dv(GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2d function specifies the value of a vec2 double uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param x Specifies the new x value to be used for the specified uniform variable.
         * \param y Specifies the new y value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2d(GLint location, GLdouble x, GLdouble y, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2dv function specifies the value of a vec2 double uniform variable array for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2dv(GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3d function specifies the value of a vec3 double uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param x Specifies the new x value to be used for the specified uniform variable.
         * \param y Specifies the new y value to be used for the specified uniform variable.
         * \param z Specifies the new z value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3dv function specifies the value of a vec3 double uniform variable array for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3dv(GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4d function specifies the value of a vec4 double uniform variable for the current
         * program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param x Specifies the new x value to be used for the specified uniform variable.
         * \param y Specifies the new y value to be used for the specified uniform variable.
         * \param z Specifies the new z value to be used for the specified uniform variable.
         * \param w Specifies the new w value to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4d(
            GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4dv function specifies the value of a vec4 double uniform variable array for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4dv(GLint location, GLsizei count, const GLdouble* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix2dv function specifies the value of a 2x2 double matrix uniform variable for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix2x3dv function specifies the value of a 2x3 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2x3dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix2x4dv function specifies the value of a 2x4 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix2x4dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3dv function specifies the value of a 3x3 double matrix uniform variable for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3x2dv function specifies the value of a 3x2 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3x2dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix3x4dv function specifies the value of a 3x4 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix3x4dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4dv function specifies the value of a 4x4 double matrix uniform variable for the
         * current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4x2dv function specifies the value of a 4x2 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4x2dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformMatrix4x3dv function specifies the value of a 4x3 double matrix uniform variable for
         * the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of matrices that are to be modified.
         * \param transpose Specifies whether to transpose the matrix as the values are loaded into the uniform
         * variable.
         * \param value Specifies a pointer to an array of values to be used for the specified uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformMatrix4x3dv(
            GLint location,
            GLsizei count,
            GLboolean transpose,
            const GLdouble* value,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniformSubroutinesuiv function loads subroutine uniform variables for a shader stage.
         * \deprecated Deprecated in OpenGL 4.6. Use glUniformSubroutinesuivEXT instead.
         *
         * \param shadertype Specifies the shader stage for which to load the subroutine uniform variables.
         * Accepted values are GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
         * \param count Specifies the number of subroutine uniform variables to load.
         * \param indices Specifies a pointer to an array of subroutine indices.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniformSubroutinesuiv(
            GLenum shadertype, GLsizei count, const GLuint* indices, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
