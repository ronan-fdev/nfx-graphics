#include "nfx/graphics/gl/core/textures/Sampler.h"

#include "nfx/graphics/gl/core/Context.h"
#include "internal/runtime/Error.h"

#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    namespace
    {
        bool isValidMagFilter(Sampler::Filter filter) noexcept
        {
            return filter == Sampler::Filter::Nearest || filter == Sampler::Filter::Linear;
        }
    } // namespace

    Sampler Sampler::create()
    {
        return create(Params{});
    }

    Sampler Sampler::create(const Params& params)
    {
        if (!isValidMagFilter(params.magFilter))
        {
            internal::runtime::logError(
                "Sampler",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: magFilter must be Nearest or Linear");
            return {};
        }

        const auto& gl = Context::current().functions();

        GLuint id = 0;
        gl.glGenSamplers(1, &id);
        if (id == 0)
        {
            return {};
        }

        gl.glSamplerParameteri(id, TEXTURE_MIN_FILTER, static_cast<GLint>(params.minFilter));
        gl.glSamplerParameteri(id, TEXTURE_MAG_FILTER, static_cast<GLint>(params.magFilter));
        gl.glSamplerParameteri(id, TEXTURE_WRAP_S, static_cast<GLint>(params.wrapS));
        gl.glSamplerParameteri(id, TEXTURE_WRAP_T, static_cast<GLint>(params.wrapT));
        gl.glSamplerParameteri(id, TEXTURE_WRAP_R, static_cast<GLint>(params.wrapR));
        gl.glSamplerParameteri(id, TEXTURE_COMPARE_MODE, static_cast<GLint>(params.compareMode));
        gl.glSamplerParameteri(id, TEXTURE_COMPARE_FUNC, static_cast<GLint>(params.compareFunc));

        return Sampler{ id, params };
    }

    Sampler::Sampler(Sampler&& other) noexcept
        : m_id{ other.m_id },
          m_params{ other.m_params }
    {
        other.m_id = 0;
    }

    Sampler& Sampler::operator=(Sampler&& other) noexcept
    {
        if (this != &other)
        {
            release();
            m_id = other.m_id;
            m_params = other.m_params;
            other.m_id = 0;
        }
        return *this;
    }

    void Sampler::release()
    {
        if (m_id != 0)
        {
            Context::current().functions().glDeleteSamplers(1, &m_id);
            m_id = 0;
        }
    }

    void Sampler::bind(GLuint unit) const
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(
                static_cast<int>(unit) < ctx.maxTextureImageUnits() &&
                "Sampler::bind(): unit exceeds GL_MAX_TEXTURE_IMAGE_UNITS");
            return;
        }
        ctx.functions().glBindSampler(unit, m_id);
    }

    void Sampler::unbind(GLuint unit)
    {
        const auto& ctx = Context::current();
        if (static_cast<int>(unit) >= ctx.maxTextureImageUnits())
        {
            assert(
                static_cast<int>(unit) < ctx.maxTextureImageUnits() &&
                "Sampler::unbind(): unit exceeds GL_MAX_TEXTURE_IMAGE_UNITS");
            return;
        }
        ctx.functions().glBindSampler(unit, 0);
    }
} // namespace nfx::graphics::gl
