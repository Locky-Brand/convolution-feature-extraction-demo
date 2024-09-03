#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "../math/vec3.h"

typedef struct {
    vec3 color;
    float intensity;
} ambient_light;

#endif