# nfx::graphics

A lightweight, zero-dependency C++20 OpenGL graphics library. Provides the full OpenGL 1.0-4.6 API on Linux/X11 and Windows/WGL through a typed C++ wrapper.

## Requirements

- C++20 compiler (GCC 12+, Clang 15+, MSVC 2022+)
- CMake 3.25+
- OpenGL 4.5+ (Linux/X11 or Windows/WGL)

## Build

Example - build everything in debug:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Public API entry points

- `include/nfx/Graphics.h`
- `include/nfx/Gl.h`

## Project Structure

```
nfx-graphics/
├── include/nfx/
│   ├── Graphics.h                    # top-level nfx::graphics API entry point
│   ├── Gl.h                          # low-level nfx::graphics::gl API entry point
│   └── graphics
│       └── gl/
│           └── core/
│               ├── functions/        # Per-version function classes (Functions_1_0.h-Functions_4_6.h)
│               ├── Context.h         # Per-thread GL function table initialization
│               ├── Functions.h       # Full OpenGL 1.0-4.6 C++ wrapper
│               ├── GlDefinitions.h   # All GL constants
│               └── GlTypes.h         # Core GL type aliases (GLuint, GLfloat, etc.), GLsync and GLDEBUGPROC
└── src/                              # Implementation
```

The function loader resolves GL 1.2+ entry points via `glXGetProcAddress` (X11) or `wglGetProcAddress` (Win32).

## Changelog

See [CHANGELOG.md](CHANGELOG.md).

## License

MIT - see [LICENSE](LICENSE).
