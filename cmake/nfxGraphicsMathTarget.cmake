#==============================================================================
# nfx::graphics::math - Target definition
#==============================================================================

add_library(nfx-graphics-math INTERFACE)

target_include_directories(nfx-graphics-math
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(nfx::graphics::math ALIAS nfx-graphics-math)
