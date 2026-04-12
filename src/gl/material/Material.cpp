#include "nfx/graphics/gl/material/Material.h"

#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "nfx/graphics/gl/core/textures/Texture2D.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/resources/ShaderCache.h"
#include "nfx/graphics/gl/resources/Texture2DCache.h"

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <utility>

namespace nfx::graphics::gl
{
    namespace
    {
        template <typename Map, typename T>
        void assignUniform(Map& uniforms, std::string_view name, T&& value)
        {
            if (auto it = uniforms.find(name); it != uniforms.end())
            {
                it->second = std::forward<T>(value);
                return;
            }

            uniforms.emplace(std::string{ name }, std::forward<T>(value));
        }
    } // namespace

    Material Material::create(ShaderHandle shader, RenderState state)
    {
        Material mat;
        mat.m_shader = shader;
        mat.m_state = state;
        return mat;
    }

    void Material::setUniform(std::string_view name, int value)
    {
        assignUniform(m_uniforms, name, value);
    }

    void Material::setUniform(std::string_view name, float value)
    {
        assignUniform(m_uniforms, name, value);
    }

    void Material::setUniform(std::string_view name, const UniformVec2& v)
    {
        assignUniform(m_uniforms, name, v);
    }

    void Material::setUniform(std::string_view name, const UniformVec3& v)
    {
        assignUniform(m_uniforms, name, v);
    }

    void Material::setUniform(std::string_view name, const UniformVec4& v)
    {
        assignUniform(m_uniforms, name, v);
    }

    void Material::setUniform(std::string_view name, const UniformMat3& v)
    {
        assignUniform(m_uniforms, name, v);
    }

    void Material::setUniform(std::string_view name, const UniformMat4& v)
    {
        assignUniform(m_uniforms, name, v);
    }

    void Material::setUniformVec2(std::string_view name, const float* v)
    {
        assert(v && "Material::setUniformVec2(): pointer must not be null");
        if (!v)
        {
            return;
        }
        assignUniform(m_uniforms, name, UniformVec2{ v[0], v[1] });
    }

    void Material::setUniformVec3(std::string_view name, const float* v)
    {
        assert(v && "Material::setUniformVec3(): pointer must not be null");
        if (!v)
        {
            return;
        }
        assignUniform(m_uniforms, name, UniformVec3{ v[0], v[1], v[2] });
    }

    void Material::setUniformVec4(std::string_view name, const float* v)
    {
        assert(v && "Material::setUniformVec4(): pointer must not be null");
        if (!v)
        {
            return;
        }
        assignUniform(m_uniforms, name, UniformVec4{ v[0], v[1], v[2], v[3] });
    }

    void Material::setUniformMat3(std::string_view name, const float* m)
    {
        assert(m && "Material::setUniformMat3(): pointer must not be null");
        if (!m)
        {
            return;
        }
        UniformMat3 mat;
        std::copy(m, m + 9, mat.data());
        assignUniform(m_uniforms, name, mat);
    }

    void Material::setUniformMat4(std::string_view name, const float* m)
    {
        assert(m && "Material::setUniformMat4(): pointer must not be null");
        if (!m)
        {
            return;
        }
        UniformMat4 mat;
        std::copy(m, m + 16, mat.data());
        assignUniform(m_uniforms, name, mat);
    }

    const Uniform* Material::uniform(std::string_view name) const noexcept
    {
        auto it = m_uniforms.find(name);
        return it != m_uniforms.end() ? &it->second : nullptr;
    }

    bool Material::hasUniform(std::string_view name) const noexcept
    {
        return m_uniforms.find(name) != m_uniforms.end();
    }

    void Material::clearUniform(std::string_view name)
    {
        if (auto it = m_uniforms.find(name); it != m_uniforms.end())
        {
            m_uniforms.erase(it);
        }
    }

    void Material::clearUniforms()
    {
        m_uniforms.clear();
    }

    void Material::setTexture(std::string_view name, Texture2DHandle handle)
    {
        m_textures[std::string{ name }] = handle;
    }

    void Material::setTextureUnit(GLuint unit, Texture2DHandle handle)
    {
        const GLuint userFirst = static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit);
        const GLuint userLast = static_cast<GLuint>(TextureBindings::UserMaterialLastUnit);
        if (unit >= userFirst && unit <= userLast)
        {
            std::fprintf(
                stderr,
                "[Material] WARNING: fixed texture unit %u is in user dynamic range [%u..%u], binding ignored\n",
                static_cast<unsigned>(unit),
                static_cast<unsigned>(userFirst),
                static_cast<unsigned>(userLast));
            return;
        }

        m_texturesByUnit[unit] = handle;
    }

    bool Material::hasTexture(std::string_view name) const noexcept
    {
        return m_textures.find(name) != m_textures.end();
    }

    bool Material::hasTextureUnit(GLuint unit) const noexcept
    {
        return m_texturesByUnit.find(unit) != m_texturesByUnit.end();
    }

    void Material::clearTexture(std::string_view name)
    {
        if (auto it = m_textures.find(name); it != m_textures.end())
        {
            m_textures.erase(it);
        }
    }

    void Material::clearTextureUnit(GLuint unit)
    {
        if (auto it = m_texturesByUnit.find(unit); it != m_texturesByUnit.end())
        {
            m_texturesByUnit.erase(it);
        }
    }

    void Material::clearTextures()
    {
        m_textures.clear();
    }

    void Material::clearTextureUnits()
    {
        m_texturesByUnit.clear();
    }

    void Material::setMaterialBlock(const MaterialBlockData& block)
    {
        m_materialBlock = block;
    }

    void Material::bind(ShaderCache& shaderCache, const Texture2DCache& textureCache)
    {
        ShaderProgram* shader = shaderCache.get(m_shader);
        if (!shader)
        {
            std::fprintf(
                stderr,
                "[Material] WARNING: missing shader handle (%llu), bind skipped\n",
                static_cast<unsigned long long>(m_shader.id));
            return;
        }

        shader->bind();
        m_state.apply();

        // Upload and bind MaterialBlock UBO
        if (!m_materialBlock.has_value())
        {
            m_materialBlock = MaterialBlockData{};
        }

        if (!m_materialBlockUbo.has_value())
        {
            m_materialBlockUbo.emplace();
        }
        m_materialBlockUbo->upload(*m_materialBlock);
        m_materialBlockUbo->bind(static_cast<GLuint>(UboBindings::MaterialBlock));

        for (const auto& [name, uniform] : m_uniforms)
        {
            std::visit([&](const auto& v) { shader->setUniform(name, v); }, uniform);
        }

        // Unbind units touched in the previous call
        for (GLuint unit : m_lastBoundUnits)
        {
            Texture2D::unbind(unit);
        }
        m_lastBoundUnits.clear();

        // Bind fixed-slot textures first (explicit texture unit -> texture handle)
        for (const auto& [unit, handle] : m_texturesByUnit)
        {
            if (const Texture2D* tex = textureCache.get(handle))
            {
                tex->bind(unit);
                m_lastBoundUnits.push_back(unit);
            }
            else
            {
                std::fprintf(
                    stderr,
                    "[Material] WARNING: missing texture handle (%llu) for fixed unit %u\n",
                    static_cast<unsigned long long>(handle.id),
                    static_cast<unsigned>(unit));
            }
        }

        // Bind named samplers in user-safe dynamic range and set sampler uniforms
        GLuint unit = static_cast<GLuint>(TextureBindings::UserMaterialFirstUnit);
        const GLuint lastUnit = static_cast<GLuint>(TextureBindings::UserMaterialLastUnit);
        for (const auto& [name, handle] : m_textures)
        {
            if (unit > lastUnit)
            {
                std::fprintf(
                    stderr,
                    "[Material] WARNING: sampler '%s' skipped, no free user texture unit in [%u..%u]\n",
                    name.c_str(),
                    static_cast<unsigned>(TextureBindings::UserMaterialFirstUnit),
                    static_cast<unsigned>(TextureBindings::UserMaterialLastUnit));
                break;
            }

            if (const Texture2D* tex = textureCache.get(handle))
            {
                tex->bind(unit);
                shader->setUniform(name, static_cast<int>(unit));
                m_lastBoundUnits.push_back(unit);
                ++unit;
            }
            else
            {
                std::fprintf(
                    stderr,
                    "[Material] WARNING: missing texture handle (%llu) for sampler '%s'\n",
                    static_cast<unsigned long long>(handle.id),
                    name.c_str());
            }
        }
    }
} // namespace nfx::graphics::gl
