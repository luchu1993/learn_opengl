#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
out vec3 fNormal;
out vec3 fPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fNormal = mat3(transpose(inverse(model))) * vNormal;
    fPosition = (model * vPosition).xyz;
    gl_Position = projection * view * vec4(fPosition, 1.0f);
}