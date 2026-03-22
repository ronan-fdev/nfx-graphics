#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/textures/Texture2D.h>

using namespace nfx::graphics::gl;

TEST_SUITE("Texture2D")
{
    TEST_CASE("Texture2D::fromMemory rejects unsupported upload internal format")
    {
        Texture2D::Params params;
        params.internalFormat = Texture2D::InternalFormat::RGBA16F;

        const unsigned char pixels[4] = { 255, 255, 255, 255 };
        const Texture2D tex = Texture2D::fromMemory(pixels, 1, 1, params);

        CHECK_FALSE(tex.isValid());
    }

    TEST_CASE("Texture2D::allocate rejects invalid internal format enum")
    {
        Texture2D::Params params;
        params.internalFormat = static_cast<Texture2D::InternalFormat>(0x7fffffff);

        const Texture2D tex = Texture2D::allocate(4, 4, params);
        CHECK_FALSE(tex.isValid());
    }
}
