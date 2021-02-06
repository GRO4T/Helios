#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    vec4 base_color;
    sampler2D texture;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

uniform Material material;
uniform PointLight light;
uniform vec3 camera_position;

out vec4 frag_color;

in vec2 p_uv;
in vec3 p_world_position;
in vec3 p_normal;

void main() {
    vec4 texture_color = texture(material.texture, p_uv);

    vec3 normal = normalize(p_normal);
    vec3 light_dir = normalize(light.position - p_world_position);
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * max(dot(normal, light_dir), 0.0) * material.diffuse;
    vec3 camera_dir = normalize(camera_position - p_world_position);
    vec3 reflect_dir = reflect(-light_dir, normal);
    vec3 specular = light.specular * pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess) * material.specular;

    vec3 result = (diffuse + ambient + specular) * texture_color.xyz;
    frag_color = vec4(result, 1.0);

}