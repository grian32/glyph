#include "glyph_internal.h"
#include "shader_frag.h"
#include "shader_vert.h"
#include <glad/glad.h>

float vertices[] = {
    -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
 -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

GLuint g_vao, g_vbo, g_ebo, g_shader;

void glyph_renderer_init() {
    glCreateVertexArrays(1, &g_vao);
    glCreateBuffers(1, &g_vbo);
    glCreateBuffers(1, &g_ebo);

    glNamedBufferStorage(g_vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(g_ebo, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayVertexBuffer(g_vao, 0, g_vbo, 0, 5 * sizeof(float));
    glVertexArrayElementBuffer(g_vao, g_ebo);

    glVertexArrayAttribFormat(g_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_vao, 0, 0);
    glEnableVertexArrayAttrib(g_vao, 0);

    glVertexArrayAttribFormat(g_vao, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexArrayAttribBinding(g_vao, 1, 0);
    glEnableVertexArrayAttrib(g_vao, 1);

    g_shader = glyph_compile_shader(vert_src, frag_src);
}
