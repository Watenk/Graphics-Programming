#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = vec3(model * vec4(aPos, 1.0));
	texCoord = aTexCoord;
	normal = mat3(transpose(inverse(model))) * aNormal; // Inversing matrices is a costly operation. Better to calculate the normal matrix on the CPU

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}