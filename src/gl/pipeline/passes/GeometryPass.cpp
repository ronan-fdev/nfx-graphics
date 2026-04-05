#include "nfx/graphics/gl/pipeline/passes/GeometryPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/material/Material.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/pipeline/frame/FrameData.h"
#include "nfx/graphics/gl/pipeline/RenderMode.h"
#include "nfx/graphics/math/geometry/Frustum.h"
#include "nfx/graphics/math/Mat3.h"
#include "detail/CullingUtils.h"

#include <cassert>
#include <cstdio>
#include <utility>

namespace nfx::graphics::gl
{
    namespace
    {
        void allocateTargets(
            Texture2DCache& texCache,
            Texture2DHandle& colorHandle,
            Texture2DHandle& depthHandle,
            Framebuffer& fbo,
            int width,
            int height)
        {
            if (colorHandle.isValid())
            {
                texCache.remove(colorHandle);
            }
            if (depthHandle.isValid())
            {
                texCache.remove(depthHandle);
            }

            colorHandle = texCache.add(Texture2D::allocate(
                width,
                height,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Linear,
                  .magFilter = Texture2D::Filter::Linear,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = Texture2D::InternalFormat::RGBA8 }));

            depthHandle = texCache.add(Texture2D::allocate(
                width,
                height,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Nearest,
                  .magFilter = Texture2D::Filter::Nearest,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = Texture2D::InternalFormat::Depth24 }));

            const Texture2D* color = texCache.get(colorHandle);
            const Texture2D* depth = texCache.get(depthHandle);
            if (!color || !depth)
            {
                assert(false && "GeometryPass::allocateTargets: failed to resolve color/depth textures from cache");
                return;
            }

            fbo.bind();
            fbo.attachColorTexture(*color);
            fbo.attachDepthTexture(*depth);
            assert(fbo.isComplete() && "GeometryPass::allocateTargets: framebuffer is incomplete after attachments");
            fbo.unbind();
        }

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
    } // namespace

    void GeometryPass::setOutputSize(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            assert(width >= 1 && height >= 1 && "GeometryPass::setOutputSize: width and height must be >= 1");
            return;
        }

        if (m_width == width && m_height == height && m_colorHandle.isValid())
        {
            return;
        }
        m_width = width;
        m_height = height;

        allocateTargets(texCache, m_colorHandle, m_depthHandle, m_framebuffer, width, height);
    }

    void GeometryPass::begin()
    {
        const auto& gl = Context::current().functions();

        if (!m_colorHandle.isValid() || !m_depthHandle.isValid())
        {
            assert(false && "GeometryPass::begin: setOutputSize() must be called before rendering");
            return;
        }

        m_framebuffer.bind();
        gl.glViewport(0, 0, m_width, m_height);

        m_state.apply();

        GLbitfield clearMask = 0;
        if (m_clearColor.clear)
        {
            gl.glClearColor(m_clearColor.value[0], m_clearColor.value[1], m_clearColor.value[2], m_clearColor.value[3]);
            clearMask |= COLOR_BUFFER_BIT;
        }
        if (m_clearDepth.clear)
        {
            gl.glClearDepth(static_cast<GLdouble>(m_clearDepth.value));
            clearMask |= DEPTH_BUFFER_BIT;
        }
        if (clearMask != 0)
        {
            gl.glClear(clearMask);
        }
    }

    void GeometryPass::execute(RenderResources& resources)
    {
        if (!m_colorHandle.isValid() || !m_depthHandle.isValid())
        {
            return;
        }

        if (m_queue.empty())
        {
            return;
        }

        const auto& ctx = Context::current();
        const auto& gl = ctx.functions();

        m_queue.sort(m_order);
        const auto& commands = m_queue.commands();

        assert(m_patchVertices >= 1 && "GeometryPass::execute: patchVertices must be >= 1");
        const int maxPatch = ctx.maxPatchVertices();
        const int clampedPatch = (m_patchVertices < 1) ? 1 : (m_patchVertices > maxPatch) ? maxPatch : m_patchVertices;
        bool patchStateApplied = false;

        Material* lastMaterial = nullptr;

        for (const RenderCommand& cmd : commands)
        {
            if (!cmd.mesh.isValid())
            {
                continue;
            }

            Material* mat = resources.materials.get(cmd.material);
            if (!mat)
            {
                if (m_fallback)
                {
                    mat = m_fallback;
                }
                else
                {
                    std::fprintf(
                        stderr,
                        "[GeometryPass] material handle %llu not found, skipping\n",
                        static_cast<unsigned long long>(cmd.material.id));
                    continue;
                }
            }

            if (mat != lastMaterial)
            {
                mat->bind(resources.shaders, resources.textures2D);
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
                    "[GeometryPass] shader handle %llu not found for material %llu, skipping\n",
                    static_cast<unsigned long long>(mat->shader().id),
                    static_cast<unsigned long long>(cmd.material.id));
                continue;
            }

            Mesh* mesh = resources.meshes.get(cmd.mesh);
            if (!mesh)
            {
                std::fprintf(
                    stderr,
                    "[GeometryPass] mesh handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(cmd.mesh.id));
                continue;
            }

            if (cmd.mode == RenderMode::Patches && !patchStateApplied)
            {
                gl.glPatchParameteri(PATCH_VERTICES, clampedPatch);
                patchStateApplied = true;
            }

            drawMesh(gl, *mesh, cmd);
        }
    }

    void GeometryPass::end()
    {
        if (m_colorHandle.isValid())
        {
            m_framebuffer.unbind();
        }
    }
} // namespace nfx::graphics::gl
