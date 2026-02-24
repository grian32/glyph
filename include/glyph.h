#ifdef _WIN32
    #define GLYPH_API __declspec(dllexport)
#else
    #define GLYPH_API __attribute__((visibility("default")))
#endif

#include <stdint.h>
#include <stddef.h>

#define DEG2RAD(x) ((x) * (3.14159265358979323846 / 180.0f))

typedef struct {
    float x;
    float y;
} GlyphVec2;

typedef struct {
    float x;
    float y;
    float z;
} GlyphVec3;

typedef float GlyphMat4[16];
typedef float GlyphRaw4[4];

typedef struct {
    float pos[3];
    float rot[3];
    float scale;
} GlyphTransform;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} GlyphColor;

// window.c
GLYPH_API void glyph_window_init(uint32_t width, uint32_t height, const char* name);

//glyph.c
GLYPH_API void glyph_init();
GLYPH_API void glyph_begin_frame();
GLYPH_API void glyph_end_frame();
GLYPH_API int glyph_should_close();
GLYPH_API void glyph_terminate();
// renderer.c
GLYPH_API void glyph_draw_quad(const float model[16], const float color[4], uint64_t texture);

// math.c
GLYPH_API void glyph_calc_forward(float yaw, float pitch, GlyphVec3* out);
GLYPH_API void glyph_calc_right(float yaw, GlyphVec3* out);
// overrides mat with identity
GLYPH_API void glyph_apply_transform(GlyphMat4 mat, const GlyphTransform* t);
// does not overide mat with identity allowing for sequential transforms
GLYPH_API void glyph_apply_stransform(GlyphMat4 mat, const GlyphTransform* t);
GLYPH_API void glyph_apply_color(GlyphRaw4 out, const GlyphColor* c);

// camera.c
GLYPH_API void glyph_camera_set_pos(float x, float y, float z);
GLYPH_API void glyph_camera_set_rot(float yaw, float pitch);

// input.c
GLYPH_API int glyph_key_held(int key);
GLYPH_API void glyph_mouse_delta(float *dx, float *dy);
GLYPH_API void glyph_disable_cursor();
GLYPH_API void glyph_enable_cursor();
GLYPH_API int glyph_mouse_pressed(int button);

// texture.c
GLYPH_API uint64_t glyph_load_texture(const uint8_t* data, size_t size);
GLYPH_API uint64_t glyph_load_texture_from_file(const char* jxl_path);

#define GLYPH_KEY_UNKNOWN            (-1)
#define GLYPH_KEY_SPACE              32
#define GLYPH_KEY_APOSTROPHE         39
#define GLYPH_KEY_COMMA              44
#define GLYPH_KEY_MINUS              45
#define GLYPH_KEY_PERIOD             46
#define GLYPH_KEY_SLASH              47
#define GLYPH_KEY_0                  48
#define GLYPH_KEY_1                  49
#define GLYPH_KEY_2                  50
#define GLYPH_KEY_3                  51
#define GLYPH_KEY_4                  52
#define GLYPH_KEY_5                  53
#define GLYPH_KEY_6                  54
#define GLYPH_KEY_7                  55
#define GLYPH_KEY_8                  56
#define GLYPH_KEY_9                  57
#define GLYPH_KEY_SEMICOLON          59
#define GLYPH_KEY_EQUAL              61
#define GLYPH_KEY_A                  65
#define GLYPH_KEY_B                  66
#define GLYPH_KEY_C                  67
#define GLYPH_KEY_D                  68
#define GLYPH_KEY_E                  69
#define GLYPH_KEY_F                  70
#define GLYPH_KEY_G                  71
#define GLYPH_KEY_H                  72
#define GLYPH_KEY_I                  73
#define GLYPH_KEY_J                  74
#define GLYPH_KEY_K                  75
#define GLYPH_KEY_L                  76
#define GLYPH_KEY_M                  77
#define GLYPH_KEY_N                  78
#define GLYPH_KEY_O                  79
#define GLYPH_KEY_P                  80
#define GLYPH_KEY_Q                  81
#define GLYPH_KEY_R                  82
#define GLYPH_KEY_S                  83
#define GLYPH_KEY_T                  84
#define GLYPH_KEY_U                  85
#define GLYPH_KEY_V                  86
#define GLYPH_KEY_W                  87
#define GLYPH_KEY_X                  88
#define GLYPH_KEY_Y                  89
#define GLYPH_KEY_Z                  90
#define GLYPH_KEY_LEFT_BRACKET       91
#define GLYPH_KEY_BACKSLASH          92
#define GLYPH_KEY_RIGHT_BRACKET      93
#define GLYPH_KEY_GRAVE_ACCENT       96
#define GLYPH_KEY_WORLD_1            161
#define GLYPH_KEY_WORLD_2            162
#define GLYPH_KEY_ESCAPE             256
#define GLYPH_KEY_ENTER              257
#define GLYPH_KEY_TAB                258
#define GLYPH_KEY_BACKSPACE          259
#define GLYPH_KEY_INSERT             260
#define GLYPH_KEY_DELETE             261
#define GLYPH_KEY_RIGHT              262
#define GLYPH_KEY_LEFT               263
#define GLYPH_KEY_DOWN               264
#define GLYPH_KEY_UP                 265
#define GLYPH_KEY_PAGE_UP            266
#define GLYPH_KEY_PAGE_DOWN          267
#define GLYPH_KEY_HOME               268
#define GLYPH_KEY_END                269
#define GLYPH_KEY_CAPS_LOCK          280
#define GLYPH_KEY_SCROLL_LOCK        281
#define GLYPH_KEY_NUM_LOCK           282
#define GLYPH_KEY_PRINT_SCREEN       283
#define GLYPH_KEY_PAUSE              284
#define GLYPH_KEY_F1                 290
#define GLYPH_KEY_F2                 291
#define GLYPH_KEY_F3                 292
#define GLYPH_KEY_F4                 293
#define GLYPH_KEY_F5                 294
#define GLYPH_KEY_F6                 295
#define GLYPH_KEY_F7                 296
#define GLYPH_KEY_F8                 297
#define GLYPH_KEY_F9                 298
#define GLYPH_KEY_F10                299
#define GLYPH_KEY_F11                300
#define GLYPH_KEY_F12                301
#define GLYPH_KEY_F13                302
#define GLYPH_KEY_F14                303
#define GLYPH_KEY_F15                304
#define GLYPH_KEY_F16                305
#define GLYPH_KEY_F17                306
#define GLYPH_KEY_F18                307
#define GLYPH_KEY_F19                308
#define GLYPH_KEY_F20                309
#define GLYPH_KEY_F21                310
#define GLYPH_KEY_F22                311
#define GLYPH_KEY_F23                312
#define GLYPH_KEY_F24                313
#define GLYPH_KEY_F25                314
#define GLYPH_KEY_KP_0               320
#define GLYPH_KEY_KP_1               321
#define GLYPH_KEY_KP_2               322
#define GLYPH_KEY_KP_3               323
#define GLYPH_KEY_KP_4               324
#define GLYPH_KEY_KP_5               325
#define GLYPH_KEY_KP_6               326
#define GLYPH_KEY_KP_7               327
#define GLYPH_KEY_KP_8               328
#define GLYPH_KEY_KP_9               329
#define GLYPH_KEY_KP_DECIMAL         330
#define GLYPH_KEY_KP_DIVIDE          331
#define GLYPH_KEY_KP_MULTIPLY        332
#define GLYPH_KEY_KP_SUBTRACT        333
#define GLYPH_KEY_KP_ADD             334
#define GLYPH_KEY_KP_ENTER           335
#define GLYPH_KEY_KP_EQUAL           336
#define GLYPH_KEY_LEFT_SHIFT         340
#define GLYPH_KEY_LEFT_CONTROL       341
#define GLYPH_KEY_LEFT_ALT           342
#define GLYPH_KEY_LEFT_SUPER         343
#define GLYPH_KEY_RIGHT_SHIFT        344
#define GLYPH_KEY_RIGHT_CONTROL      345
#define GLYPH_KEY_RIGHT_ALT          346
#define GLYPH_KEY_RIGHT_SUPER        347
#define GLYPH_KEY_MENU               348

#define GLYPH_MOUSE_BUTTON_1         0
#define GLYPH_MOUSE_BUTTON_2         1
#define GLYPH_MOUSE_BUTTON_3         2
#define GLYPH_MOUSE_BUTTON_4         3
#define GLYPH_MOUSE_BUTTON_5         4
#define GLYPH_MOUSE_BUTTON_6         5
#define GLYPH_MOUSE_BUTTON_7         6
#define GLYPH_MOUSE_BUTTON_8         7
#define GLYPH_MOUSE_BUTTON_LAST      GLYPH_MOUSE_BUTTON_8
#define GLYPH_MOUSE_BUTTON_LEFT      GLYPH_MOUSE_BUTTON_1
#define GLYPH_MOUSE_BUTTON_RIGHT     GLYPH_MOUSE_BUTTON_2
#define GLYPH_MOUSE_BUTTON_MIDDLE    GLYPH_MOUSE_BUTTON_3
#define GLYPH_MOUSE_PASSTHROUGH      0x0002000D