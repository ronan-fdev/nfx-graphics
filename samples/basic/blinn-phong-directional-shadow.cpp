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

    layout(std140, binding = 0) uniform CameraBlock {
        mat4 view;
        mat4 proj;
        mat4 viewProj;
        vec3 position;
        float _pad0;
        vec3 direction;
        float _pad1;
    } camera;

    layout(std140, binding = 3) uniform LightSpaceBlock {
        mat4 lightSpaceMatrix;
    } lightSpace;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec4 vFragPosLS;

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position   = camera.viewProj * worldPos;

        vFragPosWS    = worldPos.xyz;
        vNormalWS     = uNormalMatrix * aNormal;
        vFragPosLS    = lightSpace.lightSpaceMatrix * worldPos;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vNormalWS;
    in vec3 vFragPosWS;
    in vec4 vFragPosLS;

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

    uniform sampler2D uShadowMap;

    float shadowFactor(vec4 fragPosLS)
    {
        vec3 proj = fragPosLS.xyz / fragPosLS.w;
        proj = proj * 0.5 + 0.5;

        if(proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
        {
            return 1.0;
        }

        float currentDepth = proj.z;

        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(uShadowMap, proj.xy + vec2(x, y) * texelSize).r;
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
            // Keep plane visible from below without reusing front-face lighting orientation
            N = -N;
        }
        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff   = max(dot(N, L), 0.0);
        float spec   = pow(max(dot(N, H), 0.0), uShininess);
        float shadow = shadowFactor(vFragPosLS);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.w;
        vec3 lightColor   = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;

        vec3 color = ambientColor * uDiffuseColor
                + shadow * diff * lightColor * uDiffuseColor
                + shadow * spec * lightColor * uSpecularColor;

        fragColor = vec4(color, 1.0);
    }
)glsl";

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
//   pos               normals
    -2.f, 0.f,-2.f,    0, 1, 0,
     2.f, 0.f, 2.f,    0, 1, 0,
     2.f, 0.f,-2.f,    0, 1, 0,
    -2.f, 0.f,-2.f,    0, 1, 0,
    -2.f, 0.f, 2.f,    0, 1, 0,
     2.f, 0.f, 2.f,    0, 1, 0
};
// clang-format on

// Scene
struct Scene
{
    gl::ShaderProgram prog;
    gl::ShaderProgram depthProg;

    gl::Buffer cubeVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray cubeVao;
    gl::Buffer planeVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray planeVao;

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;             // binding 0
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;      // binding 1
    gl::UniformBuffer<gl::DirectionalLight::GpuData> dirLightUbo; // binding 2
    gl::UniformBuffer<math::Mat4> lightSpaceUbo;                  // binding 3

    gl::RenderTarget shadowMap;
    gl::Sampler shadowSampler;

    math::Vec3 lightDir{ -0.4f, -0.8f, -0.4f };

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

static void buildLightSpaceMatrix(math::Mat4& out, const math::Vec3& lightDir)
{
    constexpr math::Vec3 target{ 0.f, 0.f, 0.f };
    constexpr float sceneRadius = 6.f;
    constexpr float shadowNear = 1.f;
    constexpr float shadowFar = 25.f;

    const math::Vec3 dir = math::vec3normalize(lightDir);
    const math::Vec3 lightPos{ target.x - dir.x * 10.f, target.y - dir.y * 10.f, target.z - dir.z * 10.f };

    math::Mat4 lightView;
    math::Mat4 lightProj;
    math::mat4LookAt(lightView, lightPos.x, lightPos.y, lightPos.z, target.x, target.y, target.z);
    math::mat4Ortho(lightProj, -sceneRadius, sceneRadius, -sceneRadius, sceneRadius, shadowNear, shadowFar);
    math::mat4Mul(out, lightProj, lightView);
}

int main()
{
    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - blinn-phong-directional-shadow", 1024, 768, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shader
            scene->prog = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->prog.isValid())
            {
                std::fprintf(stderr, "blinn-phong-directional-shadow shader pipeline initialization failed\n");
            }

            scene->depthProg =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_depthVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_depthFragSrc } });
            if (!scene->depthProg.isValid())
            {
                std::fprintf(stderr, "blinn-phong-directional-shadow: depth shader initialization failed\n");
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

            // Materials
            if (scene->prog.isValid())
            {
                scene->prog.bind();
                scene->prog.setUniform("uShininess", 64.0f);
                scene->prog.setUniform("uShadowMap", 3);
                gl::ShaderProgram::unbind();
            }

            // Shadow map: depth-only 2048x2048
            scene->shadowMap =
                gl::RenderTarget(gl::RenderTarget::Desc{ .width = 2048,
                                                         .height = 2048,
                                                         .depthOnly = true,
                                                         .depthFormat = gl::Texture2D::InternalFormat::Depth32F });
            if (!scene->shadowMap.texture().isValid())
            {
                std::fprintf(stderr, "blinn-phong-directional-shadow: shadow map initialization failed\n");
            }

            // Shadow sampler: nearest + clamp -> raw depth for manual PCF in shader
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
            const gl::DirectionalLight dirLight{};
            const auto dirGpu = dirLight.toGpuData(math::vec3normalize(scene->lightDir));
            scene->dirLightUbo.upload(dirGpu);
            scene->dirLightUbo.bind(2);

            // Light space UBO (binding 3): data filled each frame
            scene->lightSpaceUbo.bind(3);

            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = 0.f;
            scene->orbitCamera.target[2] = 0.f;
            scene->orbitCamera.distance = 7.f;
            scene->orbitCamera.azimuth = 0.5f;
            scene->orbitCamera.elevation = 0.45f;

            scene->ready = scene->prog.isValid() && scene->depthProg.isValid() && scene->shadowMap.isValid() &&
                           scene->shadowMap.isComplete() && scene->shadowMap.texture().isValid() &&
                           scene->shadowSampler.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "blinn-phong-directional-shadow: initialization incomplete, rendering disabled\n");
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
            scene->angle += 0.8f * dt;

            // Cube
            math::Mat4 rot, trans, cubeModel;
            math::mat4RotateY(rot, scene->angle);
            math::mat4Translate(trans, 0.f, 0.5f, 0.f);
            math::mat4Mul(cubeModel, trans, rot);

            // Plane (slight offset to avoid Z-fighting with cube)
            math::Mat4 planeModel;
            math::mat4Translate(planeModel, 0.f, -0.001f, 0.f);

            // Light space matrix
            math::Mat4 lightSpaceMatrix;
            buildLightSpaceMatrix(lightSpaceMatrix, scene->lightDir);
            scene->lightSpaceUbo.upload(lightSpaceMatrix);
            scene->lightSpaceUbo.bind(3);

            // Depth pass
            scene->shadowMap.bind();
            funcs.glViewport(0, 0, 2048, 2048);
            funcs.glClear(gl::DEPTH_BUFFER_BIT);
            funcs.glEnable(gl::POLYGON_OFFSET_FILL);
            funcs.glPolygonOffset(2.0f, 4.0f);
            funcs.glColorMask(false, false, false, false);

            scene->depthProg.bind();
            scene->depthProg.setUniformMat4("uLightSpaceMatrix", lightSpaceMatrix.data());

            scene->depthProg.setUniformMat4("uModel", cubeModel.data());
            scene->cubeVao.bind();
            funcs.glDrawArrays(gl::TRIANGLES, 0, 36);

            funcs.glDisable(gl::CULL_FACE);
            scene->depthProg.setUniformMat4("uModel", planeModel.data());
            scene->planeVao.bind();
            funcs.glDrawArrays(gl::TRIANGLES, 0, 6);
            scene->planeVao.unbind();
            funcs.glEnable(gl::CULL_FACE);

            funcs.glColorMask(true, true, true, true);
            funcs.glDisable(gl::POLYGON_OFFSET_FILL);

            scene->shadowMap.unbind();

            // Color pass
            const float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.785f, aspect, 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);
            scene->cameraUbo.bind(0);

            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            scene->shadowMap.texture().bind(3);
            scene->shadowSampler.bind(3);

            scene->prog.bind();

            const math::Vec3 specularColor{ 1.0f, 1.0f, 1.0f };
            scene->prog.setUniformVec3("uSpecularColor", specularColor.data());

            // Cube
            const math::Vec3 cubeDiffuse{ 0.95f, 0.55f, 0.25f };
            scene->prog.setUniformVec3("uDiffuseColor", cubeDiffuse.data());
            scene->prog.setUniformMat4("uModel", cubeModel.data());
            {
                math::Mat3 n;
                math::mat3InverseTranspose(n, cubeModel);
                scene->prog.setUniformMat3("uNormalMatrix", n.data());
            }
            scene->cubeVao.bind();
            funcs.glDrawArrays(gl::TRIANGLES, 0, 36);

            // Plane
            const math::Vec3 planeDiffuse{ 0.35f, 0.40f, 0.45f };
            scene->prog.setUniformVec3("uDiffuseColor", planeDiffuse.data());
            scene->prog.setUniformMat4("uModel", planeModel.data());
            {
                math::Mat3 n;
                math::mat3InverseTranspose(n, planeModel);
                scene->prog.setUniformMat3("uNormalMatrix", n.data());
            }
            funcs.glDisable(gl::CULL_FACE);
            scene->planeVao.bind();
            funcs.glDrawArrays(gl::TRIANGLES, 0, 6);
            scene->planeVao.unbind();
            funcs.glEnable(gl::CULL_FACE);

            gl::Sampler::unbind(3);
            gl::Texture2D::unbind(3);
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
