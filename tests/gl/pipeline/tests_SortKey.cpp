#include <doctest/doctest.h>

#include <nfx/graphics/gl/pipeline/queue/SortKey.h>

#include <algorithm>
#include <array>
#include <type_traits>
#include <vector>

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

    TEST_CASE("PackedSortKey construction is restricted to official builders")
    {
        CHECK_FALSE(std::is_constructible_v<PackedSortKey, std::uint64_t>);
        CHECK_FALSE(std::is_assignable_v<PackedSortKey&, std::uint64_t>);
    }

    TEST_CASE("policy mapping by pass bucket keeps expected layer semantics")
    {
        const PackedSortKey opaqueKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 42u, 0u);
        const PackedSortKey transparentKey = SortKey::packOpaque(SortKey::TransparentLayer, 0, 42u, 0u);
        const PackedSortKey shadowKey = SortKey::packFrontToBack(SortKey::ShadowLayer, 123u);
        const PackedSortKey overlayKey = SortKey::packFrontToBack(SortKey::OverlayLayer, 0u);

        CHECK(SortKey::layer(opaqueKey) == SortKey::OpaqueLayer);
        CHECK(SortKey::layer(transparentKey) == SortKey::TransparentLayer);
        CHECK(SortKey::layer(shadowKey) == SortKey::ShadowLayer);
        CHECK(SortKey::layer(overlayKey) == SortKey::OverlayLayer);

        CHECK(opaqueKey < transparentKey);
        CHECK(transparentKey < shadowKey);
        CHECK(shadowKey < overlayKey);
    }

    TEST_CASE("mixed key families keep comparator consistency")
    {
        const std::array<PackedSortKey, 8> keys = {
            SortKey::packOpaque(0, 0, 0, 0), SortKey::packOpaque(0, 0, 0, 1), SortKey::packOpaque(0, 0, 1, 0),
            SortKey::packOpaque(0, 1, 0, 0), SortKey::packOpaque(1, 0, 0, 0), SortKey::packBackToFront(1, 0xFFFFFFFFu),
            SortKey::packBackToFront(1, 0),  SortKey::packFrontToBack(2, 0)
        };

        for (std::size_t i = 0; i < keys.size(); ++i)
        {
            CHECK_FALSE(keys[i] < keys[i]);
            for (std::size_t j = 0; j < keys.size(); ++j)
            {
                if (keys[i] < keys[j])
                {
                    CHECK_FALSE(keys[j] < keys[i]);
                }
            }
        }

        CHECK(SortKey::packOpaque(1, 0, 0, 0) == SortKey::packBackToFront(1, 0xFFFFFFFFu));

        CHECK(SortKey::packBackToFront(1, 0xFFFFFFFFu) < SortKey::packBackToFront(1, 0xFFFFFFFEu));
        CHECK(SortKey::packOpaque(1, 0, 0, 0) < SortKey::packBackToFront(1, 0));
    }

    TEST_CASE("stable_sort preserves insertion order for equal keys")
    {
        struct Entry
        {
            int id;
            PackedSortKey key;
        };

        std::vector<Entry> entries = { { 10, SortKey::packOpaque(1, 2, 3, 4) },
                                       { 20, SortKey::packOpaque(1, 2, 3, 4) },
                                       { 30, SortKey::packOpaque(1, 2, 3, 4) },
                                       { 40, SortKey::packOpaque(1, 2, 3, 5) },
                                       { 50, SortKey::packOpaque(1, 2, 3, 4) } };

        std::stable_sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) { return a.key < b.key; });

        CHECK(entries[0].id == 10);
        CHECK(entries[1].id == 20);
        CHECK(entries[2].id == 30);
        CHECK(entries[3].id == 50);
        CHECK(entries[4].id == 40);
    }
}
