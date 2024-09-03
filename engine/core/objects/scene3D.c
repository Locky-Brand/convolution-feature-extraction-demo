#include "scene3D.h"

scene3D create_scene3D(unsigned int n_objs) {
  scene3D s;
  s.objs = (entity3D**)malloc(n_objs * sizeof(entity3D*));
  s.max_objs = n_objs;
  s.n = 0;
  s.n_lights = 0;
  s.lights = NULL;
  return s;
}

void add_entity_to_scene(scene3D* s, entity3D* o) {
  if (s->n < s->max_objs) {
    s->objs[s->n] = o;
    set_uniform_mat4x4(s->objs[s->n]->gfx_obj.gfx.shader, "model", (float*)(s->objs[s->n]->_transform.m.v));
    s->n = s->n + 1;
  }
}
void add_point_light_to_scene(scene3D* s, point_light* pl) {
  s->lights = (point_light**)realloc(s->lights, (s->n_lights + 1) * sizeof(point_light*));
  s->lights[s->n_lights] = pl;
  s->n_lights++;

  for (unsigned int i = 0; i < s->n; ++i) {
    set_uniform(s->objs[i]->gfx_obj.gfx.shader, "lights.pos", UVEC3, (void*)(&pl->pos));
    set_uniform(s->objs[i]->gfx_obj.gfx.shader, "lights.color", UVEC3, (void*)(&pl->color));
    set_uniform(s->objs[i]->gfx_obj.gfx.shader, "lights.intensity", UFLOAT, (void*)(&pl->intensity));
  }
}

void set_scene_ambient_light(scene3D* s, ambient_light al) {
  vec3 col = al.color;
  float in = al.intensity;

  for (unsigned int i = 0; i < s->n; ++i) {
    set_uniform(s->objs[i]->gfx_obj.gfx.shader, "ambient_light", UVEC3, (void*)(&col));
    set_uniform(s->objs[i]->gfx_obj.gfx.shader, "ambient_light_intensity", UFLOAT, (void*)(&in));
  }
}

void update_scene(scene3D* s) {
  for (unsigned int i = 0; i < s->n_lights; ++i) {
    if (s->lights[i]->requires_update) {
      for (unsigned int j = 0; j < s->n; ++j) {
        set_uniform(s->objs[j]->gfx_obj.gfx.shader, "lights.pos", UVEC3, (void*)(&s->lights[i]->pos));
      }
    }
  }

  for (unsigned int i = 0; i < s->n; ++i) {
    switch (s->objs[i]->_type) {
      default:
        update_entity(s->objs[i], NULL, 0);
      break;
    }
  }
}
