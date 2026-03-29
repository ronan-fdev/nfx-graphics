#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in float aSign;

out vec3 vColor;
out vec3 vPosition;
out float vSign;

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

void main()
{
    gl_Position = camera.viewProj * vec4(aPosition, 1.0);

    vColor = aColor;
    vPosition = aPosition;
    vSign = aSign;
}
