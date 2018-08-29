#version 430 core

out vec4 fColor;
uniform vec4 LightColor;

void main()
{
    fColor = LightColor;
}