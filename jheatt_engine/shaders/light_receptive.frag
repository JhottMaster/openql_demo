#version 330 core

in vec3 Normal;
in vec2 Texcoord;
in vec3 FragPos;

out vec4 outColor;

uniform sampler2D tex;

uniform float lightRadius;
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 ambientLightColor;
uniform mat4 view;

void main()
{

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    float attenuation = max((lightRadius-distance(lightPos, FragPos)), 0) / lightRadius;
    vec3 diffuse = (diff * lightColor) * attenuation;
    

    vec4 lightingEffect = vec4(diffuse, 1.0) + vec4(ambientLightColor, 1.0f);
    outColor =  texture(tex, Texcoord) * lightingEffect;
}