#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <cstdio>
#include <optional>

namespace gl = nfx::graphics::gl;
namespace smp = nfx::samples;

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    gl::FontCache fontCache;
    std::optional<gl::RenderResources> renderResources;

    gl::ForwardRenderPath path;
    gl::TextPass* textPass = nullptr;

    gl::FontHandle regularFont;
    gl::TextItemHandle titleText;
    gl::TextItemHandle bodyText;
    gl::TextItemHandle timerText;

    gl::TextStyle titleStyle;
    gl::TextStyle bodyStyle;
    gl::TextStyle timerStyle;

    int layoutWidth = 0;
    int layoutHeight = 0;

    gl::OrbitCamera camera;
    smp::Clock clock;

    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - text-pass", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.path.setClearColor(0.08f, 0.09f, 0.12f, 1.0f);
            s.path.setTonemapEnabled(false);
            s.path.setGammaEnabled(false);

            s.textPass = s.path.addOverlay<gl::TextPass>("Text");
            if (s.textPass)
            {
                s.textPass->setFontCache(s.fontCache);
            }

            s.path.initialize(*s.renderResources);

            s.regularFont = smp::FontLoader::fromEmbedded(
                s.texture2DCache, s.fontCache, "JetBrains/mono/JetBrainsMono-Regular.ttf", 40.0f, 32u, 126u);

            if (s.textPass && s.regularFont.isValid())
            {
                s.titleStyle.sizePx = 48.0f;
                s.titleStyle.color[0] = 0.93f;
                s.titleStyle.color[1] = 0.96f;
                s.titleStyle.color[2] = 1.00f;

                s.bodyStyle.sizePx = 24.0f;
                s.bodyStyle.color[0] = 0.65f;
                s.bodyStyle.color[1] = 0.86f;
                s.bodyStyle.color[2] = 1.00f;

                s.timerStyle.sizePx = 22.0f;
                s.timerStyle.color[0] = 0.95f;
                s.timerStyle.color[1] = 0.78f;
                s.timerStyle.color[2] = 0.39f;

                const float x = 32.0f;
                const float yTitle = 74.0f;
                const float yBody = 116.0f;
                const float yTimer = 152.0f;

                s.titleText = s.textPass->addTextUtf8(s.regularFont, "nfx-graphics TextPass", x, yTitle, s.titleStyle);
                s.bodyText = s.textPass->addTextUtf8(
                    s.regularFont,
                    "UTF-8 rendering path enabled (ASCII glyph range in this sample)",
                    x,
                    yBody,
                    s.bodyStyle);
                s.timerText = s.textPass->addTextUtf8(s.regularFont, "time: 0.00s", x, yTimer, s.timerStyle);

                s.layoutWidth = 1280;
                s.layoutHeight = 720;
            }

            s.camera.distance = 4.0f;
            s.ready = s.textPass != nullptr && s.regularFont.isValid() && s.titleText.isValid() &&
                      s.bodyText.isValid() && s.timerText.isValid();

            if (!s.ready)
            {
                std::fprintf(stderr, "[text-pass] initialization failed\n");
                std::fprintf(stderr, "  textPass   : %s\n", s.textPass ? "ok" : "missing");
                std::fprintf(stderr, "  regularFont: %s\n", s.regularFont.isValid() ? "ok" : "invalid");
                std::fprintf(stderr, "  titleText  : %s\n", s.titleText.isValid() ? "ok" : "invalid");
                std::fprintf(stderr, "  bodyText   : %s\n", s.bodyText.isValid() ? "ok" : "invalid");
                std::fprintf(stderr, "  timerText  : %s\n", s.timerText.isValid() ? "ok" : "invalid");
            }
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            Scene& s = *scene;
            const int safeW = (width > 0) ? width : 1;
            const int safeH = (height > 0) ? height : 1;

            if (s.layoutWidth != safeW || s.layoutHeight != safeH)
            {
                const float x = 32.0f;
                const float yTitle = std::max(56.0f, 0.10f * static_cast<float>(safeH));
                const float yBody = yTitle + 42.0f;
                const float yTimer = yBody + 36.0f;

                s.textPass->clearTexts();
                s.titleText = s.textPass->addTextUtf8(s.regularFont, "nfx-graphics TextPass", x, yTitle, s.titleStyle);
                s.bodyText = s.textPass->addTextUtf8(
                    s.regularFont,
                    "UTF-8 rendering path enabled (ASCII glyph range in this sample)",
                    x,
                    yBody,
                    s.bodyStyle);

                char timerInit[64];
                std::snprintf(timerInit, sizeof(timerInit), "time: %.2fs", s.clock.elapsed());
                s.timerText = s.textPass->addTextUtf8(s.regularFont, timerInit, x, yTimer, s.timerStyle);

                s.layoutWidth = safeW;
                s.layoutHeight = safeH;
            }

            char timer[64];
            std::snprintf(timer, sizeof(timer), "time: %.2fs", s.clock.elapsed());
            s.textPass->updateText(s.timerText, timer);

            gl::FrameData frame{};
            frame.camera =
                s.camera.toGpuData(0.80f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 64.0f);
            s.path.render(frame, safeW, safeH);
        },

        // onShutdown
        [&] { scene.reset(); });
}
