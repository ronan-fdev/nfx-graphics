#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <string>
#include <unordered_set>

using namespace nfx::graphics::gl;

namespace
{
    struct DummyTag
    {
    };

    using DummyHandle = Handle<DummyTag>;
    using DummyCache = ResourceCache<DummyTag, std::string>;
} // namespace

TEST_SUITE("Handle")
{
    TEST_CASE("Default handle is invalid")
    {
        DummyHandle handle;
        CHECK(!handle.isValid());
        CHECK(handle.id == 0);
    }

    TEST_CASE("Handles compare by id")
    {
        CHECK(DummyHandle{ 1 } == DummyHandle{ 1 });
        CHECK(DummyHandle{ 1 } != DummyHandle{ 2 });
    }

    TEST_CASE("Handle hash is usable in unordered containers")
    {
        std::unordered_set<DummyHandle> set;
        set.insert(DummyHandle{ 1 });
        set.insert(DummyHandle{ 2 });
        set.insert(DummyHandle{ 1 }); // duplicate

        CHECK(set.size() == 2);
        CHECK(set.contains(DummyHandle{ 1 }));
        CHECK(set.contains(DummyHandle{ 2 }));
        CHECK(!set.contains(DummyHandle{ 3 }));
    }
}

TEST_SUITE("ResourceCache")
{
    TEST_CASE("Default cache is empty")
    {
        DummyCache cache;
        CHECK(cache.empty());
        CHECK(cache.size() == 0);
    }

    TEST_CASE("Add returns valid handles and stores values")
    {
        DummyCache cache;
        const auto first = cache.add("first");
        const auto second = cache.add("second");

        CHECK(first.isValid());
        CHECK(second.isValid());
        CHECK(first != second);
        CHECK(first.id == 1);
        CHECK(second.id == 2);
        CHECK(cache.size() == 2);
        REQUIRE(cache.get(first) != nullptr);
        REQUIRE(cache.get(second) != nullptr);
        CHECK(*cache.get(first) == "first");
        CHECK(*cache.get(second) == "second");
    }

    TEST_CASE("Mutable and const get return stored resource")
    {
        DummyCache cache;
        const auto handle = cache.add("value");

        auto* value = cache.get(handle);
        REQUIRE(value != nullptr);
        *value = "updated";

        const DummyCache& constCache = cache;
        const auto* constValue = constCache.get(handle);
        REQUIRE(constValue != nullptr);
        CHECK(*constValue == "updated");
    }

    TEST_CASE("Contains and remove reflect cache membership")
    {
        DummyCache cache;
        const auto handle = cache.add("value");

        CHECK(cache.contains(handle));
        CHECK(cache.remove(handle));
        CHECK(!cache.contains(handle));
        CHECK(cache.get(handle) == nullptr);
        CHECK(!cache.remove(handle));
    }

    TEST_CASE("Clear removes all resources")
    {
        DummyCache cache;
        const auto first = cache.add("first");
        const auto second = cache.add("second");

        REQUIRE(cache.size() == 2);
        CHECK(cache.contains(first));
        CHECK(cache.contains(second));
        cache.clear();
        CHECK(cache.empty());
        CHECK(cache.size() == 0);
    }

    TEST_CASE("Handles stay unique after remove and clear")
    {
        DummyCache cache;

        const auto first = cache.add("first");
        const auto second = cache.add("second");
        CHECK(cache.remove(first));

        const auto third = cache.add("third");
        CHECK(third.id > second.id);
        CHECK(third != first);

        cache.clear();
        const auto fourth = cache.add("fourth");
        CHECK(fourth.id > third.id);
        CHECK(fourth != first);
        CHECK(fourth != second);
        CHECK(fourth != third);
    }

    TEST_CASE("Get with unknown or invalid handle returns nullptr")
    {
        DummyCache cache;
        [[maybe_unused]] const auto handle = cache.add("value");

        CHECK(cache.get(DummyHandle{}) == nullptr);
        CHECK(cache.get(DummyHandle{ 999 }) == nullptr);

        const DummyCache& constCache = cache;
        CHECK(constCache.get(DummyHandle{}) == nullptr);
        CHECK(constCache.get(DummyHandle{ 999 }) == nullptr);
    }

    TEST_CASE("forEach visits all cached resources")
    {
        DummyCache cache;
        const auto h1 = cache.add("alpha");
        const auto h2 = cache.add("beta");
        const auto h3 = cache.add("gamma");

        std::size_t count = 0;
        bool sawAlpha = false;
        bool sawBeta = false;
        bool sawGamma = false;

        cache.forEach([&](DummyHandle, const std::string& val) {
            ++count;
            if (val == "alpha")
                sawAlpha = true;
            if (val == "beta")
                sawBeta = true;
            if (val == "gamma")
                sawGamma = true;
        });

        CHECK(count == 3);
        CHECK(sawAlpha);
        CHECK(sawBeta);
        CHECK(sawGamma);
        (void)h1;
        (void)h2;
        (void)h3;
    }

    TEST_CASE("forEach on empty cache visits nothing")
    {
        DummyCache cache;
        std::size_t count = 0;
        cache.forEach([&](DummyHandle, const std::string&) { ++count; });
        CHECK(count == 0);
    }
}

TEST_SUITE("SamplerCache - structural")
{
    TEST_CASE("Default SamplerCache is empty")
    {
        SamplerCache cache;
        CHECK(cache.empty());
        CHECK(cache.size() == 0);
    }

    TEST_CASE("Get on unknown handle returns nullptr")
    {
        SamplerCache cache;
        CHECK(cache.get(SamplerHandle{}) == nullptr);
        CHECK(cache.get(SamplerHandle{ 999 }) == nullptr);
    }

    TEST_CASE("Contains returns false for unknown handle")
    {
        SamplerCache cache;
        CHECK(!cache.contains(SamplerHandle{}));
        CHECK(!cache.contains(SamplerHandle{ 1 }));
    }

    TEST_CASE("Remove returns false on empty cache")
    {
        SamplerCache cache;
        CHECK(!cache.remove(SamplerHandle{ 1 }));
    }
}

TEST_SUITE("Texture2DCache")
{
    TEST_CASE("Texture2DCache::upload returns invalid handle and keeps cache empty on contract failure")
    {
        Texture2DCache cache;

        Texture2D::Data data;
        const unsigned char pixels[4] = { 255, 255, 255, 255 };
        data.pixels = pixels;
        data.width = 1;
        data.height = 1;
        data.params.internalFormat = Texture2D::InternalFormat::RGBA16F;

        const Texture2DHandle handle = cache.upload(data);
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }
}

TEST_SUITE("TextureCubeCache")
{
    TEST_CASE("TextureCubeCache::upload returns invalid handle and keeps cache empty on contract failure")
    {
        TextureCubeCache cache;

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

        const TextureCubeHandle handle = cache.upload(faces, params);
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }
}

TEST_SUITE("MaterialCache")
{
    TEST_CASE("MaterialCache::create returns invalid handle and keeps cache empty when shader handle is invalid")
    {
        MaterialCache cache;

        const MaterialHandle handle = cache.create(ShaderHandle{}, RenderState::opaque());
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }
}

TEST_SUITE("FontCache")
{
    TEST_CASE("FontCache::create returns invalid handle and keeps cache empty when atlas handle is invalid")
    {
        FontCache cache;

        Font font;
        font.atlas = Texture2DHandle{};

        const FontHandle handle = cache.create(std::move(font));
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }
}

TEST_SUITE("MeshCache")
{
    TEST_CASE("MeshCache::create from MeshData returns invalid handle and keeps cache empty on contract failure")
    {
        MeshCache cache;

        MeshData data;

        const MeshHandle handle = cache.create(data);
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }

    TEST_CASE("MeshCache::create from Desc returns invalid handle and keeps cache empty on contract failure")
    {
        MeshCache cache;

        Mesh::Desc desc{};

        const MeshHandle handle = cache.create(desc);
        CHECK_FALSE(handle.isValid());
        CHECK(cache.empty());
    }
}
