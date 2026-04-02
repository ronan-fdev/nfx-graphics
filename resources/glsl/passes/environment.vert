#version 450 core

layout(std140, binding = 0) uniform CameraBlock
{
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec3 position;
    float _pad0;
    vec3 direction;
    float _pad1;
}
camera;

out vec3 vTexCoord;

// Unit cube vertices (36 verts = 6 faces * 2 tris * 3 verts), generated in the shader
// The trick: position.z = position.w after projection so the skybox sits at depth 1.0 and only fills fragments not
// covered by geometry
void main()
{
    // clang-format off
    const vec3 positions[36] = vec3[](
        // +X
        vec3( 1, -1, -1), vec3( 1, -1,  1), vec3( 1,  1,  1),
        vec3( 1,  1,  1), vec3( 1,  1, -1), vec3( 1, -1, -1),
        // -X
        vec3(-1, -1,  1), vec3(-1, -1, -1), vec3(-1,  1, -1),
        vec3(-1,  1, -1), vec3(-1,  1,  1), vec3(-1, -1,  1),
        // +Y
        vec3(-1,  1, -1), vec3( 1,  1, -1), vec3( 1,  1,  1),
        vec3( 1,  1,  1), vec3(-1,  1,  1), vec3(-1,  1, -1),
        // -Y
        vec3(-1, -1,  1), vec3( 1, -1,  1), vec3( 1, -1, -1),
        vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, -1,  1),
        // +Z
        vec3(-1, -1,  1), vec3(-1,  1,  1), vec3( 1,  1,  1),
        vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1),
        // -Z
        vec3( 1, -1, -1), vec3( 1,  1, -1), vec3(-1,  1, -1),
        vec3(-1,  1, -1), vec3(-1, -1, -1), vec3( 1, -1, -1)
    );
    // clang-format on

    vec3 pos = positions[gl_VertexID];
    vTexCoord = pos;

    // Remove translation from view matrix so the skybox stays centered on the camera
    mat4 viewNoTranslation = mat4(mat3(camera.view));
    vec4 clipPos = camera.proj * viewNoTranslation * vec4(pos, 1.0);

    // Force depth to 1.0 (far plane) so background renders behind everything
    gl_Position = clipPos.xyww;
}
