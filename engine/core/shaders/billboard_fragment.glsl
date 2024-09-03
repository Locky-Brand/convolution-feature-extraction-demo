#version 330 core
out vec4 aColor;

in vec2 oTex;

uniform sampler2D tex;
uniform vec2 tex_sub_size;
uniform vec2 tex_sub_offset;

void main(){

    aColor = texture(tex, vec2(oTex.x * tex_sub_size.x, oTex.y * tex_sub_size.y) + tex_sub_offset);
}