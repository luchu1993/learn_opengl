#version 430 core

out vec4 fColor;
in vec2 TexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;

void main()
{
    fColor = mix(texture(sampler0, TexCoord), texture(sampler1, TexCoord), 0.2f);
}