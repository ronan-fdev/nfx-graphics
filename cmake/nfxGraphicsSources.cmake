#==============================================================================
# nfx::graphics - Sources
#==============================================================================

set(NFX_GRAPHICS_SOURCES
    src/gl/material/BlinnPhong.cpp
    src/gl/material/Unlit.cpp
    src/gl/material/Material.cpp
    src/gl/mesh/Mesh.cpp
    src/gl/mesh/Primitive.cpp
    src/gl/pipeline/passes/AxesPass.cpp
    src/gl/pipeline/passes/DirectionalShadowPass.cpp
    src/gl/pipeline/passes/GeometryPass.cpp
    src/gl/pipeline/passes/GridPass.cpp
    src/gl/pipeline/passes/PointShadowPass.cpp
    src/gl/pipeline/passes/PresentPass.cpp
    src/gl/pipeline/passes/SpotShadowPass.cpp
    src/gl/pipeline/passes/TransparentPass.cpp
    src/gl/pipeline/Renderer.cpp
    src/gl/pipeline/RenderState.cpp
    src/gl/pipeline/RenderTarget.cpp
)
