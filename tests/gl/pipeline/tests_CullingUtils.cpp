#include <doctest/doctest.h>

#include <nfx/Graphics.h>

#include "gl/pipeline/passes/detail/CullingUtils.h"

using namespace nfx::graphics;
using namespace nfx::graphics::gl;

TEST_SUITE("CullingUtils")
{
    TEST_CASE("inside AABB is tested and not culled")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        math::Mat4 model = math::Mat4::identity();
        math::mat4Translate(model, 0.0f, 0.0f, -3.0f);

        const std::optional<math::Bounds::AABB> meshAABB =
            math::Bounds::AABB{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };

        const auto decision = detail::decideFrustumCulling(frustum, model, {}, {}, meshAABB, {});
        CHECK(decision.tested);
        CHECK_FALSE(decision.culled);
    }

    TEST_CASE("outside AABB is tested and culled")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        math::Mat4 model = math::Mat4::identity();
        math::mat4Translate(model, 100.0f, 0.0f, -3.0f);

        const std::optional<math::Bounds::AABB> meshAABB =
            math::Bounds::AABB{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };

        const auto decision = detail::decideFrustumCulling(frustum, model, {}, {}, meshAABB, {});
        CHECK(decision.tested);
        CHECK(decision.culled);
    }

    TEST_CASE("sphere fallback is used when AABB is missing")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        math::Mat4 model = math::Mat4::identity();
        math::mat4Translate(model, 0.0f, 0.0f, -3.0f);

        const std::optional<math::Bounds::Sphere> meshSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };

        const auto decision = detail::decideFrustumCulling(frustum, model, {}, {}, {}, meshSphere);
        CHECK(decision.tested);
        CHECK_FALSE(decision.culled);
    }

    TEST_CASE("AABB takes priority over sphere")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        math::Mat4 model = math::Mat4::identity();
        math::mat4Translate(model, 0.0f, 0.0f, -3.0f);

        const std::optional<math::Bounds::AABB> commandAABB =
            math::Bounds::AABB{ { 100.0f, 100.0f, 100.0f }, { 101.0f, 101.0f, 101.0f } };
        const std::optional<math::Bounds::Sphere> commandSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, 1.0f };

        const auto decision = detail::decideFrustumCulling(frustum, model, commandAABB, commandSphere, {}, {});
        CHECK(decision.tested);
        CHECK(decision.culled);
    }

    TEST_CASE("no bounds means no culling test")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        const auto decision = detail::decideFrustumCulling(frustum, math::Mat4::identity(), {}, {}, {}, {});
        CHECK_FALSE(decision.tested);
        CHECK_FALSE(decision.culled);
    }

    TEST_CASE("sheared transforms keep visible spheres conservative")
    {
        math::Mat4 proj;
        math::mat4Perspective(proj, 1.0f, 1.0f, 0.1f, 100.0f);
        const math::Frustum frustum = math::Frustum::fromViewProj(proj);

        math::Mat4 model = math::Mat4::identity();
        model[4] = 0.75f;
        model[14] = -3.0f;

        const std::optional<math::Bounds::Sphere> meshSphere = math::Bounds::Sphere{ { 0.0f, 0.0f, 0.0f }, 0.4f };

        const auto decision = detail::decideFrustumCulling(frustum, model, {}, {}, {}, meshSphere);
        CHECK(decision.tested);
        CHECK_FALSE(decision.culled);
    }
}
