#pragma once

/**
 * \file FrameData.h
 * \brief Declares the frame-scoped struct uploaded once per frame by the Renderer.
 */

#include "nfx/graphics/gl/pipeline/shadows/PointShadowMap.h"
#include "nfx/graphics/gl/pipeline/shadows/ShadowMap.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/scene/cameras/Camera.h"
#include "nfx/graphics/gl/scene/lights/AmbientLight.h"
#include "nfx/graphics/gl/scene/lights/DirectionalLight.h"
#include "nfx/graphics/gl/scene/lights/PunctualLight.h"

#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \brief Frame-scoped lighting and camera payloads consumed by forward passes.
     *
     * This struct groups data that is constant for all draws within one rendered frame.
     * Typical usage is:
     * - fill once on CPU for the current frame,
     * - upload/bind camera and light blocks,
     * - execute one or more render passes using the same frame payload.
     */
    struct FrameData
    {
        Camera::GpuData camera = {};             ///< Camera block payload (view/proj/viewProj/position/direction)
        AmbientLight::GpuData ambientLight = {}; ///< Ambient light block payload
        DirectionalLight::GpuData directionalLight = {}; ///< Directional light block payload
        std::vector<PunctualLight::GpuData> lights;      ///< Punctual lights payload array (point + spot)

        ShadowMapData dirShadowMap = {};
        bool hasDirShadow = false;

        std::array<ShadowMapData, PipelineLimits::MaxSpotShadows> spotShadowMaps = {};
        int spotShadowCount = 0;

        std::array<PointShadowMap, PipelineLimits::MaxPointShadows> pointShadowMaps = {};
        int pointShadowCount = 0;

        TextureCubeHandle envMap = {};
        bool hasEnvMap = false;
        SamplerHandle envSampler = {};
        bool hasEnvSampler = false;
    };
} // namespace nfx::graphics::gl
