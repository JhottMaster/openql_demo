#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform float brightness;

void main()
{
    outColor = (texture(tex, Texcoord) * vec4(Color, 1.0)) * brightness;
}