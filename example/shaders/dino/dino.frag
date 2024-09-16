#version 410 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTextureDino;

void main() {
    vec4 texColor = texture(uTextureDino, oUV);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}