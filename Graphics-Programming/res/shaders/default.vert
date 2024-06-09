#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

out vec3 fragPos;
out vec2 texCoord;
out mat3 tbn;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = vec3(model * vec4(aPos, 1.0));
	texCoord = aTexCoord;
	normal = mat3(transpose(inverse(model))) * aNormal; // Inversing matrices is a costly operation. Better to calculate the normal matrix on the CPU
	vec3 n = normalize(mat3(model) * aNormal);
	vec3 t = normalize(mat3(model) * aTangent);
	vec3 b = normalize(mat3(model) * aBiTangent);
	tbn = mat3(t, b, n);

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}