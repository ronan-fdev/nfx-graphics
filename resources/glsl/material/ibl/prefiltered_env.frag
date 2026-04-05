#version 450 core

in vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;
layout(binding = 0) uniform samplerCube uEnvMap;
uniform int uFace;
uniform float uRoughness;
uniform int uSampleCount;

const float PI = 3.14159265359;

vec3 getFaceDirection(int face, vec2 uv)
{
    vec2 st = uv * 2.0 - 1.0;
    if (face == 0)
        return normalize(vec3(1.0, -st.y, -st.x));
    if (face == 1)
        return normalize(vec3(-1.0, -st.y, st.x));
    if (face == 2)
        return normalize(vec3(st.x, 1.0, st.y));
    if (face == 3)
        return normalize(vec3(st.x, -1.0, -st.y));
    if (face == 4)
        return normalize(vec3(st.x, -st.y, 1.0));
    if (face == 5)
        return normalize(vec3(-st.x, -st.y, -1.0));
    return vec3(0.0);
}

float distributionGGX(float NdotH, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float d = NdotH * NdotH * (a2 - 1.0) + 1.0;
    return a2 / max(PI * d * d, 1e-7);
}

float radicalInverseVdC(uint bits)
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10;
}

vec2 hammersley(uint i, uint N)
{
    return vec2(float(i) / float(N), radicalInverseVdC(i));
}

vec3 importanceSampleGGX(vec2 xi, vec3 N, float roughness)
{
    float a = roughness * roughness;
    float phi = 2.0 * PI * xi.x;
    float cosTheta = sqrt((1.0 - xi.y) / max(1.0 + (a * a - 1.0) * xi.y, 1e-7));
    float sinTheta = sqrt(max(1.0 - cosTheta * cosTheta, 0.0));

    vec3 H = vec3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);

    vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent = normalize(cross(up, N));
    vec3 bitan = cross(N, tangent);
    return normalize(tangent * H.x + bitan * H.y + N * H.z);
}

void main()
{
    vec3 N = getFaceDirection(uFace, vTexCoord);
    vec3 V = N; // split-sum assumption: V = R = N

    vec3 prefilteredColor = vec3(0.0);
    float totalWeight = 0.0;

    uint sampleCount = uint(max(uSampleCount, 1));
    int envSize = textureSize(uEnvMap, 0).x;
    float saTexel = 4.0 * PI / (6.0 * float(envSize * envSize));

    for (uint i = 0u; i < sampleCount; ++i)
    {
        vec2 xi = hammersley(i, sampleCount);
        vec3 H = importanceSampleGGX(xi, N, uRoughness);
        vec3 L = normalize(2.0 * dot(V, H) * H - V);

        float NdotL = max(dot(N, L), 0.0);
        if (NdotL > 0.0)
        {
            float NdotH = max(dot(N, H), 0.0);
            float HdotV = max(dot(H, V), 0.0);
            float D = distributionGGX(NdotH, uRoughness);
            float pdf = D * NdotH / max(4.0 * HdotV, 1e-7);
            float saSample = 1.0 / max(float(sampleCount) * pdf, 1e-7);
            float mipLevel = uRoughness == 0.0 ? 0.0 : 0.5 * log2(saSample / saTexel);

            prefilteredColor += textureLod(uEnvMap, L, mipLevel).rgb * NdotL;
            totalWeight += NdotL;
        }
    }

    prefilteredColor /= max(totalWeight, 1e-7);
    fragColor = vec4(prefilteredColor, 1.0);
}
