#include "nfx/graphics/gl/core/buffers/Buffer.h"

#include "nfx/graphics/gl/core/Context.h"

#include <cassert>

namespace nfx::graphics::gl
{
    namespace
    {
        bool supportsIndexedBindingTarget(Buffer::Target target) noexcept
        {
            switch (target)
            {
                case Buffer::Target::UniformBuffer:
                case Buffer::Target::ShaderStorage:
                case Buffer::Target::TransformFeedback:
                case Buffer::Target::AtomicCounter:
                    return true;
                default:
                    return false;
            }
        }
    } // namespace

    Buffer::Buffer(Target target)
        : m_target{ target }
    {
        Context::current().functions().glGenBuffers(1, &m_id);
    }

    Buffer::~Buffer()
    {
        release();
    }

    Buffer::Buffer(Buffer&& other) noexcept
        : m_target{ other.m_target },
          m_id{ other.m_id },
          m_size{ other.m_size }
    {
        other.m_id = 0;
        other.m_size = 0;
    }

    Buffer& Buffer::operator=(Buffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_target = other.m_target;
            m_id = other.m_id;
            m_size = other.m_size;
            other.m_id = 0;
            other.m_size = 0;
        }
        return *this;
    }

    void Buffer::bind() const
    {
        Context::current().functions().glBindBuffer(static_cast<GLenum>(m_target), m_id);
    }

    void Buffer::unbind() const
    {
        Context::current().functions().glBindBuffer(static_cast<GLenum>(m_target), 0);
    }

    void Buffer::setData(const void* data, std::size_t size, Usage usage)
    {
        bind();
        Context::current().functions().glBufferData(
            static_cast<GLenum>(m_target), static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
        m_size = size;
    }

    void Buffer::setSubData(const void* data, std::size_t offset, std::size_t size)
    {
        if (size > 0 && data == nullptr)
        {
            assert(data && "Buffer::setSubData(): data must be non-null when size > 0");
            return;
        }

        if (offset > m_size || size > (m_size - offset))
        {
            assert(
                offset <= m_size && size <= (m_size - offset) &&
                "Buffer::setSubData(): range exceeds current buffer storage");
            return;
        }

        bind();
        Context::current().functions().glBufferSubData(
            static_cast<GLenum>(m_target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
    }

    void Buffer::bind(GLuint bindingPoint) const
    {
        if (!supportsIndexedBindingTarget(m_target))
        {
            assert(
                supportsIndexedBindingTarget(m_target) &&
                "Buffer::bind(bindingPoint): target does not support indexed binding");
            return;
        }

        Context::current().functions().glBindBufferBase(static_cast<GLenum>(m_target), bindingPoint, m_id);
    }

    void Buffer::bind(GLuint bindingPoint, std::size_t offset, std::size_t size) const
    {
        if (!supportsIndexedBindingTarget(m_target))
        {
            assert(
                supportsIndexedBindingTarget(m_target) &&
                "Buffer::bind(bindingPoint, offset, size): target does not support indexed binding");
            return;
        }

        if (offset > m_size || size > (m_size - offset))
        {
            assert(
                offset <= m_size && size <= (m_size - offset) &&
                "Buffer::bind(bindingPoint, offset, size): range exceeds buffer size");
            return;
        }

        Context::current().functions().glBindBufferRange(
            static_cast<GLenum>(m_target),
            bindingPoint,
            m_id,
            static_cast<GLintptr>(offset),
            static_cast<GLsizeiptr>(size));
    }

    void Buffer::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteBuffers(1, &m_id);
            m_id = 0;
            m_size = 0;
        }
    }
} // namespace nfx::graphics::gl
