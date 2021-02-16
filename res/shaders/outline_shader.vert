#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 world_position = transform * vec4(position, 1.0);
    gl_Position = projection * view * world_position;
}
