#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;

// Shaders
static const char* s_vertSrc = R"glsl(
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

static const char* s_fragSrc = R"glsl(
    #version 450 core
    in vec2 vUV;
    uniform sampler2D uTex0;
    out vec4 fragColor;
    void main()
    {
        fragColor = texture(uTex0, vUV);
    }
)glsl";

static const char* s_quadVertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec2 aUV;
    out vec2 vUV;

    void main()
    {
        vUV = aUV;
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)glsl";

static const char* s_quadFragSrc = R"glsl(
    #version 450 core

    in vec2 vUV;
    out vec4 fragColor;
    uniform sampler2D uRenderTarget;

    void main()
    {
        vec4 color = texture(uRenderTarget, vUV);
        float gray = dot(color.rgb, vec3(0.2, 0.5, 0.1));
        fragColor = vec4(vec3(gray), color.a);
    }
)glsl";

// Scene
struct Scene
{
    // Offscreen pass
    gl::VertexArray cubeVao;
    gl::VertexLayout cubeLayout{ { gl::VertexLayout::Float3, gl::VertexLayout::Float2 } };
    gl::Buffer cubeVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram cubeProgram;
    gl::Texture2D textureBox;
    gl::RenderTarget rt;

    // Blit pass
    gl::ShaderProgram quadProg;
    gl::Buffer quadVbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::VertexArray quadVao;

    nfx::samples::Clock clock;
    bool ready = false;
};

// Geometry: pos(3) + uv(2), 36 vertices
// clang-format off
static const float s_cubeVerts[] = {
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

static const float s_quadVerts[] = {
    // x      y      u     v
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f
};
// clang-format on

// Entry point
int main()
{
    static constexpr int RT_W = 512;
    static constexpr int RT_H = 512;

    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - offscreen cube", 800, 600, 4, 5 },

        // onInit
        [&] {
            scene.emplace();

            const auto& f = gl::Context::current().functions();

            // Cube
            scene->cubeProgram = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->cubeProgram.isValid())
            {
                std::fprintf(stderr, "offscreen-cube: cube shader pipeline initialization failed\n");
            }

            scene->textureBox = nfx::samples::loadEmbeddedTexture("container/container.jpg");
            if (!scene->textureBox.isValid())
            {
                std::fprintf(stderr, "offscreen-cube: box texture initialization failed\n");
            }

            scene->cubeVao.bind();
            scene->cubeVbo.bind();
            scene->cubeVbo.setData(s_cubeVerts, sizeof(s_cubeVerts));
            scene->cubeVao.setVertexLayout(scene->cubeLayout);
            scene->cubeVao.unbind();

            if (scene->cubeProgram.isValid())
            {
                scene->cubeProgram.bind();
                scene->cubeProgram.setUniform("uTex0", 0);
                gl::ShaderProgram::unbind();
            }

            // Quad
            scene->quadProg = gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_quadVertSrc },
                                                               { gl::ShaderProgram::Stage::Fragment, s_quadFragSrc } });
            if (!scene->quadProg.isValid())
            {
                std::fprintf(stderr, "offscreen-cube: blit shader pipeline initialization failed\n");
            }

            scene->quadVao.bind();
            scene->quadVbo.bind();
            scene->quadVbo.setData(s_quadVerts, sizeof(s_quadVerts));
            scene->quadVao.setVertexLayout({ gl::VertexLayout::Float2, gl::VertexLayout::Float2 });
            scene->quadVao.unbind();

            scene->rt.resize(RT_W, RT_H);
            if (!scene->rt.isValid() || !scene->rt.isComplete())
            {
                std::fprintf(stderr, "offscreen-cube: render target initialization failed or incomplete\n");
            }

            if (scene->quadProg.isValid())
            {
                scene->quadProg.bind();
                scene->quadProg.setUniform("uRenderTarget", 0);
                gl::ShaderProgram::unbind();
            }

            f.glEnable(gl::DEPTH_TEST);

            scene->ready = scene->cubeProgram.isValid() && scene->textureBox.isValid() && scene->rt.isValid() &&
                           scene->rt.isComplete() && scene->quadProg.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "offscreen-cube: initialization incomplete, rendering disabled\n");
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

            math::Mat4 rx, ry, model;
            math::mat4RotateX(rx, t * 0.4f);
            math::mat4RotateY(ry, t * 0.8f);
            math::mat4Mul(model, ry, rx);

            math::Mat4 view;
            math::mat4LookAt(view, 0.0f, 1.5f, 3.0f, 0.0f, 0.0f, 0.0f);

            math::Mat4 proj;
            const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            math::mat4Perspective(proj, std::numbers::pi_v<float> / 4.0f, aspect, 0.1f, 100.0f);

            // Offscreen pass
            scene->rt.bind();
            f.glViewport(0, 0, RT_W, RT_H);
            f.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            scene->cubeProgram.bind();
            scene->cubeProgram.setUniformMat4("uModel", model.data());
            scene->cubeProgram.setUniformMat4("uView", view.data());
            scene->cubeProgram.setUniformMat4("uProj", proj.data());

            scene->textureBox.bind(0);

            scene->cubeVao.bind();
            f.glDrawArrays(gl::TRIANGLES, 0, 36);
            scene->cubeVao.unbind();

            gl::Texture2D::unbind(0);
            gl::ShaderProgram::unbind();
            scene->rt.unbind();

            // Blit pass
            f.glViewport(0, 0, width, height);
            f.glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
            f.glDisable(gl::DEPTH_TEST);

            scene->quadProg.bind();
            scene->rt.texture().bind(0);
            scene->quadVao.bind();
            f.glDrawArrays(gl::TRIANGLE_STRIP, 0, 4);
            scene->quadVao.unbind();

            gl::Texture2D::unbind(0);
            gl::ShaderProgram::unbind();
            f.glEnable(gl::DEPTH_TEST);
        },

        // onShutdown
        [&] {
            scene.reset();
            // VertexArray, Buffer, ShaderProgram and Texture2D cleaned up by RAII
        });
}
