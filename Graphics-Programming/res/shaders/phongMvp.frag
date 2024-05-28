#version 330 core
out vec4 FragColor;

struct Light {
    vec3 position;
  
    vec3 ambientStrenght;
    vec3 diffuseStrenght;
    vec3 specularStrenght;
};

struct Material {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
}; 

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;  

void main(){
    // Ambient Lighting (constant small amount of light)
    vec3 ambientColor = light.ambientStrenght * texture(material.diffuseTexture, texCoord).rgb; // Read texture uv and multiply it with light.ambientStrenght

    // Diffuse Lighting (surface light reflection)
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos); 
    float diffuseIntensity = max(dot(norm, lightDir), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    vec3 diffuseColor = light.diffuseStrenght * diffuseIntensity * texture(material.diffuseTexture, texCoord).rgb; // Read texture uv and multiply it with light.diffuseStrenght and diffuseIntensity

    // Specular Lighting (Reflection of the lightSource)
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularColor = light.specularStrenght * specularIntensity * texture(material.specularTexture, texCoord).rgb; // Read texture uv and multiply it with light.specularStrenght and diffuseIntensity

    // Final Color
    vec3 finalColor = ambientColor + diffuseColor + specularColor;
    FragColor = vec4(finalColor, 1.0f);
}