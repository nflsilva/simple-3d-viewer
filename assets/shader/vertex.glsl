#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;

out vec3 f_normal;

uniform mat4 uni_pvmMatrix;
uniform mat4 uni_modelMatrix;

void main()
{
    gl_Position = uni_pvmMatrix * vec4(v_position, 1.0);
    f_normal =  normalize((uni_modelMatrix * vec4(v_normal, 0.0)).xyz);;
}