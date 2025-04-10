#version 410 core

out vec4 FragColor;

in vec2 oUV;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, oUV);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}
