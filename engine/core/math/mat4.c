#include "mat4.h"

void dbg_print_mat4(mat4 M) {
  printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", M.v[0], M.v[1], M.v[2], M.v[3], M.v[4], M.v[5], M.v[6], M.v[7], M.v[8], M.v[9], M.v[10], M.v[11], M.v[12], M.v[13], M.v[14], M.v[15]);
}

void mul_mat4(mat4* R, mat4 A, mat4 B) { // R = A x B
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      for (int n = 0; n < 4; n++) {
        R->v[m * 4  + n] += A.v[m * 4 + k] * B.v[k * 4 + n];
      }
    }
  }
}

void mul_mat4_3(mat4* R, mat4 A, mat4 B, mat4 C) { // R = A x B x C
  mat4 tmp;
  zeroes(&tmp);
  mul_mat4(&tmp, A, B);
  mul_mat4(R, tmp, C);
}

void zeroes(mat4* M) {
  memset(M->v, 0.0f, 16 * sizeof(float));
}

vec3 mul_mat4_vec3(mat4 M, vec3 v) {
  return (vec3){
    M.v[0] * v.x + M.v[1] * v.y + M.v[2] * v.z + M.v[3],
    M.v[4] * v.x + M.v[5] * v.y + M.v[6] * v.z + M.v[7],
    M.v[8] * v.x + M.v[9] * v.y + M.v[10] * v.z + M.v[11]
  };
}

vec4 mul_mat4_vec4(mat4 M, vec4 v) {
  return (vec4){
    M.v[0] * v.x + M.v[1] * v.y + M.v[2] * v.z + M.v[3],
    M.v[4] * v.x + M.v[5] * v.y + M.v[6] * v.z + M.v[7],
    M.v[8] * v.x + M.v[9] * v.y + M.v[10] * v.z + M.v[11],
    M.v[12] * v.x + M.v[13] * v.y + M.v[14] * v.z + M.v[15]
  };
}

void identity(mat4* M) {
  zeroes(M);
  M->v[0] = 1.0f;
  M->v[5] = 1.0f;
  M->v[10] = 1.0f;
  M->v[15] = 1.0f;
}

void scale_mat4z(mat4* M, float sx, float sy, float sz) { // A = scale matrix
  zeroes(M);
  M->v[0] = sx;
  M->v[5] = sy;
  M->v[10] = sz;
  M->v[15] = 1.0f;
}
void scale_mat4(mat4* M, float sx, float sy, float sz) { // A = scale matrix
  M->v[0] = sx;
  M->v[5] = sy;
  M->v[10] = sz;
  M->v[15] = 1.0f;
}

void translate_mat4z(mat4* M, float tx, float ty, float tz) { // A = translator matrix
  identity(M);
  M->v[3] = tx;
  M->v[7] = ty;
  M->v[11] = tz;
  M->v[15] = 1.0f;
}
void translate_mat4(mat4* M, float tx, float ty, float tz) { // A = translator matrix
  M->v[3] = tx;
  M->v[7] = ty;
  M->v[11] = tz;
  M->v[15] = 1.0f;
}

void rotate_mat4(mat4* M, float a, vec3 axis) { // A = rotator matrix
  identity(M);

  float c = cos(0.5f * a);
  float s = sin(0.5f * a);

  vec4 q = (vec4){s * axis.x, s * axis.y, s * axis.z, c};

  M->v[0] = 1.0f - 2.0f * (q.y * q.y) - 2.0f * (q.z * q.z);
  M->v[1] = 2.0f * (q.x * q.y - q.w * q.z);
  M->v[2] = 2.0f * (q.x * q.z + q.w * q.y);
  M->v[3] = 0.0f;

  M->v[4] = 2.0f * (q.x * q.y + q.w * q.z);
  M->v[5] = 1.0f - 2.0f * (q.x * q.x) - 2.0f * (q.z * q.z);
  M->v[6] = 2.0f * (q.y * q.z - q.w * q.x);
  M->v[7] = 0.0f;

  M->v[8] = 2.0f * (q.x * q.z - q.w * q.y);
  M->v[9] = 2.0f * (q.y * q.z + q.w * q.x);
  M->v[10] = 1.0f - 2.0f * (q.x * q.x) - 2.0f * (q.y * q.y);
  M->v[11] = 0.0f;

  M->v[12] = 0.0f;
  M->v[13] = 0.0f;
  M->v[14] = 0.0f;
  M->v[15] = 1.0f;
}

void projection_mat4(mat4* M, float aspect, float fov, float far, float near) {
  /*M->v[0] = 1.0f / (aspect * tan(0.5f * fov));
  M->v[1] = 0.0f;
  M->v[2] = 0.0f;
  M->v[3] = 0.0f;

  M->v[4] = 0.0f;
  M->v[5] = 1.0f / (tan(0.5f * fov));
  M->v[6] = 0.0f;
  M->v[7] = 0.0f;

  M->v[8] = 0.0f;
  M->v[9] = 0.0f;
  M->v[10] = -(far + near) / (far - near);
  M->v[11] = -(2.0f * far * near) / (far - near);

  M->v[12] = 0.0f;
  M->v[13] = 0.0f;
  M->v[14] = -1.0f;
  M->v[15] = 0.0f;*/

  zeroes(M);

  double top = near * tan(fov * 0.5);
  double bottom = -top;
  double right = top * aspect;
  double left = -right;

  float rl = (float)(right - left);
  float tb = (float)(top - bottom);
  float fn = (float)(far - near);

  M->v[0] = ((float)near * 2.0f) / rl;
  M->v[5] = ((float)near * 2.0f) / tb;
  M->v[2] = ((float)right + (float)left) / rl;
  M->v[6] = ((float)top + (float)bottom) / tb;
  M->v[10] = -((float)far + (float)near) / fn;
  M->v[14] = -1.0f;
  M->v[11] = -((float)far *(float)near * 2.0f) / fn;
}

vec3_pair perspective_lookat(mat4* M, vec3 pos, vec3 targ) {
  vec3 D = norm_vec3((vec3){pos.x - targ.x, pos.y - targ.y, pos.z - targ.z});
  const vec3 tup = (vec3){0.0f, 1.0f, 0.0f};
  vec3 R = norm_vec3(cross_vec3(tup, D));
  vec3 U = norm_vec3(cross_vec3(D, R));

  M->v[0] = R.x;
  M->v[1] = R.y;
  M->v[2] = R.z;
  M->v[3] = -(R.x * pos.x) - (R.y * pos.y) - (R.z * pos.z);

  M->v[4] = U.x;
  M->v[5] = U.y;
  M->v[6] = U.z;
  M->v[7] = -(U.x * pos.x) - (U.y * pos.y) - (U.z * pos.z);

  M->v[8] = D.x;
  M->v[9] = D.y;
  M->v[10] = D.z;
  M->v[11] = -(D.x * pos.x) - (D.y * pos.y) - (D.z * pos.z);

  M->v[12] = 0.0f;
  M->v[13] = 0.0f;
  M->v[14] = 0.0f;
  M->v[15] = 1.0f;

  return (vec3_pair){R, U};
}
