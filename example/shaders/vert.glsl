#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uViewMat;

void main()
{
   vec4 res = uViewMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = res;
}