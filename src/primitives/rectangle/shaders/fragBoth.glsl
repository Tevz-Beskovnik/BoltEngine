#version 330 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexture;
uniform vec3 uColor;

void main() {
    FragColor = texture(%i, oUV) * vec4(%f, %f, %f, %f);
}