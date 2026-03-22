# Changelog

## [Unreleased]

### Added

#### Low-level OpenGL library (function loader + typed GL wrappers)

- `nfx::graphics::gl` shared library: custom OpenGL function loader covering 1.0-4.6

- Thread-local `Context` class with GL function table initialization in `Context::initialize()`
- Platform support: Linux (GLX) and Windows (WGL)
- Khronos extension headers (downloaded at build-time on Windows)

- `Buffer`: RAII wrapper for OpenGL buffer objects (bind/upload/subrange/indexed binding)
- `ShaderProgram`: RAII wrapper for shader compile/link/bind and uniform updates
- `Uniforms`: typed helper aliases for scalar/vector/matrix uniform values
- `Texture2D`: RAII wrapper for 2D texture allocation/upload and sampling parameters

#### Tests

- `gl/core/tests_Functions`: verifies GL binding mappings and wrapper-to-pointer consistency
- `gl/core/tests_ShaderProgram`: validates pipeline validation rules and file-loading error paths
- `gl/core/tests_Texture2D`: validates format rejection and allocate guard conditions

#### Samples

- `nfx-sample-common` shared library: sample framework with X11/GLX and Win32/WGL backends

- `basic-hello-triangle`: colored triangle demo

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
