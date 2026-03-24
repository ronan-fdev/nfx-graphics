#pragma once

/**
 * \file Graphics.h
 * \brief Umbrella header for nfx::graphics.
 *
 * Include this single header to access the full nfx::graphics public API.
 */

// Core
#include "Gl.h"

// Pipeline
#include "nfx/graphics/gl/pipeline/RenderTarget.h"

// Scene
#include "nfx/graphics/gl/scene/cameras/Camera.h"
#include "nfx/graphics/gl/scene/cameras/OrbitCamera.h"

// Math
#include "nfx/graphics/math/Mat4.h"
#include "nfx/graphics/math/Quat.h"
#include "nfx/graphics/math/Vec3.h"

// Tools
#include "nfx/graphics/EmbeddedResource.h"
