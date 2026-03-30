#include "nfx/graphics/gl/pipeline/passes/PointShadowPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/resources/MeshCache.h"
#include "nfx/graphics/math/Mat4.h"

#include <embedded_shaders.h>

#include <cassert>
#include <cstdio>
#include <cstring>

namespace nfx::graphics::gl
{
    // 6 face directions: target offset and up vector for each cube face (+X,-X,+Y,-Y,+Z,-Z)
    // clang-format off
    static const float kFaceTargets[6][3] = {
        { 1.f, 0.f, 0.f }, { -1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f }, {  0.f,-1.f, 0.f },
        { 0.f, 0.f, 1.f }, {  0.f, 0.f,-1.f }
    };
    static const float kFaceUps[6][3] = {
        { 0.f,-1.f, 0.f }, { 0.f,-1.f, 0.f },
        { 0.f, 0.f, 1.f }, { 0.f, 0.f,-1.f },
        { 0.f,-1.f, 0.f }, { 0.f,-1.f, 0.f }
    };
    // clang-format on

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

        void buildFaceMatrix(float out[16], const float pos[3], int face, float zNear, float zFar)
        {
            float view[16], proj[16];
            math::mat4LookAt(
                view,
                pos[0],
                pos[1],
                pos[2],
                pos[0] + kFaceTargets[face][0],
                pos[1] + kFaceTargets[face][1],
                pos[2] + kFaceTargets[face][2],
                kFaceUps[face][0],
                kFaceUps[face][1],
                kFaceUps[face][2]);
            math::mat4Perspective(proj, 1.5707963f /* 90 deg */, 1.f, zNear, zFar);
            math::mat4Mul(out, proj, view);
        }

        TextureCubeHandle allocateCube(TextureCubeCache& cache, int size)
        {
            return cache.add(TextureCube::allocate(
                size,
                { .generateMipmaps = false,
                  .minFilter = TextureCube::Filter::Nearest,
                  .magFilter = TextureCube::Filter::Nearest,
                  .wrapS = TextureCube::Wrap::ClampToEdge,
                  .wrapT = TextureCube::Wrap::ClampToEdge,
                  .wrapR = TextureCube::Wrap::ClampToEdge,
                  .internalFormat = TextureCube::InternalFormat::Depth24 }));
        }
    } // namespace

    void PointShadowPass::addLight(const PointLight& point) noexcept
    {
        if (m_pendingCount >= static_cast<int>(PipelineLimits::MaxPointShadows))
        {
            return;
        }
        m_shadowMaps[m_pendingCount].lightPos[0] = point.position[0];
        m_shadowMaps[m_pendingCount].lightPos[1] = point.position[1];
        m_shadowMaps[m_pendingCount].lightPos[2] = point.position[2];
        m_shadowMaps[m_pendingCount].nearPlane = (point.shadowNearPlane > 0.f) ? point.shadowNearPlane : 0.05f;
        m_shadowMaps[m_pendingCount].farPlane = (point.shadowFarPlane > 0.f) ? point.shadowFarPlane
                                                : (point.radius > 0.f)       ? point.radius
                                                                             : 25.f;
        ++m_pendingCount;
    }

    void PointShadowPass::setResolution(TextureCubeCache& texCache, int size)
    {
        if (size < 1)
        {
            assert(size >= 1 && "PointShadowPass::setResolution: size must be >= 1");
            std::fprintf(stderr, "[PointShadowPass] setResolution() requires size >= 1\n");
            return;
        }

        m_texCache = &texCache;
        if (m_size == size)
        {
            return;
        }
        m_size = size;
        m_dirty = true;
    }

    bool PointShadowPass::initialize()
    {
        const auto* vert = shaders::find("passes/point_shadow_depth.vert");
        const auto* geom = shaders::find("passes/point_shadow_depth.geom");
        const auto* frag = shaders::find("passes/point_shadow_depth.frag");
        if (!vert || !geom || !frag)
        {
            std::fprintf(stderr, "[PointShadowPass] Missing embedded point shadow depth shaders\n");
            return false;
        }

        m_depthShader = ShaderProgram::fromSources({ { ShaderProgram::Stage::Vertex, vert->str() },
                                                     { ShaderProgram::Stage::Geometry, geom->str() },
                                                     { ShaderProgram::Stage::Fragment, frag->str() } });

        m_shadowState = RenderState::shadowCaster();
        m_shadowState.cullFace = false;
        m_shadowState.polygonOffset = false;

        if (!m_texCache)
        {
            std::fprintf(stderr, "[PointShadowPass] setResolution() must be called before initialize()\n");
            return false;
        }

        for (int i = 0; i < static_cast<int>(PipelineLimits::MaxPointShadows); ++i)
        {
            m_cubeHandles[i] = allocateCube(*m_texCache, m_size);
            m_shadowMaps[i].texture = m_cubeHandles[i];

            const TextureCube* cube = m_texCache->get(m_cubeHandles[i]);
            if (!cube)
            {
                std::fprintf(stderr, "[PointShadowPass] Failed to resolve point shadow cube map from cache\n");
                return false;
            }

            const auto& gl = Context::current().functions();
            m_framebuffers[i].bind();
            m_framebuffers[i].attachDepthCubemap(cube->id());
            gl.glDrawBuffer(NONE);
            gl.glReadBuffer(NONE);
            if (!m_framebuffers[i].isComplete())
            {
                m_framebuffers[i].unbind();
                std::fprintf(stderr, "[PointShadowPass] Point shadow framebuffer is incomplete\n");
                return false;
            }
            m_framebuffers[i].unbind();
        }

        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
        m_dirty = false;

        return m_depthShader.isValid();
    }

    void PointShadowPass::begin()
    {
        if (m_dirty && m_texCache)
        {
            bool resizeOk = true;
            for (int i = 0; i < static_cast<int>(PipelineLimits::MaxPointShadows); ++i)
            {
                m_texCache->remove(m_cubeHandles[i]);
                m_cubeHandles[i] = allocateCube(*m_texCache, m_size);
                m_shadowMaps[i].texture = m_cubeHandles[i];

                const TextureCube* cube = m_texCache->get(m_cubeHandles[i]);
                if (!cube)
                {
                    std::fprintf(stderr, "[PointShadowPass] Failed to resolve resized point shadow cube map\n");
                    resizeOk = false;
                    break;
                }

                const auto& gl = Context::current().functions();
                m_framebuffers[i].bind();
                m_framebuffers[i].attachDepthCubemap(cube->id());
                gl.glDrawBuffer(NONE);
                gl.glReadBuffer(NONE);
                const bool complete = m_framebuffers[i].isComplete();
                m_framebuffers[i].unbind();
                if (!complete)
                {
                    std::fprintf(
                        stderr,
                        "[PointShadowPass] Point shadow framebuffer[%d] is incomplete after resize: %s\n",
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

        m_lightCount = m_pendingCount;
        m_pendingCount = 0;

        const auto& gl = Context::current().functions();
        gl.glGetIntegerv(VIEWPORT, m_savedViewport);

        m_shadowState.apply();
        m_depthShader.bind();
        m_depthUbo.bind(UboBindings::ShadowDepthBlock);
    }

    void PointShadowPass::execute(RenderResources& resources)
    {
        if (m_queue.empty() || m_lightCount <= 0)
        {
            return;
        }

        const auto& gl = Context::current().functions();
        const auto& commands = m_queue.commands();

        for (int i = 0; i < m_lightCount; ++i)
        {
            const TextureCube* cube = m_texCache->get(m_cubeHandles[i]);
            if (!cube)
            {
                continue;
            }

            // Build all 6 face matrices and pack them with light pos/far into one UBO upload
            ShadowDepthUBO uboData;
            for (int face = 0; face < 6; ++face)
            {
                buildFaceMatrix(
                    uboData.matrices[face],
                    m_shadowMaps[i].lightPos,
                    face,
                    m_shadowMaps[i].nearPlane,
                    m_shadowMaps[i].farPlane);
            }
            uboData.lightPos[0] = m_shadowMaps[i].lightPos[0];
            uboData.lightPos[1] = m_shadowMaps[i].lightPos[1];
            uboData.lightPos[2] = m_shadowMaps[i].lightPos[2];
            uboData.farPlane = m_shadowMaps[i].farPlane;
            m_depthUbo.upload(uboData);

            m_framebuffers[i].bind();
            gl.glViewport(0, 0, m_size, m_size);
            gl.glClear(DEPTH_BUFFER_BIT);

            // Geometry shader amplifies each draw to all 6 faces via gl_Layer
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
                        "[PointShadowPass] mesh handle %llu not found, skipping\n",
                        static_cast<unsigned long long>(cmd.mesh.id));
                    continue;
                }

                m_depthShader.setUniformMat4("uModel", cmd.transform.data());
                drawMeshDepth(gl, *mesh, cmd);
            }
        }
    }

    void PointShadowPass::end()
    {
        m_queue.clear();

        const auto& gl = Context::current().functions();

        m_framebuffers[m_lightCount > 0 ? m_lightCount - 1 : 0].unbind();
        gl.glViewport(m_savedViewport[0], m_savedViewport[1], m_savedViewport[2], m_savedViewport[3]);
    }
} // namespace nfx::graphics::gl
