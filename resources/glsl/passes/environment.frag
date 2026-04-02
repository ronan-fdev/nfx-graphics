#version 450 core

in vec3 vTexCoord;

layout(binding = 13) uniform samplerCube uEnvMap;
uniform float uEnvIntensity;

out vec4 fragColor;

void main()
{
    vec3 envColor = texture(uEnvMap, vTexCoord).rgb;
    fragColor = vec4(envColor * max(uEnvIntensity, 0.0), 1.0);
}
