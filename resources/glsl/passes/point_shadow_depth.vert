#version 450 core

layout(location = 0) in vec3 aPosition;

uniform mat4 uModel;

out vec3 vFragPosWS;

void main()
{
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    vFragPosWS = worldPos.xyz;
    gl_Position = worldPos; // geometry shader applies per-face view-proj
}
