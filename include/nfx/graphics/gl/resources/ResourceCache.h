#pragma once

/**
 * \file ResourceCache.h
 * \brief Declares a generic cache mapping typed opaque handles to owned resource instances.
 */

#include "Handle.h"

#include <cstdint>
#include <unordered_map>

namespace nfx::graphics::gl
{
    /**
     * \brief Generic cache storing resources behind typed opaque handles.
     * \tparam Tag Marker type used by the associated Handle.
     * \tparam Resource Stored resource type.
     */
    template <typename Tag, typename Resource>
    class ResourceCache
    {
    public:
        using HandleType = Handle<Tag>; ///< Strongly typed handle associated with the cached resource type

        ResourceCache() = default;

        ResourceCache(const ResourceCache&) = delete;
        ResourceCache& operator=(const ResourceCache&) = delete;

        ResourceCache(ResourceCache&&) = default;
        ResourceCache& operator=(ResourceCache&&) = default;

        /**
         * \brief Inserts a resource into the cache and returns its newly assigned handle.
         * \param resource Resource value to store.
         * \return Stable handle assigned to the stored resource.
         */
        [[nodiscard]] HandleType add(Resource resource)
        {
            HandleType handle{ m_nextId++ };
            m_resources.emplace(handle, std::move(resource));
            return handle;
        }

        /**
         * \brief Returns a mutable pointer to a cached resource.
         * \param handle Handle identifying the resource.
         * \return nullptr when the handle is not present in the cache.
         */
        [[nodiscard]] Resource* get(HandleType handle) noexcept
        {
            auto it = m_resources.find(handle);
            return it != m_resources.end() ? &it->second : nullptr;
        }

        /**
         * \brief Returns a const pointer to a cached resource.
         * \param handle Handle identifying the resource.
         * \return nullptr when the handle is not present in the cache.
         */
        [[nodiscard]] const Resource* get(HandleType handle) const noexcept
        {
            auto it = m_resources.find(handle);
            return it != m_resources.end() ? &it->second : nullptr;
        }

        /**
         * \brief Returns whether the cache contains a given handle.
         * \param handle Handle to test.
         * \return True when the handle exists in the cache, false otherwise.
         */
        [[nodiscard]] bool contains(HandleType handle) const noexcept { return m_resources.contains(handle); }

        /**
         * \brief Removes a resource from the cache.
         * \param handle Handle identifying the resource to remove.
         * \return True when a resource was removed, false otherwise.
         */
        bool remove(HandleType handle) { return m_resources.erase(handle) > 0; }

        /**
         * \brief Removes all resources from the cache.
         */
        void clear() { m_resources.clear(); }

        /**
         * \brief Returns the number of cached resources.
         * \return Number of cached resources.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_resources.size(); }

        /**
         * \brief Returns whether the cache contains no resources.
         * \return True when the cache is empty, false otherwise.
         */
        [[nodiscard]] bool empty() const noexcept { return m_resources.empty(); }

        /**
         * \brief Invokes \p fn for each cached resource.
         * \param fn Callable with signature \c void(HandleType, const Resource&).
         */
        template <typename Fn>
        void forEach(Fn&& fn) const
        {
            for (const auto& [handle, resource] : m_resources)
            {
                fn(handle, resource);
            }
        }

    protected:
        std::unordered_map<HandleType, Resource> m_resources;
        std::uint64_t m_nextId = 1;
    };
} // namespace nfx::graphics::gl
