#pragma once

/**
 * \file Functions_3_3.h
 * \brief Declares the OpenGL 3.3 function wrapper interface.
 */

#include "Functions_3_2.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_3_3
     * \brief Exposes the OpenGL 3.3 function set.
     */
    class Functions_3_3 : public Functions_3_2
    {
        static inline bool s_loaded;

    public:
        explicit Functions_3_3();
        Functions_3_3(const Functions_3_3&) = delete;
        Functions_3_3& operator=(const Functions_3_3&) = delete;
        Functions_3_3(Functions_3_3&&) = delete;
        Functions_3_3& operator=(Functions_3_3&&) = delete;
        virtual ~Functions_3_3();

    protected:
        bool initialize();

    public:
        /**
         * \brief The glBindFragDataLocationIndexed function binds a user-defined varying out variable to a fragment
         * shader color number and index.
         *
         * \param program Specifies the name of the program containing varying out variable whose binding to
         * modify.
         * \param colorNumber Specifies the color number to bind the user-defined varying out variable to.
         * Accepted values are non-negative integers.
         * \param index Specifies the index of the color input to bind the user-defined varying out variable to.
         * Accepted values are non-negative integers.
         * \param name Specifies the name of the user-defined varying out variable whose binding to modify.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindFragDataLocationIndexed(
            GLuint program, GLuint colorNumber, GLuint index, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glBindSampler function binds a sampler to a texture unit.
         *
         * \param unit Specifies the index of the texture unit to which the sampler is bound.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param sampler Specifies the name of the sampler object to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindSampler(GLuint unit, GLuint sampler, const char* caller = nullptr) const;

        /**
         * \brief The glColorP3ui function specifies a packed pixel color for the current color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies the packed pixel color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorP3ui(GLenum type, GLuint color, const char* caller = nullptr) const;

        /**
         * \brief The glColorP3uiv function specifies a packed pixel color for the current color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies a pointer to the packed pixel color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorP3uiv(GLenum type, const GLuint* color, const char* caller = nullptr) const;

        /**
         * \brief The glColorP4ui function specifies a packed pixel color for the current color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies the packed pixel color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorP4ui(GLenum type, GLuint color, const char* caller = nullptr) const;

        /**
         * \brief The glColorP4uiv function specifies a packed pixel color for the current color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies a pointer to the packed pixel color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorP4uiv(GLenum type, const GLuint* color, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteSamplers function deletes named sampler objects.
         *
         * \param count Specifies the number of sampler objects to be deleted.
         * Accepted values are non-negative integers.
         * \param samplers Specifies an array of sampler objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteSamplers(GLsizei count, const GLuint* samplers, const char* caller = nullptr) const;

        /**
         * \brief The glGenSamplers function generates sampler object names.
         *
         * \param count Specifies the number of sampler object names to generate.
         * Accepted values are non-negative integers.
         * \param samplers Specifies an array in which the generated sampler object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenSamplers(GLsizei count, GLuint* samplers, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryObjecti64v function returns the 64-bit integer value of a query object parameter.
         *
         * \param id Specifies the name of a query object.
         * \param pname Specifies the symbolic name of a query object parameter.
         * Accepted values are GL_QUERY_RESULT and GL_QUERY_RESULT_AVAILABLE.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryObjectui64v function returns the 64-bit unsigned integer value of a query object
         * parameter.
         *
         * \param id Specifies the name of a query object.
         * \param pname Specifies the symbolic name of a query object parameter.
         * Accepted values are GL_QUERY_RESULT and GL_QUERY_RESULT_AVAILABLE.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSamplerParameterfv function returns the float value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, and GL_TEXTURE_COMPARE_FUNC.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSamplerParameterfv(
            GLuint sampler, GLenum pname, GLfloat* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSamplerParameterIiv function returns the integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, and GL_TEXTURE_COMPARE_FUNC.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSamplerParameterIiv(
            GLuint sampler, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSamplerParameterIuiv function returns the unsigned integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, and GL_TEXTURE_COMPARE_FUNC.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSamplerParameterIuiv(
            GLuint sampler, GLenum pname, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetSamplerParameteriv function returns the integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, and GL_TEXTURE_COMPARE_FUNC.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glIsSampler function determines if a name corresponds to a sampler object.
         *
         * \param sampler Specifies a value that may be the name of a sampler object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if sampler is a sampler object, GL_FALSE otherwise.
         */
        GLboolean glIsSampler(GLuint sampler, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP1ui function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP1uiv function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies a pointer to the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP1uiv(
            GLenum texture, GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP2ui function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP2uiv function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies a pointer to the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP2uiv(
            GLenum texture, GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP3ui function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP3uiv function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies a pointer to the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP3uiv(
            GLenum texture, GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP4ui function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glMultiTexCoordP4uiv function specifies a packed pixel coordinate for a multi-texture unit.
         *
         * \param texture Specifies the texture unit.
         * Accepted values are GL_TEXTURE0, GL_TEXTURE1, ..., GL_TEXTURE31.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param coords Specifies a pointer to the packed pixel coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiTexCoordP4uiv(
            GLenum texture, GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glNormalP3ui function specifies a packed pixel normal vector.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies the packed pixel normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormalP3ui(GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glNormalP3uiv function specifies a packed pixel normal vector.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies a pointer to the packed pixel normal vector.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glNormalP3uiv(GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glQueryCounter function records the GL time into a query object after all previous commands have
         * reached the GL server.
         *
         * \param id Specifies the name of a query object into which to record the GL time.
         * \param target Specifies the target type of query object.
         * Accepted values are GL_TIMESTAMP.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glQueryCounter(GLuint id, GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameterf function sets the float value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameterfv function sets the float value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies a pointer to the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameterfv(
            GLuint sampler, GLenum pname, const GLfloat* param, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameteri function sets the integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameteri(GLuint sampler, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameterIiv function sets the integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies a pointer to the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameterIiv(
            GLuint sampler, GLenum pname, const GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameterIuiv function sets the unsigned integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies a pointer to the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameterIuiv(
            GLuint sampler, GLenum pname, const GLuint* param, const char* caller = nullptr) const;

        /**
         * \brief The glSamplerParameteriv function sets the integer value of a sampler parameter.
         *
         * \param sampler Specifies the name of the sampler object.
         * \param pname Specifies the symbolic name of a sampler parameter.
         * Accepted values are GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R,
         * GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_LOD_BIAS.
         * \param param Specifies a pointer to the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSamplerParameteriv(
            GLuint sampler, GLenum pname, const GLint* param, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColorP3ui function specifies a packed pixel secondary color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies the packed pixel secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColorP3ui(GLenum type, GLuint color, const char* caller = nullptr) const;

        /**
         * \brief The glSecondaryColorP3uiv function specifies a packed pixel secondary color.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_SHORT_4_4_4_4,
         * GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_10_10_10_2.
         * \param color Specifies a pointer to the packed pixel secondary color.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glSecondaryColorP3uiv(GLenum type, const GLuint* color, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP1ui function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP1ui(GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP1uiv function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies a pointer to the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP1uiv(GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP2ui function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP2ui(GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP2uiv function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies a pointer to the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP2uiv(GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP3ui function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP3ui(GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP3uiv function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies a pointer to the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP3uiv(GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP4ui function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP4ui(GLenum type, GLuint coords, const char* caller = nullptr) const;

        /**
         * \brief The glTexCoordP4uiv function specifies a packed pixel texture coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param coords Specifies a pointer to the packed pixel texture coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexCoordP4uiv(GLenum type, const GLuint* coords, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribDivisor function modifies the rate at which generic vertex attributes advance
         * during instanced rendering.
         * \deprecated Deprecated in OpenGL 4.5. Use glVertexAttribDivisorARB instead.
         *
         * \param index Specifies the index of the generic vertex attribute.
         * \param divisor Specifies the number of instances that will pass between updates of the generic attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribDivisor(GLuint index, GLuint divisor, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP1ui function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies the packed pixel value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP1ui(
            GLuint index, GLenum type, GLboolean normalized, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP1uiv function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies a pointer to the packed pixel value to be used for the generic vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP1uiv(
            GLuint index, GLenum type, GLboolean normalized, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP2ui function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies the packed pixel value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP2ui(
            GLuint index, GLenum type, GLboolean normalized, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP2uiv function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies a pointer to the packed pixel value to be used for the generic vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP2uiv(
            GLuint index, GLenum type, GLboolean normalized, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP3ui function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies the packed pixel value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP3ui(
            GLuint index, GLenum type, GLboolean normalized, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP3uiv function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies a pointer to the packed pixel value to be used for the generic vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP3uiv(
            GLuint index, GLenum type, GLboolean normalized, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP4ui function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies the packed pixel value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP4ui(
            GLuint index, GLenum type, GLboolean normalized, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribP4uiv function specifies a packed pixel value for a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized or converted directly as
         * fixed-point values when they are accessed.
         * \param value Specifies a pointer to the packed pixel value to be used for the generic vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribP4uiv(
            GLuint index, GLenum type, GLboolean normalized, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP2ui function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP2ui(GLenum type, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP2uiv function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies a pointer to the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP2uiv(GLenum type, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP3ui function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP3ui(GLenum type, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP3uiv function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies a pointer to the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP3uiv(GLenum type, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP4ui function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP4ui(GLenum type, GLuint value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexP4uiv function specifies a packed pixel vertex coordinate.
         *
         * \param type Specifies the type of packed pixel data.
         * Accepted values are GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
         * GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV.
         * \param value Specifies a pointer to the packed pixel vertex coordinate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexP4uiv(GLenum type, const GLuint* value, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
