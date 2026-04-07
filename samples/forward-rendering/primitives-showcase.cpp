#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <array>
#include <numbers>
#include <optional>

namespace
{
    constexpr int kShadowResolution = 2048;
    constexpr float kShadowSceneRadius = 6.5f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 30.0f;
    constexpr float kLightDir[3] = { -0.45f, -1.0f, -0.25f };
} // namespace

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

struct PrimitiveItem
{
    gl::MeshHandle mesh;
    gl::MaterialHandle material;
    float position[3] = { 0.0f, 0.0f, 0.0f };
    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float spinSpeed = 0.0f;
    std::uint64_t sortKey = 10;
};

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
    gl::OrbitCamera camera;

    gl::MeshHandle planeHandle;
    gl::MaterialHandle planeMat;

    std::array<PrimitiveItem, 12> items;

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
        { "nfx-graphics - primitives-showcase", 1440, 900, 4, 2 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            // Meshes
            s.planeHandle = s.meshCache.create(gl::Primitive::plane());

            s.items[0].mesh = s.meshCache.create(gl::Primitive::cube());
            s.items[1].mesh = s.meshCache.create(gl::Primitive::uvSphere(26, 40));
            s.items[2].mesh = s.meshCache.create(gl::Primitive::icosphere(2));
            s.items[3].mesh = s.meshCache.create(gl::Primitive::cylinder(0.45f, 1.2f, 32, 2));
            s.items[4].mesh = s.meshCache.create(gl::Primitive::cone(0.5f, 1.2f, 32, 2));
            s.items[5].mesh = s.meshCache.create(gl::Primitive::capsule(0.35f, 0.9f, 32, 8));
            s.items[6].mesh = s.meshCache.create(gl::Primitive::disk(0.6f, 48));
            s.items[7].mesh = s.meshCache.create(gl::Primitive::pyramid(0.5f, 1.2f));
            s.items[8].mesh = s.meshCache.create(gl::Primitive::tube(0.45f, 1.2f, 32, 2));
            s.items[9].mesh = s.meshCache.create(gl::Primitive::torus(0.5f, 0.17f, 32, 20));
            s.items[10].mesh = s.meshCache.create(gl::Primitive::tetrahedron(0.55f, 1.2f));
            s.items[11].mesh = s.meshCache.create(gl::Primitive::pipe(0.45f, 0.40f, 1.2f, 32, 2));

            // Materials
            // clang-format off
            const float colors[12][3] = {
                { 0.91f, 0.34f, 0.27f },
                { 0.95f, 0.70f, 0.23f },
                { 0.32f, 0.78f, 0.39f },
                { 0.18f, 0.72f, 0.82f },
                { 0.25f, 0.48f, 0.88f },
                { 0.52f, 0.36f, 0.84f },
                { 0.82f, 0.30f, 0.62f },
                { 0.86f, 0.46f, 0.30f },
                { 0.48f, 0.80f, 0.62f },
                { 0.30f, 0.65f, 0.92f },
                { 0.93f, 0.86f, 0.34f },
                { 0.85f, 0.45f, 0.25f }
            };
            // clang-format on

            for (std::size_t i = 0; i < s.items.size(); ++i)
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { colors[i][0], colors[i][1], colors[i][2] };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 28.0f;
                desc.hasShadow = true;
                s.items[i].material = desc.build(*s.renderResources);
                s.items[i].sortKey = static_cast<std::uint64_t>(10 + i);
            }

            // Disk and tube are intentionally double-sided in this showcase
            for (std::size_t idx : { std::size_t(6), std::size_t(8) })
            {
                if (gl::Material* m = s.materialCache.get(s.items[idx].material))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.32f, 0.33f, 0.36f };
                desc.specularColor = { 0.10f, 0.10f, 0.10f };
                desc.shininess = 6.0f;
                desc.hasShadow = true;
                s.planeMat = desc.build(*s.renderResources);
                if (gl::Material* m = s.materialCache.get(s.planeMat))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            // Placement (ring + center)
            constexpr float kRingRadius = 4.5f;
            for (std::size_t i = 0; i < 11; ++i)
            {
                const float a = (2.0f * std::numbers::pi_v<float> * static_cast<float>(i)) / 11.0f;
                s.items[i].position[0] = std::cos(a) * kRingRadius;
                s.items[i].position[1] = 0.05f;
                s.items[i].position[2] = std::sin(a) * kRingRadius;
                s.items[i].spinSpeed = 0.25f + 0.07f * static_cast<float>(i);
            }
            s.items[11].position[1] = 0.95f;
            s.items[11].spinSpeed = -0.35f;

            s.shadowPass = s.path.addShadowPass<gl::DirectionalShadowPass>("Shadow");
            s.shadowPass->setResolution(s.texture2DCache, kShadowResolution, kShadowResolution);

            s.path.setClearColor(0.07f, 0.08f, 0.10f, 1.0f);
            s.path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.0f);
            if (auto* grid = s.path.get<gl::GridPass>("Grid"))
            {
                grid->setFadeDistance(50.0f);
            }
            s.path.addOverlay<gl::AxesPass>("Axes")->setAxisLength(800.0f);
            if (auto* axes = s.path.get<gl::AxesPass>("Axes"))
            {
                axes->setFadeDistance(50.0f);
            }
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.camera.distance = 11.5f;
            s.camera.elevation = 0.58f;
            s.camera.target[1] = 0.5f;

            s.ready = s.planeHandle.isValid() && s.planeMat.isValid() && s.shadowPass != nullptr;
            for (const auto& item : s.items)
            {
                s.ready = s.ready && item.mesh.isValid() && item.material.isValid();
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }
            Scene& s = *scene;

            const int safeW = std::max(width, 1);
            const int safeH = std::max(height, 1);

            s.time += s.clock.tick();
            s.path.geometryPass().clearQueue();

            // Ground
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.planeHandle;
                cmd.material = s.planeMat;
                cmd.sortKey = 1;
                math::Mat4 sc, tr;
                math::mat4Scale(sc, 20.0f, 1.0f, 20.0f);
                math::mat4Translate(tr, 0.0f, -1.0f, 0.0f);
                math::mat4Mul(cmd.transform, tr, sc);
                s.path.geometryPass().submit(cmd);
            }

            // Primitives
            for (const auto& item : s.items)
            {
                gl::RenderCommand cmd;
                cmd.mesh = item.mesh;
                cmd.material = item.material;
                cmd.sortKey = item.sortKey;

                math::Mat4 sc, ry, tr, rs;
                math::mat4Scale(sc, item.scale[0], item.scale[1], item.scale[2]);
                math::mat4RotateY(ry, s.time * item.spinSpeed);
                math::mat4Mul(rs, ry, sc);
                math::mat4Translate(tr, item.position[0], item.position[1], item.position[2]);
                math::mat4Mul(cmd.transform, tr, rs);

                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            gl::FrameData frame;
            frame.camera =
                s.camera.toGpuData(0.85f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 250.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.18f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 0.95f;
            frame.directionalLight = dir.toGpuData(kLightDir);

            math::Mat4 lightSpaceMat;
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                lightSpaceMat.data(), kLightDir, 0.0f, 0.0f, 0.0f, kShadowSceneRadius, kShadowNear, kShadowFar);
            s.shadowPass->setLightSpaceMatrix(lightSpaceMat.data());
            frame.hasDirShadow = true;
            frame.dirShadowMap = s.shadowPass->shadowMap();

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
            Scene& s = *scene;
            if (!s.hasMouse)
            {
                s.lastMouseX = x;
                s.lastMouseY = y;
                s.hasMouse = true;
                return;
            }

            const float dx = static_cast<float>(x - s.lastMouseX);
            const float dy = static_cast<float>(y - s.lastMouseY);
            s.lastMouseX = x;
            s.lastMouseY = y;

            if (s.middleDown)
            {
                s.camera.orbit(dx, dy);
            }
            if (s.rightDown)
            {
                s.camera.pan(dx, dy);
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
            scene->camera.zoom(delta);
        });
}
