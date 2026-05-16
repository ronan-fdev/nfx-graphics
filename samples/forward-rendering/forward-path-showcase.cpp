#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <optional>
#include <string>

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

    constexpr float kHudTextX = 12.0f;
    constexpr float kHudTextY = 34.0f;
    constexpr float kHudUpdatePeriod = 0.1f;
    constexpr float kHudPanelHeight = 350.0f;
} // namespace

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    gl::FontCache fontCache;
    std::optional<gl::RenderResources> renderResources;

    gl::ForwardRenderPath path;

    gl::DirectionalShadowPass* dirShadow = nullptr;
    gl::PointShadowPass* pointShadow = nullptr;
    gl::Polygon2DPass* hudPass = nullptr;
    gl::TextPass* textPass = nullptr;
    gl::FontHandle statsFont;
    gl::TextItemHandle statsTextHandle;
    gl::TextItemHandle statsTextShadowHandle;

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
    float hudUpdateAccum = kHudUpdatePeriod;
    int hudViewportW = 0;
    int hudViewportH = 0;

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

            scene->hudPass = scene->path.addOverlay<gl::Polygon2DPass>("StatsPanel");
            if (!scene->hudPass)
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create Polygon2DPass overlay\n");
                return;
            }

            scene->textPass = scene->path.addOverlay<gl::TextPass>("StatsText");
            if (!scene->textPass)
            {
                std::fprintf(stderr, "forward-path-showcase: failed to create TextPass overlay\n");
                return;
            }
            scene->statsFont = smp::FontLoader::fromEmbedded(
                scene->texture2DCache, scene->fontCache, "JetBrains/mono/JetBrainsMono-Regular.ttf", 32.0f, 32u, 126u);
            if (!scene->statsFont.isValid())
            {
                std::fprintf(stderr, "forward-path-showcase: failed to load font\n");
                return;
            }
            scene->textPass->setFontCache(scene->fontCache);

            // HUD
            gl::TextStyle hudShadowStyle;
            hudShadowStyle.sizePx = 16.0f;
            hudShadowStyle.color[0] = 0.0f;
            hudShadowStyle.color[1] = 0.0f;
            hudShadowStyle.color[2] = 0.0f;
            hudShadowStyle.alpha = 1.0f;

            gl::TextStyle hudStyle;
            hudStyle.sizePx = 16.0f;
            hudStyle.color[0] = 1.0f;
            hudStyle.color[1] = 0.2f;
            hudStyle.color[2] = 0.0f;
            hudStyle.alpha = 1.0f;

            scene->statsTextShadowHandle =
                scene->textPass->addTextUtf8(scene->statsFont, "", kHudTextX + 2.0f, kHudTextY + 2.0f, hudShadowStyle);
            scene->statsTextHandle = scene->textPass->addTextUtf8(scene->statsFont, "", kHudTextX, kHudTextY, hudStyle);

            scene->path.setClearColor(0.08f, 0.09f, 0.12f);
            scene->path.setTonemapEnabled(true);
            scene->path.setGammaEnabled(true);

            scene->path.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 14.0f;
            scene->orbitCamera.elevation = 0.45f;
            scene->orbitCamera.target[1] = 0.5f;
            const bool textReady = scene->textPass != nullptr && scene->statsFont.isValid() &&
                                   scene->statsTextHandle.isValid() && scene->statsTextShadowHandle.isValid();
            scene->ready = scene->sphereHandle.isValid() && scene->cubeHandle.isValid() &&
                           scene->planeHandle.isValid() && scene->opaqueMat.isValid() && scene->groundMat.isValid() &&
                           scene->transpRed.isValid() && scene->transpGreen.isValid() && scene->transpBlue.isValid() &&
                           scene->orbMat.isValid() && scene->dirShadow != nullptr && scene->pointShadow != nullptr &&
                           scene->hudPass != nullptr && textReady;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const float dt = scene->clock.tick();
            scene->time += dt;

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
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 1u, 0);
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
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 10u, 0);
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
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 11u, 0);
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
                cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 5u, 0);
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
                    cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 1u, 0);
                    math::mat4Translate(cmd.transform, 3.0f, 0.0f, -1.5f);
                    wboit->submit(cmd);
                }
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = scene->sphereHandle;
                    cmd.material = scene->transpGreen;
                    cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 2u, 0);
                    math::mat4Translate(cmd.transform, 3.0f, 0.0f, 0.0f);
                    wboit->submit(cmd);
                }
                {
                    gl::RenderCommand cmd;
                    cmd.mesh = scene->sphereHandle;
                    cmd.material = scene->transpBlue;
                    cmd.sortKey = gl::SortKey::packOpaque(gl::SortKey::OpaqueLayer, 0, 3u, 0);
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

            // HUD
            if (scene->hudPass)
            {
                const int safeW = std::max(width, 1);
                const int safeH = std::max(height, 1);
                if (scene->hudViewportW != safeW || scene->hudViewportH != safeH)
                {
                    scene->hudViewportW = safeW;
                    scene->hudViewportH = safeH;

                    scene->hudPass->clear();

                    const float panelX = 6.0f;
                    const float panelY = 8.0f;
                    const float panelW = std::min(static_cast<float>(safeW) - 12.0f, 905.0f);
                    const float panelH = kHudPanelHeight;

                    scene->hudPass->addRect(
                        panelX, panelY, panelW, panelH, gl::Polygon2DStyle{ { 0.0f, 0.0f, 0.0f }, 0.52f });
                    scene->hudPass->addRect(
                        panelX + 1.5f,
                        panelY + 1.5f,
                        panelW - 3.0f,
                        panelH - 3.0f,
                        gl::Polygon2DStyle{ { 0.06f, 0.08f, 0.12f }, 0.30f });
                }
            }

            if (scene->textPass && scene->statsFont.isValid())
            {
                scene->hudUpdateAccum += dt;
                if (scene->hudUpdateAccum < kHudUpdatePeriod)
                {
                    return;
                }
                scene->hudUpdateAccum = 0.0f;

                const auto& frameStats = scene->path.frameStats();
                std::string hudText;
                char tmp[512];

                std::snprintf(
                    tmp,
                    sizeof(tmp),
                    "frame=%lu cpu=%.2fms gpu=%.2fms fps=%.1f\n",
                    static_cast<unsigned long>(frameStats.frameIndex),
                    frameStats.cpuFrameMs,
                    frameStats.gpuFrameMs,
                    frameStats.fps);
                hudText += tmp;

                std::snprintf(
                    tmp,
                    sizeof(tmp),
                    "drawcalls=%u opaque=%u transparent=%u shadow=%u instanced=%u passes=%u\n",
                    frameStats.drawCalls,
                    frameStats.opaqueDraws,
                    frameStats.transparentDraws,
                    frameStats.shadowDraws,
                    frameStats.instancedDraws,
                    frameStats.passesExecuted);
                hudText += tmp;

                std::snprintf(
                    tmp,
                    sizeof(tmp),
                    "commands submitted=%u drawn=%u rejected=%u\n",
                    frameStats.commandsSubmitted,
                    frameStats.commandsDrawn,
                    frameStats.commandsRejected);
                hudText += tmp;

                std::snprintf(
                    tmp,
                    sizeof(tmp),
                    "frustum culling tested=%u culled=%u accepted=%u invalid-bounds=%u\n",
                    frameStats.frustumTested,
                    frameStats.frustumCulled,
                    frameStats.accepted,
                    frameStats.invalidBounds);
                hudText += tmp;

                std::snprintf(
                    tmp,
                    sizeof(tmp),
                    "bindings shaders=%u vao=%u vbo=%u fbo=%u textures=%u shadows=%u\n",
                    frameStats.shaderBinds,
                    frameStats.vaoBinds,
                    frameStats.vboBinds,
                    frameStats.fboBinds,
                    frameStats.textureBinds,
                    frameStats.lightsCastingShadows);
                hudText += tmp;

                if (const auto* dirShadow = scene->path.get<gl::DirectionalShadowPass>("DirShadow"))
                {
                    const auto& s = dirShadow->executionStats();
                    std::snprintf(
                        tmp,
                        sizeof(tmp),
                        "directional shadow submitted=%u drawn=%u invalid=%u | binds vao=%u vbo=%u fbo=%u",
                        s.commandsSubmitted,
                        s.commandsDrawn,
                        s.commandsInvalid,
                        s.vaoBinds,
                        s.vboBinds,
                        s.fboBinds);
                    hudText += tmp;
                }
                hudText += '\n';

                if (const auto* pointShadow = scene->path.get<gl::PointShadowPass>("PointShadow"))
                {
                    const auto& s = pointShadow->executionStats();
                    std::snprintf(
                        tmp,
                        sizeof(tmp),
                        "point shadow submitted=%u drawn=%u invalid=%u | binds vao=%u vbo=%u fbo=%u",
                        s.commandsSubmitted,
                        s.commandsDrawn,
                        s.commandsInvalid,
                        s.vaoBinds,
                        s.vboBinds,
                        s.fboBinds);
                    hudText += tmp;
                }
                hudText += '\n';

                if (const auto* geometry = scene->path.get<gl::GeometryPass>("Geometry"))
                {
                    const auto& culling = geometry->cullingStats();
                    const auto& execution = geometry->executionStats();
                    std::snprintf(
                        tmp,
                        sizeof(tmp),
                        "geometry drawn=%u tested=%u culled=%u invalid=%u | binds shader=%u vao=%u vbo=%u fbo=%u",
                        culling.commandsDrawn,
                        culling.commandsTested,
                        culling.commandsCulled,
                        culling.commandsInvalid,
                        execution.shaderBinds,
                        execution.vaoBinds,
                        execution.vboBinds,
                        execution.fboBinds);
                    hudText += tmp;
                }
                hudText += '\n';

                auto appendRuntimePassStats = [&](const char* label, const gl::PassRuntimeStats& s) {
                    std::snprintf(
                        tmp,
                        sizeof(tmp),
                        "%s draws=%u | binds shader=%u vao=%u vbo=%u fbo=%u texture=%u",
                        label,
                        s.drawCalls,
                        s.shaderBinds,
                        s.vaoBinds,
                        s.vboBinds,
                        s.fboBinds,
                        s.textureBinds);
                    hudText += '\n';
                    hudText += tmp;
                };

                if (const auto* skybox = scene->path.get<gl::SkyboxPass>("Skybox"))
                {
                    appendRuntimePassStats("skybox pass", skybox->runtimeStats());
                }

                if (const auto* environment = scene->path.get<gl::EnvironmentPass>("Environment"))
                {
                    appendRuntimePassStats("environment pass", environment->runtimeStats());
                }

                if (const auto* wboit = scene->path.get<gl::WboitPass>("Transparent"))
                {
                    const auto& s = wboit->executionStats();
                    std::snprintf(
                        tmp,
                        sizeof(tmp),
                        "weighted blended transparency submitted=%u drawn=%u invalid=%u | binds vao=%u vbo=%u fbo=%u "
                        "texture=%u",
                        s.commandsSubmitted,
                        s.commandsDrawn,
                        s.commandsInvalid,
                        s.vaoBinds,
                        s.vboBinds,
                        s.fboBinds,
                        s.textureBinds);
                    hudText += '\n';
                    hudText += tmp;
                }

                if (const auto* grid = scene->path.get<gl::GridPass>("Grid"))
                {
                    appendRuntimePassStats("grid pass", grid->runtimeStats());
                }

                if (const auto* axes = scene->path.get<gl::AxesPass>("Axes"))
                {
                    appendRuntimePassStats("axes pass", axes->runtimeStats());
                }

                if (scene->hudPass)
                {
                    appendRuntimePassStats("stats panel pass", scene->hudPass->runtimeStats());
                }

                if (scene->textPass)
                {
                    appendRuntimePassStats("text pass", scene->textPass->runtimeStats());
                }

                if (const auto* present = scene->path.get<gl::PresentPass>("Present"))
                {
                    appendRuntimePassStats("present pass", present->runtimeStats());
                }

                scene->textPass->updateText(scene->statsTextShadowHandle, hudText);
                scene->textPass->updateText(scene->statsTextHandle, hudText);
            }
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
