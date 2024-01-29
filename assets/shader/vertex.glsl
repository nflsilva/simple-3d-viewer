#version 110

in vec3 vin_position;
in vec3 vin_color;

uniform mat4 uni_modelMatrix;
uniform mat4 uni_viewMatrix;
uniform mat4 uni_projectionMatrix;

varying vec3 fin_color;

void main()
{
    vec4 worldPosition = uni_modelMatrix * vec4(vin_position, 1.0);
    gl_Position = uni_projectionMatrix * uni_viewMatrix * worldPosition;
    fin_color = vin_color;
};