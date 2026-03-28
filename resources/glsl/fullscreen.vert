#version 450 core

out vec2 vTexCoord;

// Fullscreen triangle
void main()
{
    vec2 pos = vec2(
        (gl_VertexID == 0)   ? -1.0
        : (gl_VertexID == 1) ? 3.0
                             : -1.0,
        (gl_VertexID == 0)   ? -1.0
        : (gl_VertexID == 1) ? -1.0
                             : 3.0);

    vTexCoord = pos * 0.5 + 0.5;
    gl_Position = vec4(pos, 0.0, 1.0);
}
