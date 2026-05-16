#include "nfx/graphics/gl/core/textures/Texture2D.h"

#include "nfx/graphics/gl/core/Context.h"
#include "gl/core/Platform.h"
#include "internal/runtime/Error.h"

#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        bool supportsMemoryUpload(Texture2D::InternalFormat fmt) noexcept
        {
            switch (fmt)
            {
                case Texture2D::InternalFormat::RGBA8:
                case Texture2D::InternalFormat::SRGB8_Alpha:
                    return true;
                default:
                    return false;
            }
        }

        bool isValidInternalFormat(Texture2D::InternalFormat fmt) noexcept
        {
            switch (fmt)
            {
                case Texture2D::InternalFormat::RGBA8:
                case Texture2D::InternalFormat::SRGB8_Alpha:
                case Texture2D::InternalFormat::Depth24:
                case Texture2D::InternalFormat::Depth32F:
                case Texture2D::InternalFormat::RGBA16F:
                case Texture2D::InternalFormat::RGBA32F:
                case Texture2D::InternalFormat::Depth24Stencil8:
                    return true;
                default:
                    return false;
            }
        }

        unsigned int uploadTexture(const unsigned char* data, int width, int height, const Texture2D::Params& params)
        {
            if (!isValidInternalFormat(params.internalFormat))
            {
                internal::runtime::logError(
                    "Texture2D",
                    internal::runtime::ErrorLevel::Error,
                    internal::runtime::ErrorKind::Recoverable,
                    "uploadTexture: invalid internal format");
                return 0;
            }

            const auto& gl = Context::current().functions();

            unsigned int id = 0;
            gl.glGenTextures(1, &id);
            if (id == 0)
            {
                internal::runtime::logError(
                    "Texture2D",
                    internal::runtime::ErrorLevel::Error,
                    internal::runtime::ErrorKind::External,
                    "uploadTexture: glGenTextures failed");
                return 0;
            }

            gl.glBindTexture(TEXTURE_2D, id);

            gl.glTexParameteri(TEXTURE_2D, TEXTURE_MIN_FILTER, static_cast<GLint>(params.minFilter));
            gl.glTexParameteri(TEXTURE_2D, TEXTURE_MAG_FILTER, static_cast<GLint>(params.magFilter));
            gl.glTexParameteri(TEXTURE_2D, TEXTURE_WRAP_S, static_cast<GLint>(params.wrapS));
            gl.glTexParameteri(TEXTURE_2D, TEXTURE_WRAP_T, static_cast<GLint>(params.wrapT));

            GLenum format = RGBA;
            GLenum type = UNSIGNED_BYTE;
            switch (params.internalFormat)
            {
                case Texture2D::InternalFormat::Depth24:
                    format = DEPTH_COMPONENT;
                    type = UNSIGNED_INT;
                    break;
                case Texture2D::InternalFormat::Depth32F:
                    format = DEPTH_COMPONENT;
                    type = FLOAT;
                    break;
                case Texture2D::InternalFormat::Depth24Stencil8:
                    format = DEPTH_STENCIL;
                    type = UNSIGNED_INT_24_8;
                    break;
                case Texture2D::InternalFormat::RGBA16F:
                case Texture2D::InternalFormat::RGBA32F:
                    type = FLOAT;
                    break;
                default:
                    break;
            }

            gl.glTexImage2D(
                TEXTURE_2D, 0, static_cast<GLint>(params.internalFormat), width, height, 0, format, type, data);

            GLenum err = gl.glGetError();
            if (err != GL_NO_ERROR)
            {
                char msg[128];
                std::snprintf(
                    msg, sizeof(msg), "uploadTexture: glTexImage2D failed (0x%04X)", static_cast<unsigned>(err));
                internal::runtime::logError(
                    "Texture2D", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::External, msg);
                gl.glBindTexture(TEXTURE_2D, 0);
                gl.glDeleteTextures(1, &id);
                return 0;
            }

            const bool isDepthOrStencil = params.internalFormat == Texture2D::InternalFormat::Depth24 ||
                                          params.internalFormat == Texture2D::InternalFormat::Depth32F ||
                                          params.internalFormat == Texture2D::InternalFormat::Depth24Stencil8;

            if (params.generateMipmaps && !isDepthOrStencil)
            {
                gl.glGenerateMipmap(TEXTURE_2D);

                err = gl.glGetError();
                if (err != GL_NO_ERROR)
                {
                    char msg[128];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "uploadTexture: glGenerateMipmap failed (0x%04X)",
                        static_cast<unsigned>(err));
                    internal::runtime::logError(
                        "Texture2D", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::External, msg);
                    gl.glBindTexture(TEXTURE_2D, 0);
                    gl.glDeleteTextures(1, &id);
                    return 0;
                }
            }

            gl.glBindTexture(TEXTURE_2D, 0);

            return id;
        }
    } // namespace

    Texture2D::Texture2D(Texture2D&& other) noexcept
        : m_id{ other.m_id },
          m_width{ other.m_width },
          m_height{ other.m_height },
          m_params{ other.m_params }
    {
        other.m_id = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_params = {};
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            m_width = other.m_width;
            m_height = other.m_height;
            m_params = other.m_params;
            other.m_id = 0;
            other.m_width = 0;
            other.m_height = 0;
            other.m_params = {};
        }
        return *this;
    }

    void Texture2D::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteTextures(1, &m_id);
        }

        m_id = 0;
        m_width = 0;
        m_height = 0;
        m_params = {};
    }

    void Texture2D::bind(GLuint unit) const
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(static_cast<int>(unit) < ctx.maxTextureImageUnits() && "Texture2D::bind(): invalid texture unit");
            return;
        }
        const auto& gl = ctx.functions();
        gl.glActiveTexture(TEXTURE0 + unit);
        gl.glBindTexture(TEXTURE_2D, m_id);
    }

    void Texture2D::unbind(GLuint unit)
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(static_cast<int>(unit) < ctx.maxTextureImageUnits() && "Texture2D::unbind(): invalid texture unit");
            return;
        }
        const auto& gl = ctx.functions();
        gl.glActiveTexture(TEXTURE0 + unit);
        gl.glBindTexture(TEXTURE_2D, 0);
    }

    Texture2D Texture2D::fromMemory(const unsigned char* pixels, int width, int height)
    {
        return fromMemory(pixels, width, height, Params{});
    }

    Texture2D Texture2D::fromMemory(const unsigned char* pixels, int width, int height, const Params& params)
    {
        if (!pixels || width <= 0 || height <= 0)
        {
            internal::runtime::logError(
                "Texture2D",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: invalid pixel data");
            return {};
        }

        if (!supportsMemoryUpload(params.internalFormat))
        {
            internal::runtime::logError(
                "Texture2D",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: only InternalFormat::RGBA8 and InternalFormat::SRGB8_Alpha are supported for 8-bit RGBA "
                "uploads");
            return {};
        }

        const unsigned int id = uploadTexture(pixels, width, height, params);
        return Texture2D{ id, width, height, params };
    }

    Texture2D Texture2D::allocate(int width, int height, const Params& params)
    {
        if (width <= 0 || height <= 0)
        {
            internal::runtime::logError(
                "Texture2D",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocate: invalid dimensions");
            return {};
        }

        const unsigned int id = uploadTexture(nullptr, width, height, params);
        return Texture2D{ id, width, height, params };
    }
} // namespace nfx::graphics::gl
