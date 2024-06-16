#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

in vec4 fragPos;

uniform vec3 viewPos;
uniform vec3 lightDirection;
uniform Material material;

vec3 normalizeRGB(vec3 rgb);
vec3 lerp(vec3 a, vec3 b, float t);

void main()
{
	vec3 topColor = normalizeRGB(vec3(30.0f, 15.0f, 50.0f));
	vec3 bottomColor = normalizeRGB(vec3(10.0f, 5.0f, 25.0f));
	vec3 moonColor = normalizeRGB(vec3(255, 255, 255));

	vec3 viewDirection = normalize(fragPos.xyz - viewPos);
	float moon = max(pow(dot(viewDirection, normalize(lightDirection)), material.shininess), 0.0f);

	FragColor = vec4(lerp(bottomColor, topColor, max(viewDirection.y, 0.0)) + moon * moonColor, 1.0f);
}

vec3 normalizeRGB(vec3 rgb){
	return vec3(rgb.x / 255.0f, rgb.y / 255.0f, rgb.z / 255.0f);
}

vec3 lerp(vec3 a, vec3 b, float t){
	return a + (b - a) * t;
}