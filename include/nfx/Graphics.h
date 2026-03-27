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
#include "nfx/graphics/gl/material/Material.h"
#include "nfx/graphics/gl/material/MaterialBlock.h"

// Mesh
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/mesh/MeshData.h"
#include "nfx/graphics/gl/mesh/Primitive.h"

// Pipeline
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/pipeline/RenderTarget.h"

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
#include "nfx/graphics/math/Mat3.h"
#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Quat.h"
#include "nfx/graphics/math/Vec3.h"

// Tools
#include "nfx/graphics/EmbeddedResource.h"
