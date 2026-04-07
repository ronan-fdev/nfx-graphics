#include "nfx/graphics/gl/mesh/Primitive.h"
#include "detail/TangentUtils.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <numbers>
#include <unordered_map>
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

    MeshData Primitive::icosphere(int subdivisions)
    {
        if (subdivisions < 0)
        {
            subdivisions = 0;
        }
        if (subdivisions > 5)
        {
            subdivisions = 5;
        }

        const float t = (1.0f + std::sqrt(5.0f)) * 0.5f;

        std::vector<std::array<float, 3>> positions = {
            { -1.0f, t, 0.0f }, { 1.0f, t, 0.0f }, { -1.0f, -t, 0.0f }, { 1.0f, -t, 0.0f },
            { 0.0f, -1.0f, t }, { 0.0f, 1.0f, t }, { 0.0f, -1.0f, -t }, { 0.0f, 1.0f, -t },
            { t, 0.0f, -1.0f }, { t, 0.0f, 1.0f }, { -t, 0.0f, -1.0f }, { -t, 0.0f, 1.0f },
        };

        for (auto& p : positions)
        {
            const float invLen = 1.0f / std::sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
            p[0] *= invLen;
            p[1] *= invLen;
            p[2] *= invLen;
        }

        std::vector<std::array<unsigned int, 3>> faces = {
            { 0u, 11u, 5u }, { 0u, 5u, 1u },  { 0u, 1u, 7u },   { 0u, 7u, 10u }, { 0u, 10u, 11u },
            { 1u, 5u, 9u },  { 5u, 11u, 4u }, { 11u, 10u, 2u }, { 10u, 7u, 6u }, { 7u, 1u, 8u },
            { 3u, 9u, 4u },  { 3u, 4u, 2u },  { 3u, 2u, 6u },   { 3u, 6u, 8u },  { 3u, 8u, 9u },
            { 4u, 9u, 5u },  { 2u, 4u, 11u }, { 6u, 2u, 10u },  { 8u, 6u, 7u },  { 9u, 8u, 1u },
        };

        auto edgeKey = [](unsigned int a, unsigned int b) {
            const std::uint32_t lo = (a < b) ? a : b;
            const std::uint32_t hi = (a < b) ? b : a;
            return (static_cast<std::uint64_t>(lo) << 32u) | static_cast<std::uint64_t>(hi);
        };

        for (int step = 0; step < subdivisions; ++step)
        {
            std::unordered_map<std::uint64_t, unsigned int> midpointCache;
            midpointCache.reserve(faces.size() * 3u);

            auto midpointIndex = [&](unsigned int ia, unsigned int ib) {
                const std::uint64_t key = edgeKey(ia, ib);
                const auto it = midpointCache.find(key);
                if (it != midpointCache.end())
                {
                    return it->second;
                }

                const auto& a = positions[ia];
                const auto& b = positions[ib];
                std::array<float, 3> m = { 0.5f * (a[0] + b[0]), 0.5f * (a[1] + b[1]), 0.5f * (a[2] + b[2]) };
                const float invLen = 1.0f / std::sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
                m[0] *= invLen;
                m[1] *= invLen;
                m[2] *= invLen;

                const unsigned int idx = static_cast<unsigned int>(positions.size());
                positions.push_back(m);
                midpointCache.emplace(key, idx);
                return idx;
            };

            std::vector<std::array<unsigned int, 3>> newFaces;
            newFaces.reserve(faces.size() * 4u);
            for (const auto& f : faces)
            {
                const unsigned int a = f[0];
                const unsigned int b = f[1];
                const unsigned int c = f[2];
                const unsigned int ab = midpointIndex(a, b);
                const unsigned int bc = midpointIndex(b, c);
                const unsigned int ca = midpointIndex(c, a);

                newFaces.push_back({ a, ab, ca });
                newFaces.push_back({ b, bc, ab });
                newFaces.push_back({ c, ca, bc });
                newFaces.push_back({ ab, bc, ca });
            }
            faces = std::move(newFaces);
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(positions.size() * 8u);
        indices.reserve(faces.size() * 3u);

        for (const auto& p : positions)
        {
            const float x = p[0];
            const float y = p[1];
            const float z = p[2];
            const float u = 0.5f + std::atan2(z, x) / (2.0f * k_pi);
            const float v = 0.5f - std::asin(y) / k_pi;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(u);
            vertices.push_back(v);
        }

        for (const auto& f : faces)
        {
            indices.push_back(f[0]);
            indices.push_back(f[1]);
            indices.push_back(f[2]);
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

    MeshData Primitive::cylinder(float radius, float height, int slices, int stacks)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }
        if (slices < 3)
        {
            slices = 3;
        }
        if (stacks < 1)
        {
            stacks = 1;
        }

        const float halfH = 0.5f * height;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const std::size_t sideVertexCount = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t capVertexCount = 2u * (static_cast<std::size_t>(slices) + 2u);
        vertices.reserve((sideVertexCount + capVertexCount) * 8u);

        const std::size_t sideIndexCount = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;
        const std::size_t capIndexCount = static_cast<std::size_t>(slices) * 6u;
        indices.reserve(sideIndexCount + capIndexCount);

        // Side vertices
        for (int yStep = 0; yStep <= stacks; ++yStep)
        {
            const float v = static_cast<float>(yStep) / static_cast<float>(stacks);
            const float y = -halfH + v * height;

            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta);
                const float s = std::sin(theta);

                const float x = radius * c;
                const float z = radius * s;

                // position
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                // normal
                vertices.push_back(c);
                vertices.push_back(0.0f);
                vertices.push_back(s);
                // uv
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        // Side indices
        for (int yStep = 0; yStep < stacks; ++yStep)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = static_cast<unsigned int>(yStep * (slices + 1) + slice);
                const unsigned int b = a + static_cast<unsigned int>(slices + 1);

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a + 1u);

                indices.push_back(b);
                indices.push_back(b + 1u);
                indices.push_back(a + 1u);
            }
        }

        // Top cap center
        const unsigned int topCenter = static_cast<unsigned int>(vertices.size() / 8u);
        vertices.push_back(0.0f);
        vertices.push_back(halfH);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);

        // Top cap ring
        const unsigned int topRingStart = static_cast<unsigned int>(vertices.size() / 8u);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta);
            const float s = std::sin(theta);

            vertices.push_back(radius * c);
            vertices.push_back(halfH);
            vertices.push_back(radius * s);
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.5f + 0.5f * c);
            vertices.push_back(0.5f + 0.5f * s);
        }

        // Top cap indices
        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int i0 = topRingStart + static_cast<unsigned int>(slice);
            const unsigned int i1 = i0 + 1u;
            indices.push_back(topCenter);
            indices.push_back(i1);
            indices.push_back(i0);
        }

        // Bottom cap center
        const unsigned int bottomCenter = static_cast<unsigned int>(vertices.size() / 8u);
        vertices.push_back(0.0f);
        vertices.push_back(-halfH);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);

        // Bottom cap ring
        const unsigned int bottomRingStart = static_cast<unsigned int>(vertices.size() / 8u);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta);
            const float s = std::sin(theta);

            vertices.push_back(radius * c);
            vertices.push_back(-halfH);
            vertices.push_back(radius * s);
            vertices.push_back(0.0f);
            vertices.push_back(-1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.5f + 0.5f * c);
            vertices.push_back(0.5f - 0.5f * s);
        }

        // Bottom cap indices
        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int i0 = bottomRingStart + static_cast<unsigned int>(slice);
            const unsigned int i1 = i0 + 1u;
            indices.push_back(bottomCenter);
            indices.push_back(i0);
            indices.push_back(i1);
        }

        MeshData data;
        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfH, -radius }, { radius, halfH, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(radius * radius + halfH * halfH) };

        return data;
    }

    MeshData Primitive::torus(float majorRadius, float minorRadius, int majorStacks, int minorStacks)
    {
        if (majorStacks < 3)
        {
            majorStacks = 3;
        }
        if (minorStacks < 3)
        {
            minorStacks = 3;
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(static_cast<std::size_t>(majorStacks) * static_cast<std::size_t>(minorStacks + 1) * 8);
        indices.reserve(static_cast<std::size_t>(majorStacks) * static_cast<std::size_t>(minorStacks) * 6);

        for (int major = 0; major < majorStacks; ++major)
        {
            const float majorAngle = 2.0f * k_pi * static_cast<float>(major) / static_cast<float>(majorStacks);
            const float cosMajor = std::cos(majorAngle);
            const float sinMajor = std::sin(majorAngle);

            for (int minor = 0; minor <= minorStacks; ++minor)
            {
                const float minorAngle = 2.0f * k_pi * static_cast<float>(minor) / static_cast<float>(minorStacks);
                const float cosMinor = std::cos(minorAngle);
                const float sinMinor = std::sin(minorAngle);
                const float u = static_cast<float>(major) / static_cast<float>(majorStacks);
                const float v = static_cast<float>(minor) / static_cast<float>(minorStacks);

                // Vertex position on the torus
                const float tubeX = minorRadius * cosMinor;
                const float tubeY = minorRadius * sinMinor;
                const float x = (majorRadius + tubeX) * cosMajor;
                const float y = tubeY;
                const float z = (majorRadius + tubeX) * sinMajor;

                // Normal (points from major circle toward the tube surface)
                const float nx = cosMinor * cosMajor;
                const float ny = sinMinor;
                const float nz = cosMinor * sinMajor;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        // Generate indices
        for (int major = 0; major < majorStacks; ++major)
        {
            const int majorNext = (major + 1) % majorStacks;
            for (int minor = 0; minor < minorStacks; ++minor)
            {
                const int minorNext = minor + 1;
                const unsigned int v0 = static_cast<unsigned int>(major * (minorStacks + 1) + minor);
                const unsigned int v1 = static_cast<unsigned int>(major * (minorStacks + 1) + minorNext);
                const unsigned int v2 = static_cast<unsigned int>(majorNext * (minorStacks + 1) + minorNext);
                const unsigned int v3 = static_cast<unsigned int>(majorNext * (minorStacks + 1) + minor);

                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v2);
                indices.push_back(v2);
                indices.push_back(v3);
                indices.push_back(v0);
            }
        }

        MeshData data;
        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);

        float boundRad = majorRadius + minorRadius;
        data.boundsAABB =
            math::Bounds::AABB{ { -boundRad, -minorRadius, -boundRad }, { boundRad, minorRadius, boundRad } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, boundRad };

        return data;
    }

    MeshData Primitive::cone(float radius, float height, int slices, int stacks)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }
        if (slices < 3)
        {
            slices = 3;
        }
        if (stacks < 1)
        {
            stacks = 1;
        }

        const float halfH = 0.5f * height;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const std::size_t sideVertexCount = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(slices + 1);
        const std::size_t capVertexCount = static_cast<std::size_t>(slices) + 2u;
        vertices.reserve((sideVertexCount + capVertexCount) * 8u);

        const std::size_t sideIndexCount = static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u;
        const std::size_t capIndexCount = static_cast<std::size_t>(slices) * 3u;
        indices.reserve(sideIndexCount + capIndexCount);

        // Side vertices
        // Cone apex at y=+halfH, base at y=-halfH
        const float slope = radius / height;
        for (int yStep = 0; yStep <= stacks; ++yStep)
        {
            const float v = static_cast<float>(yStep) / static_cast<float>(stacks);
            const float y = halfH - v * height;
            const float ringR = radius * v;

            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta);
                const float s = std::sin(theta);

                const float x = ringR * c;
                const float z = ringR * s;

                // position
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // side normal
                float nx = c;
                float ny = slope;
                float nz = s;
                const float invLen = 1.0f / std::sqrt(nx * nx + ny * ny + nz * nz);
                vertices.push_back(nx * invLen);
                vertices.push_back(ny * invLen);
                vertices.push_back(nz * invLen);

                // uv
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        // Side indices
        for (int yStep = 0; yStep < stacks; ++yStep)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = static_cast<unsigned int>(yStep * (slices + 1) + slice);
                const unsigned int b = a + static_cast<unsigned int>(slices + 1);

                indices.push_back(a + 1u);
                indices.push_back(b);
                indices.push_back(a);

                indices.push_back(a + 1u);
                indices.push_back(b + 1u);
                indices.push_back(b);
            }
        }

        // Bottom cap center
        const unsigned int capCenter = static_cast<unsigned int>(vertices.size() / 8u);
        vertices.push_back(0.0f);
        vertices.push_back(-halfH);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);

        // Bottom cap ring
        const unsigned int capRingStart = static_cast<unsigned int>(vertices.size() / 8u);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta);
            const float s = std::sin(theta);

            vertices.push_back(radius * c);
            vertices.push_back(-halfH);
            vertices.push_back(radius * s);
            vertices.push_back(0.0f);
            vertices.push_back(-1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.5f + 0.5f * c);
            vertices.push_back(0.5f - 0.5f * s);
        }

        // Bottom cap indices
        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int i0 = capRingStart + static_cast<unsigned int>(slice);
            const unsigned int i1 = i0 + 1u;
            indices.push_back(capCenter);
            indices.push_back(i0);
            indices.push_back(i1);
        }

        MeshData data;
        detail::computeTangents(vertices, indices);

        data.layout = {
            VertexLayout::Float3, // position
            VertexLayout::Float3, // normal
            VertexLayout::Float2, // uv
            VertexLayout::Float4  // tangent
        };
        data.setVertexData(vertices.data(), vertices.size() * sizeof(float), data.layout);
        data.setIndexData(indices.data(), indices.size(), MeshData::IndexType::UInt32);
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfH, -radius }, { radius, halfH, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(radius * radius + halfH * halfH) };

        return data;
    }

    MeshData Primitive::capsule(float radius, float height, int slices, int hemisphereStacks)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }
        if (slices < 3)
        {
            slices = 3;
        }
        if (hemisphereStacks < 1)
        {
            hemisphereStacks = 1;
        }

        const float halfH = 0.5f * height;
        const int ringCount = 2 * hemisphereStacks + 1;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(static_cast<std::size_t>(ringCount + 1) * static_cast<std::size_t>(slices + 1) * 8u);
        indices.reserve(static_cast<std::size_t>(ringCount) * static_cast<std::size_t>(slices) * 6u);

        auto pushRing = [&](float ringR, float y, float centerY, float v) {
            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta);
                const float s = std::sin(theta);

                const float x = ringR * c;
                const float z = ringR * s;

                // position
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // normal
                float nx = x;
                float ny = y - centerY;
                float nz = z;
                float invLen = 1.0f / std::sqrt(nx * nx + ny * ny + nz * nz);
                vertices.push_back(nx * invLen);
                vertices.push_back(ny * invLen);
                vertices.push_back(nz * invLen);

                // uv
                vertices.push_back(u);
                vertices.push_back(v);
            }
        };

        int ringIdx = 0;

        // Top hemisphere: from top pole to top cylinder seam
        for (int i = 0; i <= hemisphereStacks; ++i)
        {
            const float t = static_cast<float>(i) / static_cast<float>(hemisphereStacks);
            const float phi = (k_pi * 0.5f) * t;
            const float ringR = radius * std::sin(phi);
            const float y = halfH + radius * std::cos(phi);
            const float v = static_cast<float>(ringIdx) / static_cast<float>(ringCount);
            pushRing(ringR, y, halfH, v);
            ++ringIdx;
        }

        // Bottom hemisphere: skip duplicate seam, then to bottom pole
        for (int i = 1; i <= hemisphereStacks; ++i)
        {
            const float t = static_cast<float>(i) / static_cast<float>(hemisphereStacks);
            const float phi = (k_pi * 0.5f) * t;
            const float ringR = radius * std::cos(phi);
            const float y = -halfH - radius * std::sin(phi);
            const float v = static_cast<float>(ringIdx) / static_cast<float>(ringCount);
            pushRing(ringR, y, -halfH, v);
            ++ringIdx;
        }

        const int generatedRings = ringIdx;

        // Indices between rings
        for (int ring = 0; ring < generatedRings - 1; ++ring)
        {
            const unsigned int row0 = static_cast<unsigned int>(ring * (slices + 1));
            const unsigned int row1 = static_cast<unsigned int>((ring + 1) * (slices + 1));

            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = row0 + static_cast<unsigned int>(slice);
                const unsigned int b = row1 + static_cast<unsigned int>(slice);

                indices.push_back(a + 1u);
                indices.push_back(b);
                indices.push_back(a);

                indices.push_back(a + 1u);
                indices.push_back(b + 1u);
                indices.push_back(b);
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

        const float halfTotal = halfH + radius;
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfTotal, -radius }, { radius, halfTotal, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, halfTotal };

        return data;
    }

    MeshData Primitive::disk(float radius, int slices)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (slices < 3)
        {
            slices = 3;
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const std::size_t vertexCount = static_cast<std::size_t>(slices) + 2u;
        vertices.reserve(vertexCount * 8u);
        indices.reserve(static_cast<std::size_t>(slices) * 3u);

        // Center vertex
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);

        // Rim vertices (duplicate first vertex at the end for UV seam)
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta);
            const float s = std::sin(theta);

            const float x = radius * c;
            const float z = radius * s;

            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(z);
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.5f + 0.5f * c);
            vertices.push_back(0.5f + 0.5f * s);
        }

        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int i0 = 1u + static_cast<unsigned int>(slice);
            const unsigned int i1 = i0 + 1u;

            indices.push_back(0u);
            indices.push_back(i1);
            indices.push_back(i0);
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
        data.boundsAABB = math::Bounds::AABB{ { -radius, 0.0f, -radius }, { radius, 0.0f, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, radius };

        return data;
    }

    MeshData Primitive::pyramid(float radius, float height)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }

        const float halfH = 0.5f * height;

        const float p0[3] = { -radius, -halfH, -radius };
        const float p1[3] = { radius, -halfH, -radius };
        const float p2[3] = { radius, -halfH, radius };
        const float p3[3] = { -radius, -halfH, radius };
        const float apex[3] = { 0.0f, halfH, 0.0f };

        auto computeFaceNormal = [](const float a[3], const float b[3], const float c[3]) {
            const float ux = b[0] - a[0];
            const float uy = b[1] - a[1];
            const float uz = b[2] - a[2];
            const float vx = c[0] - a[0];
            const float vy = c[1] - a[1];
            const float vz = c[2] - a[2];

            const float nx = uy * vz - uz * vy;
            const float ny = uz * vx - ux * vz;
            const float nz = ux * vy - uy * vx;

            const float invLen = 1.0f / std::sqrt(nx * nx + ny * ny + nz * nz);
            return std::array<float, 3>{ nx * invLen, ny * invLen, nz * invLen };
        };

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(16u * 8u);
        indices.reserve(18u);

        auto pushVertex = [&](const float p[3], const float n[3], float u, float v) {
            vertices.push_back(p[0]);
            vertices.push_back(p[1]);
            vertices.push_back(p[2]);
            vertices.push_back(n[0]);
            vertices.push_back(n[1]);
            vertices.push_back(n[2]);
            vertices.push_back(u);
            vertices.push_back(v);
        };

        // Base (two triangles, Y- normal)
        const float baseN[3] = { 0.0f, -1.0f, 0.0f };
        pushVertex(p0, baseN, 0.0f, 0.0f); // 0
        pushVertex(p1, baseN, 1.0f, 0.0f); // 1
        pushVertex(p2, baseN, 1.0f, 1.0f); // 2
        pushVertex(p3, baseN, 0.0f, 1.0f); // 3

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);

        // Side +X/-Z
        {
            const auto n = computeFaceNormal(p1, p0, apex);
            const float nn[3] = { n[0], n[1], n[2] };
            const unsigned int base = static_cast<unsigned int>(vertices.size() / 8u);
            pushVertex(p1, nn, 0.0f, 0.0f);
            pushVertex(p0, nn, 1.0f, 0.0f);
            pushVertex(apex, nn, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
        }

        // Side +X/+Z
        {
            const auto n = computeFaceNormal(p2, p1, apex);
            const float nn[3] = { n[0], n[1], n[2] };
            const unsigned int base = static_cast<unsigned int>(vertices.size() / 8u);
            pushVertex(p2, nn, 0.0f, 0.0f);
            pushVertex(p1, nn, 1.0f, 0.0f);
            pushVertex(apex, nn, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
        }

        // Side -X/+Z
        {
            const auto n = computeFaceNormal(p3, p2, apex);
            const float nn[3] = { n[0], n[1], n[2] };
            const unsigned int base = static_cast<unsigned int>(vertices.size() / 8u);
            pushVertex(p3, nn, 0.0f, 0.0f);
            pushVertex(p2, nn, 1.0f, 0.0f);
            pushVertex(apex, nn, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
        }

        // Side -X/-Z
        {
            const auto n = computeFaceNormal(p0, p3, apex);
            const float nn[3] = { n[0], n[1], n[2] };
            const unsigned int base = static_cast<unsigned int>(vertices.size() / 8u);
            pushVertex(p0, nn, 0.0f, 0.0f);
            pushVertex(p3, nn, 1.0f, 0.0f);
            pushVertex(apex, nn, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
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
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfH, -radius }, { radius, halfH, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(radius * radius + halfH * halfH) };

        return data;
    }

    MeshData Primitive::tetrahedron(float radius, float height)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }

        const float halfH = 0.5f * height;
        const float k = 0.8660254f; // sin(60deg)

        const float p0[3] = { radius, -halfH, 0.0f };
        const float p1[3] = { -0.5f * radius, -halfH, k * radius };
        const float p2[3] = { -0.5f * radius, -halfH, -k * radius };
        const float apex[3] = { 0.0f, halfH, 0.0f };

        auto computeFaceNormal = [](const float a[3], const float b[3], const float c[3]) {
            const float ux = b[0] - a[0];
            const float uy = b[1] - a[1];
            const float uz = b[2] - a[2];
            const float vx = c[0] - a[0];
            const float vy = c[1] - a[1];
            const float vz = c[2] - a[2];

            const float nx = uy * vz - uz * vy;
            const float ny = uz * vx - ux * vz;
            const float nz = ux * vy - uy * vx;

            const float invLen = 1.0f / std::sqrt(nx * nx + ny * ny + nz * nz);
            return std::array<float, 3>{ nx * invLen, ny * invLen, nz * invLen };
        };

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(12u * 8u);
        indices.reserve(12u);

        auto pushVertex = [&](const float p[3], const float n[3], float u, float v) {
            vertices.push_back(p[0]);
            vertices.push_back(p[1]);
            vertices.push_back(p[2]);
            vertices.push_back(n[0]);
            vertices.push_back(n[1]);
            vertices.push_back(n[2]);
            vertices.push_back(u);
            vertices.push_back(v);
        };

        // Base face (Y-)
        {
            const float n[3] = { 0.0f, -1.0f, 0.0f };
            const unsigned int base = 0u;
            pushVertex(p0, n, 0.0f, 0.0f);
            pushVertex(p1, n, 1.0f, 0.0f);
            pushVertex(p2, n, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
        }

        auto pushOrientedFace = [&](const float a[3], const float b[3], const float c[3]) {
            const auto n = computeFaceNormal(a, b, c);
            const float cx = (a[0] + b[0] + c[0]) / 3.0f;
            const float cy = (a[1] + b[1] + c[1]) / 3.0f;
            const float cz = (a[2] + b[2] + c[2]) / 3.0f;
            const float dot = n[0] * cx + n[1] * cy + n[2] * cz;

            const float* pA = a;
            const float* pB = b;
            const float* pC = c;
            float nn[3] = { n[0], n[1], n[2] };
            if (dot < 0.0f)
            {
                pB = c;
                pC = b;
                nn[0] = -nn[0];
                nn[1] = -nn[1];
                nn[2] = -nn[2];
            }

            const unsigned int base = static_cast<unsigned int>(vertices.size() / 8u);
            pushVertex(pA, nn, 0.0f, 0.0f);
            pushVertex(pB, nn, 1.0f, 0.0f);
            pushVertex(pC, nn, 0.5f, 1.0f);
            indices.push_back(base + 0u);
            indices.push_back(base + 1u);
            indices.push_back(base + 2u);
        };

        // Side faces
        pushOrientedFace(p0, p1, apex);
        pushOrientedFace(p1, p2, apex);
        pushOrientedFace(p2, p0, apex);

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
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfH, -radius }, { radius, halfH, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(radius * radius + halfH * halfH) };

        return data;
    }

    MeshData Primitive::tube(float radius, float height, int slices, int stacks)
    {
        if (radius <= 0.0f)
        {
            radius = 0.5f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }
        if (slices < 3)
        {
            slices = 3;
        }
        if (stacks < 1)
        {
            stacks = 1;
        }

        const float halfH = 0.5f * height;
        const unsigned int ringStride = static_cast<unsigned int>(slices + 1);
        const unsigned int ringCount = static_cast<unsigned int>(stacks + 1);

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.reserve(static_cast<std::size_t>(ringCount) * static_cast<std::size_t>(ringStride) * 8u);
        indices.reserve(static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 6u);

        for (int yStep = 0; yStep <= stacks; ++yStep)
        {
            const float v = static_cast<float>(yStep) / static_cast<float>(stacks);
            const float y = -halfH + v * height;

            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta);
                const float s = std::sin(theta);

                vertices.push_back(radius * c);
                vertices.push_back(y);
                vertices.push_back(radius * s);
                vertices.push_back(c);
                vertices.push_back(0.0f);
                vertices.push_back(s);
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        for (int yStep = 0; yStep < stacks; ++yStep)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = static_cast<unsigned int>(yStep * (slices + 1) + slice);
                const unsigned int b = a + static_cast<unsigned int>(slices + 1);

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a + 1u);

                indices.push_back(b);
                indices.push_back(b + 1u);
                indices.push_back(a + 1u);
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
        data.boundsAABB = math::Bounds::AABB{ { -radius, -halfH, -radius }, { radius, halfH, radius } };
        data.boundsSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(radius * radius + halfH * halfH) };

        return data;
    }

    MeshData Primitive::pipe(float outerRadius, float innerRadius, float height, int slices, int stacks)
    {
        if (outerRadius <= 0.0f)
        {
            outerRadius = 0.5f;
        }
        if (innerRadius <= 0.0f || innerRadius >= outerRadius)
        {
            innerRadius = outerRadius * 0.7f;
        }
        if (height <= 0.0f)
        {
            height = 1.0f;
        }
        if (slices < 3)
        {
            slices = 3;
        }
        if (stacks < 1)
        {
            stacks = 1;
        }

        const float halfH = 0.5f * height;
        const int ringVerts = slices + 1;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        const auto shellRings = static_cast<std::size_t>(stacks + 1) * static_cast<std::size_t>(ringVerts);
        const auto capVerts = static_cast<std::size_t>(ringVerts) * 2u;
        vertices.reserve((shellRings * 2u + capVerts * 2u) * 8u);
        indices.reserve(
            static_cast<std::size_t>(stacks) * static_cast<std::size_t>(slices) * 12u +
            static_cast<std::size_t>(slices) * 12u);

        auto pushVert = [&](float px, float py, float pz, float nx, float ny, float nz, float u, float v) {
            vertices.push_back(px);
            vertices.push_back(py);
            vertices.push_back(pz);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            vertices.push_back(u);
            vertices.push_back(v);
        };

        // Outer shell (normals outward)
        const unsigned int outerBase = 0u;
        for (int yStep = 0; yStep <= stacks; ++yStep)
        {
            const float v = static_cast<float>(yStep) / static_cast<float>(stacks);
            const float y = -halfH + v * height;
            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta), s = std::sin(theta);
                pushVert(outerRadius * c, y, outerRadius * s, c, 0.0f, s, u, v);
            }
        }
        for (int yStep = 0; yStep < stacks; ++yStep)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = outerBase + static_cast<unsigned int>(yStep * ringVerts + slice);
                const unsigned int b = a + static_cast<unsigned int>(ringVerts);
                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a + 1u);
                indices.push_back(b);
                indices.push_back(b + 1u);
                indices.push_back(a + 1u);
            }
        }

        // Inner shell (normals inward, reversed winding)
        const unsigned int innerBase = static_cast<unsigned int>((stacks + 1) * ringVerts);
        for (int yStep = 0; yStep <= stacks; ++yStep)
        {
            const float v = static_cast<float>(yStep) / static_cast<float>(stacks);
            const float y = -halfH + v * height;
            for (int slice = 0; slice <= slices; ++slice)
            {
                const float u = static_cast<float>(slice) / static_cast<float>(slices);
                const float theta = 2.0f * k_pi * u;
                const float c = std::cos(theta), s = std::sin(theta);
                pushVert(innerRadius * c, y, innerRadius * s, -c, 0.0f, -s, u, v);
            }
        }
        for (int yStep = 0; yStep < stacks; ++yStep)
        {
            for (int slice = 0; slice < slices; ++slice)
            {
                const unsigned int a = innerBase + static_cast<unsigned int>(yStep * ringVerts + slice);
                const unsigned int b = a + static_cast<unsigned int>(ringVerts);
                indices.push_back(a);
                indices.push_back(a + 1u);
                indices.push_back(b);
                indices.push_back(b);
                indices.push_back(a + 1u);
                indices.push_back(b + 1u);
            }
        }

        // Top cap (y = +halfH, normal = (0,+1,0))
        // Vertex layout: (outer_i, inner_i) pairs
        // Winding verified CCW from +Y: ao, bi, bo and ao, ai, bi
        const unsigned int topBase = innerBase + static_cast<unsigned int>((stacks + 1) * ringVerts);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta), s = std::sin(theta);
            pushVert(outerRadius * c, halfH, outerRadius * s, 0.0f, 1.0f, 0.0f, u, 0.0f);
            pushVert(innerRadius * c, halfH, innerRadius * s, 0.0f, 1.0f, 0.0f, u, 1.0f);
        }
        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int ao = topBase + static_cast<unsigned int>(slice * 2);
            const unsigned int ai = ao + 1u;
            const unsigned int bo = ao + 2u;
            const unsigned int bi = ao + 3u;
            indices.push_back(ao);
            indices.push_back(bi);
            indices.push_back(bo);
            indices.push_back(ao);
            indices.push_back(ai);
            indices.push_back(bi);
        }

        // Bottom cap (y = -halfH, normal = (0,-1,0))
        // Reversed winding relative to top: ao, bo, bi and ao, bi, ai
        const unsigned int botBase = topBase + static_cast<unsigned int>((slices + 1) * 2);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float u = static_cast<float>(slice) / static_cast<float>(slices);
            const float theta = 2.0f * k_pi * u;
            const float c = std::cos(theta), s = std::sin(theta);
            pushVert(outerRadius * c, -halfH, outerRadius * s, 0.0f, -1.0f, 0.0f, u, 0.0f);
            pushVert(innerRadius * c, -halfH, innerRadius * s, 0.0f, -1.0f, 0.0f, u, 1.0f);
        }
        for (int slice = 0; slice < slices; ++slice)
        {
            const unsigned int ao = botBase + static_cast<unsigned int>(slice * 2);
            const unsigned int ai = ao + 1u;
            const unsigned int bo = ao + 2u;
            const unsigned int bi = ao + 3u;
            indices.push_back(ao);
            indices.push_back(bo);
            indices.push_back(bi);
            indices.push_back(ao);
            indices.push_back(bi);
            indices.push_back(ai);
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
        data.boundsAABB =
            math::Bounds::AABB{ { -outerRadius, -halfH, -outerRadius }, { outerRadius, halfH, outerRadius } };
        data.boundsSphere =
            math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, std::sqrt(outerRadius * outerRadius + halfH * halfH) };

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
