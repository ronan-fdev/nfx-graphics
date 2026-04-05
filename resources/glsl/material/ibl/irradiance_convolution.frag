#version 450 core

in vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;
layout(binding = 0) uniform samplerCube uEnvMap;
uniform int uFace;

const float PI = 3.14159265359;

vec3 getFaceDirection(int face, vec2 uv)
{
    vec2 st = uv * 2.0 - 1.0;
    if (face == 0)
        return normalize(vec3(1.0, -st.y, -st.x));
    if (face == 1)
        return normalize(vec3(-1.0, -st.y, st.x));
    if (face == 2)
        return normalize(vec3(st.x, 1.0, st.y));
    if (face == 3)
        return normalize(vec3(st.x, -1.0, -st.y));
    if (face == 4)
        return normalize(vec3(st.x, -st.y, 1.0));
    if (face == 5)
        return normalize(vec3(-st.x, -st.y, -1.0));
    return vec3(0.0);
}

void main()
{
    vec3 N = getFaceDirection(uFace, vTexCoord);

    vec3 up = abs(N.y) < 0.999 ? vec3(0.0, 1.0, 0.0) : vec3(1.0, 0.0, 0.0);
    vec3 right = normalize(cross(up, N));
    up = normalize(cross(N, right));

    vec3 irradiance = vec3(0.0);
    const float sampleDelta = 0.025;
    int sampleCount = 0;

    for (float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for (float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            float sinT = sin(theta);
            float cosT = cos(theta);
            vec3 tangentSample = vec3(sinT * cos(phi), sinT * sin(phi), cosT);
            vec3 sampleDir = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;
            irradiance += texture(uEnvMap, sampleDir).rgb * cosT * sinT;
            ++sampleCount;
        }
    }

    irradiance = PI * irradiance / float(sampleCount);
    fragColor = vec4(irradiance, 1.0);
}
