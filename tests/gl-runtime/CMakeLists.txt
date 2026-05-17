#==============================================================================
# nfx::graphics::gl-runtime - Tests
#==============================================================================

add_executable(nfx-graphics-gl-runtime-tests
    core/tests_CoreRuntimeSmoke.cpp
    core/tests_GLContextFixture.cpp
    pipeline/tests_PipelineRuntimeSmoke.cpp
)

set_target_properties(nfx-graphics-gl-runtime-tests PROPERTIES DEBUG_POSTFIX "-d")

target_compile_definitions(nfx-graphics-gl-runtime-tests
    PRIVATE
        DOCTEST_CONFIG_USE_STD_HEADERS
        NFX_GRAPHICS_ENABLE_GL_CONTEXT_TESTS=1
)

target_link_libraries(nfx-graphics-gl-runtime-tests
    PRIVATE
        doctest::doctest_with_main
        nfx::graphics
        nfx::graphics::internal
        nfx::graphics::warnings
        $<$<PLATFORM_ID:Linux>:X11>
)

doctest_discover_tests(nfx-graphics-gl-runtime-tests
    TEST_PREFIX "gl-runtime::"
)
