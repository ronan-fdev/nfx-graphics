#include "nfx/graphics/gl/core/buffers/VertexArray.h"

#include "nfx/graphics/gl/core/Context.h"

#include <cassert>

namespace nfx::graphics::gl
{
    VertexArray::VertexArray()
    {
        Context::current().functions().glGenVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray()
    {
        release();
    }

    VertexArray::VertexArray(VertexArray&& other) noexcept
        : m_id{ other.m_id }
    {
        other.m_id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            other.m_id = 0;
        }
        return *this;
    }

    void VertexArray::bind() const
    {
        Context::current().functions().glBindVertexArray(m_id);
    }

    void VertexArray::unbind() const
    {
        Context::current().functions().glBindVertexArray(0);
    }

    void VertexArray::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }
    }

    void VertexArray::setVertexLayout(const VertexLayout& layout)
    {
        setVertexLayout(layout, 0, 0);
    }

    void VertexArray::setVertexLayout(const VertexLayout& layout, GLuint firstLocation, GLuint divisor)
    {
        const auto& ctx = Context::current();
        const auto& gl = ctx.functions();

        if (m_id == 0)
        {
            assert(m_id != 0 && "VertexArray::setVertexLayout(): invalid VAO");
            return;
        }

        GLint previousVao = 0;
        gl.glGetIntegerv(VERTEX_ARRAY_BINDING, &previousVao);
        gl.glBindVertexArray(m_id);

        for (const auto& attr : layout.attributes())
        {
            const GLuint loc = attr.location + firstLocation;
            if (static_cast<int>(loc) >= ctx.maxVertexAttribs())
            {
                assert(
                    static_cast<int>(loc) < ctx.maxVertexAttribs() &&
                    "VertexArray::setVertexLayout(): attribute location exceeds GL_MAX_VERTEX_ATTRIBS");
                gl.glBindVertexArray(static_cast<GLuint>(previousVao));
                return;
            }
        }

        for (const auto& attr : layout.attributes())
        {
            const GLuint loc = attr.location + firstLocation;
            gl.glEnableVertexAttribArray(loc);
            if (VertexLayout::isInteger(attr.type))
            {
                gl.glVertexAttribIPointer(
                    loc,
                    VertexLayout::count(attr.type),
                    VertexLayout::type(attr.type),
                    static_cast<GLsizei>(layout.stride()),
                    reinterpret_cast<void*>(attr.offset));
            }
            else
            {
                gl.glVertexAttribPointer(
                    loc,
                    VertexLayout::count(attr.type),
                    VertexLayout::type(attr.type),
                    attr.normalized,
                    static_cast<GLsizei>(layout.stride()),
                    reinterpret_cast<void*>(attr.offset));
            }
            if (divisor > 0)
            {
                gl.glVertexAttribDivisor(loc, divisor);
            }
        }

        gl.glBindVertexArray(static_cast<GLuint>(previousVao));
    }
} // namespace nfx::graphics::gl
