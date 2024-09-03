#include "camera3D.h"

camera3D create_camera3D(gfx3D* gfx, vec3 pos, vec3 target, int camera_frame) {
  camera3D cam;
  cam.pos = pos;
  vec3 dir = sub_vec3(target, pos);
  dir = norm_vec3(dir);
  cam.targ = add_vec3(pos, (vec3){0.0f, 0.0f, 1.0f});
  cam.u = (vec3){0.0f, 1.0f, 0.0f};
  cam.r = (vec3){1.0f, 0.0f, 0.0f};

  cam.pitch = 0.0f;
  cam.yaw = 0.0f;

  cam.cam_speed = 0.01f;

  if (camera_frame) {
    //cam.frame = create_FBO(gfx->scr_width, gfx->scr_height, &gfx->texture_counter);
  }
  else {
    //cam.frame = gfx->main_frame;
  }

  return cam;
}

void capture_scene(gfx3D gfx, scene3D s, camera3D* c) {

  vec3_pair ru = perspective_lookat(&c->view, c->pos, c->targ);
  c->r = ru.a;
  c->u = ru.b;

  //glBindFramebuffer(GL_FRAMEBUFFER, c->frame.ID);
  //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  //glEnable(GL_DEPTH_TEST);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (unsigned int i = 0; i < s.n; ++i) {
    //set_uniform_mat4x4(s.objs[i].gfx.shader, "view\0", c->view.v);

    //render(gfx, s, c);
  }
}

void move_camera3D_pos(camera3D* cam, vec3 to) {
  cam->pos = to;
}

void move_camera3D_dir(camera3D* cam, double* mouse_dx, double* mouse_dy) {

  float dx = *mouse_dx;
  float dy = -(*mouse_dy);

  float delta = 1.0f/60.0f;
  cam->yaw += dx * delta;
  cam->pitch += dy * delta;

  if (cam->pitch > 45.0f) {
    cam->pitch = 44.99f;
  }
  if (cam->pitch < -45.0f) {
    cam->pitch = -44.99f;
  }

  float yaw = cam->yaw * (2 * PI / 180.0f);
  float pitch = cam->pitch * (2 * PI / 180.0f);

  vec3 direction;
  direction.x = cos(yaw) * cos(pitch) + cam->pos.x;
  direction.y = sin(pitch) + cam->pos.y;
  direction.z = sin(yaw) * cos(pitch) + cam->pos.z;
  //direction = norm_vec3(direction);
  cam->targ = direction; //add_vec3(direction, cam->pos);

  (*mouse_dx) = 0.0f;
  (*mouse_dy) = 0.0f;
}

void fps_cam_w_action(void* data, unsigned int size) {
  camera3D* cam = (camera3D*)data;
  const vec3 cam_dir = norm_vec3(sub_vec3(cam->targ, cam->pos));
  const float cam_speed = cam->cam_speed;
  cam->pos.x += cam_dir.x * cam_speed;
  cam->pos.y += cam_dir.y * cam_speed;
  cam->pos.z += cam_dir.z * cam_speed;

  cam->targ.x += cam_dir.x * cam_speed;
  cam->targ.y += cam_dir.y * cam_speed;
  cam->targ.z += cam_dir.z * cam_speed;
}

void fps_cam_s_action(void* data, unsigned int size) {
  camera3D* cam = (camera3D*)data;
  const vec3 cam_dir = norm_vec3(sub_vec3(cam->targ, cam->pos));
  const float cam_speed = cam->cam_speed;
  cam->pos.x -= cam_dir.x * cam_speed;
  cam->pos.y -= cam_dir.y * cam_speed;
  cam->pos.z -= cam_dir.z * cam_speed;

  cam->targ.x -= cam_dir.x * cam_speed;
  cam->targ.y -= cam_dir.y * cam_speed;
  cam->targ.z -= cam_dir.z * cam_speed;
}

void fps_cam_a_action(void* data, unsigned int size) {
  camera3D* cam = (camera3D*)data;
  const vec3 cam_dir = norm_vec3(cam->r);
  const float cam_speed = cam->cam_speed;
  cam->pos.x -= cam_dir.x * cam_speed;
  cam->pos.y -= cam_dir.y * cam_speed;
  cam->pos.z -= cam_dir.z * cam_speed;

  cam->targ.x -= cam_dir.x * cam_speed;
  cam->targ.y -= cam_dir.y * cam_speed;
  cam->targ.z -= cam_dir.z * cam_speed;
}

void fps_cam_d_action(void* data, unsigned int size) {
  camera3D* cam = (camera3D*)data;
  const vec3 cam_dir = norm_vec3(cam->r);
  const float cam_speed = cam->cam_speed;
  cam->pos.x += cam_dir.x * cam_speed;
  cam->pos.y += cam_dir.y * cam_speed;
  cam->pos.z += cam_dir.z * cam_speed;

  cam->targ.x += cam_dir.x * cam_speed;
  cam->targ.y += cam_dir.y * cam_speed;
  cam->targ.z += cam_dir.z * cam_speed;
}

void fps_cam_left_click_action(void* data, unsigned int size) {
  printf("L\n");
}

void fps_cam_right_click_action(void* data, unsigned int size) {
  printf("R\n");
}
