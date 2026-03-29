#version 450 core

in vec3 vColor;
in vec3 vPosition;
in float vSign;

out vec4 fragColor;

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
uniform float uOccludedAlpha;

void main()
{
    float alpha = vSign < 0.0 ? 0.3 : 1.0;

    float dist = length(vPosition - camera.position);
    float fading = clamp((uFadeDistance - dist) / uFadeDistance, 0.0, 1.0);
    alpha *= fading * uOccludedAlpha;

    if (alpha < 0.01)
    {
        discard;
    }

    fragColor = vec4(vColor, alpha);
}
