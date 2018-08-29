#version 430 core

out vec4 fColor;
in vec3 fNormal;
in vec3 fPosition;

uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform vec4 LightColor;
uniform vec4 ObjectColor;

void main()
{
    vec4 ambient = 0.1f * LightColor;
    // diffuse
    vec3 L = normalize(LightPos - fPosition);
    vec3 N = normalize(fNormal);
    // lambert
    // vec4 diffuse = max(0.0f, dot(N, L)) * ObjectColor * LightColor;
    // == half lambert 
    vec4 diffuse = (0.5f * dot(N, L) + 0.5f) * ObjectColor * LightColor;
    // specular
    vec3 R = -L + 2.0f * dot(L, N) * N;
    vec3 V = normalize(ViewPos - fPosition);
    vec4 specular = pow(max(0, dot(R, V)), 8) * LightColor;

    fColor = ambient + diffuse +specular;
}