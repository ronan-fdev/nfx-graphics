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
    constexpr float kRockY = 1.8f;
    constexpr float kRockScale = 0.72f;

    constexpr int kShadowResolution = 1024;
    constexpr float kPointOrbitRadius = 4.0f;
    constexpr float kPointHeight = 3.5f;
    constexpr float kPointOrbitSpeed = 0.20f;
    constexpr float kPointFar = 20.0f;
    constexpr float kPointRadius = 12.0f;
    constexpr float kPointIntensity = 6.0f;
    constexpr float kMarkerScale = 0.22f;

    // Warm incandescent white
    constexpr float kPointColor[3] = { 1.0f, 0.82f, 0.55f };
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

    gl::Renderer renderer;
    gl::PointShadowPass* shadowPass = nullptr;
    gl::GeometryPass* geometryPass = nullptr;
    gl::GridPass* gridPass = nullptr;
    gl::AxesPass* axesPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::MeshHandle rockHandle;
    gl::MeshHandle markerSphereHandle;

    gl::MaterialHandle rockMaterial;
    gl::MaterialHandle floorMaterial;
    gl::MaterialHandle markerMaterial;

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
        { "nfx-graphics - point-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "point-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "point-shadow-pass: ObjLoader failed\n");
                return;
            }

            scene->rockHandle = scene->meshCache.create(*meshData);
            scene->markerSphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());

            if (!scene->rockHandle.isValid() || !scene->markerSphereHandle.isValid())
            {
                std::fprintf(stderr, "point-shadow-pass: failed to create mesh resources\n");
                return;
            }

            scene->rockDiffuseHandle =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", true, true));
            scene->terrainDiffuseHandle = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));

            // Shadow pass first, then geometry
            scene->shadowPass = scene->renderer.createPass<gl::PointShadowPass>("PointShadow");
            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->gridPass = scene->renderer.createPass<gl::GridPass>("Grid");
            scene->axesPass = scene->renderer.createPass<gl::AxesPass>("Axes");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->shadowPass->setResolution(scene->textureCubeCache, kShadowResolution);

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
            }
            {
                gl::UnlitMaterial desc;
                desc.color = { 1.2f, 1.15f, 1.0f };
                scene->markerMaterial = desc.build(scene->shaderCache, scene->materialCache);
            }

            scene->renderer.initialize(*scene->renderResources);

            scene->geometryPass->setOutputSize(scene->texture2DCache, 1280, 720);
            scene->geometryPass->setClearColor(true, 0.02f, 0.02f, 0.04f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);
            scene->geometryPass->setOrder(gl::RenderQueue::Order::BySortKey);

            scene->gridPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->gridPass->setGridSize(1.0f);
            scene->gridPass->setFadeDistance(90.0f);
            scene->axesPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->axesPass->setAxisLength(500.0f);
            scene->axesPass->setFadeDistance(90.0f);

            scene->presentPass->setInput(scene->geometryPass->colorOutput());
            scene->presentPass->setTonemapEnabled(true);
            scene->presentPass->setGammaEnabled(true);

            scene->orbitCamera.distance = 10.0f;
            scene->orbitCamera.elevation = 0.55f;
            scene->orbitCamera.target[1] = 1.2f;

            scene->ready = scene->rockHandle.isValid() && scene->markerSphereHandle.isValid() &&
                           scene->rockDiffuseHandle.isValid() && scene->terrainDiffuseHandle.isValid() &&
                           scene->rockMaterial.isValid() && scene->floorMaterial.isValid() &&
                           scene->markerMaterial.isValid() && scene->shadowPass != nullptr &&
                           scene->geometryPass != nullptr && scene->gridPass != nullptr && scene->axesPass != nullptr &&
                           scene->presentPass != nullptr && scene->renderResources.has_value() &&
                           scene->shadowPass->shadowMaps()[0].texture.isValid();
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

            if (scene->geometryPass->outputWidth() != safeW || scene->geometryPass->outputHeight() != safeH)
            {
                scene->geometryPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->gridPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->axesPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->presentPass->setInput(scene->geometryPass->colorOutput());
            }

            gl::FrameData frame;
            frame.camera =
                scene->orbitCamera.toGpuData(0.9f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.13f;
            frame.ambientLight = ambient.toGpuData();

            {
                gl::DirectionalLight directional;
                directional.intensity = 0.01f;
                frame.directionalLight = directional.toGpuData(std::array<float, 3>{ 0.f, -1.f, 0.f }.data());
            }

            scene->time += scene->clock.tick();
            scene->geometryPass->clearQueue();

            const float a = scene->time * kPointOrbitSpeed;
            const float px = std::cos(a) * kPointOrbitRadius;
            const float pz = std::sin(a) * kPointOrbitRadius;
            const float py = kPointHeight;

            const gl::PointLight point = gl::PointLight::create(
                px, py, pz, kPointColor[0], kPointColor[1], kPointColor[2], kPointIntensity, kPointRadius, kPointFar);

            scene->shadowPass->addLight(point);
            frame.lights.clear();
            frame.lights.push_back(point.toGpuData());
            frame.pointShadowCount = 1;
            frame.pointShadowMaps[0] = scene->shadowPass->shadowMaps()[0];

            // Marker sphere for point light
            gl::RenderCommand markerCmd;
            markerCmd.mesh = scene->markerSphereHandle;
            markerCmd.material = scene->markerMaterial;
            markerCmd.sortKey = 10;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, kMarkerScale, kMarkerScale, kMarkerScale);
                math::mat4Translate(t, px, py, pz);
                math::mat4Mul(markerCmd.transform, t, s);
            }
            scene->geometryPass->submit(markerCmd);

            // Floor: rock mesh scaled flat for omnidirectional shadow reception
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = 20;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, 9.0f, 1.0f, 9.0f);
                math::mat4Translate(t, 0.0f, 0.0f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->geometryPass->submit(floorCmd);

            // Single levitating center rock
            gl::RenderCommand rockCmd;
            rockCmd.mesh = scene->rockHandle;
            rockCmd.material = scene->rockMaterial;
            rockCmd.sortKey = 40;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, kRockScale, kRockScale, kRockScale);
                math::mat4Translate(t, 0.0f, kRockY, 0.0f);
                math::mat4Mul(rockCmd.transform, t, s);
            }
            scene->geometryPass->submit(rockCmd);
            scene->shadowPass->submit(rockCmd);

            scene->renderer.setFrameData(frame);
            scene->renderer.render();
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
