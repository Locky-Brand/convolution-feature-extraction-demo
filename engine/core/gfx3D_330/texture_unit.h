#ifndef TEX_UNIT_H
#define TEX_UNIT_H

#include "../gl_api/textures.h"
#include "../gl_api/api_tools.h"
#include "../math/vec2.h"

#define TEXTURE_UNIT_MAX_SIZE 1024

typedef struct {
    Texture* tex;
    vec2i c;
    unsigned int maxima;
    unsigned int max_height;
    unsigned int nsub_textures;

    Texture base_texture; // texture unit storing all other textures
} texture_unit;

texture_unit create_texture_unit(unsigned int* texture_counter);

int load_texture_into_unit(texture_unit* unit, const char* file, unsigned int* texture_counter);

void destroy_texture_unit(texture_unit tu);

#endif
