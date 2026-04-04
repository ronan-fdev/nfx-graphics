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
    constexpr float kLightIntensity = 1.15f;
    constexpr float kAmbientIntensity = 0.13f;

    constexpr int kShadowRes = 2048;
    constexpr float kShadowRadius = 12.0f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 40.0f;
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
    gl::DirectionalShadowPass* shadowPass = nullptr;
    gl::PointShadowPass* pointShadowPass = nullptr;

    gl::MeshHandle sphereMesh;
    gl::MeshHandle cubeMesh;
    gl::MeshHandle planeMesh;

    // Four material permutations
    gl::MaterialHandle matFlat;    // solid color, no maps, no shadow
    gl::MaterialHandle matDiffuse; // diffuse map only
    gl::MaterialHandle matNormal;  // diffuse + normal map
    gl::MaterialHandle matShadow;  // diffuse + normal + shadow

    gl::MaterialHandle matFloor;  // floor: diffuse + normal + shadow
    gl::MaterialHandle matCube;   // rotating occluder: diffuse + shadow
    gl::MaterialHandle markerMat; // Unlit light-position marker
    gl::MaterialHandle matOrb;    // Unlit orb (orbiting point light)

    gl::Texture2DHandle toyDiffuse;
    gl::Texture2DHandle brickDiffuse;
    gl::Texture2DHandle brickNormal;

    gl::Texture2DHandle terrainDiffuse;
    gl::Texture2DHandle terrainNormal;
    gl::Texture2DHandle terrainRough;

    gl::OrbitCamera orbit;
    smp::Clock clock;
    float time = 0.f;

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
        { "nfx-graphics - material-permutations", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            // Primitives
            s.sphereMesh = s.meshCache.create(gl::Primitive::uvSphere());
            s.cubeMesh = s.meshCache.create(gl::Primitive::cube());
            s.planeMesh = s.meshCache.create(gl::Primitive::plane());

            // Textures
            s.toyDiffuse = s.texture2DCache.add(smp::loadEmbeddedTexture("toybox/toy_box_diffuse.png", true, true));
            s.brickDiffuse = s.texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall.jpg", true, true));
            s.brickNormal = s.texture2DCache.add(smp::loadEmbeddedTexture("brickwall/brickwall_normal.jpg"));

            s.terrainDiffuse = s.texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));
            s.terrainNormal =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_nor_gl_1k.jpg"));
            s.terrainRough =
                s.texture2DCache.add(smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_rough_1k.jpg"));

            // Sphere 1: flat color
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.85f, 0.40f, 0.15f };
                desc.specularColor = { 0.6f, 0.6f, 0.6f };
                desc.shininess = 48.f;
                s.matFlat = desc.build(*s.renderResources);
            }

            // Sphere 2: diffuse map
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.brickDiffuse;
                desc.specularColor = { 0.3f, 0.3f, 0.3f };
                desc.shininess = 24.f;
                s.matDiffuse = desc.build(*s.renderResources);
            }

            // Sphere 3: diffuse + normal
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.brickDiffuse;
                desc.normalMap = s.brickNormal;
                desc.specularColor = { 0.4f, 0.4f, 0.4f };
                desc.shininess = 32.f;
                s.matNormal = desc.build(*s.renderResources);
            }

            // Sphere 4: diffuse + normal + shadow
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.brickDiffuse;
                desc.normalMap = s.brickNormal;
                desc.specularColor = { 0.4f, 0.4f, 0.4f };
                desc.shininess = 32.f;
                desc.hasShadow = true;
                s.matShadow = desc.build(*s.renderResources);
            }

            // Floor
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.terrainDiffuse;
                desc.normalMap = s.terrainNormal;
                desc.specularMap = s.terrainRough;
                desc.specularColor = { 0.25f, 0.25f, 0.25f };
                desc.shininess = 12.f;
                desc.hasShadow = true;
                s.matFloor = desc.build(*s.renderResources);
                if (gl::Material* m = s.materialCache.get(s.matFloor))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            // Rotating occluder cube
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseMap = s.toyDiffuse;
                desc.specularColor = { 0.3f, 0.3f, 0.3f };
                desc.shininess = 16.f;
                desc.hasShadow = true;
                s.matCube = desc.build(*s.renderResources);
            }

            // Unlit marker (light position)
            {
                gl::UnlitMaterial desc;
                desc.color = { 1.5f, 1.4f, 0.9f };
                s.markerMat = desc.build(s.shaderCache, s.materialCache);
            }

            // Unlit orb
            {
                gl::UnlitMaterial desc;
                desc.color = { 2.0f, 0.85f, 0.25f };
                s.matOrb = desc.build(s.shaderCache, s.materialCache);
            }

            // ForwardRenderPath configuration
            s.shadowPass = s.path.addShadowPass<gl::DirectionalShadowPass>("Shadow");
            if (!s.shadowPass)
            {
                std::fprintf(stderr, "material-permutations: failed to create Shadow pass\n");
                return;
            }
            s.shadowPass->setResolution(s.texture2DCache, kShadowRes, kShadowRes);

            s.pointShadowPass = s.path.addShadowPass<gl::PointShadowPass>("PointShadow");
            if (!s.pointShadowPass)
            {
                std::fprintf(stderr, "material-permutations: failed to create PointShadow pass\n");
                return;
            }
            s.pointShadowPass->setResolution(s.textureCubeCache, 512);

            if (auto* grid = s.path.addOverlay<gl::GridPass>("Grid"))
            {
                grid->setGridSize(1.f);
                grid->setFadeDistance(60.f);
            }
            else
            {
                std::fprintf(stderr, "material-permutations: failed to create Grid overlay\n");
                return;
            }

            if (auto* axes = s.path.addOverlay<gl::AxesPass>("Axes"))
            {
                axes->setAxisLength(300.f);
                axes->setFadeDistance(60.f);
            }
            else
            {
                std::fprintf(stderr, "material-permutations: failed to create Axes overlay\n");
                return;
            }

            s.path.setClearColor(0.08f, 0.09f, 0.12f);
            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);

            s.path.initialize(*s.renderResources);

            s.orbit.distance = 16.f;
            s.orbit.elevation = 0.45f;
            s.orbit.target[1] = 0.5f;

            s.ready = s.sphereMesh.isValid() && s.cubeMesh.isValid() && s.planeMesh.isValid() && s.matFlat.isValid() &&
                      s.matDiffuse.isValid() && s.matNormal.isValid() && s.matShadow.isValid() &&
                      s.matFloor.isValid() && s.matCube.isValid() && s.markerMat.isValid() &&
                      s.terrainDiffuse.isValid() && s.shadowPass && s.pointShadowPass;
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }
            Scene& s = *scene;

            const int W = width > 0 ? width : 1;
            const int H = height > 0 ? height : 1;

            s.time += s.clock.tick();

            // Build light-space matrix
            float dirLS[16];
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                dirLS, kLightDir, 0.f, 0.f, 0.f, kShadowRadius, kShadowNear, kShadowFar);
            s.shadowPass->setLightSpaceMatrix(dirLS);

            const float orbA = s.time * 0.65f;
            const float orbX = std::cos(orbA) * 3.5f;
            const float orbZ = std::sin(orbA) * 3.5f;
            constexpr float orbY = 1.2f;
            const gl::PointLight orb =
                gl::PointLight::create(orbX, orbY, orbZ, 1.0f, 0.55f, 0.12f, 8.5f, 4.5f, 6.0f, 0.05f);
            s.pointShadowPass->addLight(orb);

            // Submit geometry
            s.path.geometryPass().clearQueue();

            // Floor
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.planeMesh;
                cmd.material = s.matFloor;
                cmd.sortKey = 1;
                math::Mat4 scale, tr;
                math::mat4Scale(scale, 16.f, 1.f, 10.f);
                math::mat4Translate(tr, 0.f, -1.f, 0.f);
                math::mat4Mul(cmd.transform, tr, scale);
                s.path.geometryPass().submit(cmd);
            }

            // Rotating occluder cube (casts a shadow on sphere 4 and the floor)
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.cubeMesh;
                cmd.material = s.matCube;
                cmd.sortKey = 10;
                math::Mat4 rot, tr;
                math::mat4RotateY(rot, s.time * 0.9f);
                math::mat4Translate(tr, 4.5f, 2.2f, 0.0f);
                math::mat4Mul(cmd.transform, tr, rot);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Sphere 1: flat color
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.matFlat;
                cmd.sortKey = 20;
                math::mat4Translate(cmd.transform, -4.5f, 0.f, 0.f);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Sphere 2: diffuse map
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.matDiffuse;
                cmd.sortKey = 21;
                math::mat4Translate(cmd.transform, -1.5f, 0.f, 0.f);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Sphere 3: diffuse + normal map
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.matNormal;
                cmd.sortKey = 22;
                math::mat4Translate(cmd.transform, 1.5f, 0.f, 0.f);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Sphere 4: diffuse + normal + shadow
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.matShadow;
                cmd.sortKey = 23;
                math::mat4Translate(cmd.transform, 4.5f, 0.f, 0.f);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Orb sphere (orbiting point light visual)
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.matOrb;
                cmd.sortKey = 4;
                math::Mat4 scale, tr;
                math::mat4Scale(scale, 0.18f, 0.18f, 0.18f);
                math::mat4Translate(tr, orbX, orbY, orbZ);
                math::mat4Mul(cmd.transform, tr, scale);
                s.path.geometryPass().submit(cmd);
            }

            // Point shadow casters
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.cubeMesh;
                math::Mat4 rot, tr;
                math::mat4RotateY(rot, s.time * 0.9f);
                math::mat4Translate(tr, 4.5f, 2.2f, 0.0f);
                math::mat4Mul(cmd.transform, tr, rot);
                s.pointShadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                math::mat4Translate(cmd.transform, -4.5f, 0.f, 0.f);
                s.pointShadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                math::mat4Translate(cmd.transform, -1.5f, 0.f, 0.f);
                s.pointShadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                math::mat4Translate(cmd.transform, 1.5f, 0.f, 0.f);
                s.pointShadowPass->submit(cmd);
            }
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                math::mat4Translate(cmd.transform, 4.5f, -0.6f, 0.f);
                s.pointShadowPass->submit(cmd);
            }

            // Unlit marker at approximate light origin
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereMesh;
                cmd.material = s.markerMat;
                cmd.sortKey = 5;
                const float d = kShadowRadius + kShadowNear;
                const float mx = -kLightDir[0] * d;
                const float my = -kLightDir[1] * d;
                const float mz = -kLightDir[2] * d;
                math::Mat4 scale, tr;
                math::mat4Scale(scale, 0.18f, 0.18f, 0.18f);
                math::mat4Translate(tr, mx, my, mz);
                math::mat4Mul(cmd.transform, tr, scale);
                s.path.geometryPass().submit(cmd);
            }

            // Frame data
            gl::FrameData frame;
            frame.camera = s.orbit.toGpuData(0.9f, static_cast<float>(W) / static_cast<float>(H), 0.1f, 500.f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.f;
            ambient.intensity = kAmbientIntensity;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.f;
            dir.intensity = kLightIntensity;
            frame.directionalLight = dir.toGpuData(kLightDir);

            frame.hasDirShadow = true;
            frame.dirShadowMap = s.shadowPass->shadowMap();

            frame.pointShadowCount = 1;
            frame.pointShadowMaps[0] = s.pointShadowPass->shadowMaps()[0];

            frame.lights.clear();
            frame.lights.push_back(orb.toGpuData());

            s.path.render(frame, W, H);
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
                s.orbit.orbit(dx, dy);
            }
            if (s.rightDown)
            {
                s.orbit.pan(dx, dy);
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
