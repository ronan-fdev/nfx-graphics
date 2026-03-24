#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"

#include "nfx/graphics/gl/core/Context.h"

#include <cassert>

namespace nfx::graphics::gl
{
    Framebuffer::Framebuffer()
    {
        Context::current().functions().glGenFramebuffers(1, &m_id);
    }

    Framebuffer::~Framebuffer()
    {
        release();
    }

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept
        : m_id{ other.m_id }
    {
        other.m_id = 0;
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            other.m_id = 0;
        }
        return *this;
    }

    void Framebuffer::bind() const
    {
        Context::current().functions().glBindFramebuffer(FRAMEBUFFER, m_id);
    }

    void Framebuffer::unbind() const
    {
        Context::current().functions().glBindFramebuffer(FRAMEBUFFER, 0);
    }

    void Framebuffer::attachColorTexture(GLuint textureId, int attachmentIndex)
    {
        const auto& ctx = Context::current();
        if (attachmentIndex < 0 || attachmentIndex >= ctx.maxColorAttachments())
        {
            assert(
                attachmentIndex >= 0 && attachmentIndex < ctx.maxColorAttachments() &&
                "Framebuffer::attachColorTexture(): attachmentIndex out of GL_MAX_COLOR_ATTACHMENTS range");
            return;
        }

        ctx.functions().glFramebufferTexture2D(
            FRAMEBUFFER,
            static_cast<GLenum>(COLOR_ATTACHMENT0 + static_cast<GLenum>(attachmentIndex)),
            TEXTURE_2D,
            textureId,
            0);
    }

    void Framebuffer::attachDepthTexture(GLuint textureId)
    {
        Context::current().functions().glFramebufferTexture2D(FRAMEBUFFER, DEPTH_ATTACHMENT, TEXTURE_2D, textureId, 0);
    }

    void Framebuffer::attachStencilTexture(GLuint textureId)
    {
        Context::current().functions().glFramebufferTexture2D(
            FRAMEBUFFER, STENCIL_ATTACHMENT, TEXTURE_2D, textureId, 0);
    }

    void Framebuffer::attachDepthStencilTexture(GLuint textureId)
    {
        Context::current().functions().glFramebufferTexture2D(
            FRAMEBUFFER, DEPTH_STENCIL_ATTACHMENT, TEXTURE_2D, textureId, 0);
    }

    void Framebuffer::attachDepthCubeFace(GLuint cubeTexId, int face)
    {
        if (face < 0 || face >= 6)
        {
            assert(face >= 0 && face < 6 && "Framebuffer::attachDepthCubeFace(): face must be in [0, 5]");
            return;
        }

        Context::current().functions().glFramebufferTexture2D(
            FRAMEBUFFER, DEPTH_ATTACHMENT, static_cast<GLenum>(TEXTURE_CUBE_MAP_POSITIVE_X + face), cubeTexId, 0);
    }

    void Framebuffer::attachDepthCubemap(GLuint cubeTexId)
    {
        Context::current().functions().glFramebufferTexture(FRAMEBUFFER, DEPTH_ATTACHMENT, cubeTexId, 0);
    }

    void Framebuffer::attachDepthRenderbuffer(GLuint renderbufferId)
    {
        Context::current().functions().glFramebufferRenderbuffer(
            FRAMEBUFFER, DEPTH_ATTACHMENT, RENDERBUFFER, renderbufferId);
    }

    void Framebuffer::attachDepthStencilRenderbuffer(GLuint renderbufferId)
    {
        Context::current().functions().glFramebufferRenderbuffer(
            FRAMEBUFFER, DEPTH_STENCIL_ATTACHMENT, RENDERBUFFER, renderbufferId);
    }

    void Framebuffer::attachColorTexture(const Texture2D& texture, int attachmentIndex)
    {
        attachColorTexture(texture.id(), attachmentIndex);
    }

    void Framebuffer::attachDepthTexture(const Texture2D& texture)
    {
        attachDepthTexture(texture.id());
    }

    void Framebuffer::attachStencilTexture(const Texture2D& texture)
    {
        attachStencilTexture(texture.id());
    }

    void Framebuffer::attachDepthStencilTexture(const Texture2D& texture)
    {
        attachDepthStencilTexture(texture.id());
    }

    void Framebuffer::attachDepthRenderbuffer(const Renderbuffer& renderbuffer)
    {
        attachDepthRenderbuffer(renderbuffer.id());
    }

    void Framebuffer::attachDepthStencilRenderbuffer(const Renderbuffer& renderbuffer)
    {
        attachDepthStencilRenderbuffer(renderbuffer.id());
    }

    void Framebuffer::attachDepthCubeFace(const TextureCube& texture, TextureCube::Face face)
    {
        attachDepthCubeFace(texture.id(), static_cast<int>(face));
    }

    void Framebuffer::attachDepthCubemap(const TextureCube& texture)
    {
        attachDepthCubemap(texture.id());
    }

    bool Framebuffer::isComplete() const
    {
        return checkStatus() == FRAMEBUFFER_COMPLETE;
    }

    const char* Framebuffer::statusString() const
    {
        switch (checkStatus())
        {
            case FRAMEBUFFER_COMPLETE:
                return "Complete";
            case FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                return "Incomplete attachment";
            case FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                return "Missing attachment";
            case FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                return "Incomplete draw buffer";
            case FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                return "Incomplete read buffer";
            case FRAMEBUFFER_UNSUPPORTED:
                return "Unsupported";
            case FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                return "Incomplete multisample";
            case FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                return "Incomplete layer targets";
            default:
                return "Unknown error";
        }
    }

    void Framebuffer::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteFramebuffers(1, &m_id);
            m_id = 0;
        }
    }

    GLenum Framebuffer::checkStatus() const
    {
        return Context::current().functions().glCheckFramebufferStatus(FRAMEBUFFER);
    }
} // namespace nfx::graphics::gl
