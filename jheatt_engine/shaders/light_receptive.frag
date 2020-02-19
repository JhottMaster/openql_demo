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
uniform vec3 viewPos;

void main()
{
    vec3 norm = normalize(Normal);
    
    // Calculate diffuse lighting:
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    
    float attenuation = max((lightRadius-distance(lightPos, FragPos)), 0) / lightRadius;
    vec3 diffuse = (diff * lightColor) * attenuation;
    
    // Calculate specular lighting:
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec4 lightingEffect = vec4((ambientLightColor + diffuse + specular), 1.0);
    outColor =  texture(tex, Texcoord) * lightingEffect;
}