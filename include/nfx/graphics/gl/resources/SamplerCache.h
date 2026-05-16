#pragma once

/**
 * \file SamplerCache.h
 * \brief Declares the cache used to store Sampler instances.
 */

#include "nfx/graphics/gl/core/textures/Sampler.h"
#include "ResourceCache.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Cache of sampler objects keyed by SamplerHandle.
     */
    class SamplerCache final : public ResourceCache<SamplerTag, Sampler>
    {
    public:
        /**
         * \brief Creates a sampler with default parameters and stores it in the cache.
         * \return A stable handle referencing the cached sampler, or an invalid handle on failure.
         */
        [[nodiscard]] SamplerHandle create();

        /**
         * \brief Creates a sampler with explicit parameters and stores it in the cache.
         * \param params Sampling parameters passed to Sampler::create().
         * \return A stable handle referencing the cached sampler, or an invalid handle on failure.
         */
        [[nodiscard]] SamplerHandle create(const Sampler::Params& params);
    };
} // namespace nfx::graphics::gl
