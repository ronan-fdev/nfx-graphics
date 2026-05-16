#include "nfx/graphics/gl/pipeline/RenderTarget.h"

#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        struct DepthAttachment
        {
            Renderbuffer::Format format;
            bool depthStencil = false;
        };

        bool isDepthTextureFormat(Texture2D::InternalFormat format) noexcept
        {
            switch (format)
            {
                case Texture2D::InternalFormat::Depth24:
                case Texture2D::InternalFormat::Depth32F:
                case Texture2D::InternalFormat::Depth24Stencil8:
                    return true;
                default:
                    return false;
            }
        }

        bool isColorTextureFormat(Texture2D::InternalFormat format) noexcept
        {
            switch (format)
            {
                case Texture2D::InternalFormat::RGBA8:
                case Texture2D::InternalFormat::SRGB8_Alpha:
                case Texture2D::InternalFormat::RGBA16F:
                case Texture2D::InternalFormat::RGBA32F:
                    return true;
                default:
                    return false;
            }
        }

        DepthAttachment toRenderbufferDepth(Texture2D::InternalFormat format)
        {
            switch (format)
            {
                case Texture2D::InternalFormat::Depth24:
                    return { Renderbuffer::Format::Depth24, false };
                case Texture2D::InternalFormat::Depth32F:
                    return { Renderbuffer::Format::Depth32F, false };
                case Texture2D::InternalFormat::Depth24Stencil8:
                    return { Renderbuffer::Format::Depth24Stencil8, true };
                default:
                    assert(false && "RenderTarget::toRenderbufferDepth(): unsupported prevalidated depth format");
                    return { Renderbuffer::Format::Depth24, false };
            }
        }
    } // namespace

    void RenderTarget::resize(const Desc& desc)
    {
        if (desc.width <= 0 || desc.height <= 0)
        {
            internal::runtime::logError(
                "RenderTarget",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "resize: invalid dimensions");
            return;
        }

        if (desc.depthOnly && !isDepthTextureFormat(desc.depthFormat))
        {
            internal::runtime::logError(
                "RenderTarget",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "resize: depthOnly requires depthFormat to be Depth24, Depth32F, or Depth24Stencil8");
            return;
        }

        if (!desc.depthOnly && !isColorTextureFormat(desc.colorFormat))
        {
            internal::runtime::logError(
                "RenderTarget",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "resize: colorFormat must be a color texture format");
            return;
        }

        if (!isDepthTextureFormat(desc.depthFormat))
        {
            internal::runtime::logError(
                "RenderTarget",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "resize: depthFormat must be Depth24, Depth32F, or Depth24Stencil8");
            return;
        }

        m_desc = desc;

        const auto& gl = Context::current().functions();

        if (desc.depthOnly)
        {
            m_depthRbo.release();

            // Depth-only: Texture2D depth, no color attachment
            m_texture = Texture2D::allocate(
                desc.width,
                desc.height,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Nearest,
                  .magFilter = Texture2D::Filter::Nearest,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = desc.depthFormat });

            m_framebuffer.bind();
            m_framebuffer.attachColorTexture(0);
            m_framebuffer.attachDepthTexture(m_texture);
            gl.glDrawBuffer(NONE);
            gl.glReadBuffer(NONE);

            if (!m_framebuffer.isComplete())
            {
                char msg[160];
                std::snprintf(
                    msg, sizeof(msg), "resize: depth-only framebuffer incomplete: %s", m_framebuffer.statusString());
                internal::runtime::logError(
                    "RenderTarget",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
            }

            m_framebuffer.unbind();
        }
        else
        {
            // Color + depth renderbuffer
            m_texture = Texture2D::allocate(
                desc.width,
                desc.height,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Linear,
                  .magFilter = Texture2D::Filter::Linear,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = desc.colorFormat });

            const DepthAttachment depth = toRenderbufferDepth(desc.depthFormat);
            m_depthRbo.allocate(depth.format, desc.width, desc.height);

            m_framebuffer.bind();
            m_framebuffer.attachColorTexture(m_texture);
            if (depth.depthStencil)
            {
                m_framebuffer.attachDepthStencilRenderbuffer(m_depthRbo);
            }
            else
            {
                m_framebuffer.attachDepthRenderbuffer(m_depthRbo);
            }
            gl.glDrawBuffer(COLOR_ATTACHMENT0);
            gl.glReadBuffer(COLOR_ATTACHMENT0);

            if (!m_framebuffer.isComplete())
            {
                char msg[160];
                std::snprintf(
                    msg, sizeof(msg), "resize: color framebuffer incomplete: %s", m_framebuffer.statusString());
                internal::runtime::logError(
                    "RenderTarget",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    msg);
            }

            m_framebuffer.unbind();
        }
    }

    void RenderTarget::resize(int width, int height)
    {
        Desc desc = m_desc;
        desc.width = width;
        desc.height = height;
        resize(desc);
    }

    bool RenderTarget::isComplete() const
    {
        const auto& gl = Context::current().functions();

        GLint previousFramebuffer = 0;
        gl.glGetIntegerv(FRAMEBUFFER_BINDING, &previousFramebuffer);

        m_framebuffer.bind();
        const bool complete = m_framebuffer.isComplete();
        gl.glBindFramebuffer(FRAMEBUFFER, static_cast<GLuint>(previousFramebuffer));

        return complete;
    }
} // namespace nfx::graphics::gl
