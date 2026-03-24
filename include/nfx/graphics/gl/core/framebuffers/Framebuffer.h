#pragma once

/**
 * \file Framebuffer.h
 * \brief Declares a RAII wrapper for OpenGL framebuffer objects and their attachments.
 */

#include "nfx/graphics/gl/core/textures/Texture2D.h"
#include "nfx/graphics/gl/core/textures/TextureCube.h"
#include "Renderbuffer.h"

namespace nfx::graphics::gl
{
    /**
     * \class Framebuffer
     * \brief Owns an OpenGL framebuffer object and manages its texture and renderbuffer attachments.
     *
     * This wrapper intentionally exposes low-level OpenGL behavior:
     * attachment and status methods operate on the framebuffer currently bound to GL_FRAMEBUFFER.
     * Call bind() on this object before using them.
     */
    class Framebuffer final
    {
    public:
        /**
         * \brief Creates a new OpenGL framebuffer object.
         */
        Framebuffer();

        /**
         * \brief Releases the underlying OpenGL framebuffer object.
         */
        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        Framebuffer(Framebuffer&& other) noexcept;
        Framebuffer& operator=(Framebuffer&& other) noexcept;

        /**
         * \brief Binds the framebuffer object.
         */
        void bind() const;

        /**
         * \brief Unbinds the current framebuffer and restores the default framebuffer.
         */
        void unbind() const;

        /**
         * \brief Attaches a 2D texture object to a color attachment slot.
         * \param textureId OpenGL texture object id.
         * \param attachmentIndex Zero-based color attachment index.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachColorTexture(GLuint textureId, int attachmentIndex = 0);

        /**
         * \brief Attaches a 2D texture object to the depth attachment.
         * \param textureId OpenGL texture object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthTexture(GLuint textureId);

        /**
         * \brief Attaches a 2D texture object to the stencil attachment.
         * \param textureId OpenGL texture object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachStencilTexture(GLuint textureId);

        /**
         * \brief Attaches a 2D texture object to the combined depth-stencil attachment.
         * \param textureId OpenGL texture object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthStencilTexture(GLuint textureId);

        /**
         * \brief Attaches a renderbuffer object to the depth attachment.
         * \param renderbufferId OpenGL renderbuffer object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthRenderbuffer(GLuint renderbufferId);

        /**
         * \brief Attaches a renderbuffer object to the combined depth-stencil attachment.
         * \param renderbufferId OpenGL renderbuffer object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthStencilRenderbuffer(GLuint renderbufferId);

        /**
         * \brief Attaches one face of a cube map texture to the depth attachment.
         * \param cubeTexId OpenGL cube map texture object id.
         * \param face Face index in [0,5] mapped to +X, -X, +Y, -Y, +Z, -Z.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthCubeFace(GLuint cubeTexId, int face);

        /**
         * \brief Attaches all faces of a cube map texture to the depth attachment for layered rendering.
         *
         * Required for geometry-shader-based cube map rendering where gl_Layer selects the face.
         * \param cubeTexId OpenGL cube map texture object id.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthCubemap(GLuint cubeTexId);

        /**
         * \brief Attaches a Texture2D wrapper to a color attachment slot.
         * \param texture Texture wrapper owning the OpenGL texture object.
         * \param attachmentIndex Zero-based color attachment index.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachColorTexture(const Texture2D& texture, int attachmentIndex = 0);

        /**
         * \brief Attaches a Texture2D wrapper to the depth attachment.
         * \param texture Texture wrapper owning the OpenGL texture object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthTexture(const Texture2D& texture);

        /**
         * \brief Attaches a Texture2D wrapper to the stencil attachment.
         * \param texture Texture wrapper owning the OpenGL texture object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachStencilTexture(const Texture2D& texture);

        /**
         * \brief Attaches a Texture2D wrapper to the combined depth-stencil attachment.
         * \param texture Texture wrapper owning the OpenGL texture object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthStencilTexture(const Texture2D& texture);

        /**
         * \brief Attaches a Renderbuffer wrapper to the depth attachment.
         * \param renderbuffer Renderbuffer wrapper owning the OpenGL renderbuffer object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthRenderbuffer(const Renderbuffer& renderbuffer);

        /**
         * \brief Attaches a Renderbuffer wrapper to the combined depth-stencil attachment.
         * \param renderbuffer Renderbuffer wrapper owning the OpenGL renderbuffer object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthStencilRenderbuffer(const Renderbuffer& renderbuffer);

        /**
         * \brief Attaches one face of a TextureCube wrapper to the depth attachment.
         * \param texture Cube map texture wrapper owning the OpenGL texture object.
         * \param face Face to attach.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthCubeFace(const TextureCube& texture, TextureCube::Face face);

        /**
         * \brief Attaches all faces of a TextureCube wrapper to the depth attachment for layered rendering.
         *
         * Required for geometry-shader-based cube map rendering where gl_Layer selects the face.
         * \param texture Cube map texture wrapper owning the OpenGL texture object.
         * \pre This framebuffer must be currently bound with bind().
         */
        void attachDepthCubemap(const TextureCube& texture);

        /**
         * \brief Returns whether the framebuffer is complete for rendering.
         * \pre This framebuffer must be currently bound with bind().
         */
        [[nodiscard]] bool isComplete() const;

        /**
         * \brief Returns a human-readable string for the current framebuffer status.
         * \pre This framebuffer must be currently bound with bind().
         */
        [[nodiscard]] const char* statusString() const;

        /**
         * \brief Returns the OpenGL framebuffer object id owned by this wrapper.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL framebuffer object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

    private:
        [[nodiscard]] GLenum checkStatus() const;

        void release();

        GLuint m_id = 0;
    };
} // namespace nfx::graphics::gl
