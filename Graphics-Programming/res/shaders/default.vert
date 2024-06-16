#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

out vec3 fragPos;
out vec2 texCoord;
out mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = vec3(model * vec4(aPos, 1.0));
	texCoord = aTexCoord;
	vec3 n = normalize(vec3(model * vec4(aNormal, 0.0f)));
	vec3 t = normalize(vec3(model * vec4(aTangent, 0.0f)));
	vec3 b = normalize(vec3(model * vec4(aBiTangent, 0.0f)));
	tbn = mat3(t, b, n);

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}