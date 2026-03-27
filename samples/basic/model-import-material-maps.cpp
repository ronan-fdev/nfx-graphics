#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>
#include <string_view>

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
        vec4 direction;
        vec4 colorIntensity;
    } dirLight;

    layout(std140, binding = 16) uniform MaterialBlock {
        vec4 baseColor_alpha;
        vec4 specColor_shine;
    } material;

    uniform sampler2D uDiffuseMap;
    uniform sampler2D uNormalMap;
    uniform sampler2D uSpecularMap;

    uniform int uUseDiffuseMap;
    uniform int uUseNormalMap;
    uniform int uUseSpecularMap;

    uniform vec3  uDiffuseColor;
    uniform vec3  uSpecularColor;

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
            N = normalize(vTBN[2]);
        }

        if(!gl_FrontFacing)
        {
            N = -N;
        }

        vec3 base = (uUseDiffuseMap != 0)
            ? texture(uDiffuseMap, vUV).rgb * material.baseColor_alpha.rgb
            : uDiffuseColor * material.baseColor_alpha.rgb;
        vec3 specColor = (uUseSpecularMap != 0)
            ? texture(uSpecularMap, vUV).rgb * material.specColor_shine.rgb
            : uSpecularColor * material.specColor_shine.rgb;

        vec3 L = normalize(-dirLight.direction.xyz);
        vec3 V = normalize(camera.position - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), material.specColor_shine.w);

        vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.a;
        vec3 lightColor = dirLight.colorIntensity.rgb * dirLight.colorIntensity.a;

        vec3 color = ambientColor * base
                   + diff * lightColor * base
                   + spec * lightColor * specColor;

        fragColor = vec4(color, 1.0);
    }
)glsl";

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::Texture2DCache textureCache;
    gl::MaterialCache materialCache;

    gl::ShaderHandle shaderHandle;
    gl::MeshHandle meshHandle;
    gl::Texture2DHandle diffuseHandle;
    gl::Texture2DHandle normalHandle;
    gl::Texture2DHandle specularHandle;
    gl::MaterialHandle materialHandle;

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
    gl::Material* material,
    const math::Mat4& model,
    gl::ShaderCache& shaderCache,
    gl::Texture2DCache& textureCache,
    const gl::Functions& funcs)
{
    if (!mesh || !material)
    {
        return;
    }

    material->setUniformMat4("uModel", model.data());
    material->bind(shaderCache, textureCache);

    mesh->bind();
    const auto idxType = mesh->indexType() == gl::MeshIndexType::UInt16 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT;
    funcs.glDrawElements(gl::TRIANGLES, static_cast<GLsizei>(mesh->indexCount()), idxType, nullptr);
    mesh->unbind();
}

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - model import + material maps", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/backpack/backpack.obj");
            if (!objRes)
            {
                std::fprintf(
                    stderr, "model-import-material-maps: embedded object not found: obj/backpack/backpack.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "model-import-material-maps: ObjLoader failed\n");
                return;
            }

            scene->meshHandle = scene->meshCache.create(*meshData);
            if (!scene->meshHandle.isValid())
            {
                std::fprintf(stderr, "model-import-material-maps: mesh creation failed\n");
                return;
            }

            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->shaderHandle.isValid())
            {
                std::fprintf(stderr, "model-import-material-maps: shader pipeline initialization failed\n");
                return;
            }

            if (auto tex = smp::loadEmbeddedTexture("obj/backpack/diffuse.jpg", false); tex.isValid())
            {
                scene->diffuseHandle = scene->textureCache.add(std::move(tex));
            }
            if (auto tex = smp::loadEmbeddedTexture("obj/backpack/normal.png", false); tex.isValid())
            {
                scene->normalHandle = scene->textureCache.add(std::move(tex));
            }
            if (auto tex = smp::loadEmbeddedTexture("obj/backpack/specular.jpg", false); tex.isValid())
            {
                scene->specularHandle = scene->textureCache.add(std::move(tex));
            }

            scene->cameraUbo.bind(gl::UboBindings::CameraBlock);
            scene->ambientUbo.bind(gl::UboBindings::AmbientLightBlock);
            scene->dirLightUbo.bind(gl::UboBindings::DirectionalLightBlock);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.12f;
            scene->ambientUbo.upload(ambient.toGpuData());

            gl::DirectionalLight dirLight;
            dirLight.color[0] = dirLight.color[1] = dirLight.color[2] = 1.0f;
            dirLight.intensity = 1.0f;
            scene->dirLightUbo.upload(dirLight.toGpuData(math::Vec3{ -0.2f, -0.5f, -0.8f }));

            gl::RenderState opaqueState;
            scene->materialHandle = scene->materialCache.create(scene->shaderHandle, opaqueState);
            if (gl::Material* material = scene->materialCache.get(scene->materialHandle))
            {
                if (scene->diffuseHandle.isValid())
                {
                    material->setTexture("uDiffuseMap", scene->diffuseHandle);
                }
                if (scene->normalHandle.isValid())
                {
                    material->setTexture("uNormalMap", scene->normalHandle);
                }
                if (scene->specularHandle.isValid())
                {
                    material->setTexture("uSpecularMap", scene->specularHandle);
                }

                material->setUniform("uUseDiffuseMap", scene->diffuseHandle.isValid() ? 1 : 0);
                material->setUniform("uUseNormalMap", scene->normalHandle.isValid() ? 1 : 0);
                material->setUniform("uUseSpecularMap", scene->specularHandle.isValid() ? 1 : 0);
                material->setUniformVec3("uDiffuseColor", gl::UniformVec3{ 0.75f, 0.75f, 0.75f }.data());
                material->setUniformVec3("uSpecularColor", gl::UniformVec3{ 0.35f, 0.35f, 0.35f }.data());

                gl::MaterialBlockData block;
                block.baseColor_alpha[0] = 1.0f;
                block.baseColor_alpha[1] = 1.0f;
                block.baseColor_alpha[2] = 1.0f;
                block.specColor_shine[0] = 1.0f;
                block.specColor_shine[1] = 1.0f;
                block.specColor_shine[2] = 1.0f;
                block.specColor_shine[3] = 32.0f;
                material->setMaterialBlock(block);
            }

            scene->orbitCamera.target[0] = 0.0f;
            scene->orbitCamera.target[1] = 0.5f;
            scene->orbitCamera.target[2] = 0.0f;
            scene->orbitCamera.distance = 5.5f;
            scene->orbitCamera.azimuth = 0.5f;
            scene->orbitCamera.elevation = 0.35f;

            scene->ready = scene->shaderHandle.isValid() && scene->meshHandle.isValid() &&
                           scene->materialHandle.isValid() && scene->diffuseHandle.isValid() &&
                           scene->normalHandle.isValid() && scene->specularHandle.isValid();
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

            const float aspect = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            const auto gpuCam = scene->orbitCamera.toGpuData(0.9f, aspect, 0.1f, 100.0f);
            scene->cameraUbo.upload(gpuCam);

            math::Mat4 model = math::Mat4::identity();

            drawObject(
                scene->meshCache.get(scene->meshHandle),
                scene->materialCache.get(scene->materialHandle),
                model,
                scene->shaderCache,
                scene->textureCache,
                funcs);

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
