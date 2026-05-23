#include "app/App.h"
#include "app/FontLoader.h"

#include <nfx/Graphics.h>

#include <array>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace smp = nfx::samples;

namespace
{
    constexpr std::array<float, 4> kFullTargetColor{ 0.33f, 0.34f, 0.36f, 1.0f };
    constexpr std::array<float, 4> kInheritViewColor{ 0.20f, 0.42f, 0.78f, 1.0f };
    constexpr std::array<float, 4> kExplicitViewportColor{ 0.95f, 0.60f, 0.18f, 1.0f };
    constexpr std::array<float, 4> kMatchViewportColor{ 0.72f, 0.30f, 0.82f, 1.0f };

    class FullscreenColorPass final : public gl::RenderPass
    {
    public:
        FullscreenColorPass(
            std::string name, const std::array<float, 4>& color, const gl::RasterRegionState& rasterRegion)
            : RenderPass(std::move(name)),
              m_color(color)
        {
            setRasterRegionState(rasterRegion);
        }

        void setRasterRegion(const gl::RasterRegionState& rasterRegion) { setRasterRegionState(rasterRegion); }

    private:
        bool initialize() override
        {
            m_shader = gl::ShaderProgram::fromSources({ { gl::ShaderProgram::Stage::Vertex,
                                                          "#version 450 core\n"
                                                          "const vec2 kPositions[3] = vec2[](\n"
                                                          "    vec2(-1.0, -1.0),\n"
                                                          "    vec2( 3.0, -1.0),\n"
                                                          "    vec2(-1.0,  3.0)\n"
                                                          ");\n"
                                                          "void main()\n"
                                                          "{\n"
                                                          "    gl_Position = vec4(kPositions[gl_VertexID], 0.0, 1.0);\n"
                                                          "}\n" },
                                                        { gl::ShaderProgram::Stage::Fragment,
                                                          "#version 450 core\n"
                                                          "uniform vec4 uColor;\n"
                                                          "out vec4 fragColor;\n"
                                                          "void main()\n"
                                                          "{\n"
                                                          "    fragColor = uColor;\n"
                                                          "}\n" } });

            return m_shader.isValid() && m_vao.isValid();
        }

        void begin() override { resetRuntimeStats(); }

        void execute(gl::RenderResources&) override
        {
            const auto& funcs = gl::Context::current().functions();
            funcs.glDisable(gl::DEPTH_TEST);
            funcs.glDisable(gl::CULL_FACE);
            funcs.glDisable(gl::BLEND);

            m_shader.bind();
            ++m_runtimeStats.shaderBinds;
            m_shader.setUniformVec4("uColor", m_color.data());

            m_vao.bind();
            ++m_runtimeStats.vaoBinds;
            funcs.glDrawArrays(gl::TRIANGLES, 0, 3);
            ++m_runtimeStats.drawCalls;
            m_vao.unbind();

            m_shader.unbind();
        }

        void end() override {}

    private:
        std::array<float, 4> m_color{ 1.0f, 1.0f, 1.0f, 1.0f };
        gl::ShaderProgram m_shader;
        gl::VertexArray m_vao;
    };

    gl::RasterRegionState makeFullTargetPolicy()
    {
        gl::RasterRegionState state;
        state.viewportPolicy = gl::ViewportPolicy::FullTarget;
        state.scissorPolicy = gl::ScissorPolicy::Disabled;
        return state;
    }

    gl::RasterRegionState makeInheritViewPolicy()
    {
        gl::RasterRegionState state;
        state.viewportPolicy = gl::ViewportPolicy::InheritView;
        state.scissorPolicy = gl::ScissorPolicy::Disabled;
        return state;
    }

    gl::RasterRegionState makeExplicitViewportPolicy(const gl::ViewportRect& viewport)
    {
        gl::RasterRegionState state;
        state.viewportPolicy = gl::ViewportPolicy::Explicit;
        state.explicitViewport = viewport;
        state.scissorPolicy = gl::ScissorPolicy::Disabled;
        return state;
    }

    gl::RasterRegionState makeMatchViewportPolicy(const gl::ViewportRect& viewport)
    {
        gl::RasterRegionState state;
        state.viewportPolicy = gl::ViewportPolicy::Explicit;
        state.explicitViewport = viewport;
        state.scissorPolicy = gl::ScissorPolicy::MatchViewport;
        return state;
    }

    struct Scene
    {
        gl::MeshCache meshCache;
        gl::MaterialCache materialCache;
        gl::ShaderCache shaderCache;
        gl::Texture2DCache texture2DCache;
        gl::TextureCubeCache textureCubeCache;
        gl::SamplerCache samplerCache;
        gl::FontCache fontCache;
        std::optional<gl::RenderResources> renderResources;

        gl::Renderer sceneRenderer;
        gl::Renderer hudRenderer;

        FullscreenColorPass* fullTargetPass = nullptr;
        FullscreenColorPass* inheritViewPass = nullptr;
        FullscreenColorPass* explicitViewportPass = nullptr;
        FullscreenColorPass* matchViewportPass = nullptr;

        gl::TextPass* textPass = nullptr;
        gl::FontHandle labelFont;

        gl::TextItemHandle line1Text;
        gl::TextItemHandle line2Text;
        gl::TextItemHandle line3Text;
        gl::TextItemHandle line4Text;

        gl::TextStyle titleStyle;
        gl::TextStyle bodyStyle;

        int layoutWidth = 0;
        int layoutHeight = 0;

        gl::ViewportRect fullTargetView{ 0, 0, 1, 1 };
        gl::ViewportRect inheritedView{ 0, 0, 1, 1 };
        gl::ViewportRect explicitViewport{ 0, 0, 1, 1 };
        gl::ViewportRect matchedViewport{ 0, 0, 1, 1 };

        bool ready = false;
    };

    void buildLegend(Scene& s, int width, int height)
    {
        if (!s.textPass || !s.labelFont.isValid())
        {
            return;
        }

        s.textPass->clearTexts();

        const float x = 24.0f;
        const float y0 = 56.0f;
        const float lineStep = 34.0f;

        gl::TextStyle fullTargetStyle = s.bodyStyle;
        fullTargetStyle.color[0] = 0.85f;
        fullTargetStyle.color[1] = 0.85f;
        fullTargetStyle.color[2] = 0.85f;

        gl::TextStyle inheritViewStyle = s.bodyStyle;
        inheritViewStyle.color[0] = 0.55f;
        inheritViewStyle.color[1] = 0.75f;
        inheritViewStyle.color[2] = 1.0f;

        gl::TextStyle explicitStyle = s.bodyStyle;
        explicitStyle.color[0] = 1.0f;
        explicitStyle.color[1] = 0.72f;
        explicitStyle.color[2] = 0.38f;

        gl::TextStyle matchStyle = s.bodyStyle;
        matchStyle.color[0] = 0.88f;
        matchStyle.color[1] = 0.58f;
        matchStyle.color[2] = 1.0f;

        constexpr const char* kLegendLineFmt = "%-10s %-14s {x=%d,y=%d} {w=%d,h=%d}";

        char line1[192];
        std::snprintf(
            line1,
            sizeof(line1),
            kLegendLineFmt,
            "Gray:",
            "FullTarget",
            s.fullTargetView.x,
            s.fullTargetView.y,
            s.fullTargetView.width,
            s.fullTargetView.height);
        s.line1Text = s.textPass->addTextUtf8(s.labelFont, line1, x, y0 + lineStep * 0.0f, fullTargetStyle);

        char line2[192];
        std::snprintf(
            line2,
            sizeof(line2),
            kLegendLineFmt,
            "Blue:",
            "InheritView",
            s.inheritedView.x,
            s.inheritedView.y,
            s.inheritedView.width,
            s.inheritedView.height);
        s.line2Text = s.textPass->addTextUtf8(s.labelFont, line2, x, y0 + lineStep * 1.0f, inheritViewStyle);

        char line3[192];
        std::snprintf(
            line3,
            sizeof(line3),
            kLegendLineFmt,
            "Orange:",
            "Explicit",
            s.explicitViewport.x,
            s.explicitViewport.y,
            s.explicitViewport.width,
            s.explicitViewport.height);
        s.line3Text = s.textPass->addTextUtf8(s.labelFont, line3, x, y0 + lineStep * 2.0f, explicitStyle);

        char line4[192];
        std::snprintf(
            line4,
            sizeof(line4),
            kLegendLineFmt,
            "Purple:",
            "MatchViewport",
            s.matchedViewport.x,
            s.matchedViewport.y,
            s.matchedViewport.width,
            s.matchedViewport.height);
        s.line4Text = s.textPass->addTextUtf8(s.labelFont, line4, x, y0 + lineStep * 3.0f, matchStyle);

        s.layoutWidth = width;
        s.layoutHeight = height;
    }
} // namespace

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - raster policy showcase", 1200, 720, 4, 5 },

        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.fullTargetPass =
                s.sceneRenderer.createPass<FullscreenColorPass>("FullTarget", kFullTargetColor, makeFullTargetPolicy());

            s.inheritViewPass = s.sceneRenderer.createPass<FullscreenColorPass>(
                "InheritView", kInheritViewColor, makeInheritViewPolicy());

            s.explicitViewportPass = s.sceneRenderer.createPass<FullscreenColorPass>(
                "ExplicitViewport", kExplicitViewportColor, makeExplicitViewportPolicy(gl::ViewportRect{ 0, 0, 1, 1 }));

            s.matchViewportPass = s.sceneRenderer.createPass<FullscreenColorPass>(
                "ExplicitViewportMatchScissor",
                kMatchViewportColor,
                makeMatchViewportPolicy(gl::ViewportRect{ 0, 0, 1, 1 }));

            s.textPass = s.hudRenderer.createPass<gl::TextPass>("Legend");
            if (!s.textPass)
            {
                std::fprintf(stderr, "raster-policy-showcase: failed to create TextPass\n");
                return;
            }
            s.textPass->setFontCache(s.fontCache);

            s.sceneRenderer.initialize(*s.renderResources);
            s.hudRenderer.initialize(*s.renderResources);

            s.labelFont = smp::FontLoader::fromEmbedded(
                s.texture2DCache, s.fontCache, "JetBrains/mono/JetBrainsMono-Regular.ttf", 24.0f, 32u, 126u);
            if (!s.labelFont.isValid())
            {
                std::fprintf(stderr, "raster-policy-showcase: failed to load label font\n");
                return;
            }

            s.titleStyle.sizePx = 28.0f;
            s.titleStyle.color[0] = 0.93f;
            s.titleStyle.color[1] = 0.95f;
            s.titleStyle.color[2] = 1.00f;
            s.titleStyle.depthTest = false;

            s.bodyStyle.sizePx = 18.0f;
            s.bodyStyle.color[0] = 0.72f;
            s.bodyStyle.color[1] = 0.82f;
            s.bodyStyle.color[2] = 0.92f;
            s.bodyStyle.depthTest = false;

            s.ready = s.fullTargetPass != nullptr && s.inheritViewPass != nullptr &&
                      s.explicitViewportPass != nullptr && s.matchViewportPass != nullptr && s.textPass != nullptr &&
                      s.labelFont.isValid();

            if (!s.ready)
            {
                std::fprintf(stderr, "raster-policy-showcase: initialization failed\n");
                return;
            }
        },

        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            Scene& s = *scene;
            const int w = (width > 0) ? width : 1;
            const int h = (height > 0) ? height : 1;

            s.fullTargetView = gl::ViewportRect{ 0, 0, w, h };

            const auto& funcs = gl::Context::current().functions();
            funcs.glViewport(0, 0, w, h);

            s.inheritedView = gl::ViewportRect{ w / 4, h / 4, w / 2, h / 2 };
            s.sceneRenderer.setViewport(s.inheritedView);

            s.explicitViewport = gl::ViewportRect{ s.inheritedView.x + s.inheritedView.width / 6,
                                                   s.inheritedView.y + s.inheritedView.height / 6,
                                                   s.inheritedView.width / 3,
                                                   s.inheritedView.height / 3 };
            s.explicitViewportPass->setRasterRegion(makeExplicitViewportPolicy(s.explicitViewport));

            s.matchedViewport = gl::ViewportRect{ s.inheritedView.x + s.inheritedView.width / 2,
                                                  s.inheritedView.y + s.inheritedView.height / 5,
                                                  s.inheritedView.width / 4,
                                                  s.inheritedView.height / 2 };
            s.matchViewportPass->setRasterRegion(makeMatchViewportPolicy(s.matchedViewport));

            if (s.layoutWidth != w || s.layoutHeight != h)
            {
                buildLegend(s, w, h);
            }
            else
            {
                constexpr const char* kLegendLineFmt = "%-10s %-14s {x=%d,y=%d} {w=%d,h=%d}";

                char line1[192];
                std::snprintf(
                    line1,
                    sizeof(line1),
                    kLegendLineFmt,
                    "Gray:",
                    "FullTarget",
                    s.fullTargetView.x,
                    s.fullTargetView.y,
                    s.fullTargetView.width,
                    s.fullTargetView.height);
                s.textPass->updateText(s.line1Text, line1);

                char line2[192];
                std::snprintf(
                    line2,
                    sizeof(line2),
                    kLegendLineFmt,
                    "Blue:",
                    "InheritView",
                    s.inheritedView.x,
                    s.inheritedView.y,
                    s.inheritedView.width,
                    s.inheritedView.height);
                s.textPass->updateText(s.line2Text, line2);

                char line3[192];
                std::snprintf(
                    line3,
                    sizeof(line3),
                    kLegendLineFmt,
                    "Orange:",
                    "Explicit",
                    s.explicitViewport.x,
                    s.explicitViewport.y,
                    s.explicitViewport.width,
                    s.explicitViewport.height);
                s.textPass->updateText(s.line3Text, line3);

                char line4[192];
                std::snprintf(
                    line4,
                    sizeof(line4),
                    kLegendLineFmt,
                    "Purple:",
                    "MatchViewport",
                    s.matchedViewport.x,
                    s.matchedViewport.y,
                    s.matchedViewport.width,
                    s.matchedViewport.height);
                s.textPass->updateText(s.line4Text, line4);
            }

            s.sceneRenderer.setFrameData(gl::FrameData{});
            s.sceneRenderer.render();

            funcs.glViewport(0, 0, w, h);
            s.hudRenderer.setViewport(gl::ViewportRect{ 0, 0, w, h });
            s.hudRenderer.setFrameData(gl::FrameData{});
            s.hudRenderer.render();
        },

        [&] { scene.reset(); },
        [&](int, int) {},
        [&](int, bool) {},
        [&](float) {});
}
