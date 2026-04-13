#version 450 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUv;

out vec2 vUv;

uniform vec2 uViewport;

void main()
{
    vec2 ndc = (aPos / uViewport) * 2.0 - 1.0;
    ndc.y = -ndc.y;
    gl_Position = vec4(ndc, 0.0, 1.0);
    vUv = aUv;
}
