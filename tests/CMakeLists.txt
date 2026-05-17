#==============================================================================
# nfx::graphics - Tests
#==============================================================================

set(FETCHCONTENT_UPDATES_DISCONNECTED ON  CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET                OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        v2.5.2
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(doctest)

list(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/scripts/cmake")

include(doctest)

#----------------------------------------------
# Test subdirectories
#----------------------------------------------

add_subdirectory(gl)
if(NFX_GRAPHICS_BUILD_GL_RUNTIME_TESTS)
    add_subdirectory(gl-runtime)
endif()
add_subdirectory(math)
