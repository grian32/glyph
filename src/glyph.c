#include <stdio.h>
#include "glyph.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "glyph_internal.h"

void glyph_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("failed to load gl\n");
        exit(1);
    }
    glyph_renderer_init();
}

float g_vp[16];

void glyph_begin_frame() {
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
