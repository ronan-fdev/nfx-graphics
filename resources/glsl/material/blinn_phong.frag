#version 450 core

//==============================
// Varyings / outputs
//==============================

in vec3 vNormalWS;
in vec3 vFragPosWS;

#if defined(HAS_DIFFUSE_MAP) || defined(HAS_NORMAL_MAP) || defined(HAS_SPECULAR_MAP)
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
    vec4 position;       // xyz = world pos,  w = radius (0 = infinite)
    vec4 direction;      // xyz = direction,  w = type (0=point, 1=spot)
    vec4 colorIntensity; // rgb = color,      w = intensity
    vec4 params;         // x = cos(inner), y = cos(outer), z = farPlane, w = nearPlane
};

layout(std430, binding = 0) readonly buffer LightBlock
{
    int count;
    int _pad[3];
    LightData lights[64];
}
pointLights;

// Directional + spot light-space matrices + packed flags
layout(std140, binding = 3) uniform ShadowMatricesBlock
{
    mat4 dirLightSpace;
    mat4 spotLightSpace[4];
    ivec4 shadowInfo; // x=spotCount, y=pointCount, z=hasDirShadow, w=hasEnvMap
}
shadowMatrices;

#ifdef HAS_SHADOW
// Frame scope (Renderer-only): directional shadow map bound on unit 12 (TextureBindings::DirectionalShadowMap)
layout(binding = 12) uniform sampler2D uShadowMap;
#endif

#ifdef HAS_ENV_MAP
// Frame scope (Renderer-only): environment cube map bound on unit 13 (TextureBindings::EnvMap)
layout(binding = 13) uniform samplerCube uEnvMap;
#endif

// Point shadow cube maps: units 4-7, always bound by Renderer::bindFrameScope()
layout(binding = 4) uniform samplerCube uPointShadowMaps[4];

// Spot shadow maps: units 8-11, always bound by Renderer::bindFrameScope()
layout(binding = 8) uniform sampler2D uSpotShadowMaps[4];

//==============================
// Material scope (set=1)
//==============================

#ifdef HAS_DIFFUSE_MAP
// Built-in Material scope: diffuse albedo map bound on unit 16 (TextureBindings::DiffuseMap)
layout(binding = 16) uniform sampler2D uDiffuseMap;
#endif

#ifdef HAS_NORMAL_MAP
// Built-in Material scope: tangent-space normal map bound on unit 17 (TextureBindings::NormalMap)
layout(binding = 17) uniform sampler2D uNormalMap;
#endif

#ifdef HAS_SPECULAR_MAP
// Built-in Material scope: specular map bound on unit 18 (TextureBindings::SpecularMap)
layout(binding = 18) uniform sampler2D uSpecularMap;
#endif

layout(std140, binding = 16) uniform MaterialBlock
{
    vec4 baseColor_alpha; // rgb = diffuse/base color  , a = alpha
    vec4 specColor_shine; // rgb = specular color      , w = shininess
    vec4 emissive_env;    // rgb = emissive (default 0), w = envIntensity
}
material;

//==============================
// Helpers
//==============================

// 3x3 PCF on a spot shadow map (static dispatch to avoid non-uniform sampler indexing)
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

    // PCF: sample cube map at 9 slightly offset directions
    float shadow = 0.0;
    float offset = 0.02;
    const int numSamples = 9;

    // clang-format off
    vec3 offsets[9] = vec3[](
        vec3(      0,       0,       0),
        vec3( offset,       0,       0),
        vec3(-offset,       0,       0),
        vec3(      0,  offset,       0),
        vec3(      0, -offset,       0),
        vec3(      0,       0,  offset),
        vec3(      0,       0, -offset),
        vec3( offset,  offset,       0),
        vec3(-offset, -offset,       0)
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
#endif // HAS_SHADOW

//==============================
// Main
//==============================

void main()
{
    // Geometric normal used to guard punctual light hemisphere (prevents normal-map bleed on back faces)
    vec3 geometricN = normalize(gl_FrontFacing ? vNormalWS : -vNormalWS);

#ifdef HAS_NORMAL_MAP
    vec3 normalSample = texture(uNormalMap, vTexCoord).rgb * 2.0 - 1.0;
    vec3 N = normalize(vTBN * normalSample);
    if (!gl_FrontFacing)
    {
        N = -N;
    }
#else
    vec3 N = geometricN;
#endif
    vec3 L = normalize(-dirLight.direction.xyz);
    vec3 V = normalize(camera.position - vFragPosWS);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(N, H), 0.0), material.specColor_shine.w) * step(0.0, diff);
    float shadow = 1.0;
#ifdef HAS_SHADOW
    // shadowInfo.z == 1 when a dir shadow map is active
    // shadowFactor() returns 1.0 (fully lit) even when called with no real shadow map
    shadow = (shadowMatrices.shadowInfo.z != 0) ? shadowFactor(vFragPosLS, N, L) : 1.0;
#endif

    vec3 ambientColor = ambient.colorIntensity.rgb * ambient.colorIntensity.w;
    vec3 lightColor = dirLight.colorIntensity.rgb * dirLight.colorIntensity.w;

#ifdef HAS_DIFFUSE_MAP
    vec3 diffuseColor = texture(uDiffuseMap, vTexCoord).rgb * material.baseColor_alpha.rgb;
#else
    vec3 diffuseColor = material.baseColor_alpha.rgb;
#endif
#ifdef HAS_SPECULAR_MAP
    vec3 specularColor = texture(uSpecularMap, vTexCoord).rgb * material.specColor_shine.rgb;
#else
    vec3 specularColor = material.specColor_shine.rgb;
#endif

    vec3 color = ambientColor * diffuseColor + shadow * diff * lightColor * diffuseColor +
                 shadow * spec * lightColor * specularColor;

    // Punctual lights accumulation (point + spot)
    for (int i = 0; i < pointLights.count; ++i)
    {
        vec3 lPos = pointLights.lights[i].position.xyz;
        float radius = pointLights.lights[i].position.w;
        vec3 lDir = pointLights.lights[i].direction.xyz; // spot direction
        float lType = pointLights.lights[i].direction.w; // 0=point, 1=spot
        vec3 lColor = pointLights.lights[i].colorIntensity.rgb;
        float lInt = pointLights.lights[i].colorIntensity.w;
        float cosInner = pointLights.lights[i].params.x;
        float cosOuter = pointLights.lights[i].params.y;

        vec3 toLight = lPos - vFragPosWS;
        float dist = length(toLight);
        vec3 Lp = toLight / dist;

        // Skip lights on the wrong side of the geometric surface (prevents normal-map bleed on back faces)
        if (dot(geometricN, Lp) <= 0.0)
        {
            continue;
        }

        vec3 Hp = normalize(Lp + V);

        float atten;
        if (radius > 0.0)
        {
            float x = clamp(1.0 - dist / radius, 0.0, 1.0);
            atten = x * x;
        }
        else
        {
            atten = 1.0 / (1.0 + dist * dist);
        }

        // Spot cone attenuation + shadow
        if (lType > 0.5)
        {
            float cosTheta = dot(-Lp, normalize(lDir));
            atten *= smoothstep(cosOuter, cosInner, cosTheta);
            if (i < shadowMatrices.shadowInfo.x)
            {
                atten *= spotShadow(i, N, Lp);
            }
        }
        // Shadow caster test: params.z (farPlane) > 0 iff the light has a shadow map
        else if (pointLights.lights[i].params.z > 0.0)
        {
            atten *= pointShadow(i, N, Lp);
        }

        float dp = max(dot(N, Lp), 0.0);
        float sp = pow(max(dot(N, Hp), 0.0), material.specColor_shine.w) * step(0.0, dp);
        color += atten * lInt * lColor * (dp * diffuseColor + sp * specularColor);
    }

#ifdef HAS_ENV_MAP
    vec3 R = reflect(-V, N);
    vec3 envColor = texture(uEnvMap, R).rgb;
    color = mix(color, envColor, material.emissive_env.w);
#endif

    fragColor = vec4(color, material.baseColor_alpha.a);
}
