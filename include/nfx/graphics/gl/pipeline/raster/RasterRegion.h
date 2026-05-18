#pragma once

/**
 * \file RasterRegion.h
 * \brief Declares viewport/scissor policy and resolved raster-region contracts.
 */

#include "ScissorRect.h"
#include "SurfaceExtent.h"
#include "ViewportRect.h"

#include <optional>

namespace nfx::graphics::gl
{
    /**
     * \brief Validation mode used by raster-region resolution.
     */
    enum class RasterValidationMode
    {
        Strict,
        Warn,
        Off
    };

    /**
     * \brief Resolution status for one raster-region request.
     */
    enum class RasterResolutionStatus
    {
        Ok,
        InvalidSurfaceExtent,
        InvalidViewViewport,
        MissingExplicitViewport,
        InvalidExplicitViewport,
        MissingExplicitScissor,
        InvalidExplicitScissor
    };

    /**
     * \brief Action selected by validation policy when resolution fails.
     */
    enum class RasterResolutionDisposition
    {
        Continue,
        SkipPass,
        AbortFrame
    };

    /**
     * \brief Selects how the effective viewport is resolved.
     */
    enum class ViewportPolicy
    {
        InheritView, ///< Use renderer-provided view viewport
        FullTarget,  ///< Use full target extent
        Explicit     ///< Use pass-provided explicit viewport
    };

    /**
     * \brief Selects how the effective scissor is resolved.
     */
    enum class ScissorPolicy
    {
        Disabled,      ///< Disable GL scissor test
        MatchViewport, ///< Enable scissor and match resolved viewport
        InheritView,   ///< Enable scissor and use view viewport
        Explicit       ///< Enable scissor and use explicit rectangle
    };

    /**
     * \brief Logical raster-region policy expressed by a pass.
     */
    struct RasterRegionState
    {
        ViewportPolicy viewportPolicy = ViewportPolicy::InheritView;
        std::optional<ViewportRect> explicitViewport;

        ScissorPolicy scissorPolicy = ScissorPolicy::Disabled;
        std::optional<ScissorRect> explicitScissor;
    };

    /**
     * \brief GL-ready raster state after policy resolution.
     */
    struct ResolvedRasterState
    {
        ViewportRect viewport{};
        bool scissorEnabled = false;
        ScissorRect scissor{};
    };

    /**
     * \brief Input payload used to resolve one pass raster region.
     */
    struct RasterResolutionInput
    {
        SurfaceExtent targetExtent{};
        ViewportRect viewViewport{};
        RasterRegionState policy{};
    };

    /**
     * \brief Resolver output combining state and validation outcome.
     */
    struct RasterResolutionResult
    {
        ResolvedRasterState state{};
        RasterResolutionStatus status = RasterResolutionStatus::Ok;
        RasterResolutionDisposition disposition = RasterResolutionDisposition::Continue;

        /**
         * \brief Returns true when resolution succeeded.
         */
        [[nodiscard]] bool ok() const noexcept { return status == RasterResolutionStatus::Ok; }
    };
} // namespace nfx::graphics::gl
