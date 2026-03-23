#pragma once

/**
 * \file RenderTarget.h
 * \brief Declares a framebuffer wrapper owning a single output texture and optional depth storage.
 */

#include "nfx/graphics/gl/core/framebuffers/Framebuffer.h"
#include "nfx/graphics/gl/core/framebuffers/Renderbuffer.h"
#include "nfx/graphics/gl/core/textures/Texture2D.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Framebuffer wrapper with a single output texture, either color or depth.
     */
    class RenderTarget
    {
    public:
        /**
         * \brief Describes the texture formats and dimensions of the render target.
         */
        struct Desc
        {
            int width = 1280;       ///< Target width in pixels
            int height = 720;       ///< Target height in pixels
            bool depthOnly = false; ///< When true, creates a depth-only target
            Texture2D::InternalFormat colorFormat =
                Texture2D::InternalFormat::RGBA8; ///< Internal format of the color texture when depthOnly is false.
                                                  ///< Color targets require a non-depth texture format
            Texture2D::InternalFormat depthFormat =
                Texture2D::InternalFormat::Depth24; ///< Internal format of the depth texture or depth attachment. Must
                                                    ///< be Depth24, Depth32F, or Depth24Stencil8
        };

        /**
         * \brief Constructs an empty render target.
         *
         * \pre An OpenGL context must be current.
         * Use std::optional<RenderTarget> to defer construction until after context initialization.
         */
        RenderTarget() = default;

        /**
         * \brief Creates and allocates a render target from a full descriptor.
         * \param desc Render target specification.
         * \pre An OpenGL context must be current.
         */
        explicit RenderTarget(const Desc& desc) { resize(desc); }

        /**
         * \brief Creates and allocates a default color render target with the given size.
         * \param width Target width in pixels.
         * \param height Target height in pixels.
         * \pre An OpenGL context must be current.
         */
        RenderTarget(int width, int height) { resize({ width, height }); }

        RenderTarget(const RenderTarget&) = delete;
        RenderTarget& operator=(const RenderTarget&) = delete;

        RenderTarget(RenderTarget&&) noexcept = default;
        RenderTarget& operator=(RenderTarget&&) noexcept = default;

        /**
         * \brief Allocates or resizes the render target using a full descriptor.
         * \param desc Render target specification.
         */
        void resize(const Desc& desc);

        /**
         * \brief Allocates or resizes the render target keeping default formats.
         * \param width Target width in pixels.
         * \param height Target height in pixels.
         */
        void resize(int width, int height);

        /**
         * \brief Binds the framebuffer owned by the render target.
         */
        void bind() const { m_framebuffer.bind(); }

        /**
         * \brief Unbinds the framebuffer and restores the default framebuffer.
         */
        void unbind() const { m_framebuffer.unbind(); }

        /**
         * \brief Returns the owned output texture.
         */
        [[nodiscard]] const Texture2D& texture() const noexcept { return m_texture; }

        /**
         * \brief Returns the owned output texture.
         */
        [[nodiscard]] Texture2D& texture() noexcept { return m_texture; }

        /**
         * \brief Returns the owned framebuffer.
         */
        [[nodiscard]] const Framebuffer& framebuffer() const noexcept { return m_framebuffer; }

        /**
         * \brief Returns the current render target specification.
         */
        [[nodiscard]] const Desc& specification() const noexcept { return m_desc; }

        /**
         * \brief Returns whether the framebuffer object exists.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_framebuffer.isValid(); }

        /**
         * \brief Returns whether the framebuffer is complete.
         */
        [[nodiscard]] bool isComplete() const;

        /**
         * \brief Returns the target width in pixels.
         */
        [[nodiscard]] int width() const noexcept { return m_desc.width; }

        /**
         * \brief Returns the target height in pixels.
         */
        [[nodiscard]] int height() const noexcept { return m_desc.height; }

    private:
        Desc m_desc;
        Framebuffer m_framebuffer;
        Texture2D m_texture;
        Renderbuffer m_depthRbo;
    };
} // namespace nfx::graphics::gl
