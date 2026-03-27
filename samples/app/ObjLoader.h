#pragma once

/**
 * \file ObjLoader.h
 * \brief Declares helpers that load MeshData from source files or embedded resource contents.
 */

#include <nfx/graphics/gl/mesh/MeshData.h>

#include <embedded_objects.h>

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string_view>
#include <istream>

namespace nfx::samples
{
    /**
     * \brief Utility class loading mesh files into CPU-side MeshData structures.
     */
    class ObjLoader final
    {
    public:
        /**
         * \brief Loads mesh data from in-memory OBJ text.
         * \param sourceText OBJ file contents.
         */
        static std::optional<nfx::graphics::gl::MeshData> fromSource(std::string_view sourceText);

        /**
         * \brief Loads mesh data from an OBJ filesystem path.
         * \param path Path to the source OBJ file.
         */
        static std::optional<nfx::graphics::gl::MeshData> fromFile(const std::filesystem::path& path);

    private:
        ObjLoader() = delete;

        static std::optional<nfx::graphics::gl::MeshData> parseOBJ(std::istream& stream, std::string_view sourceName);
    };
} // namespace nfx::samples
