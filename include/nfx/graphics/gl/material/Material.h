#pragma once

/**
 * \file Material.h
 * \brief Declares the runtime material object used to bind shaders, uniforms, textures and render state.
 */

#include "nfx/graphics/gl/core/buffers/UniformBuffer.h"
#include "nfx/graphics/gl/core/shaders/Uniforms.h"
#include "nfx/graphics/gl/core/GlTypes.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/resources/Handle.h"
#include "MaterialBlock.h"

#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

namespace nfx::graphics::gl
{
    class ShaderCache;
    class Texture2DCache;

    /**
     * \brief Runtime material state combining one shader, one render state and named uniforms/textures.
     */
    class Material final
    {
    public:
        /**
         * \brief Creates a material bound to a shader and an initial render state.
         * \param shader Shader handle used by the material.
         * \param state Initial render state applied when binding the material.
         * \return A material configured with the provided shader and baseline render state.
         */
        [[nodiscard]] static Material create(ShaderHandle shader, RenderState state);

        ~Material() = default;

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        Material(Material&&) noexcept = default;
        Material& operator=(Material&&) noexcept = default;

        /**
         * \brief Sets an integer uniform override by name.
         * \param name Uniform identifier.
         * \param value Integer value to store.
         */
        void setUniform(std::string_view name, int value);

        /**
         * \brief Sets a float uniform override by name.
         * \param name Uniform identifier.
         * \param value Float value to store.
         */
        void setUniform(std::string_view name, float value);

        /**
         * \brief Sets a vec2 uniform override by name.
         * \param name Uniform identifier.
         * \param value Vec2 value to store.
         */
        void setUniform(std::string_view name, const UniformVec2& value);

        /**
         * \brief Sets a vec3 uniform override by name.
         * \param name Uniform identifier.
         * \param value Vec3 value to store.
         */
        void setUniform(std::string_view name, const UniformVec3& value);

        /**
         * \brief Sets a vec4 uniform override by name.
         * \param name Uniform identifier.
         * \param value Vec4 value to store.
         */
        void setUniform(std::string_view name, const UniformVec4& value);

        /**
         * \brief Sets a mat3 uniform override by name.
         * \param name Uniform identifier.
         * \param value Mat3 value to store.
         */
        void setUniform(std::string_view name, const UniformMat3& value);

        /**
         * \brief Sets a mat4 uniform override by name.
         * \param name Uniform identifier.
         * \param value Mat4 value to store.
         */
        void setUniform(std::string_view name, const UniformMat4& value);

        /**
         * \brief Sets a vec2 uniform from a raw pointer.
         * \param name Uniform identifier.
         * \param v Pointer to two floats.
         */
        void setUniformVec2(std::string_view name, const float* v);

        /**
         * \brief Sets a vec3 uniform from a raw pointer.
         * \param name Uniform identifier.
         * \param v Pointer to three floats.
         */
        void setUniformVec3(std::string_view name, const float* v);

        /**
         * \brief Sets a vec4 uniform from a raw pointer.
         * \param name Uniform identifier.
         * \param v Pointer to four floats.
         */
        void setUniformVec4(std::string_view name, const float* v);

        /**
         * \brief Sets a mat3 uniform from a raw pointer.
         * \param name Uniform identifier.
         * \param m Pointer to nine floats.
         */
        void setUniformMat3(std::string_view name, const float* m);

        /**
         * \brief Sets a mat4 uniform from a raw pointer.
         * \param name Uniform identifier.
         * \param m Pointer to sixteen floats.
         */
        void setUniformMat4(std::string_view name, const float* m);

        /**
         * \brief Returns a previously assigned uniform value by name.
         * \param name Uniform identifier.
         * \return Pointer to the stored uniform override, or nullptr if not found.
         */
        [[nodiscard]] const Uniform* uniform(std::string_view name) const noexcept;

        /**
         * \brief Returns whether a uniform override exists for \p name.
         * \param name Uniform identifier.
         * \return True when a uniform override exists, false otherwise.
         */
        [[nodiscard]] bool hasUniform(std::string_view name) const noexcept;

        /**
         * \brief Removes one uniform override.
         * \param name Uniform identifier.
         */
        void clearUniform(std::string_view name);

        /**
         * \brief Removes all uniform overrides.
         */
        void clearUniforms();

        /**
         * \brief Associates a named 2D texture with the material.
         * \param name Sampler uniform identifier.
         * \param handle Texture handle resolved through the texture cache.
         *
         * Named sampler bindings use the dynamic user range defined by `TextureBindings`
         * (starting at `UserMaterialFirstUnit`).
         */
        void setTexture(std::string_view name, Texture2DHandle handle);

        /**
         * \brief Associates a texture handle with an explicit texture unit.
         * \param unit Fixed texture unit index.
         * \param handle Texture handle resolved through the texture cache.
         *
         * This is the preferred path for built-in fixed-slot sampler workflows.
         * Units in `TextureBindings::UserMaterialFirstUnit..UserMaterialLastUnit`
         * are reserved for dynamic named sampler bindings and are rejected.
         */
        void setTextureUnit(GLuint unit, Texture2DHandle handle);

        /**
         * \brief Returns whether a texture binding exists for \p name.
         * \param name Sampler uniform identifier.
         * \return True when a named texture binding exists, false otherwise.
         */
        [[nodiscard]] bool hasTexture(std::string_view name) const noexcept;

        /**
         * \brief Returns whether an explicit texture-unit binding exists for \p unit.
         * \param unit Texture unit index.
         * \return True when a fixed unit binding exists, false otherwise.
         */
        [[nodiscard]] bool hasTextureUnit(GLuint unit) const noexcept;

        /**
         * \brief Removes one texture binding.
         * \param name Sampler uniform identifier.
         */
        void clearTexture(std::string_view name);

        /**
         * \brief Removes one explicit texture-unit binding.
         * \param unit Texture unit index.
         */
        void clearTextureUnit(GLuint unit);

        /**
         * \brief Removes all texture bindings.
         */
        void clearTextures();

        /**
         * \brief Removes all explicit texture-unit bindings.
         */
        void clearTextureUnits();

        /**
         * \brief Sets the MaterialBlock UBO data
         *
         * The block is uploaded and bound at the next call to bind().
         * \param block Material parameters to upload.
         */
        void setMaterialBlock(const MaterialBlockData& block);

        /**
         * \brief Returns the MaterialBlock data if set, or nullptr.
         * \return Pointer to stored MaterialBlockData when set, otherwise nullptr.
         */
        [[nodiscard]] const MaterialBlockData* materialBlock() const noexcept
        {
            return m_materialBlock.has_value() ? &m_materialBlock.value() : nullptr;
        }

        /**
         * \brief Replaces the render state used when binding the material.
         * \param state New render state.
         */
        void setRenderState(const RenderState& state) { m_state = state; }

        /**
         * \brief Returns the render state currently stored by the material.
         * \return Current material render state.
         */
        [[nodiscard]] const RenderState& renderState() const noexcept { return m_state; }

        /**
         * \brief Returns the shader handle associated with the material.
         * \return Shader handle used by this material.
         */
        [[nodiscard]] ShaderHandle shader() const noexcept { return m_shader; }

        /**
         * \brief Binds the material shader, applies the render state and uploads uniforms/textures.
         * \param shaderCache Shader cache used to resolve the shader handle.
         * \param textureCache Texture cache used to resolve texture handles.
         * \param textureBindCount Optional output count of successful texture bind calls.
         */
        void bind(
            ShaderCache& shaderCache, const Texture2DCache& textureCache, std::uint32_t* textureBindCount = nullptr);

    private:
        Material() = default;

        struct StringHash
        {
            using is_transparent = void;
            std::size_t operator()(std::string_view sv) const noexcept { return std::hash<std::string_view>{}(sv); }
            std::size_t operator()(const std::string& s) const noexcept { return std::hash<std::string>{}(s); }
        };

        ShaderHandle m_shader;
        RenderState m_state;
        std::unordered_map<std::string, Uniform, StringHash, std::equal_to<>> m_uniforms;
        std::map<std::string, Texture2DHandle, std::less<>> m_textures;
        std::map<GLuint, Texture2DHandle> m_texturesByUnit;
        std::vector<GLuint> m_lastBoundUnits;

        std::optional<MaterialBlockData> m_materialBlock;
        std::optional<UniformBuffer<MaterialBlockData>> m_materialBlockUbo;
    };
} // namespace nfx::graphics::gl
