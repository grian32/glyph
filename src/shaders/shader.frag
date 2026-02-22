#version 450 core

struct QuadData {
    mat4 model;
    vec4 color;
};

layout(std430, binding = 1) buffer Quads {
    QuadData quads[];
};

out vec4 FragColor;
flat in int v_quad_idx;

void main() {
    FragColor = quads[v_quad_idx].color;
}