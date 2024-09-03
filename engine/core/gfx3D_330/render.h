#ifndef RENDER_H
#define RENDER_H

#include "../renderer.h"
#include "../objects/scene3D.h"
#include "../objects/camera3D.h"

// rendering options
#define RENDERER_ANTI_ALIAS 0b00000001
#define RENDERER_USER_POSTPROCESS 0b00000010
#define RENDERER_DRAW_SHADOWS 0b00000100

// rendering pipeline
void render_pass(gfx3D* g, scene3D s, camera3D* c);
void lighting_pass(gfx3D* g, scene3D s, camera3D c);
void shadow_pass(gfx3D* g, scene3D s, camera3D c);
void SSAO_pass(gfx3D* g, scene3D s, camera3D c);
void FXAA_pass(gfx3D* g, scene3D s, camera3D c);
void user_postprocess();

void render(gfx3D* g, scene3D s, camera3D* c, unsigned char render_mutator);

#endif