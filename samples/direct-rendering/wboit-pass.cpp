#include "app/App.h"

#include <nfx/Graphics.h>

#include <embedded_objects.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
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

    gl::Renderer renderer;
    gl::GeometryPass* geometryPass = nullptr;
    gl::WboitPass* wboitPass = nullptr;
    gl::GridPass* gridPass = nullptr;
    gl::AxesPass* axesPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::MeshHandle sphereHandle;
    gl::MeshHandle rockHandle;

    gl::MaterialHandle opaqueMat;
    gl::MaterialHandle redMat;
    gl::MaterialHandle greenMat;
    gl::MaterialHandle blueMat;

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
        { "nfx-graphics - wboit-pass", 1024, 768, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere(32, 32));
            const auto* rockRes = smp::models::find("obj/rock/rock.obj");
            if (!rockRes)
            {
                std::fprintf(stderr, "wboit: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view rockText(
                reinterpret_cast<const char*>(rockRes->data), static_cast<std::size_t>(rockRes->size));
            const auto rockMesh = smp::ObjLoader::fromSource(rockText);
            if (!rockMesh)
            {
                std::fprintf(stderr, "wboit: ObjLoader failed for rock mesh\n");
                return;
            }
            scene->rockHandle = scene->meshCache.create(*rockMesh);

            scene->renderResources.emplace(gl::RenderResources{
                scene->meshCache,
                scene->materialCache,
                scene->shaderCache,
                scene->texture2DCache,
                scene->textureCubeCache,
                scene->samplerCache,
            });

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.95f, 0.90f, 0.30f };
                desc.specularColor = { 0.8f, 0.8f, 0.8f };
                desc.shininess = 64.0f;
                scene->opaqueMat = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 1.0f, 0.2f, 0.2f };
                desc.specularColor = { 0.5f, 0.5f, 0.5f };
                desc.shininess = 32.0f;
                desc.alpha = 0.45f;
                scene->redMat = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.2f, 1.0f, 0.3f };
                desc.specularColor = { 0.5f, 0.5f, 0.5f };
                desc.shininess = 32.0f;
                desc.alpha = 0.45f;
                scene->greenMat = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.2f, 0.4f, 1.0f };
                desc.specularColor = { 0.5f, 0.5f, 0.5f };
                desc.shininess = 32.0f;
                desc.alpha = 0.45f;
                scene->blueMat = desc.build(*scene->renderResources);
            }

            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->wboitPass = scene->renderer.createPass<gl::WboitPass>("Wboit");
            scene->gridPass = scene->renderer.createPass<gl::GridPass>("Grid");
            scene->axesPass = scene->renderer.createPass<gl::AxesPass>("Axes");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->geometryPass->setOutputSize(scene->texture2DCache, 1024, 768);
            scene->geometryPass->setClearColor(true, 0.04f, 0.04f, 0.06f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);

            scene->wboitPass->setTargetColor(scene->geometryPass->colorOutput());
            scene->wboitPass->setGeometryDepth(scene->geometryPass->depthOutput());
            scene->wboitPass->setOutputSize(scene->texture2DCache, 1024, 768);

            scene->gridPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->gridPass->setGridSize(1.0f);
            scene->gridPass->setFadeDistance(30.0f);

            scene->axesPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->axesPass->setAxisLength(10000.0f);
            scene->axesPass->setFadeDistance(30.0f);

            scene->presentPass->setInput(scene->geometryPass->colorOutput());
            scene->presentPass->setTonemapEnabled(true);
            scene->presentPass->setGammaEnabled(true);

            scene->renderer.initialize(*scene->renderResources);

            scene->orbitCamera.elevation = std::numbers::pi_v<float> / 5.0f;
            scene->orbitCamera.distance = 12.0f;

            scene->ready = scene->sphereHandle.isValid() && scene->rockHandle.isValid() && scene->opaqueMat.isValid() &&
                           scene->redMat.isValid() && scene->greenMat.isValid() && scene->blueMat.isValid() &&
                           scene->geometryPass && scene->wboitPass && scene->gridPass && scene->axesPass &&
                           scene->presentPass;
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
                scene->wboitPass->setTargetColor(scene->geometryPass->colorOutput());
                scene->wboitPass->setGeometryDepth(scene->geometryPass->depthOutput());
                scene->wboitPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->gridPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->axesPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->presentPass->setInput(scene->geometryPass->colorOutput());
            }

            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 100.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 0.25f;
            ambient.intensity = 1.0f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 1.0f;
            constexpr float kLightDir[3] = { -0.4f, -0.9f, -0.3f };
            frame.directionalLight = dir.toGpuData(kLightDir);

            scene->renderer.setFrameData(frame);

            scene->geometryPass->clearQueue();
            scene->time += scene->clock.tick();

            // Opaque center object
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->rockHandle;
                cmd.material = scene->opaqueMat;
                cmd.sortKey = 10;
                math::Mat4 s, t;
                math::mat4Scale(s, 0.72f, 0.72f, 0.72f);
                math::mat4Translate(t, 0.0f, 1.5f, 0.5f);
                math::mat4Mul(cmd.transform, t, s);
                scene->geometryPass->submit(cmd);
            }

            constexpr float r = 1.6f;
            const float offsets[3][3] = {
                { 0.f, 1.5f, r },
                { -r * 0.8f, 1.5f, -r * 0.5f },
                { r * 0.8f, 1.5f, -r * 0.5f },
            };
            const gl::MaterialHandle mats[3] = { scene->redMat, scene->greenMat, scene->blueMat };

            for (int i = 0; i < 3; ++i)
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->sphereHandle;
                cmd.material = mats[i];
                cmd.sortKey = 20 + static_cast<std::uint64_t>(i);

                math::Mat4 s, tr;
                math::mat4Scale(s, 1.8f, 1.8f, 1.8f);
                math::mat4Translate(tr, offsets[i][0], offsets[i][1], offsets[i][2]);
                math::mat4Mul(cmd.transform, tr, s);

                scene->wboitPass->submit(cmd);
            }

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
            if (scene->rightDown)
            {
                scene->orbitCamera.orbit(dx, dy);
            }
            if (scene->middleDown)
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
                scene->rightDown = pressed;
            }
            if (button == 3)
            {
                scene->middleDown = pressed;
            }
        },

        // onScroll
        [&](float delta) {
            if (scene)
            {
                scene->orbitCamera.zoom(delta);
            }
        });
}
