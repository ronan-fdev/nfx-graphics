#pragma once

/**
 * \file Functions_3_0.h
 * \brief Declares the OpenGL 3.0 function wrapper interface.
 */

#include "Functions_2_1.h"

namespace nfx::graphics::gl
{
    /**
     * \class Functions_3_0
     * \brief Exposes the OpenGL 3.0 function set.
     */
    class Functions_3_0 : public Functions_2_1
    {
        static inline bool s_loaded;

    public:
        explicit Functions_3_0();
        Functions_3_0(const Functions_3_0&) = delete;
        Functions_3_0& operator=(const Functions_3_0&) = delete;
        Functions_3_0(Functions_3_0&&) = delete;
        Functions_3_0& operator=(Functions_3_0&&) = delete;
        virtual ~Functions_3_0();

    protected:
        bool initialize();
        void teardown();

    private:
        void nullifyPointers();

    public:
        /**
         * \brief The glBeginConditionalRender function starts conditional rendering.
         * \deprecated Deprecated in OpenGL 4.5. Use glBeginConditionalRenderNV instead.
         *
         * \param id Specifies the name of a query object whose results are used to determine if rendering should
         * be performed.
         * \param mode Specifies how the results of the query object are interpreted.
         * Accepted values are GL_QUERY_WAIT, GL_QUERY_NO_WAIT, GL_QUERY_BY_REGION_WAIT,
         * GL_QUERY_BY_REGION_NO_WAIT.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBeginConditionalRender(GLuint id, GLenum mode, const char* caller = nullptr) const;

        /**
         * \brief The glBeginTransformFeedback function begins transform feedback operation.
         * \deprecated Deprecated in OpenGL 4.5. Use glBeginTransformFeedbackNV instead.
         *
         * \param primitiveMode Specifies the output type of the primitives that will be recorded into the buffer
         * objects that are bound for transform feedback. Accepted values are GL_POINTS, GL_LINES, GL_TRIANGLES.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBeginTransformFeedback(GLenum primitiveMode, const char* caller = nullptr) const;

        /**
         * \brief The glBindBufferBase function binds a buffer object to an indexed buffer target.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindBufferBaseNV instead.
         *
         * \param target Specifies the target of the bind operation.
         * Accepted values are GL_ATOMIC_COUNTER_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER,
         * GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER.
         * \param index Specifies the index of the binding point within the array specified by target.
         * \param buffer Specifies the name of a buffer object to bind to the specified binding point.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindBufferBase(GLenum target, GLuint index, GLuint buffer, const char* caller = nullptr) const;

        /**
         * \brief The glBindBufferRange function binds a range within a buffer object to an indexed buffer target.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindBufferRangeNV instead.
         *
         * \param target Specifies the target of the bind operation.
         * Accepted values are GL_ATOMIC_COUNTER_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER,
         * GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER.
         * \param index Specifies the index of the binding point within the array specified by target.
         * \param buffer Specifies the name of a buffer object to bind to the specified binding point.
         * \param offset Specifies the starting offset in basic machine units into the buffer object buffer.
         * \param size Specifies the amount of data in machine units that can be read from the buffer object while
         * used as an indexed target.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindBufferRange(
            GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char* caller = nullptr)
            const;

        /**
         * \brief The glBindFragDataLocation function binds a user-defined varying out variable to a fragment shader
         * color number.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindFragDataLocationNV instead.
         *
         * \param program Specifies the name of the program containing varying out variable whose binding to modify.
         * \param color Specifies the color number to bind the user-defined varying out variable to.
         * \param name Specifies the name of the user-defined varying out variable whose binding to modify.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindFragDataLocation(
            GLuint program, GLuint color, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glBindFramebuffer function binds a framebuffer to a framebuffer target.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindFramebufferNV instead.
         *
         * \param target Specifies the framebuffer target.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param framebuffer Specifies the name of the framebuffer object to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindFramebuffer(GLenum target, GLuint framebuffer, const char* caller = nullptr) const;

        /**
         * \brief The glBindRenderbuffer function binds a renderbuffer to a renderbuffer target.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindRenderbufferNV instead.
         *
         * \param target Specifies the renderbuffer target.
         * Accepted values are GL_RENDERBUFFER.
         * \param renderbuffer Specifies the name of the renderbuffer object to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindRenderbuffer(GLenum target, GLuint renderbuffer, const char* caller = nullptr) const;

        /**
         * \brief The glBindVertexArray function binds a vertex array object.
         * \deprecated Deprecated in OpenGL 4.5. Use glBindVertexArrayNV instead.
         *
         * \param array Specifies the name of the vertex array object to bind.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBindVertexArray(GLuint array, const char* caller = nullptr) const;

        /**
         * \brief The glBlitFramebuffer function copies a block of pixels from one framebuffer object to another.
         * \deprecated Deprecated in OpenGL 4.5. Use glBlitFramebufferNV instead.
         *
         * \param srcX0 Specifies the lower left x coordinate of the source rectangle.
         * \param srcY0 Specifies the lower left y coordinate of the source rectangle.
         * \param srcX1 Specifies the upper right x coordinate of the source rectangle.
         * \param srcY1 Specifies the upper right y coordinate of the source rectangle.
         * \param dstX0 Specifies the lower left x coordinate of the destination rectangle.
         * \param dstY0 Specifies the lower left y coordinate of the destination rectangle.
         * \param dstX1 Specifies the upper right x coordinate of the destination rectangle.
         * \param dstY1 Specifies the upper right y coordinate of the destination rectangle.
         * \param mask Specifies the bitwise OR of the flags indicating which buffers are to be copied.
         * Accepted values are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.
         * \param filter Specifies the interpolation to be applied if the image is stretched.
         * Accepted values are GL_NEAREST, GL_LINEAR.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glBlitFramebuffer(
            GLint srcX0,
            GLint srcY0,
            GLint srcX1,
            GLint srcY1,
            GLint dstX0,
            GLint dstY0,
            GLint dstX1,
            GLint dstY1,
            GLbitfield mask,
            GLenum filter,
            const char* caller = nullptr) const;

        /**
         * \brief The glCheckFramebufferStatus function checks the completeness status of a framebuffer.
         * \deprecated Deprecated in OpenGL 4.5. Use glCheckFramebufferStatusNV instead.
         *
         * \param target Specifies the target of the framebuffer completeness check.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The completeness status of the framebuffer. Returns GL_FRAMEBUFFER_COMPLETE if the framebuffer is
         * complete, otherwise returns an error code. Possible return values are GL_FRAMEBUFFER_COMPLETE,
         * GL_FRAMEBUFFER_UNDEFINED, GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
         * GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
         * GL_FRAMEBUFFER_UNSUPPORTED, GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS.
         */
        GLenum glCheckFramebufferStatus(GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glClampColor function controls color clamping.
         * \deprecated Deprecated in OpenGL 4.5. Use glClampColorNV instead.
         *
         * \param target Specifies whether to enable or disable color clamping.
         * Accepted values are GL_CLAMP_READ_COLOR.
         * \param clamp Specifies whether to enable or disable color clamping.
         * Accepted values are GL_FALSE, GL_TRUE, GL_FIXED_ONLY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClampColor(GLenum target, GLenum clamp, const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferfi function clears a buffer to a fixed value.
         * \deprecated Deprecated in OpenGL 4.5. Use glClearBufferfiNV instead.
         *
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_DEPTH_STENCIL.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * Accepted values are 0.
         * \param depth Specifies the value to clear the depth buffer to.
         * \param stencil Specifies the value to clear the stencil buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferfi(
            GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferfv function clears a buffer to a fixed value.
         * \deprecated Deprecated in OpenGL 4.5. Use glClearBufferfvNV instead.
         *
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR, GL_DEPTH.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferfv(
            GLenum buffer, GLint drawbuffer, const GLfloat* value, const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferiv function clears a buffer to a fixed value.
         * \deprecated Deprecated in OpenGL 4.5. Use glClearBufferivNV instead.
         *
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR, GL_STENCIL.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value, const char* caller = nullptr) const;

        /**
         * \brief The glClearBufferuiv function clears a buffer to a fixed value.
         * \deprecated Deprecated in OpenGL 4.5. Use glClearBufferuivNV instead.
         *
         * \param buffer Specifies the buffer to be cleared.
         * Accepted values are GL_COLOR.
         * \param drawbuffer Specifies the draw buffer to be cleared.
         * \param value Specifies a pointer to the value to clear the buffer to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glClearBufferuiv(
            GLenum buffer, GLint drawbuffer, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glColorMaski function enables and disables writing of frame buffer color components.
         * \deprecated Deprecated in OpenGL 4.5. Use glColorMaskiNV instead.
         *
         * \param index Specifies the index of the draw buffer.
         * \param r Specifies whether red values are written or not.
         * \param g Specifies whether green values are written or not.
         * \param b Specifies whether blue values are written or not.
         * \param a Specifies whether alpha values are written or not.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glColorMaski(
            GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteFramebuffers function deletes framebuffer objects.
         *
         * \param n  Specifies the number of framebuffer objects to be deleted.
         * \param framebuffers Specifies an array of framebuffer objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteRenderbuffers function deletes renderbuffer objects.
         *
         * \param n  Specifies the number of renderbuffer objects to be deleted.
         * \param renderbuffers Specifies an array of renderbuffer objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers, const char* caller = nullptr) const;

        /**
         * \brief The glDeleteVertexArrays function deletes vertex array objects.
         *
         * \param n Specifies the number of vertex array objects to be deleted.
         * \param arrays Specifies an array of vertex array objects to be deleted.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDeleteVertexArrays(GLsizei n, const GLuint* arrays, const char* caller = nullptr) const;

        /**
         * \brief The glDisablei function disables a capability for a specific draw buffer.
         *
         * \param target Specifies the capability to disable.
         * Accepted values are GL_BLEND, GL_SCISSOR_TEST, GL_COLOR_LOGIC_OP, GL_DEPTH_CLAMP,
         * GL_DEPTH_TEST, GL_STENCIL_TEST, GL_FRAMEBUFFER_SRGB, GL_SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_COVERAGE,
         * GL_SAMPLE_MASK, GL_PROGRAM_POINT_SIZE, GL_PRIMITIVE_RESTART, GL_PRIMITIVE_RESTART_FIXED_INDEX.
         * \param index Specifies the index of the draw buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glDisablei(GLenum target, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glEnablei function enables a capability for a specific draw buffer.
         *
         * \param target Specifies the capability to enable.
         * Accepted values are GL_BLEND, GL_SCISSOR_TEST, GL_COLOR_LOGIC_OP, GL_DEPTH_CLAMP,
         * GL_DEPTH_TEST, GL_STENCIL_TEST, GL_FRAMEBUFFER_SRGB, GL_SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_COVERAGE,
         * GL_SAMPLE_MASK, GL_PROGRAM_POINT_SIZE, GL_PRIMITIVE_RESTART, GL_PRIMITIVE_RESTART_FIXED_INDEX.
         * \param index Specifies the index of the draw buffer.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEnablei(GLenum target, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glEndConditionalRender function ends conditional rendering.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEndConditionalRender(const char* caller = nullptr) const;

        /**
         * \brief The glEndTransformFeedback function ends transform feedback operation.
         *
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glEndTransformFeedback(const char* caller = nullptr) const;

        /**
         * \brief The glFlushMappedBufferRange function indicates modifications to a range of a mapped buffer.
         *
         * \param target Specifies the target buffer object.
         * \param offset Specifies the start of the buffer subrange, in basic machine units.
         * \param length Specifies the length of the buffer subrange, in basic machine units.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFlushMappedBufferRange(
            GLenum target, GLintptr offset, GLsizeiptr length, const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferRenderbuffer function attaches a renderbuffer as a logical buffer to the currently
         * bound framebuffer object.
         *
         * \param target  Specifies the framebuffer target.
         *  Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         *  Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT,
         * GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT.
         * \param renderbuffertarget Specifies the renderbuffer target.
         *  Accepted values are GL_RENDERBUFFER.
         * \param renderbuffer Specifies the name of the renderbuffer object to attach.
         * \param caller  Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferRenderbuffer(
            GLenum target,
            GLenum attachment,
            GLenum renderbuffertarget,
            GLuint renderbuffer,
            const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferTexture1D function attaches a level of a one-dimensional texture object as a
         * logical buffer to the currently bound framebuffer object.
         *
         * \param target Specifies the framebuffer target.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param textarget Specifies the texture target.
         * Accepted values are GL_TEXTURE_1D.
         * \param texture Specifies the name of the texture object to attach.
         * \param level Specifies the mipmap level of the texture object to attach.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferTexture1D(
            GLenum target,
            GLenum attachment,
            GLenum textarget,
            GLuint texture,
            GLint level,
            const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferTexture2D function attaches a level of a two-dimensional texture object as a
         * logical buffer to the currently bound framebuffer object.
         *
         * \param target Specifies the framebuffer target.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param textarget Specifies the texture target.
         * Accepted values are GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
         * GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
         * GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z.
         * \param texture Specifies the name of the texture object to attach.
         * \param level Specifies the mipmap level of the texture object to attach.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferTexture2D(
            GLenum target,
            GLenum attachment,
            GLenum textarget,
            GLuint texture,
            GLint level,
            const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferTexture3D function attaches a level of a three-dimensional texture object as a
         * logical buffer to the currently bound framebuffer object.
         *
         * \param target Specifies the framebuffer target.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param textarget Specifies the texture target.
         * Accepted values are GL_TEXTURE_3D.
         * \param texture Specifies the name of the texture object to attach.
         * \param level Specifies the mipmap level of the texture object to attach.
         * \param zoffset Specifies the z-offset within the texture.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferTexture3D(
            GLenum target,
            GLenum attachment,
            GLenum textarget,
            GLuint texture,
            GLint level,
            GLint zoffset,
            const char* caller = nullptr) const;

        /**
         * \brief The glFramebufferTextureLayer function attaches a single layer of a texture object as a logical
         * buffer to the currently bound framebuffer object.
         *
         * \param target Specifies the framebuffer target.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param texture Specifies the name of the texture object to attach.
         * \param level Specifies the mipmap level of the texture object to attach.
         * \param layer Specifies the layer of the texture object to attach.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glFramebufferTextureLayer(
            GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char* caller = nullptr)
            const;

        /**
         * \brief The glGenerateMipmap function generates mipmaps for the specified texture target.
         *
         * \param target Specifies the target to which the texture is bound.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY,
         * GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenerateMipmap(GLenum target, const char* caller = nullptr) const;

        /**
         * \brief The glGenFramebuffers function generates framebuffer object names.
         *
         * \param n  Specifies the number of framebuffer object names to generate.
         * \param framebuffers Specifies an array in which the generated framebuffer object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenFramebuffers(GLsizei n, GLuint* framebuffers, const char* caller = nullptr) const;

        /**
         * \brief The glGenRenderbuffers function generates renderbuffer object names.
         *
         * \param n  Specifies the number of renderbuffer object names to generate.
         * \param renderbuffers Specifies an array in which the generated renderbuffer object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenRenderbuffers(GLsizei n, GLuint* renderbuffers, const char* caller = nullptr) const;

        /**
         * \brief The glGenVertexArrays function generates vertex array object names.
         *
         * \param n Specifies the number of vertex array object names to generate.
         * \param arrays Specifies an array in which the generated vertex array object names are stored.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGenVertexArrays(GLsizei n, GLuint* arrays, const char* caller = nullptr) const;

        /**
         * \brief The glGetBooleani_v function returns the value of a selected parameter.
         *
         * \param target Specifies the symbolic name of a parameter.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, GL_UNIFORM_BUFFER_START, GL_UNIFORM_BUFFER_SIZE,
         * GL_UNIFORM_BUFFER_BINDING.
         * \param index Specifies the index of the parameter to be returned.
         * \param data Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetBooleani_v(GLenum target, GLuint index, GLboolean* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetFragDataLocation function returns the binding of a user-defined varying out variable.
         *
         * \param program Specifies the name of the program containing varying out variable whose binding to query.
         * \param name Specifies the name of the user-defined varying out variable whose binding to query.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return The binding of the user-defined varying out variable. Returns the index of the user-defined varying
         * out variable, or -1 if the name does not correspond to a varying out variable.
         */
        GLint glGetFragDataLocation(GLuint program, const GLchar* name, const char* caller = nullptr) const;

        /**
         * \brief The glGetFramebufferAttachmentParameteriv function returns a parameter from a framebuffer object.
         *
         * \param target Specifies the target framebuffer object.
         * Accepted values are GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER.
         * \param attachment Specifies the attachment point of the framebuffer.
         * Accepted values are GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT,
         * GL_DEPTH_STENCIL_ATTACHMENT.
         * \param pname Specifies the symbolic name of a framebuffer object parameter.
         * Accepted values are GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
         * GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
         * GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE,
         * GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
         * GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE,
         * GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetFramebufferAttachmentParameteriv(
            GLenum target, GLenum attachment, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetIntegeri_v function returns the value of a selected parameter.
         *
         * \param target Specifies the symbolic name of a parameter.
         * Accepted values are GL_TRANSFORM_FEEDBACK_BUFFER_START, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
         * GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, GL_UNIFORM_BUFFER_START, GL_UNIFORM_BUFFER_SIZE,
         * GL_UNIFORM_BUFFER_BINDING.
         * \param index Specifies the index of the parameter to be returned.
         * \param data Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetIntegeri_v(GLenum target, GLuint index, GLint* data, const char* caller = nullptr) const;

        /**
         * \brief The glGetRenderbufferParameteriv function returns a parameter from a renderbuffer object.
         *
         * \param target Specifies the target renderbuffer object.
         * Accepted values are GL_RENDERBUFFER.
         * \param pname Specifies the symbolic name of a renderbuffer object parameter.
         * Accepted values are GL_RENDERBUFFER_WIDTH, GL_RENDERBUFFER_HEIGHT,
         * GL_RENDERBUFFER_INTERNAL_FORMAT, GL_RENDERBUFFER_RED_SIZE, GL_RENDERBUFFER_GREEN_SIZE,
         * GL_RENDERBUFFER_BLUE_SIZE, GL_RENDERBUFFER_ALPHA_SIZE, GL_RENDERBUFFER_DEPTH_SIZE,
         * GL_RENDERBUFFER_STENCIL_SIZE, GL_RENDERBUFFER_SAMPLES.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetRenderbufferParameteriv(
            GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetStringi function returns a string describing the current GL connection.
         *
         * \param name Specifies a symbolic constant, one of GL_VENDOR, GL_RENDERER, GL_VERSION, or
         * GL_SHADING_LANGUAGE_VERSION.
         * \param index Specifies the index of the string to return.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return A pointer to the string. Returns a pointer to the specified string, or NULL if an error occurs.
         */
        const GLubyte* glGetStringi(GLenum name, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexParameterIiv function returns the integer value of a texture parameter.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER,
         * GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a texture parameter.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC,
         * GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B, GL_TEXTURE_SWIZZLE_A,
         * GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTexParameterIuiv function returns the unsigned integer value of a texture parameter.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER,
         * GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a texture parameter.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC,
         * GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B, GL_TEXTURE_SWIZZLE_A,
         * GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to a variable that will receive the value of the parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetTransformFeedbackVarying function returns information about varying variables selected for
         * transform feedback.
         *
         * \param program Specifies the program object to be queried.
         * \param index Specifies the index of the varying variable to be queried.
         * \param bufSize Specifies the maximum number of characters that can be written into name.
         * \param length Specifies a pointer to a variable that will receive the length of the varying variable name.
         * \param size Specifies a pointer to a variable that will receive the size of the varying variable.
         * \param type Specifies a pointer to a variable that will receive the data type of the varying variable.
         * Possible values are GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4, GL_INT,
         * GL_INT_VEC2, GL_INT_VEC3, GL_INT_VEC4, GL_UNSIGNED_INT, GL_UNSIGNED_INT_VEC2, GL_UNSIGNED_INT_VEC3,
         * GL_UNSIGNED_INT_VEC4, GL_DOUBLE, GL_DOUBLE_VEC2, GL_DOUBLE_VEC3, GL_DOUBLE_VEC4.
         * \param name Specifies an array of characters that will receive the varying variable name.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetTransformFeedbackVarying(
            GLuint program,
            GLuint index,
            GLsizei bufSize,
            GLsizei* length,
            GLsizei* size,
            GLenum* type,
            GLchar* name,
            const char* caller = nullptr) const;

        /**
         * \brief The glGetUniformuiv function returns the value of an unsigned integer uniform variable for the
         * specified program object.
         *
         * \param program Specifies the program object to be queried.
         * \param location Specifies the location of the uniform variable to be queried.
         * \param params Specifies a pointer to a variable that will receive the value of the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetUniformuiv(GLuint program, GLint location, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribIiv function returns the integer value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_ARRAY_LONG, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to a variable that will receive the value of the vertex attribute
         * parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glGetVertexAttribIuiv function returns the unsigned integer value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be queried.
         * \param pname Specifies the symbolic name of the vertex attribute parameter to be queried.
         * Accepted values are GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
         * GL_VERTEX_ATTRIB_ARRAY_SIZE, GL_VERTEX_ATTRIB_ARRAY_STRIDE, GL_VERTEX_ATTRIB_ARRAY_TYPE,
         * GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, GL_VERTEX_ATTRIB_ARRAY_INTEGER, GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
         * GL_VERTEX_ATTRIB_ARRAY_LONG, GL_CURRENT_VERTEX_ATTRIB.
         * \param params Specifies a pointer to a variable that will receive the value of the vertex attribute
         * parameter.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glIsEnabledi function determines if a specific capability for a specific draw buffer is enabled.
         *
         * \param target Specifies the capability to check.
         * \param index Specifies the index of the draw buffer.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if the specified capability for the specified draw buffer is enabled, GL_FALSE otherwise.
         */
        GLboolean glIsEnabledi(GLenum target, GLuint index, const char* caller = nullptr) const;

        /**
         * \brief The glIsFramebuffer function determines if a name corresponds to a framebuffer object.
         *
         * \param framebuffer Specifies a value that may be the name of a framebuffer object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if framebuffer is a framebuffer object, GL_FALSE otherwise.
         */
        GLboolean glIsFramebuffer(GLuint framebuffer, const char* caller = nullptr) const;

        /**
         * \brief The glIsRenderbuffer function determines if a name corresponds to a renderbuffer object.
         *
         * \param renderbuffer Specifies a value that may be the name of a renderbuffer object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if renderbuffer is a renderbuffer object, GL_FALSE otherwise.
         */
        GLboolean glIsRenderbuffer(GLuint renderbuffer, const char* caller = nullptr) const;

        /**
         * \brief The glIsVertexArray function determines if a name corresponds to a vertex array object.
         *
         * \param array Specifies a value that may be the name of a vertex array object.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return GL_TRUE if array is a vertex array object, GL_FALSE otherwise.
         */
        GLboolean glIsVertexArray(GLuint array, const char* caller = nullptr) const;

        /**
         * \brief The glMapBufferRange function maps a range of a buffer object's data store.
         *
         * \param target Specifies the target buffer object.
         * Accepted values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,
         * GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
         * GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER,
         * GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER.
         * \param offset Specifies the starting offset within the buffer object.
         * \param length Specifies the length of the range to be mapped.
         * \param access Specifies a bitfield indicating the access policy.
         * Accepted values are GL_MAP_READ_BIT, GL_MAP_WRITE_BIT, GL_MAP_INVALIDATE_RANGE_BIT,
         * GL_MAP_INVALIDATE_BUFFER_BIT, GL_MAP_FLUSH_EXPLICIT_BIT, GL_MAP_UNSYNCHRONIZED_BIT.
         * \param caller Optional parameter to specify the caller function or context.
         *
         * \return A pointer to the mapped range. Returns NULL if an error occurs.
         */
        GLvoid* glMapBufferRange(
            GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, const char* caller = nullptr) const;

        /**
         * \brief The glRenderbufferStorage function establishes data storage, format, and dimensions of a
         * renderbuffer object's image.
         *
         * \param target Specifies the target renderbuffer object.
         *  Accepted values are GL_RENDERBUFFER.
         * \param internalformat Specifies the internal format to be used for the renderbuffer object's image.
         *  Accepted values are GL_RGBA4, GL_RGB565, GL_RGB5_A1, GL_DEPTH_COMPONENT16,
         * GL_STENCIL_INDEX8, GL_DEPTH24_STENCIL8.
         * \param width  Specifies the width of the renderbuffer, in pixels.
         * \param height Specifies the height of the renderbuffer, in pixels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRenderbufferStorage(
            GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char* caller = nullptr) const;

        /**
         * \brief The glRenderbufferStorageMultisample function establishes data storage, format, and dimensions of a
         * renderbuffer object's image with multisample anti-aliasing.
         *
         * \param target Specifies the target renderbuffer object.
         *  Accepted values are GL_RENDERBUFFER.
         * \param samples Specifies the number of samples to be used for the renderbuffer object's image.
         * \param internalformat Specifies the internal format to be used for the renderbuffer object's image.
         *  Accepted values are GL_RGBA4, GL_RGB565, GL_RGB5_A1, GL_DEPTH_COMPONENT16,
         * GL_STENCIL_INDEX8, GL_DEPTH24_STENCIL8.
         * \param width  Specifies the width of the renderbuffer, in pixels.
         * \param height Specifies the height of the renderbuffer, in pixels.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glRenderbufferStorageMultisample(
            GLenum target,
            GLsizei samples,
            GLenum internalformat,
            GLsizei width,
            GLsizei height,
            const char* caller = nullptr) const;

        /**
         * \brief The glTexParameterIiv function sets the integer value of a texture parameter.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER,
         * GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a texture parameter.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC,
         * GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B, GL_TEXTURE_SWIZZLE_A,
         * GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to an array of values to set the parameter to.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTexParameterIiv(GLenum target, GLenum pname, const GLint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTexParameterIuiv function sets the unsigned integer value of a texture parameter.
         *
         * \param target Specifies the target texture.
         * Accepted values are GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY,
         * GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER,
         * GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
         * \param pname Specifies the symbolic name of a texture parameter.
         * Accepted values are GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_WRAP_S,
         * GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R, GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
         * GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC,
         * GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B, GL_TEXTURE_SWIZZLE_A,
         * GL_TEXTURE_SWIZZLE_RGBA, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_VIEW_MIN_LEVEL,
         * GL_TEXTURE_VIEW_NUM_LEVELS, GL_TEXTURE_VIEW_MIN_LAYER, GL_TEXTURE_VIEW_NUM_LAYERS,
         * GL_TEXTURE_IMMUTABLE_LEVELS.
         * \param params Specifies a pointer to an array of values to set the parameter to.
         * \param caller Optional parameter to specify the caller function or context.
         */

        GLvoid glTexParameterIuiv(
            GLenum target, GLenum pname, const GLuint* params, const char* caller = nullptr) const;

        /**
         * \brief The glTransformFeedbackVaryings function specifies values to record in transform feedback buffers.
         *
         * \param program Specifies the program object whose varyings to set.
         * \param count Specifies the number of varying variables used for transform feedback.
         * \param varyings Specifies an array of pointers to strings specifying the names of the varying variables
         * to use for transform feedback.
         * \param bufferMode Specifies the mode used to capture the varying variables.
         * Accepted values are GL_INTERLEAVED_ATTRIBS, GL_SEPARATE_ATTRIBS.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glTransformFeedbackVaryings(
            GLuint program,
            GLsizei count,
            const GLchar* const* varyings,
            GLenum bufferMode,
            const char* caller = nullptr) const;

        /**
         * \brief The glUniform1ui function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1ui(GLint location, GLuint v0, const char* caller = nullptr) const;

        /**
         * \brief The glUniform1uiv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform1uiv(GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2ui function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2ui(GLint location, GLuint v0, GLuint v1, const char* caller = nullptr) const;

        /**
         * \brief The glUniform2uiv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform2uiv(GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3ui function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2, const char* caller = nullptr) const;

        /**
         * \brief The glUniform3uiv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform3uiv(GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4ui function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param v0 Specifies the first new value to be used for the uniform variable.
         * \param v1 Specifies the second new value to be used for the uniform variable.
         * \param v2 Specifies the third new value to be used for the uniform variable.
         * \param v3 Specifies the fourth new value to be used for the uniform variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4ui(
            GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char* caller = nullptr) const;

        /**
         * \brief The glUniform4uiv function specifies the value of a uniform variable for the current program object.
         *
         * \param location Specifies the location of the uniform variable to be modified.
         * \param count Specifies the number of elements that are to be modified.
         * \param value Specifies a pointer to an array of values that will be used to update the specified uniform
         * variable.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glUniform4uiv(GLint location, GLsizei count, const GLuint* value, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI1i function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI1i(GLuint index, GLint x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI1iv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new value to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI1iv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI1ui function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI1ui(GLuint index, GLuint x, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI1uiv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new value to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI1uiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI2i function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI2i(GLuint index, GLint x, GLint y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI2iv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI2iv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI2ui function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI2ui(GLuint index, GLuint x, GLuint y, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI2uiv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI2uiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI3i function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI3iv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI3iv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI3ui function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI3uiv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI3uiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4bv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 4.5. Use glVertexAttribL4bv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4bv(GLuint index, const GLbyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4i function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4iv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4iv(GLuint index, const GLint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4sv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 4.5. Use glVertexAttribL4sv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4sv(GLuint index, const GLshort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4ubv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 4.5. Use glVertexAttribL4ubv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4ubv(GLuint index, const GLubyte* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4ui function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param x Specifies the first new value to be used for the generic vertex attribute.
         * \param y Specifies the second new value to be used for the generic vertex attribute.
         * \param z Specifies the third new value to be used for the generic vertex attribute.
         * \param w Specifies the fourth new value to be used for the generic vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4ui(
            GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4uiv function specifies the value of a generic vertex attribute.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4uiv(GLuint index, const GLuint* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribI4usv function specifies the value of a generic vertex attribute.
         * \deprecated Deprecated in OpenGL 4.5. Use glVertexAttribL4usv instead.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param v Specifies a pointer to an array that contains the new values to be used for the generic
         * vertex attribute.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribI4usv(GLuint index, const GLushort* v, const char* caller = nullptr) const;

        /**
         * \brief The glVertexAttribIPointer function defines an array of generic vertex attribute data.
         *
         * \param index Specifies the index of the generic vertex attribute to be modified.
         * \param size Specifies the number of components per generic vertex attribute.
         * Accepted values are 1, 2, 3, 4.
         * \param type Specifies the data type of each component in the array.
         * Accepted values are GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT,
         * GL_UNSIGNED_INT.
         * \param stride Specifies the byte offset between consecutive generic vertex attributes.
         * \param pointer Specifies a pointer to the first component of the first generic vertex attribute in the
         * array.
         * \param caller Optional parameter to specify the caller function or context.
         */
        GLvoid glVertexAttribIPointer(
            GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer, const char* caller = nullptr)
            const;
    };
} // namespace nfx::graphics::gl
