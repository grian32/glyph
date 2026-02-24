#version 450 core
#extension GL_ARB_bindless_texture : require

struct QuadData {
    mat4 model;
    vec4 color;
    sampler2D texture;
};

layout(std430, binding = 1) buffer Quads {
    QuadData quads[];
};

out vec4 FragColor;
flat in int v_quad_idx;
in vec2 v_uv;

void main() {
    QuadData q = quads[v_quad_idx];
    if (uvec2(q.texture) != uvec2(0)) {
        FragColor = texture(q.texture, v_uv) * q.color;
    } else {
        FragColor = q.color;
    }
}