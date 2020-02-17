#version 330 core

in vec3 Normal;
in vec2 Texcoord;

out vec4 outColor;

uniform vec3 ambientLightColor;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform float swap_amount;

void main()
{
    vec4 textureColor = mix(texture(tex, Texcoord), texture(tex2, Texcoord), swap_amount);
    outColor = textureColor * vec4(ambientLightColor, 1.0f);
}