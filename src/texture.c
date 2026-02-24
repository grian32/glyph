#include <stdio.h>
#include <stdlib.h>
#include <jxl/decode.h>

#include "glyph.h"
#include "glad/glad.h"

uint64_t glyph_load_texture_from_file(const char* jxl_path) {
    FILE* f = fopen(jxl_path, "rb");
    if (!f) {
        printf("glyph::failed_open_file::%s", jxl_path);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);
    uint8_t* data = malloc(size);
    fread(data, 1, size, f);
    fclose(f);

    uint64_t handle = glyph_load_texture(data, size);
    free(data);
    return handle;
}

uint64_t glyph_load_texture(const uint8_t* data, const size_t size) {
    JxlDecoder* dec = JxlDecoderCreate(NULL);
    JxlDecoderSubscribeEvents(dec, JXL_DEC_BASIC_INFO | JXL_DEC_FULL_IMAGE);
    JxlDecoderSetInput(dec, data, size);
    JxlDecoderCloseInput(dec);

    JxlPixelFormat fmt = { 4, JXL_TYPE_UINT8, JXL_NATIVE_ENDIAN, 0};
    uint8_t* pixels = NULL;
    JxlDecoderStatus s;

    uint32_t width = 0, height = 0;

    while ((s = JxlDecoderProcessInput(dec)) != JXL_DEC_SUCCESS) {
        if (s == JXL_DEC_BASIC_INFO) {
            JxlBasicInfo info;
            JxlDecoderGetBasicInfo(dec, &info);
            width = info.xsize;
            height = info.ysize;
        } else if (s == JXL_DEC_NEED_IMAGE_OUT_BUFFER) {
            size_t buf_size;
            JxlDecoderImageOutBufferSize(dec, &fmt, &buf_size);
            pixels = malloc(buf_size);
            JxlDecoderSetImageOutBuffer(dec, &fmt, pixels, buf_size);
        } else if (s == JXL_DEC_ERROR) {
            printf("glyph::failed_jxl_decode");
            if (pixels) {
                free(pixels);
                pixels = NULL;
            }
            JxlDecoderDestroy(dec);
            return 0;
        }
    }

    JxlDecoderDestroy(dec);

    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);
    glTextureStorage2D(tex, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(tex, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint64_t handle = glGetTextureHandleARB(tex);
    // TODO: add unload texture utility
    glMakeTextureHandleResidentARB(handle);

    if (pixels) {
        free(pixels);
    }
    return handle;
}
