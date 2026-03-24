#pragma once

/**
 * \file Sampler.h
 * \brief Declares a RAII wrapper for OpenGL sampler objects.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \class Sampler
     * \brief Owns an OpenGL sampler object and manages sampling state independently from textures.
     */
    class Sampler final
    {
    public:
        // clang-format off
        enum class Filter : unsigned int
        {
            Nearest              = NEAREST,
            Linear               = LINEAR,
            NearestMipmapNearest = NEAREST_MIPMAP_NEAREST,
            LinearMipmapNearest  = LINEAR_MIPMAP_NEAREST,
            NearestMipmapLinear  = NEAREST_MIPMAP_LINEAR,
            LinearMipmapLinear   = LINEAR_MIPMAP_LINEAR
        };

        enum class Wrap : unsigned int
        {
            Repeat         = REPEAT,
            ClampToEdge    = CLAMP_TO_EDGE,
            ClampToBorder  = CLAMP_TO_BORDER,
            MirroredRepeat = MIRRORED_REPEAT
        };

        enum class CompareMode : unsigned int
        {
            None            = NONE,
            CompareRefToTex = COMPARE_REF_TO_TEXTURE
        };

        enum class CompareFunc : unsigned int
        {
            Less     = LESS,
            Lequal   = LEQUAL,
            Greater  = GREATER,
            Gequal   = GEQUAL,
            Equal    = EQUAL,
            NotEqual = NOTEQUAL,
            Always   = ALWAYS,
            Never    = NEVER
        };

        struct Params
        {
            Filter minFilter        = Filter::Linear;
            Filter magFilter        = Filter::Linear; ///< Must be Nearest or Linear (mipmap filters are invalid)
            Wrap wrapS              = Wrap::ClampToEdge;
            Wrap wrapT              = Wrap::ClampToEdge;
            Wrap wrapR              = Wrap::ClampToEdge;
            CompareMode compareMode = CompareMode::None;
            CompareFunc compareFunc = CompareFunc::Lequal;
        };
        // clang-format on

        Sampler() = default;
        ~Sampler() { release(); }

        Sampler(const Sampler&) = delete;
        Sampler& operator=(const Sampler&) = delete;

        Sampler(Sampler&& other) noexcept;
        Sampler& operator=(Sampler&& other) noexcept;

        /**
         * \brief Creates a sampler object using default sampling parameters.
         */
        [[nodiscard]] static Sampler create();

        /**
         * \brief Creates a sampler object using explicit sampling parameters.
         * \param params Sampling parameters applied to the created sampler.
         *
         * params.magFilter must be Filter::Nearest or Filter::Linear.
         */
        [[nodiscard]] static Sampler create(const Params& params);

        /**
         * \brief Releases the sampler object and resets the wrapper to an empty state.
         */
        void release();

        /**
         * \brief Binds the sampler to a texture unit.
         * \param unit Zero-based texture unit index.
         */
        void bind(GLuint unit) const;

        /**
         * \brief Unbinds any sampler object from a texture unit.
         * \param unit Zero-based texture unit index.
         */
        static void unbind(GLuint unit);

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL sampler object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the OpenGL sampler object id owned by this wrapper.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Returns the sampling parameters used to create this sampler.
         * \return Immutable reference to the stored sampler parameter set.
         */
        [[nodiscard]] const Params& params() const noexcept { return m_params; }

    private:
        Sampler(GLuint id, const Params& params)
            : m_id{ id },
              m_params{ params }
        {}

        GLuint m_id = 0;
        Params m_params = {};
    };
} // namespace nfx::graphics::gl
