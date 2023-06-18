#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexture;
uniform vec3 uColor;

void main() {
    FragColor = texture(uTexture, oUV) * vec4(uColor, 1.0);
}