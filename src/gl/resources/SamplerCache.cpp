#include "nfx/graphics/gl/resources/SamplerCache.h"

#include "internal/runtime/Error.h"

namespace nfx::graphics::gl
{
    SamplerHandle SamplerCache::create()
    {
        Sampler sampler = Sampler::create();
        if (!sampler.isValid())
        {
            internal::runtime::logError(
                "SamplerCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: sampler creation failed");
            return {};
        }
        return add(std::move(sampler));
    }

    SamplerHandle SamplerCache::create(const Sampler::Params& params)
    {
        Sampler sampler = Sampler::create(params);
        if (!sampler.isValid())
        {
            internal::runtime::logError(
                "SamplerCache",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "create: sampler creation failed");
            return {};
        }
        return add(std::move(sampler));
    }
} // namespace nfx::graphics::gl
