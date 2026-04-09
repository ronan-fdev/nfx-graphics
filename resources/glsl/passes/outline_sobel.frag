#version 450 core

in vec2 vTexCoord;

uniform sampler2D uMaskTexture;
uniform vec3 uOutlineColor;
uniform float uThickness;

out vec4 fragColor;

const float kEdgeMin = 0.01;
const float kEdgeMax = 0.10;

void main()
{
    vec2 texelSize = uThickness / vec2(textureSize(uMaskTexture, 0));

    float gx = 0.0;
    float gy = 0.0;

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            vec2 offset = vec2(x, y) * texelSize;
            float maskValue = texture(uMaskTexture, vTexCoord + offset).r;

            float kx = float(x);
            float ky = float(y);

            if (abs(x) == 1 && y == 0)
            {
                kx *= 2.0;
            }
            if (abs(y) == 1 && x == 0)
            {
                ky *= 2.0;
            }

            gx += maskValue * kx;
            gy += maskValue * ky;
        }
    }

    float edge = length(vec2(gx, gy));
    edge = smoothstep(kEdgeMin, kEdgeMax, edge);

    fragColor = vec4(uOutlineColor, edge);
}
