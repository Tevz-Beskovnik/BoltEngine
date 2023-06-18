#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec2 oUV;

uniform mat4 uViewMat;

void main()
{
   vec4 res = (vec4(aPos, 1.0)) * uViewMat;
   oUV = aUV;
   gl_Position = res;
}