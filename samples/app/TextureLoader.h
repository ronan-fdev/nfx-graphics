#pragma once

#include <nfx/graphics/gl/core/textures/Texture2D.h>

#include <stb/stb_image.h>

#include <embedded_textures.h>
#include <embedded_objects.h>

#include <cstdio>

namespace nfx::samples
{
    // srgb=true for diffuse/albedo/emissive textures, srgb=false for normal/roughness/specular/AO maps
    inline graphics::gl::Texture2D loadEmbeddedTexture(const char* name, bool flipY = true, bool srgb = false)
    {
        const auto* res = textures::find(name);
        if (!res)
        {
            res = models::find(name);
        }
        if (!res)
        {
            std::fprintf(stderr, "loadEmbeddedTexture: texture not found: %s\n", name);
            return {};
        }

        int w, h, c;
        stbi_set_flip_vertically_on_load(flipY ? 1 : 0);
        unsigned char* px = stbi_load_from_memory(
            reinterpret_cast<const stbi_uc*>(res->data), static_cast<int>(res->size), &w, &h, &c, 4);

        if (!px)
        {
            std::fprintf(stderr, "loadEmbeddedTexture: stb decode failed: %s\n", name);
            return {};
        }

        const auto internalFormat = srgb ? graphics::gl::Texture2D::InternalFormat::SRGB8_Alpha
                                         : graphics::gl::Texture2D::InternalFormat::RGBA8;

        auto tex = graphics::gl::Texture2D::fromMemory(
            px,
            w,
            h,
            { .wrapS = graphics::gl::Texture2D::Wrap::Repeat,
              .wrapT = graphics::gl::Texture2D::Wrap::Repeat,
              .internalFormat = internalFormat });

        stbi_image_free(px);
        return tex;
    }
} // namespace nfx::samples
