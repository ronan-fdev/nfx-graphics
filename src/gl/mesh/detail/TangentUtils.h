#pragma once

// Internal utility: compute per-vertex tangents (Float4, w = handedness) from a
// stride-8 interleaved buffer (pos3+normal3+uv2) and extend it to stride-12
// (pos3+normal3+uv2+tangent4).  Uses Gram-Schmidt orthogonalization and
// accumulates tangent/bitangent contributions per triangle

#include <cmath>
#include <limits>
#include <vector>

namespace nfx::graphics::gl::detail
{
    inline void computeTangents(std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    {
        constexpr int kStride = 8; // pos(3) + normal(3) + uv(2)
        if (vertices.empty() || indices.empty())
        {
            return;
        }

        if ((vertices.size() % kStride) != 0)
        {
            // Invalid input layout: keep source buffer unchanged
            return;
        }

        const int numVerts = static_cast<int>(vertices.size() / kStride);
        const int numTris = static_cast<int>(indices.size() / 3);

        std::vector<float> tanAccum(numVerts * 3, 0.0f);
        std::vector<float> bitanAccum(numVerts * 3, 0.0f);

        for (int t = 0; t < numTris; ++t)
        {
            const unsigned int i0 = indices[t * 3 + 0];
            const unsigned int i1 = indices[t * 3 + 1];
            const unsigned int i2 = indices[t * 3 + 2];

            if (i0 >= static_cast<unsigned int>(numVerts) || i1 >= static_cast<unsigned int>(numVerts) ||
                i2 >= static_cast<unsigned int>(numVerts))
            {
                continue;
            }

            const float* v0 = &vertices[i0 * kStride];
            const float* v1 = &vertices[i1 * kStride];
            const float* v2 = &vertices[i2 * kStride];

            const float dp1x = v1[0] - v0[0], dp1y = v1[1] - v0[1], dp1z = v1[2] - v0[2];
            const float dp2x = v2[0] - v0[0], dp2y = v2[1] - v0[1], dp2z = v2[2] - v0[2];

            const float duv1x = v1[6] - v0[6], duv1y = v1[7] - v0[7];
            const float duv2x = v2[6] - v0[6], duv2y = v2[7] - v0[7];

            const float denom = duv1x * duv2y - duv2x * duv1y;
            if (std::abs(denom) < std::numeric_limits<float>::epsilon())
            {
                continue;
            }
            const float r = 1.0f / denom;

            const float tx = r * (duv2y * dp1x - duv1y * dp2x);
            const float ty = r * (duv2y * dp1y - duv1y * dp2y);
            const float tz = r * (duv2y * dp1z - duv1y * dp2z);

            const float bx = r * (-duv2x * dp1x + duv1x * dp2x);
            const float by = r * (-duv2x * dp1y + duv1x * dp2y);
            const float bz = r * (-duv2x * dp1z + duv1x * dp2z);

            for (unsigned int vi : { i0, i1, i2 })
            {
                tanAccum[vi * 3 + 0] += tx;
                tanAccum[vi * 3 + 1] += ty;
                tanAccum[vi * 3 + 2] += tz;
                bitanAccum[vi * 3 + 0] += bx;
                bitanAccum[vi * 3 + 1] += by;
                bitanAccum[vi * 3 + 2] += bz;
            }
        }

        // Rebuild as stride-12: pos(3) + normal(3) + uv(2) + tangent(4)
        std::vector<float> result;
        result.reserve(static_cast<std::size_t>(numVerts) * 12);

        for (int vi = 0; vi < numVerts; ++vi)
        {
            const float* v = &vertices[vi * kStride];

            // pos
            result.push_back(v[0]);
            result.push_back(v[1]);
            result.push_back(v[2]);
            // normal
            result.push_back(v[3]);
            result.push_back(v[4]);
            result.push_back(v[5]);
            // uv
            result.push_back(v[6]);
            result.push_back(v[7]);

            const float nx = v[3], ny = v[4], nz = v[5];
            float tx = tanAccum[vi * 3 + 0];
            float ty = tanAccum[vi * 3 + 1];
            float tz = tanAccum[vi * 3 + 2];

            // Gram-Schmidt orthogonalization
            const float d = tx * nx + ty * ny + tz * nz;
            tx -= d * nx;
            ty -= d * ny;
            tz -= d * nz;
            const float len = std::sqrt(tx * tx + ty * ty + tz * tz);
            if (len > std::numeric_limits<float>::epsilon())
            {
                tx /= len;
                ty /= len;
                tz /= len;
            }

            // Handedness: sign of dot(cross(N, T), B)
            const float bx = bitanAccum[vi * 3 + 0];
            const float by = bitanAccum[vi * 3 + 1];
            const float bz = bitanAccum[vi * 3 + 2];
            const float cx = ny * tz - nz * ty;
            const float cy = nz * tx - nx * tz;
            const float cz = nx * ty - ny * tx;
            const float w = (cx * bx + cy * by + cz * bz) < 0.0f ? -1.0f : 1.0f;

            result.push_back(tx);
            result.push_back(ty);
            result.push_back(tz);
            result.push_back(w);
        }

        vertices = std::move(result);
    }
} // namespace nfx::graphics::gl::detail
