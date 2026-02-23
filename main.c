#include "glyph.h"

float color[4] = {1.0f, 0.5f, 0.2f, 1.0f};

int main() {
    glyph_window_init(800, 600 , "glyph demo");
    glyph_init();

    float m1[16];
    float m2[16];
    mat4_identity(m1);
    mat4_identity(m2);
    mat4_translate(m1, 0, 0, 0);
    mat4_translate(m2, 1, 0, 0);

    while (!glyph_should_close()) {
        glyph_begin_frame();

        glyph_camera_set_pos(0, 0, 2);
        glyph_camera_look_at(5, 0);

        glyph_draw_quad(m1, color);
        glyph_draw_quad(m2, color);

        glyph_end_frame();
    }

    glyph_terminate();
    return 0;
}
