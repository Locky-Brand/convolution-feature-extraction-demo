#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "../math/vec3.h"
#include "../math/vec4.h"

typedef struct {
    vec3 pos;
    vec3 color;
    float intensity;

    int requires_update;
} point_light;

point_light create_point_light(vec3 pos, vec3 color, float brightness);

void set_point_light_pos(point_light* light, vec3 pos);

#endif