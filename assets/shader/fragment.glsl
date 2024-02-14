#version 330 core

in vec3 f_normal;

out vec4 FragColor;

vec3 lightVector = vec3(1f);
vec4 lightColor = vec4(1f);
vec4 materialColor = vec4(1f);
float ambientCoefficient = 0.2f;

vec4 processLight(float dotNormalLight){
    float diffuseComponent = max(dotNormalLight, 0.0);
    return diffuseComponent * lightColor;
}

void main()
{
    float dotNormalLight = dot(f_normal, normalize(-lightVector));

    vec4 diffuseComponent = processLight(dotNormalLight);

    vec4 ambientColor = materialColor * ambientCoefficient;
    vec4 diffuseColor = diffuseComponent * materialColor;

    FragColor = mix(diffuseColor, ambientColor, ambientCoefficient);
} 