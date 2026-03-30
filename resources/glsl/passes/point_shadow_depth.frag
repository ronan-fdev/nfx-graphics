#version 450 core

in vec3 gFragPosWS;

layout(std140, binding = 4) uniform ShadowDepthBlock
{
    mat4 lightSpaceMatrix[6];
    vec4 lightPosAndFar; // xyz = world position, w = far plane distance
}
lightSpace;

void main()
{
    float dist = length(gFragPosWS - lightSpace.lightPosAndFar.xyz);
    gl_FragDepth = dist / lightSpace.lightPosAndFar.w;
}
