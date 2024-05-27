#version 330 core
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

in vec3 normal;
in vec3 fragPos;

void main()
{
    // Ambient Lighting (constant small amount of light)
    float ambientStrength = 0.05f;
    vec3 ambientColor = ambientStrength * lightColor;

    // Diffuse Lighting (surface light reflection)
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - fragPos); 
    float lightIntensity = max(dot(norm, lightDirection), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    vec3 diffuseColor = lightIntensity * lightColor.rgb;

    //vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);

    // Final Color
    vec3 finalColor = (ambientColor + diffuseColor) * objectColor;
    FragColor = vec4(finalColor, 1.0f);
}