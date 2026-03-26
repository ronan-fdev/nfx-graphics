#include "nfx/graphics/gl/pipeline/RenderState.h"

#include "nfx/graphics/gl/core/Context.h"

namespace nfx::graphics::gl
{
    void RenderState::apply() const
    {
        const auto& gl = Context::current().functions();

        // Depth testing
        if (depthTest)
        {
            gl.glEnable(DEPTH_TEST);
            gl.glDepthFunc(static_cast<GLenum>(depthFunc));
        }
        else
        {
            gl.glDisable(DEPTH_TEST);
        }
        gl.glDepthMask(depthWrite);

        // Blending
        if (blend)
        {
            gl.glEnable(BLEND);
            gl.glBlendFuncSeparate(
                static_cast<GLenum>(blendSrc),
                static_cast<GLenum>(blendDst),
                static_cast<GLenum>(blendSrcAlpha),
                static_cast<GLenum>(blendDstAlpha));
            gl.glBlendEquationSeparate(static_cast<GLenum>(blendOp), static_cast<GLenum>(blendOpAlpha));
        }
        else
        {
            gl.glDisable(BLEND);
        }

        // Face culling
        if (cullFace)
        {
            gl.glEnable(CULL_FACE);
            gl.glCullFace(static_cast<GLenum>(cullMode));
        }
        else
        {
            gl.glDisable(CULL_FACE);
        }
        gl.glFrontFace(static_cast<GLenum>(frontFace));

        // Color write mask
        gl.glColorMask(
            colorWrite && colorWriteR, colorWrite && colorWriteG, colorWrite && colorWriteB, colorWrite && colorWriteA);

        // Polygon offset (for shadow maps)
        if (polygonOffset)
        {
            gl.glEnable(POLYGON_OFFSET_FILL);
            gl.glPolygonOffset(polygonOffsetFactor, polygonOffsetUnits);
        }
        else
        {
            gl.glDisable(POLYGON_OFFSET_FILL);
        }
    }
} // namespace nfx::graphics::gl
