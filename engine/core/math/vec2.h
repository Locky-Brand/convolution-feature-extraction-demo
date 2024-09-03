#ifndef VEC2_H
#define VEC2_H

#include <math.h>

typedef struct{
  float x, y;
} vec2;

typedef struct{
  int x, y;
} vec2i;

float angle_full_vec2(vec2 a, vec2 b);

#endif
