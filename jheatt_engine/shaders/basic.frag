#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform float swap_amount;

void main()
{
    outColor = mix(texture(tex, Texcoord), texture(tex2, Texcoord), swap_amount);
}