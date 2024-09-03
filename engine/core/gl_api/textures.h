#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdio.h>
#include <stdlib.h>

#if defined GL330 || defined GL210

#include "api_include.h"

#include <stb/stb_image.h>

#include "api_tools.h"
#include "../math/vec2.h"

#endif

typedef struct {
  unsigned int index;
  unsigned int ID;
  vec2i sizes;
  vec2i sub_divisions;
  vec2 sub_offset;
} Texture;

typedef struct {
  unsigned char* data;
  int w;
  int h;
  int c;
} Texture_data;

Texture load_texture(const char* src, unsigned int* texture_counter, int unpack_alignment);
Texture create_texture_from_texture_data(Texture_data td, unsigned int* texture_counter, int unpack_alignment);
Texture_data load_texture_data(const char* src);
Texture empty_texture(unsigned int w, unsigned int h, unsigned int* tex_counter);
void set_texture_sub_division(Texture* tex, vec2i sub_sizes);
Texture load_sub_texture(Texture tex, vec2i sheet_index);

#endif
