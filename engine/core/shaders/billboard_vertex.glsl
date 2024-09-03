#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aTex;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 pos;
uniform vec3 size;
uniform int lock_x;
uniform int lock_y;

uniform vec2 scr_wh;

out vec2 oTex;

void main(){
    oTex = aTex;
    
    vec3 cam_right = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 cam_up = vec3(view[0][1], view[1][1], view[2][1]);

    vec3 vert_pos = pos + vec3(1.0f, 0.0f, 0.0f) * aPos.x * size.x + vec3(0.0f, 1.0f, 0.0f) * aPos.y * size.y;
    bool lx = bool(lock_x);
    bool ly = bool(lock_y);
    if (lx) {
        vert_pos = vert_pos - vec3(1.0f, 0.0f, 0.0f) * aPos.x * size.x;
        vert_pos = vert_pos + cam_right * aPos.x * size.x;
    }
    if (ly) {
        vert_pos = vert_pos - vec3(0.0f, 1.0f, 0.0f) * aPos.y * size.y;
        vert_pos = vert_pos + cam_up * aPos.y * size.y;
    }

    gl_Position = projection * view * vec4(vert_pos, 1.0f);
}