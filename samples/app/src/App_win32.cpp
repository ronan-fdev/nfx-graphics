#if defined(_WIN32)
    #include "../App.h"

    #include <nfx/graphics/gl/core/Context.h>

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/wglext.h>

    #include <bit>
    #include <cstdint>
    #include <cstdio>
    #include <type_traits>

namespace nfx::samples
{
    namespace
    {
        template <typename T>
        T loadWglProc(const char* name)
        {
            static_assert(std::is_pointer_v<T>, "T must be a pointer type");
            static_assert(sizeof(T) == sizeof(std::uintptr_t), "Unexpected pointer size mismatch");

            const PROC raw = wglGetProcAddress(name);
            if (!raw)
            {
                return nullptr;
            }

            const std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(raw);
            return std::bit_cast<T>(addr);
        }

        bool s_running = true;
        int s_width = 800;
        int s_height = 600;

        LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            switch (msg)
            {
                case WM_CLOSE:
                case WM_DESTROY:
                    s_running = false;
                    PostQuitMessage(0);
                    return 0;
                case WM_KEYDOWN:
                    if (wParam == VK_ESCAPE)
                    {
                        s_running = false;
                        PostQuitMessage(0);
                    }
                    return 0;
                case WM_SIZE:
                    s_width = LOWORD(lParam);
                    s_height = HIWORD(lParam);
                    return 0;
                default:
                    return DefWindowProcA(hwnd, msg, wParam, lParam);
            }
        }
    } // namespace

    int run(
        const AppConfig& config,
        std::function<void()> onInit,
        std::function<void(int width, int height)> onRender,
        std::function<void()> onShutdown)
    {
        if (!onRender)
        {
            std::fprintf(stderr, "onRender callback is required\n");
            return 1;
        }

        const char* title = config.title ? config.title : "nfx-graphics";

        s_running = true;
        s_width = config.width;
        s_height = config.height;

        HINSTANCE hInstance = GetModuleHandle(nullptr);
        if (!hInstance)
        {
            std::fprintf(stderr, "GetModuleHandle failed\n");
            return 1;
        }

        constexpr const char* kTmpClassName = "nfx_tmp";
        constexpr const char* kAppClassName = "nfx_app";

        ATOM tmpClassAtom = 0;
        HWND hwndTmp = nullptr;
        HDC hdcTmp = nullptr;
        HGLRC hrcTmp = nullptr;

        auto cleanupTmp = [&] {
            if (hrcTmp)
            {
                wglMakeCurrent(nullptr, nullptr);
                wglDeleteContext(hrcTmp);
                hrcTmp = nullptr;
            }

            if (hdcTmp && hwndTmp)
            {
                ReleaseDC(hwndTmp, hdcTmp);
                hdcTmp = nullptr;
            }

            if (hwndTmp)
            {
                DestroyWindow(hwndTmp);
                hwndTmp = nullptr;
            }

            if (tmpClassAtom)
            {
                UnregisterClassA(kTmpClassName, hInstance);
                tmpClassAtom = 0;
            }
        };

        // Temporary window to load WGL extensions
        WNDCLASSEXA wcTmp{};
        wcTmp.cbSize = sizeof(wcTmp);
        wcTmp.style = CS_OWNDC;
        wcTmp.lpfnWndProc = DefWindowProcA;
        wcTmp.hInstance = hInstance;
        wcTmp.lpszClassName = kTmpClassName;
        tmpClassAtom = RegisterClassExA(&wcTmp);
        if (!tmpClassAtom)
        {
            std::fprintf(stderr, "RegisterClassExA(nfx_tmp) failed\n");
            return 1;
        }

        hwndTmp = CreateWindowExA(
            0, kTmpClassName, "", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, nullptr, nullptr, hInstance, nullptr);
        if (!hwndTmp)
        {
            std::fprintf(stderr, "CreateWindowExA(nfx_tmp) failed\n");
            cleanupTmp();
            return 1;
        }

        hdcTmp = GetDC(hwndTmp);
        if (!hdcTmp)
        {
            std::fprintf(stderr, "GetDC(nfx_tmp) failed\n");
            cleanupTmp();
            return 1;
        }

        PIXELFORMATDESCRIPTOR pfdTmp{};
        pfdTmp.nSize = sizeof(pfdTmp);
        pfdTmp.nVersion = 1;
        pfdTmp.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfdTmp.iPixelType = PFD_TYPE_RGBA;
        pfdTmp.cColorBits = 32;
        pfdTmp.cDepthBits = 24;
        int pixelFormatTmp = ChoosePixelFormat(hdcTmp, &pfdTmp);
        if (pixelFormatTmp <= 0 || !SetPixelFormat(hdcTmp, pixelFormatTmp, &pfdTmp))
        {
            std::fprintf(stderr, "SetPixelFormat(nfx_tmp) failed\n");
            cleanupTmp();
            return 1;
        }

        hrcTmp = wglCreateContext(hdcTmp);
        if (!hrcTmp || !wglMakeCurrent(hdcTmp, hrcTmp))
        {
            std::fprintf(stderr, "Temporary WGL context creation failed\n");
            cleanupTmp();
            return 1;
        }

        auto wglCreateContextAttribsARB = loadWglProc<PFNWGLCREATECONTEXTATTRIBSARBPROC>("wglCreateContextAttribsARB");
        auto wglChoosePixelFormatARB = loadWglProc<PFNWGLCHOOSEPIXELFORMATARBPROC>("wglChoosePixelFormatARB");

        cleanupTmp();

        if (!wglCreateContextAttribsARB || !wglChoosePixelFormatARB)
        {
            MessageBoxA(nullptr, "WGL extensions not available", "Error", MB_ICONERROR);
            return 1;
        }

        ATOM appClassAtom = 0;
        HWND hwnd = nullptr;
        HDC hdc = nullptr;
        HGLRC hrc = nullptr;

        auto cleanupApp = [&] {
            if (hrc)
            {
                wglMakeCurrent(nullptr, nullptr);
                wglDeleteContext(hrc);
                hrc = nullptr;
            }

            if (hdc && hwnd)
            {
                ReleaseDC(hwnd, hdc);
                hdc = nullptr;
            }

            if (hwnd)
            {
                DestroyWindow(hwnd);
                hwnd = nullptr;
            }

            if (appClassAtom)
            {
                UnregisterClassA(kAppClassName, hInstance);
                appClassAtom = 0;
            }
        };

        // Real window
        WNDCLASSEXA wc{};
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = wndProc;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.lpszClassName = kAppClassName;
        appClassAtom = RegisterClassExA(&wc);
        if (!appClassAtom)
        {
            std::fprintf(stderr, "RegisterClassExA(nfx_app) failed\n");
            return 1;
        }

        hwnd = CreateWindowExA(
            0,
            kAppClassName,
            title,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            config.width,
            config.height,
            nullptr,
            nullptr,
            hInstance,
            nullptr);
        if (!hwnd)
        {
            std::fprintf(stderr, "CreateWindowExA(nfx_app) failed\n");
            cleanupApp();
            return 1;
        }

        hdc = GetDC(hwnd);
        if (!hdc)
        {
            std::fprintf(stderr, "GetDC(nfx_app) failed\n");
            cleanupApp();
            return 1;
        }

        // clang-format off
        const int pfAttribs[] = {
            WGL_DRAW_TO_WINDOW_ARB, true,
            WGL_SUPPORT_OPENGL_ARB, true,
            WGL_DOUBLE_BUFFER_ARB,  true,
            WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,     32,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            0
        };
        // clang-format on

        int pixelFormat = 0;
        UINT numFormats = 0;
        if (!wglChoosePixelFormatARB(hdc, pfAttribs, nullptr, 1, &pixelFormat, &numFormats) || numFormats == 0)
        {
            std::fprintf(stderr, "wglChoosePixelFormatARB failed\n");
            cleanupApp();
            return 1;
        }

        PIXELFORMATDESCRIPTOR pfd{};
        if (DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd) == 0 || !SetPixelFormat(hdc, pixelFormat, &pfd))
        {
            std::fprintf(stderr, "SetPixelFormat(nfx_app) failed\n");
            cleanupApp();
            return 1;
        }

        // clang-format off
        int ctxAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, config.glMajor,
            WGL_CONTEXT_MINOR_VERSION_ARB, config.glMinor,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        // clang-format on

        hrc = wglCreateContextAttribsARB(hdc, nullptr, ctxAttribs);
        if (!hrc)
        {
            MessageBoxA(nullptr, "Failed to create OpenGL core context", "Error", MB_ICONERROR);
            cleanupApp();
            return 1;
        }

        if (!wglMakeCurrent(hdc, hrc))
        {
            std::fprintf(stderr, "wglMakeCurrent failed\n");
            cleanupApp();
            return 1;
        }

        // Enable VSync
        auto wglSwapIntervalEXT_ = loadWglProc<PFNWGLSWAPINTERVALEXTPROC>("wglSwapIntervalEXT");
        if (wglSwapIntervalEXT_)
        {
            wglSwapIntervalEXT_(1);
        }

        if (!nfx::graphics::gl::Context::initialize())
        {
            std::fprintf(stderr, "Failed to initialize nfx OpenGL function table\n");
            cleanupApp();
            return 1;
        }

        const auto& gl = nfx::graphics::gl::Context::current().functions();
        const char* vendor = reinterpret_cast<const char*>(gl.glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(gl.glGetString(GL_RENDERER));
        const char* version = reinterpret_cast<const char*>(gl.glGetString(GL_VERSION));
        std::fprintf(stdout, "OpenGL vendor  : %s\n", vendor ? vendor : "<unavailable>");
        std::fprintf(stdout, "OpenGL renderer: %s\n", renderer ? renderer : "<unavailable>");
        std::fprintf(stdout, "OpenGL version : %s\n", version ? version : "<unavailable>");

        if (onInit)
        {
            onInit();
        }

        while (s_running)
        {
            MSG msg{};
            while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    s_running = false;
                }

                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }

            onRender(s_width, s_height);

            if (!SwapBuffers(hdc))
            {
                std::fprintf(stderr, "SwapBuffers failed\n");
                break;
            }
        }

        if (onShutdown)
        {
            onShutdown();
        }

        cleanupApp();

        return 0;
    }
} // namespace nfx::samples
#endif
