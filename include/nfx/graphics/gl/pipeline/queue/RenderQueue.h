#pragma once

/**
 * \file RenderQueue.h
 * \brief Declares the per-frame render queue used to collect draw commands.
 */

#include "RenderCommand.h"

#include <algorithm>
#include <cassert>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Per-frame render queue collecting RenderCommand values.
     *
     * The application submits RenderCommand values each frame, then a render pass executes
     * commands from this queue with the desired ordering policy.
     */
    class RenderQueue final
    {
    public:
        /**
         * \brief Command execution ordering policy.
         */
        enum class Order
        {
            BySubmission, ///< Commands drawn in submission order.
            BySortKey,    ///< Commands sorted by sortKey to reduce material state changes.
        };

        RenderQueue() = default;

        /**
         * \brief Appends one draw command to the queue.
         * \param cmd Draw command to enqueue.
         */
        void submit(RenderCommand cmd)
        {
            if (cmd.instanceCount < 1)
            {
                assert(cmd.instanceCount >= 1 && "RenderQueue::submit: instanceCount must be >= 1");
                cmd.instanceCount = 1;
            }
            if (cmd.sortKey.isZero())
            {
                cmd.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, cmd.material.id, 0);
            }
            m_commands.push_back(cmd);
        }

        /**
         * \brief Removes all queued commands.
         */
        void clear() { m_commands.clear(); }

        /**
         * \brief Sorts queued commands according to the given ordering policy.
         *
         * \c BySubmission is a no-op. \c BySortKey applies a stable sort by sortKey,
         * preserving relative order of commands with equal keys.
         * \param order Ordering policy to apply.
         */
        void sort(Order order)
        {
            if (order == Order::BySortKey)
            {
                std::stable_sort(
                    m_commands.begin(), m_commands.end(), [](const RenderCommand& a, const RenderCommand& b) {
                        return a.sortKey < b.sortKey;
                    });
            }
        }

        /**
         * \brief Returns queued commands in their current order.
         */
        [[nodiscard]] const std::vector<RenderCommand>& commands() const noexcept { return m_commands; }

        /**
         * \brief Returns true when no commands are queued.
         */
        [[nodiscard]] bool empty() const noexcept { return m_commands.empty(); }

        /**
         * \brief Returns the number of queued commands.
         */
        [[nodiscard]] std::size_t size() const noexcept { return m_commands.size(); }

    private:
        std::vector<RenderCommand> m_commands;
    };
} // namespace nfx::graphics::gl
