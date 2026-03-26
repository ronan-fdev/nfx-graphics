#pragma once

/**
 * \file Mesh.h
 * \brief Declares the runtime mesh wrapper owning GPU vertex/index buffers and vertex array state.
 */

#include "nfx/graphics/gl/core/buffers/Buffer.h"
#include "nfx/graphics/gl/core/buffers/VertexArray.h"
#include "nfx/graphics/gl/mesh/MeshTypes.h"

#include <cstddef>
#include <optional>

namespace nfx::graphics::gl
{
    struct MeshData;

    /**
     * \brief Runtime mesh object owning GPU buffers and the vertex array configuration used for rendering.
     */
    class Mesh final
    {
    public:
        /**
         * \brief Supported index buffer element formats.
         */
        using IndexType = MeshIndexType;

        /**
         * \brief Constructs an empty, invalid mesh. No GPU resources are allocated.
         *
         * Use \ref create() to build a valid mesh from vertex/index data.
         */
        Mesh() = default;

        ~Mesh() = default;

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&&) noexcept = default;
        Mesh& operator=(Mesh&&) noexcept = default;

        /**
         * \brief Describes the vertex and index data used to create a mesh.
         */
        struct Desc
        {
            const void* vertices = nullptr;          ///< Pointer to packed vertex data
            std::size_t vertexDataSize = 0;          ///< Size in bytes of the packed vertex data
            VertexLayout layout;                     ///< Vertex attribute layout describing the vertex buffer contents
            const void* indices = nullptr;           ///< Optional pointer to packed index data
            std::size_t indexCount = 0;              ///< Number of indices stored in the index buffer
            IndexType indexType = IndexType::UInt32; ///< Index element format
            Buffer::Usage usage = Buffer::Usage::StaticDraw; ///< Usage hint applied to uploaded GPU buffers
        };

        /**
         * \brief Creates a mesh directly from universal MeshData.
         * \param data CPU-side packed mesh data container.
         * \param usage Usage hint applied to uploaded GPU buffers.
         * \return Valid mesh on success, otherwise an invalid mesh.
         *
         * Primary API for creating meshes from Primitive generators or owned data containers.
         */
        static Mesh create(const MeshData& data, Buffer::Usage usage = Buffer::Usage::StaticDraw);

        /**
         * \brief Creates a mesh from CPU-side vertex and optional index data.
         * \param desc Description of the vertex/index buffers and layout to upload.
         * \return Valid mesh on success, otherwise an invalid mesh.
         *
         * Use this for direct pointer uploads when data is already external/optimized.
         * MeshData::create() is recommended for typical usage.
         */
        static Mesh create(const Desc& desc);

        /**
         * \brief Uploads per-instance vertex attributes and configures them on the mesh vertex array.
         * \param data Pointer to the instance buffer data.
         * \param size Size in bytes of the instance buffer data.
         * \param layout Vertex layout describing one instance entry.
         * \param firstLocation First attribute location used for instance attributes.
         * \param usage Usage hint applied to the instance buffer.
         * \pre This mesh must already be valid.
         */
        void setInstanceData(
            const void* data,
            std::size_t size,
            const VertexLayout& layout,
            GLuint firstLocation,
            Buffer::Usage usage = Buffer::Usage::DynamicDraw);

        /**
         * \brief Binds the mesh vertex array object.
         */
        void bind() const;

        /**
         * \brief Unbinds the mesh vertex array object.
         */
        void unbind() const;

        /**
         * \brief Returns whether GPU resources were successfully created for this mesh.
         * \return True when the mesh owns a valid VAO, false otherwise.
         */
        [[nodiscard]] bool isValid() const noexcept { return m_vao.has_value(); }

        /**
         * \brief Returns whether this mesh has an index buffer.
         * \return True when indexCount() is greater than zero, false otherwise.
         */
        [[nodiscard]] bool isIndexed() const noexcept { return m_indexCount > 0; }

        /**
         * \brief Returns the number of vertices stored by this mesh.
         * \return Vertex count.
         */
        [[nodiscard]] std::size_t vertexCount() const noexcept { return m_vertexCount; }

        /**
         * \brief Returns the number of indices stored by this mesh.
         * \return Index count.
         */
        [[nodiscard]] std::size_t indexCount() const noexcept { return m_indexCount; }

        /**
         * \brief Returns the index element type used by this mesh.
         * \return Mesh index type.
         */
        [[nodiscard]] IndexType indexType() const noexcept { return m_indexType; }

    private:
        std::optional<VertexArray> m_vao;
        std::optional<Buffer> m_vbo;
        std::optional<Buffer> m_ebo;
        std::optional<Buffer> m_instanceVbo;

        std::size_t m_vertexCount = 0;
        std::size_t m_indexCount = 0;
        IndexType m_indexType = IndexType::UInt32;
    };
} // namespace nfx::graphics::gl
