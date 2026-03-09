#version 450 core
#extension GL_ARB_bindless_texture : require

struct QuadData {
    vec4 rect;
    vec4 color;
    sampler2D texture;
};

layout (std430, binding = 1) buffer Quads {
    QuadData quads[];
};

flat out int v_quad_idx;
uniform mat4 u_proj;

out vec2 v_uv;

const vec2 uvs[4] = vec2[4](
    vec2(0.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0),
    vec2(1.0, 0.0)
);

const vec2 aPos[4] = vec2[4](
    vec2(0.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0),
    vec2(1.0, 0.0)
);
int indices[6] = {0, 1, 2, 0, 2, 3};


void main() {
    int quad_idx = gl_InstanceID;
    v_quad_idx = quad_idx;
    QuadData quad = quads[quad_idx];
    const int idx = indices[gl_VertexID % 6];
    v_uv = uvs[idx];

    gl_Position = u_proj * vec4(quad.rect.xy + quad.rect.zw * aPos[idx], 0.0, 1.0);
}
