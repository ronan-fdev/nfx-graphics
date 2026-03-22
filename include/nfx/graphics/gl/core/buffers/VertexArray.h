#pragma once

/**
 * \file VertexArray.h
 * \brief Declares a RAII wrapper for OpenGL vertex array objects and vertex layout configuration.
 */

#include "nfx/graphics/gl/core/GlTypes.h"
#include "VertexLayout.h"

namespace nfx::graphics::gl
{
    /**
     * \class VertexArray
     * \brief Owns an OpenGL vertex array object and applies vertex attribute layouts to it.
     */
    class VertexArray final
    {
    public:
        /**
         * \brief Creates a new OpenGL vertex array object.
         */
        VertexArray();

        /**
         * \brief Releases the underlying OpenGL vertex array object.
         */
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        /**
         * \brief Binds the vertex array object.
         */
        void bind() const;

        /**
         * \brief Unbinds the current vertex array object.
         */
        void unbind() const;

        /**
         * \brief Applies a vertex layout starting at attribute location 0 with divisor 0.
         * \param layout Vertex layout description to install on the vertex array.
         */
        void setVertexLayout(const VertexLayout& layout);

        /**
         * \brief Applies a vertex layout with an explicit first attribute location and divisor.
         * \param layout Vertex layout description to install on the vertex array.
         * \param firstLocation First shader attribute location used by the layout.
         * \param divisor Attribute divisor used for instanced rendering.
         */
        void setVertexLayout(const VertexLayout& layout, GLuint firstLocation, GLuint divisor);

        /**
         * \brief Returns the OpenGL object id owned by this vertex array.
         * \return Non-zero id when valid, 0 otherwise.
         */
        [[nodiscard]] GLuint id() const noexcept { return m_id; }

        /**
         * \brief Indicates whether the wrapper owns a valid OpenGL vertex array object.
         * \return True when id() is non-zero, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_id != 0; }

    private:
        GLuint m_id = 0;
        void release();
    };
} // namespace nfx::graphics::gl
