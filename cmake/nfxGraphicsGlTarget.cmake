#==============================================================================
# nfx::graphics::gl - Target configuration
#==============================================================================

#----------------------------------------------
# OpenGL dependencies
#----------------------------------------------

find_package(OpenGL REQUIRED)

#----------------------------------------------
# Library target
#----------------------------------------------

add_library(nfx-graphics-gl SHARED
    ${NFX_GRAPHICS_GL_SOURCES}
)

if(WIN32)
    set_target_properties(nfx-graphics-gl PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
set_target_properties(nfx-graphics-gl PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_library(nfx::graphics::gl ALIAS nfx-graphics-gl)

#----------------------------------------------
# Include directories
#----------------------------------------------

target_include_directories(nfx-graphics-gl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/3rdParty>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#----------------------------------------------
# Link libraries
#----------------------------------------------

target_link_libraries(nfx-graphics-gl
    PUBLIC
        OpenGL::GL
    PRIVATE
        nfx::graphics::internal
        nfx::graphics::warnings
)

#----------------------------------------------
# Compile definitions
#----------------------------------------------

target_compile_definitions(nfx-graphics-gl
    PUBLIC
        $<$<CONFIG:Debug>:NFX_GRAPHICS_DEBUG_OPENGL>
)

#----------------------------------------------
# Native CPU optimizations (Release only)
#----------------------------------------------

target_compile_options(nfx-graphics-gl
    PRIVATE
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/arch:AVX2>
        $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-march=native>
)

#----------------------------------------------
# Khronos extension headers
#----------------------------------------------

if(NOT WIN32)
    return()
endif()

set(NFX_GRAPHICS_3RDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty")

set(_khronos_headers
    "GL/glext.h|https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/main/api/GL/glext.h"
    "GL/wglext.h|https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/main/api/GL/wglext.h"
    "KHR/khrplatform.h|https://raw.githubusercontent.com/KhronosGroup/EGL-Registry/main/api/KHR/khrplatform.h"
)

foreach(_entry ${_khronos_headers})
    string(REPLACE "|" ";" _parts "${_entry}")
    list(GET _parts 0 _rel)
    list(GET _parts 1 _url)

    set(_dest "${NFX_GRAPHICS_3RDPARTY_DIR}/${_rel}")
    if(NOT EXISTS "${_dest}")
        get_filename_component(_dest_dir "${_dest}" DIRECTORY)
        file(MAKE_DIRECTORY "${_dest_dir}")
        message(STATUS "[nfx] Downloading ${_rel} ...")
        file(DOWNLOAD "${_url}" "${_dest}" SHOW_PROGRESS STATUS _dl_status)
        list(GET _dl_status 0 _dl_code)
        if(NOT _dl_code EQUAL 0)
            list(GET _dl_status 1 _dl_err)
            message(FATAL_ERROR "[nfx] Failed to download ${_rel}: ${_dl_err}")
        endif()
    endif()
endforeach()
