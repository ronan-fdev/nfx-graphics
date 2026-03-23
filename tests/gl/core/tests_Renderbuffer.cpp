#include <doctest/doctest.h>

#include <nfx/graphics/gl/core/framebuffers/Renderbuffer.h>

using namespace nfx::graphics::gl;

TEST_SUITE("Renderbuffer")
{
    TEST_CASE("allocate rejects invalid dimensions")
    {
        Renderbuffer rb;
        rb.allocate(Renderbuffer::Format::Depth24, 0, 16);
        CHECK_FALSE(rb.isValid());
    }

    TEST_CASE("allocate rejects invalid format enum")
    {
        Renderbuffer rb;
        rb.allocate(static_cast<Renderbuffer::Format>(0x7fffffff), 16, 16);
        CHECK_FALSE(rb.isValid());
    }

    TEST_CASE("allocateMultisample rejects invalid dimensions")
    {
        Renderbuffer rb;
        rb.allocateMultisample(Renderbuffer::Format::Depth24, 16, 0, 4);
        CHECK_FALSE(rb.isValid());
    }

    TEST_CASE("allocateMultisample rejects invalid sample count")
    {
        Renderbuffer rb;
        rb.allocateMultisample(Renderbuffer::Format::Depth24, 16, 16, 0);
        CHECK_FALSE(rb.isValid());
    }
}
