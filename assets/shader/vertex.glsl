#version 330 core
layout (location = 0) in vec3 in_position;

uniform mat4 uni_projectionMatrix;
uniform mat4 uni_viewMatrix;
uniform mat4 uni_modelMatrix;

void main()
{
    gl_Position = uni_projectionMatrix * uni_viewMatrix * uni_modelMatrix * vec4(in_position, 1.0);
}