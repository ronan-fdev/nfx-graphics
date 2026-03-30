#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

// 6 face matrices + light position / far plane packed in the same UBO as the depth pass
layout(std140, binding = 4) uniform ShadowDepthBlock
{
    mat4 lightSpaceMatrix[6];
    vec4 lightPosAndFar; // xyz = world position, w = far plane distance
}
lightSpace;

in vec3 vFragPosWS[];
out vec3 gFragPosWS;

void main()
{
    for (int face = 0; face < 6; ++face)
    {
        gl_Layer = face;
        for (int v = 0; v < 3; ++v)
        {
            gFragPosWS = vFragPosWS[v];
            gl_Position = lightSpace.lightSpaceMatrix[face] * vec4(vFragPosWS[v], 1.0);
            EmitVertex();
        }
        EndPrimitive();
    }
}
