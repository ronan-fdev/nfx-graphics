#include "nfx/graphics/gl/material/Unlit.h"

#include "nfx/graphics/gl/material/MaterialBlock.h"

#include <embedded_shaders.h>

#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        ShaderHandle shader(ShaderCache& shaderCache)
        {
            static ShaderHandle s_handle;

            if (s_handle.isValid() && shaderCache.contains(s_handle))
            {
                return s_handle;
            }

            const EmbeddedResource* vert = shaders::find("material/unlit.vert");
            const EmbeddedResource* frag = shaders::find("material/unlit.frag");
            if (!vert || !frag)
            {
                std::fprintf(stderr, "[Unlit] Missing embedded shader resources\n");
                return {};
            }

            s_handle = shaderCache.add(ShaderProgram::fromSources(
                { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } }));

            if (!s_handle.isValid())
            {
                std::fprintf(stderr, "[Unlit] Failed to compile unlit shader\n");
                return {};
            }

            return s_handle;
        }
    } // namespace

    MaterialHandle UnlitMaterial::build(ShaderCache& shaderCache, MaterialCache& matCache) const
    {
        const ShaderHandle sh = shader(shaderCache);
        if (!sh.isValid())
        {
            return {};
        }

        const RenderState state = (alpha < 1.f) ? RenderState::transparent() : RenderState::opaque();
        MaterialHandle handle = matCache.add(Material::create(sh, state));
        Material* mat = matCache.get(handle);
        if (!mat)
        {
            std::fprintf(stderr, "[Unlit] Failed to resolve created material handle\n");
            return {};
        }

        apply(*mat);

        return handle;
    }

    void UnlitMaterial::apply(Material& mat) const
    {
        const RenderState state = (alpha < 1.f) ? RenderState::transparent() : RenderState::opaque();
        mat.setRenderState(state);

        MaterialBlockData block;
        block.baseColor_alpha[0] = color[0];
        block.baseColor_alpha[1] = color[1];
        block.baseColor_alpha[2] = color[2];
        block.baseColor_alpha[3] = alpha;
        mat.setMaterialBlock(block);
    }
} // namespace nfx::graphics::gl
