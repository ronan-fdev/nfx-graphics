#include "nfx/graphics/gl/core/Context.h"

#include "Platform.h"

#include <cassert>
#include <cstdio>

namespace nfx::graphics::gl
{
    thread_local Context Context::s_instance;

    bool Context::initialize()
    {
        if (s_instance.m_initialized)
        {
            return true;
        }

        ::glGetIntegerv(GL_MAJOR_VERSION, &s_instance.m_major);
        ::glGetIntegerv(GL_MINOR_VERSION, &s_instance.m_minor);

        s_instance.m_initialized = s_instance.m_functions.initialize();
        if (s_instance.m_initialized)
        {
            const auto& f = s_instance.m_functions;
            f.glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_instance.m_maxTextureImageUnits);
            f.glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &s_instance.m_maxVertexAttribs);
        }

        return s_instance.m_initialized;
    }

    bool Context::isInitialized() noexcept
    {
        return s_instance.m_initialized;
    }

    Context& Context::current()
    {
        assert(
            s_instance.m_initialized &&
            "nfx::graphics::gl::Context::current() requires Context::initialize() on the calling thread");

        if (!s_instance.m_initialized)
        {
            std::fprintf(
                stderr,
                "[Context] current(): called before initialize() on this thread; returning uninitialized context\n");
        }
        return s_instance;
    }
} // namespace nfx::graphics::gl
