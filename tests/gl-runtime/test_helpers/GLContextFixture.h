#pragma once

#include <nfx/graphics/gl/core/Context.h>

#ifdef __linux__
    #include <X11/Xlib.h>
    #include <GL/glx.h>
#elif defined(_WIN32)
    #include <bit>
    #include <cstdint>
    #include <type_traits>

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/wglext.h>
#endif

namespace nfx::tests
{
#ifdef __linux__
    class GLContextFixture
    {
    public:
        GLContextFixture()
        {
            m_display = XOpenDisplay(nullptr);
            if (m_display == nullptr)
            {
                return;
            }

            int fbCount = 0;
            // clang-format off
            static const int fbAttribs[] = {
                GLX_X_RENDERABLE,  true,
                GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                GLX_RENDER_TYPE,   GLX_RGBA_BIT,
                GLX_RED_SIZE,      8,
                GLX_GREEN_SIZE,    8,
                GLX_BLUE_SIZE,     8,
                GLX_ALPHA_SIZE,    8,
                GLX_DEPTH_SIZE,    24,
                None
            };
            // clang-format on

            GLXFBConfig* fbConfigs = glXChooseFBConfig(m_display, DefaultScreen(m_display), fbAttribs, &fbCount);
            if (fbConfigs == nullptr || fbCount == 0)
            {
                if (fbConfigs != nullptr)
                {
                    XFree(fbConfigs);
                }
                return;
            }

            const GLXFBConfig fbConfig = fbConfigs[0];
            XFree(fbConfigs);

            // clang-format off
            static const int ctxAttribs[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
                GLX_CONTEXT_MINOR_VERSION_ARB, 5,
                GLX_CONTEXT_PROFILE_MASK_ARB,  GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                None
            };
            // clang-format on

            auto glXCreateContextAttribsARB =
                reinterpret_cast<GLXContext (*)(Display*, GLXFBConfig, GLXContext, Bool, const int*)>(
                    glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXCreateContextAttribsARB")));

            if (glXCreateContextAttribsARB == nullptr)
            {
                m_context = glXCreateNewContext(m_display, fbConfig, GLX_RGBA_TYPE, nullptr, True);
            }
            else
            {
                m_context = glXCreateContextAttribsARB(m_display, fbConfig, nullptr, True, ctxAttribs);
            }

            if (m_context == nullptr)
            {
                return;
            }

            const int pbufferAttribs[] = {
                GLX_PBUFFER_WIDTH, 1, GLX_PBUFFER_HEIGHT, 1, None,
            };
            m_pbuffer = glXCreatePbuffer(m_display, fbConfig, pbufferAttribs);
            if (m_pbuffer == 0)
            {
                glXDestroyContext(m_display, m_context);
                m_context = nullptr;
                return;
            }

            if (!glXMakeContextCurrent(m_display, m_pbuffer, m_pbuffer, m_context))
            {
                glXDestroyPbuffer(m_display, m_pbuffer);
                m_pbuffer = 0;
                glXDestroyContext(m_display, m_context);
                m_context = nullptr;
                return;
            }

            m_available = true;
        }

        ~GLContextFixture()
        {
            nfx::graphics::gl::Context::teardown();

            if (m_display != nullptr && m_context != nullptr)
            {
                glXMakeContextCurrent(m_display, None, None, nullptr);
            }
            if (m_display != nullptr && m_pbuffer != 0)
            {
                glXDestroyPbuffer(m_display, m_pbuffer);
                m_pbuffer = 0;
            }
            if (m_display != nullptr && m_context != nullptr)
            {
                glXDestroyContext(m_display, m_context);
                m_context = nullptr;
            }
            if (m_display != nullptr)
            {
                XCloseDisplay(m_display);
                m_display = nullptr;
            }
        }

        [[nodiscard]] bool available() const noexcept { return m_available; }

    private:
        Display* m_display = nullptr;
        GLXContext m_context = nullptr;
        GLXPbuffer m_pbuffer = 0;
        bool m_available = false;
    };
#elif defined(_WIN32)
    class GLContextFixture
    {
    public:
        GLContextFixture()
        {
            const HINSTANCE hInstance = GetModuleHandleA(nullptr);
            if (hInstance == nullptr)
            {
                return;
            }

            constexpr const char* kTmpClassName = "nfx_tests_tmp";
            constexpr const char* kAppClassName = "nfx_tests_app";

            if (!createWindowClass(hInstance, kTmpClassName, m_tmpClassRegistered))
            {
                return;
            }

            m_hwndTmp = createWindow(hInstance, kTmpClassName);
            if (m_hwndTmp == nullptr)
            {
                return;
            }
            m_hdcTmp = GetDC(m_hwndTmp);
            if (m_hdcTmp == nullptr)
            {
                return;
            }

            if (!setLegacyPixelFormat(m_hdcTmp))
            {
                return;
            }

            m_hglrcTmp = wglCreateContext(m_hdcTmp);
            if (m_hglrcTmp == nullptr || !wglMakeCurrent(m_hdcTmp, m_hglrcTmp))
            {
                return;
            }

            const auto wglCreateContextAttribsARB =
                loadWglProc<PFNWGLCREATECONTEXTATTRIBSARBPROC>("wglCreateContextAttribsARB");
            const auto wglChoosePixelFormatARB = loadWglProc<PFNWGLCHOOSEPIXELFORMATARBPROC>("wglChoosePixelFormatARB");

            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(m_hglrcTmp);
            m_hglrcTmp = nullptr;
            ReleaseDC(m_hwndTmp, m_hdcTmp);
            m_hdcTmp = nullptr;
            DestroyWindow(m_hwndTmp);
            m_hwndTmp = nullptr;

            if (wglCreateContextAttribsARB == nullptr || wglChoosePixelFormatARB == nullptr)
            {
                return;
            }

            if (!createWindowClass(hInstance, kAppClassName, m_appClassRegistered))
            {
                return;
            }

            m_hwnd = createWindow(hInstance, kAppClassName);
            if (m_hwnd == nullptr)
            {
                return;
            }
            m_hdc = GetDC(m_hwnd);
            if (m_hdc == nullptr)
            {
                return;
            }

            if (!setModernPixelFormat(m_hdc, wglChoosePixelFormatARB))
            {
                return;
            }

            // clang-format off
            int ctxAttribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 5,
                WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                0
            };
            // clang-format on

            m_hglrc = wglCreateContextAttribsARB(m_hdc, nullptr, ctxAttribs);
            if (m_hglrc == nullptr || !wglMakeCurrent(m_hdc, m_hglrc))
            {
                return;
            }

            m_available = true;
        }

        ~GLContextFixture()
        {
            nfx::graphics::gl::Context::teardown();

            if (m_hglrcTmp != nullptr)
            {
                wglMakeCurrent(nullptr, nullptr);
                wglDeleteContext(m_hglrcTmp);
                m_hglrcTmp = nullptr;
            }

            if (m_hdcTmp != nullptr && m_hwndTmp != nullptr)
            {
                ReleaseDC(m_hwndTmp, m_hdcTmp);
                m_hdcTmp = nullptr;
            }

            if (m_hwndTmp != nullptr)
            {
                DestroyWindow(m_hwndTmp);
                m_hwndTmp = nullptr;
            }

            if (m_hglrc != nullptr)
            {
                wglMakeCurrent(nullptr, nullptr);
                wglDeleteContext(m_hglrc);
                m_hglrc = nullptr;
            }

            if (m_hdc != nullptr && m_hwnd != nullptr)
            {
                ReleaseDC(m_hwnd, m_hdc);
                m_hdc = nullptr;
            }

            if (m_hwnd != nullptr)
            {
                DestroyWindow(m_hwnd);
                m_hwnd = nullptr;
            }

            const HINSTANCE hInstance = GetModuleHandleA(nullptr);
            if (hInstance != nullptr)
            {
                if (m_appClassRegistered)
                {
                    UnregisterClassA("nfx_tests_app", hInstance);
                    m_appClassRegistered = false;
                }
                if (m_tmpClassRegistered)
                {
                    UnregisterClassA("nfx_tests_tmp", hInstance);
                    m_tmpClassRegistered = false;
                }
            }
        }

        [[nodiscard]] bool available() const noexcept { return m_available; }

    private:
        template <typename T>
        static T loadWglProc(const char* name)
        {
            static_assert(std::is_pointer_v<T>, "T must be pointer type");
            static_assert(sizeof(T) == sizeof(std::uintptr_t), "Unexpected pointer size mismatch");

            const PROC raw = wglGetProcAddress(name);
            if (raw == nullptr)
            {
                return nullptr;
            }
            return std::bit_cast<T>(reinterpret_cast<std::uintptr_t>(raw));
        }

        static bool createWindowClass(HINSTANCE hInstance, const char* className, bool& registered)
        {
            WNDCLASSA wc{};
            wc.style = CS_OWNDC;
            wc.lpfnWndProc = DefWindowProcA;
            wc.hInstance = hInstance;
            wc.lpszClassName = className;

            const ATOM cls = RegisterClassA(&wc);
            if (cls == 0 && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
            {
                return false;
            }
            registered = true;
            return true;
        }

        static HWND createWindow(HINSTANCE hInstance, const char* className)
        {
            return CreateWindowExA(
                0,
                className,
                "nfx-graphics-tests",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                1,
                1,
                nullptr,
                nullptr,
                hInstance,
                nullptr);
        }

        static bool setLegacyPixelFormat(HDC hdc)
        {
            PIXELFORMATDESCRIPTOR pfd{};
            pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
            pfd.nVersion = 1;
            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.cColorBits = 32;
            pfd.cDepthBits = 24;
            pfd.iLayerType = PFD_MAIN_PLANE;

            const int pixelFormat = ChoosePixelFormat(hdc, &pfd);
            if (pixelFormat <= 0)
            {
                return false;
            }
            return SetPixelFormat(hdc, pixelFormat, &pfd) == TRUE;
        }

        static bool setModernPixelFormat(HDC hdc, PFNWGLCHOOSEPIXELFORMATARBPROC choosePixelFormat)
        {
            // clang-format off
            const int pfAttribs[] = {
                WGL_DRAW_TO_WINDOW_ARB, true,
                WGL_SUPPORT_OPENGL_ARB, true,
                WGL_DOUBLE_BUFFER_ARB,  true,
                WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB,     32,
                WGL_DEPTH_BITS_ARB,     24,
                WGL_STENCIL_BITS_ARB,   8,
                0
            };
            // clang-format on

            int pixelFormat = 0;
            UINT numFormats = 0;
            if (!choosePixelFormat(hdc, pfAttribs, nullptr, 1, &pixelFormat, &numFormats) || numFormats == 0)
            {
                return false;
            }

            PIXELFORMATDESCRIPTOR pfd{};
            if (DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd) == 0)
            {
                return false;
            }

            return SetPixelFormat(hdc, pixelFormat, &pfd) == TRUE;
        }

        HWND m_hwndTmp = nullptr;
        HDC m_hdcTmp = nullptr;
        HGLRC m_hglrcTmp = nullptr;

        HWND m_hwnd = nullptr;
        HDC m_hdc = nullptr;
        HGLRC m_hglrc = nullptr;
        bool m_tmpClassRegistered = false;
        bool m_appClassRegistered = false;
        bool m_available = false;
    };
#endif
} // namespace nfx::tests
