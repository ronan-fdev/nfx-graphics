#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kLightDir[3] = { 0.55f, -1.0f, 0.35f };
    constexpr float kLightIntensity = 1.0f;
    constexpr float kAmbientIntensity = 0.22f;

    constexpr int kShadowRes = 2048;
    constexpr float kShadowRadius = 12.0f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 40.0f;

    constexpr int kPointShadowRes = 512;
    constexpr float kOrbRadius = 3.5f;
    constexpr float kOrbHeight = 2.0f;
    constexpr float kOrbSpeed = 0.6f;
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

    gl::DirectionalShadowPass* dirShadow = nullptr;
    gl::PointShadowPass* pointShadow = nullptr;

    gl::MeshHandle sphereHandle;
    gl::MeshHandle cubeHandle;
    gl::MeshHandle planeHandle;
    gl::MeshHandle orbHandle;

    gl::Texture2DHandle brickDiffuse;
    gl::Texture2DHandle brickNormal;
    gl::Texture2DHandle terrainDiffuse;
    gl::Texture2DHandle terrainNormal;

    gl::MaterialHandle opaqueMat;
    gl::MaterialHandle groundMat;
    gl::MaterialHandle orbMat;

    gl::MaterialHandle transpRed;
    gl::MaterialHandle transpGreen;
    gl::MaterialHandle transpBlue;

    gl::OrbitCamera orbitCamera;
    smp::Clock clock;
    float time = 0.0f;

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
        { "nfx-graphics - forward-path-showcase", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            // Meshes
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->planeHandle = scene->meshCache.create(gl::Primitive::plane());
            scene->orbHandle = scene->meshCache.create(gl::Primitive::uvSphere());

            // Textures
            scene->brickDiffuse =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall.jpg", true, true));
            scene->brickNormal = scene->texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall_normal.jpg"));
            scene->terrainDiffuse = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));
            scene->terrainNormal =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_nor_gl_1k.jpg"));

            // Materials
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = scene->brickDiffuse;
                desc.normalMap = scene->brickNormal;
                desc.specularColor = { 0.4f, 0.4f, 0.4f };
                desc.shininess = 32.0f;
                desc.hasShadow = true;
                scene->opaqueMat = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = scene->terrainDiffuse;
                desc.normalMap = scene->terrainNormal;
                desc.specularColor = { 0.1f, 0.1f, 0.1f };
                desc.shininess = 8.0f;
                desc.hasShadow = true;
                scene->groundMat = desc.build(*scene->renderResources);
                if (gl::Material* m = scene->materialCache.get(scene->groundMat))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }
            {
                gl::UnlitMaterial desc;
                desc.color = { 2.5f, 1.8f, 0.4f };
                scene->orbMat = desc.build(scene->shaderCache, scene->materialCache);
            }

            // Transparent spheres
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.5f, 0.05f, 0.05f };
                desc.specularColor = { 0.12f, 0.12f, 0.12f };
                desc.shininess = 32.0f;
                desc.alpha = 0.5f;
                scene->transpRed = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.05f, 0.5f, 0.05f };
                desc.specularColor = { 0.12f, 0.12f, 0.12f };
                desc.shininess = 32.0f;
                desc.alpha = 0.5f;
                scene->transpGreen = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.05f, 0.15f, 0.5f };
                desc.specularColor = { 0.12f, 0.12f, 0.12f };
                desc.shininess = 32.0f;
                desc.alpha = 0.5f;
                scene->transpBlue = desc.build(*scene->renderResources);
            }

            // ForwardRenderPath configuration
            scene->dirShadow = scene->path.addShadowPass<gl::DirectionalShadowPass>("DirShadow");
            if (!scene->dirShadow)
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create DirShadow pass\n");
                return;
            }
            scene->dirShadow->setResolution(scene->texture2DCache, kShadowRes, kShadowRes);

            scene->pointShadow = scene->path.addShadowPass<gl::PointShadowPass>("PointShadow");
            if (!scene->pointShadow)
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create PointShadow pass\n");
                return;
            }
            scene->pointShadow->setResolution(scene->textureCubeCache, kPointShadowRes);

            scene->path.setSkybox(
                scene->textureCubeCache, smp::loadSkybox(scene->textureCubeCache, "skyboxes/fjords", true));

            scene->path.enableTransparency<gl::WboitPass>();

            if (auto* grid = scene->path.addOverlay<gl::GridPass>("Grid"))
            {
                grid->setGridSize(1.0f);
            }
            else
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create Grid overlay\n");
                return;
            }

            if (auto* axes = scene->path.addOverlay<gl::AxesPass>("Axes"))
            {
                axes->setAxisLength(500.0f);
            }
            else
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create Axes overlay\n");
                return;
            }

            scene->path.setClearColor(0.08f, 0.09f, 0.12f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);

            scene->path.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 14.0f;
            scene->orbitCamera.elevation = 0.45f;
            scene->orbitCamera.target[1] = 0.5f;
            scene->ready = scene->sphereHandle.isValid() && scene->cubeHandle.isValid() &&
                           scene->planeHandle.isValid() && scene->opaqueMat.isValid() && scene->groundMat.isValid() &&
                           scene->transpRed.isValid() && scene->transpGreen.isValid() && scene->transpBlue.isValid() &&
                           scene->orbMat.isValid() && scene->dirShadow != nullptr && scene->pointShadow != nullptr;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            scene->time += scene->clock.tick();

            // Light-space matrix
            float dirLS[16];
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                dirLS, kLightDir, 0.f, 0.f, 0.f, kShadowRadius, kShadowNear, kShadowFar);
            scene->dirShadow->setLightSpaceMatrix(dirLS);

            // Orbiting point light
            const float orbA = scene->time * kOrbSpeed;
            const float orbX = std::cos(orbA) * kOrbRadius;
            const float orbZ = std::sin(orbA) * kOrbRadius;
            const gl::PointLight orb =
                gl::PointLight::create(orbX, kOrbHeight, orbZ, 1.0f, 0.75f, 0.25f, 12.0f, 10.0f, 12.0f, 0.05f);
            scene->pointShadow->addLight(orb);

            // Geometry queue
            scene->path.geometryPass().clearQueue();

            // Ground
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->planeHandle;
                cmd.material = scene->groundMat;
                cmd.sortKey = 1;
                math::Mat4 sc, tr;
                math::mat4Scale(sc, 12.0f, 1.0f, 12.0f);
                math::mat4Translate(tr, 0.0f, -1.0f, 0.0f);
                math::mat4Mul(cmd.transform, tr, sc);
                scene->path.geometryPass().submit(cmd);
                scene->dirShadow->submit(cmd);
            }

            // Opaque sphere
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->sphereHandle;
                cmd.material = scene->opaqueMat;
                cmd.sortKey = 10;
                math::mat4Translate(cmd.transform, 0.0f, 0.0f, 0.0f);
                scene->path.geometryPass().submit(cmd);
                scene->dirShadow->submit(cmd);
                scene->pointShadow->submit(cmd);
            }

            // Rotating cube
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->cubeHandle;
                cmd.material = scene->opaqueMat;
                cmd.sortKey = 11;
                math::Mat4 r, tr;
                math::mat4RotateY(r, scene->time * 0.4f);
                math::mat4Translate(tr, -3.0f, 0.0f, 0.0f);
                math::mat4Mul(cmd.transform, tr, r);
                scene->path.geometryPass().submit(cmd);
                scene->dirShadow->submit(cmd);
                scene->pointShadow->submit(cmd);
            }

            // Orb marker
            {
                gl::RenderCommand cmd;
                cmd.mesh = scene->orbHandle;
                cmd.material = scene->orbMat;
                cmd.sortKey = 5;
                math::Mat4 sc, tr;
                math::mat4Scale(sc, 0.18f, 0.18f, 0.18f);
                math::mat4Translate(tr, orbX, kOrbHeight, orbZ);
                math::mat4Mul(cmd.transform, tr, sc);
                scene->path.geometryPass().submit(cmd);
            }

            // Transparent queue (WboitPass)
            if (auto* wboit = scene->path.get<gl::WboitPass>("Transparent"))
            {
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = scene->sphereHandle;
                    cmd.material = scene->transpRed;
                    cmd.sortKey = 1;
                    math::mat4Translate(cmd.transform, 3.0f, 0.0f, -1.5f);
                    wboit->submit(cmd);
                }
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = scene->sphereHandle;
                    cmd.material = scene->transpGreen;
                    cmd.sortKey = 2;
                    math::mat4Translate(cmd.transform, 3.0f, 0.0f, 0.0f);
                    wboit->submit(cmd);
                }
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = scene->sphereHandle;
                    cmd.material = scene->transpBlue;
                    cmd.sortKey = 3;
                    math::mat4Translate(cmd.transform, 3.0f, 0.0f, 1.5f);
                    wboit->submit(cmd);
                }
            }

            // Frame data
            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                0.9f, static_cast<float>(std::max(width, 1)) / static_cast<float>(std::max(height, 1)), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = kAmbientIntensity;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = kLightIntensity;
            frame.directionalLight = dir.toGpuData(kLightDir);

            frame.hasDirShadow = true;
            frame.dirShadowMap = scene->dirShadow->shadowMap();

            frame.pointShadowCount = 1;
            frame.pointShadowMaps[0] = scene->pointShadow->shadowMaps()[0];

            frame.lights.push_back(orb.toGpuData());

            scene->path.render(frame, width, height);
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
