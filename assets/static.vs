#version 330 core

layout(location = 0) in vec3 vertex;

out vec3 fragmentColor;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 worldPosition = transformationMatrix * vec4(vertex, 1.0);
    gl_Position = projectionMatrix * worldPosition;

    fragmentColor = vertex;
}