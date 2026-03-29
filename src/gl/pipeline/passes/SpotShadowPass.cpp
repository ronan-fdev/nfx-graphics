#include "nfx/graphics/gl/pipeline/passes/SpotShadowPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/resources/MeshCache.h"
#include "nfx/graphics/math/Mat4.h"

#include <embedded_shaders.h>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

namespace nfx::graphics::gl
{
    namespace
    {
        void drawMeshDepth(const Functions& gl, const Mesh& mesh, const RenderCommand& cmd)
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

        void buildSpotLightSpaceMatrix(float out[16], const gl::SpotLight& spot) noexcept
        {
            const float px = spot.position[0];
            const float py = spot.position[1];
            const float pz = spot.position[2];

            float dx = spot.direction[0], dy = spot.direction[1], dz = spot.direction[2];
            const float dlen = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (dlen > 1e-6f)
            {
                dx /= dlen;
                dy /= dlen;
                dz /= dlen;
            }

            // Up vector: avoid singularity when spot points straight up/down
            float upx = 0.f, upy = 1.f, upz = 0.f;
            if (std::abs(dy) > 0.999f)
            {
                upx = 1.f;
                upy = 0.f;
            }

            float view[16];
            math::mat4LookAt(view, px, py, pz, px + dx, py + dy, pz + dz, upx, upy, upz);

            const float fovY = 2.f * spot.outerAngle;
            const float zFar = (spot.shadowFarPlane > 0.f) ? spot.shadowFarPlane : 50.f;
            float proj[16];
            math::mat4Perspective(proj, fovY, 1.f, 0.1f, zFar);

            math::mat4Mul(out, proj, view);
        }

        Texture2DHandle allocateDepthTex(Texture2DCache& cache, int w, int h)
        {
            return cache.add(Texture2D::allocate(
                w,
                h,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Nearest,
                  .magFilter = Texture2D::Filter::Nearest,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = Texture2D::InternalFormat::Depth24 }));
        }
    } // namespace

    void SpotShadowPass::addLight(const SpotLight& spot) noexcept
    {
        if (m_pendingCount >= static_cast<int>(PipelineLimits::MaxSpotShadows))
        {
            return;
        }
        m_lights[m_pendingCount] = spot;
        ++m_pendingCount;
    }

    void SpotShadowPass::setResolution(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            assert(width >= 1 && height >= 1 && "SpotShadowPass::setResolution: width/height must be >= 1");
            return;
        }

        m_texCache = &texCache;
        if (m_width == width && m_height == height)
        {
            return;
        }
        m_width = width;
        m_height = height;
        m_dirty = true;
    }

    bool SpotShadowPass::initialize()
    {
        // Reuse the same depth-only shader as ShadowPass
        const auto* vert = shaders::find("passes/shadow_depth.vert");
        const auto* frag = shaders::find("empty.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[SpotShadowPass] Missing embedded shadow depth shaders\n");
            return false;
        }
        m_depthShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        m_shadowState = RenderState::shadowCaster();

        if (!m_texCache)
        {
            std::fprintf(stderr, "[SpotShadowPass] setResolution() must be called before initialize()\n");
            return false;
        }

        // Allocate one depth texture + FBO per slot
        for (int i = 0; i < static_cast<int>(PipelineLimits::MaxSpotShadows); ++i)
        {
            m_depthHandles[i] = allocateDepthTex(*m_texCache, m_width, m_height);
            m_shadowMaps[i].texture = m_depthHandles[i];

            const Texture2D* tex = m_texCache->get(m_depthHandles[i]);
            if (!tex)
            {
                std::fprintf(stderr, "[SpotShadowPass] Failed to resolve shadow depth texture from cache\n");
                return false;
            }
            m_framebuffers[i].bind();
            m_framebuffers[i].attachDepthTexture(*tex);
            const auto& gl = Context::current().functions();
            gl.glDrawBuffer(NONE);
            gl.glReadBuffer(NONE);
            const bool complete = m_framebuffers[i].isComplete();
            m_framebuffers[i].unbind();
            if (!complete)
            {
                std::fprintf(
                    stderr,
                    "[SpotShadowPass] shadow framebuffer[%d] incomplete after initialize: %s\n",
                    i,
                    m_framebuffers[i].statusString());
                return false;
            }
        }

        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
        m_dirty = false;

        return m_depthShader.isValid();
    }

    void SpotShadowPass::begin()
    {
        // Reallocate textures if resolution changed
        if (m_dirty && m_texCache)
        {
            bool resizeOk = true;
            for (int i = 0; i < static_cast<int>(PipelineLimits::MaxSpotShadows); ++i)
            {
                m_texCache->remove(m_depthHandles[i]);
                m_depthHandles[i] = allocateDepthTex(*m_texCache, m_width, m_height);
                m_shadowMaps[i].texture = m_depthHandles[i];

                const Texture2D* tex = m_texCache->get(m_depthHandles[i]);
                if (!tex)
                {
                    std::fprintf(stderr, "[SpotShadowPass] Failed to resolve resized shadow texture\n");
                    resizeOk = false;
                    break;
                }
                m_framebuffers[i].bind();
                m_framebuffers[i].attachDepthTexture(*tex);
                const auto& gl = Context::current().functions();
                gl.glDrawBuffer(NONE);
                gl.glReadBuffer(NONE);
                const bool complete = m_framebuffers[i].isComplete();
                m_framebuffers[i].unbind();
                if (!complete)
                {
                    std::fprintf(
                        stderr,
                        "[SpotShadowPass] shadow framebuffer[%d] incomplete after resize: %s\n",
                        i,
                        m_framebuffers[i].statusString());
                    resizeOk = false;
                    break;
                }
            }

            if (!resizeOk)
            {
                m_lightCount = 0;
                m_pendingCount = 0;
                return;
            }

            m_dirty = false;
        }

        // Commit lights registered via addLight() before render(), reset for next frame
        m_lightCount = m_pendingCount;
        m_pendingCount = 0;
        for (int i = 0; i < m_lightCount; ++i)
        {
            buildSpotLightSpaceMatrix(m_shadowMaps[i].lightSpaceMatrix, m_lights[i]);
        }

        const auto& gl = Context::current().functions();
        gl.glGetIntegerv(VIEWPORT, m_savedViewport);

        m_shadowState.apply();
        m_depthShader.bind();
        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
    }

    void SpotShadowPass::execute(RenderResources& resources)
    {
        if (m_queue.empty() || m_lightCount <= 0)
        {
            return;
        }

        const auto& gl = Context::current().functions();
        const auto& commands = m_queue.commands();

        for (int i = 0; i < m_lightCount; ++i)
        {
            m_framebuffers[i].bind();
            gl.glViewport(0, 0, m_width, m_height);
            gl.glClear(DEPTH_BUFFER_BIT);

            // Upload this spot's light-space matrix to ShadowDepth=4
            ShadowDepthUBO uboData;
            std::memcpy(uboData.matrix, m_shadowMaps[i].lightSpaceMatrix, sizeof(uboData.matrix));
            m_depthUbo.upload(uboData);

            // Render the scene from this spot's POV
            for (const RenderCommand& cmd : commands)
            {
                if (!cmd.mesh.isValid())
                {
                    continue;
                }

                Mesh* mesh = resources.meshes.get(cmd.mesh);
                if (!mesh)
                {
                    std::fprintf(
                        stderr,
                        "[SpotShadowPass] mesh handle %llu not found, skipping\n",
                        static_cast<unsigned long long>(cmd.mesh.id));
                    continue;
                }

                m_depthShader.setUniformMat4("uModel", cmd.transform.data());
                drawMeshDepth(gl, *mesh, cmd);
            }
        }
    }

    void SpotShadowPass::end()
    {
        m_queue.clear();

        const auto& gl = Context::current().functions();
        m_framebuffers[m_lightCount > 0 ? m_lightCount - 1 : 0].unbind();
        gl.glViewport(m_savedViewport[0], m_savedViewport[1], m_savedViewport[2], m_savedViewport[3]);
    }
} // namespace nfx::graphics::gl
