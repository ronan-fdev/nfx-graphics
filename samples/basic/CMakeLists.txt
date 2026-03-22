#==============================================================================
# nfx::graphics - Basic samples
#==============================================================================

file(GLOB_RECURSE NFX_GRAPHICS_BASIC_SAMPLE_SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(source IN LISTS NFX_GRAPHICS_BASIC_SAMPLE_SOURCES)
    cmake_path(GET source STEM sample_name)
    set(target "basic-${sample_name}")

    add_executable(${target} ${source})
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "-d")

    target_link_libraries(${target}
        PRIVATE
            nfx-sample-common
    )
endforeach()
