#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

// Blinn-Phong with TBN normal mapping
//
// Vertex layout from Primitive::cube():
//   location 0: vec3 position
//   location 1: vec3 normal
//   location 2: vec2 uv
//   location 3: vec4 tangent (xyz + handedness w)

static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;
    layout(location = 3) in vec4 aTangent;

    out vec3 vFragPosWS;
    out vec2 vUV;
    out mat3 vTBN;

    uniform mat4 uModel;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position   = camera.viewProj * worldPos;
        vFragPosWS    = worldPos.xyz;
        vUV           = aUV;

        mat3 normalMatrix = mat3(transpose(inverse(uModel)));
        vec3 N = normalize(normalMatrix * aNormal);
        vec3 T = normalize(normalMatrix * aTangent.xyz);
        T      = normalize(T - dot(T, N) * N);
        vec3 B = cross(N, T) * aTangent.w;
        vTBN   = mat3(T, B, N);
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec2 vUV;
    in mat3 vTBN;

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

    layout(std140, binding = 1) uniform LightBlock {
        vec4 direction;       // w unused
        vec4 colorIntensity;
    } dirLight;

    layout(std140, binding = 2) uniform AmbientBlock {
        vec4 colorIntensity;
    } ambient;

    uniform sampler2D uDiffuseMap;
    uniform sampler2D uNormalMap;
    uniform float     uShininess;

    void main()
    {
        vec3 nmap = texture(uNormalMap, vUV).rgb * 2.0 - 1.0;
        vec3 N    = normalize(vTBN * nmap);

        vec3 diffuse   = texture(uDiffuseMap, vUV).rgb;
        vec3 L         = normalize(-dirLight.direction.xyz);
        vec3 V         = normalize(camera.position - vFragPosWS);
        vec3 H         = normalize(L + V);
        float diff     = max(dot(N, L), 0.0);
        float spec     = pow(max(dot(N, H), 0.0), uShininess);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;
        vec3 lightColor   = dirLight.colorIntensity.rgb * dirLight.colorIntensity.a;

        vec3 color = ambientColor * diffuse
                   + diff * lightColor * diffuse
                   + spec * lightColor;

        fragColor = vec4(color, 1.0);
    }
)glsl";

struct Scene
{
    gl::ShaderProgram prog;
    gl::Mesh cubeMesh;

    gl::Texture2D diffuseTex;
    gl::Texture2D normalTex;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;
    gl::UniformBuffer<gl::DirectionalLight::GpuData> dirLightUbo;
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;

    gl::OrbitCamera orbitCamera;

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
        { "nfx-graphics - normal map", 900, 700, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "normal-map: shader pipeline initialization failed\n");
            }

            scene->cubeMesh = gl::Mesh::create(gl::Primitive::cube());
            if (!scene->cubeMesh.isValid())
            {
                std::fprintf(stderr, "normal-map: mesh creation failed\n");
            }

            scene->diffuseTex = smp::loadEmbeddedTexture("toybox/toy_box_diffuse.png");
            scene->normalTex = smp::loadEmbeddedTexture("toybox/toy_box_normal.png");

            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform("uDiffuseMap", 0);
                scene->prog.setUniform("uNormalMap", 1);
                scene->prog.setUniform("uShininess", 64.0f);
                gl::ShaderProgram::unbind();
            }

            scene->cameraUbo.bind(0);
            scene->dirLightUbo.bind(1);
            scene->ambientUbo.bind(2);

            constexpr float kLightDir[3] = { -0.4f, -0.8f, -0.5f };
            gl::DirectionalLight dirLight;
            dirLight.color[0] = dirLight.color[1] = dirLight.color[2] = 1.f;
            dirLight.intensity = 1.f;
            scene->dirLightUbo.upload(dirLight.toGpuData(kLightDir));

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.f;
            ambient.intensity = 0.15f;
            scene->ambientUbo.upload(ambient.toGpuData());

            scene->orbitCamera.distance = 4.f;

            scene->ready = scene->prog.isValid() && scene->cubeMesh.isValid() && scene->diffuseTex.isValid() &&
                           scene->normalTex.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "normal-map: initialization incomplete, rendering disabled\n");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const auto& funcs = gl::Context::current().functions();
            funcs.glEnable(gl::DEPTH_TEST);
            funcs.glDepthMask(true);
            funcs.glDisable(gl::BLEND);
            funcs.glEnable(gl::CULL_FACE);
            funcs.glFrontFace(gl::CCW);
            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            const float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);

            math::Mat4 model;
            math::mat4RotateY(model, 0.5f);

            scene->diffuseTex.bind(0);
            scene->normalTex.bind(1);

            scene->prog.bind();
            scene->prog.setUniformMat4("uModel", model.data());
            scene->cubeMesh.bind();

            const auto idxType =
                scene->cubeMesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
            funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(scene->cubeMesh.indexCount()), idxType, nullptr);

            scene->cubeMesh.unbind();
            gl::Texture2D::unbind(0);
            gl::Texture2D::unbind(1);
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
