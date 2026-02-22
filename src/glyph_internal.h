#ifndef GLYPH_GLYPH_INTERNAL_H
#define GLYPH_GLYPH_INTERNAL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern GLFWwindow* g_window;
extern uint32_t g_width, g_height;

void glyph_renderer_init();
GLuint glyph_compile_shader(unsigned char vert_src[], unsigned char frag_src[]);

extern float vertices[];
extern unsigned int indices[];
extern GLuint g_vao, g_vbo, g_ebo, g_shader;

#endif