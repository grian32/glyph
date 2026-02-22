#include <string.h>
#include "glyph.h"

/**
 * layout
 * 0  1  2 3
 * 4  5  6 7
 * 8  9  10 11
 * 12 13 14 15
 * column major == 12/13/14 == xyz rather than 3/7/11 == xyz
 */
void mat4_identity(float m[16]) {
    memset(m, 0, 16 * sizeof(float));
    m[0] = 1;
    m[5] = 1;
    m[10] = 1;
    m[15] = 1;
}
void mat4_translate(float m[16], float x, float y, float z) {
    m[12] = x;
    m[13] = y;
    m[14] = z;
}
