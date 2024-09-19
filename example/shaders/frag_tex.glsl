#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexturePlayer;

void main() {
    FragColor = texture(uTexturePlayer, oUV);
}