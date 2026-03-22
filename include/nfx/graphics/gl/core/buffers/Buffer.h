#pragma once

/**
 * \file Buffer.h
 * \brief Declares a RAII wrapper for OpenGL buffer objects and their common binding targets.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \class Buffer
     * \brief Owns an OpenGL buffer object and exposes common upload and binding operations.
     */
    class Buffer final
    {
    public:
        // clang-format off
        /**
         * \brief Enumerates the supported OpenGL buffer binding targets.
         */
        enum class Target : unsigned int
        {
            VertexAttributesArray = ARRAY_BUFFER,
            VertexIndicesArray    = ELEMENT_ARRAY_BUFFER,
            UniformBuffer         = UNIFORM_BUFFER,
            ShaderStorage         = SHADER_STORAGE_BUFFER,
            TransformFeedback     = TRANSFORM_FEEDBACK_BUFFER,
            CopyRead              = COPY_READ_BUFFER,
            CopyWrite             = COPY_WRITE_BUFFER,
            PixelPack             = PIXEL_PACK_BUFFER,
            PixelUnpack           = PIXEL_UNPACK_BUFFER,
            AtomicCounter         = ATOMIC_COUNTER_BUFFER,
            DrawIndirect          = DRAW_INDIRECT_BUFFER,
            DispatchIndirect      = DISPATCH_INDIRECT_BUFFER,
            Texture               = TEXTURE_BUFFER,
            Query                 = QUERY_BUFFER
        };

        /**
         * \brief Enumerates the intended usage pattern for buffer storage uploads.
         */
        enum class Usage : unsigned int
        {
            StreamDraw  = STREAM_DRAW,
            StreamRead  = STREAM_READ,
            StreamCopy  = STREAM_COPY,
            StaticDraw  = STATIC_DRAW,
            StaticRead  = STATIC_READ,
            StaticCopy  = STATIC_COPY,
            DynamicDraw = DYNAMIC_DRAW,
            DynamicRead = DYNAMIC_READ,
            DynamicCopy = DYNAMIC_COPY
        };
        // clang-format on

        /**
         * \brief Creates a buffer object for a fixed binding target.
         * \param target OpenGL target that will be used when binding and updating the buffer.
         */
        explicit Buffer(Target target);

        /**
         * \brief Releases the underlying OpenGL buffer object.
         */
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;

        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;

        /**
         * \brief Binds the buffer to its target.
         */
        void bind() const;

        /**
         * \brief Unbinds the current buffer from its target.
         */
        void unbind() const;

        /**
         * \brief Replaces the whole storage of the buffer.
         * \param data Source data pointer, or nullptr to allocate uninitialized storage.
         * \param size Size in bytes of the new storage.
         * \param usage Expected usage pattern for the uploaded data.
         *
         * When \p data is nullptr, this allocates uninitialized storage of \p size bytes.
         */
        void setData(const void* data, std::size_t size, Usage usage = Usage::StaticDraw);

        /**
         * \brief Updates a subrange of the existing buffer storage.
         * \param data Source data pointer.
         * \param offset Byte offset inside the buffer.
         * \param size Size in bytes to update.
         *
         * Requires \p data to be non-null when \p size > 0, \p offset <= this->size(),
         * and \p size <= this->size() - \p offset.
         */
        void setSubData(const void* data, std::size_t offset, std::size_t size);

        /**
         * \brief Binds the buffer to an indexed binding point.
         *
         * Valid for targets such as uniform, shader storage, transform feedback and atomic counter buffers.
         * If called for a non-indexed target, this is ignored in release and asserted in debug.
         * \param bindingPoint Binding index to associate with the buffer.
         */
        void bind(GLuint bindingPoint) const;

        /**
         * \brief Binds a byte range of the buffer to an indexed binding point.
         *
         * Valid for targets such as uniform, shader storage, transform feedback and atomic counter buffers.
         * If called for a non-indexed target, this is ignored in release and asserted in debug.
         * \param bindingPoint Binding index to associate with the buffer range.
         * \param offset Byte offset of the first bound byte.
         * \param size Size in bytes of the bound range.
         *
         * Requires \p offset <= this->size() and \p size <= this->size() - \p offset.
         */
        void bind(GLuint bindingPoint, std::size_t offset, std::size_t size) const;

        /**
         * \brief Returns the fixed OpenGL binding target of this buffer.
         * \return The target associated with this buffer object.
         */
        [[nodiscard]] Target target() const noexcept { return m_target; }

        /**
         * \brief Returns the OpenGL object id owned by this buffer.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Indicates whether the buffer currently owns a valid OpenGL object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the currently allocated buffer size.
         * \return Size in bytes of the current storage.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_size; }

    private:
        void release();

        Target m_target;
        GLuint m_id = 0;
        std::size_t m_size = 0;
    };
} // namespace nfx::graphics::gl
