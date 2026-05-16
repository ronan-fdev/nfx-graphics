#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cmath>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

struct Scene
{
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::ShaderCache shaderCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    std::optional<gl::RenderResources> renderResources;

    gl::Renderer renderer;
    gl::GeometryPass* geometryPass = nullptr;
    gl::TransparentPass* transparentPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::MeshHandle cubeHandle;
    gl::MeshHandle sphereHandle;
    gl::MeshHandle planeHandle;
    gl::MaterialHandle cubeMaterial;
    gl::MaterialHandle sphereMaterial;
    gl::MaterialHandle planeMaterial;
    gl::MaterialHandle glassRedMaterial;
    gl::MaterialHandle glassGreenMaterial;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float angle = 0.0f;
    smp::Clock clock;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - transparent pass", 800, 600, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Meshes
            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->planeHandle = scene->meshCache.create(gl::Primitive::plane());

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            // Materials
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.95f, 0.90f, 0.20f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 24.0f;
                scene->cubeMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.20f, 0.65f, 0.95f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 64.0f;
                scene->sphereMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.28f, 0.30f, 0.34f };
                desc.specularColor = { 0.20f, 0.20f, 0.20f };
                desc.shininess = 8.0f;
                scene->planeMaterial = desc.build(*scene->renderResources);
                if (gl::Material* mat = scene->materialCache.get(scene->planeMaterial))
                {
                    gl::RenderState state = mat->renderState();
                    state.cullFace = false;
                    mat->setRenderState(state);
                }
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.95f, 0.25f, 0.25f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 96.0f;
                desc.alpha = 0.45f;
                scene->glassRedMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.25f, 0.95f, 0.55f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 96.0f;
                desc.alpha = 0.35f;
                scene->glassGreenMaterial = desc.build(*scene->renderResources);
            }

            // Passes
            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->transparentPass = scene->renderer.createPass<gl::TransparentPass>("Transparent");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");
            scene->renderer.initialize(*scene->renderResources);

            scene->geometryPass->setOutputSize(scene->texture2DCache, 800, 600);
            scene->geometryPass->setClearColor(true, 0.08f, 0.10f, 0.14f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);
            scene->geometryPass->setOrder(gl::RenderQueue::Order::BySortKey);
            scene->transparentPass->setTargetTextures(
                scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());

            scene->presentPass->setInput(scene->geometryPass->colorOutput());
            scene->presentPass->setTonemapEnabled(true);
            scene->presentPass->setGammaEnabled(true);

            // Scene
            scene->orbitCamera.distance = 4.5f;
            scene->orbitCamera.target[1] = 0.25f;

            scene->ready =
                scene->cubeHandle.isValid() && scene->sphereHandle.isValid() && scene->planeHandle.isValid() &&
                scene->cubeMaterial.isValid() && scene->sphereMaterial.isValid() && scene->planeMaterial.isValid() &&
                scene->glassRedMaterial.isValid() && scene->glassGreenMaterial.isValid() &&
                scene->geometryPass != nullptr && scene->transparentPass != nullptr && scene->presentPass != nullptr;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;
            const auto& funcs = gl::Context::current().functions();
            funcs.glViewport(0, 0, safeW, safeH);

            if (scene->geometryPass->outputWidth() != safeW || scene->geometryPass->outputHeight() != safeH)
            {
                scene->geometryPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->transparentPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->presentPass->setInput(scene->geometryPass->colorOutput());
            }

            // Frame
            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 100.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.08f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight directional;
            directional.color[0] = directional.color[1] = directional.color[2] = 1.0f;
            directional.intensity = 1.0f;
            constexpr float kDir[3] = { -0.4f, -0.8f, -0.2f };
            frame.directionalLight = directional.toGpuData(kDir);

            // Scene
            scene->geometryPass->clearQueue();
            scene->transparentPass->clearQueue();

            const float dt = scene->clock.tick();
            scene->angle += 0.8f * dt;

            gl::RenderCommand planeCmd;
            planeCmd.mesh = scene->planeHandle;
            planeCmd.material = scene->planeMaterial;
            planeCmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
            {
                math::Mat4 s;
                math::Mat4 t;
                math::mat4Scale(s, 8.0f, 1.0f, 8.0f);
                math::mat4Translate(t, 0.0f, -1.15f, 0.0f);
                math::mat4Mul(planeCmd.transform, t, s);
            }
            scene->geometryPass->submit(planeCmd);

            gl::RenderCommand cubeCmd;
            cubeCmd.mesh = scene->cubeHandle;
            cubeCmd.material = scene->cubeMaterial;
            cubeCmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 20u, 0);
            {
                math::Mat4 r;
                math::Mat4 t;
                math::mat4RotateY(r, scene->angle);
                math::mat4Translate(t, -1.6f, 0.0f, 0.0f);
                math::mat4Mul(cubeCmd.transform, t, r);
            }
            scene->geometryPass->submit(cubeCmd);

            gl::RenderCommand sphereCmd;
            sphereCmd.mesh = scene->sphereHandle;
            sphereCmd.material = scene->sphereMaterial;
            sphereCmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 30u, 0);
            {
                math::Mat4 t;
                math::mat4Translate(t, 1.6f, 0.05f, 0.0f);
                sphereCmd.transform = t;
            }
            scene->geometryPass->submit(sphereCmd);

            // Transparent glass spheres: crossing trajectories to showcase back-to-front sorting
            const float t = scene->angle * 1.3f;
            const float zA = 0.9f * std::sin(t);
            const float zB = -0.9f * std::sin(t);

            gl::RenderCommand glassA;
            glassA.mesh = scene->sphereHandle;
            glassA.material = scene->glassRedMaterial;
            {
                math::Mat4 s;
                math::Mat4 tr;
                math::mat4Scale(s, 0.90f, 0.90f, 0.90f);
                math::mat4Translate(tr, -1.20f, 0.55f, zA);
                math::mat4Mul(glassA.transform, tr, s);
            }
            scene->transparentPass->submit(glassA);

            gl::RenderCommand glassB;
            glassB.mesh = scene->sphereHandle;
            glassB.material = scene->glassGreenMaterial;
            {
                math::Mat4 s;
                math::Mat4 tr;
                math::mat4Scale(s, 0.90f, 0.90f, 0.90f);
                math::mat4Translate(tr, 1.20f, 0.55f, zB);
                math::mat4Mul(glassB.transform, tr, s);
            }
            scene->transparentPass->submit(glassB);

            scene->transparentPass->setCameraPosition(frame.camera.position);

            // Render
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
