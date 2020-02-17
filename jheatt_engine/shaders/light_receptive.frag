#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 ambientLightColor;

void main()
{
    vec4 lightingEffect = vec4(lightColor, 1.0) + vec4(ambientLightColor, 1.0f);
    outColor =  texture(tex, Texcoord) * lightingEffect;
}