#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec2 oUV;

uniform uint uRotations[20];
uniform float uOffsets[20];
uniform int uTextureOffsets[20];

void main() {
    float texOffset = float(uTextureOffsets[int(gl_InstanceID)]);
    vec2 newUV = aUV;

    if(uRotations[gl_InstanceID] == uint(1)) {
        newUV.x = 1.0f - newUV.x;
    }

    newUV.x /= 11.05f;
    newUV.x += (texOffset / 11.0f);
    oUV = newUV;

    vec3 newPos = vec3(aPos.x + uOffsets[gl_InstanceID], aPos.yz);

    gl_Position = vec4(newPos, 1.0f);
}