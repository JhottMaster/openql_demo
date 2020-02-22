#version 330 core

in vec3 Normal;
in vec2 Texcoord;
in vec3 FragPos;

out vec4 outColor;

struct Material {
    sampler2D diffuse_texture;
    sampler2D specular_texture;
    float shininess;
};
uniform Material material;

struct Light {
    bool is_directional;
    vec2 constants;

    vec3 position;
    vec3 light_direction;
    vec3 view_position;

    vec3 color;
    float attenuation;
    float radius;
};
uniform Light light;  

uniform mat4 view;
uniform vec3 ambient_light_color;

void main()
{
    // Precalculate fragment normal and light direction which we'll use for other calculations:
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.is_directional ? -light.light_direction : (light.position - FragPos));  
        
    // Calculate diffuse (color of material) lighting 
    vec3 texture_sample_color = vec3(texture(material.diffuse_texture, Texcoord));
    vec3 diffuse  = light.color *  max(dot(norm, lightDir), 0.0) * texture_sample_color;  

    // Ambient lighting: 
    vec3 ambient = ambient_light_color * texture_sample_color;

    // Specular:
    vec3 viewDir = normalize(light.view_position - FragPos);
    float spec = pow(max(dot(viewDir, reflect(-lightDir, norm)), 0.0), 32);
    vec3 specular = material.shininess * spec * vec3(texture(material.specular_texture, Texcoord));
    
    // Attenuation impact:
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0f + light.constants[0] * distance + light.constants[1] * (distance * distance));
    diffuse *= attenuation;
    specular *= attenuation;

    outColor = vec4(ambient + diffuse + specular, 1.0);   
}