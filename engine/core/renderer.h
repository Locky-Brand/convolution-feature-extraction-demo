#ifndef RENDERER_H
#define RENDERER_H

#if defined GL330

#include "gfx3D_330/gfx3D_330.h"

#elif defined GL210

#include "gfx3D_210/gfx3D_210.h"

#elif defined SOFT

#include "gfx3D_soft/gfx3D_soft.h"

#elif defined ARDUINO

// embedded

#else

#include "gfx3D_330/gfx3D_330.h"

#endif

#endif
