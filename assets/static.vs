#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexture;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexture;

uniform mat4 transformationMatrix;
uniform mat4 normalMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 worldPosition = transformationMatrix * vec4(vPos, 1.0);
    gl_Position = projectionMatrix * worldPosition;

    fragPos = vec3(transformationMatrix * vec4(vPos, 1.0));
    fragNormal =  mat3(normalMatrix) * vNormal;
    fragTexture = vTexture;
}