#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
    vec4 base_color;
    sampler2D texture;
};

uniform Material material;

out vec4 frag_color;
in vec2 p_uv;
in vec3 p_position;

void main() {
    vec4 texture_color = texture(material.texture, p_uv);
    //vec4 ambient_color = texture_color * material.base_color;
    vec4 ambient_color = mix(texture_color, material.base_color, material.base_color.a);
    frag_color = ambient_color;
}