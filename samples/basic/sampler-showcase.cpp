#include "app/App.h"

#include <nfx/Graphics.h>

#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;

// Shaders
static const char* s_vertSrc = R"glsl(
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

// Geometry: pos(2) + uv(2), two quads (left then right)
// clang-format off
static const float s_verts[] = {
    // Left quad: clamp + nearest
    -0.95f,  0.85f, -1.0f,  2.0f,
    -0.95f, -0.85f, -1.0f, -1.0f,
    -0.05f,  0.85f,  2.0f,  2.0f,
    -0.95f, -0.85f, -1.0f, -1.0f,
    -0.05f, -0.85f,  2.0f, -1.0f,
    -0.05f,  0.85f,  2.0f,  2.0f,

    // Right quad: repeat + linear mipmap
     0.05f,  0.85f, -1.0f,  2.0f,
     0.05f, -0.85f, -1.0f, -1.0f,
     0.95f,  0.85f,  2.0f,  2.0f,
     0.05f, -0.85f, -1.0f, -1.0f,
     0.95f, -0.85f,  2.0f, -1.0f,
     0.95f,  0.85f,  2.0f,  2.0f
};
// clang-format on

struct Scene
{
    gl::VertexArray vao;
    gl::VertexLayout layout{ { gl::VertexLayout::Float2, gl::VertexLayout::Float2 } };
    gl::Buffer vbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram program;

    gl::Texture2D box;
    gl::Sampler clampNearest;
    gl::Sampler repeatLinear;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - sampler showcase", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();

            scene->vao.bind();
            scene->vbo.bind();
            scene->vbo.setData(s_verts, sizeof(s_verts));
            scene->vao.setVertexLayout(scene->layout);
            scene->vao.unbind();

            scene->program = gl::ShaderProgram::fromSources(
                { { gl::ShaderProgram::Stage::Vertex, s_vertSrc }, { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });
            if (!scene->program.isValid())
            {
                std::fprintf(stderr, "sampler-showcase: shader pipeline initialization failed\n");
            }

            scene->box = nfx::samples::loadEmbeddedTexture("container/container.jpg");
            if (!scene->box.isValid())
            {
                std::fprintf(stderr, "sampler-showcase: texture initialization failed\n");
            }

            scene->clampNearest = gl::Sampler::create({ .minFilter = gl::Sampler::Filter::Nearest,
                                                        .magFilter = gl::Sampler::Filter::Nearest,
                                                        .wrapS = gl::Sampler::Wrap::ClampToEdge,
                                                        .wrapT = gl::Sampler::Wrap::ClampToEdge,
                                                        .wrapR = gl::Sampler::Wrap::ClampToEdge });
            if (!scene->clampNearest.isValid())
            {
                std::fprintf(stderr, "sampler-showcase: clamp+nearest sampler initialization failed\n");
            }

            scene->repeatLinear = gl::Sampler::create({ .minFilter = gl::Sampler::Filter::LinearMipmapLinear,
                                                        .magFilter = gl::Sampler::Filter::Linear,
                                                        .wrapS = gl::Sampler::Wrap::Repeat,
                                                        .wrapT = gl::Sampler::Wrap::Repeat,
                                                        .wrapR = gl::Sampler::Wrap::Repeat });
            if (!scene->repeatLinear.isValid())
            {
                std::fprintf(stderr, "sampler-showcase: repeat+linear sampler initialization failed\n");
            }

            if (scene->program.isValid())
            {
                scene->program.bind();
                scene->program.setUniform("uTex0", 0);
                gl::ShaderProgram::unbind();
            }

            scene->ready = scene->program.isValid() && scene->box.isValid() && scene->clampNearest.isValid() &&
                           scene->repeatLinear.isValid();
            if (!scene->ready)
            {
                std::fprintf(stderr, "sampler-showcase: initialization incomplete, rendering disabled\n");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            const auto& f = gl::Context::current().functions();

            f.glViewport(0, 0, width, height);
            f.glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT);

            scene->program.bind();
            scene->box.bind(0);
            scene->vao.bind();

            // Left: clamp + nearest
            scene->clampNearest.bind(0);
            f.glDrawArrays(gl::TRIANGLES, 0, 6);

            // Right: repeat + linear mipmap
            scene->repeatLinear.bind(0);
            f.glDrawArrays(gl::TRIANGLES, 6, 6);

            scene->vao.unbind();
            gl::Sampler::unbind(0);
            gl::Texture2D::unbind(0);
            gl::ShaderProgram::unbind();
        },

        // onShutdown
        [&] {
            scene.reset();
            // VertexArray, Buffer, ShaderProgram, Texture2D and Sampler cleaned up by RAII
        });
}
