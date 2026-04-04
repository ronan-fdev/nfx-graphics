#pragma once

/**
 * \file ShaderFeatures.h
 * \brief Declares shader feature flags and helpers used to build preprocessor define lists.
 */

#include <cstdint>
#include <string>
#include <vector>
#include <string_view>

namespace nfx::graphics::gl
{
    // clang-format off
    /**
     * \brief Bitmask describing optional shader capabilities enabled for a material permutation.
     */
    enum class ShaderFeature : std::uint32_t
    {
        None                    = 0,
        HasDiffuseMap           = 1u << 0,
        HasNormalMap            = 1u << 1,
        HasSpecularMap          = 1u << 2,
        HasShadow               = 1u << 3,
        HasEnvMap               = 1u << 4,
        HasBaseColorMap         = 1u << 5,
        HasMetallicRoughnessMap = 1u << 6,
        HasOcclusionMap         = 1u << 7,
        HasArmMap               = 1u << 8
    };
    // clang-format on

    /**
     * \brief Returns the union of two shader feature sets.
     */
    inline ShaderFeature operator|(ShaderFeature a, ShaderFeature b)
    {
        return static_cast<ShaderFeature>(static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b));
    }

    /**
     * \brief In-place union of two shader feature sets.
     */
    inline ShaderFeature& operator|=(ShaderFeature& a, ShaderFeature b)
    {
        a = a | b;
        return a;
    }

    /**
     * \brief Returns the intersection of two shader feature sets.
     */
    inline ShaderFeature operator&(ShaderFeature a, ShaderFeature b)
    {
        return static_cast<ShaderFeature>(static_cast<std::uint32_t>(a) & static_cast<std::uint32_t>(b));
    }

    /**
     * \brief Returns whether a feature set contains a given flag.
     * \param set Feature bitmask to inspect.
     * \param flag Feature flag to test.
     */
    inline bool has(ShaderFeature set, ShaderFeature flag)
    {
        return (set & flag) != ShaderFeature::None;
    }

    /**
     * \brief Returns the preprocessor define names corresponding to each active feature.
     * \param features Feature bitmask to convert.
     * \return A list of define names that can be passed to ShaderProgram::fromSources(..., defines).
     */
    inline std::vector<std::string_view> toDefines(ShaderFeature features)
    {
        std::vector<std::string_view> defines;
        if (has(features, ShaderFeature::HasDiffuseMap))
        {
            defines.push_back("HAS_DIFFUSE_MAP");
        }
        if (has(features, ShaderFeature::HasNormalMap))
        {
            defines.push_back("HAS_NORMAL_MAP");
        }
        if (has(features, ShaderFeature::HasSpecularMap))
        {
            defines.push_back("HAS_SPECULAR_MAP");
        }
        if (has(features, ShaderFeature::HasShadow))
        {
            defines.push_back("HAS_SHADOW");
        }
        if (has(features, ShaderFeature::HasEnvMap))
        {
            defines.push_back("HAS_ENV_MAP");
        }
        if (has(features, ShaderFeature::HasBaseColorMap))
        {
            defines.push_back("HAS_BASE_COLOR_MAP");
        }
        if (has(features, ShaderFeature::HasMetallicRoughnessMap))
        {
            defines.push_back("HAS_METALLIC_ROUGHNESS_MAP");
        }
        if (has(features, ShaderFeature::HasOcclusionMap))
        {
            defines.push_back("HAS_OCCLUSION_MAP");
        }
        if (has(features, ShaderFeature::HasArmMap))
        {
            defines.push_back("HAS_ARM_MAP");
        }
        return defines;
    }

    /**
     * \brief Returns a human-readable string of active feature flags.
     * \param features Feature bitmask to describe.
     */
    inline std::string toDebugString(ShaderFeature features)
    {
        if (features == ShaderFeature::None)
        {
            return "None";
        }
        std::string s;
        auto append = [&](const char* name) {
            if (!s.empty())
            {
                s += '|';
            }
            s += name;
        };
        if (has(features, ShaderFeature::HasDiffuseMap))
        {
            append("HasDiffuseMap");
        }
        if (has(features, ShaderFeature::HasNormalMap))
        {
            append("HasNormalMap");
        }
        if (has(features, ShaderFeature::HasSpecularMap))
        {
            append("HasSpecularMap");
        }
        if (has(features, ShaderFeature::HasShadow))
        {
            append("HasShadow");
        }
        if (has(features, ShaderFeature::HasEnvMap))
        {
            append("HasEnvMap");
        }
        if (has(features, ShaderFeature::HasBaseColorMap))
        {
            append("HasBaseColorMap");
        }
        if (has(features, ShaderFeature::HasMetallicRoughnessMap))
        {
            append("HasMetallicRoughnessMap");
        }
        if (has(features, ShaderFeature::HasOcclusionMap))
        {
            append("HasOcclusionMap");
        }
        if (has(features, ShaderFeature::HasArmMap))
        {
            append("HasArmMap");
        }
        return s;
    }
} // namespace nfx::graphics::gl
