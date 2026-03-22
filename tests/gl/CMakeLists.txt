#==============================================================================
# nfx::graphics::gl - Tests
#==============================================================================

add_executable(nfx-graphics-gl-tests
    core/tests_Functions.cpp
)

set_target_properties(nfx-graphics-ggl-tests PROPERTIES DEBUG_POSTFIX "-d")

target_compile_definitions(nfx-graphics-ggl-tests
    PRIVATE
        DOCTEST_CONFIG_USE_STD_HEADERS
)

target_link_libraries(nfx-graphics-ggl-tests
    PRIVATE
        doctest::doctest_with_main
        nfx-graphics-warnings
)

doctest_discover_tests(nfx-graphics-ggl-tests)
