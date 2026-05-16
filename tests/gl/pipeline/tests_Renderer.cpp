#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <memory>
#include <vector>

using namespace nfx::graphics::gl;

namespace
{
    struct CountingPass final : RenderPass
    {
        explicit CountingPass(std::string name, bool initResult = true)
            : RenderPass(std::move(name)),
              m_initResult(initResult)
        {}

        int initializeCalls = 0;
        int beginCalls = 0;
        int executeCalls = 0;
        int endCalls = 0;

    protected:
        bool initialize() override
        {
            ++initializeCalls;
            return m_initResult;
        }

        void begin() override { ++beginCalls; }

        void execute(RenderResources&) override { ++executeCalls; }

        void end() override { ++endCalls; }

    private:
        bool m_initResult = true;
    };

    struct ResourceFixture
    {
        MeshCache meshes;
        MaterialCache materials;
        ShaderCache shaders;
        Texture2DCache textures2D;
        TextureCubeCache texturesCube;
        SamplerCache samplers;

        RenderResources resources{ meshes, materials, shaders, textures2D, texturesCube, samplers };
    };

    struct OrderedInitPass final : RenderPass
    {
        OrderedInitPass(std::string name, std::vector<std::string>* orderSink)
            : RenderPass(std::move(name)),
              m_orderSink(orderSink)
        {}

        int initializeCalls = 0;

    protected:
        bool initialize() override
        {
            ++initializeCalls;
            if (m_orderSink)
            {
                m_orderSink->push_back(name());
            }
            return true;
        }

        void begin() override {}
        void execute(RenderResources&) override {}
        void end() override {}

    private:
        std::vector<std::string>* m_orderSink = nullptr;
    };
} // namespace

TEST_SUITE("Renderer")
{
    TEST_CASE("addPass ignores nullptr")
    {
        Renderer renderer;
        std::unique_ptr<RenderPass> nullPass;

        renderer.addPass(std::move(nullPass));

        CHECK(renderer.count() == 0);
    }

    TEST_CASE("createPass registers pass and lookup/remove work")
    {
        Renderer renderer;
        auto* created = renderer.createPass<CountingPass>("opaque");

        REQUIRE(created != nullptr);
        CHECK(renderer.count() == 1);
        CHECK(renderer.pass("opaque") == created);
        CHECK(renderer.removePass("opaque"));
        CHECK(renderer.count() == 0);
        CHECK(renderer.pass("opaque") == nullptr);
        CHECK_FALSE(renderer.removePass("opaque"));
    }

    TEST_CASE("initialize calls pass initialize once")
    {
        Renderer renderer;
        auto* created = renderer.createPass<CountingPass>("init-once");
        REQUIRE(created != nullptr);

        ResourceFixture fixture;
        renderer.initialize(fixture.resources);
        renderer.initialize(fixture.resources);

        CHECK(created->initializeCalls == 1);
    }

    TEST_CASE("initialize keeps insertion order for fallback custom passes")
    {
        Renderer renderer;
        std::vector<std::string> initOrder;

        auto* p1 = renderer.createPass<OrderedInitPass>("custom-a", &initOrder);
        auto* p2 = renderer.createPass<OrderedInitPass>("custom-b", &initOrder);
        auto* p3 = renderer.createPass<OrderedInitPass>("custom-c", &initOrder);

        REQUIRE(p1 != nullptr);
        REQUIRE(p2 != nullptr);
        REQUIRE(p3 != nullptr);

        ResourceFixture fixture;
        renderer.initialize(fixture.resources);

        REQUIRE(initOrder.size() == 3);
        CHECK(initOrder[0] == "custom-a");
        CHECK(initOrder[1] == "custom-b");
        CHECK(initOrder[2] == "custom-c");
        CHECK(p1->initializeCalls == 1);
        CHECK(p2->initializeCalls == 1);
        CHECK(p3->initializeCalls == 1);
    }
}
