#version 330 core
layout (location = 0) in vec3 in_position;

uniform mat4 uni_pvmMatrix;

void main()
{
    gl_Position = uni_pvmMatrix * vec4(in_position, 1.0);
}