#version 330 core
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 camPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    // Ambient Lighting (constant small amount of light)
    float ambientStrength = 0.05f;
    vec3 ambientColor = ambientStrength * lightColor;

    // Diffuse Lighting (surface light reflection)
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos); 
    float lightIntensity = max(dot(norm, lightDir), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    vec3 diffuseColor = lightIntensity * lightColor.rgb;

    // Specular Lighting (Reflection of the lightSource)
    float specularStrength = 0.5f;
    int shininess = 32;
    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specIntensity = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specularColor = specularStrength * specIntensity * lightColor;

    // Final Color
    vec3 finalColor = (ambientColor + diffuseColor + specularColor) * objectColor;
    FragColor = vec4(finalColor, 1.0f);
}