#==============================================================================
# nfx::graphics::internal - Target definition
#==============================================================================

add_library(nfx-graphics-internal STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/runtime/Error.cpp
)

set_target_properties(nfx-graphics-internal PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(nfx-graphics-internal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(nfx::graphics::internal ALIAS nfx-graphics-internal)
