#pragma once

/**
 * \file MeshTypes.h
 * \brief Declares shared mesh-related public types.
 */

namespace nfx::graphics::gl
{
    /**
     * \brief Supported index buffer element formats for mesh data and mesh runtime upload.
     */
    enum class MeshIndexType
    {
        UInt16,
        UInt32
    };
} // namespace nfx::graphics::gl
