#ifndef GLYPH_GLYPH_INTERNAL_H
#define GLYPH_GLYPH_INTERNAL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_QUADS 10000

extern GLFWwindow* g_window;
extern uint32_t g_width, g_height;

void glyph_renderer_init();
GLuint glyph_compile_shader(unsigned char vert_src[], unsigned int vert_len, unsigned char frag_src[], unsigned int frag_len);

extern float vertices[];
extern GLuint g_vao, g_vbo, g_ebo, g_shader;

typedef struct {
    float model[16];
    float color[4];
} QuadData;

extern QuadData g_quads[MAX_QUADS];
extern int g_quad_count;
extern GLuint g_ssbo;

#endif