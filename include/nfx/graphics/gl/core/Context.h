#pragma once

/**
 * \file Context.h
 * \brief Declares the thread-local OpenGL context wrapper used to access the loaded Functions table.
 */

#include "Functions.h"

namespace nfx::graphics::gl
{
    /**
     * \class Context
     * \brief Represents the OpenGL function table for the context current on the calling thread.
     */
    class Context final
    {
    public:
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;
        Context(Context&&) = delete;
        Context& operator=(Context&&) = delete;

        /**
         * \brief Initializes the OpenGL function pointers for the calling thread's current context.
         *
         * Must be called once per thread after a GL context has been made current on that thread.
         * Subsequent calls on the same thread are no-ops.
         *
         * \return True if initialization succeeded, false otherwise.
         */
        static bool initialize();

        /**
         * \brief Returns true if the OpenGL function table has been initialized on the calling thread.
         */
        [[nodiscard]] static bool isInitialized() noexcept;

        /**
         * \brief Returns the Context for the calling thread.
         *
         * \pre initialize() must have been called on this thread.
         */
        static Context& current();

        /**
         * \brief Returns the OpenGL function table.
         */
        [[nodiscard]] const Functions& functions() const noexcept { return m_functions; }

        /**
         * \brief Returns the major version of the current OpenGL context.
         */
        [[nodiscard]] int majorVersion() const noexcept { return m_major; }

        /**
         * \brief Returns the minor version of the current OpenGL context.
         */
        [[nodiscard]] int minorVersion() const noexcept { return m_minor; }

        /**
         * \brief Returns true if the context supports at least the given OpenGL version.
         * \param major Required major OpenGL version.
         * \param minor Required minor OpenGL version.
         */
        [[nodiscard]] bool isVersionSupported(int major, int minor) const noexcept
        {
            return m_major > major || (m_major == major && m_minor >= minor);
        }

        /**
         * \brief Returns the maximum number of texture image units available to fragment shaders.
         */
        [[nodiscard]] int maxTextureImageUnits() const noexcept { return m_maxTextureImageUnits; }

        /**
         * \brief Returns the maximum number of vertex attribute locations.
         */
        [[nodiscard]] int maxVertexAttribs() const noexcept { return m_maxVertexAttribs; }

    private:
        Context() = default;
        ~Context() = default;

        static thread_local Context s_instance;

        Functions m_functions;
        bool m_initialized = false;
        int m_major = 0;
        int m_minor = 0;
        int m_maxTextureImageUnits = 16;
        int m_maxVertexAttribs = 16;
    };
} // namespace nfx::graphics::gl
