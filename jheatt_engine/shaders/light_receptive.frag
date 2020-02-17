#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 lightColor;

void main()
{
    outColor =  texture(tex, Texcoord) * vec4(lightColor, 1.0);
}