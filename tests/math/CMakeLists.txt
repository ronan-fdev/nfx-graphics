#==============================================================================
# nfx::graphics::math - Tests
#==============================================================================

add_executable(nfx-math-tests
    geometry/tests_Intersections.cpp
    geometry/tests_ScreenToWorldRay.cpp
    tests_Mat3.cpp
    tests_Mat4.cpp
    tests_Quat.cpp
    tests_Vec3.cpp
)

set_target_properties(nfx-math-tests PROPERTIES DEBUG_POSTFIX "-d")

target_compile_definitions(nfx-math-tests
    PRIVATE
        DOCTEST_CONFIG_USE_STD_HEADERS
)

target_link_libraries(nfx-math-tests
    PRIVATE
        doctest::doctest_with_main
        nfx::graphics::math
        nfx-graphics-warnings
)

doctest_discover_tests(nfx-math-tests)
