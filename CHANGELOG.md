# Changelog

## [Unreleased]

### Added

#### Low-level OpenGL library (function loader + typed GL wrappers)

- `nfx::graphics::gl` shared library: custom OpenGL function loader covering 1.0-4.6

- Thread-local `Context` class with GL function table initialization in `Context::initialize()`
- Platform support: Linux (GLX) and Windows (WGL)
- Khronos extension headers (downloaded at build-time on Windows)

#### Tests

- `gl/core/tests_Functions`: verifies GL binding mappings and wrapper-to-pointer consistency

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
