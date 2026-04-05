#pragma once

/**
 * \file MeshData.h
 * \brief Declares the CPU-side mesh data container used before uploading geometry to a Mesh.
 */

#include "nfx/graphics/gl/core/buffers/VertexLayout.h"
#include "nfx/graphics/gl/mesh/MeshTypes.h"
#include "nfx/graphics/math/geometry/Bounds.h"

#include <cstddef>
#include <cstring>
#include <cassert>
#include <optional>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief CPU-side mesh data made of packed vertex attributes, indices and their layout description.
     */
    struct MeshData
    {
        /**
         * \brief Supported index storage formats.
         */
        using IndexType = MeshIndexType;

        std::vector<std::byte> vertexData; ///< Packed vertex buffer data matching the declared layout
        std::size_t vertexCount = 0;       ///< Number of vertices stored in vertexData
        VertexLayout layout;               ///< Vertex attribute layout describing the contents of vertexData

        std::vector<std::byte> indexData;                 ///< Optional packed index buffer data
        std::size_t indexCount = 0;                       ///< Number of indices stored in indexData
        IndexType indexType = IndexType::UInt32;          ///< Index element format used by indexData
        std::optional<math::Bounds::AABB> boundsAABB;     ///< Optional default mesh bounding box
        std::optional<math::Bounds::Sphere> boundsSphere; ///< Optional default mesh bounding sphere

        /**
         * \brief Sets packed vertex bytes and derives vertexCount from layout stride.
         * \param data Pointer to packed vertex bytes, or nullptr when sizeBytes is zero.
         * \param sizeBytes Total size in bytes of packed vertex data.
         * \param inLayout Vertex layout describing one vertex entry.
         */
        void setVertexData(const void* data, std::size_t sizeBytes, const VertexLayout& inLayout)
        {
            layout = inLayout;
            vertexData.resize(sizeBytes);
            if (sizeBytes > 0 && data != nullptr)
            {
                std::memcpy(vertexData.data(), data, sizeBytes);
            }

            const std::size_t stride = layout.stride();
            assert(
                (stride == 0 || sizeBytes % stride == 0) &&
                "MeshData::setVertexData: sizeBytes is not a multiple of layout stride");
            vertexCount = (stride > 0) ? (sizeBytes / stride) : 0;
        }

        /**
         * \brief Sets packed index bytes with explicit type and count.
         * \param data Pointer to packed index bytes, or nullptr when count is zero.
         * \param count Number of index elements.
         * \param type Index element format.
         */
        void setIndexData(const void* data, std::size_t count, IndexType type)
        {
            indexType = type;
            indexCount = count;

            const std::size_t elemSize = (type == IndexType::UInt16) ? sizeof(std::uint16_t) : sizeof(std::uint32_t);
            const std::size_t sizeBytes = count * elemSize;

            indexData.resize(sizeBytes);
            if (sizeBytes > 0 && data != nullptr)
            {
                std::memcpy(indexData.data(), data, sizeBytes);
            }
        }
    };
} // namespace nfx::graphics::gl
