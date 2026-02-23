#include <stdio.h>
#include "glyph.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "glyph_internal.h"

float g_last_x = 0, g_last_y = 0, g_dx = 0, g_dy = 0;

int g_mouse_prev[8] = {0};
int g_mouse_curr[8] = {0};

void glyph_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("failed to load gl\n");
        exit(1);
    }
    glyph_renderer_init();
}

float g_vp[16];

void glyph_begin_frame() {
    double x, y;
    glfwGetCursorPos(g_window, &x, &y);
    g_dx = (float)x - g_last_x;
    g_dy = (float)y - g_last_y;
    g_last_x = (float)x;
    g_last_y = (float)y;

    for (int i = 0; i < 8; i++) {
        g_mouse_prev[i] = g_mouse_curr[i];
        g_mouse_curr[i] = glfwGetMouseButton(g_window, i);
    }

    mat4_zero(g_vp);
    mat4_look_at(g_view, g_ex, g_ey, g_ez, g_cx, g_cy, g_cz);
    mat4_mul(g_vp, g_proj, g_view);

    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glyph_end_frame() {
    glNamedBufferSubData(g_ssbo, 0, g_quad_count * sizeof(QuadData), g_quads);

    glUseProgram(g_shader);
    glUniformMatrix4fv(g_vp_loc, 1, GL_FALSE, g_vp);
    glBindVertexArray(g_vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, g_quad_count);
    glfwSwapBuffers(g_window);

    g_quad_count = 0;
}

int glyph_should_close() {
    return glfwWindowShouldClose(g_window);
}

void glyph_terminate() {
    glfwTerminate();
}
