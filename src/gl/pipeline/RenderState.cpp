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

    RenderState RenderState::opaque()
    {
        RenderState state;

        state.depthTest = true;
        state.depthWrite = true;
        state.depthFunc = DepthFunc::Less;

        state.blend = false;
        state.blendSrc = BlendFactor::SrcAlpha;
        state.blendDst = BlendFactor::OneMinusSrcAlpha;
        state.blendSrcAlpha = BlendFactor::SrcAlpha;
        state.blendDstAlpha = BlendFactor::OneMinusSrcAlpha;
        state.blendOp = BlendOp::Add;
        state.blendOpAlpha = BlendOp::Add;

        state.cullFace = true;
        state.cullMode = CullFace::Back;
        state.frontFace = FrontFace::CCW;

        state.colorWrite = true;
        state.colorWriteR = true;
        state.colorWriteG = true;
        state.colorWriteB = true;
        state.colorWriteA = true;

        state.polygonOffset = false;
        state.polygonOffsetFactor = 1.0f;
        state.polygonOffsetUnits = 1.0f;

        return state;
    }

    RenderState RenderState::transparent()
    {
        RenderState state;

        state.depthTest = true;
        state.depthWrite = false;
        state.depthFunc = DepthFunc::Less;

        state.blend = true;
        state.blendSrc = BlendFactor::SrcAlpha;
        state.blendDst = BlendFactor::OneMinusSrcAlpha;
        state.blendSrcAlpha = BlendFactor::SrcAlpha;
        state.blendDstAlpha = BlendFactor::OneMinusSrcAlpha;
        state.blendOp = BlendOp::Add;
        state.blendOpAlpha = BlendOp::Add;

        state.cullFace = false;
        state.cullMode = CullFace::Back;
        state.frontFace = FrontFace::CCW;

        state.colorWrite = true;
        state.colorWriteR = true;
        state.colorWriteG = true;
        state.colorWriteB = true;
        state.colorWriteA = true;

        state.polygonOffset = false;
        state.polygonOffsetFactor = 1.0f;
        state.polygonOffsetUnits = 1.0f;

        return state;
    }

    RenderState RenderState::shadowCaster()
    {
        RenderState state;

        state.depthTest = true;
        state.depthWrite = true;
        state.depthFunc = DepthFunc::Less;

        state.blend = false;
        state.blendSrc = BlendFactor::SrcAlpha;
        state.blendDst = BlendFactor::OneMinusSrcAlpha;
        state.blendSrcAlpha = BlendFactor::SrcAlpha;
        state.blendDstAlpha = BlendFactor::OneMinusSrcAlpha;
        state.blendOp = BlendOp::Add;
        state.blendOpAlpha = BlendOp::Add;

        state.cullFace = false;
        state.cullMode = CullFace::Back;
        state.frontFace = FrontFace::CCW;

        state.colorWrite = false;
        state.colorWriteR = true;
        state.colorWriteG = true;
        state.colorWriteB = true;
        state.colorWriteA = true;

        state.polygonOffset = true;
        state.polygonOffsetFactor = 2.0f;
        state.polygonOffsetUnits = 4.0f;

        return state;
    }

    RenderState RenderState::skybox()
    {
        RenderState state;

        state.depthTest = true;
        state.depthWrite = false;
        state.depthFunc = DepthFunc::LessOrEqual;

        state.blend = false;
        state.blendSrc = BlendFactor::SrcAlpha;
        state.blendDst = BlendFactor::OneMinusSrcAlpha;
        state.blendSrcAlpha = BlendFactor::SrcAlpha;
        state.blendDstAlpha = BlendFactor::OneMinusSrcAlpha;
        state.blendOp = BlendOp::Add;
        state.blendOpAlpha = BlendOp::Add;

        state.cullFace = false;
        state.cullMode = CullFace::Back;
        state.frontFace = FrontFace::CCW;

        state.colorWrite = true;
        state.colorWriteR = true;
        state.colorWriteG = true;
        state.colorWriteB = true;
        state.colorWriteA = true;

        state.polygonOffset = false;
        state.polygonOffsetFactor = 1.0f;
        state.polygonOffsetUnits = 1.0f;

        return state;
    }
} // namespace nfx::graphics::gl
