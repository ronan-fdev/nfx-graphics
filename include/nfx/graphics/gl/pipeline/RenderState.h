#pragma once

/**
 * \file RenderState.h
 * \brief Declares the fixed-function render state description applied before draw calls.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Aggregates the fixed-function OpenGL render state used for a draw or pass.
     */
    struct RenderState
    {
        // clang-format off
        /**
         * \brief Supported depth comparison functions.
         */
        enum class DepthFunc
        {
            Never          = NEVER,
            Less           = LESS,
            Equal          = EQUAL,
            LessOrEqual    = LEQUAL,
            Greater        = GREATER,
            NotEqual       = NOTEQUAL,
            GreaterOrEqual = GEQUAL,
            Always         = ALWAYS
        };

        /**
         * \brief Supported source and destination blend factors.
         */
        enum class BlendFactor
        {
            Zero                  = ZERO,
            One                   = ONE,
            SrcColor              = SRC_COLOR,
            OneMinusSrcColor      = ONE_MINUS_SRC_COLOR,
            DstColor              = DST_COLOR,
            OneMinusDstColor      = ONE_MINUS_DST_COLOR,
            SrcAlpha              = SRC_ALPHA,
            OneMinusSrcAlpha      = ONE_MINUS_SRC_ALPHA,
            DstAlpha              = DST_ALPHA,
            OneMinusDstAlpha      = ONE_MINUS_DST_ALPHA,
            ConstantColor         = CONSTANT_COLOR,
            OneMinusConstantColor = ONE_MINUS_CONSTANT_COLOR,
            ConstantAlpha         = CONSTANT_ALPHA,
            OneMinusConstantAlpha = ONE_MINUS_CONSTANT_ALPHA
        };

        /**
         * \brief Supported blend equations.
         */
        enum class BlendOp
        {
            Add             = FUNC_ADD,
            Subtract        = FUNC_SUBTRACT,
            ReverseSubtract = FUNC_REVERSE_SUBTRACT,
            Min             = MIN,
            Max             = MAX
        };

        /**
         * \brief Supported face culling modes.
         */
        enum class CullFace
        {
            Front        = FRONT,
            Back         = BACK,
            FrontAndBack = FRONT_AND_BACK
        };

        /**
         * \brief Winding order used to determine the front face.
         */
        enum class FrontFace
        {
            CCW = gl::CCW,
            CW  = gl::CW
        };
        // clang-format on

        // Depth testing
        bool depthTest = true;
        bool depthWrite = true;
        DepthFunc depthFunc = DepthFunc::Less;

        // Blending
        bool blend = false;
        BlendFactor blendSrc = BlendFactor::SrcAlpha;
        BlendFactor blendDst = BlendFactor::OneMinusSrcAlpha;
        BlendFactor blendSrcAlpha = BlendFactor::SrcAlpha;
        BlendFactor blendDstAlpha = BlendFactor::OneMinusSrcAlpha;
        BlendOp blendOp = BlendOp::Add;
        BlendOp blendOpAlpha = BlendOp::Add;

        // Face culling
        bool cullFace = true;
        CullFace cullMode = CullFace::Back;
        FrontFace frontFace = FrontFace::CCW;

        // Color write mask
        bool colorWrite = true;
        bool colorWriteR = true;
        bool colorWriteG = true;
        bool colorWriteB = true;
        bool colorWriteA = true;

        // Polygon offset (for shadow maps)
        bool polygonOffset = false;
        float polygonOffsetFactor = 1.0f;
        float polygonOffsetUnits = 1.0f;

        /**
         * \brief Applies the render state to the current OpenGL context.
         */
        void apply() const;

        /**
         * \brief Returns the default opaque rendering preset.
         */
        static RenderState opaque();

        /**
         * \brief Returns the default alpha-blended transparent rendering preset.
         */
        static RenderState transparent();
    };
} // namespace nfx::graphics::gl
