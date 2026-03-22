#include "app/App.h"

#include <nfx/Gl.h>

#include <cstdio>

// Shaders
namespace gl = nfx::graphics::gl;

static const char* s_vertSrc = R"glsl(
    #version 450 core
    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec3 aColor;
    out vec3 vColor;
    void main()
    {
        vColor = aColor;
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)glsl";

static const char* s_fragSrc = R"glsl(
    #version 450 core
    in vec3 vColor;
    out vec4 fragColor;
    void main()
    {
        fragColor = vec4(vColor, 1.0);
    }
)glsl";

// Shader helper
static GLuint compileShader(const gl::Functions& f, GLenum type, const char* src)
{
    GLuint s = f.glCreateShader(type);
    f.glShaderSource(s, 1, &src, nullptr);
    f.glCompileShader(s);

    GLint compiled = 0;
    f.glGetShaderiv(s, gl::COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLchar infoLog[2048]{};
        GLsizei infoLen = 0;
        f.glGetShaderInfoLog(s, sizeof(infoLog), &infoLen, infoLog);
        std::fprintf(
            stderr, "Shader compile failed (%s):\n%s\n", type == gl::VERTEX_SHADER ? "vertex" : "fragment", infoLog);
        f.glDeleteShader(s);
        return 0;
    }

    return s;
}

static GLuint linkProgram(const gl::Functions& f, GLuint vert, GLuint frag)
{
    GLuint program = f.glCreateProgram();
    f.glAttachShader(program, vert);
    f.glAttachShader(program, frag);
    f.glLinkProgram(program);

    GLint linked = 0;
    f.glGetProgramiv(program, gl::LINK_STATUS, &linked);
    if (!linked)
    {
        GLchar infoLog[2048]{};
        GLsizei infoLen = 0;
        f.glGetProgramInfoLog(program, sizeof(infoLog), &infoLen, infoLog);
        std::fprintf(stderr, "Program link failed:\n%s\n", infoLog);
        f.glDeleteProgram(program);
        return 0;
    }

    return program;
}

// Scene
struct Scene
{
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint program = 0;
};

// Geometry: pos(2) + color(3), 3 vertices
// clang-format off
static const float vertices[] = {
//   x      y      r     g     b
     0.0f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.0f, 0.0f, 1.0f
};
// clang-format on

// Entry point
int main()
{
    Scene scene{};

    return nfx::samples::run(
        { "nfx-graphics - hello triangle", 800, 600, 4, 5 },

        // onInit
        [&] {
            const auto& f = gl::Context::current().functions();

            f.glGenVertexArrays(1, &scene.vao);
            f.glBindVertexArray(scene.vao);

            f.glGenBuffers(1, &scene.vbo);
            f.glBindBuffer(gl::ARRAY_BUFFER, scene.vbo);
            f.glBufferData(gl::ARRAY_BUFFER, sizeof(vertices), vertices, gl::STATIC_DRAW);

            f.glEnableVertexAttribArray(0);
            f.glVertexAttribPointer(0, 2, gl::FLOAT, false, 5 * sizeof(float), reinterpret_cast<const void*>(0));
            f.glEnableVertexAttribArray(1);
            f.glVertexAttribPointer(
                1, 3, gl::FLOAT, false, 5 * sizeof(float), reinterpret_cast<const void*>(2 * sizeof(float)));

            f.glBindVertexArray(0);

            GLuint vert = compileShader(f, gl::VERTEX_SHADER, s_vertSrc);
            GLuint frag = compileShader(f, gl::FRAGMENT_SHADER, s_fragSrc);
            if (vert && frag)
            {
                scene.program = linkProgram(f, vert, frag);
            }
            f.glDeleteShader(vert);
            f.glDeleteShader(frag);

            if (!scene.program)
            {
                std::fprintf(stderr, "hello-triangle: shader pipeline initialization failed\n");
            }
        },

        // onRender
        [&](int width, int height) {
            const auto& f = gl::Context::current().functions();

            f.glViewport(0, 0, width, height);
            f.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            f.glClear(gl::COLOR_BUFFER_BIT);

            if (!scene.program)
            {
                return;
            }

            f.glUseProgram(scene.program);
            f.glBindVertexArray(scene.vao);
            f.glDrawArrays(gl::TRIANGLES, 0, 3);
            f.glBindVertexArray(0);
        },

        // onShutdown
        [&] {
            const auto& f = gl::Context::current().functions();
            f.glDeleteVertexArrays(1, &scene.vao);
            f.glDeleteBuffers(1, &scene.vbo);
            f.glDeleteProgram(scene.program);
        });
}
