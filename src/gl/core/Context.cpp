#include "nfx/graphics/gl/core/Context.h"

#include "Platform.h"
#include "internal/runtime/Error.h"

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
            f.glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &s_instance.m_maxColorAttachments);
            f.glGetIntegerv(GL_MAX_PATCH_VERTICES, &s_instance.m_maxPatchVertices);
            f.glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_instance.m_maxTextureImageUnits);
            f.glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &s_instance.m_maxVertexAttribs);
        }

        return s_instance.m_initialized;
    }

    bool Context::isInitialized() noexcept
    {
        return s_instance.m_initialized;
    }

    void Context::teardown() noexcept
    {
        s_instance.m_functions.teardown();
        s_instance.m_initialized = false;
        s_instance.m_major = 0;
        s_instance.m_minor = 0;
        s_instance.m_maxColorAttachments = 8;
        s_instance.m_maxPatchVertices = 1;
        s_instance.m_maxTextureImageUnits = 16;
        s_instance.m_maxVertexAttribs = 16;
    }

    Context& Context::current()
    {
        assert(
            s_instance.m_initialized &&
            "nfx::graphics::gl::Context::current() requires Context::initialize() on the calling thread");

        if (!s_instance.m_initialized)
        {
            internal::runtime::logError(
                "Context",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Programming,
                "current(): called before initialize() on this thread; returning uninitialized context");
        }
        return s_instance;
    }
} // namespace nfx::graphics::gl
