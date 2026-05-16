#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

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

    gl::MeshHandle sphereHandle;
    gl::MaterialHandle sphereMaterial;
    gl::TextureCubeHandle skyboxHandle;
    gl::SamplerHandle envSampler;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - environment pass", 960, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->skyboxHandle = smp::loadSkybox(scene->textureCubeCache, "skyboxes/fjords", true);

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            gl::BlinnPhongMaterial reflective;
            reflective.diffuseColor = { 0.05f, 0.05f, 0.05f };
            reflective.specularColor = { 1.0f, 1.0f, 1.0f };
            reflective.shininess = 128.0f;
            reflective.hasEnvMap = true;
            reflective.envIntensity = 1.0f;
            scene->sphereMaterial = reflective.build(*scene->renderResources);

            // Explicit sampler for the environment cubemap: Linear filtering, clamp on all axes
            // Ensures deterministic sampling independent of the texture object's default state
            scene->envSampler =
                scene->samplerCache.add(gl::Sampler::create({ .minFilter = gl::Sampler::Filter::Linear,
                                                              .magFilter = gl::Sampler::Filter::Linear,
                                                              .wrapS = gl::Sampler::Wrap::ClampToEdge,
                                                              .wrapT = gl::Sampler::Wrap::ClampToEdge,
                                                              .wrapR = gl::Sampler::Wrap::ClampToEdge }));

            scene->path.enableEnvironment(1.0f);
            scene->path.setClearColor(0.0f, 0.0f, 0.0f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);

            scene->path.initialize(*scene->renderResources);

            scene->path.geometryPass().setOrder(gl::RenderQueue::Order::BySortKey);

            scene->orbitCamera.distance = 4.2f;
            scene->orbitCamera.elevation = 0.35f;

            scene->ready = scene->sphereHandle.isValid() && scene->sphereMaterial.isValid() &&
                           scene->skyboxHandle.isValid() && scene->envSampler.isValid() &&
                           scene->renderResources.has_value();
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
            frame.camera = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 200.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.20f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = 1.0f;
            dir.color[1] = 0.97f;
            dir.color[2] = 0.90f;
            dir.intensity = 1.1f;
            constexpr float kDir[3] = { 0.50f, -0.70f, 1.0f };
            frame.directionalLight = dir.toGpuData(kDir);

            frame.envMap = scene->skyboxHandle;
            frame.hasEnvMap = true;
            frame.envSampler = scene->envSampler;
            frame.hasEnvSampler = scene->envSampler.isValid();

            scene->path.geometryPass().clearQueue();

            gl::RenderCommand sphere;
            sphere.mesh = scene->sphereHandle;
            sphere.material = scene->sphereMaterial;
            sphere.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
            {
                math::Mat4 model;
                math::mat4Scale(model, 1.0f, 1.0f, 1.0f);
                sphere.transform = model;
            }
            scene->path.geometryPass().submit(sphere);

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
