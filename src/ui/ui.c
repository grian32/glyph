#include <string.h>

#include "../glyph_internal.h"

bool g_ui_init = false;
float g_ui_proj[16];
UIQuadData g_ui_quads[MAX_QUADS];
int g_ui_quad_count = 0;

void glyph_ui_init() {
    g_ui_init = true;
    mat4_ortho(g_ui_proj, 0, g_width, g_height, 0, -1, 1);
}

void glyph_ui_draw_quad(float rect[4], float color[4], uint64_t texture) {
    memcpy(g_ui_quads[g_ui_quad_count].rect, rect, sizeof(float)*4);
    memcpy(g_ui_quads[g_ui_quad_count].color, color, sizeof(float)*4);
    g_ui_quads[g_ui_quad_count++].texture = texture;
}

void glyph_ui_flush() {
    // TODO: disable depth, enable alpha, ui ssbo, ortho uniform, draw, re enable depth, disable alpha
    g_ui_quad_count = 0;
}