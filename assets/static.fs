#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexture;

uniform vec3 color;
uniform vec3 emissive;

uniform vec3 lightPos;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform bool hasDiffuseTexture;
uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main()
{
    vec3 ambient = ambientColor;
    
    vec3 viewPos = vec3(0, 0, 0);
    vec3 norm = normalize(fragNormal);
    
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * specularColor;

    vec3 texColor = color;
    if (hasDiffuseTexture)
         texColor *= vec3(texture(diffuseTexture, fragTexture));

    vec3 result = ((ambient + diffuse + specular) * texColor) + emissive;

    FragColor = vec4(result, 1.0);
}