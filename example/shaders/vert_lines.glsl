#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;

out vec4 oColor;

uniform mat4 uViewMat;

void main() {
    vec4 res = (vec4(iPos, 1.0)) * uViewMat;
    oColor = iColor;
    gl_Position = res;
}