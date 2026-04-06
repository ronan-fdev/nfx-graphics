#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <array>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kLightDir[3] = { 0.42f, -1.0f, 0.30f };
    constexpr float kColumnSpacing = 2.35f;
    constexpr float kRowSpacing = 2.4f;
    constexpr float kRowY = 0.15f;
    constexpr float kLeftX = -3.525f;
    constexpr float kTopZ = -1.2f;

    struct MaterialSet
    {
        const char* diffuseName;
        const char* normalName;
        const char* armName;
    };

    constexpr std::array<MaterialSet, 4> kMaterialSets = {
        { { "rusty_metal_04_1k/rusty_metal_04_diff_1k.jpg",
            "rusty_metal_04_1k/rusty_metal_04_nor_gl_1k.jpg",
            "rusty_metal_04_1k/rusty_metal_04_arm_1k.jpg" },
          { "rusty_metal_grid_1k/rusty_metal_grid_diff_1k.jpg",
            "rusty_metal_grid_1k/rusty_metal_grid_nor_gl_1k.jpg",
            "rusty_metal_grid_1k/rusty_metal_grid_arm_1k.jpg" },
          { "blue_metal_plate_1k/blue_metal_plate_diff_1k.jpg",
            "blue_metal_plate_1k/blue_metal_plate_nor_gl_1k.jpg",
            "blue_metal_plate_1k/blue_metal_plate_arm_1k.jpg" },
          { "concrete_slab_wall_02_1k/concrete_slab_wall_02_diff_1k.jpg",
            "concrete_slab_wall_02_1k/concrete_slab_wall_02_nor_gl_1k.jpg",
            "concrete_slab_wall_02_1k/concrete_slab_wall_02_arm_1k.jpg" } }
    };
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
    gl::TextureCubeHandle irradianceMap;
    gl::TextureCubeHandle prefilteredEnvMap;
    gl::Texture2DHandle brdfLut;

    std::array<gl::Texture2DHandle, 4> diffuseMaps = {};
    std::array<gl::Texture2DHandle, 4> normalMaps = {};
    std::array<gl::Texture2DHandle, 4> armMaps = {};
    std::array<gl::MaterialHandle, 4> fallbackMaterials = {};
    std::array<gl::MaterialHandle, 4> splitSumMaterials = {};

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
        { "nfx-graphics - pbr-ibl-showcase", 1520, 860, 4, 5 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.sphereMesh = s.meshCache.create(gl::Primitive::uvSphere());
            s.skybox = smp::loadSkybox(s.textureCubeCache, "skyboxes/fjords", true);

            for (std::size_t i = 0; i < kMaterialSets.size(); ++i)
            {
                s.diffuseMaps[i] =
                    s.texture2DCache.add(smp::loadEmbeddedTexture(kMaterialSets[i].diffuseName, true, true));
                s.normalMaps[i] = s.texture2DCache.add(smp::loadEmbeddedTexture(kMaterialSets[i].normalName));
                s.armMaps[i] = s.texture2DCache.add(smp::loadEmbeddedTexture(kMaterialSets[i].armName));

                gl::PbrMaterial fallback;
                fallback.baseColorMap = s.diffuseMaps[i];
                fallback.normalMap = s.normalMaps[i];
                fallback.armMap = s.armMaps[i];
                fallback.hasEnvMap = true;
                fallback.useIblSplitSum = false;
                fallback.envIntensity = 0.95f;
                s.fallbackMaterials[i] = fallback.build(*s.renderResources);

                gl::PbrMaterial splitSum = fallback;
                splitSum.useIblSplitSum = true;
                s.splitSumMaterials[i] = splitSum.build(*s.renderResources);
            }

            if (const gl::TextureCube* env = s.textureCubeCache.get(s.skybox))
            {
                s.irradianceMap = s.textureCubeCache.add(gl::IrradianceMapGenerator{}.generate(*env));
                s.prefilteredEnvMap = s.textureCubeCache.add(gl::PrefilteredEnvGenerator{}.generate(*env));
                s.brdfLut = s.texture2DCache.add(gl::BrdfLutGenerator{}.generate());
            }

            s.path.setSkybox(s.textureCubeCache, s.skybox);
            s.path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.f);
            s.path.addOverlay<gl::AxesPass>("Axes")->setAxisLength(100.f);
            s.path.setClearColor(0.06f, 0.07f, 0.10f);
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.orbit.distance = 10.0f;
            s.orbit.elevation = 0.35f;
            s.orbit.target[1] = 0.5f;

            bool materialsOk = true;
            for (const gl::MaterialHandle handle : s.fallbackMaterials)
            {
                materialsOk = materialsOk && handle.isValid();
            }
            for (const gl::MaterialHandle handle : s.splitSumMaterials)
            {
                materialsOk = materialsOk && handle.isValid();
            }

            s.ready = s.sphereMesh.isValid() && s.skybox.isValid() && s.irradianceMap.isValid() &&
                      s.prefilteredEnvMap.isValid() && s.brdfLut.isValid() && materialsOk;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }
            Scene& s = *scene;

            s.path.geometryPass().clearQueue();

            for (std::size_t col = 0; col < kMaterialSets.size(); ++col)
            {
                const float x = kLeftX + static_cast<float>(col) * kColumnSpacing;

                // Top row: fallback env reflection (simple cubemap lookup)
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = s.sphereMesh;
                    cmd.material = s.fallbackMaterials[col];
                    cmd.sortKey = 100 + static_cast<std::uint32_t>(col);
                    math::mat4Translate(cmd.transform, x, kRowY, kTopZ);
                    s.path.geometryPass().submit(cmd);
                }

                // Bottom row: split-sum IBL (irradiance + prefiltered env + BRDF LUT)
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = s.sphereMesh;
                    cmd.material = s.splitSumMaterials[col];
                    cmd.sortKey = 200 + static_cast<std::uint32_t>(col);
                    math::mat4Translate(cmd.transform, x, kRowY, kTopZ + kRowSpacing);
                    s.path.geometryPass().submit(cmd);
                }
            }

            gl::FrameData frame;
            frame.camera = s.orbit.toGpuData(
                0.9f, static_cast<float>(std::max(width, 1)) / static_cast<float>(std::max(height, 1)), 0.1f, 400.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.12f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 1.0f;
            frame.directionalLight = dir.toGpuData(kLightDir);

            frame.envMap = s.skybox;
            frame.hasEnvMap = true;
            frame.irradianceMap = s.irradianceMap;
            frame.hasIrradianceMap = true;
            frame.prefilteredEnvMap = s.prefilteredEnvMap;
            frame.hasPrefilteredEnvMap = true;
            frame.brdfLut = s.brdfLut;
            frame.hasBrdfLut = true;

            s.path.render(frame, width, height);
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
