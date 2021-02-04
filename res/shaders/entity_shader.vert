#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normals;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec2 p_uv;
out vec3 p_position;

void main() {
    gl_Position = projection * view * transform * vec4(position, 1.0);

    // variables passed to fragment shader
    p_position = gl_Position.xyz;
    p_uv = uv;
}