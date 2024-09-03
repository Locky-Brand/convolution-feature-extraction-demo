#ifndef GFX330_H
#define GFX330_H

#include <stdio.h>
#include <stdlib.h>

#include "../gl_api/api_include.h"
#include "../gl_api/api_tools.h"
#include "../gl_api/textures.h"
#include "texture_unit.h"

#include "../math/vec3.h"
#include "../math/vec4.h"

#include "../utils/gbl_utils.h"

#include "../objects/asset3D.h"

typedef struct {
  // window
  GLFWwindow* window;
  unsigned int scr_width, scr_height;
  float r, g, b, a; // clear color

  // objects
  unsigned int main_VBO, main_IBO, main_VAO, main_shader;

  // rendering pipeline

  // frame
  FBO main_frame;

  // textures
  unsigned int texture_counter;
  Texture* textures;

  // assets
  unsigned int asset_counter;
  asset3D* assets;

  // default assets
  asset3D shapes[3];

} gfx3D;

// create window for rendering
gfx3D init(const char* name, unsigned int w, unsigned int h, vec4 ccol, const char** btex, unsigned int nbtex, const char** bassets, unsigned int nbassets);
void end(gfx3D* gfx);

// render loop
void begin_frame(gfx3D gfx);
void end_frame(gfx3D gfx);
void end_frame_post_process(gfx3D gfx, unsigned int post_process_shader);

// close window
int close_flag(gfx3D gfx, int (*user_events)(gfx3D));

// rendering pipeline utilities creation
void use_anti_aliasing(gfx3D* g);

#endif
