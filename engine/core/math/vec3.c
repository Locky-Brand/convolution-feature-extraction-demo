#include "vec3.h"

float dot_vec3(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 cross_vec3(vec3 a, vec3 b) {
    return (vec3){a.y * b.z - b.y * a.z, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

vec3 norm_vec3(vec3 a) {
    float l = 1.0f / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (vec3){l * a.x, l * a.y, l * a.z};
}

vec3 sub_vec3(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 add_vec3(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}


float angle_full_vec3(vec3 a, vec3 b, vec3 n) {
    float dot = a.x * b.x + a.y * b.y + a.z * b.z;
    float det = dot_vec3(cross_vec3(a, b), n);
    return atan2(det, dot);
}
float angle_full_vec3x(vec3 a, vec3 b) {
    return angle_full_vec3(a, b, (vec3){1.0f, 0.0f, 0.0f});
}
float angle_full_vec3y(vec3 a, vec3 b) {
    return angle_full_vec3(a, b, (vec3){0.0f, 1.0f, 0.0f});
}
float angle_full_vec3z(vec3 a, vec3 b) {
    return angle_full_vec3(a, b, (vec3){0.0f, 0.0f, 1.0f});
}

vec3 rotate_vec3(vec3 a, vec3 axis, float d) {
    float c = cos(d);
    float cc = 1 - c;
    float s = sin(d);
    return (vec3){
        (c + cc * axis.x * axis.x) * a.x + (cc * axis.x * axis.y - s * axis.z) * a.y + (cc * axis.x * axis.z + s * axis.y) * a.z,
        (cc * axis.x * axis.y - s * axis.z) * a.x + (c + cc * axis.y * axis.y) * a.y + (cc * axis.y * axis.z - s * axis.x) * a.z,
        (cc * axis.x * axis.z - s * axis.y) * a.x + (cc * axis.y * axis.z + s * axis.x) * a.y + (c + cc * axis.z * axis.z) * a.z
    };
}
vec3 rotate_vec3x(vec3 a, float d) {
    return (vec3){a.x * cos(d) + a.z * sin(d), a.y, -a.x * sin(d) + a.z * cos(d)};
}
vec3 rotate_vec3y(vec3 a, float d) {
    return (vec3){a.x * cos(d) + a.z * sin(d), a.y, -a.x * sin(d) + a.z * cos(d)};
}
vec3 rotate_vec3z(vec3 a, float d) {
    return (vec3){a.x * cos(d) + a.z * sin(d), a.y, -a.x * sin(d) + a.z * cos(d)};
}
