#pragma once

/**
 * \file ShaderProgram.h
 * \brief Declares a RAII wrapper for OpenGL shader programs, compilation helpers and uniform updates.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "Uniforms.h"

#include <filesystem>
#include <initializer_list>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \class ShaderProgram
     * \brief Owns an OpenGL shader program and provides helpers for compilation, linking and uniform updates.
     */
    class ShaderProgram final
    {
    public:
        // clang-format off
        /**
         * \brief Enumerates the supported programmable shader stages.
         */
        enum class Stage : unsigned int
        {
            Vertex      = VERTEX_SHADER,
            Fragment    = FRAGMENT_SHADER,
            Geometry    = GEOMETRY_SHADER,
            TessControl = TESS_CONTROL_SHADER,
            TessEval    = TESS_EVALUATION_SHADER,
            Compute     = COMPUTE_SHADER
        };
        // clang-format on

        /**
         * \brief Describes one in-memory shader source associated with a stage.
         */
        struct ShaderSource
        {
            Stage stage;
            std::string_view code;
        };

        /**
         * \brief Describes one shader file associated with a stage.
         */
        struct ShaderFile
        {
            Stage stage;
            std::filesystem::path path;
        };

        ShaderProgram() = default;

        /**
         * \brief Releases the underlying OpenGL shader program.
         */
        ~ShaderProgram() { release(); }

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;

        /**
         * \brief Builds a shader program from in-memory stage sources.
         * \param sources Shader stages and source strings to compile and link.
         * \return A valid program on success, or an empty program on failure.
         *
         * Accepted pipeline contracts:
         * - at least one stage must be provided
         * - graphics pipelines must contain at least a Vertex and a Fragment stage
         * - compute pipelines must contain exactly one Compute stage
         * - compute and graphics stages must not be mixed
         * - each stage may appear at most once
         */
        [[nodiscard]] static ShaderProgram fromSources(std::initializer_list<ShaderSource> sources);

        /**
         * \brief Builds a shader program from shader source files.
         * \param files Shader stages and file paths to load, compile and link.
         * \return A valid program on success, or an empty program on failure.
         *
         * Accepted pipeline contracts:
         * - at least one stage must be provided
         * - graphics pipelines must contain at least a Vertex and a Fragment stage
         * - compute pipelines must contain exactly one Compute stage
         * - compute and graphics stages must not be mixed
         * - each stage may appear at most once
         *
         * Missing files or invalid pipeline combinations return an empty program.
         */
        [[nodiscard]] static ShaderProgram fromFiles(std::initializer_list<ShaderFile> files);

        /**
         * \brief Releases the program object and resets the wrapper to an empty state.
         */
        void release();

        /**
         * \brief Binds the shader program for subsequent draw calls.
         */
        void bind() const;

        /**
         * \brief Unbinds the current shader program.
         */
        static void unbind();

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL program object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

        /**
         * \brief Returns the OpenGL object id owned by this program.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Sets scalar, vector and matrix uniforms by name using typed helper overloads.
         */
        void setUniform(std::string_view name, int value);
        void setUniform(std::string_view name, float value);
        void setUniform(std::string_view name, const UniformVec2& v);
        void setUniform(std::string_view name, const UniformVec3& v);
        void setUniform(std::string_view name, const UniformVec4& v);
        void setUniform(std::string_view name, const UniformMat3& m, bool transpose = false);
        void setUniform(std::string_view name, const UniformMat4& m, bool transpose = false);

        /**
         * \brief Sets uniforms from raw float pointers for interop with external math libraries.
         */
        void setUniformVec2(std::string_view name, const float* v);
        void setUniformVec3(std::string_view name, const float* v);
        void setUniformVec4(std::string_view name, const float* v);
        void setUniformMat3(std::string_view name, const float* m, bool transpose = false);
        void setUniformMat4(std::string_view name, const float* m, bool transpose = false);

    private:
        ShaderProgram(GLuint id)
            : m_id{ id }
        {}

        static ShaderProgram buildFromSources(const std::vector<ShaderSource>& sources);

        GLint uniformLocation(std::string_view name) const;

        struct StringHash
        {
            using is_transparent = void;
            std::size_t operator()(std::string_view sv) const noexcept { return std::hash<std::string_view>{}(sv); }
            std::size_t operator()(const std::string& s) const noexcept { return std::hash<std::string>{}(s); }
        };

        unsigned int m_id = 0;
        mutable std::unordered_map<std::string, GLint, StringHash, std::equal_to<>> m_locationCache;
    };
} // namespace nfx::graphics::gl
