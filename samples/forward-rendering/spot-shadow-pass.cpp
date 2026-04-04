#include "app/App.h"

#include <nfx/Graphics.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>
#include <string_view>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kRockY = 5.10f;
    constexpr float kRockScale = 0.52f;

    constexpr int kSpotCount = 3;
    constexpr int kShadowResolution = 1024;
    constexpr float kSpotOrbitRadius = 5.5f;
    constexpr float kSpotHeight = 9.5f;
    constexpr float kSpotOrbitSpeed = 0.22f;
    constexpr float kSpotInnerAngle = 0.35f; // ~20 deg
    constexpr float kSpotOuterAngle = 0.62f; // ~35 deg
    constexpr float kSpotFar = 30.0f;
    constexpr float kSpotRadius = 24.0f;
    constexpr float kSpotIntensity = 2.8f;
    constexpr float kMarkerScale = 0.36f;
    // RGB spot colors
    constexpr float kSpotColors[kSpotCount][3] = { { 1.0f, 0.30f, 0.30f },
                                                   { 0.30f, 1.0f, 0.30f },
                                                   { 0.30f, 0.55f, 1.0f } };
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
    gl::SpotShadowPass* shadowPass = nullptr;

    gl::MeshHandle rockHandle;
    gl::MeshHandle markerSphereHandle;

    gl::MaterialHandle rockMaterial;
    gl::MaterialHandle floorMaterial;
    std::array<gl::MaterialHandle, kSpotCount> markerMaterials{};

    gl::Texture2DHandle rockDiffuseHandle;
    gl::Texture2DHandle terrainDiffuseHandle;

    gl::OrbitCamera orbitCamera;

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
        { "nfx-graphics - spot-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "spot-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "spot-shadow-pass: ObjLoader failed\n");
                return;
            }

            scene->rockHandle = scene->meshCache.create(*meshData);
            scene->markerSphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());

            if (!scene->rockHandle.isValid() || !scene->markerSphereHandle.isValid())
            {
                std::fprintf(stderr, "spot-shadow-pass: failed to create mesh resources\n");
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

            scene->shadowPass = scene->path.addShadowPass<gl::SpotShadowPass>("SpotShadow");
            if (!scene->shadowPass)
            {
                std::fprintf(stderr, "spot-shadow-pass: failed to create SpotShadow pass\n");
                return;
            }
            scene->shadowPass->setResolution(scene->texture2DCache, kShadowResolution, kShadowResolution);

            // Materials
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.75f, 0.75f, 0.75f };
                desc.specularColor = { 0.25f, 0.25f, 0.25f };
                desc.shininess = 16.0f;
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
                if (gl::Material* m = scene->materialCache.get(scene->floorMaterial))
                {
                    gl::RenderState floorState = m->renderState();
                    floorState.cullFace = false;
                    m->setRenderState(floorState);
                }
            }
            for (int i = 0; i < kSpotCount; ++i)
            {
                gl::UnlitMaterial desc;
                desc.color = { kSpotColors[i][0] * 1.2f, kSpotColors[i][1] * 1.2f, kSpotColors[i][2] * 1.2f };
                scene->markerMaterials[i] = desc.build(scene->shaderCache, scene->materialCache);
            }

            if (auto* grid = scene->path.addOverlay<gl::GridPass>("Grid"))
            {
                grid->setGridSize(1.0f);
                grid->setFadeDistance(90.0f);
            }
            else
            {
                std::fprintf(stderr, "spot-shadow-pass: failed to create Grid overlay\n");
                return;
            }

            if (auto* axes = scene->path.addOverlay<gl::AxesPass>("Axes"))
            {
                axes->setAxisLength(500.0f);
                axes->setFadeDistance(90.0f);
            }
            else
            {
                std::fprintf(stderr, "spot-shadow-pass: failed to create Axes overlay\n");
                return;
            }

            scene->path.setClearColor(0.02f, 0.02f, 0.04f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);
            scene->path.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 22.0f;
            scene->orbitCamera.elevation = 0.60f;
            scene->orbitCamera.target[1] = 0.45f;

            scene->ready = scene->rockHandle.isValid() && scene->markerSphereHandle.isValid() &&
                           scene->rockDiffuseHandle.isValid() && scene->terrainDiffuseHandle.isValid() &&
                           scene->rockMaterial.isValid() && scene->floorMaterial.isValid() &&
                           scene->markerMaterials[0].isValid() && scene->markerMaterials[1].isValid() &&
                           scene->markerMaterials[2].isValid() && scene->shadowPass != nullptr &&
                           scene->renderResources.has_value() && scene->shadowPass->shadowMaps()[0].texture.isValid();
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;

            gl::FrameData frame;
            frame.camera =
                scene->orbitCamera.toGpuData(0.9f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.1f;
            frame.ambientLight = ambient.toGpuData();

            {
                gl::DirectionalLight directional;
                directional.intensity = 0.01f;
                frame.directionalLight = directional.toGpuData(std::array<float, 3>{ 0.f, -1.f, 0.f }.data());
            }

            scene->time += scene->clock.tick();

            scene->path.geometryPass().clearQueue();
            frame.lights.clear();
            frame.spotShadowCount = 0;

            // Register 3 orbiting spot lights and update per-frame uniforms
            const float spotAngleStep = (2.0f * std::numbers::pi_v<float>) / static_cast<float>(kSpotCount);
            for (int i = 0; i < kSpotCount; ++i)
            {
                const float a = scene->time * kSpotOrbitSpeed + static_cast<float>(i) * spotAngleStep;
                const float px = std::cos(a) * kSpotOrbitRadius;
                const float pz = std::sin(a) * kSpotOrbitRadius;
                const float py = kSpotHeight;

                // Direction from light position to the levitating center rock
                const float dx = -px;
                const float dy = kRockY - py;
                const float dz = -pz;

                const gl::SpotLight spot = gl::SpotLight::create(
                    px,
                    py,
                    pz,
                    dx,
                    dy,
                    dz,
                    kSpotColors[i][0],
                    kSpotColors[i][1],
                    kSpotColors[i][2],
                    kSpotIntensity,
                    kSpotInnerAngle,
                    kSpotOuterAngle,
                    kSpotRadius,
                    kSpotFar);

                scene->shadowPass->addLight(spot);
                frame.lights.push_back(spot.toGpuData());
                frame.spotShadowMaps[i] = scene->shadowPass->shadowMaps()[i];
                frame.spotShadowCount = i + 1;

                // Marker sphere for this spot light
                gl::RenderCommand markerCmd;
                markerCmd.mesh = scene->markerSphereHandle;
                markerCmd.material = scene->markerMaterials[i];
                markerCmd.sortKey = 10 + static_cast<std::uint64_t>(i);
                {
                    math::Mat4 s, t;
                    math::mat4Scale(s, kMarkerScale, kMarkerScale, kMarkerScale);
                    math::mat4Translate(t, px, py, pz);
                    math::mat4Mul(markerCmd.transform, t, s);
                }
                scene->path.geometryPass().submit(markerCmd);
            }

            // Floor
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = 5;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, 8.5f, 2.4f, 8.5f);
                math::mat4Translate(t, 0.0f, -2.15f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->path.geometryPass().submit(floorCmd);

            // Single levitating center rock
            {
                gl::RenderCommand rockCmd;
                rockCmd.mesh = scene->rockHandle;
                rockCmd.material = scene->rockMaterial;
                rockCmd.sortKey = 40;

                math::Mat4 s, t;
                math::mat4Scale(s, kRockScale, kRockScale, kRockScale);
                math::mat4Translate(t, 0.0f, kRockY, 0.0f);
                math::mat4Mul(rockCmd.transform, t, s);

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
