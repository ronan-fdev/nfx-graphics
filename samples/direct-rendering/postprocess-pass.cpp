#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>
#include <string>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr int kWindowWidth = 1000;
    constexpr int kWindowHeight = 700;

    constexpr float kFovY = 0.785f;
    constexpr float kZNear = 0.1f;
    constexpr float kZFar = 500.0f;

    constexpr float kAmbientIntensity = 0.10f;
    constexpr float kDirectionalIntensity = 1.0f;
    constexpr float kLightDir[3] = { -0.4f, -0.8f, -0.2f };

    constexpr float kRotationSpeed = 0.8f;
} // namespace

static std::string effectSource(int index)
{
    switch (index)
    {
        case 1:
            return R"glsl(
                #version 450 core
                // Effect: Monochrome + scanlines
                in vec2 vTexCoord;
                out vec4 fragColor;

                uniform sampler2D uColorInput;
                uniform float uTime;

                void main()
                {
                    vec3 col = texture(uColorInput, vTexCoord).rgb;
                    float luma = dot(col, vec3(0.2126, 0.7152, 0.0722));
                    float scan = 0.95 + 0.05 * sin((vTexCoord.y + uTime * 0.3) * 900.0);
                    vec3 gray = vec3(luma) * scan;
                    fragColor = vec4(gray, 1.0);
                }
            )glsl";
        case 2:
            return R"glsl(
                #version 450 core
                // Effect: Chromatic aberration + grain + vignette
                in vec2 vTexCoord;
                out vec4 fragColor;

                uniform sampler2D uColorInput;
                uniform float uTime;

                float rand(vec2 p)
                {
                    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
                }

                void main()
                {
                    vec2 c = vTexCoord - 0.5;
                    float d = length(c);
                    vec2 dir = normalize(c + vec2(0.0001));
                    float ca = 0.007 * d * d;

                    float r = texture(uColorInput, vTexCoord + dir * ca).r;
                    float g = texture(uColorInput, vTexCoord).g;
                    float b = texture(uColorInput, vTexCoord - dir * ca).b;
                    vec3 color = vec3(r, g, b);

                    float vignette = 1.0 - dot(c, c) * 2.8;
                    color *= clamp(vignette, 0.0, 1.0);

                    float grain = rand(vTexCoord + fract(uTime * 0.11)) * 0.06 - 0.03;
                    color = clamp(color + grain, 0.0, 1.0);

                    fragColor = vec4(color, 1.0);
                }
            )glsl";
        default:
            return R"glsl(
                #version 450 core
                // Effect: Neutral (gamma only)
                in vec2 vTexCoord;
                out vec4 fragColor;

                uniform sampler2D uColorInput;

                void main()
                {
                    vec3 color = texture(uColorInput, vTexCoord).rgb;
                    color = pow(color, vec3(1.0 / 2.2)); // simple display gamma
                    fragColor = vec4(color, 1.0);
                }
            )glsl";
    }
}

static const char* effectName(int index)
{
    switch (index)
    {
        case 1:
            return "Mono Scanlines";
        case 2:
            return "Chromatic + Grain";
        default:
            return "Neutral";
    }
}

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    std::optional<gl::RenderResources> renderResources;

    gl::Renderer renderer;
    gl::GeometryPass* geometryPass = nullptr;
    gl::PostProcessPass* postPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::MeshHandle cubeHandle;
    gl::MeshHandle sphereHandle;
    gl::MeshHandle planeHandle;

    gl::MaterialHandle cubeMaterial;
    gl::MaterialHandle sphereMaterial;
    gl::MaterialHandle planeMaterial;

    gl::OrbitCamera orbitCamera;

    smp::Clock clock;
    int effectIndex = 0;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float angle = 0.0f;
    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - postprocess-pass (left click to cycle)", kWindowWidth, kWindowHeight, 4, 5 },

        // onInit
        [&] {
            scene.emplace();

            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->planeHandle = scene->meshCache.create(gl::Primitive::plane());

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });

            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.95f, 0.90f, 0.20f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 24.0f;
                scene->cubeMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.20f, 0.65f, 0.95f };
                desc.specularColor = { 0.35f, 0.35f, 0.35f };
                desc.shininess = 64.0f;
                scene->sphereMaterial = desc.build(*scene->renderResources);
            }
            {
                gl::BlinnPhongMaterial desc;
                desc.diffuseColor = { 0.28f, 0.30f, 0.34f };
                desc.specularColor = { 0.10f, 0.10f, 0.10f };
                desc.shininess = 8.0f;
                scene->planeMaterial = desc.build(*scene->renderResources);
                if (gl::Material* m = scene->materialCache.get(scene->planeMaterial))
                {
                    gl::RenderState rs = m->renderState();
                    rs.cullFace = false;
                    m->setRenderState(rs);
                }
            }

            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->postPass = scene->renderer.createPass<gl::PostProcessPass>("PostFX");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->geometryPass->setClearColor(true, 0.10f, 0.11f, 0.14f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);
            scene->geometryPass->setOrder(gl::RenderQueue::Order::BySortKey);
            scene->geometryPass->setOutputSize(scene->texture2DCache, kWindowWidth, kWindowHeight);

            scene->postPass->setInput(scene->geometryPass->colorOutput());
            scene->postPass->setOutputSize(scene->texture2DCache, kWindowWidth, kWindowHeight);
            scene->postPass->setEffectSource(effectSource(scene->effectIndex));
            scene->presentPass->setInput(scene->postPass->colorOutput());
            scene->presentPass->setTonemapEnabled(false);
            scene->presentPass->setGammaEnabled(false);

            scene->renderer.initialize(*scene->renderResources);

            scene->orbitCamera.distance = 6.0f;
            scene->orbitCamera.elevation = 0.45f;

            std::fprintf(stdout, "[rendering-postprocess] Effect: %s\n", effectName(scene->effectIndex));

            scene->ready = scene->cubeHandle.isValid() && scene->sphereHandle.isValid() &&
                           scene->planeHandle.isValid() && scene->cubeMaterial.isValid() &&
                           scene->sphereMaterial.isValid() && scene->planeMaterial.isValid() &&
                           scene->geometryPass != nullptr && scene->postPass != nullptr &&
                           scene->presentPass != nullptr && scene->postPass->colorOutput().isValid();
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;
            gl::Context::current().functions().glViewport(0, 0, safeW, safeH);

            if (scene->geometryPass->outputWidth() != safeW || scene->geometryPass->outputHeight() != safeH)
            {
                scene->geometryPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->postPass->setInput(scene->geometryPass->colorOutput());
                scene->postPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->presentPass->setInput(scene->postPass->colorOutput());
            }

            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                kFovY, static_cast<float>(safeW) / static_cast<float>(safeH), kZNear, kZFar);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = kAmbientIntensity;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight directional;
            directional.color[0] = directional.color[1] = directional.color[2] = 1.0f;
            directional.intensity = kDirectionalIntensity;
            frame.directionalLight = directional.toGpuData(kLightDir);

            scene->geometryPass->clearQueue();
            scene->angle += kRotationSpeed * scene->clock.tick();

            gl::RenderCommand cubeCmd;
            cubeCmd.mesh = scene->cubeHandle;
            cubeCmd.material = scene->cubeMaterial;
            cubeCmd.sortKey = 10;
            {
                math::Mat4 r;
                math::Mat4 t;
                math::mat4RotateY(r, scene->angle);
                math::mat4Translate(t, -1.5f, 0.5f, 0.0f);
                math::mat4Mul(cubeCmd.transform, t, r);
            }
            scene->geometryPass->submit(cubeCmd);

            gl::RenderCommand sphereCmd;
            sphereCmd.mesh = scene->sphereHandle;
            sphereCmd.material = scene->sphereMaterial;
            sphereCmd.sortKey = 20;
            {
                math::Mat4 t;
                math::mat4Translate(t, 1.5f, 0.5f, 0.0f);
                sphereCmd.transform = t;
            }
            scene->geometryPass->submit(sphereCmd);

            gl::RenderCommand planeCmd;
            planeCmd.mesh = scene->planeHandle;
            planeCmd.material = scene->planeMaterial;
            planeCmd.sortKey = 5;
            {
                math::Mat4 s;
                math::Mat4 t;
                math::mat4Scale(s, 8.0f, 1.0f, 8.0f);
                math::mat4Translate(t, 0.0f, -1.15f, 0.0f);
                math::mat4Mul(planeCmd.transform, t, s);
            }
            scene->geometryPass->submit(planeCmd);

            scene->postPass->setUniformFloat("uTime", scene->clock.elapsed());

            scene->renderer.setFrameData(frame);
            scene->renderer.render();
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
            if (button == 1 && pressed)
            {
                scene->effectIndex = (scene->effectIndex + 1) % 3;
                scene->postPass->setEffectSource(effectSource(scene->effectIndex));
                std::fprintf(stdout, "[rendering-postprocess] Effect: %s\n", effectName(scene->effectIndex));
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
