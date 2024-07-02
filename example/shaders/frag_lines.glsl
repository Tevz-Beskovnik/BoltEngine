#version 330 core

out vec4 FragColor;

in vec4 oColor;

void main() {
    FragColor = oColor;
}