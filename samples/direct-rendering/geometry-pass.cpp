#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position = camera.viewProj * worldPos;
        vFragPosWS = worldPos.xyz;
        vNormalWS = uNormalMatrix * aNormal;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;

    out vec4 fragColor;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    layout(std140, binding = 1) uniform AmbientBlock {
        vec4 colorIntensity;
    } ambient;

    layout(std140, binding = 2) uniform DirectionalLightBlock {
        vec4 direction;
        vec4 colorIntensity;
    } dirLight;

    uniform vec3 uColor;
    uniform float uShininess;

    void main()
    {
        vec3 N = normalize(vNormalWS);
        N = gl_FrontFacing ? N : -N;

        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), uShininess);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;
        vec3 lightColor = dirLight.colorIntensity.rgb * dirLight.colorIntensity.a;

        vec3 color = ambientColor * uColor + diff * lightColor * uColor + spec * lightColor * vec3(0.35);
        fragColor = vec4(color, 1.0);
    }
)glsl";

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
    gl::PresentPass* presentPass = nullptr;

    gl::ShaderHandle shaderHandle;
    gl::MeshHandle cubeHandle;
    gl::MeshHandle sphereHandle;
    gl::MeshHandle planeHandle;
    gl::MaterialHandle cubeMaterial;
    gl::MaterialHandle sphereMaterial;
    gl::MaterialHandle planeMaterial;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float angle = 0.0f;
    smp::Clock clock;

    bool ready = false;
};

static void setMaterialColor(
    gl::MaterialCache& cache, gl::MaterialHandle handle, const gl::UniformVec3& color, float shininess)
{
    if (gl::Material* mat = cache.get(handle))
    {
        mat->setUniform("uColor", color);
        mat->setUniform("uShininess", shininess);
    }
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - geometry pass", 800, 600, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shader
            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            // Meshes
            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());
            scene->planeHandle = scene->meshCache.create(gl::Primitive::plane());

            // Materials
            scene->cubeMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());
            scene->sphereMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());

            gl::RenderState planeState = gl::RenderState::opaque();
            planeState.cullFace = false;
            scene->planeMaterial = scene->materialCache.create(scene->shaderHandle, planeState);

            setMaterialColor(scene->materialCache, scene->cubeMaterial, gl::UniformVec3{ 0.95f, 0.35f, 0.15f }, 24.0f);
            setMaterialColor(
                scene->materialCache, scene->sphereMaterial, gl::UniformVec3{ 0.20f, 0.65f, 0.95f }, 64.0f);
            setMaterialColor(scene->materialCache, scene->planeMaterial, gl::UniformVec3{ 0.28f, 0.30f, 0.34f }, 8.0f);

            // Pass
            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });
            scene->renderer.initialize(*scene->renderResources);

            scene->geometryPass->setOutputSize(scene->texture2DCache, 800, 600);
            scene->geometryPass->setClearColor(true, 0.08f, 0.10f, 0.14f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);
            scene->geometryPass->setOrder(gl::RenderQueue::Order::BySortKey);

            scene->presentPass->setInput(scene->geometryPass->colorOutput());
            scene->presentPass->setTonemapEnabled(true);
            scene->presentPass->setGammaEnabled(true);

            // Scene
            scene->orbitCamera.distance = 4.5f;
            scene->orbitCamera.target[1] = 0.25f;

            scene->ready = scene->shaderHandle.isValid() && scene->cubeHandle.isValid() &&
                           scene->sphereHandle.isValid() && scene->planeHandle.isValid() &&
                           scene->cubeMaterial.isValid() && scene->sphereMaterial.isValid() &&
                           scene->planeMaterial.isValid() && scene->geometryPass != nullptr &&
                           scene->presentPass != nullptr && scene->renderResources.has_value();
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;

            if (scene->geometryPass->outputWidth() != safeW || scene->geometryPass->outputHeight() != safeH)
            {
                scene->geometryPass->setOutputSize(scene->texture2DCache, safeW, safeH);
                scene->presentPass->setInput(scene->geometryPass->colorOutput());
            }

            // Frame
            gl::FrameData frame;
            frame.camera = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 100.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.08f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight directional;
            directional.color[0] = directional.color[1] = directional.color[2] = 1.0f;
            directional.intensity = 1.0f;
            constexpr float kDir[3] = { -0.4f, -0.8f, -0.2f };
            frame.directionalLight = directional.toGpuData(kDir);

            // Scene
            scene->geometryPass->clearQueue();

            const float dt = scene->clock.tick();
            scene->angle += 0.8f * dt;

            gl::RenderCommand planeCmd;
            planeCmd.mesh = scene->planeHandle;
            planeCmd.material = scene->planeMaterial;
            planeCmd.sortKey = 10;
            {
                math::Mat4 s;
                math::Mat4 t;
                math::mat4Scale(s, 8.0f, 1.0f, 8.0f);
                math::mat4Translate(t, 0.0f, -1.15f, 0.0f);
                math::mat4Mul(planeCmd.transform, t, s);
            }
            scene->geometryPass->submit(planeCmd);

            gl::RenderCommand cubeCmd;
            cubeCmd.mesh = scene->cubeHandle;
            cubeCmd.material = scene->cubeMaterial;
            cubeCmd.sortKey = 20;
            {
                math::Mat4 r;
                math::Mat4 t;
                math::mat4RotateY(r, scene->angle);
                math::mat4Translate(t, -1.6f, 0.0f, 0.0f);
                math::mat4Mul(cubeCmd.transform, t, r);
            }
            scene->geometryPass->submit(cubeCmd);

            gl::RenderCommand sphereCmd;
            sphereCmd.mesh = scene->sphereHandle;
            sphereCmd.material = scene->sphereMaterial;
            sphereCmd.sortKey = 30;
            {
                math::Mat4 t;
                math::mat4Translate(t, 1.6f, 0.05f, 0.0f);
                sphereCmd.transform = t;
            }
            scene->geometryPass->submit(sphereCmd);

            // Render
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
