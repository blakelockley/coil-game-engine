#version 330 core

in vec3 fragmentNormal;

out vec4 color;

void main()
{
    vec3 baseColour = vec3(0.20f, 0.91f, 0.61f);
    color = vec4(baseColour, 1.0);
}