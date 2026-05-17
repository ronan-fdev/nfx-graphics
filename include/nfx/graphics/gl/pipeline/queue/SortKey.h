#pragma once

/**
 * \file SortKey.h
 * \brief Declares helpers for packing render sort keys into a 64-bit integer.
 */

#include <cstdint>

namespace nfx::graphics::gl
{
    /**
     * \brief Strongly typed packed sort key used by render commands.
     */
    struct PackedSortKey final
    {
        constexpr PackedSortKey() noexcept = default;

        [[nodiscard]] constexpr bool isZero() const noexcept { return value == 0; }

        [[nodiscard]] static constexpr PackedSortKey zero() noexcept { return {}; }

        bool operator==(const PackedSortKey&) const noexcept = default;

        [[nodiscard]] friend constexpr bool operator<(PackedSortKey a, PackedSortKey b) noexcept
        {
            return a.value < b.value;
        }

    private:
        std::uint64_t value = 0;

        explicit constexpr PackedSortKey(std::uint64_t v) noexcept
            : value(v)
        {}

        friend struct SortKey;
    };

    /**
     * \brief Utility helpers for 64-bit render sort keys.
     *
     * The key layout is explicit and stable by contract:
     * - opaque       : layer | shader_id | material_id | depth_bucket
     * - back-to-front: layer | inverted_depth_bucket
     *
     * This gives the renderer a single sortable integer while keeping the policy
     * explicit and testable.
     */
    struct SortKey final
    {
        static constexpr std::uint32_t LayerBits = 4;
        static constexpr std::uint32_t ShaderBits = 12;
        static constexpr std::uint32_t MaterialBits = 16;
        static constexpr std::uint32_t DepthBits = 32;

        static constexpr std::uint64_t LayerMask = (1ull << LayerBits) - 1ull;
        static constexpr std::uint64_t ShaderMask = (1ull << ShaderBits) - 1ull;
        static constexpr std::uint64_t MaterialMask = (1ull << MaterialBits) - 1ull;
        static constexpr std::uint64_t DepthMask = (1ull << DepthBits) - 1ull;

        static constexpr std::uint32_t OpaqueLayer = 0;
        static constexpr std::uint32_t TransparentLayer = 1;
        static constexpr std::uint32_t ShadowLayer = 2;
        static constexpr std::uint32_t OverlayLayer = 3;

        static_assert(LayerBits + ShaderBits + MaterialBits + DepthBits == 64);

        /**
         * \brief Packs an opaque render sort key.
         *\n         * Layout: [ layer:4 | shader:12 | material:16 | depth:32 ]
         */
        [[nodiscard]] static constexpr PackedSortKey packOpaque(
            std::uint32_t layer, std::uint32_t shaderId, std::uint32_t materialId, std::uint32_t depthBucket) noexcept
        {
            return PackedSortKey{ ((static_cast<std::uint64_t>(layer) & LayerMask) << 60) |
                                  ((static_cast<std::uint64_t>(shaderId) & ShaderMask) << 48) |
                                  ((static_cast<std::uint64_t>(materialId) & MaterialMask) << 32) |
                                  (static_cast<std::uint64_t>(depthBucket) & DepthMask) };
        }

        /**
         * \brief Packs a back-to-front sort key for transparency.
         *\n         * The depth bucket is inverted so that farther objects sort first with ascending sort.
         */
        [[nodiscard]] static constexpr PackedSortKey packBackToFront(
            std::uint32_t layer, std::uint32_t depthBucket) noexcept
        {
            return PackedSortKey{ ((static_cast<std::uint64_t>(layer) & LayerMask) << 60) |
                                  (~static_cast<std::uint64_t>(depthBucket) & DepthMask) };
        }

        /**
         * \brief Packs a front-to-back depth-only sort key.
         */
        [[nodiscard]] static constexpr PackedSortKey packFrontToBack(
            std::uint32_t layer, std::uint32_t depthBucket) noexcept
        {
            return PackedSortKey{ ((static_cast<std::uint64_t>(layer) & LayerMask) << 60) |
                                  (static_cast<std::uint64_t>(depthBucket) & DepthMask) };
        }

        /**
         * \brief Extracts the layer field from a packed key.
         */
        [[nodiscard]] static constexpr std::uint32_t layer(PackedSortKey key) noexcept
        {
            return static_cast<std::uint32_t>((key.value >> 60) & LayerMask);
        }

        /**
         * \brief Extracts the shader field from an opaque packed key.
         */
        [[nodiscard]] static constexpr std::uint32_t shaderId(PackedSortKey key) noexcept
        {
            return static_cast<std::uint32_t>((key.value >> 48) & ShaderMask);
        }

        /**
         * \brief Extracts the material field from an opaque packed key.
         */
        [[nodiscard]] static constexpr std::uint32_t materialId(PackedSortKey key) noexcept
        {
            return static_cast<std::uint32_t>((key.value >> 32) & MaterialMask);
        }

        /**
         * \brief Extracts the depth bucket from a packed key.
         */
        [[nodiscard]] static constexpr std::uint32_t depthBucket(PackedSortKey key) noexcept
        {
            return static_cast<std::uint32_t>(key.value & DepthMask);
        }
    };
} // namespace nfx::graphics::gl
