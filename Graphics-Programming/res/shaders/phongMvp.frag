#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient Lighting
    float ambientStrength = 0.1f;
    vec3 ambientAmount = ambientStrength * lightColor;
    vec3 fragColor = ambientAmount * objectColor;
    FragColor = vec4(fragColor, 1.0f);
}