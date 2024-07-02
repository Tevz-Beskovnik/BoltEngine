#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexture;

void main() {
    FragColor = texture(uTexture, oUV);
}