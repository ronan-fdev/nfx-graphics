#include "nfx/graphics/gl/resources/MeshCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    MeshHandle MeshCache::create(const MeshData& data)
    {
        Mesh mesh = Mesh::create(data);
        if (!mesh.isValid())
        {
            internal::runtime::logError(
                "MeshCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: mesh creation from MeshData failed");
            return {};
        }
        return add(std::move(mesh));
    }

    MeshHandle MeshCache::create(const Mesh::Desc& desc)
    {
        Mesh mesh = Mesh::create(desc);
        if (!mesh.isValid())
        {
            internal::runtime::logError(
                "MeshCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: mesh creation from Desc failed");
            return {};
        }
        return add(std::move(mesh));
    }
} // namespace nfx::graphics::gl
