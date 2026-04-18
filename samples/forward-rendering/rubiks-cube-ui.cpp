#include "app/App.h"

#include <nfx/Graphics.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
#include <numbers>
#include <optional>
#include <random>
#include <vector>

namespace gl = nfx::graphics::gl;
namespace math = nfx::graphics::math;
namespace smp = nfx::samples;

struct Cubelet
{
    int gx = 0;
    int gy = 0;
    int gz = 0;
    gl::MaterialHandle stickerPosX;
    gl::MaterialHandle stickerNegX;
    gl::MaterialHandle stickerPosY;
    gl::MaterialHandle stickerNegY;
    gl::MaterialHandle stickerPosZ;
    gl::MaterialHandle stickerNegZ;
};

enum class MoveAxis
{
    X,
    Y,
    Z
};

struct CubeMove
{
    MoveAxis axis = MoveAxis::X;
    int layer = 1;
    int dir = 1;
    char label = '?';
};

enum class UiAction
{
    MoveF,
    MoveR,
    MoveU,
    MoveB,
    MoveL,
    MoveD,
    MoveFPrime,
    MoveRPrime,
    MoveUPrime,
    MoveBPrime,
    MoveLPrime,
    MoveDPrime,
    Scramble,
    Solve,
    ResetCube,

    ViewLeft,
    ViewRight,
    ViewUp,
    ViewDown,
    ViewReset
};

struct UiButton
{
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;
    const char* label = "";
    UiAction action = UiAction::MoveF;
    gl::TextItemHandle text;
};

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
    gl::Polygon2DPass* polygon2DPass = nullptr;
    gl::TextPass* textPass = nullptr;

    gl::MeshHandle cubeMesh;
    gl::MeshHandle quadMesh;

    gl::MaterialHandle bodyMat;
    gl::MaterialHandle facePosXMat;
    gl::MaterialHandle faceNegXMat;
    gl::MaterialHandle facePosYMat;
    gl::MaterialHandle faceNegYMat;
    gl::MaterialHandle facePosZMat;
    gl::MaterialHandle faceNegZMat;

    std::vector<Cubelet> cubelets;

    gl::FontHandle uiFont;
    gl::TextItemHandle headingText;
    std::vector<UiButton> buttons;
    int uiLayoutWidth = 0;
    int uiLayoutHeight = 0;

    smp::Clock clock;

    int lastMouseX = 0;
    int lastMouseY = 0;
    int viewportWidth = 1;
    int viewportHeight = 1;

    int lastCachedViewportWidth = -1;
    int lastCachedViewportHeight = -1;
    gl::Camera::GpuData cachedCamera{};

    float targetViewYaw = 0.0f;
    float currentViewYaw = 0.0f;
    float targetViewPitch = 0.0f;
    float currentViewPitch = 0.0f;
    math::Quat cubeOrientation;

    std::deque<CubeMove> queue;
    std::vector<CubeMove> history;
    std::array<bool, 256> keyDown{};
    bool solving = false;

    bool moveActive = false;
    CubeMove activeMove{};
    float activeAngle = 0.0f;

    std::mt19937 rng{ 1337u };

    bool ready = false;
};

namespace
{
    constexpr float kCubeletScale = 0.62f;
    constexpr float kCubeletSpacing = 0.66f;
    constexpr float kStickerScale = 0.22f;
    constexpr float kStickerOffsetEps = 0.0025f;

    constexpr float kMoveAngularSpeed = 5.5f;

    constexpr float kCubeOffsetX = 0.0f;
    constexpr float kCubeOffsetY = 0.95f;
    constexpr float kCubeOffsetZ = 0.0f;

    constexpr float kCameraZNear = 0.1f;
    constexpr float kCameraZFar = 100.0f;
    constexpr float kCameraFovY = 35.0f * (std::numbers::pi_v<float> / 180.0f);

    constexpr float kViewStep = 0.5f * std::numbers::pi_v<float>; // 90 deg per click

    enum class FaceId
    {
        PosX,
        NegX,
        PosY,
        NegY,
        PosZ,
        NegZ
    };

    struct FaceResolve
    {
        FaceId front;
        FaceId right;
        FaceId up;
        FaceId back;
        FaceId left;
        FaceId down;
    };

    [[nodiscard]] CubeMove moveForFace(FaceId face, bool prime)
    {
        switch (face)
        {
            case FaceId::NegZ:
                return CubeMove{ MoveAxis::Z, -1, prime ? -1 : 1, 'F' };
            case FaceId::PosZ:
                return CubeMove{ MoveAxis::Z, 1, prime ? 1 : -1, 'B' };
            case FaceId::NegX:
                return CubeMove{ MoveAxis::X, -1, prime ? -1 : 1, 'R' };
            case FaceId::PosX:
                return CubeMove{ MoveAxis::X, 1, prime ? 1 : -1, 'L' };
            case FaceId::PosY:
                return CubeMove{ MoveAxis::Y, 1, prime ? 1 : -1, 'U' };
            case FaceId::NegY:
                return CubeMove{ MoveAxis::Y, -1, prime ? -1 : 1, 'D' };
        }
        return {};
    }

    [[nodiscard]] FaceResolve resolveFacesForViewer(const Scene& s)
    {
        const math::Vec3 target{ kCubeOffsetX, kCubeOffsetY, kCubeOffsetZ };
        const math::Vec3 eye{ target.x + 7.4f, target.y + 6.8f, target.z + 7.4f };

        const math::Vec3 camForward = math::vec3normalize(math::vec3sub(target, eye));
        const math::Vec3 viewerDir = math::vec3normalize(math::vec3sub(eye, target));
        const math::Vec3 worldUp{ 0.0f, 1.0f, 0.0f };
        const math::Vec3 camRight = math::vec3normalize(math::vec3cross(camForward, worldUp));
        const math::Vec3 camUp = math::vec3normalize(math::vec3cross(camRight, camForward));

        struct FaceWorld
        {
            FaceId id;
            float n[3];
        };

        const std::array<std::pair<FaceId, std::array<float, 3>>, 6> localNormals = {
            std::pair{ FaceId::PosX, std::array<float, 3>{ 1.0f, 0.0f, 0.0f } },
            std::pair{ FaceId::NegX, std::array<float, 3>{ -1.0f, 0.0f, 0.0f } },
            std::pair{ FaceId::PosY, std::array<float, 3>{ 0.0f, 1.0f, 0.0f } },
            std::pair{ FaceId::NegY, std::array<float, 3>{ 0.0f, -1.0f, 0.0f } },
            std::pair{ FaceId::PosZ, std::array<float, 3>{ 0.0f, 0.0f, 1.0f } },
            std::pair{ FaceId::NegZ, std::array<float, 3>{ 0.0f, 0.0f, -1.0f } }
        };

        std::array<FaceWorld, 6> worldNormals{};
        for (std::size_t i = 0; i < localNormals.size(); ++i)
        {
            worldNormals[i].id = localNormals[i].first;
            math::quatRotate(s.cubeOrientation, localNormals[i].second.data(), worldNormals[i].n);
        }

        auto pickFace = [&](const math::Vec3& axis) {
            float best = -1e9f;
            FaceId bestId = FaceId::NegZ;
            for (const FaceWorld& f : worldNormals)
            {
                const float d = f.n[0] * axis.x + f.n[1] * axis.y + f.n[2] * axis.z;
                if (d > best)
                {
                    best = d;
                    bestId = f.id;
                }
            }
            return bestId;
        };

        const math::Vec3 negViewer{ -viewerDir.x, -viewerDir.y, -viewerDir.z };
        const math::Vec3 negRight{ -camRight.x, -camRight.y, -camRight.z };
        const math::Vec3 negUp{ -camUp.x, -camUp.y, -camUp.z };

        FaceResolve r{};
        r.front = pickFace(viewerDir);
        r.back = pickFace(negViewer);
        r.right = pickFace(camRight);
        r.left = pickFace(negRight);
        r.up = pickFace(camUp);
        r.down = pickFace(negUp);
        return r;
    }

    [[nodiscard]] gl::MaterialHandle makeUnlit(
        gl::ShaderCache& shaderCache, gl::MaterialCache& materialCache, const math::Vec3& color)
    {
        gl::UnlitMaterial desc;
        desc.color = { color.x, color.y, color.z };
        desc.alpha = 1.0f;
        return desc.build(shaderCache, materialCache);
    }

    [[nodiscard]] bool pointInButton(const UiButton& b, int x, int y)
    {
        const float px = static_cast<float>(x);
        const float py = static_cast<float>(y);
        return px >= b.x && px <= (b.x + b.w) && py >= b.y && py <= (b.y + b.h);
    }

    void buildStickerModel(math::Mat4& out, int nx, int ny, int nz)
    {
        math::Mat4 t;
        math::Mat4 r;
        math::Mat4 s;
        math::Mat4 tr;
        const float stickerInset = 0.5f * kCubeletScale + kStickerOffsetEps;

        math::mat4Translate(
            t,
            static_cast<float>(nx) * stickerInset,
            static_cast<float>(ny) * stickerInset,
            static_cast<float>(nz) * stickerInset);
        math::mat4Identity(r);

        if (nx == 1)
        {
            math::mat4RotateY(r, 0.5f * std::numbers::pi_v<float>);
        }
        else if (nx == -1)
        {
            math::mat4RotateY(r, -0.5f * std::numbers::pi_v<float>);
        }
        else if (ny == 1)
        {
            math::mat4RotateX(r, -0.5f * std::numbers::pi_v<float>);
        }
        else if (ny == -1)
        {
            math::mat4RotateX(r, 0.5f * std::numbers::pi_v<float>);
        }
        else if (nz == -1)
        {
            math::mat4RotateY(r, std::numbers::pi_v<float>);
        }

        math::mat4Scale(s, kStickerScale, kStickerScale, 1.0f);
        math::mat4Mul(tr, t, r);
        math::mat4Mul(out, tr, s);
    }

    float stepTo(float cur, float target, float step)
    {
        const float diff = target - cur;
        if (std::abs(diff) < 1e-4f)
        {
            return target;
        }
        return cur + std::copysign(std::min(step, std::abs(diff)), diff);
    }

    void updateViewAnimation(Scene& s, float dt)
    {
        const float step = kMoveAngularSpeed * dt;

        s.currentViewYaw = stepTo(s.currentViewYaw, s.targetViewYaw, step);
        s.currentViewPitch = stepTo(s.currentViewPitch, s.targetViewPitch, step);

        const math::Quat qBase = math::quatAngleAxis(std::numbers::pi_v<float>, 0.0f, 1.0f, 0.0f);
        const math::Quat qYaw = math::quatAngleAxis(s.currentViewYaw, 0.0f, 1.0f, 0.0f);
        const math::Quat qPitch = math::quatAngleAxis(s.currentViewPitch, 1.0f, 0.0f, 0.0f);

        s.cubeOrientation = math::quatNormalize(math::quatMul(qYaw, math::quatMul(qPitch, qBase)));
    }

    void resetCubeState(Scene& s)
    {
        s.cubelets.clear();
        s.cubelets.reserve(27);

        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                for (int z = -1; z <= 1; ++z)
                {
                    Cubelet c;
                    c.gx = x;
                    c.gy = y;
                    c.gz = z;

                    if (x == 1)
                    {
                        c.stickerPosX = s.facePosXMat;
                    }
                    if (x == -1)
                    {
                        c.stickerNegX = s.faceNegXMat;
                    }
                    if (y == 1)
                    {
                        c.stickerPosY = s.facePosYMat;
                    }
                    if (y == -1)
                    {
                        c.stickerNegY = s.faceNegYMat;
                    }
                    if (z == 1)
                    {
                        c.stickerPosZ = s.facePosZMat;
                    }
                    if (z == -1)
                    {
                        c.stickerNegZ = s.faceNegZMat;
                    }

                    s.cubelets.push_back(c);
                }
            }
        }

        s.queue.clear();
        s.history.clear();
        s.solving = false;
        s.moveActive = false;
        s.activeAngle = 0.0f;
    }

    [[nodiscard]] bool isCubeletInLayer(const Cubelet& c, const CubeMove& move)
    {
        switch (move.axis)
        {
            case MoveAxis::X:
                return c.gx == move.layer;
            case MoveAxis::Y:
                return c.gy == move.layer;
            case MoveAxis::Z:
                return c.gz == move.layer;
        }
        return false;
    }

    [[nodiscard]] math::Quat moveRotationQuat(const CubeMove& move, float angle)
    {
        const float signedAngle = angle * static_cast<float>(move.dir);
        switch (move.axis)
        {
            case MoveAxis::X:
                return math::quatAngleAxis(signedAngle, 1.0f, 0.0f, 0.0f);
            case MoveAxis::Y:
                return math::quatAngleAxis(signedAngle, 0.0f, 1.0f, 0.0f);
            case MoveAxis::Z:
                return math::quatAngleAxis(signedAngle, 0.0f, 0.0f, 1.0f);
        }
        return {};
    }

    void applyQuarterTurnToCubelet(Cubelet& c, const CubeMove& move)
    {
        const gl::MaterialHandle oldPosX = c.stickerPosX;
        const gl::MaterialHandle oldNegX = c.stickerNegX;
        const gl::MaterialHandle oldPosY = c.stickerPosY;
        const gl::MaterialHandle oldNegY = c.stickerNegY;
        const gl::MaterialHandle oldPosZ = c.stickerPosZ;
        const gl::MaterialHandle oldNegZ = c.stickerNegZ;

        const int x = c.gx;
        const int y = c.gy;
        const int z = c.gz;

        switch (move.axis)
        {
            case MoveAxis::X:
                if (move.dir > 0)
                {
                    c.gy = -z;
                    c.gz = y;
                }
                else
                {
                    c.gy = z;
                    c.gz = -y;
                }
                break;
            case MoveAxis::Y:
                if (move.dir > 0)
                {
                    c.gx = z;
                    c.gz = -x;
                }
                else
                {
                    c.gx = -z;
                    c.gz = x;
                }
                break;
            case MoveAxis::Z:
                if (move.dir > 0)
                {
                    c.gx = -y;
                    c.gy = x;
                }
                else
                {
                    c.gx = y;
                    c.gy = -x;
                }
                break;
        }

        switch (move.axis)
        {
            case MoveAxis::X:
                if (move.dir > 0)
                {
                    c.stickerPosY = oldNegZ;
                    c.stickerNegY = oldPosZ;
                    c.stickerPosZ = oldPosY;
                    c.stickerNegZ = oldNegY;
                }
                else
                {
                    c.stickerPosY = oldPosZ;
                    c.stickerNegY = oldNegZ;
                    c.stickerPosZ = oldNegY;
                    c.stickerNegZ = oldPosY;
                }
                break;
            case MoveAxis::Y:
                if (move.dir > 0)
                {
                    c.stickerPosX = oldPosZ;
                    c.stickerNegX = oldNegZ;
                    c.stickerPosZ = oldNegX;
                    c.stickerNegZ = oldPosX;
                }
                else
                {
                    c.stickerPosX = oldNegZ;
                    c.stickerNegX = oldPosZ;
                    c.stickerPosZ = oldPosX;
                    c.stickerNegZ = oldNegX;
                }
                break;
            case MoveAxis::Z:
                if (move.dir > 0)
                {
                    c.stickerPosX = oldNegY;
                    c.stickerNegX = oldPosY;
                    c.stickerPosY = oldPosX;
                    c.stickerNegY = oldNegX;
                }
                else
                {
                    c.stickerPosX = oldPosY;
                    c.stickerNegX = oldNegY;
                    c.stickerPosY = oldNegX;
                    c.stickerNegY = oldPosX;
                }
                break;
        }
    }

    void enqueueMove(Scene& s, const CubeMove& move)
    {
        s.queue.push_back(move);
    }

    void enqueueInverseHistory(Scene& s)
    {
        if (s.history.empty())
        {
            return;
        }
        for (auto it = s.history.rbegin(); it != s.history.rend(); ++it)
        {
            CubeMove inv = *it;
            inv.dir = -inv.dir;
            s.queue.push_back(inv);
        }

        s.history.clear();
        s.solving = true;
    }

    void enqueueScramble(Scene& s, int count)
    {
        static const CubeMove kVisualMoves[] = {
            { MoveAxis::Z, -1, 1, 'F' }, // front
            { MoveAxis::X, -1, 1, 'R' }, // right
            { MoveAxis::Y, 1, -1, 'U' }, // up
            { MoveAxis::Z, 1, -1, 'B' }, // back
            { MoveAxis::X, 1, -1, 'L' }, // left
            { MoveAxis::Y, -1, 1, 'D' }  // down
        };

        std::uniform_int_distribution<int> facePick(0, 5);
        std::uniform_int_distribution<int> dirPick(0, 1);
        std::uniform_int_distribution<int> turnPick(0, 2);

        int prevFace = -1;
        MoveAxis prevAxis = MoveAxis::X;
        bool hasPrev = false;

        for (int i = 0; i < count; ++i)
        {
            int face = 0;
            for (int guard = 0; guard < 64; ++guard)
            {
                face = facePick(s.rng);
                const CubeMove candidate = kVisualMoves[face];
                if (hasPrev && (face == prevFace || candidate.axis == prevAxis))
                {
                    continue;
                }
                break;
            }

            CubeMove m = kVisualMoves[face];
            if (turnPick(s.rng) < 2)
            {
                if (dirPick(s.rng) == 1)
                {
                    m.dir = -m.dir;
                }
                s.queue.push_back(m);
            }
            else
            {
                s.queue.push_back(m);
                s.queue.push_back(m);
            }

            prevFace = face;
            prevAxis = m.axis;
            hasPrev = true;
        }
    }

    void executeUiAction(Scene& s, UiAction action)
    {
        const FaceResolve faces = resolveFacesForViewer(s);

        switch (action)
        {
            case UiAction::MoveF:
                enqueueMove(s, moveForFace(faces.front, false));
                break;
            case UiAction::MoveR:
                enqueueMove(s, moveForFace(faces.right, false));
                break;
            case UiAction::MoveU:
                enqueueMove(s, moveForFace(faces.up, false));
                break;
            case UiAction::MoveB:
                enqueueMove(s, moveForFace(faces.back, false));
                break;
            case UiAction::MoveL:
                enqueueMove(s, moveForFace(faces.left, false));
                break;
            case UiAction::MoveD:
                enqueueMove(s, moveForFace(faces.down, false));
                break;

            case UiAction::MoveFPrime:
                enqueueMove(s, moveForFace(faces.front, true));
                break;
            case UiAction::MoveRPrime:
                enqueueMove(s, moveForFace(faces.right, true));
                break;
            case UiAction::MoveUPrime:
                enqueueMove(s, moveForFace(faces.up, true));
                break;
            case UiAction::MoveBPrime:
                enqueueMove(s, moveForFace(faces.back, true));
                break;
            case UiAction::MoveLPrime:
                enqueueMove(s, moveForFace(faces.left, true));
                break;
            case UiAction::MoveDPrime:
                enqueueMove(s, moveForFace(faces.down, true));
                break;

            case UiAction::Scramble:
                enqueueScramble(s, 24);
                s.solving = false;
                break;
            case UiAction::Solve:
                enqueueInverseHistory(s);
                break;
            case UiAction::ResetCube:
                resetCubeState(s);
                break;

            case UiAction::ViewLeft:
                s.targetViewYaw -= kViewStep;
                break;
            case UiAction::ViewRight:
                s.targetViewYaw += kViewStep;
                break;
            case UiAction::ViewUp:
                s.targetViewPitch -= kViewStep;
                break;
            case UiAction::ViewDown:
                s.targetViewPitch += kViewStep;
                break;
            case UiAction::ViewReset:
            {
                const float pi = std::numbers::pi_v<float>;
                const float twoPi = 2.0f * pi;
                s.currentViewYaw = std::fmod(s.currentViewYaw, twoPi);
                if (s.currentViewYaw > pi)
                    s.currentViewYaw -= twoPi;
                if (s.currentViewYaw < -pi)
                    s.currentViewYaw += twoPi;
                s.currentViewPitch = std::fmod(s.currentViewPitch, twoPi);
                if (s.currentViewPitch > pi)
                    s.currentViewPitch -= twoPi;
                if (s.currentViewPitch < -pi)
                    s.currentViewPitch += twoPi;
                s.targetViewYaw = 0.0f;
                s.targetViewPitch = 0.0f;
                break;
            }
        }
    }

    void rebuildUi(Scene& s, int width, int height)
    {
        if (!s.polygon2DPass || !s.textPass || !s.uiFont.isValid())
        {
            return;
        }

        s.polygon2DPass->clear();
        s.textPass->clearTexts();
        s.buttons.clear();

        gl::TextStyle headingStyle;
        headingStyle.sizePx = 24.0f;
        headingStyle.color[0] = 0.92f;
        headingStyle.color[1] = 0.95f;
        headingStyle.color[2] = 1.00f;
        s.headingText = s.textPass->addTextUtf8(s.uiFont, "Rubik's Cube Controls", 24.0f, 40.0f, headingStyle);

        gl::TextStyle btnStyle;
        btnStyle.sizePx = 22.0f;
        btnStyle.color[0] = 0.90f;
        btnStyle.color[1] = 0.95f;
        btnStyle.color[2] = 1.00f;

        const gl::Polygon2DStyle fillMain{ { 0.18f, 0.22f, 0.30f }, 0.92f };
        const gl::Polygon2DStyle fillAlt{ { 0.17f, 0.20f, 0.27f }, 0.90f };
        const gl::Polygon2DStyle fillView{ { 0.22f, 0.30f, 0.42f }, 0.96f };
        const gl::Polygon2DStyle border{ { 0.72f, 0.80f, 0.93f }, 0.95f };

        auto estimateTextWidth = [](const char* label, float fontPx) {
            const std::size_t n = std::char_traits<char>::length(label);
            return static_cast<float>(n) * fontPx * 0.55f;
        };

        auto addButton = [&](float x,
                             float y,
                             float w,
                             float h,
                             const char* label,
                             UiAction action,
                             const gl::Polygon2DStyle& fillStyle) {
            UiButton b;
            b.x = x;
            b.y = y;
            b.w = w;
            b.h = h;
            b.label = label;
            b.action = action;

            s.polygon2DPass->addRect(x, y, w, h, border);
            s.polygon2DPass->addRect(x + 1.5f, y + 1.5f, w - 3.0f, h - 3.0f, fillStyle);

            const float tx = x + std::max(8.0f, (w - estimateTextWidth(label, btnStyle.sizePx)) * 0.5f);
            const float ty = y + h * 0.65f;
            b.text = s.textPass->addTextUtf8(s.uiFont, label, tx, ty, btnStyle);
            s.buttons.push_back(b);
        };

        const float bw = 62.0f;
        const float bh = 34.0f;
        const float gap = 10.0f;

        const float rowWidth = 6.0f * bw + 5.0f * gap;
        const float cx = static_cast<float>(width) * 0.5f;
        float bx = cx - rowWidth * 0.5f;
        bx = std::clamp(bx, 24.0f, std::max(24.0f, static_cast<float>(width) - rowWidth - 24.0f));

        const float bottomMargin = 28.0f;
        const float yActions = static_cast<float>(height) - bottomMargin - bh;
        const float yMovesPrime = yActions - (bh + 12.0f);
        const float yMoves = yMovesPrime - (bh + 8.0f);

        addButton(bx + 0.0f * (bw + gap), yMoves, bw, bh, "F", UiAction::MoveF, fillMain);
        addButton(bx + 1.0f * (bw + gap), yMoves, bw, bh, "R", UiAction::MoveR, fillMain);
        addButton(bx + 2.0f * (bw + gap), yMoves, bw, bh, "U", UiAction::MoveU, fillMain);
        addButton(bx + 3.0f * (bw + gap), yMoves, bw, bh, "B", UiAction::MoveB, fillMain);
        addButton(bx + 4.0f * (bw + gap), yMoves, bw, bh, "L", UiAction::MoveL, fillMain);
        addButton(bx + 5.0f * (bw + gap), yMoves, bw, bh, "D", UiAction::MoveD, fillMain);

        addButton(bx + 0.0f * (bw + gap), yMovesPrime, bw, bh, "F'", UiAction::MoveFPrime, fillAlt);
        addButton(bx + 1.0f * (bw + gap), yMovesPrime, bw, bh, "R'", UiAction::MoveRPrime, fillAlt);
        addButton(bx + 2.0f * (bw + gap), yMovesPrime, bw, bh, "U'", UiAction::MoveUPrime, fillAlt);
        addButton(bx + 3.0f * (bw + gap), yMovesPrime, bw, bh, "B'", UiAction::MoveBPrime, fillAlt);
        addButton(bx + 4.0f * (bw + gap), yMovesPrime, bw, bh, "L'", UiAction::MoveLPrime, fillAlt);
        addButton(bx + 5.0f * (bw + gap), yMovesPrime, bw, bh, "D'", UiAction::MoveDPrime, fillAlt);

        addButton(bx, yActions, 150.0f, bh, "SCRAMBLE", UiAction::Scramble, fillView);
        addButton(bx + 164.0f, yActions, 120.0f, bh, "SOLVE", UiAction::Solve, fillView);
        addButton(bx + 298.0f, yActions, 120.0f, bh, "RESET", UiAction::ResetCube, fillView);

        const float vw = 54.0f;
        const float vh = 36.0f;
        const float vg = 12.0f;
        float padCx = bx - (vw + vg) * 2.0f - 24.0f;
        padCx = std::max(24.0f + vw + vg, padCx);
        const float padCy = yMoves - (vh + 16.0f);

        addButton(padCx, padCy - (vh + vg), vw, vh, "^", UiAction::ViewUp, fillView);
        addButton(padCx - (vw + vg), padCy, vw, vh, "<", UiAction::ViewLeft, fillView);
        addButton(padCx + (vw + vg), padCy, vw, vh, ">", UiAction::ViewRight, fillView);
        addButton(padCx, padCy + (vh + vg), vw, vh, "v", UiAction::ViewDown, fillView);
        addButton(padCx, padCy, vw, vh, "0", UiAction::ViewReset, fillView);

        s.uiLayoutWidth = width;
        s.uiLayoutHeight = height;
    }

    void updateMoveAnimation(Scene& s, float dt)
    {
        if (!s.moveActive && !s.queue.empty())
        {
            s.activeMove = s.queue.front();
            s.queue.pop_front();
            s.activeAngle = 0.0f;
            s.moveActive = true;
        }

        if (!s.moveActive)
        {
            return;
        }

        s.activeAngle += kMoveAngularSpeed * dt;
        if (s.activeAngle < 0.5f * std::numbers::pi_v<float>)
        {
            return;
        }

        s.activeAngle = 0.5f * std::numbers::pi_v<float>;

        for (Cubelet& c : s.cubelets)
        {
            if (isCubeletInLayer(c, s.activeMove))
            {
                applyQuarterTurnToCubelet(c, s.activeMove);
            }
        }

        if (!s.solving)
        {
            s.history.push_back(s.activeMove);
        }

        s.moveActive = false;
        s.activeAngle = 0.0f;
        if (s.queue.empty())
        {
            s.solving = false;
        }
    }

    gl::Camera::GpuData buildFixedCamera(Scene& s, int width, int height)
    {
        const int safeW = (width > 0) ? width : 1;
        const int safeH = (height > 0) ? height : 1;

        if (s.lastCachedViewportWidth == safeW && s.lastCachedViewportHeight == safeH)
        {
            return s.cachedCamera;
        }

        const float aspect = static_cast<float>(safeW) / static_cast<float>(safeH);

        const math::Vec3 target{ kCubeOffsetX, kCubeOffsetY, kCubeOffsetZ };
        const math::Vec3 eye{ target.x + 7.4f, target.y + 6.8f, target.z + 7.4f };
        const math::Vec3 dir = math::vec3normalize(math::vec3sub(target, eye));

        math::Mat4 view;
        math::Mat4 proj;
        math::Mat4 viewProj;
        math::mat4LookAt(view, eye.x, eye.y, eye.z, target.x, target.y, target.z);
        math::mat4Perspective(proj, kCameraFovY, aspect, kCameraZNear, kCameraZFar);
        math::mat4Mul(viewProj, proj, view);

        s.cachedCamera = gl::Camera::toGpuData(view, proj, viewProj, eye, dir);
        s.lastCachedViewportWidth = safeW;
        s.lastCachedViewportHeight = safeH;

        return s.cachedCamera;
    }

    void handleKey(Scene& s, int key)
    {
        switch (key)
        {
            // Moves
            case 'R':
                executeUiAction(s, UiAction::MoveR);
                break;
            case 'L':
                executeUiAction(s, UiAction::MoveL);
                break;
            case 'U':
                executeUiAction(s, UiAction::MoveU);
                break;
            case 'D':
                executeUiAction(s, UiAction::MoveD);
                break;
            case 'F':
                executeUiAction(s, UiAction::MoveF);
                break;
            case 'B':
                executeUiAction(s, UiAction::MoveB);
                break;

            // Meta
            case ' ':
                executeUiAction(s, UiAction::Scramble);
                break;
            case 'S':
                executeUiAction(s, UiAction::Solve);
                break;

            // View
            case 'A':
                executeUiAction(s, UiAction::ViewLeft);
                break;
            case 'E':
                executeUiAction(s, UiAction::ViewRight);
                break;
            case 'W':
                executeUiAction(s, UiAction::ViewUp);
                break;
            case 'X':
                executeUiAction(s, UiAction::ViewDown);
                break;
            case '0':
                executeUiAction(s, UiAction::ViewReset);
                break;

            default:
                break;
        }
    }
} // namespace

int main()
{
    std::optional<Scene> scene;

    return smp::run(
        { "nfx-graphics - rubiks-cube-ui", 1280, 720, 4, 5 },

        // onInit
        [&] {
            scene.emplace();
            Scene& s = *scene;

            s.renderResources.emplace(gl::RenderResources{
                s.meshCache, s.materialCache, s.shaderCache, s.texture2DCache, s.textureCubeCache, s.samplerCache });

            s.path.setClearColor(0.10f, 0.10f, 0.12f, 1.0f);
            s.path.setTonemapEnabled(false);
            s.path.setGammaEnabled(false);

            s.polygon2DPass = s.path.addOverlay<gl::Polygon2DPass>("UIRects");
            s.textPass = s.path.addOverlay<gl::TextPass>("UI");
            if (s.textPass)
            {
                s.textPass->setFontCache(s.fontCache);
            }

            s.path.initialize(*s.renderResources);

            s.cubeMesh = s.meshCache.create(gl::Primitive::cube());
            s.quadMesh = s.meshCache.create(gl::Primitive::quad());

            s.bodyMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.03f, 0.03f, 0.03f });
            s.facePosXMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.80f, 0.10f, 0.10f });
            s.faceNegXMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.95f, 0.50f, 0.10f });
            s.facePosYMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.95f, 0.85f, 0.15f });
            s.faceNegYMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.95f, 0.95f, 0.95f });
            s.facePosZMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.10f, 0.50f, 0.90f });
            s.faceNegZMat = makeUnlit(s.shaderCache, s.materialCache, math::Vec3{ 0.10f, 0.70f, 0.25f });

            resetCubeState(s);

            // Initial view
            s.targetViewYaw = 0.0f;
            s.currentViewYaw = 0.0f;
            s.targetViewPitch = 0.0f;
            s.currentViewPitch = 0.0f;
            updateViewAnimation(s, 0.0f);

            if (s.textPass)
            {
                s.uiFont = smp::FontLoader::fromEmbedded(
                    s.texture2DCache, s.fontCache, "JetBrains/mono/JetBrainsMono-Regular.ttf", 28.0f, 32u, 126u

                );
            }

            rebuildUi(s, 1280, 720);

            s.ready = s.cubeMesh.isValid() && s.quadMesh.isValid() && s.bodyMat.isValid() && s.facePosXMat.isValid() &&
                      s.faceNegXMat.isValid() && s.facePosYMat.isValid() && s.faceNegYMat.isValid() &&
                      s.facePosZMat.isValid() && s.faceNegZMat.isValid() && !s.cubelets.empty() && s.polygon2DPass &&
                      s.textPass && s.uiFont.isValid() && !s.buttons.empty();
        },

        // onRender
        [&](int width, int height) {
            if (!scene || !scene->ready)
            {
                return;
            }

            Scene& s = *scene;
            s.viewportWidth = (width > 0) ? width : 1;
            s.viewportHeight = (height > 0) ? height : 1;

            if (s.viewportWidth != s.uiLayoutWidth || s.viewportHeight != s.uiLayoutHeight)
            {
                rebuildUi(s, s.viewportWidth, s.viewportHeight);
            }

            gl::FrameData frame;
            frame.camera = buildFixedCamera(s, s.viewportWidth, s.viewportHeight);

            gl::AmbientLight ambient;
            ambient.color[0] = ambient.color[1] = ambient.color[2] = 1.0f;
            ambient.intensity = 0.04f;
            frame.ambientLight = ambient.toGpuData();

            const float dt = std::clamp(s.clock.tick(), 0.0f, 0.050f);
            updateMoveAnimation(s, dt);
            updateViewAnimation(s, dt);

            math::Mat4 cubeRot;
            math::quatToMat4(s.cubeOrientation, cubeRot);

            math::Mat4 cubeOffset;
            math::mat4Translate(cubeOffset, kCubeOffsetX, kCubeOffsetY, kCubeOffsetZ);

            s.path.geometryPass().clearQueue();

            for (std::size_t i = 0; i < s.cubelets.size(); ++i)
            {
                const Cubelet& c = s.cubelets[i];
                float px = static_cast<float>(c.gx) * kCubeletSpacing;
                float py = static_cast<float>(c.gy) * kCubeletSpacing;
                float pz = static_cast<float>(c.gz) * kCubeletSpacing;

                math::Mat4 rotate;
                math::Mat4 scale;
                math::Mat4 translate;
                math::Mat4 model;
                math::Mat4 worldLocal;
                math::Mat4 world;
                math::Mat4 worldRot;

                math::mat4Identity(rotate);

                if (s.moveActive && isCubeletInLayer(c, s.activeMove))
                {
                    const math::Quat qAnim = moveRotationQuat(s.activeMove, s.activeAngle);
                    math::quatToMat4(qAnim, rotate);

                    float pIn[3] = { px, py, pz };
                    float pOut[3] = { px, py, pz };
                    math::quatRotate(qAnim, pIn, pOut);
                    px = pOut[0];
                    py = pOut[1];
                    pz = pOut[2];
                }

                math::mat4Scale(scale, kCubeletScale, kCubeletScale, kCubeletScale);
                math::mat4Translate(translate, px, py, pz);

                math::mat4Mul(worldLocal, translate, rotate);
                math::mat4Mul(worldRot, cubeRot, worldLocal);
                math::mat4Mul(world, cubeOffset, worldRot);
                math::mat4Mul(model, world, scale);

                gl::RenderCommand cmd;
                cmd.mesh = s.cubeMesh;
                cmd.material = s.bodyMat;
                cmd.transform = model;
                cmd.sortKey = 1000 + static_cast<std::uint64_t>(i) * 10u;
                s.path.geometryPass().submit(cmd);

                auto submitSticker = [&](int nx, int ny, int nz, gl::MaterialHandle mat, std::uint64_t order) {
                    math::Mat4 stickerLocal;
                    math::Mat4 stickerModel;
                    buildStickerModel(stickerLocal, nx, ny, nz);
                    math::mat4Mul(stickerModel, world, stickerLocal);

                    gl::RenderCommand stickerCmd;
                    stickerCmd.mesh = s.quadMesh;
                    stickerCmd.material = mat;
                    stickerCmd.transform = stickerModel;
                    stickerCmd.sortKey = order;
                    s.path.geometryPass().submit(stickerCmd);
                };

                const std::uint64_t baseOrder = 1001 + static_cast<std::uint64_t>(i) * 10u;
                if (c.stickerPosX.isValid())
                {
                    submitSticker(1, 0, 0, c.stickerPosX, baseOrder + 1u);
                }
                if (c.stickerNegX.isValid())
                {
                    submitSticker(-1, 0, 0, c.stickerNegX, baseOrder + 2u);
                }
                if (c.stickerPosY.isValid())
                {
                    submitSticker(0, 1, 0, c.stickerPosY, baseOrder + 3u);
                }
                if (c.stickerNegY.isValid())
                {
                    submitSticker(0, -1, 0, c.stickerNegY, baseOrder + 4u);
                }
                if (c.stickerPosZ.isValid())
                {
                    submitSticker(0, 0, 1, c.stickerPosZ, baseOrder + 5u);
                }
                if (c.stickerNegZ.isValid())
                {
                    submitSticker(0, 0, -1, c.stickerNegZ, baseOrder + 6u);
                }
            }

            s.path.render(frame, s.viewportWidth, s.viewportHeight);
        },

        // onShutdown
        [&] { scene.reset(); },

        // onMouseMove
        [&](int x, int y) {
            if (!scene)
            {
                return;
            }
            scene->lastMouseX = x;
            scene->lastMouseY = y;
        },

        // onMouseButton
        [&](int button, bool pressed) {
            if (!scene || !pressed)
            {
                return;
            }

            if (button != 1)
            {
                return;
            }

            for (const UiButton& b : scene->buttons)
            {
                if (pointInButton(b, scene->lastMouseX, scene->lastMouseY))
                {
                    executeUiAction(*scene, b.action);
                    break;
                }
            }
        },

        // onScroll
        [&](float) {},

        // onKey
        [&](int key, bool pressed) {
            if (!scene)
            {
                return;
            }

            if (key >= 0 && key < static_cast<int>(scene->keyDown.size()))
            {
                const std::size_t k = static_cast<std::size_t>(key);
                if (pressed)
                {
                    if (scene->keyDown[k])
                    {
                        return;
                    }
                    scene->keyDown[k] = true;
                }
                else
                {
                    scene->keyDown[k] = false;
                    return;
                }
            }

            if (!pressed)
            {
                return;
            }
            handleKey(*scene, key);
        });
}
