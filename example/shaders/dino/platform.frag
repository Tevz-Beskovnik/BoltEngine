#version 410 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexturePlatform;

void main() {
    vec4 texColor = texture(uTexturePlatform, vec2(oUV.x, oUV.y));
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}