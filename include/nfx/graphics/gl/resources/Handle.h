#pragma once

/**
 * \file Handle.h
 * \brief Declares typed opaque resource handles used by the graphics caches.
 */

#include <cstdint>
#include <functional>

namespace nfx::graphics::gl
{
    /**
     * \brief Strongly typed opaque handle identified by a 64-bit id.
     * \tparam Tag Marker type used to prevent mixing handles of different resource kinds.
     */
    template <typename Tag>
    struct Handle
    {
        std::uint64_t id = 0;

        /**
         * \brief Returns whether the handle refers to a valid resource.
         */
        [[nodiscard]] bool isValid() const noexcept { return id != 0; }

        bool operator==(const Handle&) const noexcept = default;
        bool operator!=(const Handle&) const noexcept = default;
    };

    struct MaterialTag ///< Marker type for material handles
    {
    };
    struct MeshTag ///< Marker type for mesh handles
    {
    };
    struct SamplerTag ///< Marker type for sampler handles
    {
    };
    struct ShaderTag ///< Marker type for shader handles
    {
    };
    struct Texture2DTag ///< Marker type for 2D texture handles
    {
    };
    struct TextureCubeTag ///< Marker type for cube texture handles
    {
    };
    struct FontTag ///< Marker type for font handles
    {
    };
    struct TextItemTag ///< Marker type for text item handles
    {
    };

    using MaterialHandle = Handle<MaterialTag>;       ///< Opaque handle referencing a cached material resource
    using MeshHandle = Handle<MeshTag>;               ///< Opaque handle referencing a cached mesh resource
    using SamplerHandle = Handle<SamplerTag>;         ///< Opaque handle referencing a cached sampler resource
    using ShaderHandle = Handle<ShaderTag>;           ///< Opaque handle referencing a cached shader resource
    using Texture2DHandle = Handle<Texture2DTag>;     ///< Opaque handle referencing a cached 2D texture resource
    using TextureCubeHandle = Handle<TextureCubeTag>; ///< Opaque handle referencing a cached cube texture resource
    using FontHandle = Handle<FontTag>;               ///< Opaque handle referencing a cached font resource
    using TextItemHandle = Handle<TextItemTag>;       ///< Opaque handle referencing a text item in TextPass
} // namespace nfx::graphics::gl

/**
 * \brief Hash support for typed resource handles.
 */
template <typename Tag>
struct std::hash<nfx::graphics::gl::Handle<Tag>>
{
    /**
     * \brief Hashes the numeric id stored by the handle.
     */
    std::size_t operator()(const nfx::graphics::gl::Handle<Tag>& h) const noexcept
    {
        return std::hash<std::uint64_t>{}(h.id);
    }
};
