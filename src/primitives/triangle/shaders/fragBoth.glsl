#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTex;

void main() {
    FragColor = texture(uTex, oUV) * vec4(%f, %f, %f, %f);
}