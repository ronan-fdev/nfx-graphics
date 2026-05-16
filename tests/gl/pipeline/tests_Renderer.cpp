#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <array>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#ifdef __linux__
    #include <unistd.h>
#elif defined(_WIN32)
    #include <io.h>
    #include <windows.h>
#endif

using namespace nfx::graphics::gl;

namespace
{
    constexpr std::string_view kStrictAbortEnv = "NFX_RUN_STRICT_ABORT_CHILD";
    constexpr std::string_view kWarnModeEnv = "NFX_RUN_WARN_MODE_CHILD";
    constexpr std::string_view kOffModeEnv = "NFX_RUN_OFF_MODE_CHILD";
    constexpr std::string_view kRenderNoInitEnv = "NFX_RUN_RENDER_NOINIT_CHILD";
    constexpr std::string_view kRenderNoFrameEnv = "NFX_RUN_RENDER_NOFRAME_CHILD";
    constexpr std::string_view kStrictAbortChildCase = "Strict mode aborts on invalid permutation invariants";
    constexpr std::string_view kWarnModeChildCase = "Warn mode logs invariant before context assertion";
    constexpr std::string_view kOffModeChildCase = "Off mode suppresses invariant warning before context assertion";
    constexpr std::string_view kStrictAbortMarker = "[RendererChild] mode=strict";
    constexpr std::string_view kWarnModeMarker = "[RendererChild] mode=warn";
    constexpr std::string_view kOffModeMarker = "[RendererChild] mode=off";
    constexpr std::string_view kInvariantWarnMsg =
        "[Renderer] WARN(INVARIANT): spotShadowCount is out of range for PipelineLimits::MaxSpotShadows";
    constexpr std::string_view kRenderNoFrameWarnMsg =
        "[Renderer] WARN(RECOVERABLE): render() called without setFrameData()";
    constexpr std::string_view kRenderNoInitMarker = "[RendererChild] scenario=render-no-init";
    constexpr std::string_view kRenderNoFrameMarker = "[RendererChild] scenario=render-no-framedata";
    constexpr std::string_view kRenderNoInitChildCase = "Render before initialize aborts in debug";
    constexpr std::string_view kRenderNoFrameChildCase =
        "Render without frame data logs warning before context assertion";

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

    [[nodiscard]] std::string currentExecutablePath()
    {
#ifdef __linux__
        std::array<char, 4096> buf{};
        const ssize_t len = ::readlink("/proc/self/exe", buf.data(), buf.size() - 1);
        REQUIRE(len > 0);
        buf[static_cast<std::size_t>(len)] = '\0';
        return std::string(buf.data(), static_cast<std::size_t>(len));
#elif defined(_WIN32)
        std::array<char, 4096> buf{};
        const DWORD len = ::GetModuleFileNameA(nullptr, buf.data(), static_cast<DWORD>(buf.size()));
        REQUIRE(len > 0);
        return std::string(buf.data(), static_cast<std::size_t>(len));
#endif
    }

    void runStrictAbortScenario()
    {
        Renderer renderer;
        ResourceFixture fixture;
        renderer.initialize(fixture.resources);
        renderer.setValidationMode(Renderer::ValidationMode::Strict);

        FrameData frame;
        frame.spotShadowCount = static_cast<int>(PipelineLimits::MaxSpotShadows) + 1;
        renderer.setFrameData(frame);

        renderer.render();
    }

    void runValidationScenario(Renderer::ValidationMode mode)
    {
        Renderer renderer;
        ResourceFixture fixture;
        renderer.initialize(fixture.resources);
        renderer.setValidationMode(mode);

        FrameData frame;
        frame.spotShadowCount = static_cast<int>(PipelineLimits::MaxSpotShadows) + 1;
        renderer.setFrameData(frame);

        renderer.render();
    }

    void runRenderBeforeInitializeScenario()
    {
        Renderer renderer;
        renderer.render();
    }

    void runRenderWithoutFrameDataScenario()
    {
        Renderer renderer;
        ResourceFixture fixture;
        renderer.initialize(fixture.resources);
        renderer.render();
    }

    struct ChildRunResult
    {
        int rc = 0;
        std::string output;
    };

    [[nodiscard]] ChildRunResult runChildCase(
        const std::string& exe, std::string_view testCase, std::string_view envVar, std::string_view logPrefix)
    {
        const auto now = std::chrono::system_clock::now().time_since_epoch().count();
        const std::filesystem::path childLog =
            std::filesystem::temp_directory_path() / (std::string{ logPrefix } + "_" + std::to_string(now) + ".log");

#ifdef __linux__
        setenv(envVar.data(), "1", 1);
#elif defined(_WIN32)
        _putenv_s(envVar.data(), "1");
#endif

        std::string cmd;
#ifdef __linux__
        cmd = "\"" + exe + "\" --test-case=\"" + std::string{ testCase } + "\" > \"" + childLog.string() + "\" 2>&1";
#elif defined(_WIN32)
        cmd = "cmd /C \"\"" + exe + "\" --test-case=\"" + std::string{ testCase } + "\" > \"" + childLog.string() +
              "\" 2>&1\"";
#endif

        const int rc = std::system(cmd.c_str());

#ifdef __linux__
        unsetenv(envVar.data());
#elif defined(_WIN32)
        _putenv_s(envVar.data(), "");
#endif

        std::ifstream in(childLog);
        REQUIRE(in.is_open());
        std::string output((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        std::filesystem::remove(childLog);

        return { rc, std::move(output) };
    }

    [[nodiscard]] std::string getEnvValue(std::string_view key)
    {
#ifdef __linux__
        const char* value = std::getenv(key.data());
        return value ? std::string{ value } : std::string{};
#elif defined(_WIN32)
        std::array<char, 4096> buffer{};
        const DWORD len = ::GetEnvironmentVariableA(key.data(), buffer.data(), static_cast<DWORD>(buffer.size()));
        if (len == 0 || len >= buffer.size())
        {
            return {};
        }

        return std::string(buffer.data(), static_cast<std::size_t>(len));
#endif
    }
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

    TEST_CASE("pass lookup returns nullptr for unknown name")
    {
        Renderer renderer;
        auto* created = renderer.createPass<CountingPass>("known-pass");
        REQUIRE(created != nullptr);

        CHECK(renderer.pass("missing-pass") == nullptr);
        const Renderer& constRenderer = renderer;
        CHECK(constRenderer.pass("missing-pass") == nullptr);
    }

    TEST_CASE("removePass on unknown name is a no-op")
    {
        Renderer renderer;
        auto* created = renderer.createPass<CountingPass>("kept-pass");
        REQUIRE(created != nullptr);

        CHECK_FALSE(renderer.removePass("missing-pass"));
        CHECK(renderer.count() == 1);
        CHECK(renderer.pass("kept-pass") == created);
    }

    TEST_CASE("clear removes all passes and invalidates lookups")
    {
        Renderer renderer;
        auto* p1 = renderer.createPass<CountingPass>("p1");
        auto* p2 = renderer.createPass<CountingPass>("p2");
        REQUIRE(p1 != nullptr);
        REQUIRE(p2 != nullptr);

        CHECK(renderer.count() == 2);
        renderer.clear();

        CHECK(renderer.count() == 0);
        CHECK(renderer.pass("p1") == nullptr);
        CHECK(renderer.pass("p2") == nullptr);
        CHECK_FALSE(renderer.removePass("p1"));
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

    TEST_CASE("disabled pass stays disabled and is still initialized")
    {
        Renderer renderer;
        auto* pass = renderer.createPass<CountingPass>("disabled-pass");
        REQUIRE(pass != nullptr);

        pass->setEnabled(false);
        CHECK_FALSE(pass->isEnabled());

        ResourceFixture fixture;
        renderer.initialize(fixture.resources);

        CHECK(pass->initializeCalls == 1);
        CHECK_FALSE(pass->isEnabled());
    }

    TEST_CASE("enabled flag toggles deterministically")
    {
        Renderer renderer;
        auto* pass = renderer.createPass<CountingPass>("toggle-pass");
        REQUIRE(pass != nullptr);

        CHECK(pass->isEnabled());
        pass->setEnabled(false);
        CHECK_FALSE(pass->isEnabled());
        pass->setEnabled(true);
        CHECK(pass->isEnabled());
    }

    TEST_CASE("setViewport/resetViewport are safe before initialize")
    {
        Renderer renderer;

        const ViewportRect vp{ 12, 34, 640, 360 };
        renderer.setViewport(vp);
        renderer.resetViewport();
        renderer.resetViewport();

        CHECK(renderer.count() == 0);
    }

    TEST_CASE("setViewport/resetViewport do not affect pass initialization lifecycle")
    {
        Renderer renderer;
        auto* pass = renderer.createPass<CountingPass>("viewport-pass");
        REQUIRE(pass != nullptr);

        renderer.setViewport(ViewportRect{ 0, 0, 320, 200 });

        ResourceFixture fixture;
        renderer.initialize(fixture.resources);
        CHECK(pass->initializeCalls == 1);

        renderer.resetViewport();
        renderer.initialize(fixture.resources);
        CHECK(pass->initializeCalls == 1);
    }

    TEST_CASE("Strict mode aborts on invalid permutation invariants")
    {
        const std::string childFlag = getEnvValue(kStrictAbortEnv);
        if (childFlag != "1")
        {
            return;
        }

        std::fprintf(stderr, "%.*s\n", static_cast<int>(kStrictAbortMarker.size()), kStrictAbortMarker.data());
        runStrictAbortScenario();
        FAIL("unreachable: strict validation should abort the process");
    }

    TEST_CASE("Render before initialize aborts in debug")
    {
        const std::string childFlag = getEnvValue(kRenderNoInitEnv);
        if (childFlag != "1")
        {
            return;
        }

        std::fprintf(stderr, "%.*s\n", static_cast<int>(kRenderNoInitMarker.size()), kRenderNoInitMarker.data());
        runRenderBeforeInitializeScenario();
        FAIL("unreachable: render before initialize should abort/assert");
    }

    TEST_CASE("Render without frame data logs warning before context assertion")
    {
        const std::string childFlag = getEnvValue(kRenderNoFrameEnv);
        if (childFlag != "1")
        {
            return;
        }

        std::fprintf(stderr, "%.*s\n", static_cast<int>(kRenderNoFrameMarker.size()), kRenderNoFrameMarker.data());
        runRenderWithoutFrameDataScenario();
        FAIL("unreachable: missing GL context should abort process");
    }

    TEST_CASE("Warn mode logs invariant before context assertion")
    {
        const std::string childFlag = getEnvValue(kWarnModeEnv);
        if (childFlag != "1")
        {
            return;
        }

        std::fprintf(stderr, "%.*s\n", static_cast<int>(kWarnModeMarker.size()), kWarnModeMarker.data());
        runValidationScenario(Renderer::ValidationMode::Warn);
        FAIL("unreachable: missing GL context should abort process");
    }

    TEST_CASE("Off mode suppresses invariant warning before context assertion")
    {
        const std::string childFlag = getEnvValue(kOffModeEnv);
        if (childFlag != "1")
        {
            return;
        }

        std::fprintf(stderr, "%.*s\n", static_cast<int>(kOffModeMarker.size()), kOffModeMarker.data());
        runValidationScenario(Renderer::ValidationMode::Off);
        FAIL("unreachable: missing GL context should abort process");
    }

    TEST_CASE("Strict mode abort is verified via subprocess")
    {
        const std::string exe = currentExecutablePath();
        REQUIRE(!exe.empty());

        const ChildRunResult child = runChildCase(exe, kStrictAbortChildCase, kStrictAbortEnv, "nfx_test_strict_abort");

        CHECK(child.output.find(std::string{ kStrictAbortMarker }) != std::string::npos);
        CHECK(child.rc != 0);
    }

    TEST_CASE("Warn mode is verified via subprocess")
    {
        const std::string exe = currentExecutablePath();
        REQUIRE(!exe.empty());

        const ChildRunResult child = runChildCase(exe, kWarnModeChildCase, kWarnModeEnv, "nfx_test_warn_mode");

        CHECK(child.output.find(std::string{ kWarnModeMarker }) != std::string::npos);
        CHECK(child.output.find(std::string{ kInvariantWarnMsg }) != std::string::npos);
        CHECK(child.rc != 0);
    }

    TEST_CASE("Off mode is verified via subprocess")
    {
        const std::string exe = currentExecutablePath();
        REQUIRE(!exe.empty());

        const ChildRunResult child = runChildCase(exe, kOffModeChildCase, kOffModeEnv, "nfx_test_off_mode");

        CHECK(child.output.find(std::string{ kOffModeMarker }) != std::string::npos);
        CHECK(child.output.find(std::string{ kInvariantWarnMsg }) == std::string::npos);
        CHECK(child.rc != 0);
    }

    TEST_CASE("Render before initialize is verified via subprocess")
    {
        const std::string exe = currentExecutablePath();
        REQUIRE(!exe.empty());

        const ChildRunResult child =
            runChildCase(exe, kRenderNoInitChildCase, kRenderNoInitEnv, "nfx_test_render_noinit");

        CHECK(child.output.find(std::string{ kRenderNoInitMarker }) != std::string::npos);
        CHECK(child.rc != 0);
    }

    TEST_CASE("Render without frame data is verified via subprocess")
    {
        const std::string exe = currentExecutablePath();
        REQUIRE(!exe.empty());

        const ChildRunResult child =
            runChildCase(exe, kRenderNoFrameChildCase, kRenderNoFrameEnv, "nfx_test_render_noframe");

        CHECK(child.output.find(std::string{ kRenderNoFrameMarker }) != std::string::npos);
        CHECK(child.output.find(std::string{ kRenderNoFrameWarnMsg }) != std::string::npos);
        CHECK(child.rc != 0);
    }
}
