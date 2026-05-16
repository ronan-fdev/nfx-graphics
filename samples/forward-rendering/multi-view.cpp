#include "app/App.h"

#include <nfx/Graphics.h>

#include <optional>
#include <string_view>

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

    gl::ForwardRenderPath path;

    gl::MeshHandle backpackHandle;
    gl::MeshHandle rockHandle;
    gl::MeshHandle planeHandle;

    gl::MaterialHandle backpackMat;
    gl::MaterialHandle rockMat;
    gl::MaterialHandle planeMat;

    gl::OrbitCamera leftCamera;
    gl::OrbitCamera rightCamera;

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
        { "nfx-graphics - multi-view", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            const auto loadObjMesh = [&](const char* embeddedPath) -> gl::MeshHandle {
                const auto* objRes = smp::models::find(embeddedPath);
                if (!objRes)
                {
                    std::fprintf(stderr, "multi-view: embedded object not found: %s\n", embeddedPath);
                    return {};
                }

                const std::string_view objText(
                    reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

                const auto meshData = smp::ObjLoader::fromSource(objText);
                if (!meshData)
                {
                    std::fprintf(stderr, "multi-view: ObjLoader failed for %s\n", embeddedPath);
                    return {};
                }

                return s.meshCache.create(*meshData);
            };

            s.backpackHandle = loadObjMesh("obj/backpack/backpack.obj");
            s.rockHandle = loadObjMesh("obj/rock/rock.obj");
            s.planeHandle = s.meshCache.create(gl::Primitive::plane());

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.texture2DCache.add(smp::loadEmbeddedTexture("obj/backpack/diffuse.jpg", false));
                desc.normalMap = s.texture2DCache.add(smp::loadEmbeddedTexture("obj/backpack/normal.png", false));
                desc.specularMap = s.texture2DCache.add(smp::loadEmbeddedTexture("obj/backpack/specular.jpg", false));
                desc.diffuseColor = { 0.90f, 0.90f, 0.90f };
                desc.specularColor = { 0.45f, 0.45f, 0.46f };
                desc.shininess = 18.0f;
                s.backpackMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", false));
                desc.diffuseColor = { 0.82f, 0.82f, 0.84f };
                desc.specularColor = { 0.12f, 0.12f, 0.14f };
                desc.shininess = 12.0f;
                s.rockMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.texture2DCache.add(
                    smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));
                desc.normalMap =
                    s.texture2DCache.add(smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_nor_gl_1k.jpg"));
                desc.diffuseColor = { 0.85f, 0.85f, 0.86f };
                desc.specularColor = { 0.06f, 0.06f, 0.07f };
                desc.shininess = 6.0f;
                s.planeMat = desc.build(*s.renderResources);
                if (gl::Material* m = s.materialCache.get(s.planeMat))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            s.path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.0f);
            s.path.addOverlay<gl::AxesPass>("Axes")->setAxisLength(100.0f);
            s.path.setClearColor(0.14f, 0.16f, 0.19f);
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.leftCamera.distance = 8.0f;
            s.leftCamera.elevation = 0.48f;
            s.leftCamera.azimuth = -0.40f;
            s.leftCamera.target[0] = -0.15f;
            s.leftCamera.target[1] = 0.60f;
            s.leftCamera.target[2] = 0.10f;

            s.rightCamera.distance = 15.5f;
            s.rightCamera.elevation = 0.92f;
            s.rightCamera.azimuth = 0.78f;
            s.rightCamera.target[0] = -0.15f;
            s.rightCamera.target[1] = 0.60f;
            s.rightCamera.target[2] = 0.10f;

            s.ready = s.backpackHandle.isValid() && s.rockHandle.isValid() && s.planeHandle.isValid() &&
                      s.backpackMat.isValid() && s.rockMat.isValid() && s.planeMat.isValid();
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

            const float dt = s.clock.tick();
            s.angle += 0.35f * dt;

            s.path.geometryPass().clearQueue();

            {
                gl::RenderCommand cmd;
                cmd.mesh = s.backpackHandle;
                cmd.material = s.backpackMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
                math::Mat4 r, sc, t;
                math::mat4RotateY(r, -0.55f);
                math::mat4Scale(sc, 0.92f, 0.92f, 0.92f);
                math::mat4Translate(t, -2.75f, 1.6f, 0.20f);
                math::Mat4 rs;
                math::mat4Mul(rs, r, sc);
                math::mat4Mul(cmd.transform, t, rs);
                s.path.geometryPass().submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.rockHandle;
                cmd.material = s.rockMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 15u, 0);
                math::Mat4 sc, t;
                math::mat4Scale(sc, 0.42f, 0.42f, 0.42f);
                math::mat4Translate(t, -0.25f, 0.46f, 2.15f);
                math::mat4Mul(cmd.transform, t, sc);
                s.path.geometryPass().submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.rockHandle;
                cmd.material = s.rockMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 18u, 0);
                math::Mat4 r, sc, t;
                math::mat4RotateY(r, s.angle * 0.8f + 0.35f);
                math::mat4Scale(sc, 0.58f, 0.58f, 0.58f);
                math::mat4Translate(t, 3.05f, 0.42f, -1.10f);
                math::Mat4 rs;
                math::mat4Mul(rs, r, sc);
                math::mat4Mul(cmd.transform, t, rs);
                s.path.geometryPass().submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.planeHandle;
                cmd.material = s.planeMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 1u, 0);
                math::Mat4 sc, t;
                math::mat4Scale(sc, 14.0f, 1.0f, 14.0f);
                math::mat4Translate(t, 0.00f, -0.001f, 0.0f);
                math::mat4Mul(cmd.transform, t, sc);
                s.path.geometryPass().submit(cmd);
            }

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.12f;

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 1.0f;
            constexpr float kDir[3] = { -0.5f, -0.9f, -0.3f };

            const int halfW = safeW / 2;

            {
                gl::FrameData frame;
                frame.ambientLight = ambient.toGpuData();
                frame.directionalLight = dir.toGpuData(kDir);
                frame.camera =
                    s.leftCamera.toGpuData(0.785f, static_cast<float>(halfW) / static_cast<float>(safeH), 0.1f, 500.0f);

                const gl::ViewportRect vp{ 0, 0, halfW, safeH };
                s.path.render(frame, safeW, safeH, vp);
            }

            {
                gl::FrameData frame;
                frame.ambientLight = ambient.toGpuData();
                frame.directionalLight = dir.toGpuData(kDir);
                frame.camera = s.rightCamera.toGpuData(
                    0.785f, static_cast<float>(safeW - halfW) / static_cast<float>(safeH), 0.1f, 500.0f);

                const gl::ViewportRect vp{ halfW, 0, safeW - halfW, safeH };
                s.path.render(frame, safeW, safeH, vp);
            }
        },

        // onShutdown
        [&] { scene.reset(); },

        // onMouseMove (left view only)
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
                s.leftCamera.orbit(dx, dy);
            }
            if (s.rightDown)
            {
                s.leftCamera.pan(dx, dy);
            }
        },

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

        [&](float delta) {
            if (!scene)
            {
                return;
            }
            scene->leftCamera.zoom(delta);
        });
}
