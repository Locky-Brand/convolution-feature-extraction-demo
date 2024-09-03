#ifndef MAT4_H
#define MAT4_H

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "utils.h"

typedef struct {
  float v[16];
} mat4;

void dbg_print_mat4(mat4 M);

void mul_mat4(mat4* R, mat4 A, mat4 B); // R = A x B
void mul_mat4_3(mat4* R, mat4 A, mat4 B, mat4 C); // R = A x B x C

void zeroes(mat4* M);

void identity(mat4* M);

void scale_mat4z(mat4* M, float sx, float sy, float sz); // A = scale matrix
void scale_mat4(mat4* M, float sx, float sy, float sz); // A = scale matrix

void translate_mat4z(mat4* M, float tx, float ty, float tz); // A = translator matrix
void translate_mat4(mat4* M, float tx, float ty, float tz); // A = translator matrix

void rotate_mat4(mat4* M, float a, vec3 axis); // A = rotator matrix

vec3 mul_mat4_vec3(mat4 M, vec3 v);
vec4 mul_mat4_vec4(mat4 M, vec4 v);

void projection_mat4(mat4* M, float aspect, float fov, float far, float near); // 3D perspective projection

vec3_pair perspective_lookat(mat4* M, vec3 pos, vec3 targ); // 3D perspective look at matrix, for camera3D

#endif
