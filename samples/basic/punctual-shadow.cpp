#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

// Spot shader
static const char* s_pointDepthVertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec3 aPosition;
    uniform mat4 uModel;
    out vec3 vFragPosWS;
    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        vFragPosWS    = worldPos.xyz;
        gl_Position   = worldPos;
    }
)glsl";

static const char* s_pointDepthGeomSrc = R"glsl(
    #version 450 core
    layout(triangles) in;
    layout(triangle_strip, max_vertices = 18) out;

    layout(std140, binding = 3) uniform CubeFaceMatricesBlock {
        mat4 face[6];
    } cubeMatrices;

    in  vec3 vFragPosWS[];
    out vec3 gFragPosWS;

    void main()
    {
        for(int f = 0; f < 6; ++f)
        {
            gl_Layer = f;
            for(int v = 0; v < 3; ++v)
            {
                gFragPosWS  = vFragPosWS[v];
                gl_Position = cubeMatrices.face[f] * vec4(vFragPosWS[v], 1.0);
                EmitVertex();
            }
            EndPrimitive();
        }
    }
)glsl";

// Point shader
static const char* s_pointDepthFragSrc = R"glsl(
    #version 450 core
    in  vec3  gFragPosWS;
    uniform vec3  uLightPos;
    uniform float uFarPlane;
    void main()
    {
        gl_FragDepth = length(gFragPosWS - uLightPos) / uFarPlane;
    }
)glsl";

static const char* s_spotDepthVertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec3 aPosition;
    uniform mat4 uLightSpaceMatrix;
    uniform mat4 uModel;
    void main() { gl_Position = uLightSpaceMatrix * uModel * vec4(aPosition, 1.0); }
)glsl";

static const char* s_spotDepthFragSrc = R"glsl(
    #version 450 core
    void main() {}
)glsl";

// Color shader
static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view; mat4 proj; mat4 viewProj;
        vec3 position; float _pad0;
        vec3 direction; float _pad1;
    } camera;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;
    uniform mat4 uSpotLSM;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec4 vSpotFragPosLS;

    void main()
    {
        vec4 worldPos  = uModel * vec4(aPosition, 1.0);
        gl_Position    = camera.viewProj * worldPos;
        vFragPosWS     = worldPos.xyz;
        vNormalWS      = uNormalMatrix * aNormal;
        vSpotFragPosLS = uSpotLSM * worldPos;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec4 vSpotFragPosLS;
    out vec4 fragColor;

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view; mat4 proj; mat4 viewProj;
        vec3 position; float _pad0;
        vec3 direction; float _pad1;
    } camera;

    layout(std140, binding = 1) uniform AmbientBlock {
        vec4 colorIntensity;
    } ambient;

    // Light type tags (matches PunctualLight::Type)
    const int kLightTypePoint = 0;
    const int kLightTypeSpot  = 1;
    const int kMaxLights      = 64;

    struct GpuLight {
        vec4 position;       // xyz = world pos, w = radius
        vec4 direction;      // xyz = direction, w = type (0=point, 1=spot)
        vec4 colorIntensity; // rgb = color    , w = intensity
        vec4 params;         // x = cos(inner) , y = cos(outer), z = shadowFar, w = reserved
    };

    layout(std430, binding = 0) readonly buffer PunctualLightsBlock {
        int      count;
        int      _pad[3];
        GpuLight lights[kMaxLights];
    } lightBlock;

    uniform samplerCube uPointShadows[3];
    uniform sampler2D   uSpotShadow;

    uniform vec3  uDiffuse;   // surface diffuse color
    uniform float uShininess; // Blinn-Phong shininess

    // Attenuation: inverse-square with optional radius cutoff
    float attenuation(float dist, float radius)
    {
        if(radius > 0.0) {
            float x = clamp(1.0 - (dist * dist) / (radius * radius), 0.0, 1.0);
            return x * x;
        }
        return 1.0 / max(dist * dist, 0.0001);
    }

    float pointShadow(int lightIndex, vec3 fragPos, vec3 lightPos, float farPlane)
    {
        vec3  v     = fragPos - lightPos;
        float depth = length(v) / farPlane;
        float stored;
        if(lightIndex == 0)      stored = texture(uPointShadows[0], v).r;
        else if(lightIndex == 1) stored = texture(uPointShadows[1], v).r;
        else                     stored = texture(uPointShadows[2], v).r;
        return (depth - 0.005) > stored ? 0.0 : 1.0;
    }

    float spotShadow(vec4 fragPosLS)
    {
        vec3 proj = fragPosLS.xyz / fragPosLS.w;
        proj = proj * 0.5 + 0.5;
        if(proj.z < 0.0 || proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
        {
            return 1.0;
        }
        return (proj.z - 0.002) > texture(uSpotShadow, proj.xy).r ? 0.0 : 1.0;
    }

    void main()
    {
        vec3 N = normalize(vNormalWS);
        N = gl_FrontFacing ? N : -N;
        vec3 V = normalize(camera.position - vFragPosWS);

        vec3 color = ambient.colorIntensity.rgb * ambient.colorIntensity.a * uDiffuse;
        int  pointIdx = 0;

        for(int i = 0; i < lightBlock.count; ++i)
        {
            GpuLight light = lightBlock.lights[i];
            int ltype = int(light.direction.w);

            vec3  toLight = light.position.xyz - vFragPosWS;
            float dist    = length(toLight);
            vec3  L       = toLight / max(dist, 0.0001);
            vec3  H       = normalize(L + V);
            float atten   = attenuation(dist, light.position.w);
            float shadow  = 1.0;

            if(ltype == kLightTypePoint)
            {
                float farPlane = light.params.z > 0.0 ? light.params.z : 20.0;
                shadow = pointShadow(pointIdx, vFragPosWS, light.position.xyz, farPlane);
                pointIdx++;
            }
            else
            {
                vec3  spotDir  = normalize(light.direction.xyz);
                float cosTheta = dot(-L, spotDir);
                float ci       = light.params.x;
                float co       = light.params.y;
                atten *= clamp((cosTheta - co) / max(ci - co, 0.0001), 0.0, 1.0);
                shadow = spotShadow(vSpotFragPosLS);
            }

            vec3  lcolor = light.colorIntensity.rgb * light.colorIntensity.w;
            float diff   = max(dot(N, L), 0.0);
            float spec   = pow(max(dot(N, H), 0.0), uShininess);
            color += shadow * atten * lcolor * (diff * uDiffuse + spec * vec3(0.4));
        }

        fragColor = vec4(color, 1.0);
    }
)glsl";

// Unlit shader
static const char* s_markerVertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec3 aPosition;
    uniform mat4 uModel;
    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view; mat4 proj; mat4 viewProj;
        vec3 position; float _pad0; vec3 direction; float _pad1;
    } camera;
    void main() { gl_Position = camera.viewProj * uModel * vec4(aPosition, 1.0); }
)glsl";

static const char* s_markerFragSrc = R"glsl(
    #version 450 core
    uniform vec3 uColor;
    out vec4 fragColor;
    void main() { fragColor = vec4(uColor, 1.0); }
)glsl";

// Scene constants
static constexpr int kShadowRes = 512;
static constexpr float kFarPlane = 20.f;
static constexpr int kNumPointLights = 3;
static constexpr float kOrbitRadius = 3.f;
static constexpr float kOrbitHeight = 2.5f;
static constexpr float kPointRadius = 8.f;
static constexpr float kPointIntensity = 2.f;
static constexpr float kSpotIntensity = 2.f;
static constexpr float kSpotRadius = 12.f;
static constexpr float kSpotInner = 0.30f; // radians
static constexpr float kSpotOuter = 0.45f; // radians
static constexpr float kPlaneDiffuse[3] = { 0.35f, 0.38f, 0.42f };

static_assert(
    gl::PunctualLight::MaxLights == 64, "Update shader constant kMaxLights to match PunctualLight::MaxLights");

// clang-format off
static constexpr float kPointColors[kNumPointLights][3] = {
    { 1.0f, 0.2f, 0.2f }, // red
    { 0.2f, 1.0f, 0.2f }, // green
    { 0.2f, 0.4f, 1.0f }  // blue
};

static constexpr float kFaceTargets[6][3] = {
    {  1,  0,  0 }, // +X
    { -1,  0,  0 }, // -X
    {  0,  1,  0 }, // +Y
    {  0, -1,  0 }, // -Y
    {  0,  0,  1 }, // +Z
    {  0,  0, -1 }  // -Z
};

static constexpr float kFaceUps[6][3] = {
    { 0, -1,  0 }, // +X: up = -Y
    { 0, -1,  0 }, // -X: up = -Y
    { 0,  0,  1 }, // +Y: up = +Z
    { 0,  0, -1 }, // -Y: up = -Z
    { 0, -1,  0 }, // +Z: up = -Y
    { 0, -1,  0 }  // -Z: up = -Y
};
// clang-format on

struct CubeFaceBlock
{
    float face[6][16];
};

// Scene
struct Scene
{
    gl::ShaderProgram pointDepthProg;
    gl::ShaderProgram spotDepthProg;
    gl::ShaderProgram prog;
    gl::ShaderProgram markerProg;

    gl::Mesh sphereMesh;
    gl::Mesh planeMesh;
    gl::Mesh markerMesh;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;
    gl::UniformBuffer<CubeFaceBlock> cubeFaceUbo;

    gl::ShaderStorageBuffer<gl::PunctualLight::GpuBlock> lightSsbo;

    std::array<gl::TextureCube, kNumPointLights> pointShadowCubes;
    gl::Framebuffer pointShadowFbo;

    gl::Texture2D spotShadowTex;
    gl::Framebuffer spotShadowFbo;
    gl::Sampler shadowSampler;

    gl::OrbitCamera orbitCamera;
    smp::Clock clock;
    float time = 0.f;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    bool ready = false;
};

static void drawMesh(const gl::Mesh& mesh, gl::ShaderProgram& prog, const math::Mat4& model, const gl::Functions& funcs)
{
    gl::UniformMat4 arr;
    std::copy(model.data(), model.data() + 16, arr.begin());
    prog.setUniformMat4("uModel", arr.data());

    math::Mat3 nm;
    math::mat3InverseTranspose(nm, model);
    prog.setUniformMat3("uNormalMatrix", nm.data());

    mesh.bind();
    const auto idxType = mesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
    funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(mesh.indexCount()), idxType, nullptr);
    mesh.unbind();
}

static void drawDepth(
    const gl::Mesh& mesh, gl::ShaderProgram& prog, const math::Mat4& model, const gl::Functions& funcs)
{
    gl::UniformMat4 arr;
    std::copy(model.data(), model.data() + 16, arr.begin());
    prog.setUniformMat4("uModel", arr.data());
    mesh.bind();
    const auto idxType = mesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
    funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(mesh.indexCount()), idxType, nullptr);
    mesh.unbind();
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - punctual shadow (point + spot SSBO)", 1024, 768, 4, 3 },

        // onInit
        [&] {
            scene.emplace();

            scene->pointDepthProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_pointDepthVertSrc },
                                                 { gl::ShaderProgram::Stage::Geometry, s_pointDepthGeomSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_pointDepthFragSrc } });

            scene->spotDepthProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_spotDepthVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_spotDepthFragSrc } });

            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            scene->markerProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_markerVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_markerFragSrc } });

            for (auto* p : { &scene->pointDepthProg, &scene->spotDepthProg, &scene->prog, &scene->markerProg })
            {
                if (!p->isValid())
                {
                    std::fprintf(stderr, "[punctual-shadow] shader compilation failed\n");
                }
            }

            scene->sphereMesh = gl::Mesh::create(gl::Primitive::uvSphere());
            scene->planeMesh = gl::Mesh::create(gl::Primitive::plane());
            scene->markerMesh = gl::Mesh::create(gl::Primitive::uvSphere());

            // Point shadow cube maps
            const gl::TextureCube::Params cubeParams{ .generateMipmaps = false,
                                                      .minFilter = gl::TextureCube::Filter::Nearest,
                                                      .magFilter = gl::TextureCube::Filter::Nearest,
                                                      .wrapS = gl::TextureCube::Wrap::ClampToEdge,
                                                      .wrapT = gl::TextureCube::Wrap::ClampToEdge,
                                                      .wrapR = gl::TextureCube::Wrap::ClampToEdge,
                                                      .internalFormat = gl::TextureCube::InternalFormat::Depth32F };
            for (auto& cube : scene->pointShadowCubes)
            {
                cube = gl::TextureCube::allocate(kShadowRes, cubeParams);
            }

            {
                const auto& f = gl::Context::current().functions();
                scene->pointShadowFbo.bind();
                f.glDrawBuffer(gl::NONE);
                f.glReadBuffer(gl::NONE);
                scene->pointShadowFbo.unbind();
            }

            // Spot shadow map
            {
                gl::Texture2D::Params p;
                p.generateMipmaps = false;
                p.minFilter = gl::Texture2D::Filter::Nearest;
                p.magFilter = gl::Texture2D::Filter::Nearest;
                p.wrapS = gl::Texture2D::Wrap::ClampToEdge;
                p.wrapT = gl::Texture2D::Wrap::ClampToEdge;
                p.internalFormat = gl::Texture2D::InternalFormat::Depth32F;
                scene->spotShadowTex = gl::Texture2D::allocate(kShadowRes, kShadowRes, p);

                const auto& f = gl::Context::current().functions();
                scene->spotShadowFbo.bind();
                scene->spotShadowFbo.attachDepthTexture(scene->spotShadowTex);
                f.glDrawBuffer(gl::NONE);
                f.glReadBuffer(gl::NONE);
                scene->spotShadowFbo.unbind();
            }

            scene->shadowSampler = gl::Sampler::create({ .minFilter = gl::Sampler::Filter::Nearest,
                                                         .magFilter = gl::Sampler::Filter::Nearest,
                                                         .wrapS = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapT = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapR = gl::Sampler::Wrap::ClampToEdge,
                                                         .compareMode = gl::Sampler::CompareMode::None });

            // Bind sampler indices once
            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform(
                    "uPointShadows[0]", static_cast<int>(gl::TextureBindings::PointShadowMapBase + 0));
                scene->prog.setUniform(
                    "uPointShadows[1]", static_cast<int>(gl::TextureBindings::PointShadowMapBase + 1));
                scene->prog.setUniform(
                    "uPointShadows[2]", static_cast<int>(gl::TextureBindings::PointShadowMapBase + 2));
                scene->prog.setUniform("uSpotShadow", static_cast<int>(gl::TextureBindings::SpotShadowMapBase));
                scene->prog.setUniform("uShininess", 32.f);
                gl::ShaderProgram::unbind();
            }

            scene->cameraUbo.bind(gl::UboBindings::CameraBlock);
            scene->ambientUbo.bind(gl::UboBindings::AmbientLightBlock);
            scene->cubeFaceUbo.bind(gl::UboBindings::ShadowMatricesBlock);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.f;
            ambient.intensity = 0.06f;
            scene->ambientUbo.upload(ambient.toGpuData());

            scene->orbitCamera.distance = 12.f;
            scene->orbitCamera.elevation = std::numbers::pi_v<float> / 5.f;
            scene->orbitCamera.target[1] = 0.5f;

            scene->ready = scene->pointDepthProg.isValid() && scene->spotDepthProg.isValid() && scene->prog.isValid() &&
                           scene->markerProg.isValid() && scene->sphereMesh.isValid() && scene->planeMesh.isValid() &&
                           scene->markerMesh.isValid() && scene->spotShadowTex.isValid() &&
                           scene->shadowSampler.isValid();

            for (const auto& c : scene->pointShadowCubes)
            {
                scene->ready = scene->ready && c.isValid();
            }

            if (!scene->ready)
            {
                std::fprintf(stderr, "[punctual-shadow] initialization incomplete, rendering disabled\n");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            scene->time += scene->clock.tick();

            const auto& funcs = gl::Context::current().functions();

            // Build GpuBlock: point lights first (indices 0..kNumPointLights-1), spot last
            gl::PunctualLight::GpuBlock block;

            float pointPos[kNumPointLights][3];
            for (int i = 0; i < kNumPointLights; ++i)
            {
                const float angle =
                    scene->time * 0.5f + (static_cast<float>(i) * 2.f * std::numbers::pi_v<float> / kNumPointLights);
                pointPos[i][0] = kOrbitRadius * std::cos(angle);
                pointPos[i][1] = kOrbitHeight;
                pointPos[i][2] = kOrbitRadius * std::sin(angle);

                block.lights[block.count++] = gl::PointLight::toGpuData(
                    math::Vec3{ pointPos[i][0], pointPos[i][1], pointPos[i][2] },
                    math::Vec3{ kPointColors[i][0], kPointColors[i][1], kPointColors[i][2] },
                    kPointIntensity,
                    kPointRadius,
                    kFarPlane);
            }

            const math::Vec3 spotPos{ 0.f, 6.f, 0.f };
            const math::Vec3 spotDir{ 0.f, -1.f, 0.f };
            block.lights[block.count++] = gl::SpotLight::toGpuData(
                spotPos,
                spotDir,
                math::Vec3{ 1.f, 0.92f, 0.82f }, // warm white
                kSpotIntensity,
                kSpotInner,
                kSpotOuter,
                kSpotRadius);

            scene->lightSsbo.upload(block);
            scene->lightSsbo.bind(gl::SsboBindings::PunctualLightsBlock);

            // Scene objects
            math::Mat4 sphere0 = math::Mat4::identity();

            math::Mat4 t1, t2, s, sphere1, sphere2;
            math::mat4Translate(t1, 2.5f, 0.f, 2.f);
            math::mat4Translate(t2, -2.5f, 0.f, -2.f);
            math::mat4Scale(s, 0.7f, 0.7f, 0.7f);
            math::mat4Mul(sphere1, t1, s);
            math::mat4Mul(sphere2, t2, s);

            math::Mat4 planeS, planeT, planeFinal;
            math::mat4Scale(planeS, 12.f, 1.f, 12.f);
            math::mat4Translate(planeT, 0.f, -1.1f, 0.f);
            math::mat4Mul(planeFinal, planeT, planeS);

            const math::Mat4 objects[] = { sphere0, sphere1, sphere2 };

            // Spot light-space matrix
            math::Mat4 spotView, spotProj, spotLSM;
            math::mat4Perspective(spotProj, kSpotOuter * 2.f + 0.1f, 1.f, 0.5f, 30.f); // fov = 2*outerAngle + margin
            math::mat4LookAt(
                spotView,
                spotPos.x,
                spotPos.y,
                spotPos.z,
                spotPos.x + spotDir.x,
                spotPos.y + spotDir.y,
                spotPos.z + spotDir.z,
                1.f,
                0.f,
                0.f);
            math::mat4Mul(spotLSM, spotProj, spotView);

            // Cube face projection (90 deg, aspect=1)
            math::Mat4 cubeProj;
            math::mat4Perspective(cubeProj, std::numbers::pi_v<float> * 0.5f, 1.f, 0.1f, kFarPlane);

            // Point shadow passes: 1 geometry pass per light, geometry shader
            funcs.glColorMask(false, false, false, false);
            funcs.glEnable(gl::DEPTH_TEST);
            funcs.glDepthMask(true);
            funcs.glDisable(gl::CULL_FACE);
            funcs.glEnable(gl::POLYGON_OFFSET_FILL);
            funcs.glPolygonOffset(2.f, 4.f);
            funcs.glViewport(0, 0, kShadowRes, kShadowRes);

            scene->pointDepthProg.bind();
            scene->pointShadowFbo.bind();

            for (int i = 0; i < kNumPointLights; ++i)
            {
                scene->pointShadowFbo.attachDepthCubemap(scene->pointShadowCubes[i]);
                funcs.glClear(gl::DEPTH_BUFFER_BIT);

                CubeFaceBlock faceBlock{};
                const float lx = pointPos[i][0], ly = pointPos[i][1], lz = pointPos[i][2];
                for (int f = 0; f < 6; ++f)
                {
                    math::Mat4 fv, fl;
                    const float* t = kFaceTargets[f];
                    const float* u = kFaceUps[f];
                    math::mat4LookAt(fv, lx, ly, lz, lx + t[0], ly + t[1], lz + t[2], u[0], u[1], u[2]);
                    math::mat4Mul(fl, cubeProj, fv);
                    std::copy(fl.data(), fl.data() + 16, faceBlock.face[f]);
                }
                scene->cubeFaceUbo.upload(faceBlock);

                scene->pointDepthProg.setUniformVec3("uLightPos", math::Vec3{ lx, ly, lz }.data());
                scene->pointDepthProg.setUniform("uFarPlane", kFarPlane);

                for (const auto& m : objects)
                    drawDepth(scene->sphereMesh, scene->pointDepthProg, m, funcs);
                drawDepth(scene->planeMesh, scene->pointDepthProg, planeFinal, funcs);
            }

            scene->pointShadowFbo.unbind();

            // Spot shadow pass
            scene->spotDepthProg.bind();
            scene->spotShadowFbo.bind();
            funcs.glClear(gl::DEPTH_BUFFER_BIT);

            gl::UniformMat4 spotLSMArr;
            std::copy(spotLSM.data(), spotLSM.data() + 16, spotLSMArr.begin());
            scene->spotDepthProg.setUniformMat4("uLightSpaceMatrix", spotLSMArr.data());

            for (const auto& m : objects)
                drawDepth(scene->sphereMesh, scene->spotDepthProg, m, funcs);
            drawDepth(scene->planeMesh, scene->spotDepthProg, planeFinal, funcs);

            scene->spotShadowFbo.unbind();

            funcs.glDisable(gl::POLYGON_OFFSET_FILL);
            funcs.glColorMask(true, true, true, true);
            funcs.glEnable(gl::CULL_FACE);
            funcs.glFrontFace(gl::CCW);

            // Main color pass
            const float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            scene->cameraUbo.upload(scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f));

            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.03f, 0.03f, 0.05f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            for (int i = 0; i < kNumPointLights; ++i)
            {
                scene->pointShadowCubes[i].bind(gl::TextureBindings::PointShadowMapBase + i);
                scene->shadowSampler.bind(gl::TextureBindings::PointShadowMapBase + i);
            }
            scene->spotShadowTex.bind(gl::TextureBindings::SpotShadowMapBase);
            scene->shadowSampler.bind(gl::TextureBindings::SpotShadowMapBase);

            scene->prog.bind();
            scene->prog.setUniformMat4("uSpotLSM", spotLSMArr.data());

            const math::Vec3 diffuseColors[] = {
                { 0.8f, 0.8f, 0.85f }, // sphere 0: grey
                { 0.9f, 0.5f, 0.2f },  // sphere 1: orange
                { 0.3f, 0.6f, 0.9f }   // sphere 2: blue
            };

            for (int i = 0; i < 3; ++i)
            {
                scene->prog.setUniformVec3("uDiffuse", diffuseColors[i].data());
                drawMesh(scene->sphereMesh, scene->prog, objects[i], funcs);
            }

            {
                scene->prog.setUniformVec3("uDiffuse", kPlaneDiffuse);
                funcs.glDisable(gl::CULL_FACE);
                drawMesh(scene->planeMesh, scene->prog, planeFinal, funcs);
                funcs.glEnable(gl::CULL_FACE);
            }

            gl::ShaderProgram::unbind();

            for (int i = 0; i < kNumPointLights; ++i)
            {
                gl::TextureCube::unbind(gl::TextureBindings::PointShadowMapBase + i);
                gl::Sampler::unbind(gl::TextureBindings::PointShadowMapBase + i);
            }
            gl::Texture2D::unbind(gl::TextureBindings::SpotShadowMapBase);
            gl::Sampler::unbind(gl::TextureBindings::SpotShadowMapBase);

            // Light markers
            scene->markerProg.bind();
            for (int i = 0; i < block.count; ++i)
            {
                const float* pos = block.lights[i].position;
                const float* col = block.lights[i].colorIntensity;

                math::Mat4 mT, mS, mFinal;
                math::mat4Translate(mT, pos[0], pos[1], pos[2]);
                math::mat4Scale(mS, 0.1f, 0.1f, 0.1f);
                math::mat4Mul(mFinal, mT, mS);

                gl::UniformMat4 mArr;
                std::copy(mFinal.data(), mFinal.data() + 16, mArr.begin());
                scene->markerProg.setUniformMat4("uModel", mArr.data());
                scene->markerProg.setUniformVec3("uColor", math::Vec3{ col[0], col[1], col[2] }.data());

                scene->markerMesh.bind();
                const auto idx =
                    scene->markerMesh.indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
                funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(scene->markerMesh.indexCount()), idx, nullptr);
                scene->markerMesh.unbind();
            }
            gl::ShaderProgram::unbind();
        },

        // onShutdown
        [&] { scene.reset(); },

        // onMouseMove
        [&](int x, int y) {
            if (!scene)
                return;
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
