#include "app/App.h"

#include <nfx/Graphics.h>

#include <cmath>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;

// Vertex stage: forwards control points of one triangle patch
static const char* s_vertSrc = R"glsl(
    #version 450 core

    layout(location = 0) in vec2 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)glsl";

// Tessellation-control stage: writes outer/inner tessellation factors
static const char* s_tescSrc = R"glsl(
    #version 450 core

    layout(vertices = 3) out;

    uniform float uTessLevel;

    void main()
    {
        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

        if(gl_InvocationID == 0)
        {
            float level = max(1.0, uTessLevel);
            gl_TessLevelOuter[0] = level;
            gl_TessLevelOuter[1] = level;
            gl_TessLevelOuter[2] = level;
            gl_TessLevelInner[0] = level;
        }
    }
)glsl";

// Tessellation-evaluation stage: barycentric interpolation of the patch triangle
static const char* s_teseSrc = R"glsl(
    #version 450 core

    layout(triangles, equal_spacing, ccw) in;

    out vec3 vBary;

    void main()
    {
        vec4 p0 = gl_in[0].gl_Position;
        vec4 p1 = gl_in[1].gl_Position;
        vec4 p2 = gl_in[2].gl_Position;

        vec3 bc = gl_TessCoord;
        gl_Position = p0 * bc.x + p1 * bc.y + p2 * bc.z;
        vBary = bc;
    }
)glsl";

// Fragment stage: visualizes barycentric coordinates as RGB
static const char* s_fragSrc = R"glsl(
    #version 450 core

    in vec3 vBary;
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(vBary, 1.0);
    }
)glsl";

struct Scene
{
    gl::VertexArray vao;
    gl::Buffer vbo{ gl::Buffer::Target::VertexAttributesArray };
    gl::ShaderProgram program;
    nfx::samples::Clock clock;
    float t = 0.0f;
};

// Single triangular patch (3 control points)
static const float s_vertices[] = { -0.8f, -0.7f, 0.8f, -0.7f, 0.0f, 0.85f };

int main()
{
    std::optional<Scene> scene;

    return nfx::samples::run(
        { "nfx-graphics - tessellation", 1000, 700, 4, 2 },

        // onInit
        [&] {
            scene.emplace();

            const auto& ctx = gl::Context::current();
            if (ctx.maxPatchVertices() < 3)
            {
                std::fprintf(
                    stderr,
                    "tessellation: requires GL_MAX_PATCH_VERTICES >= 3 (reported %d)\n",
                    ctx.maxPatchVertices());
                return;
            }

            scene->vao.bind();
            scene->vbo.bind();
            scene->vbo.setData(s_vertices, sizeof(s_vertices), gl::Buffer::Usage::StaticDraw);
            scene->vao.setVertexLayout(gl::VertexLayout{ gl::VertexLayout::Float2 });
            scene->vbo.unbind();
            scene->vao.unbind();

            scene->program = gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex, s_vertSrc },
                                                              { gl::ShaderProgram::Stage::TessControl, s_tescSrc },
                                                              { gl::ShaderProgram::Stage::TessEval, s_teseSrc },
                                                              { gl::ShaderProgram::Stage::Fragment, s_fragSrc } });

            if (!scene->program.isValid())
            {
                std::fprintf(stderr, "tessellation: pipeline initialization failed\n");
            }

            const auto& f = gl::Context::current().functions();
            f.glPatchParameteri(gl::PATCH_VERTICES, 3);
        },

        // onRender
        [&](int width, int height) {
            if (!scene)
            {
                return;
            }

            const auto& f = gl::Context::current().functions();

            f.glViewport(0, 0, width, height);
            f.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

            if (!scene->program.isValid())
            {
                return;
            }

            scene->t += scene->clock.tick();
            // Map sin(t) from [-1, 1] to tessellation level [1, 24]
            const float level = 1.0f + 23.0f * (0.5f + 0.5f * std::sin(scene->t));

            scene->program.bind();
            scene->program.setUniform("uTessLevel", level);

            // Draw wireframe so tessellation density is clearly visible
            f.glPolygonMode(gl::FRONT_AND_BACK, gl::LINE);

            scene->vao.bind();
            f.glDrawArrays(static_cast<unsigned int>(gl::RenderMode::Patches), 0, 3);
            scene->vao.unbind();

            gl::ShaderProgram::unbind();

            f.glPolygonMode(gl::FRONT_AND_BACK, gl::FILL);
        },

        // onShutdown
        [&] { scene.reset(); });
}
