#include "nfx/graphics/gl/pipeline/passes/WboitPass.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/core/GlDefinitions.h"
#include "nfx/graphics/gl/material/Material.h"
#include "nfx/graphics/gl/mesh/Mesh.h"
#include "nfx/graphics/math/Mat3.h"

#include <embedded_shaders.h>

#include <algorithm>
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

        void resolveMaterialColorOpacity(const Material& mat, float outColor[3], float& outOpacity)
        {
            outColor[0] = 1.0f;
            outColor[1] = 1.0f;
            outColor[2] = 1.0f;
            outOpacity = 0.5f;

            if (const MaterialBlockData* block = mat.materialBlock())
            {
                outColor[0] = block->baseColor_alpha[0];
                outColor[1] = block->baseColor_alpha[1];
                outColor[2] = block->baseColor_alpha[2];
                outOpacity = std::clamp(block->baseColor_alpha[3], 0.0f, 1.0f);
            }
        }
    } // namespace

    void WboitPass::setGeometryDepth(Texture2DHandle depth) noexcept
    {
        m_geomDepthHandle = depth;

        if (!m_texCache || !m_accumHandle.isValid())
        {
            return;
        }

        const Texture2D* depthTex = m_texCache->get(m_geomDepthHandle);
        if (!depthTex)
        {
            return;
        }

        m_accumFbo.bind();
        m_accumFbo.attachDepthTexture(*depthTex);
        m_accumFbo.unbind();
    }

    void WboitPass::setOutputSize(Texture2DCache& texCache, int width, int height)
    {
        if (width < 1 || height < 1)
        {
            return;
        }

        m_texCache = &texCache;
        if (m_width == width && m_height == height && m_accumHandle.isValid())
        {
            return;
        }
        m_width = width;
        m_height = height;
        reallocate();
    }

    void WboitPass::reallocate()
    {
        if (!m_texCache || m_width == 0 || m_height == 0)
        {
            return;
        }

        if (m_accumHandle.isValid())
        {
            m_texCache->remove(m_accumHandle);
        }
        if (m_revealHandle.isValid())
        {
            m_texCache->remove(m_revealHandle);
        }

        m_accumHandle = m_texCache->add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Nearest,
              .magFilter = Texture2D::Filter::Nearest,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA16F }));

        m_revealHandle = m_texCache->add(Texture2D::allocate(
            m_width,
            m_height,
            { .generateMipmaps = false,
              .minFilter = Texture2D::Filter::Nearest,
              .magFilter = Texture2D::Filter::Nearest,
              .wrapS = Texture2D::Wrap::ClampToEdge,
              .wrapT = Texture2D::Wrap::ClampToEdge,
              .internalFormat = Texture2D::InternalFormat::RGBA8 }));

        const Texture2D* accum = m_texCache->get(m_accumHandle);
        const Texture2D* reveal = m_texCache->get(m_revealHandle);
        if (!accum || !reveal)
        {
            std::fprintf(stderr, "[WboitPass] Failed to resolve accumulation/reveal textures from cache\n");
            return;
        }

        m_accumFbo.bind();
        m_accumFbo.attachColorTexture(*accum, 0);
        m_accumFbo.attachColorTexture(*reveal, 1);
        // Share depth from the geometry pass (depth test read-only against opaque)
        if (m_geomDepthHandle.isValid())
        {
            const Texture2D* depth = m_texCache->get(m_geomDepthHandle);
            if (depth)
            {
                m_accumFbo.attachDepthTexture(*depth);
            }
        }
        m_accumFbo.unbind();
    }

    bool WboitPass::initialize()
    {
        const auto* accumVertRes = shaders::find("passes/wboit_accum.vert");
        const auto* accumFragRes = shaders::find("passes/wboit_accum.frag");
        const auto* fsVertRes = shaders::find("fullscreen.vert");
        const auto* compFragRes = shaders::find("passes/wboit_composite.frag");

        if (!fsVertRes || !accumVertRes || !accumFragRes || !compFragRes)
        {
            std::fprintf(stderr, "[WboitPass] Missing embedded WBOIT shader resources\n");
            return false;
        }

        m_accumShader = ShaderProgram::fromSources({ { ShaderProgram::Stage::Vertex, accumVertRes->str() },
                                                     { ShaderProgram::Stage::Fragment, accumFragRes->str() } });

        if (!m_accumShader.isValid())
        {
            std::fprintf(stderr, "[WboitPass] Failed to compile accumulation shader\n");
            return false;
        }

        m_compositeShader = ShaderProgram::fromSources({ { ShaderProgram::Stage::Vertex, fsVertRes->str() },
                                                         { ShaderProgram::Stage::Fragment, compFragRes->str() } });

        if (!m_compositeShader.isValid())
        {
            std::fprintf(stderr, "[WboitPass] Failed to compile composite shader\n");
            return false;
        }

        return true;
    }

    void WboitPass::begin()
    {
        m_targetBound = false;
        if (m_commands.empty())
        {
            return;
        }

        if (!m_accumHandle.isValid() || !m_revealHandle.isValid() || !m_accumShader.isValid())
        {
            return;
        }

        const auto& gl = Context::current().functions();

        // Bind accumulation FBO with both MRT targets
        m_accumFbo.bind();
        gl.glViewport(0, 0, m_width, m_height);

        const GLenum drawBuffers[2] = { COLOR_ATTACHMENT0, COLOR_ATTACHMENT0 + 1 };
        gl.glDrawBuffers(2, drawBuffers);

        // Clear accum to (0,0,0,0) and reveal to (1,1,1,1)
        const float clearAccum[4] = { 0.f, 0.f, 0.f, 0.f };
        const float clearReveal[4] = { 1.f, 1.f, 1.f, 1.f };
        gl.glClearBufferfv(COLOR, 0, clearAccum);
        gl.glClearBufferfv(COLOR, 1, clearReveal);
    }

    void WboitPass::execute(RenderResources& resources)
    {
        if (m_commands.empty())
        {
            return;
        }
        if (!m_accumHandle.isValid() || !m_revealHandle.isValid())
        {
            return;
        }

        const auto& gl = Context::current().functions();
        auto& meshCache = resources.meshes;
        auto& materialCache = resources.materials;
        auto& textureCache = resources.textures2D;

        // Accumulation pass
        gl.glEnable(DEPTH_TEST);
        gl.glDepthMask(false);

        // Per-attachment blend: attachment 0 additive, attachment 1 multiplicative
        gl.glEnable(BLEND);
        gl.glBlendFunci(0, ONE, ONE);
        gl.glBlendFunci(1, ZERO, ONE_MINUS_SRC_COLOR); // dst *= (1 - reveal)

        m_accumShader.bind();

        for (const auto& cmd : m_commands)
        {
            if (!cmd.mesh.isValid())
            {
                continue;
            }

            Material* mat = materialCache.get(cmd.material);
            if (!mat)
            {
                std::fprintf(
                    stderr,
                    "[WboitPass] material handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(cmd.material.id));

                continue;
            }

            float color[3];
            float opacity;
            resolveMaterialColorOpacity(*mat, color, opacity);

            m_accumShader.setUniformMat4("uModel", cmd.transform.data());
            float normalMatrix[9];
            math::mat3InverseTranspose(normalMatrix, cmd.transform.data());
            m_accumShader.setUniformMat3("uNormalMatrix", normalMatrix);
            m_accumShader.setUniformVec3("uColor", color);
            m_accumShader.setUniform("uOpacity", opacity);

            Mesh* mesh = meshCache.get(cmd.mesh);
            if (!mesh)
            {
                std::fprintf(
                    stderr,
                    "[WboitPass] mesh handle %llu not found, skipping\n",
                    static_cast<unsigned long long>(cmd.mesh.id));
                continue;
            }

            drawMesh(gl, *mesh, cmd);
        }

        // Done with accumulation target
        m_accumFbo.unbind();

        // Composite pass: blend WBOIT result over the configured target color texture
        if (!m_compositeShader.isValid() || !m_targetColor.isValid())
        {
            gl.glDepthMask(true);
            gl.glDisable(BLEND);
            gl.glEnable(DEPTH_TEST);
            return;
        }

        const Texture2D* targetColor = textureCache.get(m_targetColor);
        if (!targetColor)
        {
            std::fprintf(
                stderr,
                "[WboitPass] target color handle %llu not found, skipping composite\n",
                static_cast<unsigned long long>(m_targetColor.id));
            gl.glDepthMask(true);
            gl.glDisable(BLEND);
            gl.glEnable(DEPTH_TEST);
            return;
        }

        m_targetFbo.bind();
        m_targetFbo.attachColorTexture(*targetColor, 0);
        m_targetBound = true;
        gl.glViewport(0, 0, m_width, m_height);

        // Single draw buffer (default color attachment 0 of the geo FBO)
        const GLenum drawBuffer[1] = { COLOR_ATTACHMENT0 };
        gl.glDrawBuffers(1, drawBuffer);

        // Composite blend: avgColor * coverage over existing geo color
        gl.glDisable(DEPTH_TEST);
        gl.glDepthMask(false);
        gl.glEnable(BLEND);
        gl.glBlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);

        m_compositeShader.bind();

        const Texture2D* accum = textureCache.get(m_accumHandle);
        const Texture2D* reveal = textureCache.get(m_revealHandle);
        if (!accum || !reveal)
        {
            std::fprintf(stderr, "[WboitPass] accumulation/reveal textures missing, skipping composite\n");
            gl.glDepthMask(true);
            gl.glDisable(BLEND);
            gl.glEnable(DEPTH_TEST);
            return;
        }

        accum->bind(0);
        reveal->bind(1);
        m_compositeShader.setUniform("uAccum", 0);
        m_compositeShader.setUniform("uReveal", 1);

        m_dummyVAO.bind();
        gl.glDrawArrays(TRIANGLES, 0, 3);

        // Restore state
        gl.glDepthMask(true);
        gl.glDisable(BLEND);
        gl.glEnable(DEPTH_TEST);
    }

    void WboitPass::end()
    {
        m_commands.clear();
        if (m_targetBound)
        {
            m_targetFbo.unbind();
            m_targetBound = false;
        }
    }
} // namespace nfx::graphics::gl
