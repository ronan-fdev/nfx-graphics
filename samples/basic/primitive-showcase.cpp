#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

// Shaders
static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;
    layout(location = 3) in vec4 aTangent; // w = handedness (+1 / -1)

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec2 vUV;
    out mat3 vTBN;

    uniform mat4 uModel;

    layout(std140, binding = 0) uniform Camera {
        mat4 uView;
        mat4 uProj;
        mat4 uViewProj;
        vec3 uCamPos;
        float _padCam0;
        vec3 uCamDir;
        float _padCam1;
    };

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position   = uViewProj * worldPos;
        vFragPosWS    = worldPos.xyz;
        vUV           = aUV;

        mat3 normalMatrix = mat3(transpose(inverse(uModel)));
        vec3 N = normalize(normalMatrix * aNormal);
        vec3 T = normalize(normalMatrix * aTangent.xyz);
        T      = normalize(T - dot(T, N) * N); // re-orthogonalize
        vec3 B = cross(N, T) * aTangent.w;
        vTBN      = mat3(T, B, N);
        vNormalWS = N;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec2 vUV;
    in mat3 vTBN;

    out vec4 fragColor;

    layout(std140, binding = 1) uniform Light {
        vec3  uLightDir;
        float _padLight0;
        vec3  uLightColor;
        float _padLight1;
        vec3  uAmbient;
        float _padLight2;
    };

    layout(std140, binding = 0) uniform Camera {
        mat4  uView;
        mat4  uProj;
        mat4  uViewProj;
        vec3  uCamPos;
        float _padCam0;
        vec3  uCamDir;
        float _padCam1;
    };

    uniform sampler2D uDiffuseMap;
    uniform sampler2D uNormalMap;
    uniform int       uUseDiffuseMap; // 0 = flat uDiffuseColor , 1 = sample uDiffuseMap
    uniform int       uUseNormalMap;  // 0 = interpolated normal, 1 = sample uNormalMap

    uniform vec3  uDiffuseColor;
    uniform vec3  uSpecularColor;
    uniform float uShininess;
    uniform int   uUnlit; // 1 = skip diffuse/spec lighting

    void main()
    {
        vec3 N;
        if(uUseNormalMap != 0)
        {
            vec3 nmap = texture(uNormalMap, vUV).rgb;
            N = normalize(vTBN * (nmap * 2.0 - 1.0));
        }
        else
        {
            N = normalize(vNormalWS);
        }
        if(!gl_FrontFacing) N = -N;

        vec3 diffuse = (uUseDiffuseMap != 0) ? texture(uDiffuseMap, vUV).rgb : uDiffuseColor;

        if(uUnlit != 0)
        {
            fragColor = vec4(diffuse, 1.0);
            return;
        }

        vec3  L    = normalize(-uLightDir);
        vec3  V    = normalize(uCamPos - vFragPosWS);
        vec3  H    = normalize(L + V);
        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), uShininess);

        vec3 color = uAmbient * diffuse
                   + diff * uLightColor * diffuse
                   + spec * uLightColor * uSpecularColor;

        fragColor = vec4(color, 1.0);
    }
)glsl";

static gl::MeshData createTangentQuadData()
{
    // pos(3), normal(3), uv(2), tangent(4)
    // clang-format off
    static const float k_vertices[] = {
    //   pos                  normal             uv           tangent (xyz + handedness)
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };

    static const unsigned int k_indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    // clang-format on

    gl::MeshData data;
    data.layout = {
        gl::VertexLayout::Float3,
        gl::VertexLayout::Float3,
        gl::VertexLayout::Float2,
        gl::VertexLayout::Float4,
    };
    data.setVertexData(k_vertices, sizeof(k_vertices), data.layout);
    data.setIndexData(k_indices, sizeof(k_indices) / sizeof(k_indices[0]), gl::MeshIndexType::UInt32);
    return data;
}

// UBO / Scene
struct LightUBO
{
    float lightDir[3];
    float _pad0;
    float lightColor[3];
    float _pad1;
    float ambient[3];
    float _pad2;
};

struct Scene
{
    gl::ShaderProgram prog;

    gl::Mesh cubeMesh;
    gl::Mesh sphereMesh;
    gl::Mesh planeMesh;
    gl::Mesh quadMesh;

    gl::Texture2D diffuseTex;
    gl::Texture2D normalTex;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;
    gl::UniformBuffer<LightUBO> lightUbo;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float angle = 0.f;
    smp::Clock clock;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - primitive-showcase", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shader
            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "primitive-showcase: shader pipeline initialization failed\n");
            }

            // Geometry
            scene->cubeMesh = gl::Mesh::create(gl::Primitive::cube());
            scene->sphereMesh = gl::Mesh::create(gl::Primitive::uvSphere(16, 24));
            scene->planeMesh = gl::Mesh::create(gl::Primitive::plane(2, 2));
            scene->quadMesh = gl::Mesh::create(createTangentQuadData());

            if (!scene->cubeMesh.isValid() || !scene->sphereMesh.isValid() || !scene->planeMesh.isValid() ||
                !scene->quadMesh.isValid())
            {
                std::fprintf(stderr, "primitive-showcase: mesh creation failed\n");
            }

            // Materials
            scene->diffuseTex = smp::loadEmbeddedTexture("brickwall/brickwall.jpg");
            scene->normalTex = smp::loadEmbeddedTexture("brickwall/brickwall_normal.jpg");

            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform("uShininess", 64.0f);
                scene->prog.setUniform("uDiffuseMap", 0);
                scene->prog.setUniform("uNormalMap", 1);
                scene->prog.setUniform("uUnlit", 0);
                gl::ShaderProgram::unbind();
            }

            // Camera UBO (binding = 0)
            scene->cameraUbo.bind(0);

            // Light UBO (binding = 1)
            LightUBO lightData{};
            const gl::DirectionalLight dirLight{};
            const math::Vec3 lightDir{ -0.2f, -0.4f, -0.9f };
            const auto dirGpu = dirLight.toGpuData(lightDir);
            lightData.lightDir[0] = dirGpu.direction[0];
            lightData.lightDir[1] = dirGpu.direction[1];
            lightData.lightDir[2] = dirGpu.direction[2];
            lightData.lightColor[0] = dirGpu.colorIntensity[0];
            lightData.lightColor[1] = dirGpu.colorIntensity[1];
            lightData.lightColor[2] = dirGpu.colorIntensity[2];
            const auto ambGpu = gl::AmbientLight::toGpuData(math::Vec3{ 0.15f, 0.15f, 0.15f }, 1.0f);
            lightData.ambient[0] = ambGpu.colorIntensity[0];
            lightData.ambient[1] = ambGpu.colorIntensity[1];
            lightData.ambient[2] = ambGpu.colorIntensity[2];
            scene->lightUbo.upload(lightData);
            scene->lightUbo.bind(1);

            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = -1.0f;
            scene->orbitCamera.target[2] = 0.f;
            scene->orbitCamera.distance = 16.f;

            scene->ready = scene->prog.isValid() && scene->cubeMesh.isValid() && scene->sphereMesh.isValid() &&
                           scene->planeMesh.isValid() && scene->quadMesh.isValid() && scene->diffuseTex.isValid() &&
                           scene->normalTex.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "primitive-showcase: initialization incomplete, rendering disabled\n");
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

            // Camera UBO
            const float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);

            // Rotation
            const float dt = scene->clock.tick();
            scene->angle += 0.5f * dt;

            // Models
            math::Mat4 rotY;
            math::mat4RotateY(rotY, scene->angle);

            math::Mat4 tCube, mCube;
            math::mat4Translate(tCube, -3.f, 0.f, 0.f);
            math::mat4Mul(mCube, tCube, rotY);

            math::Mat4 mSphere;
            math::mat4Translate(mSphere, 3.f, 0.f, 0.f);

            math::Mat4 mPlane;
            math::mat4Translate(mPlane, -3.f, -3.f, 0.f);

            math::Mat4 mQuad;
            math::mat4Translate(mQuad, 3.f, -3.f, 0.f);

            // Bind brickwall textures for the cube (units 0 and 1 stay bound all frame)
            scene->diffuseTex.bind(0);
            scene->normalTex.bind(1);

            scene->prog.bind();

            const math::Vec3 specColor{ 1.0f, 1.0f, 1.0f };
            scene->prog.setUniformVec3("uSpecularColor", specColor.data());

            const auto drawMesh = [&](gl::Mesh& mesh, const math::Mat4& model, const math::Vec3& diffuse) {
                scene->prog.setUniformVec3("uDiffuseColor", diffuse.data());
                scene->prog.setUniformMat4("uModel", model.data());
                mesh.bind();
                if (mesh.isIndexed())
                {
                    const auto idxType =
                        mesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
                    funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(mesh.indexCount()), idxType, nullptr);
                }
                else
                {
                    funcs.glDrawArrays(gl::TRIANGLES, 0, static_cast<GLsizei>(mesh.vertexCount()));
                }
                mesh.unbind();
            };

            // Cube: diffuse + normal map
            scene->prog.setUniform("uUseDiffuseMap", 1);
            scene->prog.setUniform("uUseNormalMap", 1);
            drawMesh(scene->cubeMesh, mCube, math::Vec3{ 1.f, 1.f, 1.f });

            // Other meshes: flat color, geometric normal
            scene->prog.setUniform("uUseDiffuseMap", 0);
            scene->prog.setUniform("uUseNormalMap", 0);
            drawMesh(scene->sphereMesh, mSphere, math::Vec3{ 0.30f, 0.75f, 0.95f });

            funcs.glDisable(gl::CULL_FACE);
            drawMesh(scene->planeMesh, mPlane, math::Vec3{ 0.35f, 0.40f, 0.45f });
            scene->prog.setUniform("uUnlit", 1);
            drawMesh(scene->quadMesh, mQuad, math::Vec3{ 0.95f, 0.90f, 0.35f });
            scene->prog.setUniform("uUnlit", 0);
            funcs.glEnable(gl::CULL_FACE);

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
