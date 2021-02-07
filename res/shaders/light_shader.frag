#version 330 core

out vec4 frag_color;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main() {
    vec3 result = (light.ambient + light.diffuse + light.specular) / 2.0;
    frag_color = vec4(result, 1.0);
}