#include <math.h>

#include "glyph.h"

float color[4] = {1.0f, 0.5f, 0.2f, 1.0f};
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

    float yaw_rad = DEG2RAD(*yaw);
    float pitch_rad = DEG2RAD(*pitch);

    // TODO: add some api level helpers here? not sure how worth it tbh.. maybe make forward/rigth return vec3/vec2 and then its easy for the user to multiply
    // abstracting beyond that seems unnecessary, if theyre doing game dev they should know how this basic part of a camera works
    float forward[3] = {
        cosf(pitch_rad) * sinf(yaw_rad),
        sinf(pitch_rad),
        cosf(pitch_rad) * -cosf(yaw_rad),
    };

    float right[2] = {
        cosf(yaw_rad),
        sinf(yaw_rad),
    };

    if (glyph_key_held(GLYPH_KEY_D)) {
        *x += right[0] * speed;
        *z += right[1] * speed;
    }
    if (glyph_key_held(GLYPH_KEY_A)) {
        *x -= right[0] * speed;
        *z -= right[1] * speed;
    }
    if (glyph_key_held(GLYPH_KEY_W)) {
        *x += forward[0] * speed;
        *z += forward[2] * speed;
    }
    if (glyph_key_held(GLYPH_KEY_S)) {
        *x -= forward[0] * speed;
        *z -= forward[2] * speed;
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

    float m1[16];
    float m2[16];
    mat4_identity(m1);
    mat4_identity(m2);
    mat4_translate(m1, 0, 0, 0);
    mat4_translate(m2, 1, 0, 0);
    float x = 0, z = 2, y = 0, yaw = 0, pitch = 0;

    while (!glyph_should_close()) {
        input(&x, &y, &z, &yaw, &pitch);
        glyph_begin_frame();

        glyph_camera_look_at(yaw, pitch);
        glyph_camera_set_pos(x, y, z);

        glyph_draw_quad(m1, color);
        glyph_draw_quad(m2, color);

        glyph_end_frame();
    }

    glyph_terminate();
    return 0;
}
