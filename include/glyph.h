#ifdef _WIN32
    #define GLYPH_API __declspec(dllexport)
#else
    #define GLYPH_API __attribute__((visibility("default")))
#endif

GLYPH_API void run();

