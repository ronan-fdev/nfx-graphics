#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

// Shaders
// Depth pass: writes linear distance [0,1] into gl_FragDepth
static const char* s_depthVertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;

    uniform mat4 uModel;
    uniform mat4 uLightSpaceMatrix;

    out vec3 vFragPosWS;

    void main()
    {
        vec4 worldPos   = uModel * vec4(aPosition, 1.0);
        vFragPosWS      = worldPos.xyz;
        gl_Position     = uLightSpaceMatrix * worldPos;
    }
)glsl";

static const char* s_depthFragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;

    uniform vec3  uLightPos;
    uniform float uFarPlane;

    void main()
    {
        gl_FragDepth = length(vFragPosWS - uLightPos) / uFarPlane;
    }
)glsl";

// Main pass: Blinn-Phong + ambient + dim directional + point light with cube shadow
static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position   = camera.viewProj * worldPos;
        vFragPosWS    = worldPos.xyz;
        vNormalWS     = uNormalMatrix * aNormal;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;

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

    uniform vec3  uDiffuseColor;
    uniform vec3  uSpecularColor;
    uniform float uShininess;

    uniform vec3  uPointLightPos;
    uniform vec3  uPointLightColor;
    uniform float uPointLightIntensity;
    uniform float uPointLightRadius;
    uniform float uFarPlane;

    uniform samplerCube uShadowCube;

    float pointShadow(vec3 fragPosWS)
    {
        vec3  toLight      = fragPosWS - uPointLightPos;
        float currentDepth = length(toLight) / uFarPlane;
        float closestDepth = texture(uShadowCube, toLight).r;
        float bias         = 0.005;
        return (currentDepth - bias) > closestDepth ? 0.0 : 1.0;
    }

    out vec4 fragColor;

    void main()
    {
        vec3 N = normalize(vNormalWS);
        if(!gl_FrontFacing)
        {
            N = -N;
        }
        vec3 V = normalize(camera.position - vFragPosWS);

        // Ambient
        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.w;
        vec3 color = ambientColor * uDiffuseColor;

        // Directional (no shadow, dim fill)
        vec3  Ld   = normalize(-dirLight.direction.xyz);
        vec3  Hd   = normalize(Ld + V);
        float diffd = max(dot(N, Ld), 0.0);
        float specd = pow(max(dot(N, Hd), 0.0), uShininess);
        vec3  dirColor = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;
        color += diffd * dirColor * uDiffuseColor + specd * dirColor * uSpecularColor;

        // Point light with cube shadow
        vec3  toLight    = uPointLightPos - vFragPosWS;
        float dist       = length(toLight);
        if(dist > 1e-5)
        {
            vec3  Lp   = toLight / dist;
            vec3  Hp   = normalize(Lp + V);
            float diff = max(dot(N, Lp), 0.0);
            float spec = pow(max(dot(N, Hp), 0.0), uShininess);

            float atten;
            if(uPointLightRadius > 0.0)
            {
                float x = clamp(1.0 - dist / uPointLightRadius, 0.0, 1.0);
                atten = x * x;
            }
            else
            {
                atten = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
            }

            float shadow     = pointShadow(vFragPosWS);
            vec3  ptColor    = uPointLightColor * uPointLightIntensity;

            color += shadow * atten * (diff * ptColor * uDiffuseColor + spec * ptColor * uSpecularColor);
        }

        fragColor = vec4(color, 1.0);
    }
)glsl";

// Unlit shader for light marker cube
static const char* s_unlitVertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    uniform mat4 uModel;

    void main()
    {
        gl_Position = camera.viewProj * uModel * vec4(aPosition, 1.0);
    }
)glsl";

static const char* s_unlitFragSrc = R"glsl(
    #version 450 core

    uniform vec3 uEmissiveColor;
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(uEmissiveColor, 1.0);
    }
)glsl";

// Geometry
// clang-format off
static const float s_cubeVerts[] = {
    // Cube: pos(3) + normal(3)
    // +Z face
    -0.5f,-0.5f, 0.5f,  0, 0, 1,   0.5f,-0.5f, 0.5f,  0, 0, 1,   0.5f, 0.5f, 0.5f,  0, 0, 1,
    -0.5f,-0.5f, 0.5f,  0, 0, 1,   0.5f, 0.5f, 0.5f,  0, 0, 1,  -0.5f, 0.5f, 0.5f,  0, 0, 1,
    // -Z face
     0.5f,-0.5f,-0.5f,  0, 0,-1,  -0.5f,-0.5f,-0.5f,  0, 0,-1,  -0.5f, 0.5f,-0.5f,  0, 0,-1,
     0.5f,-0.5f,-0.5f,  0, 0,-1,  -0.5f, 0.5f,-0.5f,  0, 0,-1,   0.5f, 0.5f,-0.5f,  0, 0,-1,
    // -X face
    -0.5f,-0.5f,-0.5f, -1, 0, 0,  -0.5f,-0.5f, 0.5f, -1, 0, 0,  -0.5f, 0.5f, 0.5f, -1, 0, 0,
    -0.5f,-0.5f,-0.5f, -1, 0, 0,  -0.5f, 0.5f, 0.5f, -1, 0, 0,  -0.5f, 0.5f,-0.5f, -1, 0, 0,
    // +X face
     0.5f,-0.5f, 0.5f,  1, 0, 0,   0.5f,-0.5f,-0.5f,  1, 0, 0,   0.5f, 0.5f,-0.5f,  1, 0, 0,
     0.5f,-0.5f, 0.5f,  1, 0, 0,   0.5f, 0.5f,-0.5f,  1, 0, 0,   0.5f, 0.5f, 0.5f,  1, 0, 0,
    // -Y face
    -0.5f,-0.5f,-0.5f,  0,-1, 0,   0.5f,-0.5f,-0.5f,  0,-1, 0,   0.5f,-0.5f, 0.5f,  0,-1, 0,
    -0.5f,-0.5f,-0.5f,  0,-1, 0,   0.5f,-0.5f, 0.5f,  0,-1, 0,  -0.5f,-0.5f, 0.5f,  0,-1, 0,
    // +Y face
    -0.5f, 0.5f, 0.5f,  0, 1, 0,   0.5f, 0.5f, 0.5f,  0, 1, 0,   0.5f, 0.5f,-0.5f,  0, 1, 0,
    -0.5f, 0.5f, 0.5f,  0, 1, 0,   0.5f, 0.5f,-0.5f,  0, 1, 0,  -0.5f, 0.5f,-0.5f,  0, 1, 0
};

static const float s_planeVerts[] = {
    // Plane: pos(3) + normal(3)
    -5.f, 0.f,-5.f,  0, 1, 0,
     5.f, 0.f, 5.f,  0, 1, 0,
     5.f, 0.f,-5.f,  0, 1, 0,
    -5.f, 0.f,-5.f,  0, 1, 0,
    -5.f, 0.f, 5.f,  0, 1, 0,
     5.f, 0.f, 5.f,  0, 1, 0
};

// 6 cube face view directions: must match TextureCube::Face order (+X,-X,+Y,-Y,+Z,-Z)
static const float s_faceTargets[6][3] = {
    { 1,  0, 0 }, { -1, 0, 0 }, { 0, 1,  0 },
    { 0, -1, 0 }, {  0, 0, 1 }, { 0, 0, -1 }
};
static const float s_faceUps[6][3] = {
    { 0, -1,  0 }, { 0, -1, 0 }, { 0,  0, 1 },
    { 0,  0, -1 }, { 0, -1, 0 }, { 0, -1, 0 }
};
// clang-format on

// Constants
static constexpr int kShadowRes = 512;
static constexpr float kFarPlane = 20.f;
static constexpr float kPointLightRadius = 10.f;
static constexpr float kPointLightIntensity = 3.5f;
static constexpr float kMarkerScale = 0.08f;
static constexpr float kLightHeight = 2.5f;

// Scene
struct Scene
{
    gl::ShaderProgram prog;
    gl::ShaderProgram depthProg;
    gl::ShaderProgram unlitProg;

    gl::Buffer cubeVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray cubeVao;
    gl::Buffer planeVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray planeVao;
    gl::Buffer markerVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray markerVao;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;             // binding 0
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;      // binding 1
    gl::UniformBuffer<gl::DirectionalLight::GpuData> dirLightUbo; // binding 2

    gl::TextureCube shadowCube;
    gl::Framebuffer shadowFbo;
    gl::Sampler shadowSampler;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float time = 0.f;
    smp::Clock clock;
    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - point shadow", 1024, 768, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shaders
            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "point-shadow: main shader initialization failed\n");
            }

            scene->depthProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_depthVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_depthFragSrc } });
            if (!scene->depthProg.isValid())
            {
                std::fprintf(stderr, "point-shadow: depth shader initialization failed\n");
            }

            scene->unlitProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_unlitVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_unlitFragSrc } });
            if (!scene->unlitProg.isValid())
            {
                std::fprintf(stderr, "point-shadow: unlit shader initialization failed\n");
            }

            // Geometry
            scene->cubeVao.bind();
            scene->cubeVbo.setData(s_cubeVerts, sizeof(s_cubeVerts));
            scene->cubeVao.setVertexLayout({ gl::VertexLayout::Float3, gl::VertexLayout::Float3 });
            scene->cubeVao.unbind();

            scene->planeVao.bind();
            scene->planeVbo.setData(s_planeVerts, sizeof(s_planeVerts));
            scene->planeVao.setVertexLayout({ gl::VertexLayout::Float3, gl::VertexLayout::Float3 });
            scene->planeVao.unbind();

            scene->markerVao.bind();
            scene->markerVbo.setData(s_cubeVerts, sizeof(s_cubeVerts));
            scene->markerVao.setVertexLayout({ gl::VertexLayout::Float3, gl::VertexLayout::Float3 });
            scene->markerVao.unbind();

            // Shadow cube map: depth-only, 512x512 per face
            scene->shadowCube = gl::TextureCube::allocate(
                kShadowRes,
                { .generateMipmaps = false,
                  .minFilter = gl::TextureCube::Filter::Linear,
                  .magFilter = gl::TextureCube::Filter::Linear,
                  .wrapS = gl::TextureCube::Wrap::ClampToEdge,
                  .wrapT = gl::TextureCube::Wrap::ClampToEdge,
                  .wrapR = gl::TextureCube::Wrap::ClampToEdge,
                  .internalFormat = gl::TextureCube::InternalFormat::Depth32F });
            if (!scene->shadowCube.isValid())
            {
                std::fprintf(stderr, "point-shadow: shadow cube map initialization failed\n");
            }

            // Depth-only FBO: no color output
            const auto& funcs = gl::Context::current().functions();
            scene->shadowFbo.bind();
            funcs.glDrawBuffer(gl::NONE);
            funcs.glReadBuffer(gl::NONE);
            scene->shadowFbo.attachDepthCubeFace(scene->shadowCube, gl::TextureCube::Face::Right);
            const bool shadowFboComplete = scene->shadowFbo.isComplete();
            scene->shadowFbo.unbind();

            scene->shadowSampler = gl::Sampler::create({ .minFilter = gl::Sampler::Filter::Linear,
                                                         .magFilter = gl::Sampler::Filter::Linear,
                                                         .wrapS = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapT = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapR = gl::Sampler::Wrap::ClampToEdge,
                                                         .compareMode = gl::Sampler::CompareMode::None });

            // Shadow cube texture unit (4)
            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform("uShadowCube", 4);
                scene->prog.setUniform("uShininess", 64.0f);
                scene->prog.setUniform("uFarPlane", kFarPlane);
                scene->prog.setUniform("uPointLightRadius", kPointLightRadius);
                scene->prog.setUniform("uPointLightIntensity", kPointLightIntensity);
                gl::ShaderProgram::unbind();
            }
            if (scene->depthProg.isValid())
            {
                scene->depthProg.bind();
                scene->depthProg.setUniform("uFarPlane", kFarPlane);
                gl::ShaderProgram::unbind();
            }

            // Ambient UBO (binding 1)
            const auto ambGpu = gl::AmbientLight::toGpuData(math::Vec3{ 0.12f, 0.12f, 0.14f }, 1.0f);
            scene->ambientUbo.upload(ambGpu);
            scene->ambientUbo.bind(1);

            // Directional light UBO (binding 2)
            gl::DirectionalLight dirLight{};
            dirLight.color[0] = 0.7f;
            dirLight.color[1] = 0.75f;
            dirLight.color[2] = 0.85f;
            dirLight.intensity = 0.2f;
            const auto dirGpu = dirLight.toGpuData(math::Vec3{ -0.4f, -0.8f, -0.3f });
            scene->dirLightUbo.upload(dirGpu);
            scene->dirLightUbo.bind(2);

            // Camera UBO (binding 0)
            scene->cameraUbo.bind(0);

            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = 0.f;
            scene->orbitCamera.target[2] = 0.f;
            scene->orbitCamera.distance = 8.f;
            scene->orbitCamera.azimuth = 0.5f;
            scene->orbitCamera.elevation = 0.4f;

            scene->ready = scene->prog.isValid() && scene->depthProg.isValid() && scene->unlitProg.isValid() &&
                           scene->shadowCube.isValid() && scene->shadowSampler.isValid() && shadowFboComplete;
            if (!scene->ready)
            {
                std::fprintf(stderr, "point-shadow: initialization incomplete, rendering disabled\n");
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

            const float dt = scene->clock.tick();
            scene->time += dt;

            // Cube: 4 static cubes forming a small scene
            math::Mat4 model0, model1, model2, model3;
            math::Mat4 mTrans0, mTrans1, mTrans2, mTrans3;
            math::Mat4 mScale;
            math::mat4Scale(mScale, 0.7f, 0.7f, 0.7f);

            math::mat4Translate(mTrans0, 0.f, 0.35f, 0.f);
            math::mat4Translate(mTrans1, 2.5f, 0.35f, 2.5f);
            math::mat4Translate(mTrans2, -2.5f, 0.35f, -1.5f);
            math::mat4Translate(mTrans3, 2.0f, 0.35f, -2.5f);

            math::mat4Mul(model0, mTrans0, mScale);
            math::mat4Mul(model1, mTrans1, mScale);
            math::mat4Mul(model2, mTrans2, mScale);
            math::mat4Mul(model3, mTrans3, mScale);

            math::Mat4 planeModel;
            math::mat4Translate(planeModel, 0.f, -0.001f, 0.f);

            // Point light position (static above center)
            const float lx = 0.f;
            const float ly = kLightHeight;
            const float lz = 0.f;

            // 6 depth passes: one per cube face
            math::Mat4 faceView, faceProj, faceLSM;
            math::mat4Perspective(faceProj, static_cast<float>(std::numbers::pi) * 0.5f, 1.0f, 0.1f, kFarPlane);

            scene->depthProg.bind();
            scene->depthProg.setUniformVec3("uLightPos", math::Vec3{ lx, ly, lz }.data());
            funcs.glColorMask(false, false, false, false);

            scene->shadowFbo.bind();
            funcs.glViewport(0, 0, kShadowRes, kShadowRes);

            for (int face = 0; face < 6; ++face)
            {
                // Attach this face as depth target
                scene->shadowFbo.attachDepthCubeFace(scene->shadowCube, static_cast<gl::TextureCube::Face>(face));
                funcs.glClear(gl::DEPTH_BUFFER_BIT);

                const float* t = s_faceTargets[face];
                const float* u = s_faceUps[face];
                math::mat4LookAt(faceView, lx, ly, lz, lx + t[0], ly + t[1], lz + t[2], u[0], u[1], u[2]);
                math::mat4Mul(faceLSM, faceProj, faceView);
                scene->depthProg.setUniformMat4("uLightSpaceMatrix", faceLSM.data());

                // Draw all shadow casters with face culling disabled (cube faces can self-shadow)
                funcs.glDisable(gl::CULL_FACE);
                scene->cubeVao.bind();

                scene->depthProg.setUniformMat4("uModel", model0.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
                scene->depthProg.setUniformMat4("uModel", model1.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
                scene->depthProg.setUniformMat4("uModel", model2.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
                scene->depthProg.setUniformMat4("uModel", model3.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);

                scene->planeVao.bind();
                scene->depthProg.setUniformMat4("uModel", planeModel.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 6);
                scene->planeVao.unbind();

                funcs.glEnable(gl::CULL_FACE);
            }

            scene->shadowFbo.unbind();
            funcs.glColorMask(true, true, true, true);

            // Color pass
            const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);
            scene->cameraUbo.bind(0);

            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.04f, 0.05f, 0.08f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            scene->shadowCube.bind(4);
            scene->shadowSampler.bind(4);

            scene->prog.bind();
            const math::Vec3 lightColor{ 1.0f, 0.95f, 0.85f };
            scene->prog.setUniformVec3("uPointLightPos", math::Vec3{ lx, ly, lz }.data());
            scene->prog.setUniformVec3("uPointLightColor", lightColor.data());
            const math::Vec3 specColor{ 1.0f, 1.0f, 1.0f };
            scene->prog.setUniformVec3("uSpecularColor", specColor.data());

            auto drawCube = [&](const math::Mat4& model, const math::Vec3& diffuse) {
                scene->prog.setUniformVec3("uDiffuseColor", diffuse.data());
                scene->prog.setUniformMat4("uModel", model.data());
                math::Mat3 n;
                math::mat3InverseTranspose(n, model);
                scene->prog.setUniformMat3("uNormalMatrix", n.data());
                scene->cubeVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
            };

            drawCube(model0, math::Vec3{ 0.9f, 0.5f, 0.2f });
            drawCube(model1, math::Vec3{ 0.3f, 0.6f, 0.9f });
            drawCube(model2, math::Vec3{ 0.5f, 0.85f, 0.4f });
            drawCube(model3, math::Vec3{ 0.8f, 0.3f, 0.7f });

            // Floor
            {
                const math::Vec3 diffuse{ 0.35f, 0.38f, 0.42f };
                scene->prog.setUniformVec3("uDiffuseColor", diffuse.data());
                scene->prog.setUniformMat4("uModel", planeModel.data());
                math::Mat3 n;
                math::mat3InverseTranspose(n, planeModel);
                scene->prog.setUniformMat3("uNormalMatrix", n.data());
                funcs.glDisable(gl::CULL_FACE);
                scene->planeVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 6);
                scene->planeVao.unbind();
                funcs.glEnable(gl::CULL_FACE);
            }

            // Light marker (unlit)
            {
                scene->unlitProg.bind();
                math::Mat4 markerTrans, markerScale, markerModel;
                math::mat4Translate(markerTrans, lx, ly, lz);
                math::mat4Scale(markerScale, kMarkerScale, kMarkerScale, kMarkerScale);
                math::mat4Mul(markerModel, markerTrans, markerScale);
                scene->unlitProg.setUniformMat4("uModel", markerModel.data());
                scene->unlitProg.setUniformVec3("uEmissiveColor", lightColor.data());
                scene->markerVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
                scene->markerVao.unbind();
            }

            gl::Sampler::unbind(4);
            gl::TextureCube::unbind(4);
            gl::ShaderProgram::unbind();
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
