#include "entity.h"

// updator functions
void asset_updator(void* entity_ptr, void* data, int data_size) {

}
void shape_updator(void* entity_ptr, void* data, int data_size) {
  
}
void texture_updator(void* entity_ptr, void* data, int data_size) {
  
}
void billboard_updator(void* entity_ptr, void* data, int data_size) {
  vec3 tmp_pos = ((entity3D*)entity_ptr)->_transform.pos;
  set_uniform(((entity3D*)entity_ptr)->gfx_obj.gfx.shader, "pos", UVEC3, &tmp_pos);
}

// set texture
void set_texture(gfx3D gfx, object obj, Texture texture) {
  int tex = texture.index;
  vec2 sub_offset = texture.sub_offset;
  vec2 sub_size = (vec2){(float)texture.sizes.x / 1024.0f, (float)texture.sizes.y / 1024.0f};
  set_uniform(obj.gfx.shader, "tex", UI, (void*)(&tex));
  set_uniform(obj.gfx.shader, "tex_sub_offset", UVEC2, (void*)(&sub_offset));
  set_uniform(obj.gfx.shader, "tex_sub_size", UVEC2, (void*)(&sub_size));
}

// texture_index = -1 for solid color
entity3D create_entity(gfx3D gfx, entity_type type, unsigned int asset_index, int texture_index, unsigned char mutators) {
  entity3D out;

  out._type = type;
  out._mutators = mutators;

  out._transform.pos = (vec3){0.0f, 0.0f, 0.0f};
  out._transform.dir = (vec3){0.0f, 0.0f, 0.0f};
  out._transform.scale = (vec3){1.0f, 1.0f, 1.0f};
  identity(&out._transform.m);

  switch (type) {
    case ASSET:
      if (mutators & ASSET_CPY) {
        // copy object data from gfx
        out.gfx_obj = create_object(gfx, out.gfx_obj.verts, out.gfx_obj.inds, out.gfx_obj.nverts, out.gfx_obj.ninds, gfx.assets[asset_index].attribs, "./engine/core/shaders/vertex.glsl\0", "./engine/core/shaders/fragment.glsl\0", 1);
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);
        out._updator = asset_updator;

      }
      else {
        out.gfx_obj = create_object_asset3D(gfx, asset_index, "./engine/core/shaders/vertex.glsl\0", "./engine/core/shaders/fragment.glsl\0", 0);
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);
        out._updator = asset_updator;
      }

      if (mutators & DISABLE_LIGHTING) {
        recreate_obj_shader(gfx, &out.gfx_obj, create_shader_file("./engine/core/shaders/simple_vertex.glsl\0", "./engine/core/shaders/simple_fragment.glsl\0"));
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);
        out._updator = asset_updator;

      }
      
    break;
    case SHAPE:
    {
      if (mutators & ASSET_CPY) {
        // copy object data from gfx
        out.gfx_obj = create_object(gfx, out.gfx_obj.verts, out.gfx_obj.inds, out.gfx_obj.nverts, out.gfx_obj.ninds, gfx.shapes[asset_index].attribs, "./engine/core/shaders/vertex.glsl\0", "./engine/core/shaders/fragment.glsl\0", 1);
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);
        out._updator = shape_updator;
      }
      else {
        out.gfx_obj = create_object(gfx, gfx.shapes[asset_index].verts, gfx.shapes[asset_index].inds, gfx.shapes[asset_index].nverts, gfx.shapes[asset_index].ninds, gfx.shapes[asset_index].attribs, "./engine/core/shaders/vertex.glsl\0", "./engine/core/shaders/fragment.glsl\0", 0);
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);

        out._updator = shape_updator;
      }

      if (mutators & DISABLE_LIGHTING) {

        recreate_obj_shader(gfx, &out.gfx_obj, create_shader_file("./engine/core/shaders/simple_vertex.glsl\0", "./engine/core/shaders/simple_fragment.glsl\0"));
        set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);

        out._updator = shape_updator;
      }
    }
    break;
    case BILLBOARD:
    {
      float verts[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
      };
      unsigned int inds[] = {
        0, 1, 2, 2, 3, 0
      };

      render_elem elems[3];
      render_attribs attribs = default_attrib_list(elems);

      out.gfx_obj = create_object(gfx, verts, inds, 4, 6, attribs, "./engine/core/shaders/billboard_vertex.glsl\0", "./engine/core/shaders/billboard_fragment.glsl\0", 1);
      set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);

      vec3 tmp_pos = (vec3){0.0f, 0.0f, 0.0f};
      set_uniform(out.gfx_obj.gfx.shader, "pos", UVEC3, &tmp_pos);

      vec3 tmp_sze = (vec3){0.5f, 0.5f, 0.5f};
      set_uniform(out.gfx_obj.gfx.shader, "size", UVEC3, &tmp_sze);

      int lock_x = mutators & BILLBOARD_LOCK_X;
      set_uniform(out.gfx_obj.gfx.shader, "lock_x", UI, &lock_x);

      int lock_y = mutators & BILLBOARD_LOCK_Y;
      set_uniform(out.gfx_obj.gfx.shader, "lock_y", UI, &lock_y);

      out._updator = billboard_updator;
    }
    break;
    case TEXTURE:
    {
      float verts[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
      };
      unsigned int inds[] = {
        0, 1, 2, 2, 3, 0
      };

      render_elem elems[3];
      render_attribs attribs = default_attrib_list(elems);

      out.gfx_obj = create_object(gfx, verts, inds, 4, 6, attribs, "./engine/core/shaders/vertex.glsl\0", "./engine/core/shaders/fragment.glsl\0", 1);
      set_texture(gfx, out.gfx_obj, gfx.textures[texture_index]);

      out._updator = texture_updator;
    }
    break;
    default:

    break;
  }

  out._requires_update = 1;

  return out;
}

void update_entity(entity3D* e, void* data, int data_size) {

  e->_updator(e, data, data_size);

  if (!e->_requires_update) {
    return;
  }

  mat4 rotate;
  mat4 roll;
  mat4 pitch;
  mat4 yaw;
  identity(&rotate);
  rotate_mat4(&roll, e->_transform.dir.x, (vec3){1.0f, 0.0f, 0.0f});
  rotate_mat4(&pitch, e->_transform.dir.y, (vec3){0.0f, 1.0f, 0.0f});
  rotate_mat4(&yaw, e->_transform.dir.z, (vec3){0.0f, 0.0f, 1.0f});
  mul_mat4_3(&rotate, roll, pitch, yaw);

  mat4 scale;
  identity(&scale);
  scale_mat4(&scale, e->_transform.scale.x, e->_transform.scale.y, e->_transform.scale.z);

  mat4 translate;
  identity(&translate);
  translate_mat4(&translate, e->_transform.pos.x, e->_transform.pos.y, e->_transform.pos.z);

  mul_mat4_3(&e->_transform.m, translate, scale, rotate);

  set_uniform_mat4x4(e->gfx_obj.gfx.shader, "model", (float*)(e->_transform.m.v));

  e->_requires_update = 0;
}

void set_entity_pos(entity3D* e, vec3 pos) {
  e->_transform.pos = pos;
  e->_requires_update = 1;
}

void set_shader(gfx3D gfx, entity3D* e, unsigned int shader) {
  recreate_obj_shader(gfx, &e->gfx_obj, shader);
}

void destroy_entity(entity3D e) {
  destroy_obj(e.gfx_obj);
}