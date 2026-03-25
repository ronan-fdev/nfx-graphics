# nfx::graphics

A lightweight, zero-dependency C++20 OpenGL graphics library. Provides the full OpenGL 1.0-4.6 API on Linux/X11 and Windows/WGL through a typed C++ wrapper.

## Requirements

- C++20 compiler (GCC 12+, Clang 15+, MSVC 2022+)
- CMake 3.25+
- OpenGL 4.5+ (Linux/X11 or Windows/WGL)

## Build

### CMake options

| Option                       | Default | Description              |
| ---------------------------- | ------- | ------------------------ |
| `NFX_GRAPHICS_BUILD_TESTS`   | `OFF`   | Build unit tests         |
| `NFX_GRAPHICS_BUILD_SAMPLES` | `OFF`   | Build sample executables |

Example - build everything in debug:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DNFX_GRAPHICS_BUILD_TESTS=ON -DNFX_GRAPHICS_BUILD_SAMPLES=ON
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
│       ├── gl/
│       │   ├── core/
│       │   │   ├── buffers/          # Buffer wrappers
│       │   │   ├── framebuffers/     # Framebuffer and renderbuffer wrappers
│       │   │   ├── functions/        # Per-version function classes (Functions_1_0.h-Functions_4_6.h)
│       │   │   ├── Context.h         # Per-thread GL function table initialization
│       │   │   ├── Functions.h       # Full OpenGL 1.0-4.6 C++ wrapper
│       │   │   ├── shaders/          # Shader program wrappers and typed uniforms
│       │   │   ├── textures/         # Sampler and texture wrappers
│       │   │   ├── GlDefinitions.h   # All GL constants
│       │   │   └── GlTypes.h         # Core GL type aliases (GLuint, GLfloat, etc.), GLsync and GLDEBUGPROC
│       │   ├── pipeline/             # High-level wrappers
│       │   └── scene/
│       │       ├── cameras/          # Camera types and orbit camera
│       │       └── lights/           # Camera Light descriptors
│       ├── math/                     # Matrices, vectors, quaternions
│       └── EmbeddedResource.h        # Runtime access to resources embedded at build time
├── samples/                          # Sample applications and shared sample framework
├── src/                              # Implementation
├── tests/                            # Unit tests
└── tools/                            # Build tools and resource generator
```

The function loader resolves GL 1.2+ entry points via `glXGetProcAddress` (X11) or `wglGetProcAddress` (Win32).

## Changelog

See [CHANGELOG.md](CHANGELOG.md).

## License

MIT - see [LICENSE](LICENSE).

## Development dependencies

- [doctest](https://github.com/doctest/doctest) (MIT) - test framework, not shipped with the library.

## Third-party sample dependencies

- [stb_image](https://github.com/nothings/stb) by Sean Barrett and contributors (MIT)
- [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL) resources by Joey de Vries (MIT)
