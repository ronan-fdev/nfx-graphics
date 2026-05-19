#pragma once

#include <cstdlib>
#include <cstring>

#include <nfx/graphics/gl/pipeline/ForwardRenderPath.h>

namespace nfx::tests
{
    /**
     * \brief Detect if running in X11 headless + Mesa software rendering mode (Xvfb).
     */
    [[nodiscard]] inline bool isX11HeadlessSoftwareSession() noexcept
    {
#ifdef __linux__
        const char* display = std::getenv("DISPLAY");
        const char* software = std::getenv("LIBGL_ALWAYS_SOFTWARE");

        return display != nullptr && display[0] != '\0' && software != nullptr && std::strcmp(software, "1") == 0;
#else
        return false;
#endif
    }

    inline void disablePresentPassWhenX11Headless(nfx::graphics::gl::ForwardRenderPath& path) noexcept
    {
        if (!isX11HeadlessSoftwareSession())
        {
            return;
        }

        if (auto* present = path.renderer().pass("Present"))
        {
            present->setEnabled(false);
        }
    }
} // namespace nfx::tests
