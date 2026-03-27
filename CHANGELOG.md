# Changelog

## [Unreleased]

### Added

#### Low-level OpenGL library (function loader + typed GL wrappers)

- `nfx::graphics::gl` shared library: custom OpenGL function loader covering 1.0-4.6

- Thread-local `Context` class with GL function table initialization in `Context::initialize()`
- Platform support: Linux (GLX) and Windows (WGL)
- Khronos extension headers (downloaded at build-time on Windows)

- `Buffer`: RAII wrapper for OpenGL buffer objects (bind/upload/subrange/indexed binding)
- `ShaderStorageBuffer<T>`: typed SSBO wrapper for single/array uploads, subrange updates, and indexed binding (std430)
- `UniformBuffer<T>`: typed UBO wrapper for single value upload and indexed binding (std140)
- `VertexArray`: RAII wrapper for OpenGL vertex array objects
- `VertexLayout`: descriptor for vertex attribute formats and stride/offset metadata
- `Framebuffer`: RAII wrapper for OpenGL framebuffer objects and texture/renderbuffer attachments
- `Renderbuffer`: RAII wrapper for framebuffer renderbuffer storage
- `ShaderProgram`: RAII wrapper for shader compile/link/bind and uniform updates
- `Uniforms`: typed helper aliases for scalar/vector/matrix uniform values
- `Sampler`: RAII wrapper for OpenGL sampler objects (filter, wrap, and compare state independent from textures)
- `Texture2D`: RAII wrapper for 2D texture allocation/upload and sampling parameters
- `TextureCube`: RAII cube map wrapper - allocate or upload 6 faces, configurable filter/wrap/mipmap, depth format support

#### High-level graphics wrappers (renderer/pipeline/materials on top of the low-level GL library)

- `nfx::graphics` shared library: high-level rendering wrappers built on top of `nfx::graphics::gl`

##### Materials

- `Material`: high-level material combining shader, render state and named uniform/texture bindings
- `MaterialBlock`: std140-compatible CPU mirror of MaterialBlock UBO (baseColor+alpha, specColor+shininess)

##### Meshes

- `Mesh`: runtime wrapper for vertex/index GPU buffers, VAO setup, and optional instance attribute streams
- `MeshData`: CPU-side packed mesh container (`vertices`, `indices`, `layout`)
- `Primitive`: mesh generators (`cube`, `uvSphere`, `plane`, `quad`) with tangent-ready layouts for lit primitives

##### Pipeline

- `Bindings.h`: shared UBO/SSBO/texture binding-point conventions for pipeline and materials
- `RenderState`: pipeline state descriptor with `apply()` helper (depth, blend, cull, raster state)
- `RenderTarget`: high-level framebuffer wrapper with single output texture and depth/depth-stencil support

##### Resources

- `Handle<Tag>`: strongly typed opaque resource handle (64-bit id, `std::hash` support)
- `ResourceCache<Tag, T>`: generic cache - add/get/remove/contains/clear/forEach by typed handle
- `MaterialCache`: create material from `ShaderHandle` + `RenderState`, stored by `MaterialHandle`
- `MeshCache`: create mesh from `MeshData` or `Mesh::Desc`
- `SamplerCache`: create sampler with default or explicit `Sampler::Params`
- `ShaderCache`: compile shader program from in-memory sources
- `Texture2DCache`: upload 2D texture from pixel data
- `TextureCubeCache`: upload cube map from 6 face descriptors

##### Scene

- `Camera`: descriptor with CPU-side state (`view`, `proj`, `viewProj`, `position`, `direction`) and std140-compatible `GpuData` packing helpers
- `OrbitCamera`: quaternion-based Y-up orbit camera with orbit, proportional zoom, view-plane pan, and `Camera::GpuData` export
- `AmbientLight`: descriptor with std140 `GpuData` packing and raw/typed `toGpuData` overloads
- `DirectionalLight`: descriptor with std140 `GpuData` packing and raw/typed `toGpuData` overloads
- `PunctualLight`: punctual-light SSBO payload (`std430`) with shared `GpuData`/`GpuBlock` contracts
- `PointLight`: descriptor with raw/typed `create()` and raw/typed `toGpuData()` overloads for SSBO packing
- `SpotLight`: descriptor with raw/typed `create()` and raw/typed `toGpuData()` overloads for SSBO packing

#### Math library

- `nfx::graphics::math` interface target: lightweight Vec3 and Mat4 helpers

- `Mat3`: helpers for 3x3 identity/scale/rotation and inverse-transpose normal matrix computation
- `Mat4`: helpers for 4x4 matrix transforms, projection, view, and multiplication
- `Quat`: quaternion type with angle-axis construction, multiplication, normalization, and vector rotation
- `Vec3`: helpers for length, dot/cross products, normalization, and subtraction

#### Embedded resources & build tooling

- `nfx-graphics-resourcegen`: CLI tool that converts binary files into C++ `uint8_t[]` arrays with name and size metadata
- `nfx::graphics::EmbeddedResource`: lightweight runtime view (`name`, `data`, `size`) with `str()`, `bytes()`, `empty()`, and templated `find()`
- `nfx_graphics_embed_resources()`: CMake helper that embeds resource directories and auto-generates typed `.h`/`.cpp` registries

#### Tests

- `gl/core/tests_Functions`: verifies GL binding mappings and wrapper-to-pointer consistency
- `gl/core/tests_Renderbuffer`: validates renderbuffer allocation and format rejection guards
- `gl/core/tests_Sampler`: validates mipmap magnification filter rejection
- `gl/core/tests_ShaderProgram`: validates pipeline validation rules and file-loading error paths
- `gl/core/tests_Texture2D`: validates format rejection and allocate guard conditions
- `gl/core/tests_TextureCube`: validates non-square face rejection and unsupported upload format guards
- `gl/core/tests_VertexLayout`: validates attribute layout stride/offset computation and type helper mapping

- `gl/material/tests_Material`: material state, texture bindings, move semantics, and MaterialBlockData defaults

- `gl/mesh/tests_Mesh`: validates invalid-instance-data no-op behavior on default meshes
- `gl/mesh/tests_MeshData`: index data size calculation, vertex count derivation, and type alignment checks
- `gl/mesh/tests_Primitive`: primitive mesh layout/count/index-range checks

- `gl/pipeline/tests_RenderState`: validates RenderState defaults and enum-to-OpenGL constant mapping

- `gl/resources/tests_ResourceCache`: validates typed handle/cache behavior and failure-path cache invariants

- `gl/scene/tests_lights`: ambient/directional defaults, raw/typed packing parity, and std140 GPU payload layout checks
- `gl/scene/tests_OrbitCamera`: validates std140 GpuData layout and size, viewProj correctness, and orbit state geometry

- `math/tests_Mat3`: validates mat3 identity/scale/rotation helpers and inverse-transpose normal-matrix behavior
- `math/tests_Mat4`: validates matrix identity/transform/projection/view helpers and matrix multiplication behavior
- `math/tests_Quat`: quaternion construction/normalization/composition/vector-rotation checks
- `math/tests_Vec3`: validates length, dot/cross, normalization, and vector subtraction helpers

#### Samples

- `nfx-sample-common` shared library: sample framework with X11/GLX and Win32/WGL backends

- `basic-hello-triangle`: colored triangle demo
- `basic-textured-cube`: textured rotating cube with embedded resources
- `basic-offscreen-cube`: renders a textured cube to an offscreen target and presents it with a grayscale post-process pass
- `basic-skybox`: skybox scene with a textured spinning box and mouse-driven orbit camera controls
- `basic-sampler-showcase`: compares sampler state behavior side-by-side (`ClampToEdge + Nearest` vs `Repeat + LinearMipmapLinear`)
- `basic-blinn-phong-directional-shadow`: directional-light shadow mapping sample with depth shadow map generation and PCF-filtered lookups
- `basic-spot-shadow`: 3 orbiting RGB spot lights with per-light 1024×1024 depth shadow maps and PCF filtering
- `basic-point-shadow`: omnidirectional point light shadow with depth cube map (512×512 per face) and PCF filtering
- `basic-instanced`: draws many spheres in one call using per-instance model matrix and color attributes
- `basic-primitive-showcase`: brickwall normal-mapped cube with flat Blinn-Phong sphere, plane, and quad
- `basic-normal-map`: cube with toybox diffuse and normal map, orbit camera, Blinn-Phong with TBN normal mapping
- `basic-material-pipeline`: 3 objects sharing one shader with per-object material state and textures

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
