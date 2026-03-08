#include "glyph.h"
#include "glyph_internal.h"

int glyph_key_held(int key) {
    return glfwGetKey(g_window, key) == GLFW_PRESS;
}

int glyph_mouse_pressed(int button) {
    return g_mouse_curr[button] == GLFW_PRESS && g_mouse_prev[button] == GLFW_RELEASE;
}

void glyph_mouse_delta(float *dx, float *dy) {
    *dx = g_dx, *dy = g_dy;
}

void glyph_disable_cursor() {
    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void glyph_enable_cursor() {
    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
