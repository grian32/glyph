#include <stdint.h>
#include "glyph_internal.h"
#include "glyph.h"

GLFWwindow* g_window;
uint32_t g_width, g_height;

void glyph_window_init(uint32_t width, uint32_t height, const char *name) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_window = glfwCreateWindow(width, height, name, NULL, NULL);
    g_width = width;
    g_height = height;

    glfwMakeContextCurrent(g_window);
}
