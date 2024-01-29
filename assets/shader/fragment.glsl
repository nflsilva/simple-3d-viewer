#version 110

varying vec3 fin_color;

void main()
{
    gl_FragColor = vec4(fin_color, 1.0);  
};