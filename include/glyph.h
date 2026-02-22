#ifdef _WIN32
    #define GLYPH_API __declspec(dllexport)
#else
    #define GLYPH_API __attribute__((visibility("default")))
#endif

#include <stdint.h>

// window.c
GLYPH_API void glyph_window_init(uint32_t width, uint32_t height, const char* name);

//glyph.c
GLYPH_API void glyph_init();
GLYPH_API void glyph_begin_frame();
GLYPH_API void glyph_end_frame();
GLYPH_API int glyph_should_close();
GLYPH_API void glyph_terminate();


