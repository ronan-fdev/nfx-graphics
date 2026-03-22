#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/buffers/VertexArray.h>
#include <nfx/graphics/gl/core/buffers/VertexLayout.h>
#include <nfx/graphics/gl/core/Context.h>

using namespace nfx::graphics::gl;

TEST_SUITE("VertexLayout")
{
    TEST_CASE("Empty layout has zero stride")
    {
        VertexLayout layout{};
        CHECK(layout.stride() == 0);
        CHECK(layout.empty());
    }

    TEST_CASE("Single Float - stride 4, one attribute")
    {
        VertexLayout layout{ VertexLayout::Float };
        CHECK(layout.stride() == 4);
        REQUIRE(layout.attributes().size() == 1);
        CHECK(layout.attributes()[0].location == 0);
        CHECK(layout.attributes()[0].offset == 0);
    }

    TEST_CASE("Float3 - stride 12")
    {
        VertexLayout layout{ VertexLayout::Float3 };
        CHECK(layout.stride() == 12);
    }

    TEST_CASE("Float4 - stride 16")
    {
        VertexLayout layout{ VertexLayout::Float4 };
        CHECK(layout.stride() == 16);
    }

    TEST_CASE("Float3 + Float3 + Float2 - stride 32, locations 0/1/2, correct offsets")
    {
        VertexLayout layout{ VertexLayout::Float3, VertexLayout::Float3, VertexLayout::Float2 };
        CHECK(layout.stride() == 32);
        REQUIRE(layout.attributes().size() == 3);

        CHECK(layout.attributes()[0].location == 0);
        CHECK(layout.attributes()[0].offset == 0);

        CHECK(layout.attributes()[1].location == 1);
        CHECK(layout.attributes()[1].offset == 12);

        CHECK(layout.attributes()[2].location == 2);
        CHECK(layout.attributes()[2].offset == 24);
    }

    TEST_CASE("Float3 + Float2 + Float - stride 24")
    {
        VertexLayout layout{ VertexLayout::Float3, VertexLayout::Float2, VertexLayout::Float };
        CHECK(layout.stride() == 24);
        CHECK(layout.attributes().size() == 3);
        CHECK(layout.attributes()[2].offset == 20);
    }

    TEST_CASE("UByte4 - stride 4")
    {
        VertexLayout layout{ VertexLayout::UByte4 };
        CHECK(layout.stride() == 4);
    }

    TEST_CASE("Half2 - stride 4")
    {
        VertexLayout layout{ VertexLayout::Half2 };
        CHECK(layout.stride() == 4);
    }

    TEST_CASE("Int + Float3 - stride 16, offsets correct")
    {
        VertexLayout layout{ VertexLayout::Int, VertexLayout::Float3 };
        CHECK(layout.stride() == 16);
        CHECK(layout.attributes()[0].offset == 0);
        CHECK(layout.attributes()[1].offset == 4);
    }

    TEST_CASE("Short2 - stride 4")
    {
        VertexLayout layout{ VertexLayout::Short2 };
        CHECK(layout.stride() == 4);
    }

    TEST_CASE("Short4 - stride 8")
    {
        VertexLayout layout{ VertexLayout::Short4 };
        CHECK(layout.stride() == 8);
    }

    TEST_CASE("Multiple single attributes accumulate correctly")
    {
        VertexLayout layout{ VertexLayout::Float, VertexLayout::Float, VertexLayout::Float };
        CHECK(layout.stride() == 12);
        CHECK(layout.attributes().size() == 3);
        CHECK(layout.attributes()[0].offset == 0);
        CHECK(layout.attributes()[1].offset == 4);
        CHECK(layout.attributes()[2].offset == 8);
    }

    TEST_CASE("Static helpers map Float4 consistently")
    {
        CHECK(VertexLayout::count(VertexLayout::Float4) == 4);
        CHECK(VertexLayout::type(VertexLayout::Float4) == nfx::graphics::gl::FLOAT);
        CHECK(VertexLayout::size(VertexLayout::Float4) == 16);
        CHECK(VertexLayout::isInteger(VertexLayout::Float4) == false);
    }

    TEST_CASE("Static helpers map integer formats consistently")
    {
        CHECK(VertexLayout::count(VertexLayout::Int3) == 3);
        CHECK(VertexLayout::type(VertexLayout::Int3) == nfx::graphics::gl::INT);
        CHECK(VertexLayout::size(VertexLayout::Int3) == 12);
        CHECK(VertexLayout::isInteger(VertexLayout::Int3) == true);

        CHECK(VertexLayout::count(VertexLayout::UByte4) == 4);
        CHECK(VertexLayout::type(VertexLayout::UByte4) == nfx::graphics::gl::UNSIGNED_BYTE);
        CHECK(VertexLayout::size(VertexLayout::UByte4) == 4);
        CHECK(VertexLayout::isInteger(VertexLayout::UByte4) == true);
    }

    TEST_CASE("Static helpers map half formats consistently")
    {
        CHECK(VertexLayout::count(VertexLayout::Half2) == 2);
        CHECK(VertexLayout::type(VertexLayout::Half2) == nfx::graphics::gl::HALF_FLOAT);
        CHECK(VertexLayout::size(VertexLayout::Half2) == 4);
        CHECK(VertexLayout::isInteger(VertexLayout::Half2) == false);
    }

    TEST_CASE("addAttribute allows explicit normalized integer attributes")
    {
        VertexLayout layout;
        layout.addAttribute(VertexLayout::UByte4, true);
        layout.addAttribute(VertexLayout::Float2);

        REQUIRE(layout.attributes().size() == 2);
        CHECK(layout.attributes()[0].normalized == true);
        CHECK(layout.attributes()[0].offset == 0);
        CHECK(layout.attributes()[1].normalized == false);
        CHECK(layout.attributes()[1].offset == 4);
        CHECK(layout.stride() == 12);
    }
}
