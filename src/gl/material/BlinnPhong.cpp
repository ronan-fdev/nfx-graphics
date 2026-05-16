#include "nfx/graphics/gl/material/BlinnPhong.h"

#include "nfx/graphics/gl/pipeline/frame/RenderResources.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "ShaderFeatures.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <unordered_map>

namespace nfx::graphics::gl
{
    namespace
    {
        std::unordered_map<std::uint32_t, ShaderHandle>& shaderCache()
        {
            static std::unordered_map<std::uint32_t, ShaderHandle> cache;
            return cache;
        }

        std::string injectDefines(std::string_view src, std::string_view defines)
        {
            std::string out(src);
            if (defines.empty())
            {
                return out;
            }

            const std::size_t firstLineEnd = out.find('\n');
            if (firstLineEnd == std::string::npos)
            {
                return out;
            }
            out.insert(firstLineEnd + 1, defines);
            return out;
        }

        std::string variantDefines(ShaderFeature features)
        {
            std::string defines;
            for (std::string_view def : toDefines(features))
            {
                defines += "#define ";
                defines += def;
                defines += '\n';
            }
            return defines;
        }

        ShaderHandle resolveShaderVariant(RenderResources& resources, ShaderFeature features)
        {
            const std::uint32_t key = static_cast<std::uint32_t>(features);
            if (auto it = shaderCache().find(key); it != shaderCache().end() && resources.shaders.contains(it->second))
            {
                return it->second;
            }

            const EmbeddedResource* vert = shaders::find("material/blinn_phong.vert");
            const EmbeddedResource* frag = shaders::find("material/blinn_phong.frag");
            if (!vert || !frag)
            {
                internal::runtime::logError(
                    "BlinnPhong",
                    internal::runtime::ErrorLevel::Error,
                    internal::runtime::ErrorKind::External,
                    "Missing embedded shader resources");
                return {};
            }

            const std::string defines = variantDefines(features);
            const std::string vertSrc = injectDefines(vert->str(), defines);
            const std::string fragSrc = injectDefines(frag->str(), defines);

            ShaderHandle handle = resources.shaders.compile({
                { ShaderProgram::Stage::Vertex, vertSrc },
                { ShaderProgram::Stage::Fragment, fragSrc },
            });
            if (!handle.isValid())
            {
                char msg[128];
                std::snprintf(msg, sizeof(msg), "Failed to compile shader variant (key=%u)", key);
                internal::runtime::logError(
                    "BlinnPhong", internal::runtime::ErrorLevel::Error, internal::runtime::ErrorKind::External, msg);
                return {};
            }

            shaderCache()[key] = handle;
            return handle;
        }
    } // namespace

    MaterialHandle BlinnPhongMaterial::build(RenderResources& resources) const
    {
        ShaderFeature features = ShaderFeature::None;
        if (diffuseMap.isValid())
        {
            features |= ShaderFeature::HasDiffuseMap;
        }
        if (normalMap.isValid())
        {
            features |= ShaderFeature::HasNormalMap;
        }
        if (specularMap.isValid())
        {
            features |= ShaderFeature::HasSpecularMap;
        }
        if (hasShadow)
        {
            features |= ShaderFeature::HasShadow;
        }
        if (hasEnvMap)
        {
            features |= ShaderFeature::HasEnvMap;
        }

        const ShaderHandle shader = resolveShaderVariant(resources, features);
        if (!shader.isValid())
        {
            return {};
        }

        const float clampedAlpha = std::clamp(alpha, 0.f, 1.f);
        const RenderState state = (clampedAlpha < 1.f) ? RenderState::transparent() : RenderState::opaque();

        MaterialHandle handle = resources.materials.create(shader, state);
        Material* mat = resources.materials.get(handle);
        if (!mat)
        {
            internal::runtime::logError(
                "BlinnPhong",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::Recoverable,
                "Failed to resolve created material handle");
            return {};
        }

        apply(*mat);

        return handle;
    }

    void BlinnPhongMaterial::apply(Material& mat) const
    {
        const float clampedAlpha = std::clamp(alpha, 0.f, 1.f);
        const float clampedShininess = std::max(shininess, 1.f);

        const RenderState state = (clampedAlpha < 1.f) ? RenderState::transparent() : RenderState::opaque();

        mat.setRenderState(state);

        MaterialBlockData block;
        block.baseColor_alpha[0] = diffuseColor[0];
        block.baseColor_alpha[1] = diffuseColor[1];
        block.baseColor_alpha[2] = diffuseColor[2];
        block.baseColor_alpha[3] = clampedAlpha;
        block.specColor_shine[0] = specularColor[0];
        block.specColor_shine[1] = specularColor[1];
        block.specColor_shine[2] = specularColor[2];
        block.specColor_shine[3] = clampedShininess;
        block.emissive_env[3] = envIntensity;

        mat.setMaterialBlock(block);

        if (diffuseMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::DiffuseMap, diffuseMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::DiffuseMap);
        }

        if (normalMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::NormalMap, normalMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::NormalMap);
        }

        if (specularMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::SpecularMap, specularMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::SpecularMap);
        }
    }
} // namespace nfx::graphics::gl
