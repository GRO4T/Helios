#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec2 p_uv;
out vec3 p_world_position;
out vec3 p_normal;

void main() {
    vec4 world_position = transform * vec4(position, 1.0);
    gl_Position = projection * view * world_position;

    // variables passed to fragment shader
    p_world_position = vec3(world_position);
    p_uv = uv;
    p_normal = mat3(transpose(inverse(transform))) * normal;
}