#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "engine/engine_core.h"

int close_on_esc(gfx3D gfx) {
  if (glfwGetKey(gfx.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    return 1;
  }
  return 0;
}

int main(void) {

  const char* base_textures[] = {
    "./assets/tex1.jpg",
    "./assets/tex2.png",
    "./assets/car.png"
  };

  const char* base_assets[] = {
    "./assets/car.obj",
    "./assets/floor.obj"
  };

  // create window / gfx environment
  gfx3D gfx = init("w", 1000, 800, (vec4){1.0f, 0.0f, 0.0f, 1.0f}, base_textures, 3, base_assets, 2);

  // create scenes
  scene3D s = create_scene3D(10);

  // create player controller
  player_controller p1 = init_fp_player(&gfx, (vec3){0.0f, 0.0f, 3.0f});

  // create entities
  entity3D car = create_entity(gfx, ASSET, 0, 2, 0);
  add_entity_to_scene(&s, &car);

  entity3D cube = create_entity(gfx, SHAPE, 0, 0, 0);
  add_entity_to_scene(&s, &cube);
  set_entity_pos(&cube, (vec3){15.0f, 0.0f, 0.0f});

  // lighting
  set_scene_ambient_light(&s, (ambient_light){(vec3){1.0f, 1.0f, 1.0f}, 0.3f});
  point_light l1 = create_point_light((vec3){10.0f, 10.0f, 20.0f}, (vec3){1.0f, 1.0f, 1.0f}, 1.0f);
  add_point_light_to_scene(&s, &l1);

  // demo
  unsigned int conv_index = 0;
  unsigned int conv_shader = create_shader_file("conv_vert_shader.glsl", "conv_frag_shader.glsl");
  float conv[9] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f
  };
  set_uniform_mat3x3(conv_shader, "conv\0", conv);
  vec2 screen_wh = (vec2){gfx.scr_width, gfx.scr_height};
  set_uniform(conv_shader, "screen_wh\0", UVEC2, (void*)(&screen_wh));
  int greyscale = 0;
  set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));

  while (!close_flag(gfx, close_on_esc)) {

    poll_input(gfx, p1.usr);

    if (glfwGetKey(gfx.window, GLFW_KEY_0) == GLFW_PRESS && conv_index != 0) {
      conv_index = 0; // normal
      conv[0] = 0.0f; conv[1] = 0.0f; conv[2] = 0.0f;
      conv[3] = 0.0f; conv[4] = 1.0f; conv[5] = 0.0f;
      conv[6] = 0.0f; conv[7] = 0.0f; conv[8] = 0.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 0;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }
    if (glfwGetKey(gfx.window, GLFW_KEY_1) == GLFW_PRESS && conv_index != 1) {
      conv_index = 1; // edges
      conv[0] = -1.0f; conv[1] = -1.0f; conv[2] = -1.0f;
      conv[3] = -1.0f; conv[4] =  8.0f; conv[5] = -1.0f;
      conv[6] = -1.0f; conv[7] = -1.0f; conv[8] = -1.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 1;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }
    if (glfwGetKey(gfx.window, GLFW_KEY_2) == GLFW_PRESS && conv_index != 2) {
      conv_index = 2; // horizontal edges
      conv[0] = -1.0f; conv[1] = -1.0f; conv[2] = -1.0f;
      conv[3] = 0.0f; conv[4] = 0.0f; conv[5] = 0.0f;
      conv[6] = 1.0f; conv[7] = 1.0f; conv[8] = 1.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 1;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }
    if (glfwGetKey(gfx.window, GLFW_KEY_3) == GLFW_PRESS && conv_index != 3) {
      conv_index = 3; // vertical edges
      conv[0] = -1.0f; conv[1] = 0.0f; conv[2] = 1.0f;
      conv[3] = -1.0f; conv[4] = 0.0f; conv[5] = 1.0f;
      conv[6] = -1.0f; conv[7] = 0.0f; conv[8] = 1.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 1;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }
    if (glfwGetKey(gfx.window, GLFW_KEY_4) == GLFW_PRESS && conv_index != 4) {
      conv_index = 4; // sharpen
      conv[0] = 0.0f; conv[1] = -1.0f; conv[2] = 0.0f;
      conv[3] = -1.0f; conv[4] = 5.0f; conv[5] = -1.0f;
      conv[6] = 0.0f; conv[7] = -1.0f; conv[8] = 0.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 0;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }
    if (glfwGetKey(gfx.window, GLFW_KEY_5) == GLFW_PRESS && conv_index != 5) {
      conv_index = 5; // gauss blurring
      conv[0] = 1.0f/16.0f; conv[1] = 1.0f/8.0f; conv[2] = 1.0f/16.0f;
      conv[3] = 1.0f/8.0f; conv[4] = 1.0f/2.0f; conv[5] = 1.0f/8.0f;
      conv[6] = 1.0f/16.0f; conv[7] = 1.0f/8.0f; conv[8] = 1.0f/16.0f;
      set_uniform_mat3x3(conv_shader, "conv\0", conv);
      greyscale = 0;
      set_uniform(conv_shader, "greyscale\0", UI, (void*)(&greyscale));
    }

    set_point_light_pos(&l1, p1.cam->pos);

    move_camera3D_dir(p1.cam, &gbl_gfx_dx, &gbl_gfx_dy);

    update_scene(&s);

    begin_frame(gfx);

    // render here
    render(&gfx, s, &p1.cam[0], 0);

    end_frame_post_process(gfx, conv_shader);
  }

  destroy_player_controller(p1);
  end(&gfx);

  return 0;
}
