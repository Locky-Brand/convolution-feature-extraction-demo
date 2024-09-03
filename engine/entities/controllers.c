#include "controllers.h"

player_controller init_fp_player(gfx3D* gfx, vec3 spawn) {
  // create cameras
  camera3D* c = (camera3D*)malloc(sizeof(camera3D));
  (*c) = create_camera3D(gfx, spawn, (vec3){-10.0f, 0.0f, 0.0f}, 0);

  // set up user input
  input3D* usr_in = (input3D*)malloc(sizeof(input3D));
  (*usr_in) = create_input(*gfx, 6);
  set_key_action(usr_in, KEY_W, fps_cam_w_action, KEY_PRESS, (void*)c, sizeof(camera3D));
  set_key_action(usr_in, KEY_S, fps_cam_s_action, KEY_PRESS, (void*)c, sizeof(camera3D));
  set_key_action(usr_in, KEY_A, fps_cam_a_action, KEY_PRESS, (void*)c, sizeof(camera3D));
  set_key_action(usr_in, KEY_D, fps_cam_d_action, KEY_PRESS, (void*)c, sizeof(camera3D));

  set_key_action(usr_in, KEY_MOUSE_L, fps_cam_left_click_action, KEY_PRESS, (void*)c, sizeof(camera3D));
  set_key_action(usr_in, KEY_MOUSE_R, fps_cam_right_click_action, KEY_PRESS, (void*)c, sizeof(camera3D));

  return (player_controller){c, usr_in, 1};
}

void destroy_player_controller(player_controller pc) {
  destroy_input(*pc.usr);

  if (pc.internal) {
    free(pc.cam);
    free(pc.usr);
  }
}
