#pragma once

/**
 * \file Texture2D.h
 * \brief Declares a RAII wrapper for OpenGL 2D textures and their sampling parameters.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \class Texture2D
     * \brief Owns an OpenGL 2D texture object and manages its storage and sampling parameters.
     */
    class Texture2D final
    {
    public:
        // clang-format off
        /**
         * \brief Enumerates the supported minification and magnification filters.
         */
        enum class Filter : unsigned int
        {
            Nearest              = NEAREST,
            Linear               = LINEAR,
            NearestMipmapNearest = NEAREST_MIPMAP_NEAREST,
            LinearMipmapNearest  = LINEAR_MIPMAP_NEAREST,
            NearestMipmapLinear  = NEAREST_MIPMAP_LINEAR,
            LinearMipmapLinear   = LINEAR_MIPMAP_LINEAR
        };

        /**
         * \brief Enumerates the supported texture coordinate wrapping modes.
         */
        enum class Wrap : unsigned int
        {
            Repeat         = REPEAT,
            ClampToEdge    = CLAMP_TO_EDGE,
            ClampToBorder  = CLAMP_TO_BORDER,
            MirroredRepeat = MIRRORED_REPEAT
        };

        /**
         * \brief Enumerates the supported internal storage formats for the texture.
         */
        enum class InternalFormat : unsigned int
        {
            RGBA8           = RGBA8_EXT,
            SRGB8_Alpha     = SRGB8_ALPHA8,
            Depth24         = DEPTH_COMPONENT24,
            Depth32F        = DEPTH_COMPONENT32F,
            RGBA16F         = RGBA16F,
            RGBA32F         = RGBA32F,
            Depth24Stencil8 = DEPTH24_STENCIL8
        };

        /**
         * \brief Groups the sampling and storage parameters used to create the texture.
         */
        struct Params
        {
            bool generateMipmaps          = true;
            Filter minFilter              = Filter::LinearMipmapLinear;
            Filter magFilter              = Filter::Linear;
            Wrap wrapS                    = Wrap::ClampToEdge;
            Wrap wrapT                    = Wrap::ClampToEdge;
            InternalFormat internalFormat = InternalFormat::RGBA8;
        };
        // clang-format on

        /**
         * \brief Describes a block of pixels together with the parameters used to create a texture.
         */
        struct Data
        {
            const unsigned char* pixels = nullptr;
            int width = 0;
            int height = 0;
            Params params;
        };

        Texture2D() = default;

        /**
         * \brief Releases the underlying OpenGL texture object.
         */
        ~Texture2D() { release(); }

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&& other) noexcept;
        Texture2D& operator=(Texture2D&& other) noexcept;

        /**
         * \brief Creates a texture from raw pixel memory using default parameters.
         * \param pixels Pointer to the source pixel data.
         * \param width Texture width in pixels.
         * \param height Texture height in pixels.
         *
         * This upload path expects 8-bit RGBA source pixels and currently uses InternalFormat::RGBA8 defaults.
         */
        [[nodiscard]] static Texture2D fromMemory(const unsigned char* pixels, int width, int height);

        /**
         * \brief Creates a texture from raw pixel memory using explicit creation parameters.
         * \param pixels Pointer to the source pixel data.
         * \param width Texture width in pixels.
         * \param height Texture height in pixels.
         * \param params Sampling and storage parameters used to create the texture.
         *
         * This upload path expects 8-bit RGBA source pixels and currently supports only
         * InternalFormat::RGBA8 and InternalFormat::SRGB8_Alpha.
         */
        [[nodiscard]] static Texture2D fromMemory(
            const unsigned char* pixels, int width, int height, const Params& params);

        /**
         * \brief Allocates an empty texture with the requested size and parameters.
         * \param width Texture width in pixels.
         * \param height Texture height in pixels.
         * \param params Sampling and storage parameters used to create the texture.
         */
        [[nodiscard]] static Texture2D allocate(int width, int height, const Params& params);

        /**
         * \brief Releases the texture object and resets the wrapper to an empty state.
         */
        void release();

        /**
         * \brief Binds the texture to a texture unit.
         * \param unit Zero-based texture unit index.
         */
        void bind(GLuint unit = 0) const;

        /**
         * \brief Unbinds any 2D texture from a texture unit.
         * \param unit Zero-based texture unit index.
         */
        static void unbind(GLuint unit = 0);

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL texture object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the OpenGL object id owned by this texture.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Returns the texture width.
         * \return Width in pixels.
         */
        [[nodiscard]] int width() const noexcept { return m_width; }

        /**
         * \brief Returns the texture height.
         * \return Height in pixels.
         */
        [[nodiscard]] int height() const noexcept { return m_height; }

        /**
         * \brief Returns the creation parameters currently associated with this texture.
         * \return Reference to the parameter set stored in the wrapper.
         */
        [[nodiscard]] const Params& params() const noexcept { return m_params; }

    private:
        Texture2D(unsigned int id, int width, int height, const Params& params)
            : m_id{ id },
              m_width{ width },
              m_height{ height },
              m_params{ params }
        {}

        unsigned int m_id = 0;
        int m_width = 0;
        int m_height = 0;
        Params m_params = {};
    };
} // namespace nfx::graphics::gl
