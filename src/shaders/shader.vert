#version 450 core

struct QuadData {
    mat4 model;
    vec4 color;
};

layout (location = 0) in vec3 aPos;
layout (std430, binding = 1) buffer Quads {
    QuadData quads[];
};

flat out int v_quad_idx;
uniform mat4 u_vp;

void main() {
    int quad_idx = gl_InstanceID;
    v_quad_idx = quad_idx;
    QuadData quad = quads[quad_idx];

    gl_Position = u_vp * quad.model * vec4(aPos, 1.0);
}
