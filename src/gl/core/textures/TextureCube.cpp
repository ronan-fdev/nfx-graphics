#include "nfx/graphics/gl/core/textures/TextureCube.h"

#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <algorithm>
#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        bool supportsFaceUpload(TextureCube::InternalFormat internalFormat) noexcept
        {
            return internalFormat == TextureCube::InternalFormat::RGBA8 ||
                   internalFormat == TextureCube::InternalFormat::SRGB8_Alpha;
        }

        void selectUploadFormat(TextureCube::InternalFormat internalFormat, GLenum& format, GLenum& type)
        {
            format = RGBA;
            type = UNSIGNED_BYTE;

            switch (internalFormat)
            {
                case TextureCube::InternalFormat::Depth24:
                    format = DEPTH_COMPONENT;
                    type = UNSIGNED_INT;
                    break;
                case TextureCube::InternalFormat::Depth32F:
                    format = DEPTH_COMPONENT;
                    type = FLOAT;
                    break;
                case TextureCube::InternalFormat::RGBA16F:
                case TextureCube::InternalFormat::RGBA32F:
                    type = FLOAT;
                    break;
                default:
                    break;
            }
        }
    } // namespace

    TextureCube::TextureCube(TextureCube&& other) noexcept
        : m_id{ other.m_id },
          m_size{ other.m_size },
          m_params{ other.m_params }
    {
        other.m_id = 0;
        other.m_size = 0;
    }

    TextureCube& TextureCube::operator=(TextureCube&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            m_size = other.m_size;
            m_params = other.m_params;
            other.m_id = 0;
            other.m_size = 0;
        }
        return *this;
    }

    void TextureCube::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteTextures(1, &m_id);
            m_id = 0;
        }
        m_size = 0;
    }

    TextureCube TextureCube::allocate(int size, const Params& params)
    {
        if (size <= 0)
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocate: invalid size");
            return {};
        }
        if (params.mipLevels <= 0)
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "allocate: mipLevels must be positive");
            return {};
        }

        const auto& gl = Context::current().functions();

        const bool isDepth =
            (params.internalFormat == InternalFormat::Depth24 || params.internalFormat == InternalFormat::Depth32F);
        const int maxMipLevels = [&]() {
            int levels = 1;
            for (int levelSize = size; levelSize > 1; levelSize >>= 1)
            {
                ++levels;
            }
            return levels;
        }();
        const int explicitMipLevels = std::min(params.mipLevels, maxMipLevels);
        const int storageMipLevels = (params.generateMipmaps && !isDepth) ? 1 : explicitMipLevels;
        const GLint minFilter = (params.generateMipmaps && !isDepth && params.minFilter == Filter::Linear)
                                    ? static_cast<GLint>(LINEAR_MIPMAP_LINEAR)
                                    : static_cast<GLint>(params.minFilter);

        if (explicitMipLevels != params.mipLevels)
        {
            char msg[160];
            std::snprintf(
                msg,
                sizeof(msg),
                "allocate: clamping mipLevels from %d to %d for size %d",
                params.mipLevels,
                explicitMipLevels,
                size);
            internal::runtime::logError(
                "TextureCube", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
        }

        GLuint id = 0;
        gl.glGenTextures(1, &id);
        gl.glBindTexture(TEXTURE_CUBE_MAP, id);

        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_MIN_FILTER, minFilter);
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_MAG_FILTER, static_cast<GLint>(params.magFilter));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_S, static_cast<GLint>(params.wrapS));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_T, static_cast<GLint>(params.wrapT));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_R, static_cast<GLint>(params.wrapR));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_BASE_LEVEL, 0);
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_MAX_LEVEL, storageMipLevels - 1);

        GLenum format = RGBA;
        GLenum type = UNSIGNED_BYTE;
        selectUploadFormat(params.internalFormat, format, type);

        for (int mip = 0; mip < storageMipLevels; ++mip)
        {
            const int mipSize = std::max(1, size >> mip);
            for (int face = 0; face < 6; ++face)
            {
                gl.glTexImage2D(
                    TEXTURE_CUBE_MAP_POSITIVE_X + face,
                    mip,
                    static_cast<GLint>(params.internalFormat),
                    mipSize,
                    mipSize,
                    0,
                    format,
                    type,
                    nullptr);
            }
        }

        if (params.generateMipmaps && !isDepth)
        {
            gl.glGenerateMipmap(TEXTURE_CUBE_MAP);
        }

        gl.glBindTexture(TEXTURE_CUBE_MAP, 0);

        Params actualParams = params;
        actualParams.mipLevels = (params.generateMipmaps && !isDepth) ? maxMipLevels : explicitMipLevels;

        return TextureCube{ id, size, actualParams };
    }

    TextureCube TextureCube::fromMemory(const FaceData faces[6])
    {
        return fromMemory(faces, Params{});
    }

    TextureCube TextureCube::fromMemory(const FaceData faces[6], const Params& params)
    {
        if (faces == nullptr)
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: null faces pointer");
            return {};
        }

        const int expectedWidth = faces[0].width;
        const int expectedHeight = faces[0].height;
        if (expectedWidth <= 0 || expectedHeight <= 0)
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: invalid face dimensions");
            return {};
        }

        if (expectedWidth != expectedHeight)
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: cube faces must be square");
            return {};
        }

        if (!supportsFaceUpload(params.internalFormat))
        {
            internal::runtime::logError(
                "TextureCube",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "fromMemory: supported upload formats are InternalFormat::RGBA8 and InternalFormat::SRGB8_Alpha");
            return {};
        }

        for (int face = 0; face < 6; ++face)
        {
            if (faces[face].width != expectedWidth || faces[face].height != expectedHeight)
            {
                internal::runtime::logError(
                    "TextureCube",
                    internal::runtime::ErrorLevel::Warn,
                    internal::runtime::ErrorKind::Recoverable,
                    "fromMemory: all faces must share identical dimensions");
                return {};
            }
            if (faces[face].width != faces[face].height)
            {
                char msg[96];
                std::snprintf(msg, sizeof(msg), "fromMemory: face %d is not square", face);
                internal::runtime::logError(
                    "TextureCube", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
                return {};
            }
            if (faces[face].pixels == nullptr)
            {
                char msg[96];
                std::snprintf(msg, sizeof(msg), "fromMemory: face %d has null pixels", face);
                internal::runtime::logError(
                    "TextureCube", internal::runtime::ErrorLevel::Warn, internal::runtime::ErrorKind::Recoverable, msg);
                return {};
            }
        }

        const auto& gl = Context::current().functions();

        const bool isDepth =
            (params.internalFormat == InternalFormat::Depth24 || params.internalFormat == InternalFormat::Depth32F);
        const GLint minFilter = (params.generateMipmaps && !isDepth && params.minFilter == Filter::Linear)
                                    ? static_cast<GLint>(LINEAR_MIPMAP_LINEAR)
                                    : static_cast<GLint>(params.minFilter);

        GLuint id = 0;
        gl.glGenTextures(1, &id);
        gl.glBindTexture(TEXTURE_CUBE_MAP, id);

        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_MIN_FILTER, minFilter);
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_MAG_FILTER, static_cast<GLint>(params.magFilter));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_S, static_cast<GLint>(params.wrapS));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_T, static_cast<GLint>(params.wrapT));
        gl.glTexParameteri(TEXTURE_CUBE_MAP, TEXTURE_WRAP_R, static_cast<GLint>(params.wrapR));

        GLenum format = RGBA;
        GLenum type = UNSIGNED_BYTE;
        selectUploadFormat(params.internalFormat, format, type);

        for (int face = 0; face < 6; ++face)
        {
            gl.glTexImage2D(
                TEXTURE_CUBE_MAP_POSITIVE_X + face,
                0,
                static_cast<GLint>(params.internalFormat),
                faces[face].width,
                faces[face].height,
                0,
                format,
                type,
                faces[face].pixels);
        }

        if (params.generateMipmaps && !isDepth)
        {
            gl.glGenerateMipmap(TEXTURE_CUBE_MAP);
        }

        gl.glBindTexture(TEXTURE_CUBE_MAP, 0);

        // Use first face's width as the cube size
        return TextureCube{ id, expectedWidth, params };
    }

    void TextureCube::bind(GLuint unit) const
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(
                static_cast<int>(unit) < ctx.maxTextureImageUnits() &&
                "TextureCube::bind(): unit exceeds GL_MAX_TEXTURE_IMAGE_UNITS");
            return;
        }
        const auto& gl = ctx.functions();
        gl.glActiveTexture(TEXTURE0 + unit);
        gl.glBindTexture(TEXTURE_CUBE_MAP, m_id);
    }

    void TextureCube::unbind(GLuint unit)
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(
                static_cast<int>(unit) < ctx.maxTextureImageUnits() &&
                "TextureCube::unbind(): unit exceeds GL_MAX_TEXTURE_IMAGE_UNITS");
            return;
        }
        const auto& gl = ctx.functions();
        gl.glActiveTexture(TEXTURE0 + unit);
        gl.glBindTexture(TEXTURE_CUBE_MAP, 0);
    }
} // namespace nfx::graphics::gl
