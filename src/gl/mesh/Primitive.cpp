#include "nfx/graphics/gl/mesh/Primitive.h"
#include "detail/TangentUtils.h"

#include <cmath>
#include <numbers>
#include <vector>

namespace nfx::graphics::gl
{
    static constexpr float k_pi = std::numbers::pi_v<float>;

    // Unit cube: half-diagonal = sqrt(3) / 2
    static constexpr float k_cubeSphereRadius = 0.8660254f;
    // Unit sphere: circumscribed
    static constexpr float k_unitSphereRadius = 1.0f;
    // Unit XZ plane (1x1): half-diagonal in XZ = sqrt(2) / 2
    static constexpr float k_planeSphereRadius = 0.7071068f;
    // NDC quad (-1..1 in XY): half-diagonal = sqrt(2)
    static constexpr float k_quadSphereRadius = 1.4142136f;

    MeshData Primitive::cube()
    {
        // clang-format off
        static const float k_vertices[] = {
            // pos(3) + normal(3) + uv(2) per vertex, 4 vertices per face
            // +X                  normal                uv
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            // -X
            -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
            // +Y
            -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
            // -Y
            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
            // +Z
            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
            // -Z
             0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f
        };

        static const unsigned int k_indices[] = {
             0,  1,  2,   2,  3,  0,  // +X
             4,  5,  6,   6,  7,  4,  // -X
             8, 11, 10,  10,  9,  8,  // +Y
            12, 15, 14,  14, 13, 12,  // -Y
            16, 17, 18,  18, 19, 16,  // +Z
            20, 21, 22,  22, 23, 20   // -Z
        };
        // clang-format on

        MeshData data;
        std::vector<float> vertices(k_vertices, k_vertices + sizeof(k_vertices) / sizeof(float));
        std::vector<unsigned int> indices(k_indices, k_indices + sizeof(k_indices) / sizeof(unsigned int));

        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent (xyz + handedness w)
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, k_cubeSphereRadius };

        return data;
    }

    MeshData Primitive::uvSphere(int stacks, int slices)
    {
        if (stacks < 1)
        {
            stacks = 1;
        }
        if (slices < 3)
        {
            slices = 3;
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1) * 8);
        indices.reserve(static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6);

        for (int stack = 0; stack <= stacks; ++stack)
        {
            const float phi = k_pi * static_cast<float>(stack) / static_cast<float>(stacks);
            const float cosPhi = std::cos(phi);
            const float sinPhi = std::sin(phi);
            const float v = static_cast<float>(stack) / static_cast<float>(stacks);

            for (int slice = 0; slice <= slices; ++slice)
            {
                const float theta = 2.0f * k_pi * static_cast<float>(slice) / static_cast<float>(slices);
                const float cosTheta = std::cos(theta);
                const float sinTheta = std::sin(theta);
                const float u = static_cast<float>(slice) / static_cast<float>(slices);

                // Position and normal are identical for a unit sphere
                const float x = sinPhi * cosTheta;
                const float y = sinPhi * sinTheta;
                const float z = cosPhi;

                // pos
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                // normal = pos for unit sphere
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                // uv
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        for (int stack = 0; stack < stacks; ++stack)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const auto a = static_cast<unsigned int>(stack * (slices + 1) + slice);
                const auto b = a + static_cast<unsigned int>(slices + 1);

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a + 1);

                indices.push_back(b);
                indices.push_back(b + 1);
                indices.push_back(a + 1);
            }
        }

        MeshData data;
        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent (xyz + handedness w)
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, k_unitSphereRadius };

        return data;
    }

    MeshData Primitive::plane(int subdivisionsX, int subdivisionsZ)
    {
        if (subdivisionsX < 1)
        {
            subdivisionsX = 1;
        }
        if (subdivisionsZ < 1)
        {
            subdivisionsZ = 1;
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const int nx = subdivisionsX + 1;
        const int nz = subdivisionsZ + 1;
        vertices.reserve(static_cast<std::size_t>(nx) * static_cast<std::size_t>(nz) * 8);
        indices.reserve(static_cast<std::size_t>(subdivisionsX) * static_cast<std::size_t>(subdivisionsZ) * 6);

        for (int z = 0; z < nz; ++z)
        {
            for (int x = 0; x < nx; ++x)
            {
                const float px = (static_cast<float>(x) / static_cast<float>(subdivisionsX)) - 0.5f;
                const float pz = (static_cast<float>(z) / static_cast<float>(subdivisionsZ)) - 0.5f;
                const float u = static_cast<float>(x) / static_cast<float>(subdivisionsX);
                const float v = static_cast<float>(z) / static_cast<float>(subdivisionsZ);

                // pos
                vertices.push_back(px);
                vertices.push_back(0.0f);
                vertices.push_back(pz);
                // normal
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                // uv
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        for (int z = 0; z < subdivisionsZ; ++z)
        {
            for (int x = 0; x < subdivisionsX; ++x)
            {
                const auto a = static_cast<unsigned int>(z * nx + x);
                const auto b = a + static_cast<unsigned int>(nx);

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a + 1);

                indices.push_back(b);
                indices.push_back(b + 1);
                indices.push_back(a + 1);
            }
        }

        MeshData data;
        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent (xyz + handedness w)
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -0.5f, 0.0f, -0.5f }, { 0.5f, 0.0f, 0.5f } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, k_planeSphereRadius };

        return data;
    }

    MeshData Primitive::quad()
    {
        // Fullscreen NDC quad, layout: pos(Float3) + uv(Float2)
        // clang-format off
        static const float k_vertices[] = {
        //   pos                  uv
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f
        };
        // clang-format on

        static const unsigned int k_indices[] = { 0, 1, 2, 2, 3, 0 };

        MeshData data;
        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float2  // uv
        };
        data.setVertexData(k_vertices, sizeof(k_vertices), data.layout);
        data.setIndexData(k_indices, sizeof(k_indices) / sizeof(unsigned int), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, k_quadSphereRadius };

        return data;
    }
} // namespace nfx::graphics::gl
