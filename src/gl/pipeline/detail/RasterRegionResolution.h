#pragma once

#include "nfx/graphics/gl/pipeline/raster/RasterRegion.h"

namespace nfx::graphics::gl::detail
{
    [[nodiscard]] inline bool isRectInsideTarget(
        int x, int y, int width, int height, const SurfaceExtent& target) noexcept
    {
        return width >= 1 && height >= 1 && x >= 0 && y >= 0 && x + width <= target.width &&
               y + height <= target.height;
    }

    [[nodiscard]] inline RasterResolutionDisposition dispositionForMode(RasterValidationMode mode) noexcept
    {
        if (mode == RasterValidationMode::Strict)
        {
            return RasterResolutionDisposition::AbortFrame;
        }
        return RasterResolutionDisposition::SkipPass;
    }

    [[nodiscard]] inline RasterResolutionResult fail(RasterResolutionStatus status, RasterValidationMode mode) noexcept
    {
        RasterResolutionResult out;
        out.status = status;
        out.disposition = dispositionForMode(mode);
        return out;
    }

    [[nodiscard]] inline RasterResolutionResult resolveRasterState(
        const RasterResolutionInput& input, RasterValidationMode mode = RasterValidationMode::Warn) noexcept
    {
        if (!input.targetExtent.isValid())
        {
            return fail(RasterResolutionStatus::InvalidSurfaceExtent, mode);
        }

        if (!isRectInsideTarget(
                input.viewViewport.x,
                input.viewViewport.y,
                input.viewViewport.width,
                input.viewViewport.height,
                input.targetExtent))
        {
            return fail(RasterResolutionStatus::InvalidViewViewport, mode);
        }

        RasterResolutionResult out;

        switch (input.policy.viewportPolicy)
        {
            case ViewportPolicy::InheritView:
                out.state.viewport = input.viewViewport;
                break;
            case ViewportPolicy::FullTarget:
                out.state.viewport = { 0, 0, input.targetExtent.width, input.targetExtent.height };
                break;
            case ViewportPolicy::Explicit:
                if (!input.policy.explicitViewport.has_value())
                {
                    return fail(RasterResolutionStatus::MissingExplicitViewport, mode);
                }
                out.state.viewport = *input.policy.explicitViewport;
                if (!isRectInsideTarget(
                        out.state.viewport.x,
                        out.state.viewport.y,
                        out.state.viewport.width,
                        out.state.viewport.height,
                        input.targetExtent))
                {
                    return fail(RasterResolutionStatus::InvalidExplicitViewport, mode);
                }
                break;
        }

        switch (input.policy.scissorPolicy)
        {
            case ScissorPolicy::Disabled:
                out.state.scissorEnabled = false;
                out.state.scissor = {};
                break;
            case ScissorPolicy::MatchViewport:
                out.state.scissorEnabled = true;
                out.state.scissor = {
                    out.state.viewport.x, out.state.viewport.y, out.state.viewport.width, out.state.viewport.height
                };
                break;
            case ScissorPolicy::InheritView:
                out.state.scissorEnabled = true;
                out.state.scissor = {
                    input.viewViewport.x, input.viewViewport.y, input.viewViewport.width, input.viewViewport.height
                };
                break;
            case ScissorPolicy::Explicit:
                if (!input.policy.explicitScissor.has_value())
                {
                    return fail(RasterResolutionStatus::MissingExplicitScissor, mode);
                }
                out.state.scissorEnabled = true;
                out.state.scissor = *input.policy.explicitScissor;
                if (!isRectInsideTarget(
                        out.state.scissor.x,
                        out.state.scissor.y,
                        out.state.scissor.width,
                        out.state.scissor.height,
                        input.targetExtent))
                {
                    return fail(RasterResolutionStatus::InvalidExplicitScissor, mode);
                }
                break;
        }

        out.status = RasterResolutionStatus::Ok;
        out.disposition = RasterResolutionDisposition::Continue;
        return out;
    }
} // namespace nfx::graphics::gl::detail
