#include <math.h>
#include <string.h>

#include "../glyph_internal.h"
#include "glyph.h"
#include "shader_frag.h"
#include "shader_vert.h"
#include <glad/glad.h>

GLuint g_vao, g_shader;

QuadData g_quads[MAX_QUADS];
int g_quad_count = 0;
GLuint g_ssbo;
GLuint g_vp_loc;

float g_proj[16];
float g_view[16];

void glyph_renderer_init() {
    mat4_perspective(g_proj, DEG2RAD(70.0f), (float)g_width / (float)g_height, 0.1f, 1000.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCreateVertexArrays(1, &g_vao);

    glCreateBuffers(1, &g_ssbo);
    glNamedBufferStorage(g_ssbo, MAX_QUADS * sizeof(QuadData), NULL, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, g_ssbo);

    g_shader = glyph_compile_shader(vert_src, vert_src_len, frag_src, frag_src_len);
    g_vp_loc = glGetUniformLocation(g_shader, "u_vp");
}

void glyph_draw_quad(const GlyphMat4 model, const GlyphRaw4 color, const uint64_t texture) {
    memcpy(g_quads[g_quad_count].model, model, sizeof(float) * 16);
    memcpy(g_quads[g_quad_count].color, color, sizeof(float) * 4);
    g_quads[g_quad_count].texture = texture;
    g_quad_count++;
}