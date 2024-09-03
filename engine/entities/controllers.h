#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
#include <stdio.h>

#include "../engine_core.h"

typedef struct {
  camera3D* cam;
  input3D* usr;
  int internal;
} player_controller;

player_controller init_fp_player(gfx3D* gfx, vec3 spawn);

void destroy_player_controller(player_controller pc);

#endif
