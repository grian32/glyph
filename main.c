#include "glyph.h" 

int main() {
    glyph_window_init(800, 600 , "glyph demo");
    glyph_init();

    while (!glyph_should_close()) {
        glyph_begin_frame();
        glyph_end_frame();
    }

    glyph_terminate();
    return 0;
}
