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
    ${CMAKE_CURRENT_SOURCE_DIR}/app/src/StbImageImpl.cpp
)

if(WIN32)
    set_target_properties(nfx-sample-common PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(nfx-sample-common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/app/3rdParty
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

#----------------------------------------------
# Third-party sample dependencies
#----------------------------------------------

# stb_image.h - https://github.com/nothings/stb - MIT License
set(NFX_GRAPHICS_SAMPLE_STB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app/3rdParty/stb")
set(NFX_GRAPHICS_SAMPLE_STB_IMAGE_HEADER "${NFX_GRAPHICS_SAMPLE_STB_DIR}/stb_image.h")
if(NOT EXISTS "${NFX_GRAPHICS_SAMPLE_STB_IMAGE_HEADER}")
    file(MAKE_DIRECTORY "${NFX_GRAPHICS_SAMPLE_STB_DIR}")
    message(STATUS "[nfx] Downloading stb_image.h ...")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
        "${NFX_GRAPHICS_SAMPLE_STB_IMAGE_HEADER}"
        SHOW_PROGRESS
        STATUS _stb_image_dl_status
    )
    list(GET _stb_image_dl_status 0 _stb_image_dl_code)
    if(NOT _stb_image_dl_code EQUAL 0)
        list(GET _stb_image_dl_status 1 _stb_image_dl_err)
        message(WARNING "[nfx] Failed to download stb_image.h: ${_stb_image_dl_err}")
    endif()
endif()
