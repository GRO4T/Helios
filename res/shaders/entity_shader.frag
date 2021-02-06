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

struct PointLight {
    float ambient;
    float diffuse;
    float specular;
    vec3 color;
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
    vec4 object_color = mix(texture_color, material.base_color, material.base_color.a);

    vec3 normal = normalize(p_normal);
    vec3 light_dir = normalize(light.position - p_world_position);
    float ambient = light.ambient;
    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 camera_dir = normalize(camera_position - p_world_position);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = light.specular * pow(max(dot(camera_dir, reflect_dir), 0.0), 32);

    vec3 result = (diffuse + ambient + specular) * light.color * object_color.rgb;
    frag_color = vec4(result, 1.0);

}