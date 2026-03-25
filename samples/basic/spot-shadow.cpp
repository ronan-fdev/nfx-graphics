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
// Depth pass: renders scene depth from each spot light's point of view
static const char* s_depthVertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;

    uniform mat4 uLightSpaceMatrix;
    uniform mat4 uModel;

    void main()
    {
        gl_Position = uLightSpaceMatrix * uModel * vec4(aPosition, 1.0);
    }
)glsl";

static const char* s_depthFragSrc = R"glsl(
    #version 450 core
    void main() {}
)glsl";

// Main pass: Blinn-Phong + directional light + 3 spot lights with PCF shadow
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

    layout(std140, binding = 3) uniform SpotLightSpaceBlock {
        mat4 lsm[3];
    } spotSpace;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec4 vFragPosLS[3];

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position   = camera.viewProj * worldPos;
        vFragPosWS    = worldPos.xyz;
        vNormalWS     = uNormalMatrix * aNormal;
        for(int i = 0; i < 3; ++i)
        {
            vFragPosLS[i] = spotSpace.lsm[i] * worldPos;
        }
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec4 vFragPosLS[3];

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

    // Shared punctual light block: std140 compatible (3 spots packed)
    struct GpuLight {
        vec4 position;      // xyz = pos, w = radius
        vec4 direction;     // xyz = dir, w = type tag
        vec4 colorIntensity;
        vec4 params;        // x = cos(inner), y = cos(outer), z = shadowFarPlane, w = reserved
    };

    layout(std140, binding = 4) uniform SpotLightBlock {
        int  count;
        int  _pad0;
        int  _pad1;
        int  _pad2;
        GpuLight lights[3];
    } spotBlock;

    uniform vec3  uDiffuseColor;
    uniform vec3  uSpecularColor;
    uniform float uShininess;

    uniform sampler2D uShadowMap0;
    uniform sampler2D uShadowMap1;
    uniform sampler2D uShadowMap2;

    float pcf(sampler2D shadowMap, vec4 fragPosLS)
    {
        vec3 proj = fragPosLS.xyz / fragPosLS.w;
        proj = proj * 0.5 + 0.5;

        if(proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
        {
            return 1.0;
        }

        float currentDepth = proj.z;
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, proj.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth > pcfDepth ? 0.0 : 1.0;
            }
        }
        return shadow / 9.0;
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

        // Directional light (Blinn-Phong, no shadow)
        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 H = normalize(L + V);
        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), uShininess);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.w;
        vec3 dirColor     = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;

        vec3 color = ambientColor * uDiffuseColor
                   + diff * dirColor * uDiffuseColor
                   + spec * dirColor * uSpecularColor;

        // Spot lights with PCF shadow
        for(int i = 0; i < spotBlock.count; ++i)
        {
            GpuLight lgt = spotBlock.lights[i];

            vec3 toLight = lgt.position.xyz - vFragPosWS;
            float dist = length(toLight);
            if(dist <= 1e-5)
            {
                continue;
            }

            vec3 Lp = toLight / dist;
            vec3 spotDir = normalize(lgt.direction.xyz);
            float cosTheta  = dot(-Lp, spotDir);
            float cosInner  = lgt.params.x;
            float cosOuter  = lgt.params.y;
            float spotFactor = smoothstep(cosOuter, cosInner, cosTheta);
            if(spotFactor <= 0.0)
            {
                continue;
            }

            float shadow = 1.0;
            if(i == 0) shadow = pcf(uShadowMap0, vFragPosLS[0]);
            else if(i == 1) shadow = pcf(uShadowMap1, vFragPosLS[1]);
            else            shadow = pcf(uShadowMap2, vFragPosLS[2]);

            float radius = lgt.position.w;
            float attenuation;
            if(radius > 0.0)
            {
                float x = clamp(1.0 - dist / radius, 0.0, 1.0);
                attenuation = x * x;
            }
            else
            {
                attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
            }

            vec3 Hs = normalize(Lp + V);
            float spotDiff = max(dot(N, Lp), 0.0);
            float spotSpec = pow(max(dot(N, Hs), 0.0), uShininess);
            vec3 spotColor = lgt.colorIntensity.rgb * lgt.colorIntensity.w;

            color += shadow * spotFactor * attenuation
                   * (spotDiff * spotColor * uDiffuseColor + spotSpec * spotColor * uSpecularColor);
        }

        fragColor = vec4(color, 1.0);
    }
)glsl";

// Unlit shader for light marker cubes
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
    -2.f, 0.f,-2.f,  0, 1, 0,
     2.f, 0.f, 2.f,  0, 1, 0,
     2.f, 0.f,-2.f,  0, 1, 0,
    -2.f, 0.f,-2.f,  0, 1, 0,
    -2.f, 0.f, 2.f,  0, 1, 0,
     2.f, 0.f, 2.f,  0, 1, 0
};
// clang-format on

// Lights
struct SpotLightSpaceUBO
{
    float lsm[3][16];
};

struct SpotLightBlockUBO
{
    int count;
    int _pad[3];
    gl::PunctualLight::GpuData lights[3];
};

static constexpr float kSpotOrbitRadius = 1.5f;
static constexpr float kSpotHeight = 3.0f;
static constexpr float kSpotMarkerScale = 0.07f;
static constexpr float kSpotInnerAngle = 0.20f;
static constexpr float kSpotOuterAngle = 0.32f;
static constexpr float kSpotRadius = 8.0f;
static constexpr float kSpotIntensity = 2.5f;
static constexpr int kShadowRes = 1024;
static constexpr float kShadowNear = 0.5f;
static constexpr float kShadowFar = 20.f;

static void buildSpotLightSpaceMatrix(math::Mat4& out, float px, float py, float pz, float dx, float dy, float dz)
{
    math::Mat4 lightView, lightProj;
    math::mat4LookAt(lightView, px, py, pz, px + dx, py + dy, pz + dz);
    math::mat4Perspective(lightProj, kSpotOuterAngle * 2.5f, 1.0f, kShadowNear, kShadowFar);
    math::mat4Mul(out, lightProj, lightView);
}

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
    gl::UniformBuffer<SpotLightSpaceUBO> spotSpaceUbo;            // binding 3
    gl::UniformBuffer<SpotLightBlockUBO> spotBlockUbo;            // binding 4

    gl::RenderTarget shadowMaps[3];
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
        { "nfx-graphics - spot shadow", 1024, 768, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shaders
            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "spot-shadow: main shader pipeline initialization failed\n");
            }

            scene->depthProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_depthVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_depthFragSrc } });
            if (!scene->depthProg.isValid())
            {
                std::fprintf(stderr, "spot-shadow: depth shader initialization failed\n");
            }

            scene->unlitProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_unlitVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_unlitFragSrc } });
            if (!scene->unlitProg.isValid())
            {
                std::fprintf(stderr, "spot-shadow: unlit shader initialization failed\n");
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

            // Shadow map texture samplers
            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform("uShadowMap0", 4);
                scene->prog.setUniform("uShadowMap1", 5);
                scene->prog.setUniform("uShadowMap2", 6);
                scene->prog.setUniform("uShininess", 64.0f);
                gl::ShaderProgram::unbind();
            }

            // Shadow maps
            for (int i = 0; i < 3; ++i)
            {
                scene->shadowMaps[i] =
                    gl::RenderTarget(gl::RenderTarget::Desc{ .width = kShadowRes,
                                                             .height = kShadowRes,
                                                             .depthOnly = true,
                                                             .depthFormat = gl::Texture2D::InternalFormat::Depth32F });
                if (!scene->shadowMaps[i].texture().isValid())
                {
                    std::fprintf(stderr, "spot-shadow: shadow map %d initialization failed\n", i);
                }
            }

            scene->shadowSampler = gl::Sampler::create({ .minFilter = gl::Sampler::Filter::Nearest,
                                                         .magFilter = gl::Sampler::Filter::Nearest,
                                                         .wrapS = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapT = gl::Sampler::Wrap::ClampToEdge,
                                                         .wrapR = gl::Sampler::Wrap::ClampToEdge,
                                                         .compareMode = gl::Sampler::CompareMode::None });

            // Ambient UBO (binding 1)
            const auto ambGpu = gl::AmbientLight::toGpuData(math::Vec3{ 0.15f, 0.15f, 0.15f }, 1.0f);
            scene->ambientUbo.upload(ambGpu);
            scene->ambientUbo.bind(1);

            // Directional light UBO (binding 2)
            gl::DirectionalLight dirLight{};
            dirLight.color[0] = 0.6f;
            dirLight.color[1] = 0.6f;
            dirLight.color[2] = 0.6f;
            dirLight.intensity = 0.5f;
            const auto dirGpu = dirLight.toGpuData(math::Vec3{ -0.4f, -0.8f, -0.4f });
            scene->dirLightUbo.upload(dirGpu);
            scene->dirLightUbo.bind(2);

            // Spot light space UBO (binding 3)
            scene->spotSpaceUbo.bind(3);

            // Spot light block UBO (binding 4)
            scene->spotBlockUbo.bind(4);

            // Camera UBO (binding 0)
            scene->cameraUbo.bind(0);

            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = 0.f;
            scene->orbitCamera.target[2] = 0.f;
            scene->orbitCamera.distance = 7.f;
            scene->orbitCamera.azimuth = 0.5f;
            scene->orbitCamera.elevation = 0.45f;

            scene->ready = scene->prog.isValid() && scene->depthProg.isValid() && scene->unlitProg.isValid() &&
                           scene->shadowMaps[0].isComplete() && scene->shadowMaps[1].isComplete() &&
                           scene->shadowMaps[2].isComplete() && scene->shadowSampler.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "spot-shadow: initialization incomplete, rendering disabled\n");
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

            // Cube
            math::Mat4 cubeModel;
            math::mat4Translate(cubeModel, 0.f, 0.5001f, 0.f);

            // Plane
            math::Mat4 planeModel;
            math::mat4Translate(planeModel, 0.f, 0.f, 0.f);

            // 3 orbiting spot lights
            gl::SpotLight spots[3];
            float spotPx[3], spotPy[3], spotPz[3];
            float spotDx[3], spotDy[3], spotDz[3];
            for (int i = 0; i < 3; ++i)
            {
                const float phase =
                    scene->time * 0.4f + static_cast<float>(i) * (2.f * static_cast<float>(std::numbers::pi) / 3.f);
                spotPx[i] = std::cos(phase) * kSpotOrbitRadius;
                spotPy[i] = kSpotHeight;
                spotPz[i] = std::sin(phase) * kSpotOrbitRadius;

                // Direction: from light position toward scene center
                const float dx = -spotPx[i];
                const float dy = -spotPy[i] * 0.8f;
                const float dz = -spotPz[i];
                const float len = std::sqrt(dx * dx + dy * dy + dz * dz);
                spotDx[i] = dx / len;
                spotDy[i] = dy / len;
                spotDz[i] = dz / len;

                const float r = (i == 0) ? 1.0f : 0.08f;
                const float g = (i == 1) ? 1.0f : 0.08f;
                const float b = (i == 2) ? 1.0f : 0.08f;

                spots[i] = gl::SpotLight::create(
                    spotPx[i],
                    spotPy[i],
                    spotPz[i],
                    spotDx[i],
                    spotDy[i],
                    spotDz[i],
                    r,
                    g,
                    b,
                    kSpotIntensity,
                    kSpotInnerAngle,
                    kSpotOuterAngle,
                    kSpotRadius);
            }

            // Build light space matrices and spot block UBO
            math::Mat4 lsm[3];
            SpotLightSpaceUBO spotSpaceData{};
            SpotLightBlockUBO spotBlockData{};
            spotBlockData.count = 3;
            for (int i = 0; i < 3; ++i)
            {
                buildSpotLightSpaceMatrix(lsm[i], spotPx[i], spotPy[i], spotPz[i], spotDx[i], spotDy[i], spotDz[i]);
                for (int j = 0; j < 16; ++j)
                {
                    spotSpaceData.lsm[i][j] = lsm[i].data()[j];
                }
                spotBlockData.lights[i] = spots[i].toGpuData();
            }
            scene->spotSpaceUbo.upload(spotSpaceData);
            scene->spotSpaceUbo.bind(3);
            scene->spotBlockUbo.upload(spotBlockData);
            scene->spotBlockUbo.bind(4);

            // Depth passes
            scene->depthProg.bind();
            funcs.glColorMask(false, false, false, false);
            funcs.glEnable(gl::POLYGON_OFFSET_FILL);
            funcs.glPolygonOffset(2.0f, 4.0f);

            for (int i = 0; i < 3; ++i)
            {
                scene->shadowMaps[i].bind();
                funcs.glViewport(0, 0, kShadowRes, kShadowRes);
                funcs.glClear(gl::DEPTH_BUFFER_BIT);

                scene->depthProg.setUniformMat4("uLightSpaceMatrix", lsm[i].data());

                // Cube
                scene->depthProg.setUniformMat4("uModel", cubeModel.data());
                scene->cubeVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);

                // Floor  (no face culling)
                funcs.glDisable(gl::CULL_FACE);
                scene->depthProg.setUniformMat4("uModel", planeModel.data());
                scene->planeVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 6);

                scene->shadowMaps[i].unbind();
            }

            funcs.glDisable(gl::POLYGON_OFFSET_FILL);
            funcs.glColorMask(true, true, true, true);

            // Color pass
            const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);
            scene->cameraUbo.bind(0);

            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.05f, 0.06f, 0.10f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            // Bind shadow maps to texture units 4, 5, 6
            for (int i = 0; i < 3; ++i)
            {
                scene->shadowMaps[i].texture().bind(4 + i);
                scene->shadowSampler.bind(4 + i);
            }

            scene->prog.bind();
            const math::Vec3 specColor{ 1.0f, 1.0f, 1.0f };
            scene->prog.setUniformVec3("uSpecularColor", specColor.data());

            // Cube
            {
                const math::Vec3 diffuse{ 0.95f, 0.55f, 0.25f };
                scene->prog.setUniformVec3("uDiffuseColor", diffuse.data());
                scene->prog.setUniformMat4("uModel", cubeModel.data());
                math::Mat3 n;
                math::mat3InverseTranspose(n, cubeModel);
                scene->prog.setUniformMat3("uNormalMatrix", n.data());
                scene->cubeVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
            }

            // Floor
            {
                const math::Vec3 diffuse{ 0.35f, 0.40f, 0.45f };
                scene->prog.setUniformVec3("uDiffuseColor", diffuse.data());
                scene->prog.setUniformVec3("uSpecularColor", specColor.data());
                funcs.glDisable(gl::CULL_FACE);
                scene->planeVao.bind();

                scene->prog.setUniformMat4("uModel", planeModel.data());
                math::Mat3 nf;
                math::mat3InverseTranspose(nf, planeModel);
                scene->prog.setUniformMat3("uNormalMatrix", nf.data());
                funcs.glDrawArrays(gl::TRIANGLES, 0, 6);
            }

            // Spot light markers (unlit)
            scene->unlitProg.bind();
            for (int i = 0; i < 3; ++i)
            {
                math::Mat4 markerTrans, markerScale, markerModel;
                math::mat4Translate(markerTrans, spotPx[i], spotPy[i], spotPz[i]);
                math::mat4Scale(markerScale, kSpotMarkerScale, kSpotMarkerScale, kSpotMarkerScale);
                math::mat4Mul(markerModel, markerTrans, markerScale);
                scene->unlitProg.setUniformMat4("uModel", markerModel.data());

                const float r = (i == 0) ? 1.0f : 0.08f;
                const float g = (i == 1) ? 1.0f : 0.08f;
                const float b = (i == 2) ? 1.0f : 0.08f;
                const math::Vec3 emissive{ r, g, b };
                scene->unlitProg.setUniformVec3("uEmissiveColor", emissive.data());

                scene->markerVao.bind();
                funcs.glDrawArrays(gl::TRIANGLES, 0, 36);
            }
            scene->markerVao.unbind();

            for (int i = 0; i < 3; ++i)
            {
                gl::Sampler::unbind(4 + i);
                gl::Texture2D::unbind(4 + i);
            }
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
