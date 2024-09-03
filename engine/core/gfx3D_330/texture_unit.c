#include "texture_unit.h"

texture_unit create_texture_unit(unsigned int* texture_counter) {
    texture_unit tu = (texture_unit){NULL, (vec2i){0, 0}, 0, TEXTURE_UNIT_MAX_SIZE, 0, empty_texture(TEXTURE_UNIT_MAX_SIZE, TEXTURE_UNIT_MAX_SIZE, texture_counter)};
    return tu;
}

int load_texture_into_unit(texture_unit* unit, const char* file, unsigned int* texture_counter) {

    // load texture
    Texture_data td = load_texture_data(file);

    // does texture fit?
    if (td.w > TEXTURE_UNIT_MAX_SIZE - unit->c.x) {
        unit->c.x = 0;
        unit->c.y = unit->maxima;
        unit->max_height -= unit->maxima;
    }
    if ((unsigned int)td.h > unit->max_height) {
        //printf("no room, width: %d, height: %d vs width: %d, height: %d\n", td.w, td.h, TEXTURE_UNIT_MAX_SIZE - unit->c.x, unit->max_height);
        free(td.data);
        return 0;
    }

    // create sub texture
    unit->tex = (Texture*)realloc(unit->tex, (unit->nsub_textures + 1) * sizeof(Texture));
    unit->tex[unit->nsub_textures].index = unit->base_texture.index;
    unit->tex[unit->nsub_textures].ID = unit->base_texture.ID;
    unit->tex[unit->nsub_textures].sizes = (vec2i){td.w, td.h};
    unit->tex[unit->nsub_textures].sub_divisions = (vec2i){td.w, td.h};
    unit->tex[unit->nsub_textures].sub_offset = (vec2){(float)unit->c.x / (float)TEXTURE_UNIT_MAX_SIZE, (float)unit->c.y / (float)TEXTURE_UNIT_MAX_SIZE};
    //printf("%f, %f\n", (float)unit->c.x / (float)TEXTURE_UNIT_MAX_SIZE, (float)unit->c.y / (float)TEXTURE_UNIT_MAX_SIZE);
    unit->nsub_textures++;
    if ((unsigned int)td.h > unit->maxima) {
        unit->maxima = td.h;
    }

    // copy sub texture data to texture unit base texture
    GLenum format;
    switch(td.c){
      case 3:
        format = GL_RGB;
      break;
      case 4:
        format = GL_RGBA;
      break;
      default:
        printf("ERROR: unknown image format\n");
        format = GL_RGB;
      break;
    }
    glActiveTexture(GL_TEXTURE0 + unit->base_texture.index);
    glBindTexture(GL_TEXTURE_2D, unit->base_texture.ID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, unit->c.x, unit->c.y, td.w, td.h, format, GL_UNSIGNED_BYTE, (void*)td.data);
    
    unit->c.x += td.w;
    if (unit->c.x >= TEXTURE_UNIT_MAX_SIZE) {
        unit->c.x = 0;
        unit->c.y = unit->maxima;
        unit->max_height -= unit->maxima;
    }

    free(td.data);

    return 1;
}

void destroy_texture_unit(texture_unit tu) {
    if (tu.tex) {
      free(tu.tex);
    }
}
