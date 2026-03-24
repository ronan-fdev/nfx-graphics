#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/textures/Sampler.h>

using namespace nfx::graphics::gl;

TEST_SUITE("Sampler")
{
    TEST_CASE("Sampler::create rejects mipmap magnification filters")
    {
        Sampler::Params params;
        params.magFilter = Sampler::Filter::LinearMipmapLinear;

        const Sampler sampler = Sampler::create(params);
        CHECK_FALSE(sampler.isValid());
    }
}
