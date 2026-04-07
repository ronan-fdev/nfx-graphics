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

    TEST_CASE("icosphere base counts at subdivision 0")
    {
        const MeshData mesh = Primitive::icosphere(0);

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == 12);
        CHECK(mesh.vertexData.size() == 12u * 48u);
        CHECK(mesh.indexCount == 60);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("icosphere clamps negative subdivisions")
    {
        const MeshData clamped = Primitive::icosphere(-3);
        const MeshData zero = Primitive::icosphere(0);

        CHECK(clamped.vertexCount == zero.vertexCount);
        CHECK(clamped.indexCount == zero.indexCount);
        CHECK(indicesInRange(clamped));
    }

    TEST_CASE("cylinder counts follow slices and stacks")
    {
        constexpr int slices = 12;
        constexpr int stacks = 3;
        const MeshData mesh = Primitive::cylinder(0.5f, 1.0f, slices, stacks);

        const std::size_t sideVertices = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t capVertices = 2u * (static_cast<std::size_t>(slices) + 2u);
        const std::size_t expectedVertices = sideVertices + capVertices;

        const std::size_t sideIndices = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;
        const std::size_t capIndices = static_cast<std::size_t>(slices) * 6u;
        const std::size_t expectedIndices = sideIndices + capIndices;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("cylinder clamps invalid parameters")
    {
        const MeshData mesh = Primitive::cylinder(0.0f, 0.0f, 0, 0);

        // clamps to slices=3, stacks=1
        CHECK(mesh.vertexCount == 18);
        CHECK(mesh.indexCount == 36);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("cone counts follow slices and stacks")
    {
        constexpr int slices = 12;
        constexpr int stacks = 3;
        const MeshData mesh = Primitive::cone(0.5f, 1.0f, slices, stacks);

        const std::size_t sideVertices = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t capVertices = static_cast<std::size_t>(slices) + 2u;
        const std::size_t expectedVertices = sideVertices + capVertices;

        const std::size_t sideIndices = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;
        const std::size_t capIndices = static_cast<std::size_t>(slices) * 3u;
        const std::size_t expectedIndices = sideIndices + capIndices;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("cone clamps invalid parameters")
    {
        const MeshData mesh = Primitive::cone(0.0f, 0.0f, 0, 0);

        // clamps to slices=3, stacks=1
        CHECK(mesh.vertexCount == 13);
        CHECK(mesh.indexCount == 27);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("capsule counts follow slices and hemisphere stacks")
    {
        constexpr int slices = 12;
        constexpr int hemi = 4;
        const MeshData mesh = Primitive::capsule(0.5f, 1.0f, slices, hemi);

        const std::size_t generatedRings = static_cast<std::size_t>(2 * hemi + 1);
        const std::size_t expectedVertices = generatedRings * static_cast<std::size_t>(slices + 1);
        const std::size_t expectedIndices = (generatedRings - 1u) * static_cast<std::size_t>(slices) * 6u;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("capsule clamps invalid parameters")
    {
        const MeshData mesh = Primitive::capsule(0.0f, 0.0f, 0, 0);

        // clamps to radius=0.5, height=1.0, slices=3, hemisphereStacks=1
        CHECK(mesh.vertexCount == 12);
        CHECK(mesh.indexCount == 36);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("disk counts follow slices")
    {
        constexpr int slices = 12;
        const MeshData mesh = Primitive::disk(0.5f, slices);

        const std::size_t expectedVertices = static_cast<std::size_t>(slices) + 2u;
        const std::size_t expectedIndices = static_cast<std::size_t>(slices) * 3u;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("disk clamps invalid parameters")
    {
        const MeshData mesh = Primitive::disk(0.0f, 0);

        // clamps to radius=0.5, slices=3
        CHECK(mesh.vertexCount == 5);
        CHECK(mesh.indexCount == 9);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("pyramid layout and counts")
    {
        const MeshData mesh = Primitive::pyramid(0.5f, 1.0f);

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == 16);
        CHECK(mesh.vertexData.size() == 16u * 48u);
        CHECK(mesh.indexCount == 18);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("pyramid clamps invalid parameters")
    {
        const MeshData mesh = Primitive::pyramid(0.0f, 0.0f);

        CHECK(mesh.vertexCount == 16);
        CHECK(mesh.indexCount == 18);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("tetrahedron layout and counts")
    {
        const MeshData mesh = Primitive::tetrahedron(0.5f, 1.0f);

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == 12);
        CHECK(mesh.vertexData.size() == 12u * 48u);
        CHECK(mesh.indexCount == 12);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("tetrahedron clamps invalid parameters")
    {
        const MeshData mesh = Primitive::tetrahedron(0.0f, 0.0f);

        CHECK(mesh.vertexCount == 12);
        CHECK(mesh.indexCount == 12);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("tube counts follow slices and stacks")
    {
        constexpr int slices = 12;
        constexpr int stacks = 3;
        const MeshData mesh = Primitive::tube(0.5f, 1.0f, slices, stacks);

        const std::size_t expectedVertices =
            static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t expectedIndices = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("tube clamps invalid parameters")
    {
        const MeshData mesh = Primitive::tube(0.0f, 0.0f, 0, 0);

        // clamps to radius=0.5, height=1.0, slices=3, stacks=1
        CHECK(mesh.vertexCount == 8);
        CHECK(mesh.indexCount == 18);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("pipe counts follow slices and stacks")
    {
        constexpr int slices = 12;
        constexpr int stacks = 3;
        const MeshData mesh = Primitive::pipe(0.5f, 0.35f, 1.0f, slices, stacks);

        // outer shell + inner shell + top cap + bottom cap
        const std::size_t shellVerts = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t capVerts = static_cast<std::size_t>(slices + 1) * 2u;
        const std::size_t expectedVertices = 2u * shellVerts + 2u * capVerts;

        const std::size_t shellIndices = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;
        const std::size_t capIndices = static_cast<std::size_t>(slices) * 6u;
        const std::size_t expectedIndices = 2u * shellIndices + 2u * capIndices;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("pipe clamps invalid parameters")
    {
        const MeshData mesh = Primitive::pipe(0.0f, 0.0f, 0.0f, 0, 0);

        // clamps to outerRadius=0.5, innerRadius=0.35, height=1.0, slices=3, stacks=1
        CHECK(mesh.vertexCount == 32);
        CHECK(mesh.indexCount == 72);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("pipe rejects innerRadius >= outerRadius")
    {
        const MeshData mesh = Primitive::pipe(0.5f, 0.5f, 1.0f, 6, 1);

        // innerRadius clamped to outerRadius * 0.7 = 0.35
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("torus counts follow major and minor stacks")
    {
        constexpr int majorStacks = 12;
        constexpr int minorStacks = 8;
        const MeshData mesh = Primitive::torus(0.6f, 0.2f, majorStacks, minorStacks);

        const std::size_t expectedVertices =
            static_cast<std::size_t>(majorStacks) * static_cast<std::size_t>(minorStacks + 1);
        const std::size_t expectedIndices =
            static_cast<std::size_t>(majorStacks) * static_cast<std::size_t>(minorStacks) * 6u;

        CHECK(mesh.layout.attributes().size() == 4);
        CHECK(mesh.layout.stride() == 48);
        CHECK(mesh.vertexCount == expectedVertices);
        CHECK(mesh.vertexData.size() == expectedVertices * 48u);
        CHECK(mesh.indexCount == expectedIndices);
        CHECK(indicesInRange(mesh));
    }

    TEST_CASE("torus clamps invalid stacks")
    {
        const MeshData mesh = Primitive::torus(0.6f, 0.2f, 0, 0);

        // clamps to majorStacks=3, minorStacks=3
        CHECK(mesh.vertexCount == 12);
        CHECK(mesh.indexCount == 54);
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
