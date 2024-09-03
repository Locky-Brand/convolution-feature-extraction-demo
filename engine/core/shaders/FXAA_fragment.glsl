#version 330 core
out vec4 aColor;
in vec2 oTex;

#define EDGE_THRESHOLD_MIN 0.1
#define EDGE_THRESHOLD_MAX 1.0

uniform sampler2D screenTexture;

float rgb2luma(vec3 rgb){
    return sqrt(dot(rgb, vec3(0.299, 0.587, 0.114)));
}

void main(){

    vec3 colorCenter = texture(screenTexture, oTex).xyz;

    // Luma at the current fragment
    float lumaCenter = rgb2luma(colorCenter);

    // Luma at the four direct neighbours of the current fragment.
    //float lumaDown = rgb2luma(textureOffset(screenTexture, oTex,ivec2(0,-1)).rgb);
    //float lumaUp = rgb2luma(textureOffset(screenTexture, oTex,ivec2(0,1)).rgb);
    //float lumaLeft = rgb2luma(textureOffset(screenTexture, oTex,ivec2(-1,0)).rgb);
    //float lumaRight = rgb2luma(textureOffset(screenTexture, oTex,ivec2(1,0)).rgb);

    // Find the maximum and minimum luma around the current fragment.
    //float lumaMin = min(lumaCenter,min(min(lumaDown,lumaUp),min(lumaLeft,lumaRight)));
    //float lumaMax = max(lumaCenter,max(max(lumaDown,lumaUp),max(lumaLeft,lumaRight)));

    // Compute the delta.
    //float lumaRange = lumaMax - lumaMin;

    // If the luma variation is lower that a threshold (or if we are in a really dark area), we are not on an edge, don't perform any AA.
    //if(lumaRange < max(EDGE_THRESHOLD_MIN,lumaMax*EDGE_THRESHOLD_MAX)){
        //aColor = colorCenter;
        //return;
    //}

    aColor = vec4(0.76f, 0.76f, 0.76f, 1.0f);
}
