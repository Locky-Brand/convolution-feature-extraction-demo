#version 330 core
out vec4 aColor;
in vec2 oTex;
uniform sampler2D main_frame;

uniform mat3 conv;
uniform vec2 screen_wh;
uniform int greyscale;

float rgba2luma(vec4 rgba){
    return sqrt(dot(rgba.xyz, vec3(0.299, 0.587, 0.114))) * rgba.w;
}

void main(){

    vec4 outpix;
    if (greyscale == 1) {
        float nu = rgba2luma(texture(main_frame, vec2(oTex.x, oTex.y + 1.0f/screen_wh.y)));
        float nd = rgba2luma(texture(main_frame, vec2(oTex.x, oTex.y - 1.0f/screen_wh.y)));

        float nul = rgba2luma(texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y + 1.0f/screen_wh.y)));
        float ndl = rgba2luma(texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y - 1.0f/screen_wh.y)));
        float nl = rgba2luma(texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y)));

        float nur = rgba2luma(texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y + 1.0f/screen_wh.y)));
        float ndr = rgba2luma(texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y - 1.0f/screen_wh.y)));
        float nr = rgba2luma(texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y)));

        outpix.x = nul * conv[0][0] + nu * conv[1][0] + nur * conv[2][0] +
                   nl * conv[0][1] +  rgba2luma(texture(main_frame, oTex)) * conv[1][1] + nr * conv[2][1] +
                   ndl * conv[0][2] + nd * conv[1][2] + ndr * conv[2][2];

        aColor = vec4(outpix.x, outpix.x, outpix.x, 1.0f);
    }
    else {
        vec4 nu = (texture(main_frame, vec2(oTex.x, oTex.y + 1.0f/screen_wh.y)));
        vec4 nd = (texture(main_frame, vec2(oTex.x, oTex.y - 1.0f/screen_wh.y)));

        vec4 nul = (texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y + 1.0f/screen_wh.y)));
        vec4 ndl = (texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y - 1.0f/screen_wh.y)));
        vec4 nl = (texture(main_frame, vec2(oTex.x - 1.0f/screen_wh.x, oTex.y)));

        vec4 nur = (texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y + 1.0f/screen_wh.y)));
        vec4 ndr = (texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y - 1.0f/screen_wh.y)));
        vec4 nr = (texture(main_frame, vec2(oTex.x + 1.0f/screen_wh.x, oTex.y)));

        outpix = nul * conv[0][0] + nu * conv[1][0] + nur * conv[2][0] +
                   nl * conv[0][1] +  (texture(main_frame, oTex)) * conv[1][1] + nr * conv[2][1] +
                   ndl * conv[0][2] + nd * conv[1][2] + ndr * conv[2][2];

        aColor = vec4(outpix.x, outpix.y, outpix.z, 1.0f);
    }
    

    
};