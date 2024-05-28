#version 330 core
out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambientStrenght;
    vec3 diffuseStrenght;
    vec3 specularStrenght;
};

in vec3 normal;
in vec3 fragPos;

uniform vec3 camPos;
uniform Material material;
uniform Light light;  

void main(){
    // Ambient Lighting (constant small amount of light)
    vec3 ambientColor = light.ambientStrenght * material.ambient;

    // Diffuse Lighting (surface light reflection)
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos); 
    float lightIntensity = max(dot(norm, lightDir), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    vec3 diffuseColor = light.diffuseStrenght * (lightIntensity * material.diffuse);

    // Specular Lighting (Reflection of the lightSource)
    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specIntensity = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularColor = light.specularStrenght * (specIntensity * material.specular);

    // Final Color
    vec3 finalColor = ambientColor + diffuseColor + specularColor;
    FragColor = vec4(finalColor, 1.0f);
}