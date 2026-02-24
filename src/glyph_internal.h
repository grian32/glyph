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

extern float g_proj[16];
extern float g_view[16];
extern GLuint g_vp_loc;

extern float g_ex, g_ey, g_ez, g_cx, g_cy, g_cz;
extern float g_last_x, g_last_y, g_dx, g_dy;

extern int g_mouse_prev[8];
extern int g_mouse_curr[8];

void mat4_zero(float m[16]);
void mat4_perspective(float m[16], float fov, float aspect, float near, float far);
void mat4_mul(float into[16], const float a[16], const float b[16]);
void mat4_look_at(float m[16], float ex, float ey, float ez, float cx, float cy, float cz);

#endif