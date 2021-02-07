#version 330 core

struct Material {
    vec3 ambient;
    bool is_diffuse_map;
    sampler2D diffuse_map;
    vec3 diffuse;
    bool is_specular_map;
    sampler2D specular_map;
    vec3 specular;
    float shininess;
};

struct GlobalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    bool enabled;
};

struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;
    float constant;
    float linear;
    float quadratic;
    bool enabled;
};

#define NR_POINT_LIGHTS 4
#define NR_SPOT_LIGHTS 3

uniform Material material;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform DirLight dir_light;
uniform SpotLight spot_lights[NR_SPOT_LIGHTS];
uniform GlobalLight global_light;
uniform vec3 camera_position;

out vec4 frag_color;

in vec2 p_uv;
in vec3 p_world_position;
in vec3 p_normal;

vec3 material_ambient;
vec3 material_diffuse;
vec3 material_specular;
vec3 normal;
vec3 camera_dir;

vec3 calculateGlobalLight(GlobalLight light);
vec3 calculatePointLight(PointLight light);
vec3 calculateDirLight(DirLight light);
vec3 calculateSpotLight(SpotLight light);
void calculateMaterial(out vec3 material_ambient, out vec3 material_diffuse, out vec3 material_specular);

void main() {
    normal = normalize(p_normal);
    camera_dir = normalize(camera_position - p_world_position);
    calculateMaterial(material_ambient, material_diffuse, material_specular);
    vec3 result = vec3(0.0);
    result += calculateGlobalLight(global_light);
    result += calculateDirLight(dir_light);
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        if (point_lights[i].enabled)
        result += calculatePointLight(point_lights[i]);
    }
    for (int i = 0; i < NR_SPOT_LIGHTS; i++) {
        if (spot_lights[i].enabled)
        result += calculateSpotLight(spot_lights[i]);
    }
    frag_color = vec4(result, 1.0);
}

vec3 calculateGlobalLight(GlobalLight light) {
    vec3 ambient = light.ambient * material_ambient;
    vec3 diffuse = light.diffuse * material_diffuse;
    vec3 specular = light.specular * material_specular;
    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight light) {
    vec3 light_dir = normalize(light.position - p_world_position);
    vec3 ambient = light.ambient * material_ambient;
    vec3 diffuse = light.diffuse * max(dot(normal, light_dir), 0.0) * material_diffuse;
    vec3 reflect_dir = reflect(-light_dir, normal);
    vec3 specular = light.specular * pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess) * material_specular;
    float distance = length(light.position - p_world_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return (diffuse + ambient + specular) * attenuation;
}

vec3 calculateDirLight(DirLight light) {
    vec3 light_dir = normalize(-light.direction);
    vec3 ambient = light.ambient * material_ambient;
    vec3 diffuse = light.diffuse * max(dot(normal, light_dir), 0.0) * material_diffuse;
    vec3 reflect_dir = reflect(-light_dir, normal);
    vec3 specular = light.specular * pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess) * material_specular;

    return (diffuse + ambient + specular);
}

vec3 calculateSpotLight(SpotLight light) {
    vec3 light_dir = normalize(light.position - p_world_position);
    float theta = dot(light_dir, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * material_ambient;
    vec3 diffuse = light.diffuse * max(dot(normal, light_dir), 0.0) * material_diffuse;
    vec3 reflect_dir = reflect(-light_dir, normal);
    vec3 specular = light.specular * pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess) * material_specular;

    float distance = length(light.position - p_world_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return (diffuse + ambient + specular) * intensity * attenuation;
}

void calculateMaterial(out vec3 material_ambient, out vec3 material_diffuse, out vec3 material_specular) {
    if (material.is_diffuse_map) {
        material_diffuse = texture(material.diffuse_map, p_uv).xyz;
        material_ambient = material_diffuse;
    }
    else {
        material_diffuse = material.diffuse;
        material_ambient = material.ambient;
    }
    if (material.is_specular_map) {
        material_specular = texture(material.specular_map, p_uv).xyz;
    }
    else {
        material_specular = material.specular;
    }
}

