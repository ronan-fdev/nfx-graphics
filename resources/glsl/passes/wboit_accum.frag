#version 450 core

in vec3 vNormalWS;
in vec3 vFragPosWS;

uniform vec3 uColor;
uniform float uOpacity;

layout(location = 0) out vec4 outAccum;
layout(location = 1) out vec4 outReveal;

void main()
{
    vec3 N = normalize(vNormalWS);
    vec3 L = normalize(vec3(0.45, 0.8, 0.35));
    float diffuse = max(dot(N, L), 0.0);

    vec3 litColor = uColor * (0.25 + 0.75 * diffuse);
    float alpha = clamp(uOpacity, 0.0, 1.0);

    // Typical weighted blended OIT weight function
    float weight = clamp(pow(1.0 - gl_FragCoord.z, 3.0) * 8.0 + 0.01, 0.01, 3000.0);

    outAccum = vec4(litColor * alpha, alpha) * weight;
    outReveal = vec4(alpha, alpha, alpha, alpha);
}
