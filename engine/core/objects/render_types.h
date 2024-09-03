#ifndef RENDER_TYPES_H
#define RENDER_TYPES_H

typedef enum {
  VERT,
  TEX_COORD,
  COLOR,
  NORMAL
} render_elem_type;

typedef struct {
  render_elem_type t;
  unsigned int float_count;
} render_elem;

typedef struct {
  render_elem* elems;
  unsigned int n_elems;
} render_attribs;

render_attribs attrib_list(render_elem* elems, unsigned int count);
render_attribs default_attrib_list(render_elem* elems);

unsigned int get_vert_stride_from_attribs(render_attribs attribs);

#endif
