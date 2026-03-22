#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"

#include "nfx/graphics/gl/core/Context.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>

namespace nfx::graphics::gl
{
    namespace
    {
        std::string trimTrailingLineBreaks(std::string text)
        {
            while (!text.empty() && (text.back() == '\n' || text.back() == '\r' || text.back() == '\0'))
            {
                text.pop_back();
            }
            return text;
        }

        std::string shaderInfoLog(GLuint shaderId)
        {
            const auto& gl = Context::current().functions();

            GLint logLength = 0;
            gl.glGetShaderiv(shaderId, INFO_LOG_LENGTH, &logLength);
            if (logLength <= 1)
            {
                return {};
            }

            std::string log(static_cast<std::size_t>(logLength), '\0');
            GLsizei written = 0;
            gl.glGetShaderInfoLog(shaderId, logLength, &written, log.data());
            if (written > 0)
            {
                log.resize(static_cast<std::size_t>(written));
            }

            return trimTrailingLineBreaks(std::move(log));
        }

        std::string programInfoLog(GLuint programId)
        {
            const auto& gl = Context::current().functions();

            GLint logLength = 0;
            gl.glGetProgramiv(programId, INFO_LOG_LENGTH, &logLength);
            if (logLength <= 1)
            {
                return {};
            }

            std::string log(static_cast<std::size_t>(logLength), '\0');
            GLsizei written = 0;
            gl.glGetProgramInfoLog(programId, logLength, &written, log.data());
            if (written > 0)
            {
                log.resize(static_cast<std::size_t>(written));
            }

            return trimTrailingLineBreaks(std::move(log));
        }

        const char* stageToString(ShaderProgram::Stage stage)
        {
            switch (stage)
            {
                case ShaderProgram::Stage::Vertex:
                    return "Vertex";
                case ShaderProgram::Stage::Fragment:
                    return "Fragment";
                case ShaderProgram::Stage::Geometry:
                    return "Geometry";
                case ShaderProgram::Stage::TessControl:
                    return "TessControl";
                case ShaderProgram::Stage::TessEval:
                    return "TessEval";
                case ShaderProgram::Stage::Compute:
                    return "Compute";
            }
            assert(false && "stageToString(): unknown ShaderProgram::Stage");
            return "Unknown";
        }

        bool compileShader(unsigned int shaderId, std::string_view code, ShaderProgram::Stage stage)
        {
            const auto& gl = Context::current().functions();

            const char* source = code.data();
            const int length = static_cast<int>(code.size());
            gl.glShaderSource(shaderId, 1, &source, &length);
            gl.glCompileShader(shaderId);

            int success = 0;
            gl.glGetShaderiv(shaderId, COMPILE_STATUS, &success);
            if (!success)
            {
                std::string infoStr = shaderInfoLog(shaderId);
                if (infoStr.empty())
                {
                    infoStr = "(no compiler log available)";
                }

                std::fprintf(
                    stderr,
                    "\n[ShaderProgram] %s shader compilation failed\n"
                    "----------------------------------------\n"
                    "%s\n"
                    "----------------------------------------\n",
                    stageToString(stage),
                    infoStr.c_str());
                return false;
            }
            return true;
        }

        bool linkProgram(unsigned int programId)
        {
            const auto& gl = Context::current().functions();

            gl.glLinkProgram(programId);

            int success = 0;
            gl.glGetProgramiv(programId, LINK_STATUS, &success);
            if (!success)
            {
                std::string infoStr = programInfoLog(programId);
                if (infoStr.empty())
                {
                    infoStr = "(no linker log available)";
                }

                std::fprintf(
                    stderr,
                    "\n[ShaderProgram] Program link failed\n"
                    "----------------------------------------\n"
                    "%s\n"
                    "----------------------------------------\n",
                    infoStr.c_str());
                return false;
            }
            return true;
        }

        bool validatePipeline(const std::vector<ShaderProgram::ShaderSource>& sources)
        {
            if (sources.empty())
            {
                std::fprintf(stderr, "[ShaderProgram] Pipeline requires at least one stage\n");
                return false;
            }

            bool hasCompute = false;
            bool hasGraphics = false;
            std::unordered_set<ShaderProgram::Stage> seenStages;

            for (const auto& src : sources)
            {
                if (!seenStages.insert(src.stage).second)
                {
                    std::fprintf(stderr, "[ShaderProgram] Duplicate shader stage in pipeline\n");
                    return false;
                }

                if (src.stage == ShaderProgram::Stage::Compute)
                {
                    hasCompute = true;
                }
                else
                {
                    hasGraphics = true;
                }
            }

            if (hasCompute && hasGraphics)
            {
                std::fprintf(stderr, "[ShaderProgram] Cannot mix compute and graphics stages\n");
                return false;
            }

            if (hasCompute && sources.size() > 1)
            {
                std::fprintf(stderr, "[ShaderProgram] Compute shader must be alone\n");
                return false;
            }

            if (hasGraphics)
            {
                bool hasVertex = false, hasFragment = false;
                for (const auto& src : sources)
                {
                    if (src.stage == ShaderProgram::Stage::Vertex)
                    {
                        hasVertex = true;
                    }
                    if (src.stage == ShaderProgram::Stage::Fragment)
                    {
                        hasFragment = true;
                    }
                }

                if (!hasVertex || !hasFragment)
                {
                    std::fprintf(
                        stderr, "[ShaderProgram] Graphics pipeline requires at least Vertex + Fragment shaders\n");
                    return false;
                }
            }

            return true;
        }
    } // namespace

    ShaderProgram ShaderProgram::buildFromSources(const std::vector<ShaderSource>& sourceVec)
    {
        const auto& gl = Context::current().functions();
        std::vector<unsigned int> shaderIds;
        shaderIds.reserve(sourceVec.size());

        for (const auto& src : sourceVec)
        {
            const unsigned int shaderId = gl.glCreateShader(static_cast<GLenum>(src.stage));
            if (shaderId == 0)
            {
                std::fprintf(stderr, "[ShaderProgram] glCreateShader failed for stage %s\n", stageToString(src.stage));
                for (unsigned int id : shaderIds)
                {
                    gl.glDeleteShader(id);
                }
                return {};
            }

            if (!compileShader(shaderId, src.code, src.stage))
            {
                for (unsigned int id : shaderIds)
                {
                    gl.glDeleteShader(id);
                }
                gl.glDeleteShader(shaderId);
                return {};
            }
            shaderIds.push_back(shaderId);
        }

        const unsigned int programId = gl.glCreateProgram();
        if (programId == 0)
        {
            std::fprintf(stderr, "[ShaderProgram] glCreateProgram failed\n");
            for (unsigned int shaderId : shaderIds)
            {
                gl.glDeleteShader(shaderId);
            }
            return {};
        }

        for (unsigned int shaderId : shaderIds)
        {
            gl.glAttachShader(programId, shaderId);
        }

        if (!linkProgram(programId))
        {
            for (unsigned int shaderId : shaderIds)
            {
                gl.glDeleteShader(shaderId);
            }
            gl.glDeleteProgram(programId);
            return {};
        }

        for (unsigned int shaderId : shaderIds)
        {
            gl.glDeleteShader(shaderId);
        }

        return ShaderProgram{ programId };
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
        : m_id{ other.m_id },
          m_locationCache{ std::move(other.m_locationCache) }
    {
        other.m_id = 0;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            m_locationCache = std::move(other.m_locationCache);
            other.m_id = 0;
        }
        return *this;
    }

    void ShaderProgram::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteProgram(m_id);
            m_id = 0;

            m_locationCache.clear();
        }
    }

    void ShaderProgram::bind() const
    {
        Context::current().functions().glUseProgram(m_id);
    }

    void ShaderProgram::unbind()
    {
        Context::current().functions().glUseProgram(0);
    }

    ShaderProgram ShaderProgram::fromSources(std::initializer_list<ShaderSource> sources)
    {
        std::vector<ShaderSource> sourceVec(sources);

        if (!validatePipeline(sourceVec))
        {
            return {};
        }

        return buildFromSources(sourceVec);
    }

    ShaderProgram ShaderProgram::fromFiles(std::initializer_list<ShaderFile> files)
    {
        std::vector<std::string> codes;
        codes.reserve(files.size());

        std::vector<ShaderSource> sourceVec;
        sourceVec.reserve(files.size());

        for (const auto& file : files)
        {
            std::ifstream stream(file.path);
            if (!stream.is_open())
            {
                std::fprintf(stderr, "[ShaderProgram] Failed to open file: %s\n", file.path.string().c_str());
                return {};
            }

            std::ostringstream buffer;
            buffer << stream.rdbuf();
            codes.push_back(buffer.str());
            sourceVec.push_back({ file.stage, codes.back() });
        }

        if (!validatePipeline(sourceVec))
        {
            return {};
        }

        return buildFromSources(sourceVec);
    }

    void ShaderProgram::setUniform(std::string_view name, int value)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniform1i(location, value);
        }
    }

    void ShaderProgram::setUniform(std::string_view name, float value)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniform1f(location, value);
        }
    }

    void ShaderProgram::setUniform(std::string_view name, const UniformVec2& v)
    {
        setUniformVec2(name, v.data());
    }

    void ShaderProgram::setUniform(std::string_view name, const UniformVec3& v)
    {
        setUniformVec3(name, v.data());
    }

    void ShaderProgram::setUniform(std::string_view name, const UniformVec4& v)
    {
        setUniformVec4(name, v.data());
    }

    void ShaderProgram::setUniform(std::string_view name, const UniformMat3& m, bool transpose)
    {
        setUniformMat3(name, m.data(), transpose);
    }

    void ShaderProgram::setUniform(std::string_view name, const UniformMat4& m, bool transpose)
    {
        setUniformMat4(name, m.data(), transpose);
    }

    void ShaderProgram::setUniformVec2(std::string_view name, const float* v)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniform2fv(location, 1, v);
        }
    }

    void ShaderProgram::setUniformVec3(std::string_view name, const float* v)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniform3fv(location, 1, v);
        }
    }

    void ShaderProgram::setUniformVec4(std::string_view name, const float* v)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniform4fv(location, 1, v);
        }
    }

    void ShaderProgram::setUniformMat3(std::string_view name, const float* m, bool transpose)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniformMatrix3fv(location, 1, transpose, m);
        }
    }

    void ShaderProgram::setUniformMat4(std::string_view name, const float* m, bool transpose)
    {
        const GLint location = uniformLocation(name);
        if (location != -1)
        {
            Context::current().functions().glUniformMatrix4fv(location, 1, transpose, m);
        }
    }

    GLint ShaderProgram::uniformLocation(std::string_view name) const
    {
        auto it = m_locationCache.find(name);
        if (it != m_locationCache.end())
        {
            return it->second;
        }

        // Cache-miss path
        const std::string uniformName(name);
        const GLint location = Context::current().functions().glGetUniformLocation(m_id, uniformName.c_str());
        m_locationCache.emplace(uniformName, location);
        return location;
    }
} // namespace nfx::graphics::gl
