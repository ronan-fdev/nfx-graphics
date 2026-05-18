#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include <array>
#include <type_traits>
#include <vector>

using namespace nfx::graphics::gl;

TEST_SUITE("Pipeline pass contracts")
{
    TEST_CASE("PostProcessPass exposes expected public API")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&PostProcessPass::setInput)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PostProcessPass::setOutputSize)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PostProcessPass::setEffectSource)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PostProcessPass::setUniformFloat)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PostProcessPass::setUniformVec3)>);

        CHECK(std::is_invocable_v<decltype(&PostProcessPass::setInput), PostProcessPass*, Texture2DHandle>);
        CHECK(std::is_invocable_v<decltype(&PostProcessPass::setEffectSource), PostProcessPass*, std::string>);
        CHECK(
            std::
                is_invocable_v<decltype(&PostProcessPass::setUniformFloat), PostProcessPass*, std::string_view, float>);

        CHECK((std::is_base_of_v<RenderPass, PostProcessPass>));
    }

    TEST_CASE("PresentPass exposes expected public API")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&PresentPass::setInput)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PresentPass::setExposure)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PresentPass::setGamma)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PresentPass::setTonemapEnabled)>);
        CHECK(std::is_member_function_pointer_v<decltype(&PresentPass::setGammaEnabled)>);

        CHECK(std::is_invocable_v<decltype(&PresentPass::setInput), PresentPass*, Texture2DHandle>);
        CHECK(std::is_invocable_v<decltype(&PresentPass::setExposure), PresentPass*, float>);
        CHECK(std::is_invocable_v<decltype(&PresentPass::setGamma), PresentPass*, float>);

        CHECK((std::is_base_of_v<RenderPass, PresentPass>));
    }

    TEST_CASE("SkyboxPass exposes expected target and cubemap wiring API")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&SkyboxPass::setTargetTextures)>);
        CHECK(std::is_member_function_pointer_v<decltype(&SkyboxPass::setCubemap)>);

        CHECK(std::is_invocable_v<
              decltype(&SkyboxPass::setTargetTextures),
              SkyboxPass*,
              Texture2DHandle,
              Texture2DHandle>);

        CHECK((std::is_base_of_v<RenderPass, SkyboxPass>));
    }

    TEST_CASE("Overlay passes expose target wiring API")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&GridPass::setTargetTextures)>);
        CHECK(std::is_member_function_pointer_v<decltype(&AxesPass::setTargetTextures)>);
        CHECK(std::is_member_function_pointer_v<decltype(&ImagePlanePass::setTargetTextures)>);
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::setTargetTextures)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::setTargetTextures)>);

        CHECK((std::is_base_of_v<RenderPass, GridPass>));
        CHECK((std::is_base_of_v<RenderPass, AxesPass>));
        CHECK((std::is_base_of_v<RenderPass, ImagePlanePass>));
        CHECK((std::is_base_of_v<RenderPass, Polygon2DPass>));
        CHECK((std::is_base_of_v<RenderPass, TextPass>));
    }

    TEST_CASE("Polygon2DPass exposes item-management API contracts")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::addConvexPolygon)>);
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::addRect)>);
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::remove)>);
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::clear)>);
        CHECK(std::is_member_function_pointer_v<decltype(&Polygon2DPass::polygonCount)>);

        CHECK(std::is_invocable_v<
              decltype(&Polygon2DPass::addRect),
              Polygon2DPass*,
              float,
              float,
              float,
              float,
              const Polygon2DStyle&>);
        CHECK(std::is_invocable_v<decltype(&Polygon2DPass::remove), Polygon2DPass*, Polygon2DHandle>);
    }

    TEST_CASE("TextPass exposes text-item lifecycle API contracts")
    {
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::setFontCache)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::addTextUtf8)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::addGlyphRun)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::removeText)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::clearTexts)>);
        CHECK(std::is_member_function_pointer_v<decltype(&TextPass::textCount)>);

        CHECK(std::is_invocable_v<
              decltype(&TextPass::addTextUtf8),
              TextPass*,
              FontHandle,
              std::string_view,
              float,
              float,
              const TextStyle&>);
        CHECK(std::is_invocable_v<
              decltype(static_cast<void (TextPass::*)(TextItemHandle, std::string_view)>(&TextPass::updateText)),
              TextPass*,
              TextItemHandle,
              std::string_view>);
    }
}
