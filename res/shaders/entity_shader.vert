#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 passColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    passColor = vec3(1.0, 1.0, 0.0);
}