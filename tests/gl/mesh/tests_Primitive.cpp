#include <doctest/doctest.h>

#include <nfx/graphics/gl/mesh/Primitive.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

using namespace nfx::graphics::gl;

namespace
{
    bool indicesInRange(const MeshData& mesh)
    {
        if (mesh.vertexCount == 0)
        {
            return mesh.indexCount == 0;
        }

        if (mesh.indexCount == 0)
        {
            return true;
        }

        if (mesh.indexType == MeshData::IndexType::UInt32)
        {
            constexpr std::size_t indexByteSize = 4u;
            const std::byte* cursor = mesh.indexData.data();
            for (std::size_t i = 0; i < mesh.indexCount; ++i)
            {
                std::uint32_t idx = 0;
                std::memcpy(&idx, cursor, indexByteSize);
                if (static_cast<std::size_t>(idx) >= mesh.vertexCount)
                {
                    return false;
                }

                cursor += indexByteSize;
            }
            return true;
        }

        constexpr std::size_t indexByteSize = 2u;
        const std::byte* cursor = mesh.indexData.data();
        for (std::size_t i = 0; i < mesh.indexCount; ++i)
        {
            std::uint16_t idx = 0;
            std::memcpy(&idx, cursor, indexByteSize);
            if (static_cast<std::size_t>(idx) >= mesh.vertexCount)
            {
                return false;
            }

            cursor += indexByteSize;
        }
        return true;
    }
} // namespace

TEST_SUITE("Primitive")
{
    TEST_CASE("cube layout and counts")
    {
        const MeshData mesh = Primitive::cube();

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48); // 12 floats
        CHECK(mesh.vertexCount == 24);
        CHECK(mesh.vertexData.size() == 24u * 48u);
        CHECK(mesh.indexCount == 36);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("plane default layout and counts")
    {
        const MeshData mesh = Primitive::plane();

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48); // 12 floats
        CHECK(mesh.vertexCount == 4);
        CHECK(mesh.vertexData.size() == 4u * 48u);
        CHECK(mesh.indexCount == 6);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("plane clamps invalid subdivisions")
    {
        const MeshData mesh = Primitive::plane(0, 0);

        CHECK(mesh.vertexCount == 4);
        CHECK(mesh.indexCount == 6);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("uvSphere counts follow stacks and slices")
    {
        constexpr int stacks = 6;
        constexpr int slices = 10;
        const MeshData mesh = Primitive::uvSphere(stacks, slices);

        const std::size_t expectedVertices =
            static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t expectedIndices = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48); // 12 floats
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("uvSphere clamps invalid arguments")
    {
        const MeshData mesh = Primitive::uvSphere(0, 0);

        // clamps to stacks=1, slices=3
        CHECK(mesh.vertexCount == 8);
        CHECK(mesh.indexCount == 18);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("quad layout and counts")
    {
        const MeshData mesh = Primitive::quad();

        CHECK(mesh.layout.attributes().size() == 2);
        CHECK(mesh.layout.stride() == 20); // 5 floats
        CHECK(mesh.vertexCount == 4);
        CHECK(mesh.vertexData.size() == 4u * 20u);
        CHECK(mesh.indexCount == 6);
        CHECK(indicesInRange(mesh));
    }
}
