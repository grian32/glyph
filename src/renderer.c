#include <math.h>
#include <string.h>

#include "glyph_internal.h"
#include "glyph.h"
#include "shader_frag.h"
#include "shader_vert.h"
#include <glad/glad.h>

float vertices[] = {
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
};

static unsigned int indices[MAX_QUADS * 6];

GLuint g_vao, g_vbo, g_ebo, g_shader;

QuadData g_quads[MAX_QUADS];
int g_quad_count = 0;
GLuint g_ssbo;
GLuint g_vp_loc;

float g_proj[16];
float g_view[16];

void glyph_renderer_init() {
    for (int i = 0; i < MAX_QUADS; i++) {
        indices[i*6 + 0] = 0;
        indices[i*6 + 1] = 1;
        indices[i*6 + 2] = 2;
        indices[i*6 + 3] = 0;
        indices[i*6 + 4] = 2;
        indices[i*6 + 5] = 3;
    }
    mat4_perspective(g_proj, DEG2RAD(70.0f), (float)g_width / (float)g_height, 0.1f, 1000.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCreateVertexArrays(1, &g_vao);
    glCreateBuffers(1, &g_vbo);
    glCreateBuffers(1, &g_ebo);

    glNamedBufferStorage(g_vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(g_ebo, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayVertexBuffer(g_vao, 0, g_vbo, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(g_vao, g_ebo);

    glVertexArrayAttribFormat(g_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_vao, 0, 0);
    glEnableVertexArrayAttrib(g_vao, 0);

    glCreateBuffers(1, &g_ssbo);
    glNamedBufferStorage(g_ssbo, MAX_QUADS * sizeof(QuadData), NULL, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, g_ssbo);

    g_shader = glyph_compile_shader(vert_src, vert_src_len, frag_src, frag_src_len);
    g_vp_loc = glGetUniformLocation(g_shader, "u_vp");
}

void glyph_draw_quad(const GlyphMat4 model, const GlyphRaw4 color, const uint64_t texture) {
    memcpy(g_quads[g_quad_count].model, model, sizeof(float) * 16);
    memcpy(g_quads[g_quad_count].color, color, sizeof(float) * 4);
    g_quads[g_quad_count].texture = texture;
    g_quad_count++;
}