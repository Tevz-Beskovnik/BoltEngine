#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uViewMat;

mat4 view = mat4(
   0.75, 0, 0, 0,
   0, 1, 0, 0,
   0, 0, 1.0001, 1,
   0, -3, 7.90079, 8
);
mat4 trans = mat4(
   0.60582, 0, 0.795601, 0,
   -0.409047, 0.857709, 0.311474, 0,
   -0.682394, -0.514136, 0.519617, 0,
   0, 0, 0, 1
);


void main()
{
   vec4 res = (vec4(aPos, 1.0)) * uViewMat;
   gl_Position = res;
}