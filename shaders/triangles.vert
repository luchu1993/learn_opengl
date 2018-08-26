#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vPosition;
    TexCoord = vTexCoord;
}