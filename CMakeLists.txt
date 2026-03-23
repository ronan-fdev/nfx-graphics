#==============================================================================
# nfx::graphics - Top-level CMake configuration
#==============================================================================

#----------------------------------------------
# Project definition
#----------------------------------------------

cmake_minimum_required(VERSION 3.25)

project(nfx-graphics
    VERSION 0.0.0
    DESCRIPTION "A lightweight, zero-dependency C++20 OpenGL graphics library."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "-d")

#----------------------------------------------
# Directory paths
#----------------------------------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#----------------------------------------------
# Build options
#----------------------------------------------

option(NFX_GRAPHICS_BUILD_TESTS   "Build nfx-graphics tests"               OFF)
option(NFX_GRAPHICS_BUILD_SAMPLES "Build nfx::graphics sample executables" OFF)

#----------------------------------------------
# Build type
#----------------------------------------------

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug/Release)" FORCE)
endif()

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
# CMake modules configuration
#----------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(nfxGraphicsGlSources)
include(nfxGraphicsGlTarget)
include(nfxGraphicsMathTarget)
include(nfxGraphicsEmbedResources)

#----------------------------------------------
# Tests
#----------------------------------------------

if(NFX_GRAPHICS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#----------------------------------------------
# Samples
#----------------------------------------------

if(NFX_GRAPHICS_BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
