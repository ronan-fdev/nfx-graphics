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
    ${CMAKE_CURRENT_SOURCE_DIR}/app/src/ObjLoader.cpp
)

if(WIN32)
    set_target_properties(nfx-sample-common PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(nfx-sample-common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/app/3rdParty
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/gl/mesh
)

target_link_libraries(nfx-sample-common
    PUBLIC
        nfx::graphics
        nfx-graphics-warnings
    PRIVATE
        $<$<PLATFORM_ID:Linux>:X11>
        $<$<PLATFORM_ID:Windows>:user32;gdi32>
)

add_subdirectory(basic)
add_subdirectory(direct-rendering)

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

#----------------------------------------------
# Embedded resources
#----------------------------------------------

function(nfx_graphics_download_assets)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "" "DIR;BASE_URL" "FILES")
    foreach(_asset ${ARG_FILES})
        if(NOT EXISTS "${ARG_DIR}/${_asset}")
            message(STATUS "[nfx] Downloading ${_asset} ...")
            file(DOWNLOAD
                "${ARG_BASE_URL}/${_asset}"
                "${ARG_DIR}/${_asset}"
                SHOW_PROGRESS
                STATUS _dl_status
            )
            list(GET _dl_status 0 _dl_code)
            if(NOT _dl_code EQUAL 0)
                list(GET _dl_status 1 _dl_err)
                message(WARNING "[nfx] Failed to download ${_asset}: ${_dl_err}")
            endif()
        endif()
    endforeach()
endfunction()

# LearnOpenGL resources (Joey de Vries) - MIT License
# Source: https://github.com/JoeyDeVries/LearnOpenGL/tree/master/resources/textures
nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures/container"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/textures"
    FILES
        container.jpg
)

nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures/brickwall"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/textures"
    FILES
        brickwall.jpg
        brickwall_normal.jpg
)

nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures/toybox"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/textures"
    FILES
        toy_box_diffuse.png
        toy_box_disp.png
        toy_box_normal.png
)

nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures/skyboxes/fjords"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/textures/skybox"
    FILES
        back.jpg
        bottom.jpg
        front.jpg
        left.jpg
        right.jpg
        top.jpg
)

nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/models/obj/rock"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/objects/rock"
    FILES
        rock.obj
        rock.png
)

nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/models/obj/backpack"
    BASE_URL "https://raw.githubusercontent.com/JoeyDeVries/LearnOpenGL/refs/heads/master/resources/objects/backpack"
    FILES
        backpack.obj
        diffuse.jpg
        normal.png
        specular.jpg
        source_attribution.txt
)

# polyhaven.com resources - CC0
nfx_graphics_download_assets(
    DIR      "${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures/rocky_terrain_1k"
    BASE_URL "https://dl.polyhaven.org/file/ph-assets/Textures/jpg/1k/rocky_terrain"
    FILES
        rocky_terrain_diff_1k.jpg
)

nfx_graphics_embed_resources(
    TARGET          nfx-sample-common
    RESOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/app/resources/textures
    OUTPUT_DIR      ${CMAKE_BINARY_DIR}/gen/samples/textures
    NAMESPACE       nfx::samples::textures
    REGISTRY_NAME   embedded_textures
    PATTERN         "*.jpg" "*.png"
    RECURSE
)

nfx_graphics_embed_resources(
    TARGET          nfx-sample-common
    RESOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/app/resources/models
    OUTPUT_DIR      ${CMAKE_BINARY_DIR}/gen/samples/models
    NAMESPACE       nfx::samples::models
    REGISTRY_NAME   embedded_objects
    PATTERN         "*.obj" "*.jpg" "*.png"
    RECURSE
)
