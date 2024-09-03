#include "gfx3D_210.h"

gfx3D init(const char* name, unsigned int w, unsigned int h, vec4 ccol) {

  gfx3D gfx;
  gfx.scr_width = w;
  gfx.scr_height = h;
  gfx.r = ccol.x;
  gfx.g = ccol.y;
  gfx.b = ccol.z;
  gfx.a = ccol.w;

  gfx.texture_counter = 0;

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(gfx.scr_width, gfx.scr_height, name, NULL, NULL);
  if (window == NULL)
  {
    printf("%s\n", "Failed to create GLFW window");
    glfwTerminate();
    while(1);
  }
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("%s\n", "Failed to initialize GLAD");
    while(1);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  gfx.window = window;

  return gfx;
}

void begin_frame(gfx3D gfx) {
  glClearColor(gfx.r, gfx.g, gfx.b, gfx.a);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void end_frame(gfx3D gfx) {
  glfwPollEvents();
  glfwSwapBuffers(gfx.window);
}

int close_flag(gfx3D gfx, int (*user_events)(gfx3D)) {
  if (user_events != NULL) {
    return user_events(gfx) || glfwWindowShouldClose(gfx.window);
  }
  return glfwWindowShouldClose(gfx.window);
}
