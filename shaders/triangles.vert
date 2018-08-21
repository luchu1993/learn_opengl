#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec3 Color;
out vec2 TexCoord;

void main()
{
    gl_Position = vPosition;
    Color = vColor;
    TexCoord = vTexCoord;
}