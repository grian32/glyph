#include <math.h>
#include <stdio.h>
#include <string.h>
#include "glyph.h"

void mat4_zero(float m[16]) {
    memset(m, 0, 16 * sizeof(float));
}

/**
 * layout
 * 0  1  2 3
 * 4  5  6 7
 * 8  9  10 11
 * 12 13 14 15
 * column major == 12/13/14 == xyz rather than 3/7/11 == xyz
 */
void mat4_identity(float m[16]) {
    mat4_zero(m);
    m[0] = 1;
    m[5] = 1;
    m[10] = 1;
    m[15] = 1;
}

void mat4_translate(float m[16], float x, float y, float z) {
    m[12] += m[0] * x + m[4] * y + m[8] * z;
    m[13] += m[1] * x + m[5] * y + m[9] * z;
    m[14] += m[2] * x + m[6] * y + m[10] * z;
}

void mat4_scale(float m[16], float s) {
    m[0] *= s; m[1] *= s; m[2] *= s; m[3] *= s;
    m[4] *= s; m[5] *= s; m[6] *= s; m[7] *= s;
    m[8] *= s; m[9] *= s; m[10] *= s; m[11] *= s;
}

void mat4_rotate_x(float m[16], float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    float t1, t2;

    t1 = m[4];  t2 = m[8];  m[4]  = t1*c + t2*s;  m[8]  = -t1*s + t2*c;
    t1 = m[5];  t2 = m[9];  m[5]  = t1*c + t2*s;  m[9]  = -t1*s + t2*c;
    t1 = m[6];  t2 = m[10]; m[6]  = t1*c + t2*s;  m[10] = -t1*s + t2*c;
    t1 = m[7];  t2 = m[11]; m[7]  = t1*c + t2*s;  m[11] = -t1*s + t2*c;
}

void mat4_rotate_y(float m[16], float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    float t1, t2;

    t1 = m[0];  t2 = m[8];  m[0]  = t1*c - t2*s;  m[8]  = t1*s + t2*c;
    t1 = m[1];  t2 = m[9];  m[1]  = t1*c - t2*s;  m[9]  = t1*s + t2*c;
    t1 = m[2];  t2 = m[10]; m[2]  = t1*c - t2*s;  m[10] = t1*s + t2*c;
    t1 = m[3];  t2 = m[11]; m[3]  = t1*c - t2*s;  m[11] = t1*s + t2*c;
}

void mat4_rotate_z(float m[16], float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    float t1, t2;

    t1 = m[0];  t2 = m[4];  m[0]  = t1*c + t2*s;  m[4]  = -t1*s + t2*c;
    t1 = m[1];  t2 = m[5];  m[1]  = t1*c + t2*s;  m[5]  = -t1*s + t2*c;
    t1 = m[2];  t2 = m[6];  m[2]  = t1*c + t2*s;  m[6]  = -t1*s + t2*c;
    t1 = m[3];  t2 = m[7];  m[3]  = t1*c + t2*s;  m[7]  = -t1*s + t2*c;
}

void mat4_perspective(float m[16], float fov, float aspect, float near, float far) {
    mat4_zero(m);
    float t = tanf(fov / 2.0f);
    m[0] = 1.0f / (aspect * t);
    m[5] = 1.0f / t;
    m[10] = -(far+near) / (far - near);
    m[11] = -1.0f;
    m[14] = -(2.0f * far * near) / (far - near);
}

void mat4_look_at(float m[16], float ex, float ey, float ez, float cx, float cy, float cz) {
    float ux = 0, uz = 0, uy = 1;
    float fx = cx - ex, fy = cy - ey, fz = cz - ez;
    float fl = sqrtf(fx*fx+fy*fy+fz*fz);
    fx /= fl; fy /= fl, fz /= fl;

    float rx = fy*uz - fz*uy;
    float ry = fz*ux - fx*uz;
    float rz = fx*uy - fy*ux;
    float rl = sqrtf(rx*rx + ry*ry + rz*rz);
    rx/=rl; ry/=rl; rz/=rl;

    float tux = ry*fz - rz*fy;
    float tuy = rz*fx - rx*fz;
    float tuz = rx*fy - ry*fx;

    mat4_zero(m);
    m[0]  = rx;  m[4]  = ry;  m[8]  = rz;
    m[1]  = tux; m[5]  = tuy; m[9]  = tuz;
    m[2]  = -fx; m[6]  = -fy; m[10] = -fz;
    m[12] = -(rx*ex + ry*ey + rz*ez);
    m[13] = -(tux*ex + tuy*ey + tuz*ez);
    m[14] = fx*ex + fy*ey + fz*ez;
    m[15] = 1.0f;
}

void mat4_mul(float into[16], const float a[16], const float b[16]) {
    float tmp[16] = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                tmp[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
            }
        }
    }

    memcpy(into, tmp, sizeof(float) * 16);
}

void glyph_apply_transform(GlyphMat4 mat, const GlyphTransform* t) {
    mat4_identity(mat);
    glyph_apply_stransform(mat, t);
}
void glyph_apply_stransform(GlyphMat4 mat, const GlyphTransform* t) {
    mat4_scale(mat, t->scale);
    // makes no sense imo how it applies rotations, just swapping them out
    mat4_rotate_z(mat, DEG2RAD(t->rot[0]));
    mat4_rotate_y(mat, DEG2RAD(t->rot[1]));
    mat4_rotate_x(mat, DEG2RAD(t->rot[2]));
    mat4_translate(mat, t->pos[0], t->pos[1], t->pos[2]);
}

void glyph_apply_color(GlyphRaw4 out, const GlyphColor* c) {
    out[0] = (float)c->r / 255.0f;
    out[1] = (float)c->g / 255.0f;
    out[2] = (float)c->b / 255.0f;
    out[3] = (float)c->a / 255.0f;
}

void glyph_calc_forward(float yaw, float pitch, GlyphVec3* out) {
    float yaw_rad = DEG2RAD(yaw), pitch_rad = DEG2RAD(pitch);
    out->x = cosf(pitch_rad) * sinf(yaw_rad);
    out->y = sinf(pitch_rad);
    out->z = cosf(pitch_rad) * -cosf(yaw_rad);
}

void glyph_calc_right(float yaw, GlyphVec3* out) {
    float yaw_rad = DEG2RAD(yaw);
    out->y = 0.0f;
    out->x = cosf(yaw_rad);
    out->z = sinf(yaw_rad);
}