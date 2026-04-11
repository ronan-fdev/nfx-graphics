#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <numbers>
#include <optional>
#include <vector>

namespace
{
    constexpr bool kImagePlaneDepthTest = true;
    constexpr int kShadowResolution = 2048;
    constexpr float kShadowSceneRadius = 10.0f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 34.0f;
    constexpr float kLightDir[3] = { -0.40f, -0.95f, -0.20f };

    nfx::graphics::gl::Texture2D makeReferenceGridTexture(
        unsigned char br,
        unsigned char bg,
        unsigned char bb,
        unsigned char mr,
        unsigned char mg,
        unsigned char mb,
        unsigned char Majr,
        unsigned char Majg,
        unsigned char Majb)
    {
        constexpr int kW = 640;
        constexpr int kH = 360;
        std::vector<unsigned char> pixels(static_cast<std::size_t>(kW) * static_cast<std::size_t>(kH) * 4u, 255u);

        for (int y = 0; y < kH; ++y)
        {
            for (int x = 0; x < kW; ++x)
            {
                const bool major = (x % 64 == 0) || (y % 64 == 0);
                const bool minor = (x % 16 == 0) || (y % 16 == 0);

                unsigned char r = br;
                unsigned char g = bg;
                unsigned char b = bb;

                if (major)
                {
                    r = Majr;
                    g = Majg;
                    b = Majb;
                }
                else if (minor)
                {
                    r = mr;
                    g = mg;
                    b = mb;
                }

                const std::size_t idx =
                    (static_cast<std::size_t>(y) * static_cast<std::size_t>(kW) + static_cast<std::size_t>(x)) * 4u;
                pixels[idx + 0] = r;
                pixels[idx + 1] = g;
                pixels[idx + 2] = b;
                pixels[idx + 3] = 255;
            }
        }

        return nfx::graphics::gl::Texture2D::fromMemory(
            pixels.data(),
            kW,
            kH,
            { .generateMipmaps = false,
              .minFilter = nfx::graphics::gl::Texture2D::Filter::Linear,
              .magFilter = nfx::graphics::gl::Texture2D::Filter::Linear,
              .wrapS = nfx::graphics::gl::Texture2D::Wrap::ClampToEdge,
              .wrapT = nfx::graphics::gl::Texture2D::Wrap::ClampToEdge,
              .internalFormat = nfx::graphics::gl::Texture2D::InternalFormat::RGBA8 });
    }

} // namespace

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

    gl::MeshHandle sphereHandle;
    gl::MeshHandle cubeHandle;
    gl::MeshHandle torusHandle;
    gl::MeshHandle groundHandle;

    gl::MaterialHandle sphereMat;
    gl::MaterialHandle cubeMat;
    gl::MaterialHandle torusMat;
    gl::MaterialHandle groundMat;

    gl::Texture2DHandle imageHandleBack;
    gl::Texture2DHandle imageHandleSide;

    gl::DirectionalShadowPass* shadowPass = nullptr;

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
        { "nfx-graphics - image-plane", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.sphereHandle = s.meshCache.create(gl::Primitive::uvSphere(24, 36));
            s.cubeHandle = s.meshCache.create(gl::Primitive::cube());
            s.torusHandle = s.meshCache.create(gl::Primitive::torus(0.75f, 0.19f, 36, 24));
            s.groundHandle = s.meshCache.create(gl::Primitive::plane());

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.22f, 0.64f, 0.92f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 32.0f;
                s.sphereMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.94f, 0.82f, 0.24f };
                desc.specularColor = { 0.30f, 0.30f, 0.30f };
                desc.shininess = 20.0f;
                s.cubeMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.90f, 0.42f, 0.58f };
                desc.specularColor = { 0.38f, 0.38f, 0.38f };
                desc.shininess = 30.0f;
                s.torusMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.46f, 0.47f, 0.50f };
                desc.specularColor = { 0.10f, 0.10f, 0.10f };
                desc.shininess = 6.0f;
                desc.hasShadow = true;
                s.groundMat = desc.build(*s.renderResources);
                if (gl::Material* m = s.materialCache.get(s.groundMat))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            s.imageHandleBack = s.texture2DCache.add(makeReferenceGridTexture(24, 30, 44, 74, 94, 140, 166, 196, 255));
            s.imageHandleSide = s.texture2DCache.add(makeReferenceGridTexture(40, 26, 24, 124, 86, 78, 214, 166, 148));

            s.shadowPass = s.path.addShadowPass<gl::DirectionalShadowPass>("SunShadow");
            s.shadowPass->setResolution(s.texture2DCache, kShadowResolution, kShadowResolution);

            s.path.setClearColor(0.07f, 0.08f, 0.11f, 1.0f);
            s.path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.0f);
            if (gl::GridPass* grid = s.path.get<gl::GridPass>("Grid"))
            {
                grid->setFadeDistance(40.0f);
                const float gridColor[3] = { 0.55f, 0.57f, 0.64f };
                grid->setColor(gridColor);
            }
            s.path.addOverlay<gl::AxesPass>("Axes")->setAxisLength(260.0f);

            if (gl::ImagePlanePass* imagePlane = s.path.addOverlay<gl::ImagePlanePass>("ImagePlaneBack"))
            {
                imagePlane->setImage(s.imageHandleBack);
                imagePlane->setOpacity(0.24f);
                imagePlane->setDepthTest(kImagePlaneDepthTest);

                math::Mat4 scale, translate, model;
                math::mat4Scale(scale, 6.8f, 3.8f, 1.0f);
                math::mat4Translate(translate, 0.0f, 2.0f, -3.7f);
                math::mat4Mul(model, translate, scale);
                imagePlane->setTransform(model);
            }

            if (gl::ImagePlanePass* imagePlane = s.path.addOverlay<gl::ImagePlanePass>("ImagePlaneSide"))
            {
                imagePlane->setImage(s.imageHandleSide);
                imagePlane->setOpacity(0.20f);
                imagePlane->setDepthTest(kImagePlaneDepthTest);

                math::Mat4 scale, rotate, translate, rs, model;
                math::mat4Scale(scale, 3.0f, 3.8f, 1.0f);
                math::mat4RotateY(rotate, 0.5f * std::numbers::pi_v<float>);
                math::mat4Mul(rs, rotate, scale);
                math::mat4Translate(translate, -3.8f, 2.0f, 0.0f);
                math::mat4Mul(model, translate, rs);
                imagePlane->setTransform(model);
            }

            s.path.setTonemapEnabled(true);
            s.path.setGammaEnabled(true);
            s.path.initialize(*s.renderResources);

            s.camera.distance = 8.6f;
            s.camera.azimuth = 0.25f;
            s.camera.elevation = 0.50f;
            s.camera.target[1] = 0.95f;

            s.ready = s.sphereHandle.isValid() && s.cubeHandle.isValid() && s.torusHandle.isValid() &&
                      s.groundHandle.isValid() && s.sphereMat.isValid() && s.cubeMat.isValid() &&
                      s.torusMat.isValid() && s.groundMat.isValid() && s.imageHandleBack.isValid() &&
                      s.imageHandleSide.isValid() && s.shadowPass != nullptr &&
                      s.path.get<gl::ImagePlanePass>("ImagePlaneBack") != nullptr &&
                      s.path.get<gl::ImagePlanePass>("ImagePlaneSide") != nullptr;
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
            s.path.geometryPass().clearQueue();

            // Ground
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.groundHandle;
                cmd.material = s.groundMat;
                cmd.sortKey = 1;
                math::Mat4 scale;
                math::mat4Scale(scale, 14.0f, 1.0f, 14.0f);
                cmd.transform = scale;
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Sphere
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.sphereHandle;
                cmd.material = s.sphereMat;
                cmd.sortKey = 10;
                math::Mat4 scale, translate;
                const float bob = 0.82f + 0.10f * std::sin(s.time * 1.8f);
                math::mat4Scale(scale, 0.96f, 0.96f, 0.96f);
                math::mat4Translate(translate, -1.7f, bob, 0.8f);
                math::mat4Mul(cmd.transform, translate, scale);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Cube
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.cubeHandle;
                cmd.material = s.cubeMat;
                cmd.sortKey = 20;
                math::Mat4 scale, rotate, translate, rs;
                math::mat4Scale(scale, 0.9f, 0.9f, 0.9f);
                math::mat4RotateY(rotate, s.time * 0.8f);
                math::mat4Mul(rs, rotate, scale);
                math::mat4Translate(translate, 2.0f, 0.65f, -0.55f);
                math::mat4Mul(cmd.transform, translate, rs);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            // Torus
            {
                gl::RenderCommand cmd;
                cmd.mesh = s.torusHandle;
                cmd.material = s.torusMat;
                cmd.sortKey = 30;
                math::Mat4 rx, ry, tr, rxy;
                math::mat4RotateX(rx, 0.45f);
                math::mat4RotateY(ry, -s.time * 0.55f);
                math::mat4Mul(rxy, ry, rx);
                math::mat4Translate(tr, 0.25f, 1.15f, -0.9f);
                math::mat4Mul(cmd.transform, tr, rxy);
                s.path.geometryPass().submit(cmd);
                s.shadowPass->submit(cmd);
            }

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.11f;

            gl::DirectionalLight dir;
            dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
            dir.intensity = 1.06f;

            gl::FrameData frame;
            frame.camera =
                s.camera.toGpuData(0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 200.0f);
            frame.ambientLight = ambient.toGpuData();
            frame.directionalLight = dir.toGpuData(kLightDir);

            math::Mat4 lightSpaceMat;
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                lightSpaceMat.data(), kLightDir, 0.0f, 0.9f, 0.0f, kShadowSceneRadius, kShadowNear, kShadowFar);
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
