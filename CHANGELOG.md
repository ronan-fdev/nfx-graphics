# Changelog

## [Unreleased]

### Added

#### Low-level OpenGL library (function loader + typed GL wrappers)

- `nfx::graphics::gl` shared library: custom OpenGL function loader covering 1.0-4.6

- Thread-local `Context` class with GL function table initialization in `Context::initialize()`
- Platform support: Linux (GLX) and Windows (WGL)
- Khronos extension headers (downloaded at build-time on Windows)

- `Buffer`: RAII wrapper for OpenGL buffer objects (bind/upload/subrange/indexed binding)
- `VertexArray`: RAII wrapper for OpenGL vertex array objects
- `VertexLayout`: descriptor for vertex attribute formats and stride/offset metadata
- `Framebuffer`: RAII wrapper for OpenGL framebuffer objects and texture/renderbuffer attachments
- `Renderbuffer`: RAII wrapper for framebuffer renderbuffer storage
- `ShaderProgram`: RAII wrapper for shader compile/link/bind and uniform updates
- `Uniforms`: typed helper aliases for scalar/vector/matrix uniform values
- `Texture2D`: RAII wrapper for 2D texture allocation/upload and sampling parameters

#### High-level graphics wrappers (renderer/pipeline/materials on top of the low-level GL library)

- `nfx::graphics` shared library: high-level rendering wrappers built on top of `nfx::graphics::gl`

##### Pipeline

- `RenderTarget`: high-level framebuffer wrapper with single output texture and depth/depth-stencil support

#### Math library

- `nfx::graphics::math` interface target: lightweight Vec3 and Mat4 helpers

- `Mat4`: helpers for 4x4 matrix transforms, projection, view, and multiplication
- `Vec3`: helpers for length, dot/cross products, normalization, and subtraction

#### Embedded resources & build tooling

- `nfx-graphics-resourcegen`: CLI tool that converts binary files into C++ `uint8_t[]` arrays with name and size metadata
- `nfx::graphics::EmbeddedResource`: lightweight runtime view (`name`, `data`, `size`) with `str()`, `bytes()`, `empty()`, and templated `find()`
- `nfx_graphics_embed_resources()`: CMake helper that embeds resource directories and auto-generates typed `.h`/`.cpp` registries

#### Tests

- `gl/core/tests_Functions`: verifies GL binding mappings and wrapper-to-pointer consistency
- `gl/core/tests_Renderbuffer`: validates renderbuffer allocation and format rejection guards
- `gl/core/tests_ShaderProgram`: validates pipeline validation rules and file-loading error paths
- `gl/core/tests_Texture2D`: validates format rejection and allocate guard conditions
- `gl/core/tests_VertexLayout`: validates attribute layout stride/offset computation and type helper mapping

- `math/tests_Mat4`: validates matrix identity/transform/projection/view helpers and matrix multiplication behavior
- `math/tests_Vec3`: validates length, dot/cross, normalization, and vector subtraction helpers

#### Samples

- `nfx-sample-common` shared library: sample framework with X11/GLX and Win32/WGL backends

- `basic-hello-triangle`: colored triangle demo
- `basic-textured-cube`: textured rotating cube with embedded resources

### Changed

- NIL

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL
