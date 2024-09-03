#ifndef ASSET3D_H
#define ASSET3D_H

#include <stdlib.h>
#include <stdio.h>

// assimp
#include "assimp/cimport.h"        // Plain-C interface
#include "assimp/scene.h"          // Output data structure
#include "assimp/postprocess.h"    // Post processing flags

#include "render_types.h"

typedef struct {
  float* verts;
  unsigned int nverts;
  unsigned int* inds;
  unsigned int ninds;
  render_attribs attribs;
} asset3D;

asset3D load_obj_file(const char* obj_file);

void delete_asset3D(asset3D asset);

#endif
