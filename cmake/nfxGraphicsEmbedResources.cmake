#==============================================================================
# nfx::graphics::EmbeddedResource- Embed binary files as C++ byte arrays
#==============================================================================

#----------------------------------------------
# Resource generator tool
#----------------------------------------------

add_executable(nfx-graphics-resourcegen
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ResourceGen/main.cpp
)

set_target_properties(nfx-graphics-resourcegen
    PROPERTIES
        CXX_STANDARD          20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS        OFF
)

#----------------------------------------------
# CMake helper function
#----------------------------------------------

function(nfx_graphics_embed_resources)
    cmake_parse_arguments(
        PARSE_ARGV 0
        ARG
        "RECURSE"
        "TARGET;RESOURCE_DIR;OUTPUT_DIR;NAMESPACE;REGISTRY_NAME"
        "PATTERN"
    )

    if(NOT ARG_TARGET)
        message(FATAL_ERROR "nfx_graphics_embed_resources: TARGET is required")
    endif()
    if(NOT ARG_RESOURCE_DIR)
        message(FATAL_ERROR "nfx_graphics_embed_resources: RESOURCE_DIR is required")
    endif()
    if(NOT ARG_OUTPUT_DIR)
        message(FATAL_ERROR "nfx_graphics_embed_resources: OUTPUT_DIR is required")
    endif()
    if(NOT ARG_NAMESPACE)
        message(FATAL_ERROR "nfx_graphics_embed_resources: NAMESPACE is required")
    endif()
    if(NOT ARG_REGISTRY_NAME)
        message(FATAL_ERROR "nfx_graphics_embed_resources: REGISTRY_NAME is required")
    endif()

    set(FILE_PATTERN "${ARG_PATTERN}")
    if(NOT FILE_PATTERN)
        set(FILE_PATTERN "*")
    endif()

    file(MAKE_DIRECTORY "${ARG_OUTPUT_DIR}")

    set(GLOB_PATTERNS "")
    foreach(PATTERN ${FILE_PATTERN})
        if(ARG_RECURSE)
            list(APPEND GLOB_PATTERNS "${ARG_RESOURCE_DIR}/${PATTERN}")
        else()
            list(APPEND GLOB_PATTERNS "${ARG_RESOURCE_DIR}/${PATTERN}")
        endif()
    endforeach()

    if(ARG_RECURSE)
        file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS ${GLOB_PATTERNS})
    else()
        file(GLOB RESOURCE_FILES CONFIGURE_DEPENDS ${GLOB_PATTERNS})
    endif()

    if(NOT RESOURCE_FILES)
        message(WARNING "nfx_graphics_embed_resources: No files found in ${ARG_RESOURCE_DIR} matching: ${FILE_PATTERN}")
        return()
    endif()

    list(REMOVE_DUPLICATES RESOURCE_FILES)
    list(SORT RESOURCE_FILES COMPARE NATURAL)

    set(ALL_FILES "")
    set(ALL_IDS   "")

    foreach(RESOURCE_FILE ${RESOURCE_FILES})
        if(ARG_RECURSE)
            file(RELATIVE_PATH RESOURCE_NAME "${ARG_RESOURCE_DIR}" "${RESOURCE_FILE}")
            string(REPLACE "/" "_" RESOURCE_ID_BASE "${RESOURCE_NAME}")
            string(MAKE_C_IDENTIFIER "${RESOURCE_ID_BASE}" RESOURCE_ID)
        else()
            get_filename_component(RESOURCE_NAME "${RESOURCE_FILE}" NAME)
            string(MAKE_C_IDENTIFIER "${RESOURCE_NAME}" RESOURCE_ID)
        endif()

        set(OUTPUT_CPP "${ARG_OUTPUT_DIR}/resource_${RESOURCE_ID}.cpp")

        list(FIND ALL_IDS "${RESOURCE_ID}" EXISTING_ID_INDEX)
        if(NOT EXISTING_ID_INDEX EQUAL -1)
            message(FATAL_ERROR
                "nfx_graphics_embed_resources: identifier collision for '${RESOURCE_ID}' (resource '${RESOURCE_NAME}'). "
                "Rename one resource or adjust naming inputs.")
        endif()

        add_custom_command(
            OUTPUT  "${OUTPUT_CPP}"
            COMMAND $<TARGET_FILE:nfx-graphics-resourcegen>
                    "${RESOURCE_FILE}"
                    "${OUTPUT_CPP}"
                    "${ARG_NAMESPACE}"
                    "${RESOURCE_NAME}"
                    "${RESOURCE_ID}"
            DEPENDS "${RESOURCE_FILE}" nfx-graphics-resourcegen
            COMMENT "Embedding: ${RESOURCE_NAME}"
            VERBATIM
        )

        list(APPEND ALL_FILES "${OUTPUT_CPP}")
        list(APPEND ALL_IDS   "${RESOURCE_ID}")
    endforeach()

    set(REGISTRY_CPP    "${ARG_OUTPUT_DIR}/${ARG_REGISTRY_NAME}.cpp")
    set(REGISTRY_H      "${ARG_OUTPUT_DIR}/${ARG_REGISTRY_NAME}.h")
    set(REGISTRY_SCRIPT "${ARG_OUTPUT_DIR}/generate_${ARG_REGISTRY_NAME}.cmake")

    file(WRITE "${REGISTRY_SCRIPT}"
"# Auto-generated registry generation script
set(NAMESPACE \"${ARG_NAMESPACE}\")
set(ALL_IDS \"${ALL_IDS}\")

set(REGISTRY_EXTERNS \"\")
set(REGISTRY_ENTRIES \"\")

foreach(ID IN LISTS ALL_IDS)
    string(APPEND REGISTRY_EXTERNS \"    extern const uint8_t \${ID}_data[];\\n\")
    string(APPEND REGISTRY_EXTERNS \"    extern const size_t \${ID}_size;\\n\")
    string(APPEND REGISTRY_EXTERNS \"    extern const char \${ID}_name[];\\n\")
    string(APPEND REGISTRY_ENTRIES \"        { \${ID}_name, \${ID}_data, \${ID}_size },\\n\")
endforeach()

file(WRITE \"${REGISTRY_H}\"
\"// Auto-generated resource registry header
#pragma once

#include <nfx/graphics/EmbeddedResource.h>
#include <string_view>
#include <vector>

namespace \${NAMESPACE}
{
    const std::vector<nfx::graphics::EmbeddedResource>& all();
    const nfx::graphics::EmbeddedResource* find(std::string_view name);
} // namespace \${NAMESPACE}
\")

file(WRITE \"${REGISTRY_CPP}\"
\"// Auto-generated resource registry implementation
#include \\\"${ARG_REGISTRY_NAME}.h\\\"

namespace \${NAMESPACE}
{
\${REGISTRY_EXTERNS}
    const std::vector<nfx::graphics::EmbeddedResource>& all()
    {
        static const std::vector<nfx::graphics::EmbeddedResource> resources = {
\${REGISTRY_ENTRIES}
        };
        return resources;
    }

    const nfx::graphics::EmbeddedResource* find(std::string_view name)
    {
        return nfx::graphics::find(all(), name);
    }
} // namespace \${NAMESPACE}
\")
")

    add_custom_command(
        OUTPUT  "${REGISTRY_CPP}" "${REGISTRY_H}"
        COMMAND ${CMAKE_COMMAND} -P "${REGISTRY_SCRIPT}"
        DEPENDS ${RESOURCE_FILES} "${REGISTRY_SCRIPT}"
        COMMENT "Generating resource registry: ${ARG_REGISTRY_NAME}"
        VERBATIM
    )

    list(APPEND ALL_FILES "${REGISTRY_CPP}")
    set_source_files_properties(${ALL_FILES} PROPERTIES GENERATED TRUE)

    if(NOT TARGET ${ARG_TARGET})
        add_library(${ARG_TARGET} OBJECT ${ALL_FILES})

        target_include_directories(${ARG_TARGET}
            PUBLIC "${ARG_OUTPUT_DIR}"
        )

        set_target_properties(${ARG_TARGET}
            PROPERTIES
                CXX_STANDARD          20
                CXX_STANDARD_REQUIRED ON
                CXX_EXTENSIONS        OFF
                POSITION_INDEPENDENT_CODE ON
        )
    else()
        target_sources(${ARG_TARGET} PRIVATE ${ALL_FILES})
        target_include_directories(${ARG_TARGET} PUBLIC "${ARG_OUTPUT_DIR}")
    endif()

    list(LENGTH ALL_IDS NUM_RESOURCES)
    message(STATUS "[nfx] Embedded ${NUM_RESOURCES} resource(s) into ${ARG_TARGET}")
endfunction()
