#include "render.h"

void render_pass(gfx3D* g, scene3D s, camera3D* c) {
    // temporary render
    vec3_pair ru = perspective_lookat(&c->view, c->pos, c->targ);
    c->r = ru.a;
    c->u = ru.b;

    glBindFramebuffer(GL_FRAMEBUFFER, g->main_frame.ID);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < s.n; ++i) {
        set_uniform_mat4x4(s.objs[i]->gfx_obj.gfx.shader, "view\0", c->view.v);
        set_uniform(s.objs[i]->gfx_obj.gfx.shader, "view_pos\0", UVEC3, (void*)(&c->pos));

        render_obj(s.objs[i]->gfx_obj);
    }
}
void lighting_pass(gfx3D* g, scene3D s, camera3D c) {
    
}
void shadow_pass(gfx3D* g, scene3D s, camera3D c) {

}
void SSAO_pass(gfx3D* g, scene3D s, camera3D c) {

}
void FXAA_pass(gfx3D* g, scene3D s, camera3D c) {

}
void user_postprocess() {
    // render to screen from main_frame

    //g->write_buffer = &g->aux_buffer;
    //g->read_buffer = &g->main_frame;
}

void render(gfx3D* g, scene3D s, camera3D* c, unsigned char render_mutator) {
    render_pass(g, s, c);

    if (render_mutator & RENDERER_DRAW_SHADOWS) {
        shadow_pass(g, s, *c);
        SSAO_pass(g, s, *c);
    }

    if (render_mutator & RENDERER_ANTI_ALIAS) {
        FXAA_pass(g, s, *c);
    }

    if (render_mutator & RENDERER_USER_POSTPROCESS) {
        user_postprocess();
    }
}