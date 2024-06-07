#version 330 core
out vec4 FragColor;

uniform vec3 viewDirection;

vec3 normalizeRGB(vec3 rgb);
vec3 lerp(vec3 a, vec3 b, float t);

void main()
{
	vec3 topColor = normalizeRGB(vec3(68.0f, 118.0f, 189.0f));
	vec3 bottomColor = normalizeRGB(vec3(188.0f, 214.0f, 231.0f));

	FragColor = vec4(lerp(bottomColor, topColor, abs(viewDirection.y)), 1.0f);
}

vec3 normalizeRGB(vec3 rgb){
	return vec3(rgb.x / 255.0f, rgb.y / 255.0f, rgb.z / 255.0f);
}

vec3 lerp(vec3 a, vec3 b, float t){
	return a + (b - a) * t;
}