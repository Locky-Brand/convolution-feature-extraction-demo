#ifndef SCENE_H
#define SCENE_H
#include <stdlib.h>

#include "../../entities/entity.h"
#include "point_light.h"
#include "ambient_light.h"

// TODO change to be entity3D

typedef struct {
  entity3D** objs;
  unsigned int n;
  unsigned int max_objs;

  point_light** lights;
  unsigned int n_lights;
} scene3D;

scene3D create_scene3D(unsigned int n_objs);

void add_entity_to_scene(scene3D* s, entity3D* o);
void add_point_light_to_scene(scene3D* s, point_light* pl);

void set_scene_ambient_light(scene3D* s, ambient_light al);

void update_scene(scene3D* s);

#endif
