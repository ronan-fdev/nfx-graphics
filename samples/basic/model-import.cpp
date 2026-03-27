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

    out vec3 vFragPosWS;
    out vec3 vNormalWS;
    out vec2 vUV;

    uniform mat4 uModel;
    uniform mat3 uNormalMatrix;

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
        vNormalWS     = uNormalMatrix * aNormal;
        vUV           = aUV;
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vFragPosWS;
    in vec3 vNormalWS;
    in vec2 vUV;

    out vec4 fragColor;

    layout(std140, binding = 0) uniform Camera {
        mat4 uView;
        mat4 uProj;
        mat4 uViewProj;
        vec3 uCamPos;
        float _padCam0;
        vec3 uCamDir;
        float _padCam1;
    };

    uniform vec3  uLightDir;
    uniform vec3  uLightColor;
    uniform vec3  uAmbient;
    uniform sampler2D uDiffuseMap;
    uniform int   uUseDiffuseMap;
    uniform vec3  uDiffuseColor;
    uniform vec3  uSpecularColor;
    uniform float uShininess;

    void main()
    {
        vec3 N = normalize(vNormalWS);
        if(!gl_FrontFacing) N = -N;

        vec3 base = (uUseDiffuseMap != 0) ? texture(uDiffuseMap, vUV).rgb : uDiffuseColor;

        vec3 L = normalize(-uLightDir);
        vec3 V = normalize(uCamPos - vFragPosWS);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), uShininess);

        vec3 color = uAmbient * base
                   + diff * uLightColor * base
                   + spec * uLightColor * uSpecularColor;

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

    math::Mat3 normalMatrix;
    math::mat3InverseTranspose(normalMatrix, model);
    material->setUniformMat3("uNormalMatrix", normalMatrix.data());

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
        { "nfx-graphics - model import", 1280, 720, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto* objRes = smp::models::find("obj/rock/rock.obj");
            if (!objRes)
            {
                std::fprintf(stderr, "model-import: embedded object not found: obj/rock/rock.obj\n");
                return;
            }

            const std::string_view objText(
                reinterpret_cast<const char*>(objRes->data), static_cast<std::size_t>(objRes->size));

            const auto meshData = smp::ObjLoader::fromSource(objText);
            if (!meshData)
            {
                std::fprintf(stderr, "model-import: ObjLoader failed\n");
                return;
            }

            scene->meshHandle = scene->meshCache.create(*meshData);
            if (!scene->meshHandle.isValid())
            {
                std::fprintf(stderr, "model-import: mesh creation failed\n");
                return;
            }

            scene->shaderHandle = scene->shaderCache.compile(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->shaderHandle.isValid())
            {
                std::fprintf(stderr, "model-import: shader pipeline initialization failed\n");
                return;
            }

            if (auto tex = smp::loadEmbeddedTexture("obj/rock/rock.png"); tex.isValid())
            {
                scene->diffuseHandle = scene->textureCache.add(std::move(tex));
            }
            if (!scene->diffuseHandle.isValid())
            {
                std::fprintf(stderr, "model-import: diffuse texture load failed: obj/rock/rock.png\n");
                return;
            }

            scene->cameraUbo.bind(gl::UboBindings::CameraBlock);
            scene->ambientUbo.bind(gl::UboBindings::AmbientLightBlock);
            scene->dirLightUbo.bind(gl::UboBindings::DirectionalLightBlock);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.15f;
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

                material->setUniform("uUseDiffuseMap", scene->diffuseHandle.isValid() ? 1 : 0);
                material->setUniformVec3("uLightDir", gl::UniformVec3{ -0.2f, -0.5f, -0.8f }.data());
                material->setUniformVec3("uLightColor", gl::UniformVec3{ 1.0f, 1.0f, 1.0f }.data());
                material->setUniformVec3("uAmbient", gl::UniformVec3{ 0.15f, 0.15f, 0.15f }.data());
                material->setUniformVec3("uDiffuseColor", gl::UniformVec3{ 0.8f, 0.8f, 0.8f }.data());
                material->setUniformVec3("uSpecularColor", gl::UniformVec3{ 0.35f, 0.35f, 0.35f }.data());
                material->setUniform("uShininess", 10.0f);

                gl::MaterialBlockData block;
                block.baseColor_alpha[0] = 1.0f;
                block.baseColor_alpha[1] = 1.0f;
                block.baseColor_alpha[2] = 1.0f;
                block.specColor_shine[0] = 1.0f;
                block.specColor_shine[1] = 1.0f;
                block.specColor_shine[2] = 1.0f;
                block.specColor_shine[3] = 10.0f;
                material->setMaterialBlock(block);
            }

            scene->orbitCamera.target[0] = 0.0f;
            scene->orbitCamera.target[1] = 0.2f;
            scene->orbitCamera.target[2] = 0.0f;
            scene->orbitCamera.distance = 4.0f;
            scene->orbitCamera.azimuth = 0.5f;
            scene->orbitCamera.elevation = 0.35f;

            scene->ready = scene->shaderHandle.isValid() && scene->meshHandle.isValid() &&
                           scene->materialHandle.isValid() && scene->diffuseHandle.isValid();
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
