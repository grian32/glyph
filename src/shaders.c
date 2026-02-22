#include <stdio.h>
#include <stdlib.h>

#include "glyph_internal.h"
#include <glad/glad.h>

void checkShaderError(GLuint shader, bool vert) {
    GLint success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("glyph");
        if (vert) {
            printf("::vert");
        } else {
            printf("::frag");
        }
        printf("::shader_compilation_error::%s\n", log);
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

GLuint glyph_compile_shader(unsigned char vert_src[], unsigned int vert_len, unsigned char frag_src[], unsigned int frag_len) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    const char* casted_vert_src = (const char*) vert_src;
    const GLint vert_length = (GLint) vert_len;
    glShaderSource(vert, 1, &casted_vert_src, &vert_length);
    glCompileShader(vert);

    checkShaderError(vert, true);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    const char* casted_frag_src = (const char*) frag_src;
    const GLint frag_length = (GLint) frag_len;
    glShaderSource(frag, 1, &casted_frag_src, &frag_length);
    glCompileShader(frag);

    checkShaderError(frag, false);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    checkProgramError(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}
