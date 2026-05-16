#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>
#include <random>
#include <string_view>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr int kRockCount = 8;
    constexpr float kRockRingRadius = 4.6f;
    constexpr float kRockOrbitSpeed = 0.45f;
    constexpr float kRockBobSpeed = 1.7f;
    constexpr float kRockAngleStep = (2.0f * std::numbers::pi_v<float>) / static_cast<float>(kRockCount);
    constexpr float kRockBaseY = 5.10f;
    constexpr float kRockBobAmplitude = 0.20f;
    constexpr int kShadowResolution = 2048;
    constexpr float kShadowSceneRadius = 8.0f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 30.0f;
    constexpr float kLightDir[3] = { -0.35f, -0.75f, -0.40f };
} // namespace

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    std::optional<gl::RenderResources> renderResources;

    gl::ForwardRenderPath path;
    gl::DirectionalShadowPass* shadowPass = nullptr;
    gl::GridPass* gridPass = nullptr;
    gl::AxesPass* axesPass = nullptr;

    gl::MeshHandle rockHandle;

    gl::MaterialHandle rockMaterial;
    gl::MaterialHandle floorMaterial;

    gl::Texture2DHandle rockDiffuseHandle;
    gl::Texture2DHandle terrainDiffuseHandle;

    gl::OrbitCamera orbitCamera;

    std::vector<math::Vec3> rockSpinAxes;
    std::vector<float> rockSpinSpeeds;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float time = 0.0f;
    smp::Clock clock;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - directional-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "directional-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "directional-shadow-pass: ObjLoader failed\n");
                return;
            }

            scene->rockHandle = scene->meshCache.create(*meshData);

            if (!scene->rockHandle.isValid())
            {
                std::fprintf(stderr, "directional-shadow-pass: failed to create mesh\n");
                return;
            }

            scene->rockDiffuseHandle =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", true, true));
            scene->terrainDiffuseHandle = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            // Materials
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.75f, 0.75f, 0.75f };
                desc.specularColor = { 0.25f, 0.25f, 0.25f };
                desc.shininess = 12.0f;
                desc.diffuseMap = scene->rockDiffuseHandle;
                desc.hasShadow = true;
                scene->rockMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.35f, 0.35f, 0.35f };
                desc.specularColor = { 0.03f, 0.03f, 0.03f };
                desc.shininess = 3.0f;
                desc.diffuseMap = scene->terrainDiffuseHandle;
                desc.hasShadow = true;
                scene->floorMaterial = desc.build(*scene->renderResources);
                if (gl::Material* floorMat = scene->materialCache.get(scene->floorMaterial))
                {
                    gl::RenderState floorState = floorMat->renderState();
                    floorState.cullFace = false;
                    floorMat->setRenderState(floorState);
                }
            }

            // ForwardRenderPath: shadow -> geometry -> overlays -> present
            scene->shadowPass = scene->path.addShadowPass<gl::DirectionalShadowPass>("Shadow");
            if (!scene->shadowPass)
            {
                std::fprintf(stderr, "directional-shadow-pass: failed to create Shadow pass\n");
                return;
            }
            scene->shadowPass->setResolution(scene->texture2DCache, kShadowResolution, kShadowResolution);

            scene->gridPass = scene->path.addOverlay<gl::GridPass>("Grid");
            if (!scene->gridPass)
            {
                std::fprintf(stderr, "directional-shadow-pass: failed to create Grid overlay\n");
                return;
            }
            scene->gridPass->setGridSize(1.0f);
            scene->gridPass->setFadeDistance(90.0f);

            scene->axesPass = scene->path.addOverlay<gl::AxesPass>("Axes");
            if (!scene->axesPass)
            {
                std::fprintf(stderr, "directional-shadow-pass: failed to create Axes overlay\n");
                return;
            }
            scene->axesPass->setAxisLength(500.0f);
            scene->axesPass->setFadeDistance(90.0f);

            scene->path.setClearColor(0.08f, 0.10f, 0.14f, 1.0f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);
            scene->path.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 14.0f;
            scene->orbitCamera.elevation = 0.50f;
            scene->orbitCamera.target[1] = 0.35f;

            // Generate random spin axes and speeds for each rock
            std::mt19937 rng(std::random_device{}());
            std::uniform_real_distribution<float> axisDist(-1.0f, 1.0f);
            std::uniform_real_distribution<float> speedDist(0.5f, 2.5f);
            scene->rockSpinAxes.resize(kRockCount);
            scene->rockSpinSpeeds.resize(kRockCount);
            for (int i = 0; i < kRockCount; ++i)
            {
                float x = axisDist(rng);
                float y = axisDist(rng);
                float z = axisDist(rng);
                float len = std::sqrt(x * x + y * y + z * z);
                if (len > 0.0f)
                {
                    scene->rockSpinAxes[i] = math::Vec3{ x / len, y / len, z / len };
                }
                else
                {
                    scene->rockSpinAxes[i] = math::Vec3{ 0.0f, 1.0f, 0.0f };
                }
                scene->rockSpinSpeeds[i] = speedDist(rng);
            }

            scene->ready = scene->rockHandle.isValid() && scene->rockDiffuseHandle.isValid() &&
                           scene->terrainDiffuseHandle.isValid() && scene->rockMaterial.isValid() &&
                           scene->floorMaterial.isValid() && scene->shadowPass != nullptr &&
                           scene->gridPass != nullptr && scene->axesPass != nullptr &&
                           scene->renderResources.has_value() && scene->rockSpinAxes.size() == kRockCount &&
                           scene->rockSpinSpeeds.size() == kRockCount;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;
            gl::Context::current().functions().glViewport(0, 0, safeW, safeH);

            gl::FrameData frame;
            frame.camera =
                scene->orbitCamera.toGpuData(0.9f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.12f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight directional;
            directional.color[0] = directional.color[1] = directional.color[2] = 1.0f;
            directional.intensity = 1.0f;
            frame.directionalLight = directional.toGpuData(kLightDir);

            // Build light-space matrix for the directional shadow pass
            math::Mat4 lightSpaceMat;
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                lightSpaceMat.data(), kLightDir, 0.0f, 0.0f, 0.0f, kShadowSceneRadius, kShadowNear, kShadowFar);
            scene->shadowPass->setLightSpaceMatrix(lightSpaceMat.data());
            frame.hasDirShadow = true;
            frame.dirShadowMap = scene->shadowPass->shadowMap();

            // shadowPass queue is cleared automatically at end() after each frame
            scene->path.geometryPass().clearQueue();

            scene->time += scene->clock.tick();

            // Floor
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 5u, 0);
            {
                math::Mat4 s;
                math::Mat4 t;
                math::mat4Scale(s, 8.5f, 2.4f, 8.5f);
                math::mat4Translate(t, 0.0f, -2.15f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->path.geometryPass().submit(floorCmd);

            for (int i = 0; i < kRockCount; ++i)
            {
                const float a = scene->time * kRockOrbitSpeed + static_cast<float>(i) * kRockAngleStep;
                const float x = std::cos(a) * kRockRingRadius;
                const float z = std::sin(a) * kRockRingRadius;
                const float y =
                    kRockBaseY + kRockBobAmplitude * std::sin(scene->time * kRockBobSpeed + static_cast<float>(i));

                gl::RenderCommand rockCmd;
                rockCmd.mesh = scene->rockHandle;
                rockCmd.material = scene->rockMaterial;
                rockCmd.sortKey =
                    gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, static_cast<std::uint32_t>(20 + i), 0);

                math::Mat4 s;
                math::Mat4 r;
                math::Mat4 rSpin;
                math::Mat4 t;
                math::Mat4 rs;
                math::mat4Scale(s, 0.42f, 0.42f, 0.42f);
                math::mat4RotateY(r, -a * 1.3f);

                // Apply individual spin rotation around random axis using quaternions
                const auto& axis = scene->rockSpinAxes[i];
                float spinAngle = scene->time * scene->rockSpinSpeeds[i];
                math::Quat spinQuat = math::quatAngleAxis(spinAngle, axis.x, axis.y, axis.z);
                math::quatToMat4(spinQuat, rSpin);
                math::mat4Mul(rs, r, rSpin);
                math::Mat4 rss;
                math::mat4Mul(rss, rs, s);
                math::mat4Translate(t, x, y, z);
                math::mat4Mul(rockCmd.transform, t, rss);

                scene->path.geometryPass().submit(rockCmd);
                scene->shadowPass->submit(rockCmd);
            }

            scene->path.render(frame, safeW, safeH);
        },

        // onShutdown
        [&] { scene.reset(); },

        // onMouseMove
        [&](int x, int y) {
            if (!scene)
            {
                return;
            }
            if (!scene->hasMouse)
            {
                scene->lastMouseX = x;
                scene->lastMouseY = y;
                scene->hasMouse = true;
                return;
            }
            const float dx = static_cast<float>(x - scene->lastMouseX);
            const float dy = static_cast<float>(y - scene->lastMouseY);
            scene->lastMouseX = x;
            scene->lastMouseY = y;
            if (scene->middleDown)
            {
                scene->orbitCamera.orbit(dx, dy);
            }
            if (scene->rightDown)
            {
                scene->orbitCamera.pan(dx, dy);
            }
        },

        // onMouseButton
        [&](int button, bool pressed) {
            if (!scene)
            {
                return;
            }
            if (button == 2)
            {
                scene->middleDown = pressed;
            }
            if (button == 3)
            {
                scene->rightDown = pressed;
            }
        },

        // onScroll
        [&](float delta) {
            if (!scene)
            {
                return;
            }
            scene->orbitCamera.zoom(delta);
        });
}
