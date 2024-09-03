#include "input3D.h"

float gbl_gfx_mouse_sensitivity = DEFAULT_MOUSE_SENSITIVITY;
int gbl_gfx_first_mouse = 1;
double gbl_gfx_xpos = 0.0;
double gbl_gfx_ypos = 0.0;
double gbl_gfx_dx = 0.0;
double gbl_gfx_dy = 0.0;

input3D create_input(gfx3D gfx, int key_count) {
  input3D usr_in;

  glfwSetInputMode(gfx.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(gfx.window, mouse_callback);

  usr_in.key_actions = (key_press_action*)malloc(key_count * sizeof(key_press_action));
  usr_in.key_act_count = 0;
  usr_in.key_act_max = key_count;

  return usr_in;
}

void set_key_action(input3D* in, key k, void (*act)(void*, unsigned int), trigger on, void* data, unsigned int size) {
  if (in->key_act_count < in->key_act_max) {
    in->key_actions[in->key_act_count] = (key_press_action){k, act, on, data, size};
    ++in->key_act_count;
    return;
  }
  printf("WARN: set_key_action(): max key amount reached\n");
}

void poll_input(gfx3D gfx, input3D* in) {
  for (int i = 0; i < in->key_act_count; ++i) {
    if (glfwGetKey(gfx.window, in->key_actions[i].k) == in->key_actions[i].trig) {
      in->key_actions[i].action(in->key_actions[i].data, in->key_actions[i].data_size);
    }
  }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

  if (gbl_gfx_first_mouse)
  {
      gbl_gfx_xpos = xpos;
      gbl_gfx_ypos = ypos;
      gbl_gfx_first_mouse = 0;
  }

  gbl_gfx_dx = xpos - gbl_gfx_xpos;
  gbl_gfx_dy = ypos - gbl_gfx_ypos;

  gbl_gfx_xpos = xpos;
  gbl_gfx_ypos = ypos;

  gbl_gfx_dx *= gbl_gfx_mouse_sensitivity;
  gbl_gfx_dy *= gbl_gfx_mouse_sensitivity;

}

void destroy_input(input3D in) {
  free(in.key_actions);
}
