#version 450 core
#extension GL_ARB_bindless_texture : require

struct QuadData {
    mat4 model;
    vec4 color;
    sampler2D texture;
};

layout (location = 0) in vec3 aPos;
layout (std430, binding = 1) buffer Quads {
    QuadData quads[];
};

flat out int v_quad_idx;
uniform mat4 u_vp;

const vec2 uvs[4] = vec2[4](
    vec2(0.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0),
    vec2(1.0, 0.0)
);
out vec2 v_uv;

void main() {
    int quad_idx = gl_InstanceID;
    v_quad_idx = quad_idx;
    QuadData quad = quads[quad_idx];
    v_uv = uvs[gl_VertexID % 4];

    gl_Position = u_vp * quad.model * vec4(aPos, 1.0);
}
