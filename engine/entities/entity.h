#ifndef ENTITY_H
#define ENTITY_H

#include "../core/math/vec3.h"
#include "../core/math/vec4.h"
#include "../core/math/mat4.h"
#include "../core/objects/objects.h"

// entity3D creation mutators

// copy asset data into new array
#define ASSET_CPY 0b00000001
#define INSTANCE 0b00000010

// use lighting effects
#define DISABLE_LIGHTING 0b00000100

// billboard mutators
#define BILLBOARD_LOCK_Y 0b00000001
#define BILLBOARD_LOCK_X 0b00000010

// types
typedef struct {
  mat4 m; // model matrix for shader
  vec3 pos; // x, y, z position in 3D space
  vec3 dir; // roll, pitch, yaw of object i.e. rotation around x, rotation around y, rotation around z 
  vec3 scale; // scale x, scale y, scale z
} transform;

typedef enum {
  ASSET,
  SHAPE,
  BILLBOARD,
  TEXTURE
} entity_type;

typedef struct {
  object gfx_obj;
  transform _transform;
  
  entity_type _type;
  unsigned char _mutators;
  void (*_updator)(void*, void*, int);
  int _requires_update;

} entity3D;

// updator functions
void asset_updator(void* entity_ptr, void* data, int data_size);
void shape_updator(void* entity_ptr, void* data, int data_size);
void texture_updator(void* entity_ptr, void* data, int data_size);
void billboard_updator(void* entity_ptr, void* data, int data_size);

// set entity properties
void set_texture(gfx3D gfx, object obj, Texture texture);
void set_shader(gfx3D gfx, entity3D* e, unsigned int shader);
void set_entity_pos(entity3D* e, vec3 pos);

// entity creation
entity3D create_entity(gfx3D gfx, entity_type type, unsigned int asset_index, int texture_index, unsigned char mutators);
void update_entity(entity3D* e, void* data, int data_size);
void destroy_entity(entity3D e);

#endif
