#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct {
  int x, y, z;
} vec3i;

typedef struct {
  float x, y, z;
} vec3;

typedef struct {
  vec3 a;
  vec3 b;
} vec3_pair;

float dot_vec3(vec3 a, vec3 b);

vec3 cross_vec3(vec3 a, vec3 b);

vec3 norm_vec3(vec3 a);

vec3 sub_vec3(vec3 a, vec3 b);

vec3 add_vec3(vec3 a, vec3 b);

float angle_full_vec3(vec3 a, vec3 b, vec3 n);
float angle_full_vec3x(vec3 a, vec3 b);
float angle_full_vec3y(vec3 a, vec3 b);
float angle_full_vec3z(vec3 a, vec3 b);

vec3 rotate_vec3(vec3 a, vec3 axis, float d);
vec3 rotate_vec3x(vec3 a, float d);
vec3 rotate_vec3y(vec3 a, float d);
vec3 rotate_vec3z(vec3 a, float d);

#endif
