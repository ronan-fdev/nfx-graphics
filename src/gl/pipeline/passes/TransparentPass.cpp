#include "nfx/graphics/gl/pipeline/passes/TransparentPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/material/Material.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/math/Mat3.h"

#include <algorithm>
#include <cstdio>
#include <vector>

namespace nfx::graphics::gl
{
    namespace
    {
        void drawMesh(const Functions& gl, const Mesh& mesh, const RenderCommand& cmd)
        {
            mesh.bind();
            const GLenum mode = static_cast<GLenum>(cmd.mode);
            const bool instanced = cmd.instanceCount > 1;
            if (mesh.isIndexed())
            {
                const GLenum indexType = mesh.indexType() == Mesh::IndexType::UInt16
                                             ? static_cast<GLenum>(UNSIGNED_SHORT)
                                             : static_cast<GLenum>(UNSIGNED_INT);
                if (instanced)
                {
                    gl.glDrawElementsInstanced(
                        mode,
                        static_cast<GLsizei>(mesh.indexCount()),
                        indexType,
                        nullptr,
                        static_cast<GLsizei>(cmd.instanceCount));
                }
                else
                {
                    gl.glDrawElements(mode, static_cast<GLsizei>(mesh.indexCount()), indexType, nullptr);
                }
            }
            else
            {
                if (instanced)
                {
                    gl.glDrawArraysInstanced(
                        mode, 0, static_cast<GLsizei>(mesh.vertexCount()), static_cast<GLsizei>(cmd.instanceCount));
                }
                else
                {
                    gl.glDrawArrays(mode, 0, static_cast<GLsizei>(mesh.vertexCount()));
                }
            }
        }

        float squaredDistanceToCamera(const RenderCommand& cmd, const float cam[3])
        {
            // Translation is at column 3 of the column-major model matrix
            const float dx = cmd.transform[12] - cam[0];
            const float dy = cmd.transform[13] - cam[1];
            const float dz = cmd.transform[14] - cam[2];
            return dx * dx + dy * dy + dz * dz;
        }
    } // namespace

    void TransparentPass::begin()
    {
        m_targetBound = false;
    }

    void TransparentPass::execute(RenderResources& resources)
    {
        if (m_queue.empty())
        {
            return;
        }

        const auto& gl = Context::current().functions();

        if (m_targetColor.isValid())
        {
            const Texture2D* color = resources.textures2D.get(m_targetColor);
            if (!color)
            {
                std::fprintf(
                    stderr,
                    "[TransparentPass] target color handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(m_targetColor.id));
                return;
            }

            m_targetFbo.bind();
            m_targetFbo.attachColorTexture(*color);
            if (m_targetDepth.isValid())
            {
                const Texture2D* depth = resources.textures2D.get(m_targetDepth);
                if (depth)
                {
                    m_targetFbo.attachDepthTexture(*depth);
                }
            }

            if (!m_targetFbo.isComplete())
            {
                std::fprintf(
                    stderr,
                    "[TransparentPass] framebuffer incomplete after attachments: %s\n",
                    m_targetFbo.statusString());
                m_targetFbo.unbind();
                return;
            }

            gl.glViewport(0, 0, color->width(), color->height());
            m_targetBound = true;
        }

        std::vector<const RenderCommand*> sorted;
        sorted.reserve(m_queue.size());
        for (const RenderCommand& cmd : m_queue.commands())
        {
            sorted.push_back(&cmd);
        }

        // Sort back-to-front by model translation and camera position
        // Keep ordering stable to reduce flicker when distances are nearly equal
        std::stable_sort(sorted.begin(), sorted.end(), [this](const RenderCommand* a, const RenderCommand* b) {
            const float da = squaredDistanceToCamera(*a, m_cameraPos);
            const float db = squaredDistanceToCamera(*b, m_cameraPos);
            if (da != db)
            {
                return da > db;
            }
            return a->sortKey < b->sortKey;
        });

        // Force blending on and depth write off for all transparent draws
        gl.glEnable(BLEND);
        gl.glBlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
        gl.glDepthMask(false);

        Material* lastMaterial = nullptr;

        // Two-pass transparency: back faces first, then front faces
        // This makes convex objects like spheres self-composite correctly
        for (int pass = 0; pass < 2; ++pass)
        {
            gl.glEnable(CULL_FACE);
            gl.glCullFace(pass == 0 ? static_cast<GLenum>(FRONT) : static_cast<GLenum>(BACK));
            lastMaterial = nullptr;

            for (const RenderCommand* cmdPtr : sorted)
            {
                const RenderCommand& cmd = *cmdPtr;
                if (!cmd.mesh.isValid())
                {
                    continue;
                }

                Material* mat = resources.materials.get(cmd.material);
                if (!mat)
                {
                    std::fprintf(
                        stderr,
                        "[TransparentPass] material handle %llu not found, skipping\n",
                        static_cast<unsigned long long>(cmd.material.id));
                    continue;
                }

                if (mat != lastMaterial)
                {
                    mat->bind(resources.shaders, resources.textures2D);
                    gl.glDepthMask(false);
                    gl.glEnable(BLEND);
                    gl.glBlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
                    // culling is managed by the outer pass loop, not the material
                    gl.glEnable(CULL_FACE);
                    gl.glCullFace(pass == 0 ? static_cast<GLenum>(FRONT) : static_cast<GLenum>(BACK));
                    lastMaterial = mat;
                }

                if (ShaderProgram* shader = resources.shaders.get(mat->shader()))
                {
                    shader->setUniformMat4("uModel", cmd.transform.data());

                    float normalMatrix[9];
                    math::mat3InverseTranspose(normalMatrix, cmd.transform.data());
                    shader->setUniformMat3("uNormalMatrix", normalMatrix);
                }
                else
                {
                    std::fprintf(
                        stderr,
                        "[TransparentPass] shader handle %llu not found for material %llu, skipping\n",
                        static_cast<unsigned long long>(mat->shader().id),
                        static_cast<unsigned long long>(cmd.material.id));
                    continue;
                }

                Mesh* mesh = resources.meshes.get(cmd.mesh);
                if (!mesh)
                {
                    std::fprintf(
                        stderr,
                        "[TransparentPass] mesh handle %llu not found, skipping\n",
                        static_cast<unsigned long long>(cmd.mesh.id));
                    continue;
                }

                drawMesh(gl, *mesh, cmd);
            }
        }

        // Restore depth write
        gl.glDepthMask(true);
        gl.glDisable(BLEND);
        gl.glDisable(CULL_FACE);
    }

    void TransparentPass::end()
    {
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
