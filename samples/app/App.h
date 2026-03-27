#pragma once

#include "Clock.h"
#include "ObjLoader.h"
#include "TextureLoader.h"

#include <functional>

namespace nfx::samples
{
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
        std::function<void(float delta)> onScroll = {});
} // namespace nfx::samples
