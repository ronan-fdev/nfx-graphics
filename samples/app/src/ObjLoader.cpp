#include "../ObjLoader.h"

#include <detail/TangentUtils.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstring>

namespace gl = nfx::graphics::gl;

namespace nfx::samples
{
    namespace
    {
        // Hash function for vertex indices (v/vt/vn)
        struct VertexKey
        {
            int posIdx = 0;
            int uvIdx = 0;
            int normalIdx = 0;

            bool operator==(const VertexKey& other) const
            {
                return posIdx == other.posIdx && uvIdx == other.uvIdx && normalIdx == other.normalIdx;
            }
        };

        struct VertexKeyHash
        {
            std::size_t operator()(const VertexKey& k) const
            {
                return std::hash<int>()(k.posIdx) ^ (std::hash<int>()(k.uvIdx) << 1) ^
                       (std::hash<int>()(k.normalIdx) << 2);
            }
        };

        // Parse OBJ face index format: v, v/vt, v/vt/vn, v//vn
        VertexKey parseFaceIndex(const std::string& token)
        {
            VertexKey key;
            std::istringstream ss(token);
            std::string part;

            // Position
            if (std::getline(ss, part, '/'))
            {
                key.posIdx = std::stoi(part);
            }

            // UV
            if (std::getline(ss, part, '/'))
            {
                if (!part.empty())
                {
                    key.uvIdx = std::stoi(part);
                }
            }

            // Normal
            if (std::getline(ss, part, '/'))
            {
                if (!part.empty())
                {
                    key.normalIdx = std::stoi(part);
                }
            }

            return key;
        }
    } // namespace

    std::optional<gl::MeshData> ObjLoader::fromSource(std::string_view sourceText)
    {
        std::istringstream stream(std::string{ sourceText });
        return parseOBJ(stream, "<embedded>");
    }

    std::optional<gl::MeshData> ObjLoader::fromFile(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::fprintf(stderr, "[ObjLoader] Failed to open file: %s\n", path.string().c_str());
            return std::nullopt;
        }

        return parseOBJ(file, path.string());
    }

    std::optional<gl::MeshData> ObjLoader::parseOBJ(std::istream& stream, std::string_view sourceName)
    {
        std::vector<float> positions; // x, y, z
        std::vector<float> normals;   // nx, ny, nz
        std::vector<float> uvs;       // u, v

        std::vector<float> interleavedVertices;
        std::vector<unsigned int> indices;
        std::unordered_map<VertexKey, unsigned int, VertexKeyHash> vertexMap;

        std::string line;
        while (std::getline(stream, line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            std::istringstream ss{ line };
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") // Vertex position
            {
                float x, y, z;
                ss >> x >> y >> z;
                positions.push_back(x);
                positions.push_back(y);
                positions.push_back(z);
            }
            else if (prefix == "vt") // Texture coordinate
            {
                float u, v;
                ss >> u >> v;
                uvs.push_back(u);
                uvs.push_back(v);
            }
            else if (prefix == "vn") // Normal
            {
                float nx, ny, nz;
                ss >> nx >> ny >> nz;
                normals.push_back(nx);
                normals.push_back(ny);
                normals.push_back(nz);
            }
            else if (prefix == "f") // Face
            {
                std::vector<std::string> faceTokens;
                std::string token;
                while (ss >> token)
                {
                    faceTokens.push_back(token);
                }

                // Triangulate if needed (quad -> 2 triangles)
                for (size_t i = 1; i + 1 < faceTokens.size(); ++i)
                {
                    for (size_t j : { size_t{ 0 }, i, i + 1 })
                    {
                        VertexKey key = parseFaceIndex(faceTokens[j]);

                        // Check if we've seen this vertex combination before
                        auto it = vertexMap.find(key);
                        if (it != vertexMap.end())
                        {
                            indices.push_back(it->second);
                        }
                        else
                        {
                            unsigned int newIndex = static_cast<unsigned int>(interleavedVertices.size() / 8);

                            // Add interleaved vertex: pos(3) + normal(3) + uv(2)
                            // Position (OBJ indices are 1-based)
                            if (key.posIdx > 0 && key.posIdx <= static_cast<int>(positions.size() / 3))
                            {
                                int idx = (key.posIdx - 1) * 3;
                                interleavedVertices.push_back(positions[idx]);
                                interleavedVertices.push_back(positions[idx + 1]);
                                interleavedVertices.push_back(positions[idx + 2]);
                            }
                            else
                            {
                                interleavedVertices.push_back(0.0f);
                                interleavedVertices.push_back(0.0f);
                                interleavedVertices.push_back(0.0f);
                            }

                            // Normal
                            if (key.normalIdx > 0 && key.normalIdx <= static_cast<int>(normals.size() / 3))
                            {
                                int idx = (key.normalIdx - 1) * 3;
                                interleavedVertices.push_back(normals[idx]);
                                interleavedVertices.push_back(normals[idx + 1]);
                                interleavedVertices.push_back(normals[idx + 2]);
                            }
                            else
                            {
                                interleavedVertices.push_back(0.0f);
                                interleavedVertices.push_back(1.0f);
                                interleavedVertices.push_back(0.0f);
                            }

                            // UV
                            if (key.uvIdx > 0 && key.uvIdx <= static_cast<int>(uvs.size() / 2))
                            {
                                int idx = (key.uvIdx - 1) * 2;
                                interleavedVertices.push_back(uvs[idx]);
                                interleavedVertices.push_back(uvs[idx + 1]);
                            }
                            else
                            {
                                interleavedVertices.push_back(0.0f);
                                interleavedVertices.push_back(0.0f);
                            }

                            vertexMap[key] = newIndex;
                            indices.push_back(newIndex);
                        }
                    }
                }
            }
        }

        if (interleavedVertices.empty())
        {
            std::fprintf(
                stderr,
                "[ObjLoader] No vertices found in OBJ: %.*s\n",
                static_cast<int>(sourceName.size()),
                sourceName.data());

            return std::nullopt;
        }

        gl::detail::computeTangents(interleavedVertices, indices);

        gl::MeshData data;
        data.setVertexData(
            interleavedVertices.data(),
            interleavedVertices.size() * sizeof(float),
            {
                gl::VertexLayout::Float3, // position
                gl::VertexLayout::Float3, // normal
                gl::VertexLayout::Float2, // uv
                gl::VertexLayout::Float4  // tangent (xyz + handedness w)
            });
        data.setIndexData(indices.data(), indices.size(), gl::MeshData::IndexType::UInt32);

        return data;
    }
} // namespace nfx::samples
