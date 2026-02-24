#include <math.h>
#include <stdio.h>

#include "glyph.h"

float sensitivity = 0.07f;
float speed = 0.01f;
bool moveCam = true;

void input(float* x, float* y, float* z, float* yaw, float* pitch) {
    if (moveCam) {
        float dx, dy;
        glyph_mouse_delta(&dx, &dy);

        *yaw += dx * sensitivity;
        *pitch += -dy * sensitivity;
        *yaw = fmodf(*yaw, 360.0f);
        if (*pitch > 89.0f) {
            *pitch = 89.0f;
        } else if (*pitch < -89.0f) {
            *pitch = -89.0f;
        }
    }

    GlyphVec3 forward;
    GlyphVec3 right;
    glyph_calc_forward(*yaw, *pitch, &forward);
    glyph_calc_right(*yaw, &right);

    if (glyph_key_held(GLYPH_KEY_D)) {
        *x += right.x * speed;
        *z += right.z * speed;
    }
    if (glyph_key_held(GLYPH_KEY_A)) {
        *x -= right.x * speed;
        *z -= right.z * speed;
    }
    if (glyph_key_held(GLYPH_KEY_W)) {
        *x += forward.x * speed;
        *z += forward.z * speed;
    }
    if (glyph_key_held(GLYPH_KEY_S)) {
        *x -= forward.x * speed;
        *z -= forward.z * speed;
    }
    if (glyph_key_held(GLYPH_KEY_LEFT_SHIFT)) {
        *y -= speed;
    }
    if (glyph_key_held(GLYPH_KEY_SPACE)) {
        *y += speed;
    }
    if (glyph_key_held(GLYPH_KEY_ESCAPE)) {
        moveCam = false;
        glyph_enable_cursor();
    }
    if (glyph_mouse_pressed(GLYPH_MOUSE_BUTTON_LEFT)) {
        moveCam = true;
        glyph_disable_cursor();
    }

}

int main() {
    glyph_window_init(800, 600 , "glyph demo");
    glyph_init();
    glyph_disable_cursor();

    GlyphRaw4 color;
    GlyphColor c = { .r = 191, .g = 189, .b = 45, .a = 255 };
    glyph_apply_color(color, &c);

    GlyphMat4 m1;
    GlyphMat4 m2;
    GlyphMat4 m3;
    const GlyphTransform t = { .pos = { 0.5f, -0.5f, 0.0f}, .rot = { -50, 0, 0}, .scale = 0.5f};
    const GlyphTransform t2 = { .pos = { 1, 0, 0 }, .rot = { 0, 0, 0 }, .scale = 1};
    const GlyphTransform t3 = { .pos = { 1, -0.5f, -0.5f }, .rot = { -90, 0, 0}, .scale = 1};
    glyph_apply_transform(m1, &t);
    glyph_apply_transform(m2, &t2);
    glyph_apply_transform(m3, &t3);
    float x = 0, z = 2, y = 0, yaw = 0, pitch = 0;

    while (!glyph_should_close()) {
        input(&x, &y, &z, &yaw, &pitch);
        glyph_begin_frame();

        glyph_camera_set_rot(yaw, pitch);
        glyph_camera_set_pos(x, y, z);

        glyph_draw_quad(m1, color);
        glyph_draw_quad(m2, color);
        glyph_draw_quad(m3, color);

        glyph_end_frame();
    }

    glyph_terminate();
    return 0;
}
