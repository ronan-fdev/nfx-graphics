#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
#if defined(HAS_DIFFUSE_MAP) || defined(HAS_NORMAL_MAP) || defined(HAS_SPECULAR_MAP)
layout(location = 2) in vec2 aTexCoord;
#endif
#ifdef HAS_NORMAL_MAP
layout(location = 3) in vec4 aTangent;
#endif

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

#ifdef HAS_SHADOW
layout(std140, binding = 3) uniform ShadowMatricesBlock
{
    mat4 dirLightSpace;
    mat4 spotLightSpace[4];
    ivec4 shadowInfo; // x=spotCount, y=pointCount, z=hasDirShadow, w=hasEnvMap
}
shadowMatrices;
#endif

uniform mat4 uModel;
uniform mat3 uNormalMatrix;

out vec3 vNormalWS;
out vec3 vFragPosWS;
#if defined(HAS_DIFFUSE_MAP) || defined(HAS_NORMAL_MAP) || defined(HAS_SPECULAR_MAP)
out vec2 vTexCoord;
#endif
#ifdef HAS_SHADOW
out vec4 vFragPosLS;
#endif
#ifdef HAS_NORMAL_MAP
out mat3 vTBN;
#endif

void main()
{
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    gl_Position = camera.viewProj * worldPos;
    vFragPosWS = worldPos.xyz;
    vNormalWS = uNormalMatrix * aNormal;
#if defined(HAS_DIFFUSE_MAP) || defined(HAS_NORMAL_MAP) || defined(HAS_SPECULAR_MAP)
    vTexCoord = aTexCoord;
#endif
#ifdef HAS_SHADOW
    vFragPosLS = shadowMatrices.dirLightSpace * worldPos;
#endif
#ifdef HAS_NORMAL_MAP
    vec3 T = normalize(uNormalMatrix * aTangent.xyz);
    vec3 N = normalize(uNormalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N); // re-orthogonalize
    vec3 B = cross(N, T) * aTangent.w;
    vTBN = mat3(T, B, N);
#endif
}
