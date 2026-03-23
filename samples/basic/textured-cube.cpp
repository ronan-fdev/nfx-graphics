#include "app/App.h"

#include <nfx/Gl.h>
#include <nfx/graphics/math/Mat4.h>

#include <cstdio>
#include <numbers>
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

// Scene
struct Scene
{
    gl::VertexArray vao;
    gl::VertexLayout layout{ gl::VertexLayout::Float3, gl::VertexLayout::Float2 };
    gl::Buffer vbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram program;
    gl::Texture2D box;

    nfx::samples::Clock clock;
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
// clang-format on

// Entry point
int main()
{
    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - textured cube", 800, 600, 4, 5 },

        // onInit
        [&] {
            scene.emplace();

            const auto& f = gl::Context::current().functions();

            scene->vao.bind();

            scene->vbo.bind();
            scene->vbo.setData(s_cubeVerts, sizeof(s_cubeVerts));
            scene->vao.setVertexLayout(scene->layout);
            scene->vao.unbind();

            scene->program = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            scene->box = nfx::samples::loadEmbeddedTexture("container/container.jpg");

            scene->program.bind();
            scene->program.setUniform("uTex0", 0);
            gl::ShaderProgram::unbind();

            f.glEnable(gl::DEPTH_TEST);
        },

        // onRender
        [&](int width, int height) {
            const auto& f = gl::Context::current().functions();

            const float t = scene->clock.elapsed();

            f.glViewport(0, 0, width, height);
            f.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            if (!scene->program.isValid())
            {
                return;
            }

            math::Mat4 rx, ry, model;
            math::mat4RotateX(rx, t * 0.4f);
            math::mat4RotateY(ry, t * 0.8f);
            math::mat4Mul(model, ry, rx);

            math::Mat4 view;
            math::mat4LookAt(view, 0.0f, 1.5f, 3.0f, 0.0f, 0.0f, 0.0f);

            math::Mat4 proj;
            const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
            math::mat4Perspective(proj, std::numbers::pi_v<float> / 4.0f, aspect, 0.1f, 100.0f);

            scene->program.bind();
            scene->program.setUniformMat4("uModel", model.data());
            scene->program.setUniformMat4("uView", view.data());
            scene->program.setUniformMat4("uProj", proj.data());

            scene->box.bind(0);

            scene->vao.bind();
            f.glDrawArrays(gl::TRIANGLES, 0, 36);
            scene->vao.unbind();

            gl::Texture2D::unbind(0);
            gl::ShaderProgram::unbind();
        },

        // onShutdown
        [&] {
            scene.reset();
            // VertexArray, Buffer, ShaderProgram and Texture2D cleaned up by RAII
        });
}
