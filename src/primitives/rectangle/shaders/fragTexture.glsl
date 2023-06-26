#version 330 core

out vec4 FragColor;

in vec2 oUV;

void main()
{
    FragColor = texture(%i, oUV) * vec4(uColor, 10.0);
}