#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <optional>
#include <vector>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

// Blinn-Phong shader driven by per-instance mat4 + color
//
// The sphere mesh uses 3 per-vertex attributes:
//   location 0: vec3 position
//   location 1: vec3 normal
//   location 2: vec2 uv  (not used in fragment, VAO still sets it up)
//
// Per-instance data starts at location 3:
//   locations 3-6: mat4 columns (4 × vec4, divisor = 1)
//   location  7  : vec3 color   (divisor = 1)

static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;

    layout(location = 3) in vec4 aInstCol0;
    layout(location = 4) in vec4 aInstCol1;
    layout(location = 5) in vec4 aInstCol2;
    layout(location = 6) in vec4 aInstCol3;
    layout(location = 7) in vec3 aInstColor;
    layout(location = 8) in vec3 aInstNormCol0;
    layout(location = 9) in vec3 aInstNormCol1;
    layout(location = 10) in vec3 aInstNormCol2;

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
    out vec3 vColor;

    void main()
    {
        mat4 model        = mat4(aInstCol0, aInstCol1, aInstCol2, aInstCol3);
        mat3 normalMatrix = mat3(aInstNormCol0, aInstNormCol1, aInstNormCol2);

        vec4 worldPos = model * vec4(aPosition, 1.0);
        gl_Position   = camera.viewProj * worldPos;
        vFragPosWS    = worldPos.xyz;
        vNormalWS     = normalMatrix * aNormal;
        vColor        = aInstColor;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec3 vColor;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    layout(std140, binding = 1) uniform AmbientLightBlock {
        vec4 colorIntensity;
    } ambient;

    layout(std140, binding = 2) uniform DirectionalLightBlock {
        vec4 direction;
        vec4 colorIntensity;
    } dirLight;

    out vec4 fragColor;

    void main()
    {
        vec3 N = normalize(vNormalWS);
        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), 64.0);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.w;
        vec3 lightColor   = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;

        vec3 color = ambientColor * vColor
                   + diff * lightColor * vColor
                   + spec * lightColor * vec3(1.0);

        fragColor = vec4(color, 1.0);
    }
)glsl";

// Per-instance data uploaded as a flat struct into the instance VBO
// Layout: mat4 (4 × Float4 = 64 bytes) + vec3 color (Float3 = 12 bytes)
//       + mat3 normal matrix (3 × Float3 = 36 bytes) = 112 bytes/instance
// Must match the VertexLayout passed to setInstanceData
struct InstanceData
{
    float mat[16]; // column-major model matrix
    float color[3];
    float normalMat[9]; // column-major inverse-transpose of upper-left 3x3
};
static_assert(sizeof(InstanceData) == 112, "InstanceData must be 112 bytes");

static constexpr int kGridX = 10;
static constexpr int kGridZ = 10;
static constexpr int kInstanceCount = kGridX * kGridZ;
static constexpr float kSpacing = 2.2f;

struct Scene
{
    gl::ShaderProgram prog;
    gl::Mesh sphereMesh;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;
    gl::UniformBuffer<gl::DirectionalLight::GpuData> directionalUbo;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    smp::Clock clock;
    float time = 0.f;

    std::vector<InstanceData> instances;
    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - instanced", 800, 600, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "instanced: shader pipeline initialization failed\n");
            }

            scene->sphereMesh = gl::Mesh::create(gl::Primitive::uvSphere(16, 24));
            if (!scene->sphereMesh.isValid())
            {
                std::fprintf(stderr, "instanced: sphere mesh creation failed\n");
            }
            if (scene->sphereMesh.isValid() && !scene->sphereMesh.isIndexed())
            {
                std::fprintf(stderr, "instanced: sphere mesh must be indexed for this sample\n");
            }

            scene->cameraUbo.bind(0);
            scene->ambientUbo.bind(1);
            scene->directionalUbo.bind(2);

            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = 0.f;
            scene->orbitCamera.target[2] = 0.f;
            scene->orbitCamera.distance = 28.f;

            scene->instances.reserve(kInstanceCount);

            scene->ready = scene->prog.isValid() && scene->sphereMesh.isValid() && scene->sphereMesh.isIndexed();
            if (!scene->ready)
            {
                std::fprintf(stderr, "instanced: initialization incomplete, rendering disabled\n");
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
            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.f, 0.f, 0.f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            const auto gpuCam = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 200.f);
            scene->cameraUbo.upload(gpuCam);

            scene->time += scene->clock.tick();

            constexpr float kLightDir[3] = { -0.5f, -1.0f, -0.3f };
            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 0.15f;
            ambient.intensity = 1.f;
            gl::DirectionalLight dirLight;
            dirLight.color[0] = dirLight.color[1] = dirLight.color[2] = 1.f;
            dirLight.intensity = 1.f;

            scene->ambientUbo.upload(ambient.toGpuData());
            scene->directionalUbo.upload(dirLight.toGpuData(kLightDir));

            // Build per-instance data: one matrix + color per sphere
            scene->instances.clear();
            scene->instances.reserve(kInstanceCount);

            const float offsetX = (kGridX - 1) * kSpacing * 0.5f;
            const float offsetZ = (kGridZ - 1) * kSpacing * 0.5f;

            for (int z = 0; z < kGridZ; ++z)
            {
                for (int x = 0; x < kGridX; ++x)
                {
                    const float px = x * kSpacing - offsetX;
                    const float pz = z * kSpacing - offsetZ;
                    const float phase = (px + pz) * 0.25f;
                    const float py = 0.5f + std::sin(scene->time * 1.5f + phase) * 0.8f;

                    InstanceData inst{};
                    math::mat4Translate(inst.mat, px, py, pz);

                    math::Mat4 modelMat;
                    std::copy_n(inst.mat, 16, modelMat.data());
                    math::Mat3 nm;
                    math::mat3InverseTranspose(nm, modelMat);
                    std::copy_n(nm.data(), 9, inst.normalMat);

                    // Color: gradient across the grid
                    inst.color[0] = static_cast<float>(x) / (kGridX - 1);
                    inst.color[1] = static_cast<float>(z) / (kGridZ - 1);
                    inst.color[2] = 1.f - inst.color[0] * 0.5f;

                    scene->instances.push_back(inst);
                }
            }

            // Stream instance data to GPU: 4 × Float4 (mat4 columns) + Float3 (color)
            // + 3 × Float3 (normal matrix columns), starting at attribute location 3
            scene->sphereMesh.setInstanceData(
                scene->instances.data(),
                scene->instances.size() * sizeof(InstanceData),
                { gl::VertexLayout::Float4,
                  gl::VertexLayout::Float4,
                  gl::VertexLayout::Float4,
                  gl::VertexLayout::Float4,
                  gl::VertexLayout::Float3,
                  gl::VertexLayout::Float3,
                  gl::VertexLayout::Float3,
                  gl::VertexLayout::Float3 },
                3); // firstLocation

            // Single draw call for all kInstanceCount spheres
            scene->prog.bind();
            scene->sphereMesh.bind();
            const auto idxType =
                scene->sphereMesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
            funcs.glDrawElementsInstanced(
                gl::TRIANGLES,
                static_cast<GLsizei>(scene->sphereMesh.indexCount()),
                idxType,
                nullptr,
                static_cast<GLsizei>(kInstanceCount));
            scene->sphereMesh.unbind();
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
