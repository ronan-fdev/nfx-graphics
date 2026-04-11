#version 450 core

in vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D uImage;
uniform float uOpacity;

void main()
{
    vec4 color = texture(uImage, vTexCoord);
    fragColor = vec4(color.rgb, color.a * uOpacity);
}
