#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uViewMat;

void main()
{
   vec4 res = (vec4(aPos, 1.0)) * uViewMat;
   gl_Position = res;
}