#version 450 core

layout(location = 0) in vec3 aPosition;

layout(std140, binding = 4) uniform ShadowDepthBlock
{
    mat4 lightSpaceMatrix;
}
lightSpace;

uniform mat4 uModel;

void main()
{
    gl_Position = lightSpace.lightSpaceMatrix * uModel * vec4(aPosition, 1.0);
}
