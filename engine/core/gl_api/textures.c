#include "textures.h"

Texture load_texture(const char* src, unsigned int* texture_counter, int unpack_alignment) {
  Texture tex;

  int width, height, channels;

  // generate new texture object
  glGenTextures(1, &tex.ID);
  glActiveTexture(GL_TEXTURE0 + (*texture_counter));
  tex.index = (*texture_counter);
  (*texture_counter)++;
  //glBindTextureUnit(mTextureCount, mTexID);
  glBindTexture(GL_TEXTURE_2D, tex.ID);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(src, &width, &height, &channels, 0);
  if(data){
     // load image, create texture and generate mipmaps
    GLenum format;
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);
    switch(channels){
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    printf("ERROR: failed to load texture\n");
  }
  stbi_image_free(data);

  tex.sizes = (vec2i){width, height};
  tex.sub_divisions = (vec2i){width, height};
  tex.sub_offset = (vec2){0.0f, 0.0f};

  return tex;
}

Texture_data load_texture_data(const char* src) {
  Texture_data td;

  stbi_set_flip_vertically_on_load(true);
  td.data = stbi_load(src, &td.w, &td.h, &td.c, 0);

  return td;
}

Texture create_texture_from_texture_data(Texture_data td, unsigned int* texture_counter, int unpack_alignment) {
  Texture tex;

  // generate new texture object
  glGenTextures(1, &tex.ID);
  glActiveTexture(GL_TEXTURE0 + (*texture_counter));
  tex.index = (*texture_counter);
  (*texture_counter)++;
  //glBindTextureUnit(mTextureCount, mTexID);
  glBindTexture(GL_TEXTURE_2D, tex.ID);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  if(td.data){
    // load image, create texture and generate mipmaps
    GLenum format;
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, td.w, td.h, 0, format, GL_UNSIGNED_BYTE, td.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    printf("ERROR: failed to load texture from texture data\n");
  }
  stbi_image_free(td.data);

  tex.sizes = (vec2i){td.w, td.h};
  tex.sub_divisions = (vec2i){td.w, td.h};
  tex.sub_offset = (vec2){0, 0};

  return tex;
}

Texture empty_texture(unsigned int w, unsigned int h, unsigned int* tex_counter) {
  unsigned int id = create_empty_tex(w, h, tex_counter);
  return (Texture){(*tex_counter) - 1, id, (vec2i){(int)w, (int)h}, (vec2i){(int)w, (int)h}, (vec2){0.0f, 0.0f}};
}

void set_texture_sub_division(Texture* tex, vec2i sub_sizes){
  tex->sub_divisions = sub_sizes;
}

Texture load_sub_texture(Texture tex, vec2i sheet_index) {
  //vec2 sub_coord = (vec2){tex.sub_divisions.x * sheet_index.x, tex.sub_divisions.y * sheet_index.y};
  return (Texture){tex.index, tex.ID, tex.sizes, tex.sub_divisions, (vec2){0.0f, 0.0f}};
}
