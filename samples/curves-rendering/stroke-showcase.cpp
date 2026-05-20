#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>
#include <optional>
#include <vector>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

namespace
{
    constexpr float kLightDir[3] = { -0.45f, -1.0f, -0.25f };

    std::vector<float> makeVShape(float width, float height)
    {
        const float hw = width * 0.5f;
        return { -hw, -height, 0.0f, height, hw, -height };
    }

    std::vector<float> makeLine(float halfLength)
    {
        return { -halfLength, 0.0f, halfLength, 0.0f };
    }

    std::vector<float> makeConvexPentagon()
    {
        return { -2.2f, -1.2f, 0.0f, 2.1f, 2.2f, -1.2f, 1.3f, -3.0f, -1.3f, -3.0f };
    }

    std::vector<float> makeConcaveArrow()
    {
        return { -2.6f, -2.6f, 0.0f, 2.4f, 2.6f, -2.6f, 0.9f, -2.6f, 0.0f, -1.1f, -0.9f, -2.6f };
    }

    std::vector<float> makeWaveTrack()
    {
        return { -7.0f, 0.0f, -4.5f, 1.1f, -2.0f, -0.8f, 0.8f, 1.0f, 3.2f, -0.7f, 5.8f, 1.1f, 8.2f, 0.0f };
    }

    bool addStrokeChecked(gl::StrokePass& pass, const gl::StrokeItemDesc2D& desc, const char* msg)
    {
        const auto handle = pass.addStroke(desc);
        if (!handle.isValid())
        {
            std::fprintf(stderr, "stroke-showcase: failed to add %s\n", msg);
            return false;
        }
        return true;
    }

    bool rebuildStrokes(
        gl::StrokePass& pass,
        const std::vector<float>& vPts,
        const std::vector<float>& lPts,
        const std::vector<float>& convexPts,
        const std::vector<float>& concavePts,
        const std::vector<float>& wavePts,
        float t)
    {
        pass.clear();

        const float capOrbit = t * 0.8f;
        const float capSpin = t * 1.1f;

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ vPts };
            d.pointCount = 3;
            d.style.width = 0.5f;
            d.style.join = gl::StrokeJoin::Miter;
            d.style.cap = gl::StrokeCap::Butt;
            d.style.color[0] = 0.95f;
            d.style.color[1] = 0.78f;
            d.style.color[2] = 0.24f;
            math::mat4Translate(d.transform, -13.5f, 7.0f, 0.0f);
            if (!addStrokeChecked(pass, d, "miter join stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ vPts };
            d.pointCount = 3;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Bevel;
            d.style.cap = gl::StrokeCap::Square;
            d.style.color[0] = 0.96f;
            d.style.color[1] = 0.58f;
            d.style.color[2] = 0.32f;
            math::mat4Translate(d.transform, -13.5f, 0.4f, 0.0f);
            if (!addStrokeChecked(pass, d, "bevel join stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ vPts };
            d.pointCount = 3;
            d.style.width = 0.2f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.95f;
            d.style.color[1] = 0.34f;
            d.style.color[2] = 0.30f;
            math::mat4Translate(d.transform, -13.5f, -6.2f, 0.0f);
            if (!addStrokeChecked(pass, d, "round join stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ convexPts };
            d.pointCount = convexPts.size() / 2;
            d.closed = true;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.86f;
            d.style.color[1] = 0.92f;
            d.style.color[2] = 0.35f;
            math::Mat4 rz;
            math::mat4RotateZ(rz, t * 0.8f);
            math::Mat4 tr;
            math::mat4Translate(tr, 1.2f, 3.8f, 0.0f);
            math::mat4Mul(d.transform, tr, rz);
            if (!addStrokeChecked(pass, d, "convex closed polygon stroke"))
            {
                return false;
            }
        }

        {
            const float orbitA = t * 0.7f;
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ concavePts };
            d.pointCount = concavePts.size() / 2;
            d.closed = true;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.58f;
            d.style.color[1] = 0.90f;
            d.style.color[2] = 0.86f;
            math::Mat4 rz;
            math::mat4RotateZ(rz, -t * 0.9f);
            math::Mat4 tr;
            math::mat4Translate(tr, 1.2f + std::cos(orbitA) * 1.0f, -4.2f + std::sin(orbitA) * 0.6f, 0.0f);
            math::mat4Mul(d.transform, tr, rz);
            if (!addStrokeChecked(pass, d, "concave closed polygon stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ lPts };
            d.pointCount = 2;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Butt;
            d.style.color[0] = 0.34f;
            d.style.color[1] = 0.80f;
            d.style.color[2] = 0.96f;
            math::mat4Translate(d.transform, 13.5f, 7.0f, 0.0f);
            if (!addStrokeChecked(pass, d, "butt cap stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ lPts };
            d.pointCount = 2;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Square;
            d.style.color[0] = 0.34f;
            d.style.color[1] = 0.90f;
            d.style.color[2] = 0.72f;
            math::Mat4 tr;
            math::mat4Translate(tr, 13.5f + std::cos(capOrbit) * 0.9f, 0.4f + std::sin(capOrbit) * 0.45f, 0.0f);
            d.transform = tr;
            if (!addStrokeChecked(pass, d, "square cap stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ lPts };
            d.pointCount = 2;
            d.style.width = 1.0f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.42f;
            d.style.color[1] = 0.84f;
            d.style.color[2] = 0.96f;
            math::Mat4 rz;
            math::mat4RotateZ(rz, capSpin);
            math::Mat4 tr;
            math::mat4Translate(tr, 13.5f, -6.2f, 0.0f);
            math::mat4Mul(d.transform, tr, rz);
            if (!addStrokeChecked(pass, d, "round cap stroke"))
            {
                return false;
            }
        }

        {
            const float orbitA = t * 0.9f;
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ wavePts };
            d.pointCount = wavePts.size() / 2;
            d.style.width = 0.6f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.95f;
            d.style.color[1] = 0.70f;
            d.style.color[2] = 0.30f;
            math::Mat4 ry;
            math::mat4RotateY(ry, t * 1.1f);
            math::Mat4 rx;
            math::mat4RotateX(rx, 0.50f + std::sin(t * 0.8f) * 0.20f);
            math::Mat4 rxy;
            math::mat4Mul(rxy, ry, rx);
            math::Mat4 tr;
            math::mat4Translate(
                tr,
                std::cos(orbitA) * 5.0f,
                11.0f + std::sin(orbitA) * 1.4f,
                -7.0f + std::sin(orbitA * 0.5f) * 1.2f);
            math::mat4Mul(d.transform, tr, rxy);
            if (!addStrokeChecked(pass, d, "orbiting 3d wave stroke"))
            {
                return false;
            }
        }

        {
            gl::StrokeItemDesc2D d;
            d.xy = std::span<const float>{ lPts };
            d.pointCount = 2;
            d.style.width = 0.7f;
            d.style.join = gl::StrokeJoin::Round;
            d.style.cap = gl::StrokeCap::Round;
            d.style.color[0] = 0.88f;
            d.style.color[1] = 0.38f;
            d.style.color[2] = 0.88f;
            math::Mat4 rz;
            math::mat4RotateZ(rz, t * 1.7f);
            math::Mat4 ry;
            math::mat4RotateY(ry, 0.55f + std::sin(t * 0.9f) * 0.25f);
            math::Mat4 r;
            math::mat4Mul(r, ry, rz);
            math::Mat4 tr;
            math::mat4Translate(tr, 0.0f, 10.0f, -3.0f);
            math::mat4Mul(d.transform, tr, r);
            if (!addStrokeChecked(pass, d, "pinned spinner stroke"))
            {
                return false;
            }
        }

        return true;
    }

} // namespace

struct Scene
{
    gl::ShaderCache shaderCache;
    gl::MeshCache meshCache;
    gl::MaterialCache materialCache;
    gl::Texture2DCache texture2DCache;
    gl::TextureCubeCache textureCubeCache;
    gl::SamplerCache samplerCache;
    std::optional<gl::RenderResources> renderResources;
    gl::FontCache fontCache;

    gl::ForwardRenderPath path;
    gl::StrokePass* strokePass = nullptr;
    gl::TextPass* textPass = nullptr;
    gl::OrbitCamera camera;
    gl::FontHandle labelFont;
    smp::Clock clock;

    std::vector<float> vPts;
    std::vector<float> lPts;
    std::vector<float> convexPts;
    std::vector<float> concavePts;
    std::vector<float> wavePts;

    bool middleDown = false;
    bool rightDown = false;
    bool hasMouse = false;
    int lastMouseX = 0;
    int lastMouseY = 0;
    bool ready = false;
};

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - stroke-showcase", 1280, 720, 4, 5 },

        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.strokePass = s.path.addStrokePass("Strokes");
            if (!s.strokePass)
            {
                std::fprintf(stderr, "stroke-showcase: failed to create StrokePass\n");
                return;
            }

            s.textPass = s.path.addOverlay<gl::TextPass>("Labels");
            if (!s.textPass)
            {
                std::fprintf(stderr, "stroke-showcase: failed to create TextPass\n");
                return;
            }
            s.textPass->setFontCache(s.fontCache);

            if (auto* grid = s.path.addOverlay<gl::GridPass>("Grid"))
            {
                grid->setGridSize(1.0f);
                grid->setFadeDistance(85.0f);
                const float color[3] = { 0.22f, 0.24f, 0.28f };
                grid->setColor(color);
            }

            if (auto* axes = s.path.addOverlay<gl::AxesPass>("Axes"))
            {
                axes->setAxisLength(30.0f);
                axes->setFadeDistance(85.0f);
            }

            s.path.setClearColor(0.08f, 0.09f, 0.12f, 1.0f);
            s.path.setTonemapEnabled(false);
            s.path.setGammaEnabled(false);
            s.path.initialize(*s.renderResources);

            s.labelFont = smp::FontLoader::fromEmbedded(
                s.texture2DCache, s.fontCache, "JetBrains/mono/JetBrainsMono-Regular.ttf", 30.0f, 32u, 126u);
            if (!s.labelFont.isValid())
            {
                std::fprintf(stderr, "stroke-showcase: failed to load label font\n");
                return;
            }

            gl::TextStyle title;
            title.sizePx = 28.0f;
            title.color[0] = 0.93f;
            title.color[1] = 0.95f;
            title.color[2] = 1.00f;
            title.depthTest = false;

            gl::TextStyle body;
            body.sizePx = 19.0f;
            body.color[0] = 0.72f;
            body.color[1] = 0.82f;
            body.color[2] = 0.92f;
            body.depthTest = false;

            s.textPass->addTextUtf8(s.labelFont, "Stroke Showcase", 32.0f, 46.0f, title);
            s.textPass->addTextUtf8(s.labelFont, "Joins: Miter / Bevel / Round", 32.0f, 84.0f, body);
            s.textPass->addTextUtf8(s.labelFont, "Caps: Butt / Square / Round", 32.0f, 112.0f, body);
            s.textPass->addTextUtf8(s.labelFont, "Closed: Convex + Concave", 32.0f, 140.0f, body);
            s.textPass->addTextUtf8(s.labelFont, "Animated: orbit + spin + pinned", 32.0f, 168.0f, body);

            s.vPts = makeVShape(10.0f, 4.2f);
            s.lPts = makeLine(5.2f);
            s.convexPts = makeConvexPentagon();
            s.concavePts = makeConcaveArrow();
            s.wavePts = makeWaveTrack();

            if (!rebuildStrokes(*s.strokePass, s.vPts, s.lPts, s.convexPts, s.concavePts, s.wavePts, 0.0f))
            {
                return;
            }

            s.camera.azimuth = 0.0f;
            s.camera.elevation = 0.10f;
            s.camera.distance = 46.0f;
            s.camera.target[0] = 0.0f;
            s.camera.target[1] = 0.2f;
            s.camera.target[2] = 0.0f;

            s.ready = true;
        },

        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            Scene& s = *scene;
            const int safeW = std::max(width, 1);
            const int safeH = std::max(height, 1);

            if (!rebuildStrokes(*s.strokePass, s.vPts, s.lPts, s.convexPts, s.concavePts, s.wavePts, s.clock.elapsed()))
            {
                return;
            }

            gl::FrameData frame;
            frame.camera =
                s.camera.toGpuData(0.70f, static_cast<float>(safeW) / static_cast<float>(safeH), 0.1f, 140.0f);

            gl::AmbientLight ambient;
            ambient.color[0] = 1.0f;
            ambient.color[1] = 0.0f;
            ambient.color[2] = 0.0f;
            ambient.intensity = 0.10f;
            frame.ambientLight = ambient.toGpuData();

            gl::DirectionalLight dir;
            dir.color[0] = 1.0f;
            dir.color[1] = 1.0f;
            dir.color[2] = 1.0f;
            dir.intensity = 0.90f;
            frame.directionalLight = dir.toGpuData(kLightDir);

            s.path.render(frame, safeW, safeH);
        },

        [&] { scene.reset(); },

        [&](int x, int y) {
            if (!scene)
            {
                return;
            }

            Scene& s = *scene;
            if (!s.hasMouse)
            {
                s.lastMouseX = x;
                s.lastMouseY = y;
                s.hasMouse = true;
                return;
            }

            const float dx = static_cast<float>(x - s.lastMouseX);
            const float dy = static_cast<float>(y - s.lastMouseY);
            s.lastMouseX = x;
            s.lastMouseY = y;

            if (s.middleDown)
            {
                s.camera.orbit(dx, dy);
            }
            if (s.rightDown)
            {
                s.camera.pan(dx, dy);
            }
        },

        [&](int button, bool pressed) {
            if (!scene)
            {
                return;
            }
            if (button == 2)
            {
                scene->middleDown = pressed;
            }
            if (button == 3)
            {
                scene->rightDown = pressed;
            }
        },

        [&](float delta) {
            if (!scene)
            {
                return;
            }
            scene->camera.zoom(delta);
        });
}
