#pragma once

/**
 * \file Functions_1_5.h
 * \brief Declares the OpenGL 1.5 function wrapper interface.
 */

#include "Functions_1_4.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_1_5
     * \brief Exposes the OpenGL 1.5 function set.
     */
    class Functions_1_5 : public Functions_1_4
    {
        static inline bool s_loaded;

    public:
        explicit Functions_1_5();
        Functions_1_5(const Functions_1_5&) = delete;
        Functions_1_5& operator=(const Functions_1_5&) = delete;
        Functions_1_5(Functions_1_5&&) = delete;
        Functions_1_5& operator=(Functions_1_5&&) = delete;
        virtual ~Functions_1_5();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBeginQuery function creates a query object and begins a query operation.
         * \deprecated Deprecated in OpenGL 3.0. Use glBeginQueryIndexed instead.
         *
         * \param target Specifies the target type of query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN.
         * \param id Specifies the name of a query object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBeginQuery(GLenum target, GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glBindBuffer function binds a named buffer object.
         *
         * \param target Specifies the target to which the buffer object is bound.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param buffer Specifies the name of a buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindBuffer(GLenum target, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glBufferData function creates and initializes a buffer object's data store.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param size Specifies the size in bytes of the buffer object's new data store.
         * \param data Specifies a pointer to data that will be copied into the data store.
         * \param usage Specifies the expected usage pattern of the data store.
         * Accepted values are GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW,
         * GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBufferData(
            GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage, const char* caller = nullptr) const;

        /**
         * \brief The glBufferSubData function updates a subset of a buffer object's data store.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param offset Specifies the offset into the buffer object's data store where data replacement will begin.
         * \param size Specifies the size in bytes of the data store region being replaced.
         * \param data Specifies a pointer to the new data that will be copied into the data store.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBufferSubData(
            GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteBuffers function deletes named buffer objects.
         *
         * \param n Specifies the number of buffer objects to be deleted.
         * \param buffers Specifies an array of buffer objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteBuffers(GLsizei n, const GLuint* buffers, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteQueries function deletes named query objects.
         *
         * \param n Specifies the number of query objects to be deleted.
         * \param ids Specifies an array of query objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteQueries(GLsizei n, const GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glEndQuery function ends a query object.
         *
         * \param target Specifies the target type of query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEndQuery(GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glGenBuffers function generates buffer object names.
         *
         * \param n Specifies the number of buffer object names to be generated.
         * \param buffers Specifies an array in which the generated buffer object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenBuffers(GLsizei n, GLuint* buffers, const char* caller = nullptr) const;

        /**
         * \brief The glGenQueries function generates query object names.
         *
         * \param n Specifies the number of query object names to be generated.
         * \param ids Specifies an array in which the generated query object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenQueries(GLsizei n, GLuint* ids, const char* caller = nullptr) const;

        /**
         * \brief The glGetBufferParameteriv function returns parameters of a buffer object.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param pname Specifies the symbolic name of a buffer object parameter.
         * Accepted values are GL_BUFFER_SIZE, GL_BUFFER_USAGE, GL_BUFFER_ACCESS, GL_BUFFER_MAPPED.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetBufferPointerv function returns the pointer to a mapped buffer object's data store.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param pname Specifies the symbolic name of a buffer object parameter.
         * Accepted values are GL_BUFFER_MAP_POINTER.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBufferPointerv(GLenum target, GLenum pname, GLvoid** params, const char* caller = nullptr) const;

        /**
         * \brief The glGetBufferSubData function returns a subset of a buffer object's data store.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param offset Specifies the offset into the buffer object's data store where data retrieval will begin.
         * \param size Specifies the size in bytes of the data store region being retrieved.
         * \param data Specifies a pointer to the location where the retrieved data will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBufferSubData(
            GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryiv function returns parameters of a query object target.
         * \deprecated Deprecated in OpenGL 3.0. Use glGetQueryIndexediv instead.
         *
         * \param target Specifies the target query object.
         * Accepted values are GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED,
         * GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN.
         * \param pname Specifies the symbolic name of a query object parameter.
         * Accepted values are GL_QUERY_COUNTER_BITS, GL_CURRENT_QUERY.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryiv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryObjectiv function returns the integer value of a query object parameter.
         * \deprecated Deprecated in OpenGL 3.0. Use glGetQueryObjecti64v instead.
         *
         * \param id Specifies the name of a query object.
         * \param pname Specifies the symbolic name of a query object parameter.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_AVAILABLE.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetQueryObjectuiv function returns the unsigned integer value of a query object parameter.
         * \deprecated Deprecated in OpenGL 3.0. Use glGetQueryObjectui64v instead.
         *
         * \param id Specifies the name of a query object.
         * \param pname Specifies the symbolic name of a query object parameter.
         * Accepted values are GL_QUERY_RESULT, GL_QUERY_RESULT_AVAILABLE.
         * \param params Specifies a pointer to the location where the parameter value will be stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glIsBuffer function determines if a name corresponds to a buffer object.
         *
         * \param buffer Specifies a value that may be the name of a buffer object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if buffer is currently the name of a buffer object. GL_FALSE otherwise.
         */
        GLboolean glIsBuffer(GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glIsQuery function determines if a name corresponds to a query object.
         *
         * \param id Specifies a value that may be the name of a query object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if id is currently the name of a query object. GL_FALSE otherwise.
         */
        GLboolean glIsQuery(GLuint id, const char* caller = nullptr) const;

        /**
         * \brief The glMapBuffer function maps a buffer object's data store.
         * \deprecated Deprecated in OpenGL 3.0. Use glMapBufferRange instead.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param access Specifies the access policy for the mapping.
         * Accepted values are GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return A pointer to the mapped buffer object's data store.
         */
        GLvoid* glMapBuffer(GLenum target, GLenum access, const char* caller = nullptr) const;

        /**
         * \brief The glUnmapBuffer function releases the mapping of a buffer object's data store.
         * \deprecated Deprecated in OpenGL 3.0. Use glFlushMappedBufferRange instead.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         * GL_PIXEL_UNPACK_BUFFER.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if the data store contents have been successfully unmapped, GL_FALSE otherwise.
         */
        GLboolean glUnmapBuffer(GLenum target, const char* caller = nullptr) const;
    };
} // namespace nfx::graphics::gl
