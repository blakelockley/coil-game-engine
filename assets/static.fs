#version 330 core

in vec3 fragPos;
in vec3 fragNormal;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

void main()
{
    vec3 ambient = ambientColor;
    
    vec3 viewPos = vec3(0, 0, 0);
    vec3 norm = normalize(fragNormal);
    
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
   
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * specularColor;

    vec3 baseColour = vec3(0.20f, 0.91f, 0.61f);
    vec3 result = (ambient + diffuse + specular) * baseColour;

    color = vec4(result, 1.0);
}