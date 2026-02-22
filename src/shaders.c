#include <stdio.h>
#include <stdlib.h>

#include "glyph_internal.h"
#include <glad/glad.h>

void checkShaderError(GLuint shader) {
    GLint success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("glyph::shader_compilation_error::%s\n", log);
        exit(1);
    }
}

void checkProgramError(GLuint program) {
    GLint success;
    char log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, log);
        printf("glyph::shader_linking_error::%s\n", log);
        exit(1);
    }
}

GLuint glyph_compile_shader(unsigned char vert_src[], unsigned char frag_src[]) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    const char* casted_vert_src = (const char*) vert_src;
    glShaderSource(vert, 1, &casted_vert_src, NULL);
    glCompileShader(vert);

    checkShaderError(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    const char* casted_frag_src = (const char*) frag_src;
    glShaderSource(frag, 1, &casted_frag_src, NULL);
    glCompileShader(frag);

    checkShaderError(frag);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    checkProgramError(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}
