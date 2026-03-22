#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/shaders/ShaderProgram.h>
#include <nfx/graphics/gl/core/Context.h>

using namespace nfx::graphics::gl;

TEST_SUITE("ShaderProgram")
{
    TEST_CASE("fromSources rejects empty pipeline")
    {
        const ShaderProgram program = ShaderProgram::fromSources({});
        CHECK_FALSE(program.isValid());
    }

    TEST_CASE("fromSources rejects mixed compute and graphics stages")
    {
        const ShaderProgram program = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Compute, "#version 430 core\nvoid main(){}" },
              { ShaderProgram::Stage::Fragment, "#version 430 core\nout vec4 c; void main(){ c = vec4(1.0); }" } });

        CHECK_FALSE(program.isValid());
    }

    TEST_CASE("fromSources rejects compute pipeline with more than one stage")
    {
        const ShaderProgram program =
            ShaderProgram::fromSources({ { ShaderProgram::Stage::Compute, "#version 430 core\nvoid main(){}" },
                                         { ShaderProgram::Stage::Compute, "#version 430 core\nvoid main(){}" } });

        CHECK_FALSE(program.isValid());
    }

    TEST_CASE("fromSources rejects graphics pipeline without fragment stage")
    {
        const ShaderProgram program = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, "#version 430 core\nvoid main(){ gl_Position = vec4(0.0); }" } });

        CHECK_FALSE(program.isValid());
    }

    TEST_CASE("fromSources rejects duplicate graphics stage")
    {
        const ShaderProgram program = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, "#version 430 core\nvoid main(){ gl_Position = vec4(0.0); }" },
              { ShaderProgram::Stage::Vertex, "#version 430 core\nvoid main(){ gl_Position = vec4(1.0); }" },
              { ShaderProgram::Stage::Fragment, "#version 430 core\nout vec4 c; void main(){ c = vec4(1.0); }" } });

        CHECK_FALSE(program.isValid());
    }

    TEST_CASE("fromFiles rejects missing file")
    {
        const ShaderProgram program =
            ShaderProgram::fromFiles({ { ShaderProgram::Stage::Vertex, "__missing_shader_file__.vert" },
                                       { ShaderProgram::Stage::Fragment, "__missing_shader_file__.frag" } });

        CHECK_FALSE(program.isValid());
    }
}
