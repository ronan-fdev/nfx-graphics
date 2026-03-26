#include <doctest/doctest.h>

#include <nfx/graphics/gl/mesh/MeshData.h>
#include <nfx/graphics/gl/core/buffers/VertexLayout.h>

#include <cstddef>

using namespace nfx::graphics::gl;

TEST_SUITE("MeshData")
{
    TEST_CASE("setIndexData correctly calculates byte size for UInt16")
    {
        const std::uint16_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        MeshData mesh;

        mesh.setIndexData(indices, 6, MeshIndexType::UInt16);

        CHECK(mesh.indexCount == 6);
        CHECK(mesh.indexType == MeshIndexType::UInt16);
        CHECK(mesh.indexData.size() == 6 * sizeof(std::uint16_t));
    }

    TEST_CASE("setIndexData correctly calculates byte size for UInt32")
    {
        const std::uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        MeshData mesh;

        mesh.setIndexData(indices, 6, MeshIndexType::UInt32);

        CHECK(mesh.indexCount == 6);
        CHECK(mesh.indexType == MeshIndexType::UInt32);
        CHECK(mesh.indexData.size() == 6 * sizeof(std::uint32_t));
    }

    TEST_CASE("setIndexData copies index data correctly")
    {
        const std::uint16_t indices[3] = { 10, 20, 30 };
        MeshData mesh;

        mesh.setIndexData(indices, 3, MeshIndexType::UInt16);

        CHECK(mesh.indexData.size() == 3 * sizeof(std::uint16_t));
        const auto* copied = reinterpret_cast<const std::uint16_t*>(mesh.indexData.data());
        CHECK(copied[0] == 10);
        CHECK(copied[1] == 20);
        CHECK(copied[2] == 30);
    }

    TEST_CASE("setVertexData correctly derives vertexCount from layout stride")
    {
        const float verts[24] = {
            0.f, 0.f, 0.f, // v0 pos
            1.f, 0.f, 0.f, // v1 pos
            0.f, 1.f, 0.f, // v2 pos
            1.f, 1.f, 0.f, // v3 pos
            0.f, 0.f, 1.f, // v0 normal
            1.f, 0.f, 0.f, // v1 normal
            0.f, 1.f, 0.f, // v2 normal
            1.f, 1.f, 0.f  // v3 normal
        };

        VertexLayout layout{ VertexLayout::Float3, VertexLayout::Float3 }; // pos + normal

        MeshData mesh;
        mesh.setVertexData(verts, sizeof(verts), layout);

        const std::size_t expectedStride = 6 * sizeof(float); // 2 * Float3
        const std::size_t expectedCount = sizeof(verts) / expectedStride;

        CHECK(mesh.vertexCount == expectedCount);
        CHECK(mesh.vertexData.size() == sizeof(verts));
    }

    TEST_CASE("MeshIndexType matches Mesh::IndexType alias")
    {
        MeshData mesh;
        MeshIndexType rawType = MeshIndexType::UInt32;
        MeshData::IndexType aliasType = MeshIndexType::UInt32;

        CHECK(rawType == aliasType);
        CHECK(sizeof(rawType) == sizeof(aliasType));
    }
}
