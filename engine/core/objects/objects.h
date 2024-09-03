#ifndef OBJ_H
#define OBJ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// assimp
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include "../gl_api/api_include.h"
#include "../gfx3D_330/gfx3D_330.h"
#include "../math/math_def.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"
#include "./asset3D.h"
#include "./render_types.h"

typedef enum {
  VERTS,
  INDS
} render_indexing_method;

typedef struct {
  unsigned int VBO, VAO, IBO, shader;
} render_buffers;

typedef struct {
  render_buffers gfx;
  render_indexing_method m;
  unsigned int n; // num verts or inds based on m

  float* verts;
  unsigned int nverts;
  unsigned int* inds;
  unsigned int ninds;

  render_attribs attribs;
} object;

object create_object(gfx3D gfx, float* verts, unsigned int* inds, unsigned int n_verts, unsigned int n_inds, render_attribs attribs, const char* vspath, const char* fspath, int cpy_gfx_data);

object create_object_asset3D(gfx3D gfx, unsigned int asset_index, const char* vspath, const char* fspath, int cpy_gfx_data);

void recreate_obj_shader(gfx3D gfx, object* obj, unsigned int new_shader);

void render_obj(object obj);

void destroy_obj(object obj); 

#endif
