#pragma once

/**
 * \file Uniforms.h
 * \brief Declares lightweight CPU-side aliases used to pass uniform values to ShaderProgram.
 */

#include <array>
#include <variant>

namespace nfx::graphics::gl
{
    using UniformVec2 = std::array<float, 2>;  ///< Two-component floating-point uniform value
    using UniformVec3 = std::array<float, 3>;  ///< Three-component floating-point uniform value
    using UniformVec4 = std::array<float, 4>;  ///< Four-component floating-point uniform value
    using UniformMat3 = std::array<float, 9>;  ///< 3x3 floating-point matrix uniform value stored in a flat array
    using UniformMat4 = std::array<float, 16>; ///< 4x4 floating-point matrix uniform value stored in a flat array

    // Variant of the supported scalar, vector and matrix uniform value types
    using Uniform = std::variant<int, float, UniformVec2, UniformVec3, UniformVec4, UniformMat3, UniformMat4>;
} // namespace nfx::graphics::gl
