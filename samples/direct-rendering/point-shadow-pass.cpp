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

    uniform vec3      uPointPos;
    uniform vec3      uPointColor;
    uniform float     uPointIntensity;
    uniform float     uPointRadius;
    uniform float     uPointFarPlane;
    uniform float     uShadowBiasMin;
    uniform float     uShadowBiasMax;
    uniform float     uShadowDiskRadius;

    layout(std140, binding = 3) uniform ShadowMatricesBlock {
        mat4 dirLightSpace;
        mat4 spotLightSpace[4];
        ivec4 shadowInfo;
    } shadowMatrices;

    layout(binding = 4) uniform samplerCube uPointShadowMaps[4];

    // 20-tap PCF on cube shadow map for soft omnidirectional shadows
    float pointShadowPCF(vec3 fragPosWS, vec3 N)
    {
        if (shadowMatrices.shadowInfo.y <= 0)
        {
            return 1.0;
        }

        vec3 toLight = fragPosWS - uPointPos;
        float currentDepth = length(toLight) / uPointFarPlane;

        // Normal-scaled bias to avoid acne on rough geometry
        vec3 L = normalize(-toLight);
        float cosTheta = max(dot(N, L), 0.0);
        float bias = mix(uShadowBiasMax, uShadowBiasMin, cosTheta);

        float diskRadius = uShadowDiskRadius * (1.0 + 0.5 * currentDepth);
        const vec3 offsets[20] = vec3[](
            vec3( 1, 1, 1), vec3( 1,-1, 1), vec3(-1,-1, 1), vec3(-1, 1, 1),
            vec3( 1, 1,-1), vec3( 1,-1,-1), vec3(-1,-1,-1), vec3(-1, 1,-1),
            vec3( 1, 1, 0), vec3( 1,-1, 0), vec3(-1,-1, 0), vec3(-1, 1, 0),
            vec3( 1, 0, 1), vec3(-1, 0, 1), vec3( 1, 0,-1), vec3(-1, 0,-1),
            vec3( 0, 1, 1), vec3( 0,-1, 1), vec3( 0,-1,-1), vec3( 0, 1,-1)
        );

        float shadow = 0.0;
        for(int i = 0; i < 20; ++i)
        {
            float closest = texture(uPointShadowMaps[0], toLight + offsets[i] * diskRadius).r;
            shadow += (currentDepth - bias) > closest ? 0.0 : 1.0;
        }
        return shadow / 20.0;
    }

    void main()
    {
        vec3 N = normalize(vNormalWS);
        if(!gl_FrontFacing) N = -N;

        vec3 base = (uUseDiffuseMap != 0) ? texture(uDiffuseMap, vUV).rgb : uDiffuseColor;
        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;

        vec3 color = ambientColor * base;

        vec3 toPoint = uPointPos - vFragPosWS;
        float dist = length(toPoint);
        if(dist > 1e-5)
        {
            vec3 L = toPoint / dist;
            vec3 V = normalize(camera.position - vFragPosWS);
            vec3 H = normalize(L + V);

            float diff = max(dot(N, L), 0.0);
            float spec = pow(max(dot(N, H), 0.0), uShininess);
            float shadow = pointShadowPCF(vFragPosWS, N);

            float atten = 1.0;
            if(uPointRadius > 0.0)
            {
                float x = clamp(1.0 - dist / uPointRadius, 0.0, 1.0);
                atten = x * x;
            }

            vec3 lightColor = uPointColor * uPointIntensity;
            color += shadow * atten * (diff * lightColor * base + spec * lightColor * uSpecularColor);
        }

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
    constexpr float kRockY = 1.8f;
    constexpr float kRockScale = 0.72f;

    constexpr int kShadowResolution = 1024;
    constexpr float kPointOrbitRadius = 4.0f;
    constexpr float kPointHeight = 3.5f;
    constexpr float kPointOrbitSpeed = 0.20f;
    constexpr float kPointFar = 20.0f;
    constexpr float kPointRadius = 12.0f;
    constexpr float kPointIntensity = 6.0f;
    constexpr float kMarkerScale = 0.22f;

    // Warm incandescent white
    constexpr float kPointColor[3] = { 1.0f, 0.82f, 0.55f };
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
    gl::PointShadowPass* shadowPass = nullptr;
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
    gl::MaterialHandle markerMaterial;

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

static void setPointUniforms(Scene& scene, const gl::PointLight& point)
{
    const gl::UniformVec3 pos{ point.position[0], point.position[1], point.position[2] };
    const gl::UniformVec3 col{ point.color[0], point.color[1], point.color[2] };

    for (gl::MaterialHandle h : { scene.rockMaterial, scene.floorMaterial })
    {
        if (gl::Material* m = scene.materialCache.get(h))
        {
            m->setUniform("uPointPos", pos);
            m->setUniform("uPointColor", col);
            m->setUniform("uPointIntensity", point.intensity);
            m->setUniform("uPointRadius", point.radius);
            m->setUniform("uPointFarPlane", (point.shadowFarPlane > 0.f) ? point.shadowFarPlane : kPointFar);
        }
    }
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - point-shadow-pass", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "point-shadow-pass: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "point-shadow-pass: ObjLoader failed\n");
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
                std::fprintf(stderr, "point-shadow-pass: failed to create mesh or shader(s)\n");
                return;
            }

            scene->rockDiffuseHandle =
                scene->texture2DCache.add(smp::loadEmbeddedTexture("obj/rock/rock.png", true, true));
            scene->terrainDiffuseHandle = scene->texture2DCache.add(
                smp::loadEmbeddedTexture("rocky_terrain_1k/rocky_terrain_diff_1k.jpg", true, true));

            scene->rockMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());

            scene->floorMaterial = scene->materialCache.create(scene->shaderHandle, gl::RenderState::opaque());

            scene->markerMaterial = scene->materialCache.create(scene->markerShaderHandle, gl::RenderState::opaque());
            if (gl::Material* marker = scene->materialCache.get(scene->markerMaterial))
            {
                marker->setUniform("uColor", gl::UniformVec3{ 1.2f, 1.15f, 1.0f });
            }

            auto setupMat = [&](gl::MaterialHandle h, gl::Texture2DHandle diffuse) {
                if (gl::Material* m = scene->materialCache.get(h))
                {
                    m->setUniform("uUseDiffuseMap", diffuse.isValid() ? 1 : 0);
                    m->setUniform("uDiffuseColor", gl::UniformVec3{ 0.75f, 0.75f, 0.75f });
                    m->setUniform("uSpecularColor", gl::UniformVec3{ 0.25f, 0.25f, 0.25f });
                    m->setUniform("uShininess", 16.0f);
                    m->setUniform("uPointColor", gl::UniformVec3{ kPointColor[0], kPointColor[1], kPointColor[2] });
                    m->setUniform("uPointIntensity", kPointIntensity);
                    m->setUniform("uPointRadius", kPointRadius);
                    m->setUniform("uPointFarPlane", kPointFar);
                    m->setUniform("uShadowBiasMin", 0.01f);
                    m->setUniform("uShadowBiasMax", 0.06f);
                    m->setUniform("uShadowDiskRadius", 0.04f);
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

            // Shadow pass first, then geometry
            scene->shadowPass = scene->renderer.createPass<gl::PointShadowPass>("PointShadow");
            scene->geometryPass = scene->renderer.createPass<gl::GeometryPass>("Geometry");
            scene->gridPass = scene->renderer.createPass<gl::GridPass>("Grid");
            scene->axesPass = scene->renderer.createPass<gl::AxesPass>("Axes");
            scene->presentPass = scene->renderer.createPass<gl::PresentPass>("Present");

            scene->shadowPass->setResolution(scene->textureCubeCache, kShadowResolution);

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

            scene->orbitCamera.distance = 10.0f;
            scene->orbitCamera.elevation = 0.55f;
            scene->orbitCamera.target[1] = 1.2f;

            scene->ready = scene->rockHandle.isValid() && scene->markerSphereHandle.isValid() &&
                           scene->shaderHandle.isValid() && scene->markerShaderHandle.isValid() &&
                           scene->rockDiffuseHandle.isValid() && scene->terrainDiffuseHandle.isValid() &&
                           scene->rockMaterial.isValid() && scene->floorMaterial.isValid() &&
                           scene->shadowPass != nullptr && scene->geometryPass != nullptr &&
                           scene->presentPass != nullptr && scene->renderResources.has_value() &&
                           scene->shadowPass->shadowMaps()[0].texture.isValid();
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
            ambient.intensity = 0.13f;
            frame.ambientLight = ambient.toGpuData();

            {
                gl::DirectionalLight directional;
                directional.intensity = 0.01f;
                frame.directionalLight = directional.toGpuData(std::array<float, 3>{ 0.f, -1.f, 0.f }.data());
            }

            scene->time += scene->clock.tick();
            scene->geometryPass->clearQueue();

            const float a = scene->time * kPointOrbitSpeed;
            const float px = std::cos(a) * kPointOrbitRadius;
            const float pz = std::sin(a) * kPointOrbitRadius;
            const float py = kPointHeight;

            const gl::PointLight point = gl::PointLight::create(
                px, py, pz, kPointColor[0], kPointColor[1], kPointColor[2], kPointIntensity, kPointRadius, kPointFar);

            scene->shadowPass->addLight(point);
            setPointUniforms(*scene, point);

            const auto& maps = scene->shadowPass->shadowMaps();
            frame.pointShadowCount = maps[0].texture.isValid() ? 1 : 0;
            frame.pointShadowMaps[0] = maps[0];

            // Marker sphere for point light
            gl::RenderCommand markerCmd;
            markerCmd.mesh = scene->markerSphereHandle;
            markerCmd.material = scene->markerMaterial;
            markerCmd.sortKey = 10;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, kMarkerScale, kMarkerScale, kMarkerScale);
                math::mat4Translate(t, px, py, pz);
                math::mat4Mul(markerCmd.transform, t, s);
            }
            scene->geometryPass->submit(markerCmd);

            // Floor: rock mesh scaled flat for omnidirectional shadow reception
            gl::RenderCommand floorCmd;
            floorCmd.mesh = scene->rockHandle;
            floorCmd.material = scene->floorMaterial;
            floorCmd.sortKey = 20;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, 9.0f, 1.0f, 9.0f);
                math::mat4Translate(t, 0.0f, 0.0f, 0.0f);
                math::mat4Mul(floorCmd.transform, t, s);
            }
            scene->geometryPass->submit(floorCmd);

            // Single levitating center rock
            gl::RenderCommand rockCmd;
            rockCmd.mesh = scene->rockHandle;
            rockCmd.material = scene->rockMaterial;
            rockCmd.sortKey = 40;
            {
                math::Mat4 s, t;
                math::mat4Scale(s, kRockScale, kRockScale, kRockScale);
                math::mat4Translate(t, 0.0f, kRockY, 0.0f);
                math::mat4Mul(rockCmd.transform, t, s);
            }
            scene->geometryPass->submit(rockCmd);
            scene->shadowPass->submit(rockCmd);

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
