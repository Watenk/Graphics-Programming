#version 330 core
out vec4 FragColor;

struct Material{
    // Light Maps
    sampler2D diffuseTexture;
    sampler2D specularTexture;

    float shininess;
}; 

in vec2 TexCoord;

void main()
{
	FragColor = texture(diffuseTexture, TexCoord);
}