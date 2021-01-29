#version 330 core

out vec4 fragColor;
in vec3 passColor;
in vec2 passUV;

uniform sampler2D texture0;

void main() {
    //fragColor = vec4(passColor, 1.0);
    fragColor = texture(texture0, passUV);
}