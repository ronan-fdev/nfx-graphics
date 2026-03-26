#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/mesh/MeshData.h"

#include <cassert>
#include <cstdio>
#include <cstdint>

namespace nfx::graphics::gl
{
    Mesh Mesh::create(const MeshData& data, Buffer::Usage usage)
    {
        Desc desc{};
        desc.vertices = data.vertexData.empty() ? nullptr : data.vertexData.data();
        desc.vertexDataSize = data.vertexData.size();
        desc.layout = data.layout;
        desc.indices = data.indexData.empty() ? nullptr : data.indexData.data();
        desc.indexCount = data.indexCount;
        desc.indexType = data.indexType;
        desc.usage = usage;
        return create(desc);
    }

    Mesh Mesh::create(const Desc& desc)
    {
        Mesh mesh;

        const std::size_t vertexStride = desc.layout.stride();
        if (desc.vertices == nullptr || desc.vertexDataSize == 0)
        {
            std::fprintf(stderr, "[Mesh] create: vertices are required and vertexDataSize must be > 0\n");
            return {};
        }

        if (vertexStride == 0)
        {
            std::fprintf(stderr, "[Mesh] create: vertex layout stride must be > 0\n");
            return {};
        }

        if ((desc.vertexDataSize % vertexStride) != 0)
        {
            std::fprintf(stderr, "[Mesh] create: vertexDataSize must be a multiple of layout stride\n");
            return {};
        }

        if (desc.indexCount > 0 && desc.indices == nullptr)
        {
            std::fprintf(stderr, "[Mesh] create: indices pointer is null but indexCount is > 0\n");
            return {};
        }

        mesh.m_vbo.emplace(Buffer::Target::VertexAttributesArray);
        mesh.m_vbo->setData(desc.vertices, desc.vertexDataSize, desc.usage);
        mesh.m_vertexCount = desc.vertexDataSize / vertexStride;

        if (desc.indices && desc.indexCount > 0)
        {
            const std::size_t elemSize = (desc.indexType == IndexType::UInt16) ? sizeof(uint16_t) : sizeof(uint32_t);
            mesh.m_ebo.emplace(Buffer::Target::VertexIndicesArray);
            mesh.m_ebo->setData(desc.indices, desc.indexCount * elemSize, desc.usage);
            mesh.m_indexCount = desc.indexCount;
            mesh.m_indexType = desc.indexType;
        }

        mesh.m_vao.emplace();
        mesh.m_vao->bind();
        mesh.m_vbo->bind();
        if (mesh.m_ebo)
        {
            mesh.m_ebo->bind();
        }
        mesh.m_vao->setVertexLayout(desc.layout);
        mesh.m_vao->unbind();

        return mesh;
    }

    void Mesh::setInstanceData(
        const void* data, std::size_t size, const VertexLayout& layout, GLuint firstLocation, Buffer::Usage usage)
    {
        if (!m_vao)
        {
            std::fprintf(stderr, "[Mesh] setInstanceData: mesh is invalid\n");
            return;
        }

        const std::size_t instanceStride = layout.stride();
        if (data == nullptr || size == 0)
        {
            std::fprintf(stderr, "[Mesh] setInstanceData: data is required and size must be > 0\n");
            return;
        }

        if (instanceStride == 0)
        {
            std::fprintf(stderr, "[Mesh] setInstanceData: instance layout stride must be > 0\n");
            return;
        }

        if ((size % instanceStride) != 0)
        {
            std::fprintf(stderr, "[Mesh] setInstanceData: size must be a multiple of layout stride\n");
            return;
        }

        if (!m_instanceVbo)
        {
            m_instanceVbo.emplace(Buffer::Target::VertexAttributesArray);
        }

        m_instanceVbo->setData(data, size, usage);

        m_vao->bind();
        m_instanceVbo->bind();
        m_vao->setVertexLayout(layout, firstLocation, 1);
        m_vao->unbind();
    }

    void Mesh::bind() const
    {
        if (m_vao)
        {
            m_vao->bind();
        }
    }

    void Mesh::unbind() const
    {
        if (m_vao)
        {
            m_vao->unbind();
        }
    }
} // namespace nfx::graphics::gl
