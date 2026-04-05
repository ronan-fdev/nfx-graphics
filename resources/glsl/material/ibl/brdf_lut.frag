#version 450 core

in vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;

const float PI = 3.14159265359;

float geometrySchlickGGX(float NdotV, float k)
{
    return NdotV / max(NdotV * (1.0 - k) + k, 1e-4);
}

float geometrySmith(float NdotV, float NdotL, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return geometrySchlickGGX(NdotV, k) * geometrySchlickGGX(NdotL, k);
}

vec2 integrateBRDF(float NdotV, float roughness)
{
    vec3 V = vec3(sqrt(max(1.0 - NdotV * NdotV, 0.0)), 0.0, NdotV);
    float A = 0.0;
    float B = 0.0;
    const uint SAMPLE_COUNT = 1024u;
    for (uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        float xi = float(i) / float(SAMPLE_COUNT);
        float phi = 2.0 * PI * xi;
        float a = roughness * roughness;
        float cosTheta = sqrt((1.0 - xi) / (1.0 + (a * a - 1.0) * xi));
        float sinTheta = sqrt(max(1.0 - cosTheta * cosTheta, 0.0));

        vec3 H = vec3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
        vec3 L = normalize(2.0 * dot(V, H) * H - V);

        float NdotL = max(L.z, 0.0);
        float NdotH = max(H.z, 0.0);
        float VdotH = max(dot(V, H), 0.0);
        if (NdotL > 0.0)
        {
            float G = geometrySmith(NdotV, NdotL, roughness);
            float G_Vis = (G * VdotH) / max(NdotH * NdotV, 1e-4);
            float Fc = pow(1.0 - VdotH, 5.0);
            A += (1.0 - Fc) * G_Vis;
            B += Fc * G_Vis;
        }
    }
    return vec2(A, B) / float(SAMPLE_COUNT);
}

void main()
{
    vec2 value = integrateBRDF(vTexCoord.x, vTexCoord.y);
    fragColor = vec4(value, 0.0, 1.0);
}
