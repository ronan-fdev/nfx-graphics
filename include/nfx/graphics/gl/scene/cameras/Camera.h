#pragma once

/**
 * \file Camera.h
 * \brief Declares the camera data layout shared between CPU-side scene code and GPU uniform buffers.
 */

#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Vec3.h"

#include <algorithm>

namespace nfx::graphics::gl
{
    /**
     * \brief Camera descriptor storing CPU-side state and helpers to build GPU upload data.
     */
    struct Camera
    {
        // clang-format off
        float view[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        }; ///< View matrix (column-major)
        float proj[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        }; ///< Projection matrix (column-major)
        float viewProj[16] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        }; ///< Precomputed projection * view matrix (column-major)
        float position[3] = { 0.f, 0.f, 0.f };  ///< Camera world position
        float direction[3] = { 0.f, 0.f, -1.f }; ///< Camera forward direction
        // clang-format on

        /**
         * \brief std140-compatible camera payload uploaded to the camera uniform buffer.
         */
        struct GpuData
        {
            float view[16];
            float proj[16];
            float viewProj[16]; // proj * view - precomputed to avoid per-vertex mat mul
            float position[3];
            float _pad0 = 0.f;
            float direction[3]; // normalized forward vector
            float _pad1 = 0.f;
        };

        /**
         * \brief Packs the camera state into its GPU payload representation.
         */
        [[nodiscard]] GpuData toGpuData() const noexcept
        {
            return toGpuData(view, proj, viewProj, position, direction);
        }

        /**
         * \brief Packs camera matrices and vectors into a std140-compatible GPU payload.
         * \param view View matrix stored in column-major order.
         * \param proj Projection matrix stored in column-major order.
         * \param viewProj Precomputed projection * view matrix stored in column-major order.
         * \param position Camera world position.
         * \param direction Normalized camera forward direction.
         */
        [[nodiscard]] static GpuData toGpuData(
            const float view[16],
            const float proj[16],
            const float viewProj[16],
            const float position[3],
            const float direction[3]) noexcept
        {
            GpuData d{};
            std::copy_n(view, 16, d.view);
            std::copy_n(proj, 16, d.proj);
            std::copy_n(viewProj, 16, d.viewProj);
            std::copy_n(position, 3, d.position);
            std::copy_n(direction, 3, d.direction);
            return d;
        }

        /**
         * \brief Packs camera matrices and vectors into a std140-compatible GPU payload.
         * \param view View matrix stored in column-major order.
         * \param proj Projection matrix stored in column-major order.
         * \param viewProj Precomputed projection * view matrix stored in column-major order.
         * \param position Camera world position.
         * \param direction Normalized camera forward direction.
         */
        [[nodiscard]] static GpuData toGpuData(
            const math::Mat4& view,
            const math::Mat4& proj,
            const math::Mat4& viewProj,
            const math::Vec3& position,
            const math::Vec3& direction) noexcept
        {
            return toGpuData(view.data(), proj.data(), viewProj.data(), position.data(), direction.data());
        }
    };
} // namespace nfx::graphics::gl
