#pragma once

/**
 * \file ShaderCache.h
 * \brief Declares the cache used to store ShaderProgram instances.
 */

#include "nfx/graphics/gl/core/shaders/ShaderProgram.h"
#include "ResourceCache.h"

#include <cstdio>
#include <initializer_list>

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of shader programs keyed by ShaderHandle.
     */
    class ShaderCache final : public ResourceCache<ShaderTag, ShaderProgram>
    {
    public:
        /**
         * \brief Compiles and links a shader program from in-memory sources and stores it in the cache.
         * \param sources Shader stages and source strings passed to ShaderProgram::fromSources().
         * \return A stable handle referencing the cached program, or an invalid handle on failure.
         */
        [[nodiscard]] ShaderHandle compile(std::initializer_list<ShaderProgram::ShaderSource> sources)
        {
            ShaderProgram program = ShaderProgram::fromSources(sources);
            if (!program.isValid())
            {
                std::fprintf(stderr, "[ShaderCache] compile: shader compilation or linking failed\n");
                return {};
            }
            return add(std::move(program));
        }
    };
} // namespace nfx::graphics::gl
