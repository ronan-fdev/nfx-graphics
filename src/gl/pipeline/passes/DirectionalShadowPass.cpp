#include "nfx/graphics/gl/pipeline/passes/DirectionalShadowPass.h"

#include "nfx/graphics/gl/core/buffers/UniformBuffer.h"
#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/resources/MeshCache.h"
#include "nfx/graphics/math/Mat4.h"

#include <embedded_shaders.h>

#include <cassert>
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

        Texture2DHandle allocateDepthTexture(Texture2DCache& texCache, int width, int height)
        {
            return texCache.add(Texture2D::allocate(
                width,
                height,
                { .generateMipmaps = false,
                  .minFilter = Texture2D::Filter::Nearest,
                  .magFilter = Texture2D::Filter::Nearest,
                  .wrapS = Texture2D::Wrap::ClampToEdge,
                  .wrapT = Texture2D::Wrap::ClampToEdge,
                  .internalFormat = Texture2D::InternalFormat::Depth24 }));
        }

    } // namespace

    void DirectionalShadowPass::setLightSpaceMatrix(const float m[16]) noexcept
    {
        std::memcpy(m_depthData.matrix, m, sizeof(m_depthData.matrix));
        if (m_depthUbo.isValid())
        {
            m_depthUbo.upload(m_depthData);
        }
    }

    void DirectionalShadowPass::setResolution(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            assert(width >= 1 && height >= 1 && "DirectionalShadowPass::setResolution: width/height must be >= 1");
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

    ShadowMapData DirectionalShadowPass::shadowMap() const noexcept
    {
        ShadowMapData smd;
        smd.texture = m_shadowHandle;
        std::memcpy(smd.lightSpaceMatrix, m_depthData.matrix, sizeof(smd.lightSpaceMatrix));
        return smd;
    }

    bool DirectionalShadowPass::initialize()
    {
        const auto* vert = shaders::find("passes/shadow_depth.vert");
        const auto* frag = shaders::find("empty.frag");
        if (!vert || !frag)
        {
            std::fprintf(stderr, "[DirectionalShadowPass] Missing embedded shadow depth shaders\n");
            return false;
        }

        m_depthShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, vert->str() }, { ShaderProgram::Stage::Fragment, frag->str() } });

        m_shadowState = RenderState::shadowCaster();

        if (!m_texCache)
        {
            std::fprintf(stderr, "[DirectionalShadowPass] setResolution() must be called before initialize()\n");
            return false;
        }
        Texture2DCache& texCache = *m_texCache;

        // Allocate depth texture in the cache
        m_shadowHandle = allocateDepthTexture(texCache, m_width, m_height);
        const Texture2D* depthTex = texCache.get(m_shadowHandle);
        if (!depthTex)
        {
            std::fprintf(stderr, "[DirectionalShadowPass] Failed to resolve shadow depth texture from cache\n");
            return false;
        }

        m_framebuffer.bind();
        m_framebuffer.attachDepthTexture(*depthTex);
        const auto& gl = Context::current().functions();
        gl.glDrawBuffer(NONE);
        gl.glReadBuffer(NONE);
        const bool complete = m_framebuffer.isComplete();
        m_framebuffer.unbind();
        if (!complete)
        {
            std::fprintf(stderr, "[DirectionalShadowPass] Shadow framebuffer is incomplete\n");
            return false;
        }

        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
        m_dirty = false;

        return m_depthShader.isValid() && m_framebuffer.isValid();
    }

    void DirectionalShadowPass::begin()
    {
        m_executionStats = {};
        m_executionStats.commandsSubmitted = static_cast<std::uint32_t>(m_queue.size());

        if (m_dirty && m_texCache)
        {
            // Remove old depth texture from cache and allocate a new one
            if (m_shadowHandle.isValid())
            {
                m_texCache->remove(m_shadowHandle);
            }
            m_shadowHandle = allocateDepthTexture(*m_texCache, m_width, m_height);
            const Texture2D* depthTex = m_texCache->get(m_shadowHandle);
            if (!depthTex)
            {
                std::fprintf(stderr, "[DirectionalShadowPass] Failed to resolve resized shadow texture\n");
                return;
            }

            m_framebuffer.bind();
            m_framebuffer.attachDepthTexture(*depthTex);
            const auto& gl = Context::current().functions();
            gl.glDrawBuffer(NONE);
            gl.glReadBuffer(NONE);
            const bool resizeComplete = m_framebuffer.isComplete();
            m_framebuffer.unbind();
            if (!resizeComplete)
            {
                std::fprintf(stderr, "[DirectionalShadowPass] Shadow framebuffer incomplete after resize\n");
                return;
            }

            m_dirty = false;
        }

        const auto& gl = Context::current().functions();
        gl.glGetIntegerv(VIEWPORT, m_savedViewport);
        m_framebuffer.bind();
        ++m_executionStats.fboBinds;
        gl.glViewport(0, 0, m_width, m_height);

        m_shadowState.apply();
        gl.glClear(DEPTH_BUFFER_BIT);
        m_depthShader.bind();
        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
    }

    void DirectionalShadowPass::execute(RenderResources& resources)
    {
        if (m_queue.empty())
        {
            return;
        }

        const auto& gl = Context::current().functions();
        const auto& commands = m_queue.commands();
        for (const RenderCommand& cmd : commands)
        {
            if (!cmd.mesh.isValid())
            {
                ++m_executionStats.commandsInvalid;
                continue;
            }

            Mesh* mesh = resources.meshes.get(cmd.mesh);
            if (!mesh)
            {
                std::fprintf(
                    stderr,
                    "[DirectionalShadowPass] mesh handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(cmd.mesh.id));
                ++m_executionStats.commandsInvalid;
                continue;
            }

            m_depthShader.setUniformMat4("uModel", cmd.transform.data());
            drawMeshDepth(gl, *mesh, cmd);
            ++m_executionStats.commandsDrawn;
            ++m_executionStats.vaoBinds;
            ++m_executionStats.vboBinds;
            if (cmd.instanceCount > 1)
            {
                ++m_executionStats.instancedDraws;
            }
        }
    }

    void DirectionalShadowPass::end()
    {
        m_queue.clear();
        m_framebuffer.unbind();

        const auto& gl = Context::current().functions();
        gl.glViewport(m_savedViewport[0], m_savedViewport[1], m_savedViewport[2], m_savedViewport[3]);
    }
} // namespace nfx::graphics::gl
