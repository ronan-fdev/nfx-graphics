#pragma once

/**
 * \file TextureCube.h
 * \brief Declares a RAII wrapper for OpenGL cube map textures and their sampling parameters.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \class TextureCube
     * \brief Owns an OpenGL cube map texture object and manages its storage and sampling parameters.
     */
    class TextureCube final
    {
    public:
        // clang-format off
        /**
         * \brief Enumerates the supported minification and magnification filters.
         */
        enum class Filter : unsigned int
        {
            Nearest            = NEAREST,
            Linear             = LINEAR,
            LinearMipmapLinear = LINEAR_MIPMAP_LINEAR

        };

        /**
         * \brief Enumerates the supported texture coordinate wrapping modes for cube maps.
         */
        enum class Wrap : unsigned int
        {
            Repeat         = REPEAT,
            ClampToEdge    = CLAMP_TO_EDGE,
            ClampToBorder  = CLAMP_TO_BORDER,
            MirroredRepeat = MIRRORED_REPEAT
        };

        /**
         * \brief Enumerates the supported internal storage formats for the cube map.
         */
        enum class InternalFormat : unsigned int
        {
            RGBA8       = RGBA8_EXT,
            SRGB8_Alpha = SRGB8_ALPHA8,
            RGBA16F     = RGBA16F,
            RGBA32F     = RGBA32F,
            Depth24     = DEPTH_COMPONENT24,
            Depth32F    = DEPTH_COMPONENT32F
        };

        /**
         * \brief Groups the sampling and storage parameters used to create the cube map.
         */
        struct Params
        {
            bool generateMipmaps          = false;
            int mipLevels                 = 1;
            Filter minFilter              = Filter::Linear;
            Filter magFilter              = Filter::Linear;
            Wrap wrapS                    = Wrap::ClampToEdge;
            Wrap wrapT                    = Wrap::ClampToEdge;
            Wrap wrapR                    = Wrap::ClampToEdge;
            InternalFormat internalFormat = InternalFormat::RGBA8;
        };

        enum class Face : int
        {
            Right  = 0, // +X
            Left   = 1, // -X
            Top    = 2, // +Y
            Bottom = 3, // -Y
            Front  = 4, // +Z
            Back   = 5  // -Z
        };
        // clang-format on

        /**
         * \brief Describes one 8-bit RGBA face upload for a cube map.
         *
         * Faces are ordered as +X, -X, +Y, -Y, +Z, -Z when passed to fromMemory().
         * Each face MUST provide square 8-bit RGBA pixel data.
         */
        struct FaceData
        {
            const unsigned char* pixels = nullptr;
            int width = 0;
            int height = 0;
        };

        TextureCube() = default;

        /**
         * \brief Releases the underlying OpenGL cube map texture object.
         */
        ~TextureCube() { release(); }

        TextureCube(const TextureCube&) = delete;
        TextureCube& operator=(const TextureCube&) = delete;

        TextureCube(TextureCube&& other) noexcept;
        TextureCube& operator=(TextureCube&& other) noexcept;

        /**
         * \brief Creates a cube map from six pre-loaded faces using default parameters.
         * \param faces Array of six face descriptions ordered as +X, -X, +Y, -Y, +Z, -Z.
         *
         * Faces MUST be square, share identical dimensions, and contain 8-bit RGBA pixels.
         */
        [[nodiscard]] static TextureCube fromMemory(const FaceData faces[6]);

        /**
         * \brief Creates a cube map from six pre-loaded faces.
         * \param faces Array of six face descriptions ordered as +X, -X, +Y, -Y, +Z, -Z.
         * \param params Sampling and storage parameters used to create the cube map.
         *
         * Faces MUST be square, share identical dimensions, and contain 8-bit RGBA pixels.
         * This upload path currently supports InternalFormat::RGBA8 and InternalFormat::SRGB8_Alpha.
         */
        [[nodiscard]] static TextureCube fromMemory(const FaceData faces[6], const Params& params);

        /**
         * \brief Allocates an empty cube map with square faces.
         * \param size Face width and height in pixels.
         * \param params Sampling and storage parameters used to create the cube map.
         */
        [[nodiscard]] static TextureCube allocate(int size, const Params& params);

        /**
         * \brief Releases the texture object and resets the wrapper to an empty state.
         */
        void release();

        /**
         * \brief Binds the cube map to a texture unit.
         * \param unit Zero-based texture unit index.
         */
        void bind(GLuint unit = 0) const;

        /**
         * \brief Unbinds any cube map texture from a texture unit.
         * \param unit Zero-based texture unit index.
         */
        static void unbind(GLuint unit = 0);

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL cube map texture object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the OpenGL cube map texture object id owned by this wrapper.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Returns the cube face size in pixels.
         * \return Width and height of each square face, or 0 when unallocated.
         */
        [[nodiscard]] int size() const noexcept { return m_size; }

        /**
         * \brief Returns the sampling and storage parameters used to create this cube map.
         * \return Immutable reference to the stored cube map parameter set.
         */
        [[nodiscard]] const Params& params() const noexcept { return m_params; }

    private:
        TextureCube(GLuint id, int size, const Params& params)
            : m_id{ id },
              m_size{ size },
              m_params{ params }
        {}

        GLuint m_id = 0;
        int m_size = 0;
        Params m_params = {};
    };
} // namespace nfx::graphics::gl
