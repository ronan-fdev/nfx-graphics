#include "nfx/graphics/gl/pipeline/Renderer.h"

#include "nfx/graphics/gl/core/Context.h"
#include "nfx/graphics/gl/pipeline/Bindings.h"

#include <algorithm>
#include <cassert>
#include <utility>

namespace nfx::graphics::gl
{
    void Renderer::addPass(std::unique_ptr<RenderPass> pass)
    {
        if (!pass)
        {
            return;
        }
        m_passes.push_back(std::move(pass));
    }

    RenderPass* Renderer::pass(std::string_view name) noexcept
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        return (it != m_passes.end()) ? it->get() : nullptr;
    }

    const RenderPass* Renderer::pass(std::string_view name) const noexcept
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        return (it != m_passes.end()) ? it->get() : nullptr;
    }

    bool Renderer::removePass(std::string_view name)
    {
        const auto it = std::find_if(m_passes.begin(), m_passes.end(), [name](const std::unique_ptr<RenderPass>& p) {
            if (!p)
            {
                return false;
            }
            return p->name() == name;
        });
        if (it == m_passes.end())
        {
            return false;
        }
        m_passes.erase(it);
        return true;
    }

    void Renderer::initialize(RenderResources& resources)
    {
        m_resources = &resources;
        for (auto& passPtr : m_passes)
        {
            if (!passPtr)
            {
                continue;
            }
            if (!passPtr->m_initialized)
            {
                passPtr->m_initialized = passPtr->initialize();
            }
        }
    }

    void Renderer::render()
    {
        assert(m_resources && "Renderer::render: call initialize() before render()");
        if (!m_resources)
        {
            return;
        }

        bindFrameScope();

        const auto& ctx = Context::current();
        const auto& gl = ctx.functions();
        const bool debugGroups = ctx.isVersionSupported(4, 3);

        for (auto& passPtr : m_passes)
        {
            if (!passPtr)
            {
                continue;
            }
            if (!passPtr->isEnabled())
            {
                continue;
            }

            // Lazy-initialize passes added after initialize()
            if (!passPtr->m_initialized)
            {
                passPtr->m_initialized = passPtr->initialize();
            }

            if (!passPtr->m_initialized)
            {
                continue; // initialization failed, skip
            }

            if (debugGroups)
            {
                gl.glPushDebugGroup(DEBUG_SOURCE_APPLICATION, 0, -1, passPtr->name().c_str());
            }

            passPtr->begin();
            passPtr->execute(*m_resources);
            passPtr->end();

            if (debugGroups)
            {
                gl.glPopDebugGroup();
            }
        }
    }

    void Renderer::bindFrameScope()
    {
        if (!m_frameData.has_value())
        {
            return;
        }

        if (!m_cameraUbo)
        {
            m_cameraUbo.emplace();
        }
        if (!m_ambientUbo)
        {
            m_ambientUbo.emplace();
        }
        if (!m_directionalUbo)
        {
            m_directionalUbo.emplace();
        }
        if (!m_punctualLightsSsbo)
        {
            m_punctualLightsSsbo.emplace();
        }

        const FrameData& frame = *m_frameData;

        m_cameraUbo->upload(frame.camera);
        m_cameraUbo->bind(UboBindings::CameraBlock);

        m_ambientUbo->upload(frame.ambientLight);
        m_ambientUbo->bind(UboBindings::AmbientLightBlock);

        m_directionalUbo->upload(frame.directionalLight);
        m_directionalUbo->bind(UboBindings::DirectionalLightBlock);

        PunctualLight::GpuBlock block{};
        const std::size_t copiedCount = std::min<std::size_t>(frame.lights.size(), PunctualLight::MaxLights);
        block.count = static_cast<int>(copiedCount);
        for (std::size_t i = 0; i < copiedCount; ++i)
        {
            block.lights[i] = frame.lights[i];
        }
        m_punctualLightsSsbo->upload(block);
        m_punctualLightsSsbo->bind(SsboBindings::PunctualLightsBlock);
    }
} // namespace nfx::graphics::gl
