# Convolution demo of my graphics framework

## Overview

A graphics framework that provides abstraction of libraries such as glfw and ASSIMP into a common API 

### Example Usage

Here's a brief code snippet demonstrating how to use the convolution operations provided by **MyGraphicsFramework**:

```cpp
//custom window exit function
int close_on_esc(gfx3D gfx) {
  if (glfwGetKey(gfx.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    return 1;
  }
  return 0;
}

int main(void) {
  // load textures
  const char* base_textures[] = {
    "./assets/tex1.jpg",
    "./assets/tex2.png",
    "./assets/car.png"
  };

  // load 3D model files
  const char* base_assets[] = {
    "./assets/car.obj",
    "./assets/floor.obj"
  };

  // create window / gfx environment
  gfx3D gfx = init("w", 1000, 800, (vec4){1.0f, 0.0f, 0.0f, 1.0f}, base_textures, 3, base_assets, 2);

  // create scene
  scene3D s = create_scene3D(10);

  // create player controller
  player_controller p1 = init_fp_player(&gfx, (vec3){0.0f, 0.0f, 3.0f});

  // create entities
  entity3D car = create_entity(gfx, ASSET, 0, 2, 0);
  add_entity_to_scene(&s, &car);

  entity3D cube = create_entity(gfx, SHAPE, 0, 0, DISABLE_LIGHTING);
  add_entity_to_scene(&s, &cube);

  entity3D bill = create_entity(gfx, BILLBOARD, 0, 0, BILLBOARD_LOCK_X);
  add_entity_to_scene(&s, &bill);

  entity3D tex = create_entity(gfx, TEXTURE, 0, 1, 0);
  add_entity_to_scene(&s, &tex);

  set_entity_pos(&tex, (vec3){0.0f, 15.0f, 0.0f});
  set_entity_pos(&cube, (vec3){15.0f, 0.0f, 0.0f});
  set_entity_pos(&bill, (vec3){15.0f, 0.0f, 20.0f});

  // apply lighting
  set_scene_ambient_light(&s, (ambient_light){(vec3){1.0f, 0.0f, 0.0f}, 0.1f});
  point_light l1 = create_point_light((vec3){10.0f, 10.0f, 20.0f}, (vec3){1.0f, 1.0f, 1.0f}, 1.0f);
  add_point_light_to_scene(&s, &l1);

  // main loop
  while (!close_flag(gfx, close_on_esc)) {

    poll_input(gfx, p1.usr);

    move_camera3D_dir(p1.cam, &gbl_gfx_dx, &gbl_gfx_dy);

    update_scene(&s);

    begin_frame(gfx);

    // render here
    render(&gfx, s, &p1.cam[0], 0);

    end_frame(gfx);
  }

  // clean up
  destroy_player_controller(p1);
  end(&gfx);

  return 0;
}
```

## Demo: Convolution Feature Extraction

To demonstrate the project it was used to display the output of convolution feature extraction kernals applied to a 3D scene.



