#pragma once

/**
 * \file EmbeddedResource.h
 * \brief Declares lightweight views over binary resources embedded at build time.
 */

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace nfx::graphics
{
    /**
     * \brief Represents an embedded binary resource.
     */
    struct EmbeddedResource
    {
        std::string_view name; ///< EmbeddedResource identifier (typically the original filename)
        const uint8_t* data;   ///< Pointer to the embedded binary data
        size_t size;           ///< Size of the resource in bytes

        /**
         * \brief Interprets the resource contents as a string view.
         */
        [[nodiscard]] std::string_view str() const noexcept { return { reinterpret_cast<const char*>(data), size }; }

        /**
         * \brief Returns the raw byte pointer of the resource.
         */
        [[nodiscard]] constexpr const uint8_t* bytes() const noexcept { return data; }

        /**
         * \brief Returns whether the resource contains no data.
         */
        [[nodiscard]] constexpr bool empty() const noexcept { return size == 0; }
    };

    /**
     * \brief Finds a resource by name in a collection.
     * \tparam ResourceArray Collection type exposing begin/end over EmbeddedResource values.
     * \param resources Resource collection to search.
     * \param name Resource identifier to match.
     * \return A pointer to the matching resource, or nullptr when not found.
     */
    template <typename ResourceArray>
    [[nodiscard]] inline const EmbeddedResource* find(const ResourceArray& resources, std::string_view name) noexcept
    {
        auto it = std::find_if(
            std::begin(resources), std::end(resources), [name](const EmbeddedResource& r) { return r.name == name; });

        return it != std::end(resources) ? &(*it) : nullptr;
    }

} // namespace nfx::graphics
