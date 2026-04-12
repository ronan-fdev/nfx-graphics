#include "nfx/graphics/gl/material/Pbr.h"

#include "nfx/graphics/gl/material/MaterialBlock.h"
#include "ShaderFeatures.h"

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

            const EmbeddedResource* vert = shaders::find("material/pbr.vert");
            const EmbeddedResource* frag = shaders::find("material/pbr.frag");
            if (!vert || !frag)
            {
                std::fprintf(stderr, "[Pbr] Missing embedded shader resources\n");
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
                std::fprintf(stderr, "[Pbr] Failed to compile shader variant (key=%u)\n", key);
                return {};
            }

            shaderCache()[key] = handle;
            return handle;
        }
    } // namespace

    MaterialHandle PbrMaterial::build(RenderResources& resources) const
    {
        ShaderFeature features = ShaderFeature::None;
        if (baseColorMap.isValid())
        {
            features |= ShaderFeature::HasBaseColorMap;
        }
        if (normalMap.isValid())
        {
            features |= ShaderFeature::HasNormalMap;
        }
        if (armMap.isValid())
        {
            features |= ShaderFeature::HasArmMap;
        }
        else
        {
            if (metallicRoughnessMap.isValid())
            {
                features |= ShaderFeature::HasMetallicRoughnessMap;
            }
            if (occlusionMap.isValid())
            {
                features |= ShaderFeature::HasOcclusionMap;
            }
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
            std::fprintf(stderr, "[Pbr] Failed to resolve created material handle\n");
            return {};
        }

        apply(*mat);

        return handle;
    }

    void PbrMaterial::apply(Material& mat) const
    {
        const float clampedAlpha = std::clamp(alpha, 0.f, 1.f);
        const float clampedMetallic = std::clamp(metallic, 0.f, 1.f);
        const float clampedRoughness = std::clamp(roughness, 0.045f, 1.f);
        const float clampedAo = std::clamp(ao, 0.f, 1.f);

        const RenderState state = (clampedAlpha < 1.f) ? RenderState::transparent() : RenderState::opaque();
        mat.setRenderState(state);

        MaterialBlockData block;
        block.baseColor_alpha[0] = baseColor[0];
        block.baseColor_alpha[1] = baseColor[1];
        block.baseColor_alpha[2] = baseColor[2];
        block.baseColor_alpha[3] = clampedAlpha;
        block.specColor_shine[0] = clampedMetallic;
        block.specColor_shine[1] = clampedRoughness;
        block.specColor_shine[2] = clampedAo;
        block.specColor_shine[3] = useIblSplitSum ? 1.f : 0.f;
        block.emissive_env[0] = emissive[0];
        block.emissive_env[1] = emissive[1];
        block.emissive_env[2] = emissive[2];
        block.emissive_env[3] = envIntensity;
        mat.setMaterialBlock(block);

        if (baseColorMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::BaseColorMap, baseColorMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::BaseColorMap);
        }

        if (normalMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::NormalMap, normalMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::NormalMap);
        }

        if (armMap.isValid())
        {
            mat.setTextureUnit(TextureBindings::ArmMap, armMap);
            mat.clearTextureUnit(TextureBindings::MetallicRoughnessMap);
        }
        else
        {
            mat.clearTextureUnit(TextureBindings::ArmMap);

            if (metallicRoughnessMap.isValid())
            {
                mat.setTextureUnit(TextureBindings::MetallicRoughnessMap, metallicRoughnessMap);
            }
            else
            {
                mat.clearTextureUnit(TextureBindings::MetallicRoughnessMap);
            }

            if (occlusionMap.isValid())
            {
                mat.setTextureUnit(TextureBindings::OcclusionMap, occlusionMap);
            }
            else
            {
                mat.clearTextureUnit(TextureBindings::OcclusionMap);
            }
        }
    }
} // namespace nfx::graphics::gl
