#pragma once

#include "Clock.h"
#include "FontLoader.h"
#include "ObjLoader.h"
#include "SkyboxLoader.h"
#include "TextureLoader.h"

#include <functional>

namespace nfx::samples
{
    // clang-format off
    enum class KeyCode : int
    {
        Space     =  32,
        Escape    = 256,
        Enter     = 257,
        Backspace = 258,
        Tab       = 259,
        Left      = 260,
        Right     = 261,
        Up        = 262,
        Down      = 263
    };
    // clang-format on

    struct AppConfig
    {
        const char* title = "nfx-graphics";
        int width = 800;
        int height = 600;
        int glMajor = 4;
        int glMinor = 5;
    };

    int run(
        const AppConfig& config,
        std::function<void()> onInit,
        std::function<void(int width, int height)> onRender,
        std::function<void()> onShutdown = {},
        std::function<void(int x, int y)> onMouseMove = {},
        std::function<void(int button, bool pressed)> onMouseButton = {},
        std::function<void(float delta)> onScroll = {},
        std::function<void(int key, bool pressed)> onKey = {});
} // namespace nfx::samples
