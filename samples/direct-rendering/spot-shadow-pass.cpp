#include "app/App.h"

#include <nfx/Graphics.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <optional>
#include <string_view>

static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec2 vUV;

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

    void main()
    {
        vec4 worldPos = uModel * vec4(aPosition, 1.0);
        gl_Position = camera.viewProj * worldPos;
        vFragPosWS = worldPos.xyz;
        vNormalWS = uNormalMatrix * aNormal;
        vUV = aUV;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec2 vUV;

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

    uniform sampler2D uDiffuseMap;
    uniform int       uUseDiffuseMap;
    uniform vec3      uDiffuseColor;
    uniform vec3      uSpecularColor;
    uniform float     uShininess;

    layout(std140, binding = 3) uniform ShadowMatricesBlock {
        mat4 dirLightSpace;
        mat4 spotLightSpace[4];
        ivec4 shadowInfo;
    } shadowMatrices;

    uniform int uSpotCount;

    layout(binding = 8) uniform sampler2D uSpotShadowMaps[4];
    uniform vec3      uSpotPos0;
    uniform vec3      uSpotPos1;
    uniform vec3      uSpotPos2;
    uniform vec3      uSpotDir0;
    uniform vec3      uSpotDir1;
    uniform vec3      uSpotDir2;
    uniform vec3      uSpotColor0;
    uniform vec3      uSpotColor1;
    uniform vec3      uSpotColor2;
    uniform float     uSpotInner0;
    uniform float     uSpotInner1;
    uniform float     uSpotInner2;
    uniform float     uSpotOuter0;
    uniform float     uSpotOuter1;
    uniform float     uSpotOuter2;

    float pcfSpot(int idx, vec2 uv, float depth)
    {
        float shadow = 0.0;
        vec2 texelSize;
        if (idx == 0)
        {
            texelSize = 1.0 / textureSize(uSpotShadowMaps[0], 0);
        }
        else if (idx == 1)
        {
            texelSize = 1.0 / textureSize(uSpotShadowMaps[1], 0);
        }
        else if (idx == 2)
        {
            texelSize = 1.0 / textureSize(uSpotShadowMaps[2], 0);
        }
        else
        {
            texelSize = 1.0 / textureSize(uSpotShadowMaps[3], 0);
        }

        for(int x = -1; x <= 1; ++x)
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth;
                if (idx == 0)
                    pcfDepth = texture(uSpotShadowMaps[0], uv + vec2(x, y) * texelSize).r;
                else if (idx == 1)
                    pcfDepth = texture(uSpotShadowMaps[1], uv + vec2(x, y) * texelSize).r;
                else if (idx == 2)
                    pcfDepth = texture(uSpotShadowMaps[2], uv + vec2(x, y) * texelSize).r;
                else
                    pcfDepth = texture(uSpotShadowMaps[3], uv + vec2(x, y) * texelSize).r;

                shadow += depth > pcfDepth ? 0.0 : 1.0;
            }

        return shadow / 9.0;
    }

    float spotShadow(int idx)
    {
        vec4 fragPosLS = shadowMatrices.spotLightSpace[idx] * vec4(vFragPosWS, 1.0);
        vec3 proj = fragPosLS.xyz / fragPosLS.w;
        proj = proj * 0.5 + 0.5;

        if(proj.z < 0.0 || proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
            return 1.0;

        return pcfSpot(idx, proj.xy, proj.z);
    }

    vec3 blinnPhongSpot(vec3 N, vec3 base, vec3 spotPos, vec3 spotDir,
                        vec3 spotColor, float innerAngle, float outerAngle, int shadowIdx)
    {
        vec3 L = normalize(spotPos - vFragPosWS);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        // Cone attenuation
        float cosOuter = cos(outerAngle);
        float cosInner = cos(innerAngle);
        float cosTheta = dot(L, normalize(-spotDir));
        float cone = clamp((cosTheta - cosOuter) / max(cosInner - cosOuter, 1e-4), 0.0, 1.0);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), uShininess);
        float shadow = (shadowIdx < shadowMatrices.shadowInfo.x) ? spotShadow(shadowIdx) : 1.0;

        return cone * shadow * (diff * spotColor * base + spec * spotColor * uSpecularColor);
    }

    void main()
    {
        vec3 N = normalize(vNormalWS);
        if(!gl_FrontFacing) N = -N;

        vec3 base = (uUseDiffuseMap != 0) ? texture(uDiffuseMap, vUV).rgb : uDiffuseColor;
        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;

        vec3 color = ambientColor * base;

        if(uSpotCount > 0)
            color += blinnPhongSpot(N, base, uSpotPos0, uSpotDir0, uSpotColor0,
                                    uSpotInner0, uSpotOuter0, 0);
        if(uSpotCount > 1)
            color += blinnPhongSpot(N, base, uSpotPos1, uSpotDir1, uSpotColor1,
                                    uSpotInner1, uSpotOuter1, 1);
        if(uSpotCount > 2)
            color += blinnPhongSpot(N, base, uSpotPos2, uSpotDir2, uSpotColor2,
                                    uSpotInner2, uSpotOuter2, 2);

        fragColor = vec4(color, 1.0);
    }
)glsl";

static const char* s_markerVertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec3 aPosition;

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
        gl_Position = camera.viewProj * (uModel * vec4(aPosition, 1.0));
    }
)glsl";

static const char* s_markerFragSrc = R"glsl(
    #version 450 core

    uniform vec3 uColor;
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(uColor, 1.0);
    }
)glsl";

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kRockY = 5.10f;
    constexpr float kRockScale = 0.52f;

    constexpr int kSpotCount = 3;
    constexpr int kShadowResolution = 1024;
    constexpr float kSpotOrbitRadius = 5.5f;
    constexpr float kSpotHeight = 9.5f;
    constexpr float kSpotOrbitSpeed = 0.22f;
    constexpr float kSpotInnerAngle = 0.35f; // ~20 deg
    constexpr float kSpotOuterAngle = 0.62f; // ~35 deg
    constexpr float kSpotFar = 30.0f;
    constexpr float kSpotRadius = 24.0f;
    constexpr float kSpotIntensity = 2.8f;
    constexpr float kMarkerScale = 0.36f;
    // RGB spot colors
    constexpr float kSpotColors[kSpotCount][3] = { { 1.0f, 0.30f, 0.30f },
                                                   { 0.30f, 1.0f, 0.30f },
                                                   { 0.30f, 0.55f, 1.0f } };

    static_assert(kSpotCount == 3, "spot-shadow-pass sample currently supports exactly 3 spot lights");
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
    gl::SpotShadowPass* shadowPass = nullptr;
    gl::GeometryPass* geometryPass = nullptr;
    gl::GridPass* gridPass = nullptr;
    gl::AxesPass* axesPass = nullptr;
    gl::PresentPass* presentPass = nullptr;

    gl::ShaderHandle shaderHandle;
    gl::ShaderHandle markerShaderHandle;
    gl::MeshHandle rockHandle;
    gl::MeshHandle markerSphereHandle;

    gl::MaterialHandle rockMaterial;
    gl::MaterialHandle floorMaterial;
    std::array<gl::MaterialHandle, kSpotCount> markerMaterials{};

    gl::Texture2DHandle rockDiffuseHandle;
    gl::Texture2DHandle terrainDiffuseHandle;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    float time = 0.0f;
    smp::Clock clock;

    bool ready = false;
};

// Sets a named spot uniform on both rock and floor materials
static void setSpotUniforms(Scene& scene, int idx, const gl::SpotLight& spot)
{
    char posName[32], dirName[32], colorName[32], innerName[32], outerName[32];
    std::snprintf(posName, sizeof(posName), "uSpotPos%d", idx);
    std::snprintf(dirName, sizeof(dirName), "uSpotDir%d", idx);
    std::snprintf(colorName, sizeof(colorName), "uSpotColor%d", idx);
    std::snprintf(innerName, sizeof(innerName), "uSpotInner%d", idx);
    std::snprintf(outerName, sizeof(outerName), "uSpotOuter%d", idx);

    const gl::UniformVec3 pos{ spot.position[0], spot.position[1], spot.position[2] };
    const gl::UniformVec3 dir{ spot.direction[0], spot.direction[1], spot.direction[2] };
    const gl::UniformVec3 col{ kSpotColors[idx][0] * kSpotIntensity,
                               kSpotColors[idx][1] * kSpotIntensity,
                               kSpotColors[idx][2] * kSpotIntensity };

    for (gl::MaterialHandle h : { scene.rockMaterial, scene.floorMaterial })
    {
        if (gl::Material* m = scene.materialCache.get(h))
        {
            m->setUniform(posName, pos);
            m->setUniform(dirName, dir);
            m->setUniform(colorName, col);
            m->setUniform(innerName, spot.innerAngle);
            m->setUniform(outerName, spot.outerAngle);
        }
    }
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - spot-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "spot-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "spot-shadow-pass: ObjLoader failed\n");
                return;
            }

            scene->rockHandle = scene->meshCache.create(*meshData);
            scene->markerSphereHandle = scene->meshCache.create(gl::Primitive::uvSphere());

            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            scene->markerShaderHandle =
                scene->shaderCache.compile({ { gl::ShaderProgram::Stage::Vertex, s_markerVertSrc },
                                             { gl::ShaderProgram::Stage::Fragment, s_markerFragSrc } });

            if (!scene->rockHandle.isValid() || !scene->markerSphereHandle.isValid() ||
                !scene->shaderHandle.isValid() || !scene->markerShaderHandle.isValid())
            {
                std::fprintf(stderr, "spot-shadow-pass: failed to create mesh or shader(s)\n");
                return;
            }

            scene->rockDiffuseHandle =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", true, true));
            scene->terrainDiffuseHandle = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));

            scene->rockMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());

            gl::RenderState floorState = gl::RenderState::opaque();
            floorState.cullFace = false;
            scene->floorMaterial = scene->materialCache.create(scene->shaderHandle, floorState);

            auto setupMat = [&](gl::MaterialHandle h, gl::Texture2DHandle diffuse) {
                if (gl::Material* m = scene->materialCache.get(h))
                {
                    m->setUniform("uUseDiffuseMap", diffuse.isValid() ? 1 : 0);
                    m->setUniform("uDiffuseColor", gl::UniformVec3{ 0.75f, 0.75f, 0.75f });
                    m->setUniform("uSpecularColor", gl::UniformVec3{ 0.25f, 0.25f, 0.25f });
                    m->setUniform("uShininess", 16.0f);
                    m->setUniform("uSpotCount", kSpotCount);
                    if (diffuse.isValid())
                    {
                        m->setTexture("uDiffuseMap", diffuse);
                    }
                }
            };
            setupMat(scene->rockMaterial, scene->rockDiffuseHandle);
            setupMat(scene->floorMaterial, scene->terrainDiffuseHandle);

            if (gl::Material* m = scene->materialCache.get(scene->floorMaterial))
            {
                m->setUniform("uDiffuseColor", gl::UniformVec3{ 0.35f, 0.35f, 0.35f });
                m->setUniform("uSpecularColor", gl::UniformVec3{ 0.03f, 0.03f, 0.03f });
                m->setUniform("uShininess", 3.0f);
            }

            for (int i = 0; i < kSpotCount; ++i)
            {
                scene->markerMaterials[i] =
                    scene->materialCache.create(scene->markerShaderHandle, gl::RenderState::opaque());
                if (gl::Material* m = scene->materialCache.get(scene->markerMaterials[i]))
                {
                    m->setUniform(
                        "uColor",
                        gl::UniformVec3{
                            kSpotColors[i][0] * 1.2f, kSpotColors[i][1] * 1.2f, kSpotColors[i][2] * 1.2f });
                }
            }

            // Shadow pass first, then geometry
            scene->shadowPass = scene->renderer.createPass<gl::SpotShadowPass>("SpotShadow");
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
            scene->geometryPass->setClearColor(true, 0.02f, 0.02f, 0.04f, 1.0f);
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

            scene->orbitCamera.distance = 22.0f;
            scene->orbitCamera.elevation = 0.60f;
            scene->orbitCamera.target[1] = 0.45f;

            scene->ready = scene->rockHandle.isValid() && scene->markerSphereHandle.isValid() &&
                           scene->shaderHandle.isValid() && scene->markerShaderHandle.isValid() &&
                           scene->rockDiffuseHandle.isValid() && scene->terrainDiffuseHandle.isValid() &&
                           scene->rockMaterial.isValid() && scene->floorMaterial.isValid() &&
                           scene->shadowPass != nullptr && scene->geometryPass != nullptr &&
                           scene->gridPass != nullptr && scene->axesPass != nullptr && scene->presentPass != nullptr &&
                           scene->renderResources.has_value() && scene->shadowPass->shadowMaps()[0].texture.isValid() &&
                           scene->shadowPass->shadowMaps()[1].texture.isValid() &&
                           scene->shadowPass->shadowMaps()[2].texture.isValid();
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
            ambient.intensity = 0.1f;
            frame.ambientLight = ambient.toGpuData();

            {
                gl::DirectionalLight directional;
                directional.intensity = 0.01f;
                frame.directionalLight = directional.toGpuData(std::array<float, 3>{ 0.f, -1.f, 0.f }.data());
            }

            scene->time += scene->clock.tick();

            scene->geometryPass->clearQueue();

            // Register orbiting spot lights and update per-frame uniforms
            const float spotAngleStep = (2.0f * std::numbers::pi_v<float>) / static_cast<float>(kSpotCount);
            for (int i = 0; i < kSpotCount; ++i)
            {
                const float a = scene->time * kSpotOrbitSpeed + static_cast<float>(i) * spotAngleStep;
                const float px = std::cos(a) * kSpotOrbitRadius;
                const float pz = std::sin(a) * kSpotOrbitRadius;
                const float py = kSpotHeight;

                // Direction from light position to the levitating center rock
                const float dx = -px;
                const float dy = kRockY - py;
                const float dz = -pz;

                const gl::SpotLight spot = gl::SpotLight::create(
                    px,
                    py,
                    pz,
                    dx,
                    dy,
                    dz,
                    kSpotColors[i][0],
                    kSpotColors[i][1],
                    kSpotColors[i][2],
                    kSpotIntensity,
                    kSpotInnerAngle,
                    kSpotOuterAngle,
                    kSpotRadius,
                    kSpotFar);

                scene->shadowPass->addLight(spot);

                setSpotUniforms(*scene, i, spot);

                // Marker sphere for this spot light
                gl::RenderCommand markerCmd;
                markerCmd.mesh = scene->markerSphereHandle;
                markerCmd.material = scene->markerMaterials[i];
                markerCmd.sortKey = 10 + static_cast<std::uint64_t>(i);
                {
                    math::Mat4 s, t;
                    math::mat4Scale(s, kMarkerScale, kMarkerScale, kMarkerScale);
                    math::mat4Translate(t, px, py, pz);
                    math::mat4Mul(markerCmd.transform, t, s);
                }
                scene->geometryPass->submit(markerCmd);
            }

            frame.spotShadowCount = kSpotCount;
            const auto& spotMaps = scene->shadowPass->shadowMaps();
            for (int i = 0; i < kSpotCount; ++i)
            {
                frame.spotShadowMaps[i] = spotMaps[i];
            }

            // Floor
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = 5;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, 8.5f, 2.4f, 8.5f);
                math::mat4Translate(t, 0.0f, -2.15f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->geometryPass->submit(floorCmd);

            // Single levitating center rock
            {
                gl::RenderCommand rockCmd;
                rockCmd.mesh = scene->rockHandle;
                rockCmd.material = scene->rockMaterial;
                rockCmd.sortKey = 40;

                math::Mat4 s, t;
                math::mat4Scale(s, kRockScale, kRockScale, kRockScale);
                math::mat4Translate(t, 0.0f, kRockY, 0.0f);
                math::mat4Mul(rockCmd.transform, t, s);

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
