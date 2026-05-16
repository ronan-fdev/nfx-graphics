#include "app/App.h"

#include <nfx/Graphics.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

constexpr float kLightDir[3] = { 0.55f, -1.0f, 0.35f };
constexpr float kLightIntensity = 1.6f;
constexpr float kAmbientIntensity = 0.15f;
constexpr int kShadowRes = 2048;
constexpr float kShadowRadius = 12.0f;
constexpr float kShadowNear = 1.0f;
constexpr float kShadowFar = 40.0f;

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

    gl::MeshHandle cubeHandle;
    gl::MeshHandle sphereHandle;
    gl::MeshHandle planeHandle;
    gl::TextureCubeHandle skyboxCube;

    gl::Texture2DHandle brickDiffuse;
    gl::Texture2DHandle brickNormal;
    gl::Texture2DHandle rockDiffuse;
    gl::Texture2DHandle rockNormal;

    gl::MaterialHandle cubeMaterial;
    gl::MaterialHandle sphereMaterial;
    gl::MaterialHandle groundMaterial;

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
        { "nfx-graphics - skybox-pass", 1000, 700, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->planeHandle = scene->meshCache.create(gl::Primitive::plane());

            scene->brickDiffuse =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall.jpg", true, true));
            scene->brickNormal = scene->texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall_normal.jpg"));
            scene->rockDiffuse = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));
            scene->rockNormal =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_nor_gl_1k.jpg"));

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            // Cube: diffuse + normal + shadow
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = scene->brickDiffuse;
                desc.normalMap = scene->brickNormal;
                desc.specularColor = { 0.4f, 0.4f, 0.4f };
                desc.shininess = 32.f;
                desc.hasShadow = true;
                scene->cubeMaterial = desc.build(*scene->renderResources);
            }

            // Sphere: diffuse + normal + shadow
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = scene->brickDiffuse;
                desc.normalMap = scene->brickNormal;
                desc.specularColor = { 0.4f, 0.4f, 0.4f };
                desc.shininess = 32.f;
                desc.hasShadow = true;
                scene->sphereMaterial = desc.build(*scene->renderResources);
            }

            // Ground: rocky terrain + shadow
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = scene->rockDiffuse;
                desc.normalMap = scene->rockNormal;
                desc.specularColor = { 0.2f, 0.2f, 0.2f };
                desc.shininess = 12.f;
                desc.hasShadow = true;
                scene->groundMaterial = desc.build(*scene->renderResources);
                if (gl::Material* m = scene->materialCache.get(scene->groundMaterial))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            // ForwardRenderPath: shadow -> geometry -> skybox -> overlays -> present
            scene->shadowPass = scene->path.addShadowPass<gl::DirectionalShadowPass>("Shadow");
            if (!scene->shadowPass)
            {
                std::fprintf(stderr, "skybox-pass: failed to create Shadow pass\n");
                return;
            }
            scene->shadowPass->setResolution(scene->texture2DCache, kShadowRes, kShadowRes);

            scene->skyboxCube = smp::loadSkybox(scene->textureCubeCache, "skyboxes/fjords", true);
            if (!scene->skyboxCube.isValid())
            {
                std::fprintf(stderr, "skybox-pass: failed to load skybox cubemap\n");
                return;
            }
            scene->path.setSkybox(scene->textureCubeCache, scene->skyboxCube);

            scene->gridPass = scene->path.addOverlay<gl::GridPass>("Grid");
            if (!scene->gridPass)
            {
                std::fprintf(stderr, "skybox-pass: failed to create Grid overlay\n");
                return;
            }
            scene->gridPass->setGridSize(1.0f);
            scene->gridPass->setFadeDistance(60.0f);

            scene->axesPass = scene->path.addOverlay<gl::AxesPass>("Axes");
            if (!scene->axesPass)
            {
                std::fprintf(stderr, "skybox-pass: failed to create Axes overlay\n");
                return;
            }
            scene->axesPass->setAxisLength(1000.0f);
            scene->axesPass->setFadeDistance(60.0f);

            scene->path.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);
            scene->path.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 5.0f;
            scene->orbitCamera.elevation = 0.4f;

            scene->ready = scene->cubeHandle.isValid() && scene->sphereHandle.isValid() &&
                           scene->planeHandle.isValid() && scene->skyboxCube.isValid() &&
                           scene->cubeMaterial.isValid() && scene->sphereMaterial.isValid() &&
                           scene->groundMaterial.isValid() && scene->shadowPass != nullptr &&
                           scene->gridPass != nullptr && scene->axesPass != nullptr;
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

            scene->time += scene->clock.tick();

            // Build light-space matrix
            float dirLS[16];
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                dirLS, kLightDir, 0.f, 0.f, 0.f, kShadowRadius, kShadowNear, kShadowFar);
            scene->shadowPass->setLightSpaceMatrix(dirLS);

            // Submit to shadow pass
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->cubeHandle;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
                {
                    math::Mat4 r, t;
                    math::mat4RotateY(r, scene->time * 0.3f);
                    math::mat4Translate(t, -1.5f, 0.5f, 0.0f);
                    math::mat4Mul(cmd.transform, t, r);
                }
                scene->shadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->sphereHandle;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 20u, 0);
                {
                    math::Mat4 t;
                    math::mat4Translate(t, 1.5f, 0.5f, 0.0f);
                    cmd.transform = t;
                }
                scene->shadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->planeHandle;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 1u, 0);
                {
                    math::Mat4 scale, t;
                    math::mat4Scale(scale, 8.0f, 1.0f, 8.0f);
                    math::mat4Translate(t, 0.0f, -1.0f, 0.0f);
                    math::mat4Mul(cmd.transform, t, scale);
                }
                scene->shadowPass->submit(cmd);
            }

            // Frame data
            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = kAmbientIntensity;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = kLightIntensity;
            frame.directionalLight = dir.toGpuData(kLightDir);

            frame.hasDirShadow = true;
            frame.dirShadowMap = scene->shadowPass->shadowMap();

            scene->path.geometryPass().clearQueue();

            // Rotating cube
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->cubeHandle;
                cmd.material = scene->cubeMaterial;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
                {
                    math::Mat4 r, t;
                    math::mat4RotateY(r, scene->time * 0.3f);
                    math::mat4Translate(t, -1.5f, 0.5f, 0.0f);
                    math::mat4Mul(cmd.transform, t, r);
                }
                scene->path.geometryPass().submit(cmd);
            }

            // Static sphere
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->sphereHandle;
                cmd.material = scene->sphereMaterial;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 20u, 0);
                {
                    math::Mat4 t;
                    math::mat4Translate(t, 1.5f, 0.5f, 0.0f);
                    cmd.transform = t;
                }
                scene->path.geometryPass().submit(cmd);
            }

            // Ground plane
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->planeHandle;
                cmd.material = scene->groundMaterial;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 1u, 0);
                {
                    math::Mat4 scale, t;
                    math::mat4Scale(scale, 8.0f, 1.0f, 8.0f);
                    math::mat4Translate(t, 0.0f, -1.0f, 0.0f);
                    math::mat4Mul(cmd.transform, t, scale);
                }
                scene->path.geometryPass().submit(cmd);
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
