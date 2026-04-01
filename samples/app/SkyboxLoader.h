#pragma once

#include <nfx/graphics/gl/resources/TextureCubeCache.h>

#include <stb/stb_image.h>

#include <embedded_textures.h>

#include <cstdio>

namespace nfx::samples
{
    // srgb=true for LDR skyboxes (JPG/PNG), srgb=false for HDR or linear cubemaps
    inline graphics::gl::TextureCubeHandle loadSkybox(
        graphics::gl::TextureCubeCache& cache, const char* prefix, bool srgb = false)
    {
        // OpenGL face order: +X -X +Y -Y +Z -Z
        const char* faceNames[6] = { "right", "left", "top", "bottom", "front", "back" };

        graphics::gl::TextureCube::FaceData faces[6]{};
        unsigned char* pixels[6]{};

        for (int i = 0; i < 6; ++i)
        {
            char path[256];
            std::snprintf(path, sizeof(path), "%s/%s.jpg", prefix, faceNames[i]);
            const auto* res = textures::find(path);
            if (!res)
            {
                std::fprintf(stderr, "[loadSkybox] Missing embedded face: %s\n", path);
                for (int j = 0; j < i; ++j)
                {
                    stbi_image_free(pixels[j]);
                }
                return {};
            }
            int w, h, c;
            stbi_set_flip_vertically_on_load(0);
            pixels[i] = stbi_load_from_memory(
                reinterpret_cast<const stbi_uc*>(res->data), static_cast<int>(res->size), &w, &h, &c, 4);
            if (!pixels[i])
            {
                std::fprintf(stderr, "[loadSkybox] stbi_load failed for: %s\n", path);
                for (int j = 0; j < i; ++j)
                {
                    stbi_image_free(pixels[j]);
                }
                return {};
            }
            faces[i] = { pixels[i], w, h };
        }

        auto handle = cache.upload(
            faces,
            { .generateMipmaps = false,
              .minFilter = graphics::gl::TextureCube::Filter::Linear,
              .magFilter = graphics::gl::TextureCube::Filter::Linear,
              .wrapS = graphics::gl::TextureCube::Wrap::ClampToEdge,
              .wrapT = graphics::gl::TextureCube::Wrap::ClampToEdge,
              .wrapR = graphics::gl::TextureCube::Wrap::ClampToEdge,
              .internalFormat = srgb ? graphics::gl::TextureCube::InternalFormat::SRGB8_Alpha
                                     : graphics::gl::TextureCube::InternalFormat::RGBA8 });

        for (int i = 0; i < 6; ++i)
        {
            stbi_image_free(pixels[i]);
        }
        return handle;
    }

} // namespace nfx::samples
