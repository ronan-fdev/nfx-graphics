#if defined(__linux__)
    #include "../App.h"

    #include <nfx/graphics/gl/core/Context.h>

    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <GL/glx.h>

    #include <cstdio>

typedef GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace nfx::samples
{
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

        Display* display = XOpenDisplay(nullptr);
        if (!display)
        {
            std::fprintf(stderr, "Cannot open X display\n");
            return 1;
        }

        GLXContext ctx = nullptr;
        Colormap colormap = 0;
        Window win = 0;

        auto cleanup = [&] {
            if (ctx)
            {
                glXMakeCurrent(display, None, nullptr);
                glXDestroyContext(display, ctx);
                ctx = nullptr;
            }

            if (win)
            {
                XDestroyWindow(display, win);
                win = 0;
            }

            if (colormap)
            {
                XFreeColormap(display, colormap);
                colormap = 0;
            }

            XCloseDisplay(display);
        };

        int screen = DefaultScreen(display);

        // clang-format off
        static const int fbAttribs[] = {
            GLX_X_RENDERABLE,  true,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE,   GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE,      8,
            GLX_GREEN_SIZE,    8,
            GLX_BLUE_SIZE,     8,
            GLX_ALPHA_SIZE,    8,
            GLX_DEPTH_SIZE,    24,
            GLX_STENCIL_SIZE,  8,
            GLX_DOUBLEBUFFER,  true,
            None
        };
        // clang-format on

        int fbCount = 0;
        GLXFBConfig* fbc = glXChooseFBConfig(display, screen, fbAttribs, &fbCount);
        if (!fbc || fbCount == 0)
        {
            std::fprintf(stderr, "No matching GLX framebuffer config found\n");
            if (fbc)
            {
                XFree(fbc);
            }
            cleanup();
            return 1;
        }
        GLXFBConfig bestFbc = fbc[0];
        XFree(fbc);

        XVisualInfo* vi = glXGetVisualFromFBConfig(display, bestFbc);
        if (!vi)
        {
            std::fprintf(stderr, "glXGetVisualFromFBConfig failed\n");
            cleanup();
            return 1;
        }

        Window root = DefaultRootWindow(display);
        XSetWindowAttributes swa{};
        colormap = XCreateColormap(display, root, vi->visual, AllocNone);
        if (!colormap)
        {
            std::fprintf(stderr, "XCreateColormap failed\n");
            XFree(vi);
            cleanup();
            return 1;
        }

        swa.colormap = colormap;
        swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

        win = XCreateWindow(
            display,
            root,
            0,
            0,
            static_cast<unsigned>(config.width),
            static_cast<unsigned>(config.height),
            0,
            vi->depth,
            InputOutput,
            vi->visual,
            CWColormap | CWEventMask,
            &swa);
        XFree(vi);

        if (!win)
        {
            std::fprintf(stderr, "XCreateWindow failed\n");
            cleanup();
            return 1;
        }

        XStoreName(display, win, title);
        XMapWindow(display, win);

        Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", False);
        if (wmDelete == None)
        {
            std::fprintf(stderr, "XInternAtom(WM_DELETE_WINDOW) failed\n");
            cleanup();
            return 1;
        }

        XSetWMProtocols(display, win, &wmDelete, 1);

        auto glXCreateContextAttribsARB = reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
            glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXCreateContextAttribsARB")));

        if (!glXCreateContextAttribsARB)
        {
            std::fprintf(stderr, "glXCreateContextAttribsARB not available\n");
            cleanup();
            return 1;
        }

        // clang-format off
        static const int ctxAttribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, config.glMajor,
            GLX_CONTEXT_MINOR_VERSION_ARB, config.glMinor,
            GLX_CONTEXT_PROFILE_MASK_ARB,  GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            None
        };
        // clang-format on

        ctx = glXCreateContextAttribsARB(display, bestFbc, nullptr, True, ctxAttribs);
        if (!ctx)
        {
            std::fprintf(stderr, "Failed to create OpenGL %d.%d core context\n", config.glMajor, config.glMinor);
            cleanup();
            return 1;
        }

        if (!glXMakeCurrent(display, win, ctx))
        {
            std::fprintf(stderr, "glXMakeCurrent failed\n");
            cleanup();
            return 1;
        }

        // Enable VSync
        auto glXSwapIntervalEXT_ = reinterpret_cast<void (*)(Display*, GLXDrawable, int)>(
            glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXSwapIntervalEXT")));
        if (glXSwapIntervalEXT_)
        {
            glXSwapIntervalEXT_(display, win, 1);
        }

        if (!nfx::graphics::gl::Context::initialize())
        {
            std::fprintf(stderr, "Failed to initialize nfx OpenGL function table\n");
            cleanup();
            return 1;
        }

        const auto& ctxInfo = nfx::graphics::gl::Context::current();
        const auto& gl = ctxInfo.functions();
        const char* vendor = reinterpret_cast<const char*>(gl.glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(gl.glGetString(GL_RENDERER));
        const char* version = reinterpret_cast<const char*>(gl.glGetString(GL_VERSION));
        std::fprintf(stdout, "OpenGL vendor  : %s\n", vendor ? vendor : "<unavailable>");
        std::fprintf(stdout, "OpenGL renderer: %s\n", renderer ? renderer : "<unavailable>");
        std::fprintf(stdout, "OpenGL version : %s\n", version ? version : "<unavailable>");
        std::fprintf(
            stdout,
            "nfx::graphics ctx limits : colorAttachments=%d, textureUnits=%d, vertexAttribs=%d\n",
            ctxInfo.maxColorAttachments(),
            ctxInfo.maxTextureImageUnits(),
            ctxInfo.maxVertexAttribs());

        if (onInit)
        {
            onInit();
        }

        int winWidth = config.width, winHeight = config.height;
        bool running = true;
        while (running)
        {
            while (XPending(display))
            {
                XEvent ev;
                XNextEvent(display, &ev);

                if (ev.type == ClientMessage && static_cast<Atom>(ev.xclient.data.l[0]) == wmDelete)
                {
                    running = false;
                }
                if (ev.type == KeyPress)
                {
                    KeySym key = XLookupKeysym(&ev.xkey, 0);
                    if (key == XK_Escape)
                    {
                        running = false;
                    }
                }
                if (ev.type == ConfigureNotify)
                {
                    winWidth = ev.xconfigure.width;
                    winHeight = ev.xconfigure.height;
                }
            }

            onRender(winWidth, winHeight);

            glXSwapBuffers(display, win);
        }

        if (onShutdown)
        {
            onShutdown();
        }

        cleanup();

        return 0;
    }
} // namespace nfx::samples
#endif
