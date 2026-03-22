#==============================================================================
# nfx::graphics - Samples
#==============================================================================

if(UNIX AND NOT APPLE)
    set(NFX_GRAPHICS_SAMPLE_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/app/src/App_x11.cpp)
elseif(WIN32)
    set(NFX_GRAPHICS_SAMPLE_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/app/src/App_win32.cpp)
else()
    message(STATUS "Samples: skipped (requires Linux/X11 or Windows/WGL)")
    return()
endif()

add_library(nfx-sample-common SHARED
    ${NFX_GRAPHICS_SAMPLE_APP_SRC}
)

if(WIN32)
    set_target_properties(nfx-sample-common PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(nfx-sample-common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(nfx-sample-common
    PUBLIC
        nfx::graphics::gl
        nfx-graphics-warnings
    PRIVATE
        $<$<PLATFORM_ID:Linux>:X11>
        $<$<PLATFORM_ID:Windows>:user32;gdi32>
)

add_subdirectory(basic)
