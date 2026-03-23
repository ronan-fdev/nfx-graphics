#pragma once

#include <chrono>

namespace nfx::samples
{
    class Clock
    {
    public:
        Clock()
            : m_last{ now() }
        {}

        float tick()
        {
            auto current = now();
            float dt = std::chrono::duration<float>(current - m_last).count();
            m_last = current;
            return dt;
        }

        float elapsed() const { return std::chrono::duration<float>(now() - m_start).count(); }

    private:
        using TimePoint = std::chrono::steady_clock::time_point;

        static TimePoint now() { return std::chrono::steady_clock::now(); }

        TimePoint m_start{ now() };
        TimePoint m_last;
    };
} // namespace nfx::samples
