#version 450 core

in vec3 vPosition;

out vec4 fragColor;

uniform float uGridSize;
uniform float uFadeDistance;
uniform vec3 uGridColor;

vec4 grid(vec3 fragPos3D, float scale)
{
    vec2 coord = fragPos3D.xz / scale;
    vec2 derivative = fwidth(coord);
    vec2 g = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(g.x, g.y);
    return vec4(uGridColor, 1.0 - min(line, 1.0));
}

void main()
{
    float dist = length(vPosition.xz);
    float fading = clamp((uFadeDistance - dist) / uFadeDistance, 0.0, 1.0);

    fragColor = grid(vPosition, uGridSize);
    fragColor.a *= fading;

    if (fragColor.a < 0.01)
    {
        discard;
    }
}
