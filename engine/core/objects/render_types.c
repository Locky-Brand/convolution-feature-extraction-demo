#include "render_types.h"

render_attribs attrib_list(render_elem* elems, unsigned int count) {
  return (render_attribs){elems, count};
}

render_attribs default_attrib_list(render_elem* elems) {

  elems[0] = (render_elem){VERT, 3};
  elems[1] = (render_elem){NORMAL, 3};
  elems[2] = (render_elem){TEX_COORD, 2};

  return (render_attribs){elems, 3};
}

unsigned int get_vert_stride_from_attribs(render_attribs attribs) {
  unsigned int sum = 0;
  for (unsigned int i = 0; i < attribs.n_elems; ++i) {
    sum += attribs.elems[i].float_count;
  }
  return sum;
}
