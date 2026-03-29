#version 450 core

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

uniform float uFadeDistance;

out vec3 vPosition;

const vec2 quadPos[6] =
    vec2[](vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(1.0, 1.0), vec2(-1.0, -1.0), vec2(1.0, 1.0), vec2(-1.0, 1.0));

void main()
{
    vec2 q = quadPos[gl_VertexID] * uFadeDistance;
    vec3 worldPos = vec3(q.x, 0.0, q.y);
    vPosition = worldPos;
    gl_Position = camera.viewProj * vec4(worldPos, 1.0);
}
