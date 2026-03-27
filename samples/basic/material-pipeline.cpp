#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

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

    layout(std140, binding = 1) uniform AmbientBlock {
        vec4 colorIntensity;
    } ambient;

    layout(std140, binding = 2) uniform DirectionalLightBlock {
        vec4 direction;      // w unused
        vec4 colorIntensity;
    } dirLight;

    layout(std140, binding = 16) uniform MaterialBlock {
        vec4 baseColor_alpha; // rgb = diffuse tint  , a = alpha
        vec4 specColor_shine; // rgb = specular color, w = shininess
    } material;

    uniform sampler2D uDiffuseMap;
    uniform sampler2D uNormalMap;

    uniform int uHasDiffuse; // 1 when a diffuse texture is bound
    uniform int uHasNormal;  // 1 when a normal map is bound

    void main()
    {
        vec3 N;
        if(uHasNormal == 1)
        {
            vec3 nmap = texture(uNormalMap, vUV).rgb * 2.0 - 1.0;
            N = normalize(vTBN * nmap);
        }
        else
        {
            N = normalize(vTBN[2]); // geometry normal
        }

        vec3 diffuse = (uHasDiffuse == 1)
            ? texture(uDiffuseMap, vUV).rgb * material.baseColor_alpha.rgb
            : material.baseColor_alpha.rgb;
        vec3 L       = normalize(-dirLight.direction.xyz);
        vec3 V       = normalize(camera.position - vFragPosWS);
        vec3 H       = normalize(L + V);
        float diff   = max(dot(N, L), 0.0);
        float spec   = pow(max(dot(N, H), 0.0), material.specColor_shine.w);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;
        vec3 lightColor   = dirLight.colorIntensity.rgb * dirLight.colorIntensity.a;

        vec3 color = ambientColor * diffuse
                   + diff * lightColor * diffuse
                   + spec * lightColor * material.specColor_shine.rgb;

        fragColor = vec4(color, material.baseColor_alpha.a);
    }
)glsl";

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::Texture2DCache textureCache;
    gl::MaterialCache materialCache;

    gl::ShaderHandle shaderHandle;

    // Meshes
    gl::MeshHandle cubeHandle;
    gl::MeshHandle sphereHandle;
    gl::MeshHandle quadHandle;

    // Textures
    gl::Texture2DHandle toyboxDiffuseHandle;
    gl::Texture2DHandle toyboxNormalHandle;
    gl::Texture2DHandle brickDiffuseHandle;
    gl::Texture2DHandle brickNormalHandle;

    // Materials: one per object, same shader, different block data and textures
    gl::MaterialHandle cubeMaterial;   // toybox     + white tint + shininess 64
    gl::MaterialHandle sphereMaterial; // brickwall  + white tint + shininess 128
    gl::MaterialHandle quadMaterial;   // no texture + red tint   + shininess 256

    gl::UniformBuffer<gl::Camera::GpuData> cameraUbo;
    gl::UniformBuffer<gl::AmbientLight::GpuData> ambientUbo;
    gl::UniformBuffer<gl::DirectionalLight::GpuData> dirLightUbo;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    bool ready = false;
};

static void drawObject(
    gl::Mesh* mesh,
    gl::Material* mat,
    const math::Mat4& model,
    gl::ShaderCache& shaderCache,
    gl::Texture2DCache& textureCache,
    const gl::Functions& funcs)
{
    gl::UniformMat4 modelArr;
    std::copy(model.data(), model.data() + 16, modelArr.begin());
    mat->setUniform("uModel", modelArr);
    mat->bind(shaderCache, textureCache);

    mesh->bind();
    const auto idxType = mesh->indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
    funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(mesh->indexCount()), idxType, nullptr);
    mesh->unbind();
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - material pipeline", 1100, 700, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            // Shader
            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            // Meshes
            scene->cubeHandle = scene->meshCache.create(gl::Primitive::cube());
            scene->sphereHandle = scene->meshCache.create(gl::Primitive::uvSphere(32, 16));
            scene->quadHandle = scene->meshCache.create(gl::Primitive::plane());

            // Textures
            scene->toyboxDiffuseHandle =
                scene->textureCache.add(smp::loadEmbeddedTexture("toybox/toy_box_diffuse.png"));
            scene->toyboxNormalHandle = scene->textureCache.add(smp::loadEmbeddedTexture("toybox/toy_box_normal.png"));
            scene->brickDiffuseHandle = scene->textureCache.add(smp::loadEmbeddedTexture("brickwall/brickwall.jpg"));
            scene->brickNormalHandle =
                scene->textureCache.add(smp::loadEmbeddedTexture("brickwall/brickwall_normal.jpg"));

            // Materials
            gl::RenderState opaqueState; // depthTest=true, cullBack, CCW - all defaults

            // Cube
            scene->cubeMaterial = scene->materialCache.create(scene->shaderHandle, opaqueState);
            if (gl::Material* mat = scene->materialCache.get(scene->cubeMaterial))
            {
                mat->setTexture("uDiffuseMap", scene->toyboxDiffuseHandle);
                mat->setTexture("uNormalMap", scene->toyboxNormalHandle);
                mat->setUniform("uHasDiffuse", 1);
                mat->setUniform("uHasNormal", 1);
                gl::MaterialBlockData block;
                block.specColor_shine[3] = 8.f;
                mat->setMaterialBlock(block);
            }

            // Sphere
            scene->sphereMaterial = scene->materialCache.create(scene->shaderHandle, opaqueState);
            if (gl::Material* mat = scene->materialCache.get(scene->sphereMaterial))
            {
                mat->setTexture("uDiffuseMap", scene->brickDiffuseHandle);
                mat->setTexture("uNormalMap", scene->brickNormalHandle);
                mat->setUniform("uHasDiffuse", 1);
                mat->setUniform("uHasNormal", 1);
                gl::MaterialBlockData block;
                block.specColor_shine[3] = 32.f;
                mat->setMaterialBlock(block);
            }

            // Quad
            gl::RenderState quadState;
            quadState.cullFace = false;
            scene->quadMaterial = scene->materialCache.create(scene->shaderHandle, quadState);
            if (gl::Material* mat = scene->materialCache.get(scene->quadMaterial))
            {
                mat->setUniform("uHasDiffuse", 0);
                mat->setUniform("uHasNormal", 0);
                gl::MaterialBlockData block;
                block.baseColor_alpha[0] = 1.0f; // bright red
                block.baseColor_alpha[1] = 0.25f;
                block.baseColor_alpha[2] = 0.25f;
                block.specColor_shine[0] = block.specColor_shine[1] = block.specColor_shine[2] = 1.f;
                block.specColor_shine[3] = 16.f;
                mat->setMaterialBlock(block);
            }

            // UBOs
            scene->cameraUbo.bind(gl::UboBindings::CameraBlock);
            scene->ambientUbo.bind(gl::UboBindings::AmbientLightBlock);
            scene->dirLightUbo.bind(gl::UboBindings::DirectionalLightBlock);

            constexpr float kLightDir[3] = { -0.3f, -0.5f, -0.8f };
            gl::DirectionalLight dirLight;
            dirLight.color[0] = dirLight.color[1] = dirLight.color[2] = 1.f;
            dirLight.intensity = 1.2f;
            scene->dirLightUbo.upload(dirLight.toGpuData(kLightDir));

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.f;
            ambient.intensity = 0.45f;
            scene->ambientUbo.upload(ambient.toGpuData());

            scene->orbitCamera.distance = 7.f;
            scene->orbitCamera.target[1] = 0.3f;

            scene->ready = scene->shaderHandle.isValid() && scene->cubeHandle.isValid() &&
                           scene->sphereHandle.isValid() && scene->quadHandle.isValid() &&
                           scene->cubeMaterial.isValid() && scene->sphereMaterial.isValid() &&
                           scene->quadMaterial.isValid();

            if (!scene->ready)
            {
                std::fprintf(stderr, "[material-pipeline] initialization incomplete, rendering disabled\n");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const auto& funcs = gl::Context::current().functions();
            funcs.glViewport(0, 0, width, height);
            funcs.glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
            funcs.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            const auto gpuCam = scene->orbitCamera.toGpuData(
                0.785f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f);
            scene->cameraUbo.upload(gpuCam);

            // Left: cube (toybox)
            {
                math::Mat4 model;
                math::mat4Translate(model, -2.8f, 0.f, 0.f);
                drawObject(
                    scene->meshCache.get(scene->cubeHandle),
                    scene->materialCache.get(scene->cubeMaterial),
                    model,
                    scene->shaderCache,
                    scene->textureCache,
                    funcs);
            }

            // Center: sphere (brickwall)
            {
                math::Mat4 model;
                math::mat4Translate(model, 0.f, 0.f, 0.f);
                drawObject(
                    scene->meshCache.get(scene->sphereHandle),
                    scene->materialCache.get(scene->sphereMaterial),
                    model,
                    scene->shaderCache,
                    scene->textureCache,
                    funcs);
            }

            // Right: quad (red, no texture)
            {
                math::Mat4 model;
                math::mat4Translate(model, 2.8f, 0.f, 0.f);
                drawObject(
                    scene->meshCache.get(scene->quadHandle),
                    scene->materialCache.get(scene->quadMaterial),
                    model,
                    scene->shaderCache,
                    scene->textureCache,
                    funcs);
            }
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
