#include "../FontLoader.h"

#include <embedded_fonts.h>

#include <stb/stb_truetype.h>

#include <cstdio>
#include <fstream>
#include <vector>

namespace gl = nfx::graphics::gl;

namespace nfx::samples
{
    constexpr int DEFAULT_ATLAS_WIDTH = 1024;
    constexpr int DEFAULT_ATLAS_HEIGHT = 1024;

    std::optional<gl::Font> FontLoader::fromSource(
        gl::Texture2DCache& textureCache,
        const unsigned char* ttfBytes,
        std::size_t ttfSize,
        float pixelHeight,
        std::uint32_t firstCodepoint,
        std::uint32_t lastCodepoint)
    {
        if (!ttfBytes || ttfSize == 0)
        {
            std::fprintf(stderr, "[FontLoader] fromSource: empty TTF payload\n");
            return std::nullopt;
        }

        if (pixelHeight <= 0.0f || firstCodepoint > lastCodepoint)
        {
            std::fprintf(stderr, "[FontLoader] fromSource: invalid bake parameters\n");
            return std::nullopt;
        }

        const std::uint32_t glyphCountU32 = (lastCodepoint - firstCodepoint) + 1u;
        if (glyphCountU32 == 0u || glyphCountU32 > static_cast<std::uint32_t>(INT32_MAX))
        {
            std::fprintf(stderr, "[FontLoader] fromSource: invalid glyph range\n");
            return std::nullopt;
        }

        const int glyphCount = static_cast<int>(glyphCountU32);
        std::vector<unsigned char> alpha(
            static_cast<std::size_t>(DEFAULT_ATLAS_WIDTH) * static_cast<std::size_t>(DEFAULT_ATLAS_HEIGHT), 0u);
        std::vector<stbtt_bakedchar> baked(static_cast<std::size_t>(glyphCount));

        const int bakeResult = stbtt_BakeFontBitmap(
            ttfBytes,
            0,
            pixelHeight,
            alpha.data(),
            DEFAULT_ATLAS_WIDTH,
            DEFAULT_ATLAS_HEIGHT,
            static_cast<int>(firstCodepoint),
            glyphCount,
            baked.data());

        if (bakeResult <= 0)
        {
            std::fprintf(stderr, "[FontLoader] fromSource: stbtt_BakeFontBitmap failed\n");
            return std::nullopt;
        }

        std::vector<unsigned char> rgba(
            static_cast<std::size_t>(DEFAULT_ATLAS_WIDTH) * static_cast<std::size_t>(DEFAULT_ATLAS_HEIGHT) * 4u, 255u);
        for (std::size_t i = 0; i < alpha.size(); ++i)
        {
            rgba[i * 4u + 3u] = alpha[i];
        }

        gl::Texture2D::Data atlasData{};
        atlasData.pixels = rgba.data();
        atlasData.width = DEFAULT_ATLAS_WIDTH;
        atlasData.height = DEFAULT_ATLAS_HEIGHT;
        atlasData.params.generateMipmaps = false;
        atlasData.params.minFilter = gl::Texture2D::Filter::Linear;
        atlasData.params.magFilter = gl::Texture2D::Filter::Linear;
        atlasData.params.wrapS = gl::Texture2D::Wrap::ClampToEdge;
        atlasData.params.wrapT = gl::Texture2D::Wrap::ClampToEdge;
        atlasData.params.internalFormat = gl::Texture2D::InternalFormat::RGBA8;

        const gl::Texture2DHandle atlasHandle = textureCache.upload(atlasData);
        if (!atlasHandle.isValid())
        {
            std::fprintf(stderr, "[FontLoader] fromSource: atlas upload failed\n");
            return std::nullopt;
        }

        gl::Font font;
        font.atlas = atlasHandle;

        stbtt_fontinfo fontInfo{};
        const int offset = stbtt_GetFontOffsetForIndex(ttfBytes, 0);
        if (offset >= 0 && stbtt_InitFont(&fontInfo, ttfBytes, offset) != 0)
        {
            int ascent = 0;
            int descent = 0;
            int lineGap = 0;
            stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
            const float scale = stbtt_ScaleForPixelHeight(&fontInfo, pixelHeight);
            font.metrics.ascentPx = static_cast<float>(ascent) * scale;
            font.metrics.descentPx = static_cast<float>(descent) * scale;
            font.metrics.lineGapPx = static_cast<float>(lineGap) * scale;
        }

        for (int i = 0; i < glyphCount; ++i)
        {
            const std::uint32_t cp = firstCodepoint + static_cast<std::uint32_t>(i);
            const stbtt_bakedchar& bc = baked[i];

            gl::Glyph g;
            g.codepoint = cp;
            g.u0 = bc.x0 / static_cast<float>(DEFAULT_ATLAS_WIDTH);
            g.v0 = bc.y0 / static_cast<float>(DEFAULT_ATLAS_HEIGHT);
            g.u1 = bc.x1 / static_cast<float>(DEFAULT_ATLAS_WIDTH);
            g.v1 = bc.y1 / static_cast<float>(DEFAULT_ATLAS_HEIGHT);
            g.widthPx = static_cast<float>(bc.x1 - bc.x0);
            g.heightPx = static_cast<float>(bc.y1 - bc.y0);
            g.bearingXPx = bc.xoff;
            g.bearingYPx = -bc.yoff;
            g.advanceXPx = bc.xadvance;
            font.glyphs.emplace(cp, g);
        }

        return font;
    }

    gl::FontHandle FontLoader::fromEmbedded(
        gl::Texture2DCache& textureCache,
        gl::FontCache& fontCache,
        const char* resourceName,
        float pixelHeight,
        std::uint32_t firstCodepoint,
        std::uint32_t lastCodepoint)
    {
        if (!resourceName || resourceName[0] == '\0')
        {
            std::fprintf(stderr, "[FontLoader] fromEmbedded: empty resource name\n");
            return {};
        }

        const auto* res = samples::fonts::find(resourceName);
        if (!res)
        {
            std::fprintf(stderr, "[FontLoader] fromEmbedded: font resource not found: %s\n", resourceName);
            return {};
        }

        auto font = fromSource(
            textureCache,
            reinterpret_cast<const unsigned char*>(res->data),
            res->size,
            pixelHeight,
            firstCodepoint,
            lastCodepoint);

        if (!font)
        {
            return {};
        }

        return fontCache.create(std::move(*font));
    }
} // namespace nfx::samples
