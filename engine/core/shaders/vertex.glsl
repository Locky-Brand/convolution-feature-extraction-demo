#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 scr_wh;

out vec3 frag_pos;
out vec2 oTex;
out vec3 oNorm;
void main(){
    oTex = aTex;
    oNorm = aNorm;
    frag_pos = (model * vec4(aPos, 1.0f)).xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}