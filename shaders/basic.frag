#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 viewPos;

in vec3 Normal; 
in vec3 FragPos; 

void main()
{
    //Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * material.ambient;

    //Difuse
    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse;

    //Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * material.specular;   

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
} 