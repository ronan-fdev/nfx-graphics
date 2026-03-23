#pragma once

/**
 * \file Renderbuffer.h
 * \brief Declares a RAII wrapper for OpenGL renderbuffer storage used by framebuffers.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \class Renderbuffer
     * \brief Owns an OpenGL renderbuffer object used for offscreen attachments.
     */
    class Renderbuffer final
    {
    public:
        // clang-format off
        /**
         * \brief Enumerates the supported renderbuffer storage formats.
         */
        enum class Format : unsigned int
        {
            Depth16          = DEPTH_COMPONENT16,
            Depth24          = DEPTH_COMPONENT24,
            Depth32F         = DEPTH_COMPONENT32F,
            Depth24Stencil8  = DEPTH24_STENCIL8,
            Depth32FStencil8 = DEPTH32F_STENCIL8,
            RGBA8            = RGBA8_EXT,
            RGBA16F          = RGBA16F,
            Stencil8         = STENCIL_INDEX8
        };
        // clang-format on

        Renderbuffer() = default;

        /**
         * \brief Releases the underlying OpenGL renderbuffer object.
         */
        ~Renderbuffer() { release(); }

        Renderbuffer(const Renderbuffer&) = delete;
        Renderbuffer& operator=(const Renderbuffer&) = delete;

        Renderbuffer(Renderbuffer&& other) noexcept;
        Renderbuffer& operator=(Renderbuffer&& other) noexcept;

        /**
         * \brief Allocates renderbuffer storage for a single-sampled attachment.
         * \param format Storage format to allocate.
         * \param width Width in pixels.
         * \param height Height in pixels.
         *
         * Width and height must be positive. Unsupported format values are rejected.
         */
        void allocate(Format format, int width, int height);

        /**
         * \brief Allocates renderbuffer storage for a multisampled attachment.
         * \param format Storage format to allocate.
         * \param width Width in pixels.
         * \param height Height in pixels.
         * \param samples Number of samples per pixel.
         *
         * Width, height, and samples must be positive. Unsupported format values are rejected.
         */
        void allocateMultisample(Format format, int width, int height, int samples);

        /**
         * \brief Releases the renderbuffer storage and resets the object to an empty state.
         */
        void release();

        /**
         * \brief Returns the OpenGL renderbuffer object id owned by this wrapper.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL renderbuffer object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the currently allocated renderbuffer width.
         * \return Width in pixels, or 0 when unallocated.
         */
        [[nodiscard]] int width() const noexcept { return m_width; }

        /**
         * \brief Returns the currently allocated renderbuffer height.
         * \return Height in pixels, or 0 when unallocated.
         */
        [[nodiscard]] int height() const noexcept { return m_height; }

        /**
         * \brief Returns the currently configured storage format.
         * \return Renderbuffer storage format value.
         */
        [[nodiscard]] Format format() const noexcept { return m_format; }

    private:
        GLuint m_id = 0;
        int m_width = 0;
        int m_height = 0;
        Format m_format = Format::Depth24;
    };
} // namespace nfx::graphics::gl
