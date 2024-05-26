#include "Shader.h"

#include <glad/glad.h>
#include <iostream>

#include "util/FileUtil.h"

// Public

Shader::Shader(const std::string& shadersPath, const std::string& shaderName){
    // Shader Parseing
    std::string vertexString = FileUtil::parsePath(shadersPath + "/" + shaderName + ".vert");
    std::string fragmentString = FileUtil::parsePath(shadersPath + "/" + shaderName + ".frag");

    // Shader Compilation
    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexString);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentString);

    // Shader Program
    shaderProgramID = createShaderProgram(vertexShader, fragmentShader);
}

Shader::~Shader(){
    glDeleteProgram(shaderProgramID);
}

void Shader::bind() const{
    glUseProgram(shaderProgramID);
}

unsigned int Shader::getID() const{
    return shaderProgramID;
}

void Shader::setVec4(const char* name, glm::vec4 data){
    glUniform4f(getUniformLocation(name), data.x, data.y, data.z, data.w);
}

void Shader::setVec3(const char* name, glm::vec3 data){
    glUniform3f(getUniformLocation(name), data.x, data.y, data.z);
}

void Shader::setVec2(const char* name, glm::vec2 data){
    glUniform2f(getUniformLocation(name), data.x, data.y);
}

void Shader::setFloat(const char* name, float data){
    glUniform1f(getUniformLocation(name), data);
}

void Shader::setInt(const char* name, int data){
    glUniform1i(getUniformLocation(name), data);
}

void Shader::setUInt(const char* name, unsigned int data){
    glUniform1ui(getUniformLocation(name), data);
}

void Shader::setVec4Array(const char* name, std::vector<glm::vec4> data){
    float floatArray[data.size() * 4];
    int index = 0;
    for (int i = 0; i < data.size(); i++) {
        floatArray[index++] = data[i].x;
        floatArray[index++] = data[i].y;
        floatArray[index++] = data[i].z;
        floatArray[index++] = data[i].w;
    }
    glUniform2fv(getUniformLocation(name), data.size(), floatArray);
}

void Shader::setVec3Array(const char* name, std::vector<glm::vec3> data){
    float floatArray[data.size() * 3];
    int index = 0;
    for (int i = 0; i < data.size(); i++) {
        floatArray[index++] = data[i].x;
        floatArray[index++] = data[i].y;
        floatArray[index++] = data[i].z;
    }
    glUniform2fv(getUniformLocation(name), data.size(), floatArray);
}

void Shader::setVec2Array(const char* name, std::vector<glm::vec2> data){
    float floatArray[data.size() * 2];
    int index = 0;
    for (int i = 0; i < data.size(); i++) {
        floatArray[index++] = data[i].x;
        floatArray[index++] = data[i].y;
    }
    glUniform2fv(getUniformLocation(name), data.size(), floatArray);
}

void Shader::setFloatArray(const char* name, std::vector<float> data){
    glUniform1fv(getUniformLocation(name), data.size(), data.data());
}

void Shader::setIntArray(const char* name, std::vector<int> data){
    glUniform1iv(getUniformLocation(name), data.size(), data.data());
}

void Shader::setUIntArray(const char* name, std::vector<unsigned int> data){
    glUniform1uiv(getUniformLocation(name), data.size(), data.data());
}

// Private

const unsigned int Shader::compileShader(const unsigned int type, const std::string& source){
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // Error handling
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader Compilation Failed\n" << infoLog << std::endl;
    }

    return shader;
}

const unsigned int Shader::createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader){
    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Error handling
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    // Check for validation errors
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader Program Validation Failed: " << infoLog << std::endl;
    }

    // The shaders are attached to the program so they can be deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int Shader::getUniformLocation(const char* name){
    bind();
    return glGetUniformLocation(shaderProgramID, name);
}