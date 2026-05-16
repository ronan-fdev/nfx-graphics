#include <doctest/doctest.h>

#include <nfx/graphics/gl/pipeline/queue/SortKey.h>

using namespace nfx::graphics::gl;

TEST_SUITE("SortKey")
{
    TEST_CASE("packOpaque round-trips its fields")
    {
        const PackedSortKey key = SortKey::packOpaque(2, 17, 409, 0xAABBCCDDu);

        CHECK(SortKey::layer(key) == 2);
        CHECK(SortKey::shaderId(key) == 17);
        CHECK(SortKey::materialId(key) == 409);
        CHECK(SortKey::depthBucket(key) == 0xAABBCCDDu);
    }

    TEST_CASE("packOpaque sorts by layer then shader then material then depth")
    {
        const PackedSortKey base = SortKey::packOpaque(1, 10, 20, 30);
        const PackedSortKey higherLayer = SortKey::packOpaque(2, 10, 20, 30);
        const PackedSortKey higherShader = SortKey::packOpaque(1, 11, 20, 30);
        const PackedSortKey higherMaterial = SortKey::packOpaque(1, 10, 21, 30);
        const PackedSortKey higherDepth = SortKey::packOpaque(1, 10, 20, 31);

        CHECK(base < higherLayer);
        CHECK(base < higherShader);
        CHECK(base < higherMaterial);
        CHECK(base < higherDepth);
    }

    TEST_CASE("packBackToFront inverts depth ordering")
    {
        const PackedSortKey nearKey = SortKey::packBackToFront(1, 10);
        const PackedSortKey farKey = SortKey::packBackToFront(1, 20);

        CHECK(farKey < nearKey);
        CHECK(SortKey::layer(nearKey) == 1);
        CHECK(SortKey::depthBucket(nearKey) == ~10u);
        CHECK(SortKey::depthBucket(farKey) == ~20u);
    }

    TEST_CASE("packFrontToBack keeps ascending depth ordering")
    {
        const PackedSortKey nearKey = SortKey::packFrontToBack(2, 10);
        const PackedSortKey farKey = SortKey::packFrontToBack(2, 20);

        CHECK(nearKey < farKey);
        CHECK(SortKey::layer(nearKey) == 2);
        CHECK(SortKey::depthBucket(nearKey) == 10u);
        CHECK(SortKey::depthBucket(farKey) == 20u);
    }

    TEST_CASE("layer constants are distinct")
    {
        CHECK(SortKey::OpaqueLayer != SortKey::TransparentLayer);
        CHECK(SortKey::OpaqueLayer != SortKey::ShadowLayer);
        CHECK(SortKey::OpaqueLayer != SortKey::OverlayLayer);
        CHECK(SortKey::TransparentLayer != SortKey::ShadowLayer);
        CHECK(SortKey::TransparentLayer != SortKey::OverlayLayer);
        CHECK(SortKey::ShadowLayer != SortKey::OverlayLayer);
    }

    TEST_CASE("packOpaque masks fields to their declared bit widths")
    {
        // layer overflows into 4 bits, shader into 12, material into 16, depth into 32
        const PackedSortKey key = SortKey::packOpaque(0xFFu, 0xFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu);

        CHECK(SortKey::layer(key) == (0xFFu & ((1u << SortKey::LayerBits) - 1u)));
        CHECK(SortKey::shaderId(key) == (0xFFFFu & ((1u << SortKey::ShaderBits) - 1u)));
        CHECK(SortKey::materialId(key) == (0xFFFFFFFFu & ((1u << SortKey::MaterialBits) - 1u)));
        CHECK(SortKey::depthBucket(key) == 0xFFFFFFFFu);
    }

    TEST_CASE("packOpaque zero fields produce zero key")
    {
        const PackedSortKey key = SortKey::packOpaque(0, 0, 0, 0);
        CHECK(key == PackedSortKey::zero());
        CHECK(key.isZero());
    }

    TEST_CASE("packBackToFront zero depth sorts last")
    {
        const PackedSortKey nearZero = SortKey::packBackToFront(0, 0);
        const PackedSortKey farMax = SortKey::packBackToFront(0, 0xFFFFFFFFu);

        // ~0 > ~0xFFFFFFFF so farMax (inverted=0) < nearZero (inverted=max)
        CHECK(farMax < nearZero);
    }

    TEST_CASE("layer dominates all other fields in packOpaque ordering")
    {
        const PackedSortKey highLayerMin = SortKey::packOpaque(1, 0, 0, 0);
        const PackedSortKey lowLayerMax = SortKey::packOpaque(0, 0xFFFu, 0xFFFFu, 0xFFFFFFFFu);

        CHECK(lowLayerMax < highLayerMin);
    }

    TEST_CASE("shader dominates material and depth in packOpaque ordering")
    {
        const PackedSortKey highShaderMin = SortKey::packOpaque(0, 2, 0, 0);
        const PackedSortKey lowShaderMax = SortKey::packOpaque(0, 1, 0xFFFFu, 0xFFFFFFFFu);

        CHECK(lowShaderMax < highShaderMin);
    }

    TEST_CASE("equal packOpaque keys compare equal")
    {
        const PackedSortKey a = SortKey::packOpaque(1, 10, 20, 30);
        const PackedSortKey b = SortKey::packOpaque(1, 10, 20, 30);

        CHECK(a == b);
        CHECK_FALSE(a < b);
        CHECK_FALSE(b < a);
    }

    TEST_CASE("packFrontToBack zero depth sorts before all others")
    {
        const PackedSortKey nearZero = SortKey::packFrontToBack(0, 0);
        const PackedSortKey anyFar = SortKey::packFrontToBack(0, 1);

        CHECK(nearZero < anyFar);
    }

    TEST_CASE("default PackedSortKey is zero")
    {
        const PackedSortKey key{};
        CHECK(key.isZero());
        CHECK(key == PackedSortKey::zero());
    }
}
