#version 330 core

struct Light {
    vec4 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexture;

uniform vec3 color;
uniform vec3 emissive;

uniform Light light;

uniform bool hasDiffuseTexture;
uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main()
{
    vec3 position = vec3(light.position);

    float dist = length(position - fragPos);
    float attenuation = 1.0 /
        (light.constant + light.linear * dist + light.quadratic * (dist * dist));  
    
    attenuation = pow(attenuation, light.position.w);
    
    vec3 viewPos = vec3(0, 0, 0);
    vec3 norm = normalize(fragNormal);
    
    vec3 lightDir = normalize(position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    
    vec3 ambient = light.ambient * attenuation;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * attenuation;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * light.specular * attenuation;

    vec3 texColor = color;
    if (hasDiffuseTexture)
         texColor *= vec3(texture(diffuseTexture, fragTexture));

    vec3 result = ((ambient + diffuse + specular) * texColor) + emissive;
    FragColor = vec4(result, 1.0);
}