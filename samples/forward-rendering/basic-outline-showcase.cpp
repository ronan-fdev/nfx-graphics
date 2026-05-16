#include "app/App.h"

#include <nfx/Graphics.h>

#include <embedded_objects.h>

#include <cmath>
#include <cstdio>
#include <limits>
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

    gl::ForwardRenderPath path;

    gl::MeshHandle rockHandle;
    gl::MeshHandle torusHandle;
    gl::MeshHandle sphereHandle;

    gl::MaterialHandle rockMat;
    gl::MaterialHandle torusMat;
    gl::MaterialHandle sphereMat;

    enum class Selected
    {
        None,
        Rock,
        Torus,
        Sphere
    };

    Selected selected = Selected::None;
    bool pickRequested = false;
    int pickMouseX = 0;
    int pickMouseY = 0;

    gl::OrbitCamera camera;
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
        { "nfx-graphics - basic-outline-showcase", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.torusHandle = s.meshCache.create(gl::Primitive::torus(0.8f, 0.22f, 40, 24));
            s.sphereHandle = s.meshCache.create(gl::Primitive::uvSphere(28, 40));

            const auto* rockRes = smp::models::find("obj/rock/rock.obj");
            if (rockRes)
            {
                const std::string_view objText(
                    reinterpret_cast<const char*>(rockRes->data), static_cast<std::size_t>(rockRes->size));
                if (const auto meshData = smp::ObjLoader::fromSource(objText))
                {
                    s.rockHandle = s.meshCache.create(*meshData);
                }
                else
                {
                    std::fprintf(stderr, "outline-showcase: ObjLoader failed for rock.obj\n");
                }
            }
            else
            {
                std::fprintf(stderr, "outline-showcase: embedded object not found: obj/rock/rock.obj\n");
            }

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.82f, 0.72f, 0.60f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 24.0f;
                s.rockMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.20f, 0.65f, 0.95f };
                desc.specularColor = { 0.45f, 0.45f, 0.45f };
                desc.shininess = 36.0f;
                s.torusMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.95f, 0.75f, 0.22f };
                desc.specularColor = { 0.40f, 0.40f, 0.40f };
                desc.shininess = 28.0f;
                s.sphereMat = desc.build(*s.renderResources);
            }

            s.path.setClearColor(0.02f, 0.02f, 0.02f, 1.0f);
            s.path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.0f);
            if (auto* grid = s.path.get<gl::GridPass>("Grid"))
            {
                grid->setFadeDistance(40.0f);
            }

            s.path.addOverlay<gl::AxesPass>("Axes")->setAxisLength(10000.0f);
            if (auto* axes = s.path.get<gl::AxesPass>("Axes"))
            {
                axes->setFadeDistance(40.0f);
            }

            const float outlineColor[3] = { 1.0f, 0.35f, 0.15f };
            s.path.enableOutline(outlineColor, 2.0f);
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.camera.distance = 10.0f;
            s.camera.elevation = 0.50f;
            s.camera.target[1] = 0.4f;

            s.ready = s.path.outlinePass() && s.torusHandle.isValid() && s.sphereHandle.isValid() &&
                      s.rockHandle.isValid() && s.rockMat.isValid() && s.torusMat.isValid() && s.sphereMat.isValid();
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

            s.time += s.clock.tick();

            const gl::Camera::GpuData cam =
                s.camera.toGpuData(0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 120.0f);

            if (s.pickRequested)
            {
                s.pickRequested = false;

                const float screenPos[2] = { static_cast<float>(s.pickMouseX), static_cast<float>(s.pickMouseY) };
                const float viewportSize[2] = { static_cast<float>(safeW), static_cast<float>(safeH) };
                const math::Ray ray = math::screenToWorldRay(screenPos, viewportSize, cam.view, cam.proj);

                s.selected = Scene::Selected::None;
                float best = std::numeric_limits<float>::max();

                // Rock bounds
                {
                    math::Bounds::AABB aabb;
                    aabb.min[0] = -2.2f - 0.65f;
                    aabb.min[1] = 0.0f;
                    aabb.min[2] = -0.65f;
                    aabb.max[0] = -2.2f + 0.65f;
                    aabb.max[1] = 0.75f + 1.1f;
                    aabb.max[2] = 0.65f;
                    if (const auto hit = math::intersect(ray, aabb);
                        hit && hit->distance >= 0.0f && hit->distance < best)
                    {
                        best = hit->distance;
                        s.selected = Scene::Selected::Rock;
                    }
                }

                // Torus bounds
                {
                    constexpr float kTorusCenterY = 1.0f;
                    constexpr float kMajorRadius = 0.8f;
                    constexpr float kMinorRadius = 0.22f;
                    constexpr float kOuterRadius = kMajorRadius + kMinorRadius;

                    const math::Bounds::Sphere outer{ { 0.0f, kTorusCenterY, 0.0f }, kOuterRadius };
                    const auto hitOuter = math::intersect(ray, outer);

                    if (hitOuter && hitOuter->distance >= 0.0f && hitOuter->distance < best)
                    {
                        auto torusSdfAt = [&](float t) -> float {
                            const float px = ray.origin[0] + t * ray.direction[0];
                            const float py = ray.origin[1] + t * ray.direction[1] - kTorusCenterY;
                            const float pz = ray.origin[2] + t * ray.direction[2];
                            const float radial = std::sqrt(px * px + pz * pz);
                            const float qx = radial - kMajorRadius;
                            const float qy = py;
                            return std::sqrt(qx * qx + qy * qy) - kMinorRadius;
                        };

                        const float tStart = (hitOuter->distance > 0.6f) ? (hitOuter->distance - 0.6f) : 0.0f;
                        const float tEnd = ((hitOuter->distance + 2.2f) < best) ? (hitOuter->distance + 2.2f) : best;

                        constexpr float kStep = 0.01f;
                        float prevT = tStart;
                        float prevSdf = torusSdfAt(prevT);

                        bool found = false;
                        float hitT = 0.0f;

                        for (int stepIdx = 1; (prevT + stepIdx * kStep) <= tEnd; ++stepIdx)
                        {
                            const float t = prevT + stepIdx * kStep;
                            const float sdf = torusSdfAt(t);
                            if (prevSdf > 0.0f && sdf <= 0.0f)
                            {
                                float lo = prevT;
                                float hi = t;
                                for (int i = 0; i < 12; ++i)
                                {
                                    const float mid = 0.5f * (lo + hi);
                                    const float msdf = torusSdfAt(mid);
                                    if (msdf <= 0.0f)
                                    {
                                        hi = mid;
                                    }
                                    else
                                    {
                                        lo = mid;
                                    }
                                }
                                hitT = hi;
                                found = true;
                                break;
                            }
                            prevT = t;
                            prevSdf = sdf;
                        }

                        if (found && hitT >= 0.0f && hitT < best)
                        {
                            best = hitT;
                            s.selected = Scene::Selected::Torus;
                        }
                    }
                }

                // Sphere bounds
                {
                    const math::Bounds::Sphere sphere{ { 2.5f, 1.0f, 0.0f }, 0.8f };
                    if (const auto hit = math::intersect(ray, sphere);
                        hit && hit->distance >= 0.0f && hit->distance < best)
                    {
                        best = hit->distance;
                        s.selected = Scene::Selected::Sphere;
                    }
                }
            }

            s.path.geometryPass().clearQueue();
            if (gl::OutlinePass* outline = s.path.outlinePass())
            {
                outline->clearQueue();
            }

            // Rock
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.rockHandle;
                cmd.material = s.rockMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
                math::Mat4 sc, tr;
                math::mat4Scale(sc, 0.7f, 0.7f, 0.7f);
                math::mat4Translate(tr, -2.2f, 0.75f, 0.0f);
                math::mat4Mul(cmd.transform, tr, sc);
                s.path.geometryPass().submit(cmd);
                if (s.selected == Scene::Selected::Rock)
                {
                    if (gl::OutlinePass* outline = s.path.outlinePass())
                    {
                        outline->submit(cmd);
                    }
                }
            }

            // Torus
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.torusHandle;
                cmd.material = s.torusMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 20u, 0);
                math::Mat4 r, t;
                math::mat4RotateY(r, s.time * 0.8f);
                math::mat4Translate(t, 0.0f, 1.0f, 0.0f);
                math::mat4Mul(cmd.transform, t, r);
                s.path.geometryPass().submit(cmd);
                if (s.selected == Scene::Selected::Torus)
                {
                    if (gl::OutlinePass* outline = s.path.outlinePass())
                    {
                        outline->submit(cmd);
                    }
                }
            }

            // Sphere
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereHandle;
                cmd.material = s.sphereMat;
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 30u, 0);
                math::Mat4 sc, tr;
                math::mat4Scale(sc, 0.8f, 0.8f, 0.8f);
                math::mat4Translate(tr, 2.5f, 1.0f, 0.0f);
                math::mat4Mul(cmd.transform, tr, sc);
                s.path.geometryPass().submit(cmd);
                if (s.selected == Scene::Selected::Sphere)
                {
                    if (gl::OutlinePass* outline = s.path.outlinePass())
                    {
                        outline->submit(cmd);
                    }
                }
            }

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.14f;

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 0.9f;
            constexpr float kDir[3] = { -0.45f, -0.85f, -0.25f };

            gl::FrameData frame;
            frame.camera = cam;
            frame.ambientLight = ambient.toGpuData();
            frame.directionalLight = dir.toGpuData(kDir);

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

            if (button == 1 && pressed && scene->hasMouse)
            {
                scene->pickRequested = true;
                scene->pickMouseX = scene->lastMouseX;
                scene->pickMouseY = scene->lastMouseY;
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
