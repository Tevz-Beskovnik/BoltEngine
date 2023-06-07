#version 330 core

out vec4 FragColor;

uniform vec3 uColor;
uniform float uTime;

void main()
{
    vec2 resolution = vec2(600, 800);
    vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / resolution.y;
    float d = length(uv);
    vec3 col = uColor;
    d = sin(d*8. + uTime)/8.;
    d = abs(d);
    d = 0.02/d;
    col *= d;
    FragColor = vec4(col, 1.0);
}