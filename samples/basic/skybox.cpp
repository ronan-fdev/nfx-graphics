#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;

// Box shaders
static const char* s_boxVertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aUV;
    uniform mat4 uModel;
    uniform mat4 uView;
    uniform mat4 uProj;
    out vec2 vUV;
    void main()
    {
        vUV = aUV;
        gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    }
)glsl";

static const char* s_boxFragSrc = R"glsl(
    #version 450 core
    in vec2 vUV;
    uniform sampler2D uTex0;
    out vec4 fragColor;
    void main()
    {
        fragColor = texture(uTex0, vUV);
    }
)glsl";

// Skybox shaders
static const char* s_skyVertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec3 aPos;
    uniform mat4 uView;
    uniform mat4 uProj;
    out vec3 vDir;
    void main()
    {
        vDir = aPos;
        vec4 pos = uProj * uView * vec4(aPos, 1.0);
        gl_Position = pos.xyww;
    }
)glsl";

static const char* s_skyFragSrc = R"glsl(
    #version 450 core
    in vec3 vDir;
    uniform samplerCube uSkybox;
    out vec4 fragColor;
    void main()
    {
        fragColor = texture(uSkybox, vDir);
    }
)glsl";

// Geometry: box pos(3) + uv(2), 36 vertices
// clang-format off
static const float s_boxVerts[] = {
    // +Z
    -0.5f,-0.5f, 0.5f,  0.0f, 0.0f,   0.5f,-0.5f, 0.5f,  1.0f, 0.0f,   0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
    -0.5f,-0.5f, 0.5f,  0.0f, 0.0f,   0.5f, 0.5f, 0.5f,  1.0f, 1.0f,  -0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
    // -Z
     0.5f,-0.5f,-0.5f,  0.0f, 0.0f,  -0.5f,-0.5f,-0.5f,  1.0f, 0.0f,  -0.5f, 0.5f,-0.5f,  1.0f, 1.0f,
     0.5f,-0.5f,-0.5f,  0.0f, 0.0f,  -0.5f, 0.5f,-0.5f,  1.0f, 1.0f,   0.5f, 0.5f,-0.5f,  0.0f, 1.0f,
    // -X
    -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,  -0.5f,-0.5f, 0.5f,  1.0f, 0.0f,  -0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
    -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,  -0.5f, 0.5f, 0.5f,  1.0f, 1.0f,  -0.5f, 0.5f,-0.5f,  0.0f, 1.0f,
    // +X
     0.5f,-0.5f, 0.5f,  1.0f, 0.0f,   0.5f,-0.5f,-0.5f,  0.0f, 0.0f,   0.5f, 0.5f,-0.5f,  0.0f, 1.0f,
     0.5f,-0.5f, 0.5f,  1.0f, 0.0f,   0.5f, 0.5f,-0.5f,  0.0f, 1.0f,   0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
    // -Y
    -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,   0.5f,-0.5f,-0.5f,  1.0f, 0.0f,   0.5f,-0.5f, 0.5f,  1.0f, 1.0f,
    -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,   0.5f,-0.5f, 0.5f,  1.0f, 1.0f,  -0.5f,-0.5f, 0.5f,  0.0f, 1.0f,
    // +Y
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,   0.5f, 0.5f, 0.5f,  1.0f, 0.0f,   0.5f, 0.5f,-0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,   0.5f, 0.5f,-0.5f,  1.0f, 1.0f,  -0.5f, 0.5f,-0.5f,  0.0f, 1.0f
};

// Geometry: skybox cube pos(3), 36 vertices
static const float s_skyVerts[] = {
    // +Z
    -1.0f,-1.0f, 1.0f,   1.0f,-1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,   1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
    // -Z
     1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,   1.0f, 1.0f,-1.0f,
    // -X
    -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,
    // +X
     1.0f,-1.0f, 1.0f,   1.0f,-1.0f,-1.0f,   1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,   1.0f, 1.0f,-1.0f,   1.0f, 1.0f, 1.0f,
    // -Y
    -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f,   1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,   1.0f,-1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,
    // +Y
    -1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f
};
// clang-format on

// Texture helper
static gl::TextureCube loadEmbeddedTextureCube(const char* base)
{
    static const char* s_faces[6] = { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" };

    gl::TextureCube::FaceData faces[6]{};
    unsigned char* decoded[6]{};

    for (int i = 0; i < 6; ++i)
    {
        char name[256]{};
        std::snprintf(name, sizeof(name), "%s/%s", base, s_faces[i]);

        const auto* res = nfx::samples::textures::find(name);
        if (!res)
        {
            std::fprintf(stderr, "[skybox] cubemap face not found: %s\n", name);
            for (unsigned char* p : decoded)
            {
                if (p)
                {
                    stbi_image_free(p);
                }
            }
            return {};
        }

        int w, h, c;
        stbi_set_flip_vertically_on_load(0);
        decoded[i] = stbi_load_from_memory(
            reinterpret_cast<const stbi_uc*>(res->data), static_cast<int>(res->size), &w, &h, &c, 4);
        if (!decoded[i])
        {
            std::fprintf(stderr, "[skybox] cubemap decode failed: %s\n", name);
            for (unsigned char* p : decoded)
            {
                if (p)
                {
                    stbi_image_free(p);
                }
            }
            return {};
        }

        faces[i] = { decoded[i], w, h };
    }

    auto cube = gl::TextureCube::fromMemory(
        faces,
        { .generateMipmaps = true,
          .minFilter = gl::TextureCube::Filter::Linear,
          .magFilter = gl::TextureCube::Filter::Linear,
          .wrapS = gl::TextureCube::Wrap::ClampToEdge,
          .wrapT = gl::TextureCube::Wrap::ClampToEdge,
          .wrapR = gl::TextureCube::Wrap::ClampToEdge,
          .internalFormat = gl::TextureCube::InternalFormat::RGBA8 });

    for (unsigned char* p : decoded)
    {
        if (p)
        {
            stbi_image_free(p);
        }
    }

    return cube;
}

struct Scene
{
    gl::VertexArray boxVao;
    gl::VertexLayout boxLayout{ { gl::VertexLayout::Float3, gl::VertexLayout::Float2 } };
    gl::Buffer boxVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram boxProgram;
    gl::Texture2D boxTexture;

    gl::VertexArray skyVao;
    gl::VertexLayout skyLayout;
    gl::Buffer skyVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram skyProgram;
    gl::TextureCube skyTexture;

    gl::OrbitCamera orbitCamera;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    nfx::samples::Clock clock;
    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - skybox", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();

            const auto& f = gl::Context::current().functions();

            scene->boxProgram =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_boxVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_boxFragSrc } });
            if (!scene->boxProgram.isValid())
            {
                std::fprintf(stderr, "skybox: box shader pipeline initialization failed\n");
            }

            scene->skyProgram =
                gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_skyVertSrc },
                                                 { gl::ShaderProgram::Stage::Fragment, s_skyFragSrc } });
            if (!scene->skyProgram.isValid())
            {
                std::fprintf(stderr, "skybox: sky shader pipeline initialization failed\n");
            }

            scene->boxVao.bind();
            scene->boxVbo.bind();
            scene->boxVbo.setData(s_boxVerts, sizeof(s_boxVerts));
            scene->boxVao.setVertexLayout(scene->boxLayout);
            scene->boxVao.unbind();

            scene->skyVao.bind();
            scene->skyVbo.bind();
            scene->skyVbo.setData(s_skyVerts, sizeof(s_skyVerts));
            scene->skyLayout = gl::VertexLayout({ gl::VertexLayout::Float3 });
            scene->skyVao.setVertexLayout(scene->skyLayout);
            scene->skyVao.unbind();

            scene->boxTexture = nfx::samples::loadEmbeddedTexture("container/container.jpg");
            scene->skyTexture = loadEmbeddedTextureCube("skyboxes/fjords");

            if (scene->boxProgram.isValid())
            {
                scene->boxProgram.bind();
                scene->boxProgram.setUniform("uTex0", 0);
                gl::ShaderProgram::unbind();
            }

            if (scene->skyProgram.isValid())
            {
                scene->skyProgram.bind();
                scene->skyProgram.setUniform("uSkybox", 0);
                gl::ShaderProgram::unbind();
            }

            scene->orbitCamera.distance = 4.5f;
            scene->orbitCamera.elevation = std::numbers::pi_v<float> / 12.f;
            scene->orbitCamera.target[0] = 0.f;
            scene->orbitCamera.target[1] = 0.f;
            scene->orbitCamera.target[2] = 0.f;

            f.glEnable(gl::DEPTH_TEST);

            scene->ready = scene->boxProgram.isValid() && scene->skyProgram.isValid() && scene->boxTexture.isValid() &&
                           scene->skyTexture.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "skybox: initialization incomplete, rendering disabled\n");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const auto& f = gl::Context::current().functions();
            const float t = scene->clock.elapsed();

            const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            const auto camGpu = scene->orbitCamera.toGpuData(std::numbers::pi_v<float> / 4.0f, aspect, 0.1f, 200.0f);

            math::Mat4 model;
            math::Mat4 rx;
            math::Mat4 ry;
            math::mat4RotateX(rx, t * 0.4f);
            math::mat4RotateY(ry, t * 0.8f);
            math::mat4Mul(model, ry, rx);

            f.glViewport(0, 0, width, height);
            f.glClearColor(0.05f, 0.07f, 0.10f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            // Draw box
            scene->boxProgram.bind();
            scene->boxProgram.setUniformMat4("uModel", model.data());
            scene->boxProgram.setUniformMat4("uView", camGpu.view);
            scene->boxProgram.setUniformMat4("uProj", camGpu.proj);

            scene->boxTexture.bind(0);
            scene->boxVao.bind();
            f.glDrawArrays(gl::TRIANGLES, 0, 36);
            scene->boxVao.unbind();
            gl::Texture2D::unbind(0);
            gl::ShaderProgram::unbind();

            // Draw skybox
            float skyView[16];
            for (int i = 0; i < 16; ++i)
            {
                skyView[i] = camGpu.view[i];
            }
            skyView[12] = 0.f;
            skyView[13] = 0.f;
            skyView[14] = 0.f;

            f.glDepthFunc(gl::LEQUAL);
            scene->skyProgram.bind();
            scene->skyProgram.setUniformMat4("uView", skyView);
            scene->skyProgram.setUniformMat4("uProj", camGpu.proj);
            scene->skyTexture.bind(0);
            scene->skyVao.bind();
            f.glDrawArrays(gl::TRIANGLES, 0, 36);
            scene->skyVao.unbind();
            gl::TextureCube::unbind(0);
            gl::ShaderProgram::unbind();
            f.glDepthFunc(gl::LESS);
        },

        // onShutdown
        [&] {
            scene.reset();
            // VertexArray, Buffer, ShaderProgram and Texture wrappers cleaned up by RAII
        },

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
