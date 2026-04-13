#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("TextTypes")
{
    TEST_CASE("FontHandle default is invalid")
    {
        const FontHandle h{};
        CHECK(!h.isValid());
    }

    TEST_CASE("TextItemHandle default is invalid")
    {
        const TextItemHandle h{};
        CHECK(!h.isValid());
    }

    TEST_CASE("FontMetrics defaults are zero")
    {
        const FontMetrics m{};
        CHECK(m.ascentPx == doctest::Approx(0.0f));
        CHECK(m.descentPx == doctest::Approx(0.0f));
        CHECK(m.lineGapPx == doctest::Approx(0.0f));
    }

    TEST_CASE("Glyph default codepoint is zero")
    {
        const Glyph g{};
        CHECK(g.codepoint == 0u);
    }

    TEST_CASE("Font kerning defaults to zero when missing")
    {
        Font f;
        CHECK(f.kerningPx('A', 'V') == doctest::Approx(0.0f));
    }
}
