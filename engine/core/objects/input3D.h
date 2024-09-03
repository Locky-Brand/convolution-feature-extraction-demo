#ifndef INPUT3D_H
#define INPUT3D_H

#include <stdio.h>

#include "../renderer.h"
#include "../math/math_def.h"

#define DEFAULT_MOUSE_SENSITIVITY 5.0f

typedef enum {
#if defined(GL330) || defined(GL210)
  KEY_W = GLFW_KEY_W,
  KEY_A = GLFW_KEY_A,
  KEY_S = GLFW_KEY_S,
  KEY_D = GLFW_KEY_D,
  KEY_SHIFT = GLFW_KEY_LEFT_SHIFT,
  KEY_MOUSE_L = GLFW_MOUSE_BUTTON_LEFT,
  KEY_MOUSE_R = GLFW_MOUSE_BUTTON_RIGHT,
  KEY_Q = GLFW_KEY_Q,
  KEY_E = GLFW_KEY_E,
  KEY_R = GLFW_KEY_R,
  KEY_ARROW_LEFT = GLFW_KEY_LEFT,
  KEY_ARROW_UP = GLFW_KEY_UP,
  KEY_ARROW_RIGHT = GLFW_KEY_RIGHT,
  KEY_ARROW_DOWN = GLFW_KEY_DOWN
#endif
} key;

typedef enum {
#if defined(GL330) || defined(GL210)
  KEY_PRESS = GLFW_PRESS,
  KEY_RELEASE = GLFW_RELEASE
#endif
} trigger;

typedef struct {
  key k;
  void (*action)(void*, unsigned int);
  trigger trig;
  void* data;
  unsigned int data_size;
} key_press_action;

typedef struct {
  key_press_action* key_actions;
  int key_act_count;
  int key_act_max;
} input3D;

extern float gbl_gfx_mouse_sensitivity;
extern double gbl_gfx_xpos;
extern double gbl_gfx_ypos;
extern double gbl_gfx_dx;
extern double gbl_gfx_dy;
extern int gbl_gfx_first_mouse;

input3D create_input(gfx3D gfx, int key_count);

void set_key_action(input3D* in, key k, void (*act)(void*, unsigned int), trigger on, void* data, unsigned int size);

void poll_input(gfx3D gfx, input3D* in);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void destroy_input(input3D in);

#endif
