#include <string.h>
#include <glad/glad.h>

#include "../glyph_internal.h"
#include "glyph.h"
#include "ui_shader_vert.h"
#include "ui_shader_frag.h"

bool g_ui_init = false;
float g_ui_proj[16];
UIQuadData g_ui_quads[MAX_QUADS];
int g_ui_quad_count = 0;
GLuint g_ui_shader, g_ui_vao, g_ui_ssbo, g_ui_proj_loc;

void glyph_ui_init() {
    g_ui_init = true;
    mat4_ortho(g_ui_proj, 0, (float)g_width, (float)g_height, 0, -1, 1);

    g_ui_shader = glyph_compile_shader(ui_vert_src, ui_vert_src_len, ui_frag_src, ui_frag_src_len);

    glCreateVertexArrays(1, &g_ui_vao);

    glCreateBuffers(1, &g_ui_ssbo);
    glNamedBufferStorage(g_ui_ssbo, MAX_QUADS * sizeof(UIQuadData), NULL, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, g_ssbo);

    g_ui_proj_loc = glGetUniformLocation(g_ui_shader, "u_proj");
}

void glyph_ui_draw_quad(float rect[4], float color[4], uint64_t texture) {
    memcpy(g_ui_quads[g_ui_quad_count].rect, rect, sizeof(float)*4);
    memcpy(g_ui_quads[g_ui_quad_count].color, color, sizeof(float)*4);
    g_ui_quads[g_ui_quad_count++].texture = texture;
}

void glyph_ui_flush() {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glEnable(GL_ALPHA_TEST);

    glNamedBufferSubData(g_ui_ssbo, 0, g_ui_quad_count * sizeof(UIQuadData), g_ui_quads);

    glUseProgram(g_ui_shader);
    glUniformMatrix4fv(g_ui_proj_loc, 1, GL_FALSE, g_ui_proj);
    glBindVertexArray(g_ui_vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_ui_quad_count);

    g_ui_quad_count = 0;
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_ALPHA_TEST);
}