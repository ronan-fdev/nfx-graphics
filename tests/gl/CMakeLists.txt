#==============================================================================
# nfx::graphics::gl - Tests
#==============================================================================

add_executable(nfx-graphics-gl-tests
    core/tests_Functions.cpp
    core/tests_Renderbuffer.cpp
    core/tests_ShaderProgram.cpp
    core/tests_Texture2D.cpp
    core/tests_VertexLayout.cpp
)

set_target_properties(nfx-graphics-gl-tests PROPERTIES DEBUG_POSTFIX "-d")

target_compile_definitions(nfx-graphics-gl-tests
    PRIVATE
        DOCTEST_CONFIG_USE_STD_HEADERS
)

target_link_libraries(nfx-graphics-gl-tests
    PRIVATE
        doctest::doctest_with_main
        nfx::graphics::gl
        nfx-graphics-warnings
)

doctest_discover_tests(nfx-graphics-gl-tests)
