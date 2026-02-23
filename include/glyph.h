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
// renderer.c
GLYPH_API void glyph_draw_quad(const float model[16], const float color[4]);

// math.c
GLYPH_API void mat4_identity(float m[16]);
GLYPH_API void mat4_translate(float m[16], float x, float y, float z);

// camera.c
GLYPH_API void glyph_camera_set_pos(float x, float y, float z);
GLYPH_API void glyph_camera_look_at(float yaw, float pitch);

