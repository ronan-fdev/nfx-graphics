#pragma once

/**
 * \file VertexLayout.h
 * \brief Declares vertex attribute layout descriptors used to describe buffer formats for vertex arrays.
 */

#include "nfx/graphics/gl/core/GlDefinitions.h"

#include <cassert>
#include <initializer_list>
#include <vector>

namespace nfx::graphics::gl
{
    /**
     * \class VertexLayout
     * \brief Describes the format of one vertex as a sequence of typed attributes.
     *
     * The layout stores the ordered attributes used by a vertex buffer along with
     * their byte offsets and the final vertex stride.
     */
    class VertexLayout final
    {
    public:
        /**
         * \brief Enumerates the supported attribute element formats.
         */
        enum Type : unsigned int
        {
            // clang-format off
            Float,   ///< GL_FLOAT × 1
            Float2,  ///< GL_FLOAT × 2
            Float3,  ///< GL_FLOAT × 3
            Float4,  ///< GL_FLOAT × 4

            Half,    ///< GL_HALF_FLOAT × 1
            Half2,   ///< GL_HALF_FLOAT × 2
            Half3,   ///< GL_HALF_FLOAT × 3
            Half4,   ///< GL_HALF_FLOAT × 4

            Int,     ///< GL_INT × 1
            Int2,    ///< GL_INT × 2
            Int3,    ///< GL_INT × 3
            Int4,    ///< GL_INT × 4

            UInt,    ///< GL_UNSIGNED_INT × 1

            Short2,  ///< GL_SHORT × 2
            Short4,  ///< GL_SHORT × 4

            UShort2, ///< GL_UNSIGNED_SHORT × 2
            UShort4, ///< GL_UNSIGNED_SHORT × 4

            Byte4,   ///< GL_BYTE × 4
            UByte2,  ///< GL_UNSIGNED_BYTE × 2
            UByte3,  ///< GL_UNSIGNED_BYTE × 3
            UByte4,  ///< GL_UNSIGNED_BYTE × 4
            // clang-format on
        };

        /**
         * \brief Describes one attribute inside a vertex.
         */
        struct Attribute
        {
            GLuint location;    ///< Shader location consumed by the attribute
            Type type;          ///< Element format used by the attribute
            bool normalized;    ///< Whether integer data should be normalized when interpreted as floating point
            std::size_t offset; ///< Byte offset of the attribute from the start of the vertex
        };

        VertexLayout() = default;

        /**
         * \brief Builds a tightly packed vertex layout from an ordered list of attribute formats.
         * \param types Attribute formats in the order they appear in a vertex.
         */
        VertexLayout(std::initializer_list<Type> types)
        {
            m_attributes.reserve(types.size());
            for (Type t : types)
            {
                addAttribute(t);
            }
        }

        /**
         * \brief Appends one attribute to the end of the layout.
         * \param type Attribute format to append.
         * \param normalized Whether integer data should be normalized when read as floating-point.
         */
        void addAttribute(Type type, bool normalized = false)
        {
            const GLuint location = static_cast<GLuint>(m_attributes.size());
            const std::size_t offset = m_stride;
            m_attributes.push_back({ location, type, normalized, offset });
            m_stride += size(type);
        }

        /**
         * \brief Returns the byte size of one vertex described by the layout.
         * \return Stride in bytes.
         */
        [[nodiscard]] std::size_t stride() const noexcept { return m_stride; }

        /**
         * \brief Returns the ordered list of vertex attributes.
         * \return Reference to the attribute descriptor array.
         */
        [[nodiscard]] const std::vector<Attribute>& attributes() const noexcept { return m_attributes; }

        /**
         * \brief Returns whether the layout contains no attributes.
         * \return True when no attributes are present, false otherwise.
         */
        [[nodiscard]] bool empty() const noexcept { return m_attributes.empty(); }

        /**
         * \brief Returns the component count for an attribute format.
         * \param t Attribute format to inspect.
         * \return Number of scalar components in the attribute.
         */
        [[nodiscard]] static int count(Type t) noexcept
        {
            switch (t)
            {
                case Float:
                case Half:
                case Int:
                case UInt:
                    return 1;
                case Float2:
                case Half2:
                case Int2:
                case Short2:
                case UShort2:
                case UByte2:
                    return 2;
                case Float3:
                case Half3:
                case Int3:
                case UByte3:
                    return 3;
                case Float4:
                case Half4:
                case Int4:
                case Short4:
                case UShort4:
                case Byte4:
                case UByte4:
                    return 4;
            }

            assert(false && "VertexLayout::count(): invalid VertexLayout::Type");
            return 1;
        }

        /**
         * \brief Returns the OpenGL scalar type constant used by an attribute format.
         * \param t Attribute format to inspect.
         * \return OpenGL scalar type enum (for example FLOAT, INT, UNSIGNED_BYTE).
         */
        [[nodiscard]] static unsigned int type(Type t) noexcept
        {
            switch (t)
            {
                case Float:
                case Float2:
                case Float3:
                case Float4:
                    return FLOAT;
                case Half:
                case Half2:
                case Half3:
                case Half4:
                    return HALF_FLOAT;
                case Int:
                case Int2:
                case Int3:
                case Int4:
                    return INT;
                case UInt:
                    return UNSIGNED_INT;
                case Short2:
                case Short4:
                    return SHORT;
                case UShort2:
                case UShort4:
                    return UNSIGNED_SHORT;
                case Byte4:
                    return BYTE;
                case UByte2:
                case UByte3:
                case UByte4:
                    return UNSIGNED_BYTE;
            }

            assert(false && "VertexLayout::type(): invalid VertexLayout::Type");
            return FLOAT;
        }

        /**
         * \brief Returns the byte size of an attribute format.
         * \param t Attribute format to inspect.
         * \return Attribute size in bytes.
         */
        [[nodiscard]] static std::size_t size(Type t) noexcept
        {
            switch (t)
            {
                case Float:
                    return 4;
                case Float2:
                    return 8;
                case Float3:
                    return 12;
                case Float4:
                    return 16;
                case Half:
                    return 2;
                case Half2:
                    return 4;
                case Half3:
                    return 6;
                case Half4:
                    return 8;
                case Int:
                    return 4;
                case Int2:
                    return 8;
                case Int3:
                    return 12;
                case Int4:
                    return 16;
                case UInt:
                    return 4;
                case Short2:
                    return 4;
                case Short4:
                    return 8;
                case UShort2:
                    return 4;
                case UShort4:
                    return 8;
                case Byte4:
                    return 4;
                case UByte2:
                    return 2;
                case UByte3:
                    return 3;
                case UByte4:
                    return 4;
            }

            assert(false && "VertexLayout::size(): invalid VertexLayout::Type");
            return 4;
        }

        /**
         * \brief Returns whether an attribute type is a true integer type.
         * \param t Attribute format to inspect.
         * \return True for integer formats, false for floating-point formats.
         */
        [[nodiscard]] static bool isInteger(Type t) noexcept
        {
            switch (t)
            {
                case Float:
                case Float2:
                case Float3:
                case Float4:
                case Half:
                case Half2:
                case Half3:
                case Half4:
                    return false;
                case Int:
                case Int2:
                case Int3:
                case Int4:
                case UInt:
                case Short2:
                case Short4:
                case UShort2:
                case UShort4:
                case Byte4:
                case UByte2:
                case UByte3:
                case UByte4:
                    return true;
            }

            assert(false && "VertexLayout::isInteger(): invalid VertexLayout::Type");
            return false;
        }

    private:
        std::vector<Attribute> m_attributes;
        std::size_t m_stride = 0;
    };
} // namespace nfx::graphics::gl
