#pragma once

/**
 * \file Graphics.h
 * \brief Umbrella header for nfx::graphics.
 *
 * Include this single header to access the full nfx::graphics public API.
 */

// Core
#include "Gl.h"

// Material
#include "nfx/graphics/gl/material/ibl/BrdfLutGenerator.h"
#include "nfx/graphics/gl/material/ibl/IrradianceMapGenerator.h"
#include "nfx/graphics/gl/material/ibl/PrefilteredEnvGenerator.h"
#include "nfx/graphics/gl/material/BlinnPhong.h"
#include "nfx/graphics/gl/material/Material.h"
#include "nfx/graphics/gl/material/MaterialBlock.h"
#include "nfx/graphics/gl/material/Pbr.h"
#include "nfx/graphics/gl/material/Unlit.h"

// Mesh
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/mesh/MeshData.h"
#include "nfx/graphics/gl/mesh/Primitive.h"

// Pipeline
#include "nfx/graphics/gl/pipeline/frame/FrameData.h"
#include "nfx/graphics/gl/pipeline/frame/RenderResources.h"
#include "nfx/graphics/gl/pipeline/passes/AxesPass.h"
#include "nfx/graphics/gl/pipeline/passes/DirectionalShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/EnvironmentPass.h"
#include "nfx/graphics/gl/pipeline/passes/GeometryPass.h"
#include "nfx/graphics/gl/pipeline/passes/GridPass.h"
#include "nfx/graphics/gl/pipeline/passes/ImagePlanePass.h"
#include "nfx/graphics/gl/pipeline/passes/OutlinePass.h"
#include "nfx/graphics/gl/pipeline/passes/PointShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/Polygon2DPass.h"
#include "nfx/graphics/gl/pipeline/passes/PostProcessPass.h"
#include "nfx/graphics/gl/pipeline/passes/PresentPass.h"
#include "nfx/graphics/gl/pipeline/passes/RenderPass.h"
#include "nfx/graphics/gl/pipeline/passes/SkyboxPass.h"
#include "nfx/graphics/gl/pipeline/passes/TextPass.h"
#include "nfx/graphics/gl/pipeline/passes/SpotShadowPass.h"
#include "nfx/graphics/gl/pipeline/passes/TransparentPass.h"
#include "nfx/graphics/gl/pipeline/passes/WboitPass.h"
#include "nfx/graphics/gl/pipeline/queue/RenderCommand.h"
#include "nfx/graphics/gl/pipeline/queue/RenderQueue.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/pipeline/ForwardRenderPath.h"
#include "nfx/graphics/gl/pipeline/Renderer.h"
#include "nfx/graphics/gl/pipeline/RenderMode.h"
#include "nfx/graphics/gl/pipeline/RenderTarget.h"
#include "nfx/graphics/gl/pipeline/ViewportRect.h"

// Resources
#include "nfx/graphics/gl/resources/Handle.h"
#include "nfx/graphics/gl/resources/MaterialCache.h"
#include "nfx/graphics/gl/resources/MeshCache.h"
#include "nfx/graphics/gl/resources/ResourceCache.h"
#include "nfx/graphics/gl/resources/SamplerCache.h"
#include "nfx/graphics/gl/resources/ShaderCache.h"
#include "nfx/graphics/gl/resources/Texture2DCache.h"
#include "nfx/graphics/gl/resources/TextureCubeCache.h"

// Scene
#include "nfx/graphics/gl/scene/cameras/Camera.h"
#include "nfx/graphics/gl/scene/cameras/OrbitCamera.h"
#include "nfx/graphics/gl/scene/lights/AmbientLight.h"
#include "nfx/graphics/gl/scene/lights/DirectionalLight.h"
#include "nfx/graphics/gl/scene/lights/PointLight.h"
#include "nfx/graphics/gl/scene/lights/PunctualLight.h"
#include "nfx/graphics/gl/scene/lights/SpotLight.h"

// Math
#include "nfx/graphics/math/geometry/Bounds.h"
#include "nfx/graphics/math/geometry/Frustum.h"
#include "nfx/graphics/math/geometry/Ray.h"
#include "nfx/graphics/math/Mat3.h"
#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Quat.h"
#include "nfx/graphics/math/Vec3.h"

// Tools
#include "nfx/graphics/EmbeddedResource.h"
