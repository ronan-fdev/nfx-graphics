#==============================================================================
# nfx::graphics::math - Target definition
#==============================================================================

add_library(nfx-graphics-math STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/geometry/Frustum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/geometry/Ray.cpp
)

set_target_properties(nfx-graphics-math PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(nfx-graphics-math
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(nfx::graphics::math ALIAS nfx-graphics-math)
