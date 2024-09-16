#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec2 oUV;

uniform vec2 uTranslation;
uniform bool uRotation;

void main() {
    oUV = aUV;
    if(uRotation == bool(1)) {
        oUV.x = 1 - oUV.x;
    }

    gl_Position = vec4(aPos.xy + uTranslation, aPos.z, 1.0f);
}