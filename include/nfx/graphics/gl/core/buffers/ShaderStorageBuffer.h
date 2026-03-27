#pragma once

/**
 * \file ShaderStorageBuffer.h
 * \brief Declares a typed shader storage buffer wrapper built on top of Buffer.
 */

#include "Buffer.h"

#include <cassert>
#include <type_traits>

namespace nfx::graphics::gl
{
    /**
     * \class ShaderStorageBuffer
     * \brief Typed SSBO wrapper around Buffer.
     *
     * Supports both single-element and array uploads. T can use std430 layout
     * (no vec3 padding restrictions unlike std140 UBOs).
     *
     * Single element:
     *   struct MyData { float transforms[64]; };
     *   ShaderStorageBuffer<MyData> ssbo;
     *   ssbo.upload(data);
     *   ssbo.bind(1); // layout(std430, binding = 1) in the shader
     *
     * Array of elements:
     *   ShaderStorageBuffer<float> ssbo;
     *   ssbo.upload(transforms.data(), transforms.size());
     *   ssbo.bind(2);
     */
    template <typename T>
    class ShaderStorageBuffer final
    {
    public:
        static_assert(std::is_trivially_copyable_v<T>, "ShaderStorageBuffer<T> requires T to be trivially copyable");
        static_assert(std::is_standard_layout_v<T>, "ShaderStorageBuffer<T> requires T to be standard layout");
        /**
         * \brief Creates an empty shader storage buffer wrapper.
         * \param usage Usage hint applied to future storage uploads.
         */
        ShaderStorageBuffer(Buffer::Usage usage = Buffer::Usage::DynamicDraw)
            : m_buffer{ Buffer::Target::ShaderStorage },
              m_bufferUsage{ usage }
        {}

        ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
        ShaderStorageBuffer& operator=(const ShaderStorageBuffer&) = delete;
        ShaderStorageBuffer(ShaderStorageBuffer&&) noexcept = default;
        ShaderStorageBuffer& operator=(ShaderStorageBuffer&&) noexcept = default;

        /**
         * \brief Uploads a single value of T to the storage buffer.
         * \param data Value to upload.
         */
        void upload(const T& data)
        {
            m_buffer.setData(&data, sizeof(T), m_bufferUsage);
            m_count = 1;
        }

        /**
         * \brief Uploads an array of T values to the storage buffer.
         * \param data Pointer to the first element to upload.
         * \param count Number of elements to upload.
         */
        void upload(const T* data, std::size_t count)
        {
            if (count == 0)
            {
                m_buffer.setData(nullptr, 0, m_bufferUsage);
                m_count = 0;
                return;
            }

            if (data == nullptr)
            {
                assert(data && "ShaderStorageBuffer::upload(data, count) requires non-null data when count > 0");
                return;
            }
            m_buffer.setData(data, sizeof(T) * count, m_bufferUsage);
            m_count = count;
        }

        /**
         * \brief Updates a subrange of the existing storage buffer.
         * \param data Pointer to the first element to upload.
         * \param offset Element offset inside the buffer.
         * \param count Number of elements to upload.
         */
        void upload(const T* data, std::size_t offset, std::size_t count)
        {
            if (count == 0)
            {
                return;
            }

            if (data == nullptr)
            {
                assert(
                    data && "ShaderStorageBuffer::upload(data, offset, count) requires non-null data when count > 0");
                return;
            }

            if (offset + count > m_count)
            {
                assert(
                    offset + count <= m_count &&
                    "ShaderStorageBuffer::upload(data, offset, count) range out of bounds");
                return;
            }

            m_buffer.setSubData(data, sizeof(T) * offset, sizeof(T) * count);
        }

        /**
         * \brief Binds the storage buffer to an indexed binding point.
         * \param bindingPoint Binding index expected by the GLSL shader storage block.
         */
        void bind(GLuint bindingPoint) const { m_buffer.bind(bindingPoint); }

        /**
         * \brief Binds a range of the storage buffer to an indexed binding point.
         * \param bindingPoint Binding index expected by the GLSL shader storage block.
         * \param offset Element offset of the first bound element.
         * \param count Number of bound elements.
         */
        void bind(GLuint bindingPoint, std::size_t offset, std::size_t count) const
        {
            if (offset + count > m_count)
            {
                assert(
                    offset + count <= m_count &&
                    "ShaderStorageBuffer::bind(bindingPoint, offset, count) range out of bounds");
                return;
            }
            m_buffer.bind(bindingPoint, sizeof(T) * offset, sizeof(T) * count);
        }

        /**
         * \brief Returns the number of T elements currently represented by the buffer.
         */
        [[nodiscard]] std::size_t count() const noexcept { return m_count; }

        /**
         * \brief Returns the total size in bytes currently represented by the buffer.
         */
        [[nodiscard]] std::size_t size() const noexcept { return sizeof(T) * m_count; }

    private:
        Buffer m_buffer;
        Buffer::Usage m_bufferUsage;
        std::size_t m_count = 0;
    };
} // namespace nfx::graphics::gl
