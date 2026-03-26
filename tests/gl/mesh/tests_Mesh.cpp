#include <doctest/doctest.h>

#include <nfx/graphics/gl/mesh/Mesh.h>

using namespace nfx::graphics::gl;

TEST_SUITE("Mesh")
{
    TEST_CASE("setInstanceData on an invalid mesh is a no-op")
    {
        Mesh mesh;
        const float instanceData[4] = { 1.f, 2.f, 3.f, 4.f };
        const VertexLayout layout{ VertexLayout::Float4 };

        mesh.setInstanceData(instanceData, sizeof(instanceData), layout, 1);

        CHECK_FALSE(mesh.isValid());
        CHECK_FALSE(mesh.isIndexed());
        CHECK(mesh.vertexCount() == 0);
        CHECK(mesh.indexCount() == 0);
    }
}
