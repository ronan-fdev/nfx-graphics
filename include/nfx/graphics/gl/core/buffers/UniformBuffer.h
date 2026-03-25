#pragma once

/**
 * \file UniformBuffer.h
 * \brief Declares a typed uniform buffer wrapper built on top of Buffer.
 */

#include "Buffer.h"

#include <cassert>
#include <type_traits>

namespace nfx::graphics::gl
{
    /**
     * \class UniformBuffer
     * \brief Typed UBO wrapper around Buffer.
     *
     * T must match the std140 layout of the corresponding GLSL uniform block.
     * Use alignas(16) on vec3 fields and explicit padding to avoid surprises.
     *
     * Example:
     *   struct CameraUBO { float view[16]; float proj[16]; };
     *   UniformBuffer<CameraUBO> ubo;
     *   ubo.upload(data);
     *   ubo.bind(0); // layout(binding = 0) in the shader
     */
    template <typename T>
    class UniformBuffer final
    {
    public:
        static_assert(std::is_trivially_copyable_v<T>, "UniformBuffer<T> requires T to be trivially copyable");
        static_assert(std::is_standard_layout_v<T>, "UniformBuffer<T> requires T to be standard layout");

        /**
         * \brief Creates a uniform buffer sized for one instance of T.
         *
         * The buffer storage is allocated immediately using the provided usage hint.
         * \param usage Usage hint applied to storage allocation and updates.
         * \pre An OpenGL context must be current.
         */
        UniformBuffer(Buffer::Usage usage = Buffer::Usage::DynamicDraw)
            : m_buffer{ Buffer::Target::UniformBuffer }
        {
            m_buffer.setData(nullptr, sizeof(T), usage);
        }

        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;
        UniformBuffer(UniformBuffer&&) noexcept = default;
        UniformBuffer& operator=(UniformBuffer&&) noexcept = default;

        /**
         * \brief Uploads one value of T to the underlying uniform buffer.
         * \param data Value to copy into the buffer storage.
         */
        void upload(const T& data)
        {
            if (m_buffer.size() < sizeof(T))
            {
                assert(m_buffer.size() >= sizeof(T) && "UniformBuffer::upload() requires allocated storage");
                return;
            }
            m_buffer.setSubData(&data, 0, sizeof(T));
        }

        /**
         * \brief Binds the uniform buffer to an indexed binding point.
         * \param bindingPoint Binding index expected by the GLSL uniform block.
         */
        void bind(GLuint bindingPoint) const { m_buffer.bind(bindingPoint); }

        /**
         * \brief Binds a byte range of the uniform buffer to an indexed binding point.
         * \param bindingPoint Binding index expected by the GLSL uniform block.
         * \param offset Byte offset of the first bound byte.
         * \param size Size in bytes of the bound range.
         */
        void bind(GLuint bindingPoint, std::size_t offset, std::size_t size) const
        {
            m_buffer.bind(bindingPoint, offset, size);
        }

        /**
         * \brief Returns the OpenGL buffer object id owned by the underlying uniform buffer.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_buffer.id(); }

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL uniform buffer object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_buffer.isValid(); }

        /**
         * \brief Returns the currently allocated uniform buffer size.
         * \return Size in bytes of the underlying buffer storage.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_buffer.size(); }

    private:
        Buffer m_buffer;
    };
} // namespace nfx::graphics::gl
