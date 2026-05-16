#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kLightDir[3] = { 0.45f, -1.0f, 0.25f };
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

    gl::MeshHandle sphereMesh;
    gl::TextureCubeHandle skybox;

    gl::Texture2DHandle rusty04Diff;
    gl::Texture2DHandle rusty04Normal;
    gl::Texture2DHandle rusty04Arm;

    gl::Texture2DHandle rustyGridDiff;
    gl::Texture2DHandle rustyGridNormal;
    gl::Texture2DHandle rustyGridArm;

    gl::MaterialHandle rusty04Mat;
    gl::MaterialHandle rustyGridMat;

    gl::OrbitCamera orbit;

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
        { "nfx-graphics - pbr-minimal", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.sphereMesh = s.meshCache.create(gl::Primitive::uvSphere());

            s.rusty04Diff = s.texture2DCache.add(
                smp::loadEmbeddedTexture("rusty_metal_04_1k/rusty_metal_04_diff_1k.jpg", true, true));
            s.rusty04Normal =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rusty_metal_04_1k/rusty_metal_04_nor_gl_1k.jpg"));
            s.rusty04Arm =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rusty_metal_04_1k/rusty_metal_04_arm_1k.jpg"));

            s.rustyGridDiff = s.texture2DCache.add(
                smp::loadEmbeddedTexture("rusty_metal_grid_1k/rusty_metal_grid_diff_1k.jpg", true, true));
            s.rustyGridNormal =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rusty_metal_grid_1k/rusty_metal_grid_nor_gl_1k.jpg"));
            s.rustyGridArm =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rusty_metal_grid_1k/rusty_metal_grid_arm_1k.jpg"));

            {
                gl::PbrMaterial pbr;
                pbr.baseColorMap = s.rusty04Diff;
                pbr.normalMap = s.rusty04Normal;
                pbr.armMap = s.rusty04Arm; // R=ao, G=roughness, B=metallic
                pbr.hasEnvMap = true;
                pbr.envIntensity = 0.9f;
                s.rusty04Mat = pbr.build(*s.renderResources);
            }

            {
                gl::PbrMaterial pbr;
                pbr.baseColorMap = s.rustyGridDiff;
                pbr.normalMap = s.rustyGridNormal;
                pbr.armMap = s.rustyGridArm; // R=ao, G=roughness, B=metallic
                pbr.hasEnvMap = true;
                pbr.envIntensity = 0.9f;
                s.rustyGridMat = pbr.build(*s.renderResources);
            }

            s.skybox = smp::loadSkybox(s.textureCubeCache, "skyboxes/fjords", true);
            s.path.setSkybox(s.textureCubeCache, s.skybox);

            if (auto* grid = s.path.addOverlay<gl::GridPass>("Grid"))
            {
                grid->setGridSize(1.f);
            }
            else
            {
                std::fprintf(stderr, "pbr-minimal: failed to create Grid overlay\n");
                return;
            }

            if (auto* axes = s.path.addOverlay<gl::AxesPass>("Axes"))
            {
                axes->setAxisLength(100.f);
            }
            else
            {
                std::fprintf(stderr, "pbr-minimal: failed to create Axes overlay\n");
                return;
            }

            s.path.setClearColor(0.07f, 0.08f, 0.11f);
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.orbit.distance = 6.0f;
            s.orbit.elevation = 0.4f;

            s.ready = s.sphereMesh.isValid() && s.rusty04Mat.isValid() && s.rustyGridMat.isValid() &&
                      s.skybox.isValid() && s.renderResources.has_value();
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            Scene& s = *scene;

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;
            gl::Context::current().functions().glViewport(0, 0, safeW, safeH);

            s.path.geometryPass().clearQueue();

            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.rusty04Mat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
                math::mat4Translate(cmd.transform, -1.6f, 0.0f, 0.0f);
                s.path.geometryPass().submit(cmd);
            }

            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.rustyGridMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 11u, 0);
                math::mat4Translate(cmd.transform, 1.6f, 0.0f, 0.0f);
                s.path.geometryPass().submit(cmd);
            }

            gl::FrameData frame;
            frame.camera = s.orbit.toGpuData(0.9f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 300.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.14f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 1.0f;
            frame.directionalLight = dir.toGpuData(kLightDir);

            frame.envMap = s.skybox;
            frame.hasEnvMap = true;

            s.path.render(frame, safeW, safeH);
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
                scene->orbit.orbit(dx, dy);
            }
            if (scene->rightDown)
            {
                scene->orbit.pan(dx, dy);
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
            scene->orbit.zoom(delta);
        });
}
