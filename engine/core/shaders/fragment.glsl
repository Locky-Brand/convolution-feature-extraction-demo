#version 330 core
out vec4 aColor;

in vec3 frag_pos;
in vec2 oTex;
in vec3 oNorm;

uniform sampler2D tex;
uniform vec2 tex_sub_size;
uniform vec2 tex_sub_offset;

// lighting
uniform vec3 ambient_light;
uniform float ambient_light_intensity;

uniform vec3 view_pos;

struct Light {
    vec3 pos;
    vec3 color;
    float intensity;
};
uniform Light lights; 

void main(){

    vec4 object_color = texture(tex, vec2(oTex.x * tex_sub_size.x, oTex.y * tex_sub_size.y) + tex_sub_offset);

    vec3 ambient = ambient_light_intensity * ambient_light;
    float specular_strength = 0.5;

    vec3 light_dir = normalize(lights.pos - frag_pos);
    float diff = max(dot(oNorm, light_dir), 0.0);
    vec3 diffuse = diff * lights.color * lights.intensity;

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, oNorm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * lights.color;  

    aColor = vec4((ambient + diffuse + specular) * object_color.xyz, object_color.w);
}