#version 450 core

in vec2 vTexCoord;
out vec4 fragColor;

uniform sampler2D uColorInput;
uniform float uExposure;
uniform float uGamma;
uniform int uTonemapEnabled;
uniform int uGammaEnabled;

// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
vec3 ACESFilm(vec3 x)
{
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main()
{
    vec3 c = texture(uColorInput, vTexCoord).rgb;

    if (uTonemapEnabled != 0)
    {
        c = ACESFilm(c * uExposure);
    }

    if (uGammaEnabled != 0)
    {
        c = pow(max(c, vec3(0.0)), vec3(1.0 / uGamma));
    }

    fragColor = vec4(c, 1.0);
}
