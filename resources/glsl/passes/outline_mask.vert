#version 450 core

layout(location = 0) in vec3 aPosition;

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

uniform mat4 uModel;

void main()
{
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    gl_Position = camera.viewProj * worldPos;
}
