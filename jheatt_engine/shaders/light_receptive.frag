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
    bool is_spotlight;
    vec2 constants;

    vec3 position;
    vec3 light_direction;
    float spotlight_cutoff;
    float spotlight_inner_cutoff;

    vec3 color;
    float attenuation;
    float radius;
};

#define MAXIMUM_DYNAMIC_LIGHTS 32
uniform Light dynamic_lights[MAXIMUM_DYNAMIC_LIGHTS]; 
uniform int number_of_dynamic_lights;

uniform vec3 camera_view_position;
uniform vec3 ambient_light_color;

vec3 CalculateLightMultiplier(Light light, vec3 normal, vec3 fragment_position, vec3 diffuse_sample, vec3 view_direction);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 diffuse_sample = vec3(texture(material.diffuse_texture, Texcoord));
    vec3 view_direction = normalize(camera_view_position - FragPos);

    // Ambient lighting: 
    vec3 result = ambient_light_color * diffuse_sample;

    for(int i = 0; i < number_of_dynamic_lights; i++) {
        result += CalculateLightMultiplier(dynamic_lights[i], normal, FragPos, diffuse_sample, view_direction);
    }
        
    outColor = vec4(result, 1.0);
}

vec3 CalculateLightMultiplier(Light light, vec3 normal, vec3 fragment_position, vec3 diffuse_sample, vec3 view_direction)
{
    // Precalculate fragment normal and light direction which we'll use for other calculations:
    vec3 lightDir = normalize(light.is_directional ? -light.light_direction : (light.position - fragment_position));  
        
    // Calculate diffuse (color of material) lighting 
    vec3 diffuse  = light.color *  max(dot(normal, lightDir), 0.0) * diffuse_sample;  

    // Specular:
    float spec = pow(max(dot(view_direction, reflect(-lightDir, normal)), 0.0), 32);
    vec3 specular = material.shininess * spec * vec3(texture(material.specular_texture, Texcoord));
    
    // Attenuation impact:
    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (1.0f + light.constants[0] * distance + light.constants[1] * (distance * distance));
    diffuse *= attenuation;
    specular *= attenuation;

    if (light.is_spotlight) {
        // Everything outside the spotlight should be dark:
        float intensity = 0.0;

        // If we're inside the spotlight, calculate edges and light intensity:
        float theta = dot(lightDir, normalize(-light.light_direction));
        if(theta > light.spotlight_cutoff) {
            float epsilon = light.spotlight_inner_cutoff - light.spotlight_cutoff;
            intensity = clamp((theta - light.spotlight_cutoff) / epsilon, 0.0, 1.0);    
        }
        diffuse *= intensity;
        specular *= intensity;
    }
    
    return (diffuse + specular);   
}

