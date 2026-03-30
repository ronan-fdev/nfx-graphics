#==============================================================================
# nfx::graphics - Target configuration
#==============================================================================

#----------------------------------------------
# Warning policy
#----------------------------------------------

add_library(nfx-graphics-warnings INTERFACE)

target_compile_options(nfx-graphics-warnings
    INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

#----------------------------------------------
# Library target
#----------------------------------------------

add_library(nfx-graphics SHARED
    ${NFX_GRAPHICS_SOURCES}
)

if(WIN32)
    set_target_properties(nfx-graphics PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
set_target_properties(nfx-graphics PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_library(nfx::graphics ALIAS nfx-graphics)

#----------------------------------------------
# Library resources
#----------------------------------------------

nfx_graphics_embed_resources(
    TARGET          nfx-graphics
    RESOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/resources/glsl
    OUTPUT_DIR      ${CMAKE_CURRENT_BINARY_DIR}/gen/shaders
    NAMESPACE       nfx::graphics::shaders
    REGISTRY_NAME   embedded_shaders
    PATTERN         "*.vert" "*.frag" "*.geom"
    RECURSE
)

#----------------------------------------------
# Include directories
#----------------------------------------------

target_include_directories(nfx-graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/3rdParty>
)

#----------------------------------------------
# Link libraries
#----------------------------------------------

target_link_libraries(nfx-graphics
    PUBLIC
        nfx::graphics::gl
    PRIVATE
        nfx-graphics-warnings
)

#----------------------------------------------
# Native CPU optimizations (Release only)
#----------------------------------------------

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(nfx-graphics
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
            $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-march=native>
    )
endif()
