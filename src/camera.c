#include <math.h>

#include "glyph.h"
#include "glyph_internal.h"

float g_ex, g_ey, g_ez, g_cx, g_cy, g_cz;

void glyph_camera_set_pos(float x, float y, float z) {
    g_ex = x, g_ey = y, g_ez = z;
}

void glyph_camera_look_at(float yaw, float pitch) {
    float yaw_rad = DEG2RAD(yaw), pitch_rad = DEG2RAD(pitch);

    g_cx = g_ex + cosf(pitch_rad) * sinf(yaw_rad);
    g_cy = g_ey + sinf(pitch_rad);
    g_cz = g_ez + cosf(pitch_rad) * -cosf(yaw_rad);
}