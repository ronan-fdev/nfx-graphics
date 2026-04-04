#version 450 core

//==============================
// Varyings / outputs
//==============================

in vec3 vNormalWS;
in vec3 vFragPosWS;

#if defined(HAS_BASE_COLOR_MAP) || defined(HAS_NORMAL_MAP) || defined(HAS_METALLIC_ROUGHNESS_MAP) ||                   \
    defined(HAS_ARM_MAP) || defined(HAS_OCCLUSION_MAP)
in vec2 vTexCoord;
#endif

#ifdef HAS_SHADOW
in vec4 vFragPosLS;
#endif

#ifdef HAS_NORMAL_MAP
in mat3 vTBN;
#endif

out vec4 fragColor;

//==============================
// Frame scope (set=0)
//==============================

layout(std140, binding = 0) uniform CameraBlock
{
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec3 position;
    float _pad0;
    vec3 direction;
    float _pad1;
}
camera;

layout(std140, binding = 1) uniform AmbientLightBlock
{
    vec4 colorIntensity;
}
ambient;

layout(std140, binding = 2) uniform DirectionalLightBlock
{
    vec4 direction;
    vec4 colorIntensity;
}
dirLight;

struct LightData
{
    vec4 position;
    vec4 direction;
    vec4 colorIntensity;
    vec4 params;
};

layout(std430, binding = 0) readonly buffer LightBlock
{
    int count;
    int _pad[3];
    LightData lights[64];
}
pointLights;

layout(std140, binding = 3) uniform ShadowMatricesBlock
{
    mat4 dirLightSpace;
    mat4 spotLightSpace[4];
    ivec4 shadowInfo;
}
shadowMatrices;

//==============================
// Material scope (set=1)
//==============================

#ifdef HAS_SHADOW
layout(binding = 12) uniform sampler2D uShadowMap;
#endif

#ifdef HAS_ENV_MAP
layout(binding = 13) uniform samplerCube uEnvMap;
#endif

layout(binding = 4) uniform samplerCube uPointShadowMaps[4];
layout(binding = 8) uniform sampler2D uSpotShadowMaps[4];

#ifdef HAS_BASE_COLOR_MAP
layout(binding = 16) uniform sampler2D uBaseColorMap;
#endif

#ifdef HAS_NORMAL_MAP
layout(binding = 17) uniform sampler2D uNormalMap;
#endif

#ifdef HAS_METALLIC_ROUGHNESS_MAP
layout(binding = 18) uniform sampler2D uMetallicRoughnessMap;
#endif

#ifdef HAS_ARM_MAP
layout(binding = 19) uniform sampler2D uArmMap;
#endif

#ifdef HAS_OCCLUSION_MAP
layout(binding = 19) uniform sampler2D uOcclusionMap;
#endif

layout(std140, binding = 16) uniform MaterialBlock
{
    vec4 baseColor_alpha;
    vec4 specColor_shine; // x=metallic, y=roughness, z=ao, w=unused
    vec4 emissive_env;
}
material;

//==============================
// Helpers
//==============================

const float kPi = 3.14159265359;

float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = NdotH2 * (a2 - 1.0) + 1.0;
    return a2 / max(kPi * denom * denom, 1e-4);
}

float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return NdotV / max(NdotV * (1.0 - k) + k, 1e-4);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    return geometrySchlickGGX(max(dot(N, V), 0.0), roughness) * geometrySchlickGGX(max(dot(N, L), 0.0), roughness);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float pcfSpot(sampler2D sm, vec2 uv, float depth, float bias)
{
    float s = 0.0;
    vec2 ts = 1.0 / textureSize(sm, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            s += (depth - bias) > texture(sm, uv + vec2(x, y) * ts).r ? 0.0 : 1.0;
        }
    }
    return s / 9.0;
}

float spotShadow(int idx, vec3 N, vec3 Lp)
{
    vec4 fragPosLS = shadowMatrices.spotLightSpace[idx] * vec4(vFragPosWS, 1.0);
    if (fragPosLS.w <= 0.0)
    {
        return 1.0;
    }
    vec3 proj = fragPosLS.xyz / fragPosLS.w;
    proj = proj * 0.5 + 0.5;
    if (proj.z > 1.0 || proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0)
    {
        return 1.0;
    }
    float bias = max(0.005 * (1.0 - dot(N, Lp)), 0.001);
    if (idx == 0)
    {
        return pcfSpot(uSpotShadowMaps[0], proj.xy, proj.z, bias);
    }
    if (idx == 1)
    {
        return pcfSpot(uSpotShadowMaps[1], proj.xy, proj.z, bias);
    }
    if (idx == 2)
    {
        return pcfSpot(uSpotShadowMaps[2], proj.xy, proj.z, bias);
    }
    if (idx == 3)
    {
        return pcfSpot(uSpotShadowMaps[3], proj.xy, proj.z, bias);
    }
    return 1.0;
}

float pointShadow(int idx, vec3 N, vec3 Lp)
{
    vec3 fragToLight = vFragPosWS - pointLights.lights[idx].position.xyz;
    vec3 sampleDir = normalize(fragToLight);
    float currentDepth = length(fragToLight);
    float nearPlane = pointLights.lights[idx].params.w;
    if (currentDepth < nearPlane)
    {
        return 1.0;
    }

    float bias = max(0.08 * (1.0 - dot(N, Lp)), 0.02);
    float shadow = 0.0;
    float offset = 0.02;
    const int numSamples = 9;

    // clang-format off
    vec3 offsets[9] = vec3[](
        vec3( 0      ,  0     ,  0     ),
        vec3( offset ,  0     ,  0     ),
        vec3(-offset ,  0     ,  0     ),
        vec3( 0      ,  offset,  0     ),
        vec3( 0      , -offset,  0     ),
        vec3( 0      ,  0     ,  offset),
        vec3( 0      ,  0     , -offset),
        vec3( offset ,  offset,  0     ),
        vec3(-offset , -offset,  0     )
    );
    // clang-format on

    float closestDepth;
    for (int s = 0; s < numSamples; ++s)
    {
        if (idx == 0)
        {
            closestDepth = texture(uPointShadowMaps[0], sampleDir + offsets[s]).r;
        }
        else if (idx == 1)
        {
            closestDepth = texture(uPointShadowMaps[1], sampleDir + offsets[s]).r;
        }
        else if (idx == 2)
        {
            closestDepth = texture(uPointShadowMaps[2], sampleDir + offsets[s]).r;
        }
        else
        {
            closestDepth = texture(uPointShadowMaps[3], sampleDir + offsets[s]).r;
        }
        closestDepth *= pointLights.lights[idx].params.z;
        shadow += (currentDepth - bias) > closestDepth ? 0.0 : 1.0;
    }
    return shadow / float(numSamples);
}

#ifdef HAS_SHADOW
float shadowFactor(vec4 fragPosLS, vec3 N, vec3 L)
{
    vec3 proj = fragPosLS.xyz / fragPosLS.w;
    proj = proj * 0.5 + 0.5;
    if (proj.z > 1.0)
    {
        return 1.0;
    }
    float bias = max(0.005 * (1.0 - dot(N, L)), 0.001);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(uShadowMap, proj.xy + vec2(x, y) * texelSize).r;
            shadow += (proj.z - bias) > pcfDepth ? 0.0 : 1.0;
        }
    }
    return shadow / 9.0;
}
#endif

vec3 evaluateLight(vec3 N, vec3 V, vec3 L, vec3 radiance, vec3 albedo, float metallic, float roughness)
{
    vec3 H = normalize(V + L);
    float NdotL = max(dot(N, L), 0.0);
    float NdotV = max(dot(N, V), 0.0);

    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float D = distributionGGX(N, H, roughness);
    float G = geometrySmith(N, V, L, roughness);

    vec3 numerator = D * G * F;
    float denominator = max(4.0 * NdotV * NdotL, 1e-4);
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);
    vec3 diffuse = kD * albedo / kPi;

    return (diffuse + specular) * radiance * NdotL;
}

//==============================
// Main
//==============================

void main()
{
#ifdef HAS_NORMAL_MAP
    vec3 normalSample = texture(uNormalMap, vTexCoord).rgb * 2.0 - 1.0;
    vec3 N = normalize(vTBN * normalSample);
    if (!gl_FrontFacing)
    {
        N = -N;
    }
#else
    vec3 N = normalize(gl_FrontFacing ? vNormalWS : -vNormalWS);
#endif

    vec3 V = normalize(camera.position - vFragPosWS);

#ifdef HAS_BASE_COLOR_MAP
    vec4 baseColorSample = texture(uBaseColorMap, vTexCoord);
    vec3 albedo = baseColorSample.rgb * material.baseColor_alpha.rgb;
    float alpha = baseColorSample.a * material.baseColor_alpha.a;
#else
    vec3 albedo = material.baseColor_alpha.rgb;
    float alpha = material.baseColor_alpha.a;
#endif

    float metallic = material.specColor_shine.x;
    float roughness = material.specColor_shine.y;
    float ao = material.specColor_shine.z;

#ifdef HAS_ARM_MAP
    vec3 arm = texture(uArmMap, vTexCoord).rgb;
    ao *= arm.r;
    roughness *= arm.g;
    metallic *= arm.b;
#else
    #ifdef HAS_METALLIC_ROUGHNESS_MAP
    vec4 mr = texture(uMetallicRoughnessMap, vTexCoord);
    roughness *= mr.g;
    metallic *= mr.b;
    #endif

    #ifdef HAS_OCCLUSION_MAP
    ao *= texture(uOcclusionMap, vTexCoord).r;
    #endif
#endif

    metallic = clamp(metallic, 0.0, 1.0);
    roughness = clamp(roughness, 0.045, 1.0);
    ao = clamp(ao, 0.0, 1.0);

    vec3 color = ambient.colorIntensity.rgb * ambient.colorIntensity.w * albedo * ao;

    vec3 dirL = normalize(-dirLight.direction.xyz);
    vec3 dirRadiance = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;
    float dirShadow = 1.0;
#ifdef HAS_SHADOW
    dirShadow = (shadowMatrices.shadowInfo.z != 0) ? shadowFactor(vFragPosLS, N, dirL) : 1.0;
#endif
    color += dirShadow * evaluateLight(N, V, dirL, dirRadiance, albedo, metallic, roughness);

    for (int i = 0; i < pointLights.count; ++i)
    {
        vec3 lPos = pointLights.lights[i].position.xyz;
        float radius = pointLights.lights[i].position.w;
        vec3 lDir = pointLights.lights[i].direction.xyz;
        float lType = pointLights.lights[i].direction.w;
        vec3 lColor = pointLights.lights[i].colorIntensity.rgb;
        float lInt = pointLights.lights[i].colorIntensity.w;
        float cosInner = pointLights.lights[i].params.x;
        float cosOuter = pointLights.lights[i].params.y;

        vec3 toLight = lPos - vFragPosWS;
        float dist = length(toLight);
        vec3 Lp = toLight / max(dist, 1e-4);

        float atten;
        if (radius > 0.0)
        {
            float x = clamp(1.0 - dist / radius, 0.0, 1.0);
            atten = x * x;
        }
        else
        {
            atten = 1.0 / max(dist * dist, 1e-4);
        }

        if (lType > 0.5)
        {
            float cd = dot(normalize(-lDir), Lp);
            float spot = smoothstep(cosOuter, cosInner, cd);
            atten *= spot;
        }

        if (atten <= 0.0)
        {
            continue;
        }

        vec3 radiance = lColor * lInt * atten;
        float visibility = 1.0;
        if (lType > 0.5)
        {
            if (i < shadowMatrices.shadowInfo.x)
            {
                visibility *= spotShadow(i, N, Lp);
            }
        }
        else if (i < shadowMatrices.shadowInfo.y)
        {
            visibility *= pointShadow(i, N, Lp);
        }

        color += visibility * evaluateLight(N, V, Lp, radiance, albedo, metallic, roughness);
    }

#ifdef HAS_ENV_MAP
    vec3 R = reflect(-V, N);
    vec3 env = texture(uEnvMap, R).rgb;
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(N, V), 0.0), F0);
    color += env * F * material.emissive_env.w * ao;
#endif

    color += material.emissive_env.rgb;
    fragColor = vec4(color, alpha);
}
