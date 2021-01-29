#version 330 core

out vec4 fragColor;
in vec3 passColor;

void main() {
    fragColor = vec4(passColor, 1.0);
}