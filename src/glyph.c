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

void glyph_begin_frame() {
    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glyph_end_frame() {
    glUseProgram(g_shader);
    glBindVertexArray(g_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(g_window);
}

int glyph_should_close() {
    return glfwWindowShouldClose(g_window);
}

void glyph_terminate() {
    glfwTerminate();
}
