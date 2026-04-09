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
- `MaterialBlock`: std140-compatible CPU mirror of MaterialBlock UBO (baseColor+alpha, specColor+shininess, emissive+envIntensity)
- `IblFrameBlock`: std140 frame-global IBL state block used to bind split-sum resources

- `BlinnPhong`: material descriptor with diffuse/specular/normal map support, alpha transparency and shadow permutation
- `Unlit`: material descriptor for constant-color rendering with alpha support
- `Pbr`: metallic-roughness material descriptor with base color, normal, occlusion, shadow, and environment-map support

- `BrdfLutGenerator`: GPU-side BRDF integration LUT generator for PBR split-sum IBL.
- `IrradianceMapGenerator`: GPU-side diffuse irradiance cubemap generator for IBL
- `PrefilteredEnvGenerator`: GPU-side specular prefiltered environment cubemap generator for split-sum IBL

##### Meshes

- `Mesh`: runtime wrapper for vertex/index GPU buffers, VAO setup, and optional instance attribute streams
- `MeshData`: CPU-side packed mesh container (`vertices`, `indices`, `layout`)
- `Primitive`: mesh generators (`cube`, `uvSphere`, `icosphere`, `cylinder`, `cone`, `capsule`, `disk`, `pyramid`, `tetrahedron`, `tube`, `pipe`, `plane`, `quad`, `torus`) with tangent-ready layouts for lit primitives

##### Pipeline

- `FrameData`: frame-scoped camera and light payloads uploaded once per frame by the Renderer
- `RenderResources`: non-owning bundle of cache references used by the renderer to resolve handles

- `AxesPass`: world-axes overlay pass with embedded shader, configurable axis length/fade distance, and optional target framebuffer
- `GridPass`: infinite anti-aliased ground grid overlay pass with configurable cell size, fade distance, and color

- `RenderPass`: abstract base class for render passes with begin/execute/end lifecycle, enabled state and output accessors
- `GeometryPass`: opaque geometry pass with queue submission, material/mesh/shader resolution, fallback material, render target, sort order, patch vertex count, and per-frame clear control
- `PresentPass`: final fullscreen pass for presentation (input color, optional tonemap, optional gamma)
- `TransparentPass`: transparent geometry pass with back-to-front sorting, alpha blending, and target framebuffer compositing
- `PostProcessPass`: generic fullscreen post-process pass with custom fragment source, input color handle, output texture target, and dynamic uniforms
- `SkyboxPass`: cubemap skybox pass rendered behind opaque scene geometry
- `WboitPass`: weighted blended OIT pass with accumulation/reveal targets and fullscreen composite
- `EnvironmentPass`: environment cubemap composition pass with configurable intensity and explicit target color/depth wiring
- `OutlinePass`: selection outline compositing pass rendering selected geometry into a mask, extracting edges via Sobel filter, and compositing outlines with configurable color/thickness and viewport support

- `DirectionalShadowPass`: depth-only directional shadow-map pass producing a `ShadowMap` payload (depth texture + light-space matrix)
- `SpotShadowPass`: depth-only spot shadow-map pass producing one 2D depth map per spot light
- `PointShadowPass`: depth-only point-light shadow pass producing layered cube-map depth shadows

- `RenderCommand`: draw command: mesh + material handles, transform, primitive topology, instance count and sort key
- `RenderQueue`: per-frame draw command queue with sortKey assignment, stable sort by key, submission order preservation and clear

- `ShadowMap`: directional/spot shadow map payload combining depth texture handle and light-space matrix
- `PointShadowMap`: point-light shadow payload combining depth cube map, light position, and far plane
- `ShadowMatricesBlock`: std140 block for shadow matrices

- `Bindings.h`: shared UBO/SSBO/texture binding-point conventions for pipeline and materials
- `Renderer`: frame renderer orchestrating an ordered sequence of render passes with frame-scoped UBO/SSBO binding
- `RenderMode`: primitive topology enum mapped to OpenGL draw modes
- `RenderState`: pipeline state descriptor with `apply()` helper and `opaque()` / `transparent()` / `shadowCaster()` presets
- `RenderTarget`: high-level framebuffer wrapper with single output texture and depth/depth-stencil support
- `ViewportRect`: pixel-space rectangle (x, y, width, height) for multi-viewport rendering contracts

- `ForwardRenderPath`: forward rendering pipeline assembler - fluent pass configuration (`addShadowPass<T>`, `setSkybox`, `enableTransparency<T>`, `addOverlay<T>`), automatic color/depth target wiring, viewport resize handling, and typed pass access via `get<T>(name)`

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

- `nfx::graphics::math` static library: Vec3, Mat4, and geometry helpers

- `Mat3`: helpers for 3x3 identity/scale/rotation and inverse-transpose normal matrix computation
- `Mat4`: helpers for 4x4 matrix transforms, projection, view, and multiplication
- `Quat`: quaternion type with angle-axis construction, multiplication, normalization, and vector rotation
- `Vec3`: helpers for length, dot/cross products, normalization, and subtraction

- `Bounds`: AABB and Sphere bounding volume types
- `Ray`: ray type with AABB/sphere/triangle intersection helpers and screen-to-world unprojection
- `Frustum`: view frustum extracted from a view-projection matrix with point/sphere/AABB intersection tests

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

- `gl/pipeline/tests_Bindings`: validates UBO and texture binding slot uniqueness, alias mapping, and range separation
- `gl/pipeline/tests_CullingUtils`: validates frustum culling decisions and world-space bound transforms (`AABB` first, `Sphere` fallback)
- `gl/pipeline/tests_ForwardRenderPathWiring`: validates automatic target texture wiring between passes (geometry output routed to overlays/transparent/outline)
- `gl/pipeline/tests_Renderer`: validates renderer pass registration/removal, null-pass handling, and one-time pass initialization behavior
- `gl/pipeline/tests_RenderQueue`: validates submission contract, default sort-key assignment, order preservation, and clear behavior
- `gl/pipeline/tests_RenderState`: validates RenderState defaults and enum-to-OpenGL constant mapping
- `gl/pipeline/tests_ViewportRect`: validates ViewportRect invariants, coordinate system, and multi-viewport composition contracts
- `gl/pipeline/tests_ViewportValidation`: validates viewport-inside-surface bounds check including invalid dimensions and out-of-bounds rectangles

- `gl/resources/tests_ResourceCache`: validates typed handle/cache behavior and failure-path cache invariants

- `gl/scene/tests_lights`: ambient/directional defaults, raw/typed packing parity, and std140 GPU payload layout checks
- `gl/scene/tests_OrbitCamera`: validates std140 GpuData layout and size, viewProj correctness, and orbit state geometry

- `gl/material/tests_ShaderFeatures`: shader feature bitmask operations, define generation, and debug string formatting

- `math/geometry/tests_Frustum`: plane normalization, point/sphere/AABB containment and intersection checks against a perspective frustum
- `math/geometry/tests_Intersections`: ray/AABB, ray/sphere and ray/triangle intersection checks
- `math/geometry/tests_ScreenToWorldRay`: semantic and picking coverage for `screenToWorldRay` (center/corner direction, normalized direction, camera origin, viewport-local invariant, hit/miss, closest-object selection)
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
- `basic-punctual-shadow`: point + spot shadow mapping with a geometry-shader layered cube-map depth pass
- `basic-model-import`: embedded OBJ mesh import with `ObjLoader` and textured model rendering using orbit camera
- `basic-model-import-material-maps`: embedded OBJ model import with diffuse, normal, and specular texture maps
- `basic-tessellation`: dynamic triangle patch tessellation sample using vertex + tessellation + fragment shaders

- `direct-rendering-geometry-pass`: GeometryPass pipeline sample with 3 submitted commands, per-frame FrameData upload, and orbit camera controls
- `direct-rendering-viewport-overlays`: three-pass pipeline sample (GeometryPass + GridPass + AxesPass) with infinite grid and world-axes overlay
- `direct-rendering-transparent-pass`: two-pass pipeline sample (GeometryPass + TransparentPass) with back-to-front sorted alpha-blended spheres
- `direct-rendering-postprocess-pass`: post-process sample with left-click effect cycling (neutral, mono scanlines, chromatic grain)
- `direct-rendering-wboit-pass`: weighted blended OIT sample (GeometryPass + WboitPass)

- `forward-rendering-forward-path-showcase`: ForwardRenderPath showcase combining directional + point shadows, skybox background, WBOIT transparency, and grid/axes overlays
- `forward-rendering-directional-shadow-pass`: directional-light shadow mapping with orbiting rocks and textured terrain floor
- `forward-rendering-spot-shadow-pass`: spot-light shadow mapping with one levitating rock and three orbiting light markers
- `forward-rendering-point-shadow-pass`: point-light cube-shadow mapping with one levitating rock and one moving light marker
- `forward-rendering-material-permutations`: BlinnPhong/Unlit material permutations with directional and point shadows
- `forward-rendering-skybox-pass`: SkyboxPass pipeline sample with cubemap background and orbit camera
- `forward-rendering-environment-pass`: reflective sphere sample using `BlinnPhongMaterial` (`hasEnvMap=true`) with `EnvironmentPass`
- `forward-rendering-pbr-minimal`: minimal ForwardRenderPath sample with two PBR materials using packed ARM maps (`R=ao`, `G=roughness`, `B=metallic`)
- `forward-rendering-multi-view`: two-viewport split-screen sample with a shared geometry queue, distinct cameras per view, and grid/axes overlays
- `forward-rendering-primitives-showcase`: forward sample showcasing 3D primitives in a circular layout with orbit camera

- `forward-rendering-pbr-ibl-showcase`: visual comparison sample of fallback env reflection vs split-sum IBL across four PBR materials

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
