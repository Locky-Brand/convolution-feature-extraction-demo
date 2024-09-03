#include "point_light.h"

point_light create_point_light(vec3 pos, vec3 color, float brightness) {
    point_light out;

    out.pos = pos;
    out.color = color;
    out.intensity = brightness;
    out.requires_update = 0;
    
    return out;
}

void set_point_light_pos(point_light* light, vec3 pos) {
    light->pos = pos;
    light->requires_update = 1;
}