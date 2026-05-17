#pragma once

/**
 * \file Functions_4_3.h
 * \brief Declares the OpenGL 4.3 function wrapper interface.
 */

#include "Functions_4_2.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_4_3
     * \brief Exposes the OpenGL 4.3 function set.
     */
    class Functions_4_3 : public Functions_4_2
    {
        static inline bool s_loaded;

    public:
        explicit Functions_4_3();
        Functions_4_3(const Functions_4_3&) = delete;
        Functions_4_3& operator=(const Functions_4_3&) = delete;
        Functions_4_3(Functions_4_3&&) = delete;
        Functions_4_3& operator=(Functions_4_3&&) = delete;
        virtual ~Functions_4_3();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBindVertexBuffer function binds a buffer to a vertex buffer binding point.
         *
         * \param bindingindex Specifies the index of the vertex buffer binding point to which to bind the buffer.
         * \param buffer Specifies the name of the buffer to bind.
         * \param offset Specifies the offset of the first element of the buffer.
         * \param stride Specifies the distance between elements within the buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindVertexBuffer(
            GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferData function fills a buffer object's data store with a fixed value.
         *
         * \param target Specifies the target buffer object.
         *  Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         *  GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER,
         *  GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER,
         *  GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param internalformat Specifies the internal format of the data in the buffer object.
         * \param format Specifies the format of the data in the buffer object.
         *  Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL.
         * \param type  Specifies the type of the data in the buffer object.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         *  GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         *  GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         *  GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         *  GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         *  GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data  Specifies a pointer to the data to be used to clear the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferData(
            GLenum target,
            GLenum internalformat,
            GLenum format,
            GLenum type,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferSubData function fills a subregion of a buffer object's data store with a fixed
         * value.
         *
         * \param target Specifies the target buffer object.
         *  Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         *  GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER,
         *  GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER,
         *  GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param internalformat Specifies the internal format of the data in the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size  Specifies the size of the subregion to be filled.
         * \param format Specifies the format of the data in the buffer object.
         *  Accepted values are GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT,
         * GL_DEPTH_STENCIL.
         * \param type  Specifies the type of the data in the buffer object.
         *  Accepted values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT,
         *  GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
         *  GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
         *  GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
         *  GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
         *  GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV.
         * \param data  Specifies a pointer to the data to be used to clear the buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferSubData(
            GLenum target,
            GLenum internalformat,
            GLintptr offset,
            GLsizeiptr size,
            GLenum format,
            GLenum type,
            const GLvoid* data,
            const char* caller = nullptr) const;

        /**
         * \brief The glCopyImageSubData function copies a region of texel data from one image to another.
         *
         * \param srcName Specifies the name of the source image.
         * \param srcTarget Specifies the target of the source image.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_RECTANGLE,
         * GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_RENDERBUFFER.
         * \param srcLevel Specifies the level of the source image.
         * \param srcX Specifies the x coordinate of the source region.
         * \param srcY Specifies the y coordinate of the source region.
         * \param srcZ Specifies the z coordinate of the source region.
         * \param dstName Specifies the name of the destination image.
         * \param dstTarget Specifies the target of the destination image.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_RECTANGLE,
         * GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_RENDERBUFFER.
         * \param dstLevel Specifies the level of the destination image.
         * \param dstX Specifies the x coordinate of the destination region.
         * \param dstY Specifies the y coordinate of the destination region.
         * \param dstZ Specifies the z coordinate of the destination region.
         * \param srcWidth Specifies the width of the region to be copied.
         * \param srcHeight Specifies the height of the region to be copied.
         * \param srcDepth Specifies the depth of the region to be copied.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glCopyImageSubData(
            GLuint srcName,
            GLenum srcTarget,
            GLint srcLevel,
            GLint srcX,
            GLint srcY,
            GLint srcZ,
            GLuint dstName,
            GLenum dstTarget,
            GLint dstLevel,
            GLint dstX,
            GLint dstY,
            GLint dstZ,
            GLsizei srcWidth,
            GLsizei srcHeight,
            GLsizei srcDepth,
            const char* caller = nullptr) const;

        /**
         * \brief The glDebugMessageCallback function specifies a callback to receive debugging messages from the GL.
         * \deprecated Deprecated in OpenGL 4.6. Use glDebugMessageCallbackKHR instead.
         *
         * \param callback Specifies the callback function that will be called when a debug message is generated.
         * \param userParam Specifies a pointer to user-supplied data that will be passed to the callback function.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDebugMessageCallback(
            GLDEBUGPROC callback, const GLvoid* userParam, const char* caller = nullptr) const;

        /**
         * \brief The glDebugMessageControl function controls the reporting of debug messages.
         * \deprecated Deprecated in OpenGL 4.6. Use glDebugMessageControlKHR instead.
         *
         * \param source Specifies the source of debug messages to enable or disable.
         * Accepted values are GL_DEBUG_SOURCE_API, GL_DEBUG_SOURCE_WINDOW_SYSTEM,
         * GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_SOURCE_APPLICATION,
         * GL_DEBUG_SOURCE_OTHER.
         * \param type Specifies the type of debug messages to enable or disable.
         * Accepted values are GL_DEBUG_TYPE_ERROR, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
         * GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, GL_DEBUG_TYPE_PORTABILITY, GL_DEBUG_TYPE_PERFORMANCE, GL_DEBUG_TYPE_MARKER,
         * GL_DEBUG_TYPE_PUSH_GROUP, GL_DEBUG_TYPE_POP_GROUP, GL_DEBUG_TYPE_OTHER.
         * \param severity Specifies the severity of debug messages to enable or disable.
         * Accepted values are GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM, GL_DEBUG_SEVERITY_LOW,
         * GL_DEBUG_SEVERITY_NOTIFICATION.
         * \param count Specifies the number of elements in the ids array.
         * \param ids Specifies an array of unsigned integers containing the ids of the messages to enable or
         * disable.
         * \param enabled Specifies whether the selected messages should be enabled or disabled.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDebugMessageControl(
            GLenum source,
            GLenum type,
            GLenum severity,
            GLsizei count,
            const GLuint* ids,
            GLboolean enabled,
            const char* caller = nullptr) const;

        /**
         * \brief The glDebugMessageInsert function inserts a debug message into the debug output queue.
         * \deprecated Deprecated in OpenGL 4.6. Use glDebugMessageInsertKHR instead.
         *
         * \param source Specifies the source of the debug message.
         * Accepted values are GL_DEBUG_SOURCE_API, GL_DEBUG_SOURCE_WINDOW_SYSTEM,
         * GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_SOURCE_APPLICATION,
         * GL_DEBUG_SOURCE_OTHER.
         * \param type Specifies the type of the debug message.
         * Accepted values are GL_DEBUG_TYPE_ERROR, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
         * GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, GL_DEBUG_TYPE_PORTABILITY, GL_DEBUG_TYPE_PERFORMANCE, GL_DEBUG_TYPE_MARKER,
         * GL_DEBUG_TYPE_PUSH_GROUP, GL_DEBUG_TYPE_POP_GROUP, GL_DEBUG_TYPE_OTHER.
         * \param id Specifies the id of the debug message.
         * \param severity Specifies the severity of the debug message.
         * Accepted values are GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM, GL_DEBUG_SEVERITY_LOW,
         * GL_DEBUG_SEVERITY_NOTIFICATION.
         * \param length Specifies the length of the debug message.
         * \param buf Specifies a pointer to the debug message string.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDebugMessageInsert(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* buf,
            const char* caller = nullptr) const;

        /**
         * \brief The glDispatchCompute function launches one or more compute work groups.
         *
         * \param num_groups_x Specifies the number of work groups to be launched in the x dimension.
         * \param num_groups_y Specifies the number of work groups to be launched in the y dimension.
         * \param num_groups_z Specifies the number of work groups to be launched in the z dimension.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDispatchCompute(
            GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, const char* caller = nullptr) const;

        /**
         * \brief The glDispatchComputeIndirect function launches one or more compute work groups using parameters
         * stored in a buffer.
         *
         * \param indirect Specifies the offset into the buffer object currently bound to GL_DISPATCH_INDIRECT_BUFFER
         * where the parameters are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDispatchComputeIndirect(GLintptr indirect, const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferParameteri function sets a named parameter of a framebuffer object.
         *
         * \param target Specifies the target of the framebuffer object.
         * Accepted values are GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER.
         * \param pname Specifies the parameter to be set.
         * Accepted values are GL_FRAMEBUFFER_DEFAULT_WIDTH, GL_FRAMEBUFFER_DEFAULT_HEIGHT,
         * GL_FRAMEBUFFER_DEFAULT_LAYERS, GL_FRAMEBUFFER_DEFAULT_SAMPLES,
         * GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS.
         * \param param Specifies the value to set the parameter to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferParameteri(GLenum target, GLenum pname, GLint param, const char* caller = nullptr) const;

        /**
         * \brief The glGetDebugMessageLog function retrieves messages from the debug message log.
         * \deprecated Deprecated in OpenGL 4.6. Use glGetDebugMessageLogKHR instead.
         *
         * \param count Specifies the number of debug messages to retrieve.
         * \param bufSize Specifies the size of the buffer to receive the messages.
         * \param sources Specifies an array to receive the sources of the messages.
         * Accepted values are GL_DEBUG_SOURCE_API, GL_DEBUG_SOURCE_WINDOW_SYSTEM,
         * GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_SOURCE_APPLICATION,
         * GL_DEBUG_SOURCE_OTHER.
         * \param types Specifies an array to receive the types of the messages.
         * Accepted values are GL_DEBUG_TYPE_ERROR, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
         * GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, GL_DEBUG_TYPE_PORTABILITY, GL_DEBUG_TYPE_PERFORMANCE, GL_DEBUG_TYPE_MARKER,
         * GL_DEBUG_TYPE_PUSH_GROUP, GL_DEBUG_TYPE_POP_GROUP, GL_DEBUG_TYPE_OTHER.
         * \param ids Specifies an array to receive the ids of the messages.
         * \param severities Specifies an array to receive the severities of the messages.
         * Accepted values are GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM,
         * GL_DEBUG_SEVERITY_LOW, GL_DEBUG_SEVERITY_NOTIFICATION.
         * \param lengths Specifies an array to receive the lengths of the messages.
         * \param messageLog Specifies a buffer to receive the messages.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The number of debug messages retrieved.
         */
        GLuint glGetDebugMessageLog(
            GLuint count,
            GLsizei bufSize,
            GLenum* sources,
            GLenum* types,
            GLuint* ids,
            GLenum* severities,
            GLsizei* lengths,
            GLchar* messageLog,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetFramebufferParameteriv function retrieves a parameter from a framebuffer object.
         *
         * \param target Specifies the target of the framebuffer object.
         * Accepted values are GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER.
         * \param pname Specifies the parameter to be retrieved.
         * Accepted values are GL_FRAMEBUFFER_DEFAULT_WIDTH, GL_FRAMEBUFFER_DEFAULT_HEIGHT,
         * GL_FRAMEBUFFER_DEFAULT_LAYERS, GL_FRAMEBUFFER_DEFAULT_SAMPLES,
         * GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetFramebufferParameteriv(
            GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetInternalformati64v function retrieves information about implementation-dependent support
         * for internal formats.
         *
         * \param target Specifies the target renderbuffer or texture.
         *  Accepted values are GL_RENDERBUFFER, GL_TEXTURE_1D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY,
         *  GL_TEXTURE_RECTANGLE, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE,
         * GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param internalformat Specifies the internal format about which to retrieve information.
         * \param pname  Specifies the type of information to query.
         *  Accepted values are GL_SAMPLES, GL_NUM_SAMPLE_COUNTS.
         * \param count  Specifies the size of the buffer whose address is given in params.
         * \param params Specifies the address of a buffer into which the query result will be placed.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetInternalformati64v(
            GLenum target,
            GLenum internalformat,
            GLenum pname,
            GLsizei count,
            GLint64* params,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetObjectLabel function retrieves the label of a named object.
         *
         * \param identifier Specifies the type of the object.
         * Accepted values are GL_BUFFER, GL_SHADER, GL_PROGRAM, GL_VERTEX_ARRAY, GL_QUERY,
         * GL_PROGRAM_PIPELINE, GL_TRANSFORM_FEEDBACK, GL_SAMPLER, GL_FRAMEBUFFER, GL_RENDERBUFFER, GL_TEXTURE.
         * \param name Specifies the name of the object.
         * \param bufSize Specifies the size of the buffer to receive the label.
         * \param length Specifies a pointer to the variable to receive the length of the label.
         * \param label Specifies a buffer to receive the label.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetObjectLabel(
            GLenum identifier,
            GLuint name,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* label,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetObjectPtrLabel function retrieves the label of a sync object.
         *
         * \param ptr Specifies a pointer to the sync object.
         * \param bufSize Specifies the size of the buffer to receive the label.
         * \param length Specifies a pointer to the variable to receive the length of the label.
         * \param label Specifies a buffer to receive the label.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetObjectPtrLabel(
            const GLvoid* ptr, GLsizei bufSize, GLsizei* length, GLchar* label, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramInterfaceiv function retrieves information about a program interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_UNIFORM_BLOCK, GL_PROGRAM_INPUT,
         * GL_PROGRAM_OUTPUT, GL_BUFFER_VARIABLE, GL_SHADER_STORAGE_BLOCK, GL_VERTEX_SUBROUTINE,
         *  GL_TESS_CONTROL_SUBROUTINE, GL_TESS_EVALUATION_SUBROUTINE, GL_GEOMETRY_SUBROUTINE,
         * GL_FRAGMENT_SUBROUTINE, GL_COMPUTE_SUBROUTINE, GL_VERTEX_SUBROUTINE_UNIFORM,
         *  GL_TESS_CONTROL_SUBROUTINE_UNIFORM, GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
         * GL_GEOMETRY_SUBROUTINE_UNIFORM, GL_FRAGMENT_SUBROUTINE_UNIFORM, GL_COMPUTE_SUBROUTINE_UNIFORM,
         * GL_TRANSFORM_FEEDBACK_VARYING, GL_ATOMIC_COUNTER_BUFFER.
         * \param pname  Specifies the parameter to be retrieved.
         *  Accepted values are GL_ACTIVE_RESOURCES, GL_MAX_NAME_LENGTH,
         * GL_MAX_NUM_ACTIVE_VARIABLES, GL_MAX_NUM_COMPATIBLE_SUBROUTINES.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramInterfaceiv(
            GLuint program, GLenum programInterface, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramResourceIndex function retrieves the index of a named resource within a program
         * interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_UNIFORM_BLOCK, GL_PROGRAM_INPUT,
         * GL_PROGRAM_OUTPUT, GL_BUFFER_VARIABLE, GL_SHADER_STORAGE_BLOCK, GL_VERTEX_SUBROUTINE,
         *  GL_TESS_CONTROL_SUBROUTINE, GL_TESS_EVALUATION_SUBROUTINE, GL_GEOMETRY_SUBROUTINE,
         * GL_FRAGMENT_SUBROUTINE, GL_COMPUTE_SUBROUTINE, GL_VERTEX_SUBROUTINE_UNIFORM,
         *  GL_TESS_CONTROL_SUBROUTINE_UNIFORM, GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
         * GL_GEOMETRY_SUBROUTINE_UNIFORM, GL_FRAGMENT_SUBROUTINE_UNIFORM, GL_COMPUTE_SUBROUTINE_UNIFORM,
         *  GL_TRANSFORM_FEEDBACK_VARYING, GL_ATOMIC_COUNTER_BUFFER.
         * \param name  Specifies the name of the resource.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The index of the named resource within the program interface.
         */
        GLuint glGetProgramResourceIndex(
            GLuint program, GLenum programInterface, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramResourceiv function retrieves information about a resource within a program
         * interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_UNIFORM_BLOCK, GL_PROGRAM_INPUT,
         * GL_PROGRAM_OUTPUT, GL_BUFFER_VARIABLE, GL_SHADER_STORAGE_BLOCK, GL_VERTEX_SUBROUTINE,
         *  GL_TESS_CONTROL_SUBROUTINE, GL_TESS_EVALUATION_SUBROUTINE, GL_GEOMETRY_SUBROUTINE,
         * GL_FRAGMENT_SUBROUTINE, GL_COMPUTE_SUBROUTINE, GL_VERTEX_SUBROUTINE_UNIFORM,
         *  GL_TESS_CONTROL_SUBROUTINE_UNIFORM, GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
         * GL_GEOMETRY_SUBROUTINE_UNIFORM, GL_FRAGMENT_SUBROUTINE_UNIFORM, GL_COMPUTE_SUBROUTINE_UNIFORM,
         *  GL_TRANSFORM_FEEDBACK_VARYING, GL_ATOMIC_COUNTER_BUFFER.
         * \param index  Specifies the index of the resource within the program interface.
         * \param propCount Specifies the number of properties to query.
         * \param props  Specifies an array of properties to query.
         * \param count  Specifies the size of the buffer whose address is given in params.
         * \param length Specifies a pointer to the variable to receive the length of the query result.
         * \param params Specifies a pointer to the buffer to receive the query result.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramResourceiv(
            GLuint program,
            GLenum programInterface,
            GLuint index,
            GLsizei propCount,
            const GLenum* props,
            GLsizei count,
            GLsizei* length,
            GLint* params,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramResourceLocation function retrieves the location of a named resource within a
         * program interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_PROGRAM_INPUT, GL_PROGRAM_OUTPUT,
         * GL_TRANSFORM_FEEDBACK_VARYING.
         * \param name  Specifies the name of the resource.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The location of the named resource within the program interface.
         */
        GLint glGetProgramResourceLocation(
            GLuint program, GLenum programInterface, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramResourceLocationIndex function retrieves the location index of a named resource
         * within a program interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_PROGRAM_INPUT, GL_PROGRAM_OUTPUT,
         * GL_TRANSFORM_FEEDBACK_VARYING.
         * \param name  Specifies the name of the resource.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The location index of the named resource within the program interface.
         */
        GLint glGetProgramResourceLocationIndex(
            GLuint program, GLenum programInterface, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetProgramResourceName function retrieves the name of a resource within a program interface.
         *
         * \param program Specifies the name of the program object.
         * \param programInterface Specifies the interface within the program object.
         *  Accepted values are GL_UNIFORM, GL_UNIFORM_BLOCK, GL_PROGRAM_INPUT,
         * GL_PROGRAM_OUTPUT, GL_BUFFER_VARIABLE, GL_SHADER_STORAGE_BLOCK, GL_VERTEX_SUBROUTINE,
         *  GL_TESS_CONTROL_SUBROUTINE, GL_TESS_EVALUATION_SUBROUTINE, GL_GEOMETRY_SUBROUTINE,
         * GL_FRAGMENT_SUBROUTINE, GL_COMPUTE_SUBROUTINE, GL_VERTEX_SUBROUTINE_UNIFORM,
         *  GL_TESS_CONTROL_SUBROUTINE_UNIFORM, GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
         * GL_GEOMETRY_SUBROUTINE_UNIFORM, GL_FRAGMENT_SUBROUTINE_UNIFORM, GL_COMPUTE_SUBROUTINE_UNIFORM,
         *  GL_TRANSFORM_FEEDBACK_VARYING, GL_ATOMIC_COUNTER_BUFFER.
         * \param index  Specifies the index of the resource within the program interface.
         * \param bufSize Specifies the size of the buffer to receive the name.
         * \param length Specifies a pointer to the variable to receive the length of the name.
         * \param name  Specifies a buffer to receive the name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetProgramResourceName(
            GLuint program,
            GLenum programInterface,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateBufferData function invalidates the content of a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object whose data store to invalidate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateBufferData(GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateBufferSubData function invalidates a subregion of a buffer object's data store.
         *
         * \param buffer Specifies the name of the buffer object whose data store to invalidate.
         * \param offset Specifies the offset within the buffer object.
         * \param length Specifies the length of the subregion to invalidate.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateBufferSubData(
            GLuint buffer, GLintptr offset, GLsizeiptr length, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateFramebuffer function invalidates the content of a framebuffer object's attachments.
         *
         * \param target Specifies the target of the framebuffer object.
         *  Accepted values are GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER.
         * \param numAttachments Specifies the number of attachments to invalidate.
         * \param attachments Specifies an array of attachments to invalidate.
         *  Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateFramebuffer(
            GLenum target, GLsizei numAttachments, const GLenum* attachments, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateSubFramebuffer function invalidates the content of a subregion of a framebuffer
         * object's attachments.
         *
         * \param target Specifies the target of the framebuffer object.
         *  Accepted values are GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER.
         * \param numAttachments Specifies the number of attachments to invalidate.
         * \param attachments Specifies an array of attachments to invalidate.
         *  Accepted values are GL_COLOR_ATTACHMENTi, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param x  Specifies the x coordinate of the subregion.
         * \param y  Specifies the y coordinate of the subregion.
         * \param width  Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateSubFramebuffer(
            GLenum target,
            GLsizei numAttachments,
            const GLenum* attachments,
            GLint x,
            GLint y,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateTexImage function invalidates the content of a texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateTexImage(GLuint texture, GLint level, const char* caller = nullptr) const;

        /**
         * \brief The glInvalidateTexSubImage function invalidates the content of a subregion of a texture image.
         *
         * \param texture Specifies the name of the texture object.
         * \param level Specifies the level of the texture object.
         * \param xoffset Specifies the x offset of the subregion.
         * \param yoffset Specifies the y offset of the subregion.
         * \param zoffset Specifies the z offset of the subregion.
         * \param width Specifies the width of the subregion.
         * \param height Specifies the height of the subregion.
         * \param depth Specifies the depth of the subregion.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glInvalidateTexSubImage(
            GLuint texture,
            GLint level,
            GLint xoffset,
            GLint yoffset,
            GLint zoffset,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawArraysIndirect function renders multiple sets of primitives from array data, with
         * parameters sourced from a buffer object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param indirect Specifies a pointer to the location where the parameters are stored.
         * \param drawcount Specifies the number of draws to execute.
         * \param stride Specifies the byte offset between consecutive sets of draw parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawArraysIndirect(
            GLenum mode, const GLvoid* indirect, GLsizei drawcount, GLsizei stride, const char* caller = nullptr) const;

        /**
         * \brief The glMultiDrawElementsIndirect function renders multiple sets of primitives by specifying indices
         * of array data elements, with parameters sourced from a buffer object.
         *
         * \param mode Specifies what kind of primitives to render.
         * Accepted values are GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
         * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES.
         * \param type Specifies the type of the values in the indices.
         * Accepted values are GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT.
         * \param indirect Specifies a pointer to the location where the parameters are stored.
         * \param drawcount Specifies the number of draws to execute.
         * \param stride Specifies the byte offset between consecutive sets of draw parameters.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glMultiDrawElementsIndirect(
            GLenum mode,
            GLenum type,
            const GLvoid* indirect,
            GLsizei drawcount,
            GLsizei stride,
            const char* caller = nullptr) const;

        /**
         * \brief The glObjectLabel function labels a named object identified within a namespace.
         *
         * \param identifier Specifies the namespace from which the name is allocated.
         * Accepted values are GL_BUFFER, GL_SHADER, GL_PROGRAM, GL_VERTEX_ARRAY, GL_QUERY,
         * GL_PROGRAM_PIPELINE, GL_TRANSFORM_FEEDBACK, GL_SAMPLER, GL_FRAMEBUFFER, GL_RENDERBUFFER, GL_TEXTURE.
         * \param name Specifies the name of the object to label.
         * \param length Specifies the length of the label.
         * \param label Specifies a pointer to the label string.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glObjectLabel(
            GLenum identifier, GLuint name, GLsizei length, const GLchar* label, const char* caller = nullptr) const;

        /**
         * \brief The glObjectPtrLabel function labels a sync object identified by a pointer.
         *
         * \param ptr Specifies a pointer to the sync object.
         * \param length Specifies the length of the label.
         * \param label Specifies a pointer to the label string.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glObjectPtrLabel(
            const GLvoid* ptr, GLsizei length, const GLchar* label, const char* caller = nullptr) const;

        /**
         * \brief The glPushDebugGroup function pushes a debug group onto the stack.
         * \deprecated Deprecated in OpenGL 4.6. Use glPushDebugGroupKHR instead.
         *
         * \param source Specifies the source of the debug message.
         * Accepted values are GL_DEBUG_SOURCE_API, GL_DEBUG_SOURCE_WINDOW_SYSTEM,
         * GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_SOURCE_APPLICATION,
         * GL_DEBUG_SOURCE_OTHER.
         * \param id Specifies the id of the debug message.
         * \param length Specifies the length of the debug message.
         * \param message Specifies a pointer to the debug message string.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPushDebugGroup(
            GLenum source, GLuint id, GLsizei length, const GLchar* message, const char* caller = nullptr) const;

        /**
         * \brief The glPopDebugGroup function pops the active debug group.
         * \deprecated Deprecated in OpenGL 4.6. Use glPopDebugGroupKHR instead.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glPopDebugGroup(const char* caller = nullptr) const;

        /**
         * \brief The glShaderStorageBlockBinding function assigns a binding point to an active shader storage block.
         *
         * \param program  Specifies the name of the program object.
         * \param storageBlockIndex Specifies the index of the shader storage block within the program object.
         * \param storageBlockBinding Specifies the binding point to which to bind the shader storage block.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glShaderStorageBlockBinding(
            GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding, const char* caller = nullptr) const;

        /**
         * \brief The glTexBufferRange function binds a range of a buffer object's data store to a buffer texture.
         *
         * \param target Specifies the target of the operation.
         *  Accepted values are GL_TEXTURE_BUFFER.
         * \param internalformat Specifies the internal format of the data in the buffer texture.
         * \param buffer Specifies the name of the buffer object.
         * \param offset Specifies the offset within the buffer object.
         * \param size  Specifies the size of the range to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexBufferRange(
            GLenum target,
            GLenum internalformat,
            GLuint buffer,
            GLintptr offset,
            GLsizeiptr size,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexStorage2DMultisample function specifies the storage requirements for a two-dimensional
         * multisample texture.
         *
         * \param target  Specifies the target of the operation.
         *  Accepted values are GL_TEXTURE_2D_MULTISAMPLE, GL_PROXY_TEXTURE_2D_MULTISAMPLE.
         * \param samples  Specifies the number of samples in the multisample texture.
         * \param internalformat Specifies the internal format of the data in the multisample texture.
         * \param width  Specifies the width of the multisample texture.
         * \param height  Specifies the height of the multisample texture.
         * \param fixedsamplelocations Specifies whether the sample locations are fixed.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTexStorage2DMultisample(
            GLenum target,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexStorage3DMultisample function specifies the storage requirements for a three-dimensional
         * multisample texture.
         *
         * \param target  Specifies the target of the operation.
         *  Accepted values are GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
         * GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param samples  Specifies the number of samples in the multisample texture.
         * \param internalformat Specifies the internal format of the data in the multisample texture.
         * \param width  Specifies the width of the multisample texture.
         * \param height  Specifies the height of the multisample texture.
         * \param depth  Specifies the depth of the multisample texture.
         * \param fixedsamplelocations Specifies whether the sample locations are fixed.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glTexStorage3DMultisample(
            GLenum target,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            GLsizei depth,
            GLboolean fixedsamplelocations,
            const char* caller = nullptr) const;

        /**
         * \brief The glTextureView function creates a view of an existing texture object.
         *
         * \param texture Specifies the name of the texture object to create the view for.
         * \param target Specifies the target of the view.
         *  Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D,
         * GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY,
         * GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param origtexture Specifies the name of the original texture object.
         * \param internalformat Specifies the internal format of the view.
         * \param minlevel Specifies the minimum level of the view.
         * \param numlevels Specifies the number of levels of the view.
         * \param minlayer Specifies the minimum layer of the view.
         * \param numlayers Specifies the number of layers of the view.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTextureView(
            GLuint texture,
            GLenum target,
            GLuint origtexture,
            GLenum internalformat,
            GLuint minlevel,
            GLuint numlevels,
            GLuint minlayer,
            GLuint numlayers,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribBinding function associates a vertex attribute with a vertex buffer binding point.
         *
         * \param attribindex Specifies the index of the vertex attribute to associate.
         * \param bindingindex Specifies the index of the vertex buffer binding point to associate with the vertex
         * attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribBinding(GLuint attribindex, GLuint bindingindex, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribFormat function specifies the organization of data in a vertex attribute array.
         *
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         *  Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT, GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV,
         * GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV.
         * \param normalized Specifies whether fixed-point data values should be normalized.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribFormat(
            GLuint attribindex,
            GLint size,
            GLenum type,
            GLboolean normalized,
            GLuint relativeoffset,
            const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribIFormat function specifies the organization of integer data in a vertex attribute
         * array.
         *
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         *  Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribIFormat(
            GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribLFormat function specifies the organization of double data in a vertex attribute
         * array.
         *
         * \param attribindex Specifies the index of the vertex attribute to configure.
         * \param size  Specifies the number of components per vertex attribute.
         * \param type  Specifies the data type of each component in the array.
         *  Accepted value is GL_DOUBLE.
         * \param relativeoffset Specifies the offset of the first component of the vertex attribute relative to the
         * start of the vertex buffer binding.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribLFormat(
            GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char* caller = nullptr) const;

        /**
         * \brief The glVertexBindingDivisor function modifies the rate at which generic vertex attributes advance
         * during instanced rendering.
         *
         * \param bindingindex Specifies the index of the binding whose divisor to modify.
         * \param divisor Specifies the number of instances that will pass between updates of the generic
         * attribute at slot bindingindex.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexBindingDivisor(GLuint bindingindex, GLuint divisor, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
