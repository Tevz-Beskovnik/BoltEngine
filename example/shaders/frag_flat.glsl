#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexture0;
uniform vec4 uCol;

void main() {
    FragColor = texture(uTexture0, oUV) * uCol;
}