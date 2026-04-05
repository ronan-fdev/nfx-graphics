#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/textures/TextureCube.h>

using namespace nfx::graphics::gl;

TEST_SUITE("TextureCube")
{
    TEST_CASE("TextureCube::fromMemory rejects non-square faces")
    {
        TextureCube::FaceData faces[6]{};
        const unsigned char px[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

        for (auto& face : faces)
        {
            face.pixels = px;
            face.width = 2;
            face.height = 1;
        }

        const TextureCube cube = TextureCube::fromMemory(faces);
        CHECK_FALSE(cube.isValid());
    }

    TEST_CASE("TextureCube::fromMemory rejects unsupported upload internal format")
    {
        TextureCube::FaceData faces[6]{};
        const unsigned char px[4] = { 255, 255, 255, 255 };

        for (auto& face : faces)
        {
            face.pixels = px;
            face.width = 1;
            face.height = 1;
        }

        TextureCube::Params params;
        params.internalFormat = TextureCube::InternalFormat::RGBA16F;

        const TextureCube cube = TextureCube::fromMemory(faces, params);
        CHECK_FALSE(cube.isValid());
    }

    TEST_CASE("TextureCube::allocate rejects non-positive mipLevels")
    {
        TextureCube::Params params;
        params.mipLevels = 0;

        const TextureCube cube = TextureCube::allocate(4, params);
        CHECK_FALSE(cube.isValid());
    }
}
