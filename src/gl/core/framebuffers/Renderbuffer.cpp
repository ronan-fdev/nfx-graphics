#include "nfx/graphics/gl/core/framebuffers/Renderbuffer.h"

#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        bool isValidRenderbufferFormat(Renderbuffer::Format format) noexcept
        {
            switch (format)
            {
                case Renderbuffer::Format::Depth16:
                case Renderbuffer::Format::Depth24:
                case Renderbuffer::Format::Depth32F:
                case Renderbuffer::Format::Depth24Stencil8:
                case Renderbuffer::Format::Depth32FStencil8:
                case Renderbuffer::Format::RGBA8:
                case Renderbuffer::Format::RGBA16F:
                case Renderbuffer::Format::Stencil8:
                    return true;
                default:
                    return false;
            }
        }
    } // namespace

    Renderbuffer::Renderbuffer(Renderbuffer&& other) noexcept
        : m_id{ other.m_id },
          m_width{ other.m_width },
          m_height{ other.m_height },
          m_format{ other.m_format }
    {
        other.m_id = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_format = Format::Depth24;
    }

    Renderbuffer& Renderbuffer::operator=(Renderbuffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            m_width = other.m_width;
            m_height = other.m_height;
            m_format = other.m_format;
            other.m_id = 0;
            other.m_width = 0;
            other.m_height = 0;
            other.m_format = Format::Depth24;
        }
        return *this;
    }

    void Renderbuffer::allocate(Format format, int width, int height)
    {
        if (width <= 0 || height <= 0)
        {
            internal::runtime::logError(
                "Renderbuffer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocate: invalid dimensions");
            return;
        }

        if (!isValidRenderbufferFormat(format))
        {
            internal::runtime::logError(
                "Renderbuffer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocate: invalid format");
            return;
        }

        const auto& gl = Context::current().functions();

        if (m_id == 0)
        {
            gl.glGenRenderbuffers(1, &m_id);
        }

        gl.glBindRenderbuffer(RENDERBUFFER, m_id);
        gl.glRenderbufferStorage(RENDERBUFFER, static_cast<GLenum>(format), width, height);
        gl.glBindRenderbuffer(RENDERBUFFER, 0);

        m_format = format;
        m_width = width;
        m_height = height;
    }

    void Renderbuffer::allocateMultisample(Format format, int width, int height, int samples)
    {
        if (width <= 0 || height <= 0)
        {
            internal::runtime::logError(
                "Renderbuffer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocateMultisample: invalid dimensions");
            return;
        }

        if (samples <= 0)
        {
            internal::runtime::logError(
                "Renderbuffer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocateMultisample: invalid sample count");
            return;
        }

        if (!isValidRenderbufferFormat(format))
        {
            internal::runtime::logError(
                "Renderbuffer",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocateMultisample: invalid format");
            return;
        }

        const auto& gl = Context::current().functions();

        if (m_id == 0)
        {
            gl.glGenRenderbuffers(1, &m_id);
        }

        gl.glBindRenderbuffer(RENDERBUFFER, m_id);
        gl.glRenderbufferStorageMultisample(RENDERBUFFER, samples, static_cast<GLenum>(format), width, height);
        gl.glBindRenderbuffer(RENDERBUFFER, 0);

        m_format = format;
        m_width = width;
        m_height = height;
    }

    void Renderbuffer::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteRenderbuffers(1, &m_id);
        }

        m_id = 0;
        m_width = 0;
        m_height = 0;
        m_format = Format::Depth24;
    }
} // namespace nfx::graphics::gl
