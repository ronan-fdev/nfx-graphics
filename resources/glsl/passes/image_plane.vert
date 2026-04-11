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

uniform mat4 uModel;

out vec2 vTexCoord;

const vec2 kPos[6] =
    vec2[](vec2(-0.5, -0.5), vec2(0.5, -0.5), vec2(0.5, 0.5), vec2(-0.5, -0.5), vec2(0.5, 0.5), vec2(-0.5, 0.5));
const vec2 kUV[6] =
    vec2[](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(1.0, 1.0), vec2(0.0, 0.0), vec2(1.0, 1.0), vec2(0.0, 1.0));

void main()
{
    vec3 worldPos = (uModel * vec4(kPos[gl_VertexID], 0.0, 1.0)).xyz;
    gl_Position = camera.viewProj * vec4(worldPos, 1.0);
    vTexCoord = kUV[gl_VertexID];
}
