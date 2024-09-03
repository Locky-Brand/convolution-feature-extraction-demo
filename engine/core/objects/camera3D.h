#ifndef CAM3D_H
#define CAM3D_H

#include "../renderer.h"
#include "scene3D.h"

#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"
#include "../math/utils.h"

typedef struct {
  vec3 pos;
  vec3 targ;

  vec3 r;
  vec3 u;

  float yaw;
  float pitch;

  double mouse_dx;
  double mouse_dy;

  mat4 view;

  //FBO frame;

  float cam_speed;
  float sensitivity;
} camera3D;

camera3D create_camera3D(gfx3D* gfx, vec3 pos, vec3 target, int camera_frame);

void capture_scene(gfx3D gfx, scene3D s, camera3D* c);

void move_camera3D_pos(camera3D* cam, vec3 to);

void move_camera3D_dir(camera3D* cam, double* mouse_dx, double* mouse_dy);

// fps mode user input
void fps_cam_w_action(void* data, unsigned int size);
void fps_cam_s_action(void* data, unsigned int size);
void fps_cam_a_action(void* data, unsigned int size);
void fps_cam_d_action(void* data, unsigned int size);
void fps_cam_left_click_action(void* data, unsigned int size);
void fps_cam_right_click_action(void* data, unsigned int size);

#endif
