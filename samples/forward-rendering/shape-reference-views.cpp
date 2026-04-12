#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <numbers>
#include <optional>
#include <vector>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    gl::Texture2D makeReferenceGridTexture(
        unsigned char br,
        unsigned char bg,
        unsigned char bb,
        unsigned char mr,
        unsigned char mg,
        unsigned char mb,
        unsigned char majr,
        unsigned char majg,
        unsigned char majb)
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
                    r = majr;
                    g = majg;
                    b = majb;
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

        return gl::Texture2D::fromMemory(
            pixels.data(),
            kW,
            kH,
            { .generateMipmaps = false,
              .minFilter = gl::Texture2D::Filter::Linear,
              .magFilter = gl::Texture2D::Filter::Linear,
              .wrapS = gl::Texture2D::Wrap::ClampToEdge,
              .wrapT = gl::Texture2D::Wrap::ClampToEdge,
              .internalFormat = gl::Texture2D::InternalFormat::RGBA8 });
    }

    void submitHullProxy(
        gl::GeometryPass& geometryPass,
        gl::MeshHandle hullHandle,
        gl::MeshHandle cabinHandle,
        gl::MeshHandle groundHandle,
        gl::MaterialHandle hullMat,
        gl::MaterialHandle cabinMat,
        gl::MaterialHandle groundMat)
    {
        geometryPass.clearQueue();

        {
            gl::RenderCommand cmd;
            cmd.mesh = groundHandle;
            cmd.material = groundMat;
            cmd.sortKey = 1;
            math::Mat4 scale;
            math::mat4Scale(scale, 18.0f, 1.0f, 12.0f);
            cmd.transform = scale;
            geometryPass.submit(cmd);
        }

        {
            gl::RenderCommand cmd;
            cmd.mesh = hullHandle;
            cmd.material = hullMat;
            cmd.sortKey = 10;
            math::Mat4 scale, rotate, translate, rs;
            math::mat4Scale(scale, 1.45f, 1.0f, 1.0f);
            math::mat4RotateZ(rotate, -0.5f * std::numbers::pi_v<float>);
            math::mat4Mul(rs, rotate, scale);
            math::mat4Translate(translate, 0.0f, 1.10f, 0.0f);
            math::mat4Mul(cmd.transform, translate, rs);
            geometryPass.submit(cmd);
        }

        {
            gl::RenderCommand cmd;
            cmd.mesh = cabinHandle;
            cmd.material = cabinMat;
            cmd.sortKey = 20;
            math::Mat4 scale, translate;
            math::mat4Scale(scale, 0.90f, 0.65f, 0.75f);
            math::mat4Translate(translate, 0.95f, 1.75f, 0.0f);
            math::mat4Mul(cmd.transform, translate, scale);
            geometryPass.submit(cmd);
        }
    }

    gl::FrameData makeFrameData(const gl::OrbitCamera& camera, float fovY, float aspect)
    {
        gl::AmbientLight ambient;
        ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
        ambient.intensity = 0.10f;

        gl::DirectionalLight dir;
        dir.color[0] = dir.color[1] = dir.color[2] = 1.0f;
        dir.intensity = 1.05f;
        constexpr float kDir[3] = { -0.45f, -0.90f, -0.25f };

        gl::FrameData frame;
        frame.camera = camera.toGpuData(fovY, aspect, 0.1f, 400.0f);
        frame.ambientLight = ambient.toGpuData();
        frame.directionalLight = dir.toGpuData(kDir);
        return frame;
    }
} // namespace

struct Scene
{
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::ShaderCache shaderCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    std::optional<gl::RenderResources> renderResources;

    gl::ForwardRenderPath frontPath;
    gl::ForwardRenderPath sidePath;

    gl::MeshHandle hullHandle;
    gl::MeshHandle cabinHandle;
    gl::MeshHandle groundHandle;

    gl::MaterialHandle hullMat;
    gl::MaterialHandle cabinMat;
    gl::MaterialHandle groundMat;

    gl::Texture2DHandle frontReference;
    gl::Texture2DHandle sideReference;

    gl::OrbitCamera frontCamera;
    gl::OrbitCamera sideCamera;

    int lastMouseX = 0;
    int lastMouseY = 0;
    int surfaceWidth = 1;
    int activeView = 0;
    bool hasMouse = false;
    bool panDown = false;
    bool ready = false;
};

static gl::OrbitCamera& activeCamera(Scene& s, int x)
{
    return (x < (s.surfaceWidth / 2)) ? s.frontCamera : s.sideCamera;
}

static gl::OrbitCamera& activeCamera(Scene& s)
{
    return (s.activeView == 0) ? s.frontCamera : s.sideCamera;
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - shape-reference-views", 1440, 810, 4, 2 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.hullHandle = s.meshCache.create(gl::Primitive::capsule(0.50f, 4.4f, 36, 12));
            s.cabinHandle = s.meshCache.create(gl::Primitive::cube());
            s.groundHandle = s.meshCache.create(gl::Primitive::plane());

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.22f, 0.62f, 0.88f };
                desc.specularColor = { 0.30f, 0.30f, 0.30f };
                desc.shininess = 24.0f;
                s.hullMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.92f, 0.78f, 0.24f };
                desc.specularColor = { 0.22f, 0.22f, 0.22f };
                desc.shininess = 18.0f;
                s.cabinMat = desc.build(*s.renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.44f, 0.45f, 0.49f };
                desc.specularColor = { 0.08f, 0.08f, 0.08f };
                desc.shininess = 5.0f;
                s.groundMat = desc.build(*s.renderResources);
                if (gl::Material* m = s.materialCache.get(s.groundMat))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            s.frontReference = s.texture2DCache.add(makeReferenceGridTexture(24, 30, 44, 74, 94, 140, 166, 196, 255));
            s.sideReference = s.texture2DCache.add(makeReferenceGridTexture(42, 26, 22, 120, 76, 64, 208, 150, 120));

            auto configurePath = [&](gl::ForwardRenderPath& path) {
                path.setClearColor(0.07f, 0.08f, 0.11f, 1.0f);
                path.setTonemapEnabled(true);
                path.setGammaEnabled(true);
                path.addOverlay<gl::GridPass>("Grid")->setGridSize(1.0f);
            };

            configurePath(s.frontPath);
            configurePath(s.sidePath);

            bool frontImagePlaneReady = false;
            if (gl::ImagePlanePass* imagePlane = s.frontPath.addOverlay<gl::ImagePlanePass>("FrontReference"))
            {
                imagePlane->setImage(s.frontReference);
                imagePlane->setOpacity(0.24f);
                imagePlane->setDepthTest(true);

                math::Mat4 scale, translate, model;
                math::mat4Scale(scale, 7.4f, 4.2f, 1.0f);
                math::mat4Translate(translate, 0.0f, 2.0f, -4.0f);
                math::mat4Mul(model, translate, scale);
                imagePlane->setTransform(model);
                frontImagePlaneReady = true;
            }

            bool sideImagePlaneReady = false;
            if (gl::ImagePlanePass* imagePlane = s.sidePath.addOverlay<gl::ImagePlanePass>("SideReference"))
            {
                imagePlane->setImage(s.sideReference);
                imagePlane->setOpacity(0.22f);
                imagePlane->setDepthTest(true);

                math::Mat4 scale, rotate, translate, rs, model;
                math::mat4Scale(scale, 3.8f, 4.2f, 1.0f);
                math::mat4RotateY(rotate, 0.5f * std::numbers::pi_v<float>);
                math::mat4Mul(rs, rotate, scale);
                math::mat4Translate(translate, -4.4f, 2.0f, 0.0f);
                math::mat4Mul(model, translate, rs);
                imagePlane->setTransform(model);
                sideImagePlaneReady = true;
            }

            s.frontPath.initialize(*s.renderResources);
            s.sidePath.initialize(*s.renderResources);

            // Front view: along -Z, low FOV to behave like a drafting reference view
            s.frontCamera.distance = 14.0f;
            s.frontCamera.azimuth = 0.0f;
            s.frontCamera.elevation = 0.0f;
            s.frontCamera.target[1] = 1.35f;
            s.frontCamera.panSpeed = 0.0007f;
            s.frontCamera.zoomSpeed = 0.08f;

            // Side view: along -X, same low-FOV drafting behavior
            s.sideCamera.distance = 14.0f;
            s.sideCamera.azimuth = 0.5f * std::numbers::pi_v<float>;
            s.sideCamera.elevation = 0.0f;
            s.sideCamera.target[1] = 1.35f;
            s.sideCamera.panSpeed = 0.0007f;
            s.sideCamera.zoomSpeed = 0.08f;

            s.ready = s.hullHandle.isValid() && s.cabinHandle.isValid() && s.groundHandle.isValid() &&
                      s.hullMat.isValid() && s.cabinMat.isValid() && s.groundMat.isValid() &&
                      s.frontReference.isValid() && s.sideReference.isValid() && frontImagePlaneReady &&
                      sideImagePlaneReady;
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
            const int halfW = safeW / 2;
            s.surfaceWidth = safeW;

            submitHullProxy(
                s.frontPath.geometryPass(),
                s.hullHandle,
                s.cabinHandle,
                s.groundHandle,
                s.hullMat,
                s.cabinMat,
                s.groundMat);
            submitHullProxy(
                s.sidePath.geometryPass(),
                s.hullHandle,
                s.cabinHandle,
                s.groundHandle,
                s.hullMat,
                s.cabinMat,
                s.groundMat);

            const float frontAspect = static_cast<float>(halfW) / static_cast<float>(safeH);
            const float sideAspect = static_cast<float>(safeW - halfW) / static_cast<float>(safeH);
            const float draftFov = 0.18f;

            const gl::FrameData frontFrame = makeFrameData(s.frontCamera, draftFov, frontAspect);
            const gl::FrameData sideFrame = makeFrameData(s.sideCamera, draftFov, sideAspect);

            s.frontPath.render(frontFrame, safeW, safeH, { 0, 0, halfW, safeH });
            s.sidePath.render(sideFrame, safeW, safeH, { halfW, 0, safeW - halfW, safeH });
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

            if (!s.panDown)
            {
                return;
            }

            activeCamera(s).pan(dx, dy);
        },

        // onMouseButton
        [&](int button, bool pressed) {
            if (!scene)
            {
                return;
            }
            if (button == 2 || button == 3)
            {
                scene->panDown = pressed;
                if (pressed)
                {
                    if (scene->hasMouse)
                    {
                        scene->activeView = (scene->lastMouseX < (scene->surfaceWidth / 2)) ? 0 : 1;
                    }
                    else
                    {
                        scene->activeView = 0;
                    }
                }
            }
        },

        // onScroll
        [&](float delta) {
            if (!scene)
            {
                return;
            }
            if (!scene->hasMouse)
            {
                return;
            }
            activeCamera(*scene, scene->lastMouseX).zoom(delta);
        });
}
