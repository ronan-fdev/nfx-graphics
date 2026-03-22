#pragma once

/**
 * \file GlTypes.h
 * \brief Defines the core OpenGL scalar types, handles and callback aliases without relying on platform GL headers.
 */

#include <cstddef>
#include <cstdint>

// clang-format off
using GLvoid      = void;
using GLchar      = char;
using GLbyte      = std::int8_t;
using GLubyte     = std::uint8_t;
using GLboolean   = std::uint8_t;
using GLshort     = std::int16_t;
using GLushort    = std::uint16_t;
using GLint       = std::int32_t;
using GLsizei     = std::int32_t;
using GLuint      = std::uint32_t;
using GLenum      = std::uint32_t;
using GLbitfield  = std::uint32_t;
using GLfloat     = float;
using GLclampf    = float;
using GLdouble    = double;
using GLclampd    = double;
using GLint64     = std::int64_t;
using GLuint64    = std::uint64_t;
using GLintptr    = std::ptrdiff_t;
using GLsizeiptr  = std::ptrdiff_t;

struct __GLsync;
using GLsync      = __GLsync*;

using GLDEBUGPROC = void (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, const GLvoid*);
// clang-format on
