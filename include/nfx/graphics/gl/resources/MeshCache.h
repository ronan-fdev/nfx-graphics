#pragma once

/**
 * \file MeshCache.h
 * \brief Declares the cache used to store Mesh instances.
 */

#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/mesh/MeshData.h"
#include "ResourceCache.h"

#include <cstdio>

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of meshes keyed by MeshHandle.
     */
    class MeshCache final : public ResourceCache<MeshTag, Mesh>
    {
    public:
        /**
         * \brief Creates a mesh from a MeshData container and stores it in the cache.
         * \param data CPU-side mesh data passed to Mesh::create().
         * \return A stable handle referencing the cached mesh, or an invalid handle on failure.
         */
        [[nodiscard]] MeshHandle create(const MeshData& data)
        {
            Mesh mesh = Mesh::create(data);
            if (!mesh.isValid())
            {
                std::fprintf(stderr, "[MeshCache] create: mesh creation from MeshData failed\n");
                return {};
            }
            return add(std::move(mesh));
        }

        /**
         * \brief Creates a mesh from a descriptor and stores it in the cache.
         * \param desc Vertex/index buffer description passed to Mesh::create().
         * \return A stable handle referencing the cached mesh, or an invalid handle on failure.
         */
        [[nodiscard]] MeshHandle create(const Mesh::Desc& desc)
        {
            Mesh mesh = Mesh::create(desc);
            if (!mesh.isValid())
            {
                std::fprintf(stderr, "[MeshCache] create: mesh creation from Desc failed\n");
                return {};
            }
            return add(std::move(mesh));
        }
    };
} // namespace nfx::graphics::gl
