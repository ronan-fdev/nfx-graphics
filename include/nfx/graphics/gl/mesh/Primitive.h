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
         * \brief Builds an icosphere (geodesic sphere) mesh.
         * \param subdivisions Number of recursive edge subdivisions.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated icosphere mesh data.
         */
        static MeshData icosphere(int subdivisions = 2);

        /**
         * \brief Builds a cylinder mesh centered at origin.
         * \param radius Cylinder radius.
         * \param height Cylinder height.
         * \param slices Number of subdivisions around the circumference.
         * \param stacks Number of vertical subdivisions on the side surface.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated cylinder mesh data.
         */
        static MeshData cylinder(float radius = 0.5f, float height = 1.0f, int slices = 32, int stacks = 1);

        /**
         * \brief Builds a torus mesh.
         * \param majorRadius Distance from the torus center to the center of the tube.
         * \param minorRadius Radius of the tube cross-section.
         * \param majorStacks Number of vertical (tube) subdivisions around the major circle.
         * \param minorStacks Number of subdivisions along the minor circle.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated torus mesh data.
         */
        static MeshData torus(
            float majorRadius = 0.6f, float minorRadius = 0.2f, int majorStacks = 24, int minorStacks = 16);

        /**
         * \brief Builds a cone mesh centered at origin.
         * \param radius Base radius.
         * \param height Cone height.
         * \param slices Number of subdivisions around the base.
         * \param stacks Number of vertical subdivisions on the side surface.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated cone mesh data.
         */
        static MeshData cone(float radius = 0.5f, float height = 1.0f, int slices = 32, int stacks = 1);

        /**
         * \brief Builds a capsule mesh aligned on Y axis, centered at origin.
         * \param radius Capsule radius.
         * \param height Cylinder section height between hemispheres.
         * \param slices Number of subdivisions around the circumference.
         * \param hemisphereStacks Number of subdivisions per hemisphere.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated capsule mesh data.
         */
        static MeshData capsule(float radius = 0.5f, float height = 1.0f, int slices = 32, int hemisphereStacks = 8);

        /**
         * \brief Builds a disk mesh on the XZ plane centered at origin.
         * \param radius Disk radius.
         * \param slices Number of subdivisions around the circumference.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated disk mesh data.
         */
        static MeshData disk(float radius = 0.5f, int slices = 32);

        /**
         * \brief Builds a square-base pyramid mesh centered at origin.
         * \param radius Half-size of the square base on X and Z.
         * \param height Pyramid height.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated pyramid mesh data.
         */
        static MeshData pyramid(float radius = 0.5f, float height = 1.0f);

        /**
         * \brief Builds a triangular-base pyramid (tetrahedron-like) mesh centered at origin.
         * \param radius Circumradius of the triangular base in the XZ plane.
         * \param height Height from base plane to apex.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated tetrahedron mesh data.
         */
        static MeshData tetrahedron(float radius = 0.5f, float height = 1.0f);

        /**
         * \brief Builds a tube mesh (open cylinder without caps) centered at origin.
         * \param radius Tube radius.
         * \param height Tube height.
         * \param slices Number of subdivisions around the circumference.
         * \param stacks Number of vertical subdivisions.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated tube mesh data.
         */
        static MeshData tube(float radius = 0.5f, float height = 1.0f, int slices = 32, int stacks = 1);

        /**
         * \brief Builds a pipe mesh (hollow cylinder with caps) centered at origin.
         * \param outerRadius Outer radius.
         * \param innerRadius Inner radius (must be less than outerRadius).
         * \param height Pipe height.
         * \param slices Number of subdivisions around the circumference.
         * \param stacks Number of vertical subdivisions on the side surfaces.
         *
         * Layout is position + normal + UV + tangent (Float3, Float3, Float2, Float4).
         * \return Generated pipe mesh data.
         */
        static MeshData pipe(
            float outerRadius = 0.5f, float innerRadius = 0.35f, float height = 1.0f, int slices = 32, int stacks = 1);

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
