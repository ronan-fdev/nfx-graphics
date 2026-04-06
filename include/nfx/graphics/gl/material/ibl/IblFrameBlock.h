#pragma once

/**
 * \file IblFrameBlock.h
 * \brief Declares the std140-compatible frame-global IBL state block.
 */

namespace nfx::graphics::gl
{
    struct IblFrameBlockData
    {
        int flags[4] = { 0, 0, 0, 0 }; ///< x=env, y=irradiance, z=prefiltered, w=brdfLut
    };

    static_assert(sizeof(IblFrameBlockData) == 16, "IblFrameBlockData must be 16 bytes (std140)");
} // namespace nfx::graphics::gl
