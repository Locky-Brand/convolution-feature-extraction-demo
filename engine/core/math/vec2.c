#include "vec2.h"

float angle_full_vec2(vec2 a, vec2 b) {
    float dot = a.x * b.x + a.y * b.y;
    float det = a.x * b.y - a.y * b.x;
    return atan2(det, dot);
}