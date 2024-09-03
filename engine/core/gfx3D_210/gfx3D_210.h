#ifndef GFX210_H
#define GFX210_H

#include <stdio.h>
#include <stdlib.h>

#include "../gl_api/api_include.h"
#include "../gl_api/api_tools.h"

#include "../math/vec4.h"

typedef struct {
  // window
  GLFWwindow* window;
  unsigned int scr_width, scr_height;
  float r, g, b, a; // clear color

  // textures
  unsigned int texture_counter;

} gfx3D;

// create window for rendering
gfx3D init(const char* name, unsigned int w, unsigned int h, vec4 ccol);

// render loop
void begin_frame(gfx3D gfx);
void end_frame(gfx3D gfx);

// close window
int close_flag(gfx3D gfx, int (*user_events)(gfx3D));

#endif
