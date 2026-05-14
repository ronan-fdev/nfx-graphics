#==============================================================================
# nfx::graphics::gl - Tests
#==============================================================================

add_executable(nfx-graphics-gl-tests
    core/tests_Functions.cpp
    core/tests_Renderbuffer.cpp
    core/tests_Sampler.cpp
    core/tests_ShaderProgram.cpp
    core/tests_Texture2D.cpp
    core/tests_TextureCube.cpp
    core/tests_VertexLayout.cpp

    material/tests_Material.cpp

    pipeline/tests_Bindings.cpp
    pipeline/tests_CullingUtils.cpp
    pipeline/tests_ForwardRenderPathWiring.cpp
    pipeline/tests_GeometryPassStats.cpp
    pipeline/tests_PassStatsSemantics.cpp
    pipeline/tests_Renderer.cpp
    pipeline/tests_RenderQueue.cpp
    pipeline/tests_RenderState.cpp
    pipeline/tests_ViewportRect.cpp
    pipeline/tests_ViewportValidation.cpp

    mesh/tests_Mesh.cpp
    mesh/tests_MeshData.cpp
    mesh/tests_Primitive.cpp

    resources/tests_ResourceCache.cpp

    scene/tests_lights.cpp
    scene/tests_OrbitCamera.cpp

    shaders/tests_ShaderFeatures.cpp

    text/tests_TextTypes.cpp
)

set_target_properties(nfx-graphics-gl-tests PROPERTIES DEBUG_POSTFIX "-d")

target_compile_definitions(nfx-graphics-gl-tests
    PRIVATE
        DOCTEST_CONFIG_USE_STD_HEADERS
)

target_link_libraries(nfx-graphics-gl-tests
    PRIVATE
        doctest::doctest_with_main
        nfx::graphics
        nfx-graphics-warnings
)

target_include_directories(nfx-graphics-gl-tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

doctest_discover_tests(nfx-graphics-gl-tests)
