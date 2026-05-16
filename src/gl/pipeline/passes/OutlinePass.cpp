#include "nfx/graphics/gl/pipeline/passes/OutlinePass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/gl/pipeline/RenderState.h"
#include "nfx/graphics/gl/pipeline/ViewportRect.h"
#include "internal/runtime/Error.h"

#include <embedded_shaders.h>

#include <cassert>
#include <cstdio>

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
    } // namespace

    void OutlinePass::setInput(
        Texture2DHandle colorHandle, Texture2DHandle depthHandle, const Framebuffer* geoFbo) noexcept
    {
        m_geoColorHandle = colorHandle;
        m_geoDepthHandle = depthHandle;
        m_geoFbo = geoFbo;
    }

    void OutlinePass::setOutputSize(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            assert(width >= 1 && height >= 1 && "OutlinePass::setOutputSize: width/height must be >= 1");
            return;
        }

        m_texCache = &texCache;
        if (m_width == width && m_height == height && m_outputHandle.isValid())
        {
            return;
        }

        m_width = width;
        m_height = height;
        reallocateTargets();
        m_dirty = false;
    }

    void OutlinePass::reallocateTargets()
    {
        if (!m_texCache || m_width == 0 || m_height == 0)
        {
            return;
        }
        auto& texCache = *m_texCache;

        if (m_maskColorHandle.isValid())
        {
            texCache.remove(m_maskColorHandle);
        }
        if (m_maskDepthHandle.isValid())
        {
            texCache.remove(m_maskDepthHandle);
        }
        if (m_outputHandle.isValid())
        {
            texCache.remove(m_outputHandle);
        }

        m_maskColorHandle = texCache.add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Nearest,
              .magFilter = Texture2D::Filter::Nearest,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA8 }));

        m_maskDepthHandle = texCache.add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Nearest,
              .magFilter = Texture2D::Filter::Nearest,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::Depth24 }));

        m_outputHandle = texCache.add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Linear,
              .magFilter = Texture2D::Filter::Linear,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA8 }));

        const Texture2D* maskColor = texCache.get(m_maskColorHandle);
        const Texture2D* maskDepth = texCache.get(m_maskDepthHandle);
        const Texture2D* outputTex = texCache.get(m_outputHandle);

        if (!maskColor || !maskDepth || !outputTex)
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to resolve internal targets from cache");
            return;
        }

        m_maskFbo.bind();
        m_maskFbo.attachColorTexture(*maskColor);
        m_maskFbo.attachDepthTexture(*maskDepth);
        if (!m_maskFbo.isComplete())
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "mask framebuffer is incomplete");
        }
        m_maskFbo.unbind();

        m_outputFbo.bind();
        m_outputFbo.attachColorTexture(*outputTex);
        if (!m_outputFbo.isComplete())
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Warn,
                internal::runtime::ErrorKind::Recoverable,
                "output framebuffer is incomplete");
        }
        m_outputFbo.unbind();
    }

    bool OutlinePass::initialize()
    {
        const auto* maskVert = shaders::find("passes/outline_mask.vert");
        const auto* maskFrag = shaders::find("mask.frag");

        const auto* fsVert = shaders::find("fullscreen.vert");
        const auto* sobelFrag = shaders::find("passes/outline_sobel.frag");

        if (!maskVert || !maskFrag || !fsVert || !sobelFrag)
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "missing embedded shader resources");
            return false;
        }

        m_maskShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, maskVert->str() }, { ShaderProgram::Stage::Fragment, maskFrag->str() } });
        if (!m_maskShader.isValid())
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to compile mask shader");
            return false;
        }

        m_sobelShader = ShaderProgram::fromSources(
            { { ShaderProgram::Stage::Vertex, fsVert->str() }, { ShaderProgram::Stage::Fragment, sobelFrag->str() } });
        if (!m_sobelShader.isValid())
        {
            internal::runtime::logError(
                "OutlinePass",
                internal::runtime::ErrorLevel::Error,
                internal::runtime::ErrorKind::External,
                "failed to compile sobel shader");
            return false;
        }

        return true;
    }

    void OutlinePass::begin()
    {
        resetRuntimeStats();
        if (m_dirty)
        {
            reallocateTargets();
            m_dirty = false;
        }

        if (!m_outputHandle.isValid() || !m_maskShader.isValid())
        {
            return;
        }

        if (!m_geoColorHandle.isValid() || !m_geoDepthHandle.isValid() || !m_geoFbo)
        {
            return;
        }

        const auto& gl = Context::current().functions();

        gl.glBindFramebuffer(READ_FRAMEBUFFER, m_geoFbo->id());
        gl.glBindFramebuffer(DRAW_FRAMEBUFFER, m_maskFbo.id());
        ++m_runtimeStats.fboBinds;
        gl.glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, DEPTH_BUFFER_BIT, NEAREST);

        m_maskFbo.bind();
        ++m_runtimeStats.fboBinds;
        gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        gl.glClear(COLOR_BUFFER_BIT);
        m_maskFbo.unbind();

        gl.glBindFramebuffer(READ_FRAMEBUFFER, m_geoFbo->id());
        gl.glBindFramebuffer(DRAW_FRAMEBUFFER, m_outputFbo.id());
        ++m_runtimeStats.fboBinds;
        gl.glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, COLOR_BUFFER_BIT, NEAREST);
        gl.glBindFramebuffer(FRAMEBUFFER, 0);
    }

    void OutlinePass::execute(RenderResources& resources)
    {
        if (!m_outputHandle.isValid() || !m_maskFbo.isValid() || !m_sobelShader.isValid() || !m_maskShader.isValid())
        {
            m_queue.clear();
            return;
        }

        if (m_queue.empty())
        {
            return;
        }

        const auto& gl = Context::current().functions();

        {
            RenderState maskState;
            maskState.depthTest = true;
            maskState.depthFunc = RenderState::DepthFunc::LessOrEqual;
            maskState.depthWrite = false;
            maskState.blend = false;
            maskState.cullFace = false;
            maskState.polygonOffset = true;
            maskState.polygonOffsetFactor = -1.0f;
            maskState.polygonOffsetUnits = -1.0f;
            maskState.apply();

            m_maskFbo.bind();
            ++m_runtimeStats.fboBinds;
            if (currentViewport())
            {
                const auto* vp = currentViewport();
                gl.glViewport(vp->x, vp->y, vp->width, vp->height);
            }
            else
            {
                gl.glViewport(0, 0, m_width, m_height);
            }
            m_maskShader.bind();
            ++m_runtimeStats.shaderBinds;

            for (const RenderCommand& cmd : m_queue.commands())
            {
                if (!cmd.mesh.isValid())
                {
                    continue;
                }

                Mesh* mesh = resources.meshes.get(cmd.mesh);
                if (!mesh)
                {
                    char msg[128];
                    std::snprintf(
                        msg,
                        sizeof(msg),
                        "mesh handle %llu not found, skipping",
                        static_cast<unsigned long long>(cmd.mesh.id));
                    internal::runtime::logError(
                        "OutlinePass",
                        internal::runtime::ErrorLevel::Warn,
                        internal::runtime::ErrorKind::Recoverable,
                        msg);
                    continue;
                }

                m_maskShader.setUniformMat4("uModel", cmd.transform.data());
                drawMesh(gl, *mesh, cmd);
                ++m_runtimeStats.drawCalls;
                ++m_runtimeStats.vaoBinds;
                ++m_runtimeStats.vboBinds;
            }

            m_queue.clear();
            m_maskFbo.unbind();
        }

        {
            RenderState sobelState = RenderState::transparent();
            sobelState.depthTest = false;
            sobelState.apply();

            m_outputFbo.bind();
            ++m_runtimeStats.fboBinds;
            if (currentViewport())
            {
                const auto* vp = currentViewport();
                gl.glViewport(vp->x, vp->y, vp->width, vp->height);
            }
            else
            {
                gl.glViewport(0, 0, m_width, m_height);
            }

            if (const Texture2D* maskTex = resources.textures2D.get(m_maskColorHandle))
            {
                maskTex->bind(0);
                ++m_runtimeStats.textureBinds;
            }
            else
            {
                m_outputFbo.unbind();
                return;
            }

            m_sobelShader.bind();
            ++m_runtimeStats.shaderBinds;
            m_sobelShader.setUniform("uMaskTexture", 0);
            m_sobelShader.setUniformVec3("uOutlineColor", m_outlineColor);
            m_sobelShader.setUniform("uThickness", m_thickness);

            drawFullscreenTriangle();
            m_outputFbo.unbind();
        }
    }

    void OutlinePass::end() {}

    void OutlinePass::drawFullscreenTriangle()
    {
        m_dummyVAO.bind();
        ++m_runtimeStats.vaoBinds;
        ++m_runtimeStats.drawCalls;
        Context::current().functions().glDrawArrays(TRIANGLES, 0, 3);
        m_dummyVAO.unbind();
    }
} // namespace nfx::graphics::gl
