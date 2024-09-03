#include "objects.h"

object create_object(gfx3D gfx, float* verts, unsigned int* inds, unsigned int n_verts, unsigned int n_inds, render_attribs attribs, const char* vspath, const char* fspath, int cpy_gfx_data) {

  unsigned int vertex_fc = 0;
  for (unsigned int i = 0; i < attribs.n_elems; ++i) {
    vertex_fc += attribs.elems[i].float_count;
  }

  unsigned int VBO = 0;
  unsigned int IBO = 0;
  unsigned int VAO = 0;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, n_verts * vertex_fc * sizeof(float), verts, GL_DYNAMIC_DRAW);

  int offset = 0;
  for (unsigned int i = 0; i < attribs.n_elems; ++i) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attribs.elems[i].float_count, GL_FLOAT, GL_FALSE, vertex_fc * sizeof(float), (void*)(offset * sizeof(float)));
    offset += attribs.elems[i].float_count;
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  render_indexing_method m = VERTS;
  int n = n_verts;

  if (n_inds) {
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_inds * sizeof(unsigned int), inds, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m = INDS;
    n = n_inds;
  }

  unsigned int shader = 0;

  {
    /*const char* vertex = "#version 330 core\n"
                         "layout(location = 0) in vec3 aPos;\n"
                         "uniform mat4 model;\n"
                         "uniform mat4 view;\n"
                         "uniform mat4 projection;\n"
                         "void main(){\n"
                         "gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
                         "};\n\0";
    const char* fragment = "#version 330 core\n"
                         "out vec4 aColor;\n"
                         "void main(){\n"
                         "aColor = vec4(1.0f);\n"
                         "};\n\0";*/

    shader = create_shader_file(vspath, fspath);

    //vec2 scr_dim = (vec2){(float)gfx.scr_width, (float)gfx.scr_height};
    //set_uniform(shader, "scr_wh\0", UVEC2, (void*)(&scr_dim));
  }

  // maths
  mat4 model;
  identity(&model);
  set_uniform_mat4x4(shader, "model\0", model.v);

  mat4 view;
  identity(&view);
  set_uniform_mat4x4(shader, "view\0", view.v);

  mat4 projection;
  projection_mat4(&projection, (float)((float)gfx.scr_width / (float)gfx.scr_height), PI/4.0f, 1000.0f, 0.01f);
  set_uniform_mat4x4(shader, "projection\0", projection.v);

  object out;

  out.gfx = (render_buffers){VBO, VAO, IBO, shader};
  out.m = m;
  out.n = n;
  out.verts = NULL;
  out.nverts = n_verts;
  out.inds = NULL;
  out.ninds = n_inds;

  out.attribs = (render_attribs){NULL, 0};

  if (cpy_gfx_data) {

    out.verts = (float*)malloc(n_verts * get_vert_stride_from_attribs(attribs) * sizeof(float));
    memcpy(out.verts, verts, n_verts * get_vert_stride_from_attribs(attribs) * sizeof(float));

    out.inds = (unsigned int*)malloc(n_inds * sizeof(float));
    memcpy(out.inds, inds, n_inds * sizeof(unsigned int));

    out.attribs.n_elems = attribs.n_elems;
    out.attribs.elems = (render_elem*)malloc(attribs.n_elems * sizeof(render_elem));
    memcpy(out.attribs.elems, attribs.elems, attribs.n_elems * sizeof(render_elem));

  }
  
  return out;
}

object create_object_asset3D(gfx3D gfx, unsigned int asset_index, const char* vspath, const char* fspath, int cpy_gfx_data) {
  return create_object(gfx, gfx.assets[asset_index].verts, gfx.assets[asset_index].inds, gfx.assets[asset_index].nverts, gfx.assets[asset_index].ninds, gfx.assets[asset_index].attribs, vspath, fspath, cpy_gfx_data);
}

void recreate_obj_shader(gfx3D gfx, object* obj, unsigned int new_shader) {
  glDeleteShader(obj->gfx.shader);
  obj->gfx.shader = new_shader;

  mat4 model;
  identity(&model);
  set_uniform_mat4x4(obj->gfx.shader, "model\0", model.v);

  mat4 view;
  identity(&view);
  set_uniform_mat4x4(obj->gfx.shader, "view\0", view.v);

  mat4 projection;
  projection_mat4(&projection, (float)((float)gfx.scr_width / (float)gfx.scr_height), PI/4.0f, 1000.0f, 0.01f);
  set_uniform_mat4x4(obj->gfx.shader, "projection\0", projection.v);
}

void render_obj(object obj) {
  switch (obj.m) {
    case VERTS:
    {
      glBindVertexArray(obj.gfx.VAO);
      glUseProgram(obj.gfx.shader);
      glDrawArrays(GL_TRIANGLES, 0, obj.n);
      glBindVertexArray(0);
      glUseProgram(0);
    }
      break;
    case INDS:
    {
      glBindVertexArray(obj.gfx.VAO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.gfx.IBO);
      glUseProgram(obj.gfx.shader);
      glDrawElements(GL_TRIANGLES, obj.n, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glUseProgram(0);
    }
      break;
  }
}

void destroy_obj(object obj) {
  if (obj.verts != NULL) {
    free(obj.verts);
  }
  if (obj.inds != NULL) {
    free(obj.inds);
  }
}
