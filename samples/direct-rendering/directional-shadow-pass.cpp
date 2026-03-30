#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>
#include <random>
#include <string_view>

static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec2 vUV;
    out vec4 vFragPosLS;

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

    layout(std140, binding = 3) uniform ShadowMatricesBlock {
        mat4 dirLightSpace;
        mat4 spotLightSpace[4];
        ivec4 shadowInfo;
    } shadowMatrices;

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position = camera.viewProj * worldPos;
        vFragPosWS = worldPos.xyz;
        vNormalWS = uNormalMatrix * aNormal;
        vUV = aUV;
        vFragPosLS = shadowMatrices.dirLightSpace * worldPos;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec2 vUV;
    in vec4 vFragPosLS;

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

    layout(std140, binding = 3) uniform ShadowMatricesBlock {
        mat4 dirLightSpace;
        mat4 spotLightSpace[4];
        ivec4 shadowInfo;
    } shadowMatrices;

    uniform sampler2D uDiffuseMap;
    uniform int uUseDiffuseMap;
    uniform vec3 uDiffuseColor;
    uniform vec3 uSpecularColor;
    uniform float uShininess;
    layout(binding = 12) uniform sampler2D uShadowMap;

    float shadowFactor(vec4 fragPosLS)
    {
        vec3 proj = fragPosLS.xyz / fragPosLS.w;
        proj = proj * 0.5 + 0.5;

        if(proj.z < 0.0 || proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
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

    void main()
    {
        vec3 N = normalize(vNormalWS);
        if(!gl_FrontFacing) N = -N;

        vec3 base = (uUseDiffuseMap != 0) ? texture(uDiffuseMap, vUV).rgb : uDiffuseColor;

        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff   = max(dot(N, L), 0.0);
        float spec   = pow(max(dot(N, H), 0.0), uShininess);
        float shadow = (shadowMatrices.shadowInfo.z != 0) ? shadowFactor(vFragPosLS) : 1.0;

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;
        vec3 lightColor   = dirLight.colorIntensity.rgb * dirLight.colorIntensity.a;

        vec3 color = ambientColor * base
                   + shadow * diff * lightColor * base
                   + shadow * spec * lightColor * uSpecularColor;
        fragColor = vec4(color, 1.0);
    }
)glsl";

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr int kRockCount = 8;
    constexpr float kRockRingRadius = 4.6f;
    constexpr float kRockOrbitSpeed = 0.45f;
    constexpr float kRockBobSpeed = 1.7f;
    constexpr float kRockAngleStep = (2.0f * std::numbers::pi_v<float>) / static_cast<float>(kRockCount);
    constexpr float kRockBaseY = 5.10f;
    constexpr float kRockBobAmplitude = 0.20f;
    constexpr int kShadowResolution = 2048;
    constexpr float kShadowSceneRadius = 8.0f;
    constexpr float kShadowNear = 1.0f;
    constexpr float kShadowFar = 30.0f;
    constexpr float kLightDir[3] = { -0.35f, -0.75f, -0.40f };
} // namespace

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
    gl::DirectionalShadowPass* shadowPass = nullptr;
    gl::GeometryPass* geometryPass = nullptr;
    gl::GridPass* gridPass = nullptr;
    gl::AxesPass* axesPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::ShaderHandle shaderHandle;
    gl::MeshHandle rockHandle;

    gl::MaterialHandle rockMaterial;
    gl::MaterialHandle floorMaterial;

    gl::Texture2DHandle rockDiffuseHandle;
    gl::Texture2DHandle terrainDiffuseHandle;

    gl::OrbitCamera orbitCamera;

    std::vector<math::Vec3> rockSpinAxes;
    std::vector<float> rockSpinSpeeds;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float time = 0.0f;
    smp::Clock clock;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - directional-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "directional-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "directional-shadow-pass: ObjLoader failed\n");
                return;
            }

            scene->rockHandle = scene->meshCache.create(*meshData);

            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            if (!scene->rockHandle.isValid() || !scene->shaderHandle.isValid())
            {
                std::fprintf(stderr, "directional-shadow-pass: failed to create mesh or shader\n");
                return;
            }

            scene->rockDiffuseHandle =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", true, true));
            scene->terrainDiffuseHandle = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));

            scene->rockMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());

            gl::RenderState floorState = gl::RenderState::opaque();
            floorState.cullFace = false; // visible from below
            scene->floorMaterial = scene->materialCache.create(scene->shaderHandle, floorState);

            // uShadowMap is wired after renderer.initialize() once the depth texture is allocated
            if (gl::Material* rockMat = scene->materialCache.get(scene->rockMaterial))
            {
                rockMat->setUniform("uUseDiffuseMap", scene->rockDiffuseHandle.isValid() ? 1 : 0);
                rockMat->setUniform("uDiffuseColor", gl::UniformVec3{ 0.75f, 0.75f, 0.75f });
                rockMat->setUniform("uSpecularColor", gl::UniformVec3{ 0.25f, 0.25f, 0.25f });
                rockMat->setUniform("uShininess", 12.0f);
                if (scene->rockDiffuseHandle.isValid())
                {
                    rockMat->setTexture("uDiffuseMap", scene->rockDiffuseHandle);
                }
            }

            if (gl::Material* floorMat = scene->materialCache.get(scene->floorMaterial))
            {
                floorMat->setUniform("uUseDiffuseMap", scene->terrainDiffuseHandle.isValid() ? 1 : 0);
                floorMat->setUniform("uDiffuseColor", gl::UniformVec3{ 0.35f, 0.35f, 0.35f });
                floorMat->setUniform("uSpecularColor", gl::UniformVec3{ 0.03f, 0.03f, 0.03f });
                floorMat->setUniform("uShininess", 3.0f);
                if (scene->terrainDiffuseHandle.isValid())
                {
                    floorMat->setTexture("uDiffuseMap", scene->terrainDiffuseHandle);
                }
            }

            // Shadow pass must come first so it executes before the geometry pass
            scene->shadowPass = scene->renderer.createPass<gl::DirectionalShadowPass>("Shadow");
            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->gridPass = scene->renderer.createPass<gl::GridPass>("Grid");
            scene->axesPass = scene->renderer.createPass<gl::AxesPass>("Axes");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->shadowPass->setResolution(scene->texture2DCache, kShadowResolution, kShadowResolution);

            scene->renderResources.emplace(gl::RenderResources{ scene->meshCache,
                                                                scene->materialCache,
                                                                scene->shaderCache,
                                                                scene->texture2DCache,
                                                                scene->textureCubeCache,
                                                                scene->samplerCache });
            scene->renderer.initialize(*scene->renderResources);

            scene->geometryPass->setOutputSize(scene->texture2DCache, 1280, 720);
            scene->geometryPass->setClearColor(true, 0.08f, 0.10f, 0.14f, 1.0f);
            scene->geometryPass->setClearDepth(true, 1.0f);
            scene->geometryPass->setOrder(gl::RenderQueue::Order::BySortKey);

            scene->gridPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->gridPass->setGridSize(1.0f);
            scene->gridPass->setFadeDistance(90.0f);
            scene->axesPass->setTargetTextures(scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
            scene->axesPass->setAxisLength(500.0f);
            scene->axesPass->setFadeDistance(90.0f);

            scene->presentPass->setInput(scene->geometryPass->colorOutput());
            scene->presentPass->setTonemapEnabled(true);
            scene->presentPass->setGammaEnabled(true);

            scene->orbitCamera.distance = 14.0f;
            scene->orbitCamera.elevation = 0.50f;
            scene->orbitCamera.target[1] = 0.35f;

            // Generate random spin axes and speeds for each rock
            std::mt19937 rng(std::random_device{}());
            std::uniform_real_distribution<float> axisDist(-1.0f, 1.0f);
            std::uniform_real_distribution<float> speedDist(0.5f, 2.5f);
            scene->rockSpinAxes.resize(kRockCount);
            scene->rockSpinSpeeds.resize(kRockCount);
            for (int i = 0; i < kRockCount; ++i)
            {
                float x = axisDist(rng);
                float y = axisDist(rng);
                float z = axisDist(rng);
                float len = std::sqrt(x * x + y * y + z * z);
                if (len > 0.0f)
                {
                    scene->rockSpinAxes[i] = math::Vec3{ x / len, y / len, z / len };
                }
                else
                {
                    scene->rockSpinAxes[i] = math::Vec3{ 0.0f, 1.0f, 0.0f };
                }
                scene->rockSpinSpeeds[i] = speedDist(rng);
            }

            scene->ready = scene->rockHandle.isValid() && scene->shaderHandle.isValid() &&
                           scene->rockDiffuseHandle.isValid() && scene->terrainDiffuseHandle.isValid() &&
                           scene->rockMaterial.isValid() && scene->floorMaterial.isValid() &&
                           scene->shadowPass != nullptr && scene->geometryPass != nullptr &&
                           scene->gridPass != nullptr && scene->axesPass != nullptr && scene->presentPass != nullptr &&
                           scene->renderResources.has_value() && scene->shadowPass->depthOutput().isValid();
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
                scene->gridPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->axesPass->setTargetTextures(
                    scene->geometryPass->colorOutput(), scene->geometryPass->depthOutput());
                scene->presentPass->setInput(scene->geometryPass->colorOutput());
            }

            gl::FrameData frame;
            frame.camera =
                scene->orbitCamera.toGpuData(0.9f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 500.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.12f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight directional;
            directional.color[0] = directional.color[1] = directional.color[2] = 1.0f;
            directional.intensity = 1.0f;
            frame.directionalLight = directional.toGpuData(kLightDir);

            // Build light-space matrix for the directional shadow pass
            math::Mat4 lightSpaceMat;
            gl::DirectionalShadowPass::buildLightSpaceMatrix(
                lightSpaceMat.data(), kLightDir, 0.0f, 0.0f, 0.0f, kShadowSceneRadius, kShadowNear, kShadowFar);
            scene->shadowPass->setLightSpaceMatrix(lightSpaceMat.data());
            frame.hasDirShadow = true;
            frame.dirShadowMap = scene->shadowPass->shadowMap();

            // shadowPass queue is cleared automatically at end() after each frame
            scene->geometryPass->clearQueue();

            scene->time += scene->clock.tick();

            // Floor
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = 5;
            {
                math::Mat4 s;
                math::Mat4 t;
                math::mat4Scale(s, 8.5f, 2.4f, 8.5f);
                math::mat4Translate(t, 0.0f, -2.15f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->geometryPass->submit(floorCmd);

            for (int i = 0; i < kRockCount; ++i)
            {
                const float a = scene->time * kRockOrbitSpeed + static_cast<float>(i) * kRockAngleStep;
                const float x = std::cos(a) * kRockRingRadius;
                const float z = std::sin(a) * kRockRingRadius;
                const float y =
                    kRockBaseY + kRockBobAmplitude * std::sin(scene->time * kRockBobSpeed + static_cast<float>(i));

                gl::RenderCommand rockCmd;
                rockCmd.mesh = scene->rockHandle;
                rockCmd.material = scene->rockMaterial;
                rockCmd.sortKey = 20 + static_cast<std::uint64_t>(i);

                math::Mat4 s;
                math::Mat4 r;
                math::Mat4 rSpin;
                math::Mat4 t;
                math::Mat4 rs;
                math::mat4Scale(s, 0.42f, 0.42f, 0.42f);
                math::mat4RotateY(r, -a * 1.3f);
                // Apply individual spin rotation around random axis using quaternions
                const auto& axis = scene->rockSpinAxes[i];
                float spinAngle = scene->time * scene->rockSpinSpeeds[i];
                math::Quat spinQuat = math::quatAngleAxis(spinAngle, axis.x, axis.y, axis.z);
                math::quatToMat4(spinQuat, rSpin);
                math::mat4Mul(rs, r, rSpin);
                math::Mat4 rss;
                math::mat4Mul(rss, rs, s);
                math::mat4Translate(t, x, y, z);
                math::mat4Mul(rockCmd.transform, t, rss);

                scene->geometryPass->submit(rockCmd);
                scene->shadowPass->submit(rockCmd);
            }

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
