#version 450 core

in vec2 vUv;

out vec4 fragColor;

uniform sampler2D uAtlas;
uniform vec4 uColor;

void main()
{
    float alpha = texture(uAtlas, vUv).a;
    if (alpha < 0.004)
    {
        discard;
    }
    fragColor = vec4(uColor.rgb, uColor.a * alpha);
}
