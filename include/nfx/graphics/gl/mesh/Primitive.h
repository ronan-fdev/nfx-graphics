#pragma once

/**
 * \file Primitive.h
 * \brief Declares helpers that generate built-in mesh primitives as MeshData.
 */

#include "MeshData.h"

namespace nfx::graphics::gl
{
    /**
     * \brief Utility class generating built-in primitive meshes.
     */
    class Primitive final
    {
    public:
        Primitive() = delete;

        /**
         * \brief Builds a unit cube mesh.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated cube mesh data.
         */
        static MeshData cube();

        /**
         * \brief Builds a UV sphere mesh.
         * \param stacks Number of vertical subdivisions.
         * \param slices Number of horizontal subdivisions.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated UV sphere mesh data.
         */
        static MeshData uvSphere(int stacks = 24, int slices = 36);

        /**
         * \brief Builds a subdivided XZ plane mesh.
         * \param subdivisionsX Number of subdivisions along the X axis.
         * \param subdivisionsZ Number of subdivisions along the Z axis.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated plane mesh data.
         */
        static MeshData plane(int subdivisionsX = 1, int subdivisionsZ = 1);

        /**
         * \brief Builds a screen-aligned quad mesh.
         *
         * Layout is position + UV (Float3, Float2) only (no normal/tangent generation).
         * \return Generated quad mesh data.
         */
        static MeshData quad();
    };
} // namespace nfx::graphics::gl
