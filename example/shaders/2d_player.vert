#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec2 oUV;

uniform vec3 uTranslation;

void main() {
    oUV = aUV;
    gl_Position = vec4(aPos, 1.0f) + vec4(uTranslation, 1.0f);;
}