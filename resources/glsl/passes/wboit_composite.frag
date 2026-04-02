#version 450 core

in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2D uAccum;  // RGBA16F - weighted colour sum
uniform sampler2D uReveal; // R8      - coverage product

void main()
{
    vec4 accum = texture(uAccum, vTexCoord);
    float reveal = texture(uReveal, vTexCoord).r;

    // Avoid division by near-zero alpha
    if (accum.a < 1e-4)
    {
        discard;
    }

    // Reconstruct average colour and composite with (1 - coverage)
    vec3 avgColor = accum.rgb / accum.a;
    fragColor = vec4(avgColor, 1.0 - reveal);
}
