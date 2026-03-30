#version 450 core

layout(std140, binding = 16) uniform MaterialBlock
{
    vec4 baseColor_alpha; // rgb = diffuse/base color, a = alpha
    vec4 specColor_shine; // rgb = specular color    , w = shininess
}
material;

out vec4 fragColor;

void main()
{
    fragColor = vec4(material.baseColor_alpha.rgb, material.baseColor_alpha.a);
}
